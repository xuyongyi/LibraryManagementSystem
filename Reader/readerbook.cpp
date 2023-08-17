#include "readerbook.h"
#include "ui_readerbook.h"

ReaderBook::ReaderBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderBook)
{
    ui->setupUi(this);
    init();
    connectslots();
}

ReaderBook::~ReaderBook()
{
    delete ui;
}

void ReaderBook::init()	//初始化
{
    //ui->widget->setEnabled(false);
    setBookInfoHeader();
    gSetTableWidgetMode(ui->tw_BookInfo);
}
void ReaderBook::connectslots()	//连接信号与槽
{
    connect(ui->pb_SearchBookInfo, SIGNAL(clicked()), this, SLOT(slt_Search()));
    connect(ui->pb_LookBookInfo, SIGNAL(clicked()), this, SLOT(slt_Look()));
    connect(ui->pb_Borrow, SIGNAL(clicked()), this, SLOT(slt_Borrow()));
    connect(ui->pb_Order, SIGNAL(clicked()), this, SLOT(slt_Order()));
    connect(ui->tw_BookInfo, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(slt_BookInfoSClicked(QTableWidgetItem *)));

}
void ReaderBook::setInitWidget()	//设置显示界面
{
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    gAddList2CB(ui->cb_Cond, gFindCond);
    gAddList2CB(ui->comb_bookLanguage, gBookLanguage);
    gAddList2CB(ui->comb_bookType, gBookClass);
    clearBookInfoFormInfo();
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    flushBookInfoList();
}

void ReaderBook::slt_Search()
{
    int condIndex = ui->cb_Cond->currentIndex();
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    QString key = ui->le_Key->text().trimmed();
    if (key == "")
    {
        gWarnning("请输入查询关键字!");
        return;
    }
    map<string, BookInfo> temp = gAllBooks;
    gAllBooks.clear();
    map<string, BookInfo>::iterator iter = temp.begin();
    for (;iter != temp.end();iter++)
    {
        BookInfo info = iter->second;
        QString condStr;
        if (condIndex == 0)
        {
            QString bookID = gStr2QStr(info.bookID);
            QString bookIndex = gStr2QStr(info.bookIndex);
            QString bookClassID = gStr2QStr(info.bookClassID);
            QString bookName = gStr2QStr(info.bookName);
            QString bookAuth = gStr2QStr(info.bookAuth);
            QString bookPublish = gStr2QStr(info.bookPublish);
            QString bookPushDate = gStr2QStr(info.bookPushDate);
            QString bookISBN = gStr2QStr(info.bookISBN);
            QString bookDesc = gStr2QStr(info.bookDesc);
            QString bookLanguage = gStr2QStr(info.bookLanguage);
            QString bookType = gStr2QStr(info.bookType);

            if (bookID.contains(key) || bookIndex.contains(key) || bookClassID.contains(key) || bookName.contains(key) || bookAuth.contains(key) || bookPublish.contains(key) || bookPushDate.contains(key) || bookISBN.contains(key) || bookDesc.contains(key) || bookLanguage.contains(key) || bookType.contains(key))
            {
                gAllBooks[iter->first] = info;
            }
            return;
        }
        else if (condIndex == 1)
        {
            condStr = gStr2QStr(info.bookID);
        }
        else if (condIndex == 2)
        {
            condStr = gStr2QStr(info.bookName);
        }
        else if (condIndex == 3)
        {
            condStr = gStr2QStr(info.bookAuth);
        }
        else if (condIndex == 4)
        {
            condStr = gStr2QStr(info.bookPublish);
        }
        else if (condIndex == 5)
        {
            condStr = gStr2QStr(info.bookISBN);
        }
        if (condStr.contains(key))
        {
            gAllBooks[iter->first] = info;
        }
        /*QString bookID = gStr2QStr(info.bookID);
        QString bookIndex = gStr2QStr(info.bookIndex);
        QString bookClassID = gStr2QStr(info.bookClassID);
        QString bookName = gStr2QStr(info.bookName);
        QString bookAuth = gStr2QStr(info.bookAuth);
        QString bookPublish = gStr2QStr(info.bookPublish);
        QString bookPushDate = gStr2QStr(info.bookPushDate);
        QString bookISBN = gStr2QStr(info.bookISBN);
        QString bookDesc = gStr2QStr(info.bookDesc);
        QString bookLanguage = gStr2QStr(info.bookLanguage);
        QString bookType = gStr2QStr(info.bookType);

        if (bookID.contains(key) || bookIndex.contains(key) || bookClassID.contains(key) || bookName.contains(key) || bookAuth.contains(key) || bookPublish.contains(key) || bookPushDate.contains(key) || bookISBN.contains(key) || bookDesc.contains(key) || bookLanguage.contains(key) || bookType.contains(key))
        {
        gAllBooks[iter->first] = info;
        }*/
    }
    clearBookInfoFormInfo();
    flushBookInfoList();
    return;
}
void ReaderBook::slt_Look()
{
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    clearBookInfoFormInfo();
    flushBookInfoList();
}

