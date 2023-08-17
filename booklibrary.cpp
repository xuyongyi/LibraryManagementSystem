#include "booklibrary.h"
#include "ui_booklibrary.h"

BookLibrary::BookLibrary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookLibrary)
{
    ui->setupUi(this);
    setWindowTitle("高校图书管理系统");
    QString iconStr = gCurrPath + "/Img/icon.png";
    QIcon icon(iconStr);
    setWindowIcon(icon);
    init();
    connectslots();
    addClass2Tab();
}

BookLibrary::~BookLibrary()
{
    delete ui;
}

void BookLibrary::init()	//初始化
{
    string schoolLogo = gQStr2Str(gCurrPath) + "/Img/logo.jpg";
    gLoadPixmap(ui->l_SchoolLogo, schoolLogo);
}
void BookLibrary::connectslots()	//连接信号与槽
{
    connect(ui->pb_Exit,SIGNAL(clicked()),this,SLOT(slt_Exit()));
connect(&m_ReaderFunc,SIGNAL(sig_Reset()),this,SLOT(slt_flushTX()));
     connect(&m_AdminFunc,SIGNAL(sig_Reset()),this,SLOT(slt_flushTX()));
}
void BookLibrary::setInitWidget(int userType)	//设置显示界面
{
    m_userType = userType;

    if (userType == 0)	//超级管理员
    {
        ui->l_Title->setText("高校图书管理系统 - 系统管理员端");
        ui->l_Name->setText("Admin");
        m_SuperFunc.setInitWidget();
        ui->stackedWidget->setCurrentWidget(&m_SuperFunc);
    }
    else if (userType == 1)	//普通管理员
    {
        ui->l_Title->setText("高校图书管理系统 - 图书管理员端");
        gLoadPixmap(ui->l_TX, gCurrReader.touxiangName);
        ui->l_Name->setText(gStr2QStr(gCurrReader.readerName));
        m_AdminFunc.setInitWidget();
        ui->stackedWidget->setCurrentWidget(&m_AdminFunc);
    }
    else if (userType == 2)	//普通管理员
    {
        ui->l_Title->setText("高校图书管理系统 - 读者端");
        gLoadPixmap(ui->l_TX, gCurrReader.touxiangName);
        ui->l_Name->setText(gStr2QStr(gCurrReader.readerName));
        m_ReaderFunc.setInitWidget();
        ui->stackedWidget->setCurrentWidget(&m_ReaderFunc);
    }
}

void BookLibrary::slt_Exit()
{
    this->close();
    emit sig_exit();
}

 void BookLibrary::slt_flushTX()
 {
     if (m_userType == 0)	//超级管理员
     {
         ui->l_Title->setText("高校图书管理系统 - 系统管理员端");
         ui->l_Name->setText("Admin");
     }
     else if (m_userType == 1)	//普通管理员
     {
         ui->l_Title->setText("高校图书管理系统 - 图书管理员端");
         gLoadPixmap(ui->l_TX, gCurrReader.touxiangName);
         ui->l_Name->setText(gStr2QStr(gCurrReader.readerName));
     }
     else if (m_userType == 2)	//普通管理员
     {
         ui->l_Title->setText("高校图书管理系统 - 读者端");
         gLoadPixmap(ui->l_TX, gCurrReader.touxiangName);
         ui->l_Name->setText(gStr2QStr(gCurrReader.readerName));
     }
 }

void BookLibrary::addClass2Tab()	//添加类到ta
{
    ui->stackedWidget->addWidget(&m_SuperFunc);
    ui->stackedWidget->addWidget(&m_AdminFunc);
    ui->stackedWidget->addWidget(&m_ReaderFunc);
}

void BookLibrary::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString picName = gCurrPath + "/Img/bg.jpg";
    painter.drawPixmap(rect(), QPixmap(picName), QRect());
}
