#include "superfunc.h"
#include "ui_superfunc.h"

SuperFunc::SuperFunc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperFunc)
{
    ui->setupUi(this);
    init();
    connectslots();
    addClass2Tab();
}

SuperFunc::~SuperFunc()
{
    delete ui;
}

void SuperFunc::init()	//初始化
{
    //ui->tabWidget->setTabPosition(QTabWidget::West);//QTabWidget竖向
    //ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}
void SuperFunc::connectslots()	//连接信号与槽
{
    //connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slt_tabChange(int)));
    connect(&m_SuperSysSetOrder, SIGNAL(sig_OK()), this, SLOT(slt_updateConfData()));
    connect(&m_SuperSysSetJYSC, SIGNAL(sig_OK()), this, SLOT(slt_updateConfData()));
    connect(&m_SuperSysSetZNJ, SIGNAL(sig_OK()), this, SLOT(slt_updateConfData()));
    connect(&m_SuperPerson, SIGNAL(sig_OK()), this, SLOT(slt_updateConfData()));
    connect(&m_SuperSysSetWB, SIGNAL(sig_OK()), this, SLOT(slt_updateConfData()));

    connect(ui->pb_Admin, SIGNAL(clicked()), this, SLOT(slt_Admin()));
    connect(ui->pb_Order, SIGNAL(clicked()), this, SLOT(slt_Order()));
    connect(ui->pb_JYSC, SIGNAL(clicked()), this, SLOT(slt_JYSC()));
    connect(ui->pb_ZNJ, SIGNAL(clicked()), this, SLOT(slt_ZNJ()));
    connect(ui->pb_Person, SIGNAL(clicked()), this, SLOT(slt_Person()));
    connect(ui->pb_WB, SIGNAL(clicked()), this, SLOT(slt_WB()));
}
void SuperFunc::setInitWidget()	//设置显示界面
{
    //slt_tabChange(0);
    m_AdminManagerWidget.setInitWidget();
    m_SuperSysSetOrder.setInitWidget("预约时长设置", "请输入预约时长(天):", gConfInfo.order, true);
    m_SuperSysSetJYSC.setInitWidget("借阅时长设置", "请输入借阅/续约时长(天):", gConfInfo.jysc, true);
    m_SuperSysSetZNJ.setInitWidget("滞纳金设置", "请输入滞纳金(天/本):", gConfInfo.znj, true);
    m_SuperPerson.setInitWidget("请输入新密码:", gConfInfo.superPwd);
    m_SuperSysSetWB.setInitWidget("维保设置", "请输入维保时长(小时):", gConfInfo.wbTime, false);
}


void SuperFunc::slt_Admin()	//借阅时长
{
    m_AdminManagerWidget.setInitWidget();
}

void SuperFunc::slt_Order()
{
    m_SuperSysSetOrder.show();
}

void SuperFunc::slt_JYSC()	//借阅时长
{
    m_SuperSysSetJYSC.show();
}
void SuperFunc::slt_ZNJ()
{
    m_SuperSysSetZNJ.show();
}
void SuperFunc::slt_Person()
{
    m_SuperPerson.show();
}
void SuperFunc::slt_WB()
{
    m_SuperSysSetWB.show();
}

void SuperFunc::addClass2Tab()//添加类到tab
{
    QVBoxLayout *lay1 = new QVBoxLayout();
    lay1->addWidget(&m_AdminManagerWidget);
    ui->w_Admin->setLayout(lay1);

    /*QVBoxLayout *lay2 = new QVBoxLayout();
    lay2->addWidget(&m_SuperSysSetJYSC);
    ui->tab_2->setLayout(lay2);

    QVBoxLayout *lay3 = new QVBoxLayout();
    lay3->addWidget(&m_SuperSysSetZNJ);
    ui->tab_3->setLayout(lay3);

    QVBoxLayout *lay4 = new QVBoxLayout();
    lay4->addWidget(&m_SuperPerson);
    ui->tab_4->setLayout(lay4);

    QVBoxLayout *lay5 = new QVBoxLayout();
    lay5->addWidget(&m_SuperSysSetWB);
    ui->tab_5->setLayout(lay5);*/
}

/*void SuperFunc::slt_tabChange(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    switch (index)
    {
    case 0:
        m_AdminManagerWidget.setInitWidget();
        break;
    case 1:
        m_SuperSysSetJYSC.setInitWidget("请输入借阅/续约时长(天):", gConfInfo.jysc,true);
        break;
    case 2:
        m_SuperSysSetZNJ.setInitWidget("请输入滞纳金(天/本):", gConfInfo.znj, true);
        break;
    case 3:
        m_SuperPerson.setInitWidget("请输入新密码:", gConfInfo.superPwd);
        break;
    case 4:
        m_SuperSysSetWB.setInitWidget("请输入维保时长(小时):", gConfInfo.wbTime,false);
        break;
    default:
        break;
    }
}*/

void SuperFunc::slt_updateConfData()	//更新配置文件数据
{
    gConfInfo.superPwd = m_SuperPerson.m_resetValue;
    gConfInfo.order = m_SuperSysSetOrder.m_resetValue;
    gConfInfo.jysc = m_SuperSysSetJYSC.m_resetValue;
    gConfInfo.znj = m_SuperSysSetZNJ.m_resetValue;
    gConfInfo.wbTime = m_SuperSysSetWB.m_resetValue;
    gRWFile.writeConfInfo(gConfInfo);
    return;
}
