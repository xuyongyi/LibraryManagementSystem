#include "adminbrrecord.h"
#include "ui_adminbrrecord.h"

AdminBRRecord::AdminBRRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminBRRecord)
{
    ui->setupUi(this);
    init();
    connectslots();
}

AdminBRRecord::~AdminBRRecord()
{
    delete ui;
}

void AdminBRRecord::init()	//初始化
{
    ui->le_UserID->setEnabled(false);
    ui->le_BookID->setEnabled(false);
    m_SelectUser.id = -1;
    m_SelectBook.id = -1;
    m_SelectRecord.id = -1;
    m_currRecordWidgetIndex = -1;

    setUserHeader();
    gSetTableWidgetMode(ui->tw_User);
    setBookHeader();
    gSetTableWidgetMode(ui->tw_Book);
}
void AdminBRRecord::connectslots()	//连接信号与槽
{
    connect(ui->pb_LookUser,SIGNAL(clicked()),this,SLOT(slt_LookUser()));
    connect(ui->pb_FindUser, SIGNAL(clicked()), this, SLOT(slt_FindUser()));
    connect(ui->pb_LookBook, SIGNAL(clicked()), this, SLOT(slt_LookBook()));
    connect(ui->pb_FindBook, SIGNAL(clicked()), this, SLOT(slt_FindBook()));

    connect(ui->tw_User, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_UserSClicked(QTableWidgetItem *)));
    connect(ui->tw_Book, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_BookSClicked(QTableWidgetItem *)));

    connect(ui->pb_JY, SIGNAL(clicked()), this, SLOT(slt_JY()));
    connect(ui->pb_Order, SIGNAL(clicked()), this, SLOT(slt_Order()));
}
void AdminBRRecord::setInitWidget()	//设置显示界面
{
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    flushUserList(gAllReaders);
    flushBookList(gAllBooks);
}

void AdminBRRecord::slt_LookUser()	//浏览读者
{
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    flushUserList(gAllReaders);
}
void AdminBRRecord::slt_FindUser()	//查询读者
{
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    QString key = ui->le_KeyUser->text().trimmed();
    if (key == "")
    {
        gWarnning("请输入查询关键字!");
        return;
    }
    map<string, ReaderInfo> temp = gAllReaders;
    gAllReaders.clear();
    map<string, ReaderInfo>::iterator iter = temp.begin();
    for (;iter != temp.end();iter++)
    {
        ReaderInfo info = iter->second;
        QString readerID = gStr2QStr(info.readerID);
        QString readerPwd = gStr2QStr(info.readerPwd);
        QString readerName = gStr2QStr(info.readerName);
        QString readerPhone = gStr2QStr(info.readerPhone);
        QString readerClassID = gStr2QStr(info.readerClassID);
        QString readerCollege = gStr2QStr(info.readerCollege);
        QString touxiangName = gStr2QStr(info.touxiangName);

        if (readerID.contains(key) || readerPwd.contains(key) || readerName.contains(key) || readerPhone.contains(key) || readerClassID.contains(key) || readerCollege.contains(key) || readerCollege.contains(key) || touxiangName.contains(key))
        {
            gAllReaders[iter->first] = info;
        }
    }
    flushUserList(gAllReaders);
    return;
}

void AdminBRRecord::slt_LookBook()	//浏览书籍
{
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    flushBookList(gAllBooks);
}
void AdminBRRecord::slt_FindBook()	//查询书籍
{
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
    QString key = ui->le_KeyBook->text().trimmed();
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
    }
    flushBookList(gAllBooks);
    return;
}

void AdminBRRecord::slt_JY()	//借阅
{
    if (ui->le_UserID->text() == "" || ui->le_BookID->text() == "" || m_SelectUser.id == -1 || m_SelectBook.id == -1)
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
    BookBRRecordInfo record;
    record.borrowID = gGetDateTimemsStr();
    record.readerID = m_SelectUser.readerID;
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
    m_SelectUser.borrowBookSize++;
    m_SelectUser.readBookSize++;
    m_SelectUser.existNoReturn = 1;
    gMySqlFunc.updateReaderInfoTable(gError, m_SelectUser);
    flushAllData();
    m_SelectUser.id = -1;
    m_SelectBook.id = -1;
    ui->le_UserID->setText("");
    ui->le_BookID->setText("");
    gWarnning("借阅成功!");
    return;
}

