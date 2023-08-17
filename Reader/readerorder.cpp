#include "readerorder.h"
#include "ui_readerorder.h"

ReaderOrder::ReaderOrder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderOrder)
{
    ui->setupUi(this);
    init();
    connectslots();
}

ReaderOrder::~ReaderOrder()
{
    delete ui;
}

void ReaderOrder::init()	//初始化
{
    ui->le_UserJYID->setEnabled(false);
    m_SelectRecord.id = -1;
    setUserJYHeader();
    gSetTableWidgetMode(ui->tw_UserJY);
}
void ReaderOrder::connectslots()	//连接信号与槽
{
    connect(ui->pb_Cancel, SIGNAL(clicked()), this, SLOT(slt_Cancel()));
    connect(ui->pb_Delete, SIGNAL(clicked()), this, SLOT(slt_Delete()));
    connect(ui->tw_UserJY, SIGNAL(itemClicked(QTableWidgetItem *)), \
        this, SLOT(slt_UserJYSClicked(QTableWidgetItem *)));
}
void ReaderOrder::setInitWidget()	//设置显示界面
{
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);
    gMySqlFunc.searchSingleOrderInfoTableStr(gError, m_Records, "readerID", gCurrReader.readerID); //查询当前读者的所有数据
    flushUserJYList(m_Records);
}

void ReaderOrder::slt_Delete()	//删除预约
{
    if (m_SelectRecord.id == -1)
    {
        gWarnning("请先选择预约记录!");
        return;
    }
    string currTime = gQStr2Str(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if (m_SelectRecord.orderFinishTime > currTime)
    {
        gWarnning("在预约时间内,请先取消预约!");
        return;
    }
    if(gWarnningDel("确认删除?") == 0)
    {
        return;
    }
    gMySqlFunc.deleteOrderInfoTable(gError, m_SelectRecord);
    gMySqlFunc.searchSingleOrderInfoTableStr(gError, m_Records, "readerID", gCurrReader.readerID); //查询当前读者的所有数据
    flushUserJYList(m_Records);
    m_SelectRecord.id = -1;
    return;
}
void ReaderOrder::slt_Cancel()	//取消预约
{
    if (m_SelectRecord.id == -1)
    {
        gWarnning("请先选择预约记录!");
        return;
    }
    m_SelectRecord.waitStat = 1;
    m_SelectRecord.orderFinishTime = "";
    gMySqlFunc.updateOrderInfoTable(gError, m_SelectRecord);
    gMySqlFunc.searchSingleOrderInfoTableStr(gError, m_Records, "readerID", gCurrReader.readerID); //查询当前读者的所有数据
    flushUserJYList(m_Records);
    gWarnning("取消预约成功!");
    m_SelectRecord.id = -1;
}

void ReaderOrder::slt_UserJYSClicked(QTableWidgetItem *item)	//列表元素被单击槽函数
{
    int count = item->row();
    m_SelectRecord = m_Records[count];
    ui->le_UserJYID->setText(gStr2QStr(m_SelectRecord.orderID));
}

void ReaderOrder::setUserJYHeader()
{
    QStringList headers;
    headers << "预定号" << ("书籍条码") << ("书籍名称") << "预定时间" << "预定结束时间";
    ui->tw_UserJY->setColumnCount(headers.size());
    //ui->tw_UserJY->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_UserJY->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_UserJY->setHorizontalHeaderLabels(headers);
}
void ReaderOrder::flushUserJYList(vector<OrderInfo> records)
{
    ui->tw_UserJY->setRowCount(records.size());
    int row = 0;
    vector<OrderInfo>::iterator iter = records.begin();
    for (;iter != records.end();iter++)
    {
        OrderInfo info = *iter;
        BookInfo book = gAllBooks.find(info.bookID)->second;
        ui->tw_UserJY->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.orderID)));
        ui->tw_UserJY->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookID)));
        ui->tw_UserJY->setItem(row, 2, new QTableWidgetItem(gStr2QStr(book.bookName)));
        ui->tw_UserJY->setItem(row, 3, new QTableWidgetItem(gStr2QStr(info.orderTime)));
        ui->tw_UserJY->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.orderFinishTime)));
        row++;
    }
}