void ReaderBook::slt_Borrow()	//借阅
{
    if (m_SelectBook.id == -1)
    {
        gWarnning("请先选择读者与书籍!");
        return;
    }
    BookInfo book = gAllBooks.find(m_SelectBook.bookID)->second;
    if (book.noBorrowSize <= 0)
    {
        gWarnning("在馆数量不足!");
        return;
    }
    m_ReaderWarn.setInitWidget1();
    if (m_ReaderWarn.m_Records.size() > 0)
    {
        gWarnning("存在逾期未归还书籍,不能借阅!");
        return;
    }

    BookBRRecordInfo record;
    record.borrowID = gGetDateTimemsStr();
    record.readerID = gCurrReader.readerID;
    record.bookID = m_SelectBook.bookID;
    record.bookISBN = book.bookISBN;
    int jysc = atoi(gConfInfo.jysc.c_str()) * 24 * 60 * 60;
    //QDateTime currTime = QDateTime::currentDateTime();	//获取当前时间
    QDateTime currTime = ui->dateTimeEdit->dateTime();	//获取当前时间
    calcBeginEndTime(currTime, jysc, record.borrowTime, record.returnTime);
    record.realTime = "";
    record.returnStat = 0;
    gMySqlFunc.insertBookBRRecordInfoTable(gError, record); //插入借阅记录
    //修改图书剩余数量
    book.noBorrowSize--;
    book.borrowedSize++;
    gMySqlFunc.updateBookInfoTable(gError, book);

    //修改读者读书数量
    gCurrReader.borrowBookSize++;
    gCurrReader.readBookSize++;
    gCurrReader.existNoReturn = 1;
    gMySqlFunc.updateReaderInfoTable(gError, gCurrReader);

    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    flushBookInfoList();
    m_SelectBook.id = -1;
    gWarnning("借阅成功!");
    return;
}
void ReaderBook::slt_Order()	//预约
{
    if (m_SelectBook.id == -1)
    {
        gWarnning("请先选择读者与书籍!");
        return;
    }
    OrderInfo record;
    record.orderID = gGetDateTimemsStr();
    record.readerID = gCurrReader.readerID;
    record.bookID = m_SelectBook.bookID;
    QDateTime currTime = ui->dateTimeEdit->dateTime();	//获取当前时间
    int yyzq = atoi(gConfInfo.order.c_str()) * 24 * 60 * 60;	//预约周期
    calcBeginEndTime(currTime, yyzq, record.orderTime, record.orderFinishTime);
    record.orderStat = 0;
    record.isOverTime = 0;
    record.waitStat = 1;
    gMySqlFunc.insertOrderInfoTable(gError, record);
    gWarnning("预约成功!");
    return;
}
void ReaderBook::slt_BookInfoSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
{
    int count = item->row();
    int row = 0;
    map<string, BookInfo>::iterator iter = gAllBooks.begin();
    for (;iter != gAllBooks.end();iter++)
    {
        if (row == count)
        {
            m_SelectBook = iter->second;
            showBookInfoFormInfo(m_SelectBook);
            break;
        }
        row++;
    }
}

void ReaderBook::clearBookInfoFormInfo()
{
    ui->le_bookID->setText("");
    ui->le_bookIndex->setText("");
    ui->le_bookClassID->setText("");
    ui->le_bookName->setText("");
    ui->le_bookAuth->setText("");
    ui->le_bookPublish->setText("");
    //ui->le_bookPushDate->setText("");
    ui->le_bookISBN->setText("");
    ui->te_bookDesc->setPlainText("");
    m_SelectBook.id = -1;
}

