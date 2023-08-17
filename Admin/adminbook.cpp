#include "adminbook.h"
#include "ui_adminbook.h"

AdminBook::AdminBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminBook)
{
    ui->setupUi(this);
    init();
    connectslots();
}

AdminBook::~AdminBook()
{
    delete ui;
}

void AdminBook::init()
{
    setBookInfoHeader();
    gSetTableWidgetMode(ui->tw_BookInfo);
}

void AdminBook::connectslots()
{
    connect(&m_AdminAddBook, SIGNAL(sig_Add()), this, SLOT(slt_flushData()));
    connect(ui->pb_AddBookInfo, SIGNAL(clicked()), this, SLOT(slt_AddBookInfo()));
    connect(ui->pb_DelBookInfo, SIGNAL(clicked()), this, SLOT(slt_DelBookInfo()));
    connect(ui->pb_ResetBookInfo, SIGNAL(clicked()), this, SLOT(slt_ResetBookInfo()));
    connect(ui->pb_SearchBookInfo, SIGNAL(clicked()), this, SLOT(slt_SearchBookInfo()));
    connect(ui->pb_LookBookInfo, SIGNAL(clicked()), this, SLOT(slt_LookBookInfo()));
    connect(ui->pb_ClearBookInfo, SIGNAL(clicked()), this, SLOT(slt_ClearBookInfo()));
    connect(ui->tw_BookInfo, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(slt_BookInfoSClicked(QTableWidgetItem *)));
}

void AdminBook::setInitWidget()
{
    gAddList2CB(ui->cb_Cond, gFindCond);
    gAddList2CB(ui->comb_bookLanguage, gBookLanguage);
    gAddList2CB(ui->comb_bookType, gBookClass);
    ui->le_bookPushDate->setDate(QDate::currentDate());
    clearBookInfoFormInfo();
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    flushBookInfoList();
}

BookInfo AdminBook::getBookInfoFormInfo()
{
    int n = 0;
    BookInfo info;
    string bookID = gQStr2Str(ui->le_bookID->text());
    string bookIndex = gQStr2Str(ui->le_bookIndex->text());
    string bookClassID = gQStr2Str(ui->le_bookClassID->text());
    string bookName = gQStr2Str(ui->le_bookName->text());
    string bookAuth = gQStr2Str(ui->le_bookAuth->text());
    string bookPublish = gQStr2Str(ui->le_bookPublish->text());
    string bookPushDate = gQStr2Str(ui->le_bookPushDate->date().toString("yyyy-MM-dd"));
    string bookISBN = gQStr2Str(ui->le_bookISBN->text());
    string bookDesc = gQStr2Str(ui->te_bookDesc->toPlainText());
    string bookLanguage = gQStr2Str(ui->comb_bookLanguage->currentText());
    float bookPrice = ui->le_bookPrice->text().toFloat();
    string bookType = gQStr2Str(ui->comb_bookType->currentText());
    int totalSize = ui->le_totalSize->text().toInt();
    int noBorrowSize = totalSize;
    int borrowedSize = 0;
    info.bookID = bookID;
    info.bookIndex = bookIndex;
    info.bookClassID = bookClassID;
    info.bookName = bookName;
    info.bookAuth = bookAuth;
    info.bookPublish = bookPublish;
    info.bookPushDate = bookPushDate;
    info.bookISBN = bookISBN;
    info.bookDesc = bookDesc;
    info.bookLanguage = bookLanguage;
    info.bookPrice = bookPrice;
    info.bookType = bookType;
    info.totalSize = totalSize;
    info.noBorrowSize = noBorrowSize;
    info.borrowedSize = borrowedSize;
    return info;
}

void AdminBook::clearBookInfoFormInfo()
{
    int m = 0;
    ui->le_bookID->setText("");
    ui->le_bookIndex->setText("");
    ui->le_bookClassID->setText("");
    ui->le_bookName->setText("");
    ui->le_bookAuth->setText("");
    ui->le_bookPublish->setText("");
    //ui->le_bookPushDate->setText("");
    ui->le_bookISBN->setText("");
    ui->te_bookDesc->setPlainText("");
    ui->le_bookPrice->setText("");
    ui->le_totalSize->setText("");
    mSelectBookInfoItem.id = -1;
}

void AdminBook::showBookInfoFormInfo(BookInfo info)
{
    int m = 0;
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
    ui->le_bookPrice->setText(QString::number(info.bookPrice));
    ui->comb_bookType->setCurrentText(gStr2QStr(info.bookType));
    ui->le_totalSize->setText(QString::number(info.totalSize));
}

