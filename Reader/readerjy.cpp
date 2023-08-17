#include "readerjy.h"
#include "ui_readerjy.h"


ReaderJY::ReaderJY(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderJY)
{
    ui->setupUi(this);
    init();
    connectslots();
}

ReaderJY::~ReaderJY()
{
    delete ui;
}

void ReaderJY::init()	//初始化
{
    ui->le_UserJYID->setEnabled(false);
    m_SelectRecord.id = -1;
    ui->rb_NoReturn->setChecked(true);

    setUserJYHeader();
    gSetTableWidgetMode(ui->tw_UserJY);
}
void ReaderJY::connectslots()	//连接信号与槽
{
    connect(ui->pb_Look, SIGNAL(clicked()), this, SLOT(slt_Look()));
    connect(ui->pb_XJ, SIGNAL(clicked()), this, SLOT(slt_XJ()));
    connect(ui->pb_GH, SIGNAL(clicked()), this, SLOT(slt_GH()));
    connect(ui->tw_UserJY, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_UserJYSClicked(QTableWidgetItem *)));
}
void ReaderJY::setInitWidget()	//设置显示界面
{
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    vector<BookBRRecordInfo> datas;
    gMySqlFunc.searchSingleBookBRRecordInfoTableStr(gError, datas, "readerID", gCurrReader.readerID); //查询当前读者的所有数据
    filterDatas(datas);
    flushUserJYList(m_Records);
}

void ReaderJY::slt_Look()	//浏览
{
    vector<BookBRRecordInfo> datas;
    gMySqlFunc.searchSingleBookBRRecordInfoTableStr(gError, datas, "readerID", gCurrReader.readerID); //查询当前读者的所有数据
    filterDatas(datas);
    flushUserJYList(m_Records);
}

void ReaderJY::slt_XJ()	//续借
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
    m_SelectRecord.id = -1;
    ui->le_UserJYID->setText("");
    slt_Look();
    return;
}
void ReaderJY::slt_GH()	//归还
{
    if (m_SelectRecord.id == -1)
    {
        gWarnning("请先选择借阅记录!");
        return;
    }
    if (m_SelectRecord.returnStat == 1)
    {
        gWarnning("图书已归还!");
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

    slt_Look();
    m_SelectRecord.id = -1;
    ui->le_UserJYID->setText("");
    return;
}

void ReaderJY::slt_UserJYSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
{
    int count = item->row();
    m_SelectRecord = m_Records[count];
    ui->le_UserJYID->setText(gStr2QStr(m_SelectRecord.borrowID));
}

void ReaderJY::setUserJYHeader()
{
    QStringList headers;
    headers << "借阅号" << ("书籍条码") << ("书籍名称") << "借阅时间" << "到期时间"<<"剩余天数";
    ui->tw_UserJY->setColumnCount(headers.size());
    ui->tw_UserJY->setHorizontalHeaderLabels(headers);
}
void ReaderJY::flushUserJYList(vector<BookBRRecordInfo> records)
{
    ui->tw_UserJY->setRowCount(records.size());
    int row = 0;
    vector<BookBRRecordInfo>::iterator iter = records.begin();
    for (;iter != records.end();iter++)
    {
        BookBRRecordInfo info = *iter;
        BookInfo book = gAllBooks.find(info.bookID)->second;
        ui->tw_UserJY->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.borrowID)));
        ui->tw_UserJY->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookID)));
        ui->tw_UserJY->setItem(row, 2, new QTableWidgetItem(gStr2QStr(book.bookName)));
        ui->tw_UserJY->setItem(row, 3, new QTableWidgetItem(gStr2QStr(info.borrowTime)));
        ui->tw_UserJY->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.returnTime)));
        ui->tw_UserJY->setItem(row, 5, new QTableWidgetItem(QString::number(info.warnDays)));
        row++;
    }
}

void ReaderJY::filterDatas(vector<BookBRRecordInfo> datas)
{
    m_Records.clear();
    QDateTime currTime = QDateTime::currentDateTime();
    if (ui->rb_NoReturn->isChecked())
    {
        for (int m = 0;m < datas.size();m++)
        {
            if (datas[m].returnStat == 0)
            {
                QString strTime = gStr2QStr(datas[m].returnTime);
                QDateTime returnTime = QDateTime::fromString(strTime, "yyyy-MM-dd hh:mm:ss");
                int ssc = returnTime.toTime_t() - currTime.toTime_t();
                datas[m].warnDays = (ssc) / (60 * 60 * 24);	//计算天数差值
                m_Records.push_back(datas[m]);
            }
        }
    }
    else if (ui->rb_Return->isChecked())
    {
        for (int m = 0;m < datas.size();m++)
        {
            if (datas[m].returnStat == 1)
            {
                m_Records.push_back(datas[m]);
            }
        }
    }
    else
    {
        m_Records = datas;
    }
    return;
}