void ReaderBook::showBookInfoFormInfo(BookInfo info)	//显示图书信息信息
{
    ui->le_bookID->setText(gStr2QStr(info.bookID));
    ui->le_bookIndex->setText(gStr2QStr(info.bookIndex));
    ui->le_bookClassID->setText(gStr2QStr(info.bookClassID));
    ui->le_bookName->setText(gStr2QStr(info.bookName));
    ui->le_bookAuth->setText(gStr2QStr(info.bookAuth));
    ui->le_bookPublish->setText(gStr2QStr(info.bookPublish));
    QString dateStr = gStr2QStr(info.bookPushDate);
    QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
    ui->le_bookPushDate->setDate(date);
    ui->le_bookISBN->setText(gStr2QStr(info.bookISBN));
    ui->te_bookDesc->setPlainText(gStr2QStr(info.bookDesc));
    ui->comb_bookLanguage->setCurrentText(gStr2QStr(info.bookLanguage));
    ui->comb_bookType->setCurrentText(gStr2QStr(info.bookType));
}
void ReaderBook::setBookInfoHeader()	//设置图书信息信息列表头部显示信息
{
    QStringList headers;
    headers << ("图书条码") << ("图书索引号") << ("书籍分类号") << ("图书名称") << ("图书作者") << ("出版社") << ("图书发布时间") << ("图书ISBN号") << ("图书简短介绍") << ("图书语言") << ("图书价格") << ("图书分类") << ("总数量") << ("未借出数量") << ("借出数量");
    ui->tw_BookInfo->setColumnCount(headers.size());
    //ui->tw_BookInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_BookInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_BookInfo->setHorizontalHeaderLabels(headers);
}
void ReaderBook::flushBookInfoList()	//刷新图书信息信息列表
{
    ui->tw_BookInfo->setRowCount(gAllBooks.size());
    int row = 0;
    map<string, BookInfo>::iterator iter = gAllBooks.begin();
    for (;iter != gAllBooks.end();iter++)
    {
        BookInfo info = iter->second;
        ui->tw_BookInfo->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.bookID)));
        ui->tw_BookInfo->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookIndex)));
        ui->tw_BookInfo->setItem(row, 2, new QTableWidgetItem(gStr2QStr(info.bookClassID)));
        ui->tw_BookInfo->setItem(row, 3, new QTableWidgetItem(gStr2QStr(info.bookName)));
        ui->tw_BookInfo->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.bookAuth)));
        ui->tw_BookInfo->setItem(row, 5, new QTableWidgetItem(gStr2QStr(info.bookPublish)));
        ui->tw_BookInfo->setItem(row, 6, new QTableWidgetItem(gStr2QStr(info.bookPushDate)));
        ui->tw_BookInfo->setItem(row, 7, new QTableWidgetItem(gStr2QStr(info.bookISBN)));
        ui->tw_BookInfo->setItem(row, 8, new QTableWidgetItem(gStr2QStr(info.bookDesc)));
        ui->tw_BookInfo->setItem(row, 9, new QTableWidgetItem(gStr2QStr(info.bookLanguage)));
        ui->tw_BookInfo->setItem(row, 10, new QTableWidgetItem(QString::number(info.bookPrice)));
        ui->tw_BookInfo->setItem(row, 11, new QTableWidgetItem(gStr2QStr(info.bookType)));
        ui->tw_BookInfo->setItem(row, 12, new QTableWidgetItem(QString::number(info.totalSize)));
        ui->tw_BookInfo->setItem(row, 13, new QTableWidgetItem(QString::number(info.noBorrowSize)));
        ui->tw_BookInfo->setItem(row, 14, new QTableWidgetItem(QString::number(info.borrowedSize)));
        row++;
    }
}

//void ReaderBook::flushBookInfoListSort()
//{
//	ui->tw_BookInfo->setRowCount(m_SortedVec.size());
//	int row = 0;
//	vector<SortData>::iterator iter = m_SortedVec.begin();
//	for (;iter != m_SortedVec.end();iter++)
//	{
//		SortData data = *iter;
//		if (gAllBooks.count(data.id))
//		{
//			BookInfo info = gAllBooks.find(data.id)->second;
//			ui->tw_BookInfo->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.bookID)));
//			ui->tw_BookInfo->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookIndex)));
//			ui->tw_BookInfo->setItem(row, 2, new QTableWidgetItem(gStr2QStr(info.bookClassID)));
//			ui->tw_BookInfo->setItem(row, 3, new QTableWidgetItem(gStr2QStr(info.bookName)));
//			ui->tw_BookInfo->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.bookAuth)));
//			ui->tw_BookInfo->setItem(row, 5, new QTableWidgetItem(gStr2QStr(info.bookPublish)));
//			ui->tw_BookInfo->setItem(row, 6, new QTableWidgetItem(gStr2QStr(info.bookPushDate)));
//			ui->tw_BookInfo->setItem(row, 7, new QTableWidgetItem(gStr2QStr(info.bookISBN)));
//			ui->tw_BookInfo->setItem(row, 8, new QTableWidgetItem(gStr2QStr(info.bookDesc)));
//			ui->tw_BookInfo->setItem(row, 9, new QTableWidgetItem(gStr2QStr(info.bookLanguage)));
//			ui->tw_BookInfo->setItem(row, 10, new QTableWidgetItem(QString::number(info.bookPrice)));
//			ui->tw_BookInfo->setItem(row, 11, new QTableWidgetItem(gStr2QStr(info.bookType)));
//			ui->tw_BookInfo->setItem(row, 12, new QTableWidgetItem(QString::number(info.totalSize)));
//			ui->tw_BookInfo->setItem(row, 13, new QTableWidgetItem(QString::number(info.noBorrowSize)));
//			ui->tw_BookInfo->setItem(row, 14, new QTableWidgetItem(QString::number(info.borrowedSize)));
//			row++;
//		}
//
//	}
//}

void ReaderBook::calcBeginEndTime(QDateTime curr, int zq, string &start, string &end)
{
    start = gQStr2Str(curr.toString("yyyy-MM-dd hh:mm:ss"));
    QDateTime backTime = curr.addSecs(zq);
    end = gQStr2Str(backTime.toString("yyyy-MM-dd hh:mm:ss"));
    return;
}