void AdminBRRecord::slt_Order()	//预约
{
    if (ui->le_UserID->text() == "" || ui->le_BookID->text() == "" || m_SelectUser.id == -1 || m_SelectBook.id == -1)
    {
        gWarnning("请先选择读者与书籍!");
        return;
    }
    OrderInfo record;
    record.orderID = gGetDateTimemsStr();
    record.readerID = m_SelectUser.readerID;
    record.bookID = m_SelectBook.bookID;
    QDateTime currTime = ui->dateTimeEdit->dateTime();	//获取当前时间
    int yyzq = atoi(gConfInfo.order.c_str())*24 * 60 * 60;	//预约周期
    calcBeginEndTime(currTime, yyzq, record.orderTime, record.orderFinishTime);
    record.orderStat = 0;
    record.isOverTime = 0;
    record.waitStat = 1;
    gMySqlFunc.insertOrderInfoTable(gError, record);
    gWarnning("预约成功!");
    return;
}


void AdminBRRecord::slt_UserSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
{
    int count = item->row();
    int row = 0;
    map<string, ReaderInfo>::iterator iter = gAllReaders.begin();
    for (;iter != gAllReaders.end();iter++)
    {
        if (row == count)
        {
            m_SelectUser = iter->second;
            ui->le_UserID->setText(gStr2QStr(m_SelectUser.readerID));
            break;
        }
        row++;
    }
}

void AdminBRRecord::slt_BookSClicked(QTableWidgetItem *item)
{
    int count = item->row();
    int row = 0;
    map<string, BookInfo>::iterator iter = gAllBooks.begin();
    for (;iter != gAllBooks.end();iter++)
    {
        if (row == count)
        {
            m_SelectBook = iter->second;
            ui->le_BookID->setText(gStr2QStr(m_SelectUser.readerID));
            break;
        }
        row++;
    }
}


void AdminBRRecord::setUserHeader()
{
    QStringList headers;
    headers << ("学号/职工号") << ("姓名") ;
    ui->tw_User->setColumnCount(headers.size());
    //ui->tw_User->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_User->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_User->setHorizontalHeaderLabels(headers);
}
void AdminBRRecord::flushUserList(map<string, ReaderInfo> readers)
{
    ui->tw_User->setRowCount(readers.size());
    int row = 0;
    map<string, ReaderInfo>::iterator iter = readers.begin();
    for (;iter != readers.end();iter++)
    {
        ReaderInfo info = iter->second;
        ui->tw_User->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.readerID)));
        ui->tw_User->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.readerName)));
        row++;
    }
}
void AdminBRRecord::setBookHeader()
{
    QStringList headers;
    headers << ("书籍条码") << ("书籍名称") <<"ISBN号"<< "作者" << "借出数量" << "剩余数量" << "语言";
    ui->tw_Book->setColumnCount(headers.size());
    //ui->tw_Book->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_Book->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_Book->setHorizontalHeaderLabels(headers);
}
void AdminBRRecord::flushBookList(map<string, BookInfo> books)
{
    ui->tw_Book->setRowCount(books.size());
    int row = 0;
    map<string, BookInfo>::iterator iter = books.begin();
    for (;iter != books.end();iter++)
    {
        BookInfo info = iter->second;
        ui->tw_Book->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.bookID)));
        ui->tw_Book->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookName)));
        ui->tw_Book->setItem(row, 2, new QTableWidgetItem(gStr2QStr(info.bookISBN)));
        ui->tw_Book->setItem(row, 3, new QTableWidgetItem(gStr2QStr(info.bookAuth)));
        ui->tw_Book->setItem(row, 4, new QTableWidgetItem(QString::number(info.borrowedSize)));
        ui->tw_Book->setItem(row, 5, new QTableWidgetItem(QString::number(info.noBorrowSize)));
        ui->tw_Book->setItem(row,6, new QTableWidgetItem(gStr2QStr(info.bookLanguage)));
        row++;
    }
}

void AdminBRRecord::flushAllData()
{
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    flushUserList(gAllReaders);
    flushBookList(gAllBooks);
}

void AdminBRRecord::calcBeginEndTime(QDateTime curr, int zq, string &start, string &end)
{
    start = gQStr2Str(curr.toString("yyyy-MM-dd hh:mm:ss"));
    QDateTime backTime = curr.addSecs(zq);
    end = gQStr2Str(backTime.toString("yyyy-MM-dd hh:mm:ss"));
    return;
}
