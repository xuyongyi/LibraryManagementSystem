#include "adminmoney.h"
#include "ui_adminmoney.h"

AdminMoney::AdminMoney(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMoney)
{
    ui->setupUi(this);
    setWindowTitle("罚款提醒");
    QString iconStr = gCurrPath + "/Img/icon.png";
    QIcon icon(iconStr);
    setWindowIcon(icon);
    init();
    connectslots();
}

AdminMoney::~AdminMoney()
{
    delete ui;
}

void AdminMoney::init()	//初始化
{
    ui->le_BID->setEnabled(false);
    setUserJYHeader();
    gSetTableWidgetMode(ui->tw_UserJY);
}
void AdminMoney::connectslots()	//连接信号与槽
{
    connect(ui->pb_Money, SIGNAL(clicked()), this, SLOT(slt_Money()));

    connect(ui->tw_UserJY, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_UserSClicked(QTableWidgetItem *)));
}
void AdminMoney::setInitWidget()	//设置显示界面
{
    ui->le_BID->setText("");
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    vector<BookBRRecordInfo> records;
    gMySqlFunc.searchBookBRRecordInfoTable(gError, records);
    filterRecords(records);
    flushUserJYList(m_Records);
}

void AdminMoney::slt_Money()
{
    m_SelectUserJL.returnTime = gQStr2Str(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    gMySqlFunc.updateBookBRRecordInfoTable(gError, m_SelectUserJL);	//更新理论归还时间
    setInitWidget();
}
void AdminMoney::slt_UserSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
{
    int count = item->row();
    m_SelectUserJL = m_Records[count];
    ui->le_BID->setText(gStr2QStr(m_SelectUserJL.borrowID));
}

void AdminMoney::filterRecords(vector<BookBRRecordInfo> records)	//过滤数据
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
            if (records[m].warnDays < 0)	//已逾期,需要计算滞纳金
            {
                m_Records.push_back(records[m]);
            }
        }
    }
    return;
}

void AdminMoney::setUserJYHeader()
{
    QStringList headers;
    headers << "借阅号" << ("书籍条码") << ("书籍名称") << "借阅人账号" << "借阅人姓名" << "剩余天数" <<"滞纳金"<< "借阅时间" << "到期时间";
    ui->tw_UserJY->setColumnCount(headers.size());
    //ui->tw_UserJY->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_UserJY->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_UserJY->setHorizontalHeaderLabels(headers);
}

void AdminMoney::flushUserJYList(vector<BookBRRecordInfo> records)
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
        ui->tw_UserJY->setItem(row, 6, new QTableWidgetItem(QString::number(abs(info.warnDays * 0.2))));
        ui->tw_UserJY->setItem(row, 7, new QTableWidgetItem(gStr2QStr(info.borrowTime)));
        ui->tw_UserJY->setItem(row, 8, new QTableWidgetItem(gStr2QStr(info.returnTime)));
        row++;
    }
}

void AdminMoney::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString picName = gCurrPath + "/Img/bg.jpg";
    painter.drawPixmap(rect(), QPixmap(picName), QRect());
}
