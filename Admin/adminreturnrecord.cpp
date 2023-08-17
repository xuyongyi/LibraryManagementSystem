#include "adminreturnrecord.h"
#include "ui_adminreturnrecord.h"

AdminReturnRecord::AdminReturnRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminReturnRecord)
{
    ui->setupUi(this);
    init();
    connectslots();
}

AdminReturnRecord::~AdminReturnRecord()
{
    delete ui;
}

void AdminReturnRecord::init()	//初始化
{
    ui->le_UserID->setEnabled(false);
    ui->le_UserJYID->setEnabled(false);
    m_SelectUser.id = -1;
    m_SelectRecord.id = -1;

    setUserHeader();
    gSetTableWidgetMode(ui->tw_User);
    setUserJYHeader();
    gSetTableWidgetMode(ui->tw_UserJY);
}
void AdminReturnRecord::connectslots()	//连接信号与槽
{
    connect(ui->pb_LookUser, SIGNAL(clicked()), this, SLOT(slt_LookUser()));
    connect(ui->pb_FindUser, SIGNAL(clicked()), this, SLOT(slt_FindUser()));
    connect(ui->pb_LookUserJY, SIGNAL(clicked()), this, SLOT(slt_LookUserJY()));
    connect(ui->pb_FindUserJY, SIGNAL(clicked()), this, SLOT(slt_FindUserJY()));

    connect(ui->pb_XJ, SIGNAL(clicked()), this, SLOT(slt_XJ()));
    connect(ui->pb_GH, SIGNAL(clicked()), this, SLOT(slt_GH()));
    connect(ui->pb_Warn, SIGNAL(clicked()), this, SLOT(slt_Warn()));
    connect(ui->pb_Money, SIGNAL(clicked()), this, SLOT(slt_Money()));

    connect(ui->tw_User, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_UserSClicked(QTableWidgetItem *)));
    connect(ui->tw_UserJY, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_UserJYSClicked(QTableWidgetItem *)));
}
void AdminReturnRecord::setInitWidget()	//初始化界面显示信息
{

    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    flushUserList(gAllReaders);
}

void AdminReturnRecord::slt_LookUser()	//浏览读者
{
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    flushUserList(gAllReaders);
}
void AdminReturnRecord::slt_FindUser()	//查询读者
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
void AdminReturnRecord::slt_LookUserJY()	//浏览读者借阅情况
{
    gMySqlFunc.searchBookBRRecordInfoTableBorrowed(gError, gAllRecord, "readerID", m_SelectUser.readerID);
    flushUserJYList(gAllRecord);
}
void AdminReturnRecord::slt_FindUserJY()	//查询读者借阅情况
{
    gMySqlFunc.searchBookBRRecordInfoTableBorrowed(gError, gAllRecord, "readerID", m_SelectUser.readerID);
    QString key = ui->le_KeyUserJY->text().trimmed();
    if (key == "")
    {
        gWarnning("请输入查询关键字!");
        return;
    }
    vector<BookBRRecordInfo> temp = gAllRecord;
    gAllRecord.clear();
    vector<BookBRRecordInfo>::iterator iter = temp.begin();
    for (;iter != temp.end();iter++)
    {
        BookBRRecordInfo info = *iter;
        BookInfo book = gAllBooks.find(info.bookID)->second;
        QString bookName = gStr2QStr(book.bookName);
        QString bookAuth = gStr2QStr(book.bookAuth);
        QString bookPublish = gStr2QStr(book.bookPublish);
        QString bookISBN = gStr2QStr(book.bookISBN);
        QString bookDesc = gStr2QStr(book.bookDesc);

        if (bookName.contains(key) || bookAuth.contains(key) || bookPublish.contains(key) || bookISBN.contains(key) || bookDesc.contains(key))
        {
            gAllRecord.push_back(info);
        }
    }
    flushUserJYList(gAllRecord);
    return;
}

void AdminReturnRecord::slt_UserSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
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
            //查询用户的借阅记录(尚未归还的书籍)
            gMySqlFunc.searchBookBRRecordInfoTableBorrowed(gError, gAllRecord, "readerID", m_SelectUser.readerID);
            flushUserJYList(gAllRecord);
            break;
        }
        row++;
    }
}
void AdminReturnRecord::slt_UserJYSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
{
    int count = item->row();
    m_SelectRecord = gAllRecord[count];
    ui->le_UserJYID->setText(gStr2QStr(m_SelectRecord.borrowID));
}

