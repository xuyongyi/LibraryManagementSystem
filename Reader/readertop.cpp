#include "readertop.h"
#include "ui_readertop.h"

bool cmp_max(SortData x, SortData y) {
    return x.size > y.size;
}

bool cmp_min(SortData x, SortData y) {
    return x.size < y.size;
}

ReaderTop::ReaderTop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderTop)
{
    ui->setupUi(this);
    init();
    connectslots();
}

ReaderTop::~ReaderTop()
{
    delete ui;
}

void ReaderTop::init()	//初始化
{
    ui->rb_BookDown->setChecked(true);
    ui->rb_ReaderDown->setChecked(true);
}
void ReaderTop::connectslots()//连接信号与槽
{
    connect(ui->pb_Book,SIGNAL(clicked()),this,SLOT(slt_Book()));
    connect(ui->pb_Reader, SIGNAL(clicked()), this, SLOT(slt_Reader()));
}
void ReaderTop::setInitWidget()	//设置显示界面
{
    setBookInfoHeader();
    setReaderInfoHeader();
    gSetTableWidgetMode(ui->tw_Book);
    gSetTableWidgetMode(ui->tw_Reader);
}

void ReaderTop::slt_Book()
{
    sortBookByBorrowSize();
    flushBookInfoList();
}
void ReaderTop::slt_Reader()
{
    sortReaderByBorrowSize();
    flushReaderInfoList();
}

void ReaderTop::setBookInfoHeader()	//设置图书信息信息列表头部显示信息
{
    QStringList headers;
    headers << ("图书条码") << ("图书名称") << ("图书ISBN号")<<"借阅数量" << ("图书作者") << ("出版社")  << ("图书语言") ;
    ui->tw_Book->setColumnCount(headers.size());
    ui->tw_Book->setHorizontalHeaderLabels(headers);
}
void ReaderTop::flushBookInfoList()	//刷新图书信息信息列表
{
    ui->tw_Book->setRowCount(m_SortedBookVec.size());
    int row = 0;
    vector<SortData>::iterator iter = m_SortedBookVec.begin();
    for (;iter != m_SortedBookVec.end();iter++)
    {
        SortData data = *iter;
        if (gAllBooks.count(data.id))
        {
            BookInfo info = gAllBooks.find(data.id)->second;
            ui->tw_Book->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.bookID)));
            ui->tw_Book->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.bookName)));
            ui->tw_Book->setItem(row, 2, new QTableWidgetItem(gStr2QStr(info.bookISBN)));
            ui->tw_Book->setItem(row, 3, new QTableWidgetItem(QString::number(data.size)));
            ui->tw_Book->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.bookAuth)));
            ui->tw_Book->setItem(row, 5, new QTableWidgetItem(gStr2QStr(info.bookPublish)));
            ui->tw_Book->setItem(row, 6, new QTableWidgetItem(gStr2QStr(info.bookLanguage)));
            row++;
        }
    }
}
void ReaderTop::setReaderInfoHeader()	//设置读者信息信息列表头部显示信息
{
    QStringList headers;
    headers << ("读者编号") << ("读者姓名")  << "借阅数量";
    ui->tw_Reader->setColumnCount(headers.size());
    ui->tw_Reader->setHorizontalHeaderLabels(headers);
}
void ReaderTop::flushReaderInfoList()	//刷新读者信息信息列表
{
    ui->tw_Reader->setRowCount(m_SortedReaderVec.size());
    int row = 0;
    vector<SortData>::iterator iter = m_SortedReaderVec.begin();
    for (;iter != m_SortedReaderVec.end();iter++)
    {
        SortData data = *iter;
        if (gAllReaders.count(data.id))
        {
            ReaderInfo info = gAllReaders.find(data.id)->second;
            QString name = gStr2QStr(info.readerName);
            QString lastName;
            for (int size = 1;size < name.size() ;size ++)
            {
                lastName += "*";
            }
            name = name.left(1) + lastName;
            ui->tw_Reader->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.readerID)));
            ui->tw_Reader->setItem(row, 1, new QTableWidgetItem(name));
            ui->tw_Reader->setItem(row, 2, new QTableWidgetItem(QString::number(data.size)));
            row++;
        }
    }
}

void ReaderTop::sortBookByBorrowSize()	//排序(书籍)
{
    //获取所有的记录
    map<string, int> sortInfo;
    vector<BookBRRecordInfo> datas;
    map<string, BookInfo> allBooks;
    gMySqlFunc.searchBookInfoTable(gError, allBooks);
    map<string, BookInfo>::iterator iter = allBooks.begin();
    for (;iter != allBooks.end();iter++)
    {
        sortInfo[iter->first] = 0;	//获取所有书籍信息
    }

    gMySqlFunc.searchBookBRRecordInfoTable(gError, datas);	//获取所有的记录
    for (int m = 0;m < datas.size();m++)
    {
        sortInfo[datas[m].bookID]++; //获取信息
    }
    m_SortedBookVec.clear();
    map<string, int>::iterator iterSort = sortInfo.begin();
    for (;iterSort != sortInfo.end();iterSort++)
    {
        SortData t;
        t.id = iterSort->first;
        t.size = iterSort->second;
        m_SortedBookVec.push_back(t);
    }
    if (ui->rb_BookUp->isChecked())
    {
        sort(m_SortedBookVec.begin(), m_SortedBookVec.end(), cmp_min);	//按照借阅量排序
    }
    else
    {
        sort(m_SortedBookVec.begin(), m_SortedBookVec.end(), cmp_max);	//按照借阅量排序
    }
}
void ReaderTop::sortReaderByBorrowSize()	//排序(读者)
{
    //获取所有的记录
    map<string, int> sortInfo;
    vector<BookBRRecordInfo> datas;
    map<string, ReaderInfo> allReaders;
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    map<string, ReaderInfo>::iterator iter = allReaders.begin();
    for (;iter != allReaders.end();iter++)
    {
        sortInfo[iter->first] = 0;	//获取所有书籍信息
    }

    gMySqlFunc.searchBookBRRecordInfoTable(gError, datas);	//获取所有的记录
    for (int m = 0;m < datas.size();m++)
    {
        sortInfo[datas[m].readerID]++; //获取信息
    }
    m_SortedReaderVec.clear();
    map<string, int>::iterator iterSort = sortInfo.begin();
    for (;iterSort != sortInfo.end();iterSort++)
    {
        SortData t;
        t.id = iterSort->first;
        t.size = iterSort->second;
        m_SortedReaderVec.push_back(t);
    }
    if (ui->rb_ReaderUp->isChecked())
    {
        sort(m_SortedReaderVec.begin(), m_SortedReaderVec.end(), cmp_min);	//按照借阅量排序
    }
    else
    {
        sort(m_SortedReaderVec.begin(), m_SortedReaderVec.end(), cmp_max);	//按照借阅量排序
    }
}

