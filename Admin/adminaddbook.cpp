#include "adminaddbook.h"
#include "ui_adminaddbook.h"

AdminAddBook::AdminAddBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminAddBook)
{
    ui->setupUi(this);
    setWindowTitle("添加书籍");
    QString iconStr = gCurrPath + "/Img/icon.png";
    QIcon icon(iconStr);
    setWindowIcon(icon);
    init();
    connectslots();
}

AdminAddBook::~AdminAddBook()
{
    delete ui;
}

void AdminAddBook::init()	//初始化
{

}
void AdminAddBook::connectslots()	//连接信号与槽
{
    connect(ui->pb_AddBookInfo, SIGNAL(clicked()), this, SLOT(slt_AddBookInfo()));
    connect(ui->pb_DelBookInfo, SIGNAL(clicked()), this, SLOT(slt_Back()));
}
void AdminAddBook::setInitWidget()	//初始化界面显示信息
{
    gAddList2CB(ui->comb_bookLanguage, gBookLanguage);
    gAddList2CB(ui->comb_bookType, gBookClass);
    ui->le_bookPushDate->setDate(QDate::currentDate());
    clearBookInfoFormInfo();
    gMySqlFunc.searchBookInfoTable(gError, gAllBooks);//结合数据库,从数据库中查找信息
}

void AdminAddBook::slt_AddBookInfo()	//添加槽函数
{
    BookInfo info = getBookInfoFormInfo();
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
    emit sig_Add();
    return;
}
void AdminAddBook::slt_Back()	//返回
{
    this->close();
}

BookInfo AdminAddBook::getBookInfoFormInfo()	//获取图书信息信息
{
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
void AdminAddBook::clearBookInfoFormInfo()	//清空图书信息信息
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
    ui->le_bookPrice->setText("");
    ui->le_totalSize->setText("");
}
int AdminAddBook::isExistBookInfoKey(string bookID)	//查看关键字是否重复
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

void AdminAddBook::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString picName = gCurrPath + "/Img/bg.jpg";
    painter.drawPixmap(rect(), QPixmap(picName), QRect());
}