void AdminBook::setBookInfoHeader()
{
    QStringList headers;
    headers << ("图书编号(条码)") << ("图书索引号") << ("书籍分类号") << ("图书名称") << ("图书作者") << ("出版社") << ("图书发布时间") << ("图书ISBN号") << ("图书简短介绍") << ("图书语言") << ("图书价格") << ("图书分类") << ("总数量") << ("未借出数量") << ("借出数量");
    ui->tw_BookInfo->setColumnCount(headers.size());
    //ui->tw_BookInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_BookInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_BookInfo->setHorizontalHeaderLabels(headers);
}

void AdminBook::flushBookInfoList()
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

int AdminBook::isExistBookInfoKey(string bookID)	//查看关键字是否重复
{
    map<string, BookInfo>::iterator iter = gAllBooks.begin();
    for (;iter != gAllBooks.end();iter++)
    {
        if (iter->second.bookID == bookID)
        {
            return 1;
        }
    }
    return 0;
}

void AdminBook::slt_AddBookInfo()
{
    m_AdminAddBook.setInitWidget();
    m_AdminAddBook.show();
    /*BookInfo info = getBookInfoFormInfo();
    if (info.bookID == "" || info.bookIndex == "" || info.bookClassID == "" || info.bookName == "" || info.bookAuth == "" || info.bookPublish == "" || info.bookPushDate == "" || info.bookISBN == "")
    {
        gWarnning("存在未填写项!");
        return;
    }
    if (isExistBookInfoKey(info.bookID))
    {
        gWarnning("图书编号(唯一值,条形码)已存在,添加失败!");
        return;
    }
    gMySqlFunc.insertBookInfoTable(gError, info);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    clearBookInfoFormInfo();
    flushBookInfoList();
    return;*/
}

void AdminBook::slt_DelBookInfo()
{
    if (mSelectBookInfoItem.id == -1)
    {
        gWarnning("请先选择要删除的图书信息!");
        return;
    }
    if(gWarnningDel("确认删除?") == 0)
    {
        return;
    }
    gMySqlFunc.deleteBookInfoTable(gError, mSelectBookInfoItem);
    gMySqlFunc.deleteCondTableStr(gError, "BookBRRecordInfo", "bookID", mSelectBookInfoItem.bookID);	//删除借阅记录
    gMySqlFunc.deleteCondTableStr(gError, "OrderInfo", "bookID", mSelectBookInfoItem.bookID);	//删除预订
    //根据实际需要增加删除关联的数据库数据信息代码
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    clearBookInfoFormInfo();
    flushBookInfoList();
    return;
}

void AdminBook::slt_ResetBookInfo()
{
    if (mSelectBookInfoItem.id == -1)
    {
        gWarnning("请先选择要删除的图书信息!");
        return;
    }
    BookInfo info = getBookInfoFormInfo();
    info.id = mSelectBookInfoItem.id;
    info.totalSize = mSelectBookInfoItem.totalSize;
    info.borrowedSize = mSelectBookInfoItem.borrowedSize;
    info.noBorrowSize = mSelectBookInfoItem.noBorrowSize;
    if (info.bookID == "" || info.bookIndex == "" || info.bookClassID == "" || info.bookName == "" || info.bookAuth == "" || info.bookPublish == "" || info.bookPushDate == "" || info.bookISBN == "")
    {
        gWarnning("存在未填写项!");
        return;
    }
    if (info.bookID != mSelectBookInfoItem.bookID)
    {
        if (isExistBookInfoKey(info.bookID))//关键字发生变化
        {
            gWarnning("图书编号(唯一值,条形码)已存在,修改失败!");
            return;
        }
    }
    gMySqlFunc.updateBookInfoTable(gError, info);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    clearBookInfoFormInfo();
    flushBookInfoList();
    return;
}

void AdminBook::slt_SearchBookInfo()
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

void AdminBook::slt_LookBookInfo()
{
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    clearBookInfoFormInfo();
    flushBookInfoList();
}

void AdminBook::slt_ClearBookInfo()
{
    clearBookInfoFormInfo();
}

void AdminBook::slt_BookInfoSClicked(QTableWidgetItem *item)
{
    int count = item->row();
    int row = 0;
    map<string, BookInfo>::iterator iter = gAllBooks.begin();
    for (;iter != gAllBooks.end();iter++)
    {
        if (row == count)
        {
            mSelectBookInfoItem = iter->second;
            showBookInfoFormInfo(mSelectBookInfoItem);
            break;
        }
        row++;
    }
}

void AdminBook::slt_flushData()
{
    setInitWidget();
}