void AdminReturnRecord::slt_XJ()	//续借
{
    if (m_SelectRecord.id == -1)
    {
        gWarnning("请先选择借阅记录!");
        return;
    }
    int jysc = atoi(gConfInfo.jysc.c_str()) * 24 * 60 * 60;
    QString str = gStr2QStr(m_SelectRecord.returnTime);
    QDateTime tempTime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
    QDateTime backTime = tempTime.addSecs(jysc);
    m_SelectRecord.returnTime = gQStr2Str(backTime.toString("yyyy-MM-dd hh:mm:ss"));
    gMySqlFunc.updateBookBRRecordInfoTable(gError, m_SelectRecord);
    gMySqlFunc.searchBookBRRecordInfoTableBorrowed(gError, gAllRecord, "readerID", m_SelectUser.readerID);
    flushUserJYList(gAllRecord);
    m_SelectRecord.id = -1;
    ui->le_UserJYID->setText("");
    gWarnning("续借成功!");
    return;
}
void AdminReturnRecord::slt_GH()	//归还
{
    if (m_SelectRecord.id == -1)
    {
        gWarnning("请先选择借阅记录!");
        return;
    }
    QDateTime currTime = QDateTime::currentDateTime();	//获取当前时间
    m_SelectRecord.realTime = gQStr2Str(currTime.toString("yyyy-MM-dd hh:mm:ss"));
    m_SelectRecord.returnStat = 1;
    gMySqlFunc.updateBookBRRecordInfoTable(gError, m_SelectRecord);
    BookInfo book = gAllBooks.find(m_SelectRecord.bookID)->second;
    //修改图书剩余数量
    book.noBorrowSize++;
    book.borrowedSize--;
    gMySqlFunc.updateBookInfoTable(gError, book);
    //修改读者信息
    ReaderInfo reader = gAllReaders.find(m_SelectRecord.readerID)->second;
    reader.borrowBookSize--;
    if (reader.borrowBookSize == 0)
    {
        reader.existNoReturn = 0;
    }
    gMySqlFunc.updateReaderInfoTable(gError, reader);
    gMySqlFunc.searchBookBRRecordInfoTableBorrowed(gError, gAllRecord, "readerID", m_SelectUser.readerID);
    flushUserJYList(gAllRecord);
    m_SelectRecord.id = -1;
    ui->le_UserJYID->setText("");
    gWarnning("归还成功!");
    return;
}
void AdminReturnRecord::slt_Warn()	//到期提醒
{
    m_AdminWarn.setInitWidget();
    m_AdminWarn.show();
}
void AdminReturnRecord::slt_Money()	//罚款信息
{
    m_AdminMoney.setInitWidget();
    m_AdminMoney.show();
}

void AdminReturnRecord::setUserHeader()
{
    QStringList headers;
    headers << ("学号/职工号") << ("姓名");
    ui->tw_User->setColumnCount(headers.size());
    ui->tw_User->setHorizontalHeaderLabels(headers);
}
void AdminReturnRecord::flushUserList(map<string, ReaderInfo> readers)
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
void AdminReturnRecord::setUserJYHeader()
{
    QStringList headers;
    headers << "借阅号" << ("书籍条码") <<"ISBN号"<< ("书籍名称") << "借阅时间" << "到期时间"<<"剩余天数";
    ui->tw_UserJY->setColumnCount(headers.size());
    ui->tw_UserJY->setHorizontalHeaderLabels(headers);
}
void AdminReturnRecord::flushUserJYList(vector<BookBRRecordInfo> records)
{
    QDateTime currTime = QDateTime::currentDateTime();
    ui->tw_UserJY->setRowCount(records.size());
    int row = 0;
    vector<BookBRRecordInfo>::iterator iter = records.begin();
    for (;iter != records.end();iter++)
    {
        BookBRRecordInfo info = *iter;
        BookInfo book = gAllBooks.find(info.bookID)->second;

        QString strTime = gStr2QStr(info.returnTime);
        QDateTime returnTime = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");
        int ssc = returnTime.toTime_t() - currTime.toTime_t();
        info.warnDays = (ssc) / (60 * 60 * 24);	//计算天数差值

        ui->tw_UserJY->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.borrowID)));
        ui->tw_UserJY->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookID)));
        ui->tw_UserJY->setItem(row, 2, new QTableWidgetItem(gStr2QStr(book.bookISBN)));
        ui->tw_UserJY->setItem(row, 3, new QTableWidgetItem(gStr2QStr(book.bookName)));
        ui->tw_UserJY->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.borrowTime)));
        ui->tw_UserJY->setItem(row, 5, new QTableWidgetItem(gStr2QStr(info.returnTime)));
        ui->tw_UserJY->setItem(row, 6, new QTableWidgetItem(QString::number(info.warnDays)));
        row++;
    }
}
void AdminReturnRecord::flushAllData()	//刷新所有的数据
{

}
