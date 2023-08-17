#include "readerwarn.h"
#include "ui_readerwarn.h"

ReaderWarn::ReaderWarn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderWarn)
{
    ui->setupUi(this);
    setWindowTitle("到期/预期提醒");
    QString iconStr = gCurrPath + "/Img/icon.png";
    QIcon icon(iconStr);
    setWindowIcon(icon);
    setAttribute(Qt::WA_ShowModal);
    init();
    connectslots();
}

ReaderWarn::~ReaderWarn()
{
    delete ui;
}

void ReaderWarn::init()	//初始化
{
    setUserJYHeader();
    gSetTableWidgetMode(ui->tw_UserJY);
}
void ReaderWarn::connectslots()	//连接信号与槽
{

}
void ReaderWarn::setInitWidget()	//设置显示界面
{
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    vector<BookBRRecordInfo> records;
    gMySqlFunc.searchSingleBookBRRecordInfoTableStr(gError, records,"readerID",gCurrReader.readerID);
    filterRecords(records);
    flushUserJYList(m_Records);
}

void ReaderWarn::setUserJYHeader()
{
    QStringList headers;
    headers << "借阅号" << ("书籍条码") << ("书籍名称") << "借阅人账号" << "借阅人姓名" << "剩余天数" << "借阅时间" << "到期时间";
    ui->tw_UserJY->setColumnCount(headers.size());
    ui->tw_UserJY->setHorizontalHeaderLabels(headers);
}
void ReaderWarn::flushUserJYList(vector<BookBRRecordInfo> records)
{
    ui->tw_UserJY->setRowCount(records.size());
    int row = 0;
    vector<BookBRRecordInfo>::iterator iter = records.begin();
    for (;iter != records.end();iter++)
    {
        BookBRRecordInfo info = *iter;
        ReaderInfo reader = gAllReaders.find(info.readerID)->second;
        BookInfo book = gAllBooks.find(info.bookID)->second;
        ui->tw_UserJY->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.borrowID)));
        ui->tw_UserJY->setItem(row, 1, new QTableWidgetItem(gStr2QStr(book.bookID)));
        ui->tw_UserJY->setItem(row, 2, new QTableWidgetItem(gStr2QStr(book.bookName)));
        ui->tw_UserJY->setItem(row, 3, new QTableWidgetItem(gStr2QStr(reader.readerID)));
        ui->tw_UserJY->setItem(row, 4, new QTableWidgetItem(gStr2QStr(reader.readerName)));
        ui->tw_UserJY->setItem(row, 5, new QTableWidgetItem(QString::number(info.warnDays)));
        ui->tw_UserJY->setItem(row, 6, new QTableWidgetItem(gStr2QStr(info.borrowTime)));
        ui->tw_UserJY->setItem(row, 7, new QTableWidgetItem(gStr2QStr(info.returnTime)));
        row++;
    }
}

void ReaderWarn::filterRecords(vector<BookBRRecordInfo> records)	//过滤数据
{
    m_Records.clear();
    QDateTime currTime = QDateTime::currentDateTime();
    for (int m = 0;m < records.size();m++)
    {
        if (records[m].returnStat == 0) //未归还
        {
            QString strTime = gStr2QStr(records[m].returnTime);
            QDateTime returnTime = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");
            int ssc = returnTime.toTime_t() - currTime.toTime_t();
            records[m].warnDays = (ssc) / (60 * 60 * 24);	//计算天数差值
            if (records[m].warnDays < 3)	//时间低于3天或已逾期
            {
                m_Records.push_back(records[m]);
            }
        }
    }
    return;
}

void ReaderWarn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString picName = gCurrPath + "/Img/bg.jpg";
    painter.drawPixmap(rect(), QPixmap(picName), QRect());
}


void ReaderWarn::setInitWidget1()	//设置显示界面
{
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    vector<BookBRRecordInfo> records;
    gMySqlFunc.searchSingleBookBRRecordInfoTableStr(gError, records,"readerID",gCurrReader.readerID);
    filterRecords1(records);
    //flushUserJYList(m_Records);
}
void ReaderWarn::filterRecords1(vector<BookBRRecordInfo> records)	//过滤数据
{
    m_Records.clear();
    QDateTime currTime = QDateTime::currentDateTime();
    for (int m = 0;m < records.size();m++)
    {
        if (records[m].returnStat == 0) //未归还
        {
            QString strTime = gStr2QStr(records[m].returnTime);
            QDateTime returnTime = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");
            int ssc = returnTime.toTime_t() - currTime.toTime_t();
            records[m].warnDays = (ssc) / (60 * 60 * 24);	//计算天数差值
            if (records[m].warnDays < 0)	//时间低于3天或已逾期
            {
                m_Records.push_back(records[m]);
            }
        }
    }
    return;
}
