#include "adminfunc.h"
#include "ui_adminfunc.h"

AdminFunc::AdminFunc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminFunc)
{
    ui->setupUi(this);
    init();
    connectslots();
    addClass2Tab();
}

AdminFunc::~AdminFunc()
{
    delete ui;
}

void AdminFunc::init()	//初始化
{
    ui->tabWidget->setTabPosition(QTabWidget::West);//QTabWidget竖向
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}
void AdminFunc::connectslots()	//连接信号与槽
{
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slt_tabChange(int)));
    connect(&m_AdminPerson, SIGNAL(sig_Reset()), this, SLOT(slt_Reset()));
}

void AdminFunc::slt_Reset()
{
    emit sig_Reset();
}

void AdminFunc::setInitWidget()	//设置显示界面
{
    slt_tabChange(0);
}
void AdminFunc::addClass2Tab()	//添加类到tab
{
    QVBoxLayout *lay1 = new QVBoxLayout();
    lay1->addWidget(&m_AdminBook);
    ui->tab->setLayout(lay1);

    QVBoxLayout *lay2 = new QVBoxLayout();
    lay2->addWidget(&m_AdminUser);
    ui->tab_2->setLayout(lay2);

    QVBoxLayout *lay3 = new QVBoxLayout();
    lay3->addWidget(&m_AdminBRRecord);
    ui->tab_3->setLayout(lay3);

    QVBoxLayout *lay4 = new QVBoxLayout();
    lay4->addWidget(&m_AdminReturnRecord);
    ui->tab_4->setLayout(lay4);

    QVBoxLayout *lay5 = new QVBoxLayout();
    lay5->addWidget(&m_AdminPerson);
    ui->tab_5->setLayout(lay5);
}

void AdminFunc::slt_tabChange(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    switch (index)
    {
    case 0:
        m_AdminBook.setInitWidget();
        break;
    case 1:
        m_AdminUser.setInitWidget();
        break;
    case 2:
        m_AdminBRRecord.setInitWidget();
        break;
    case 3:
        m_AdminReturnRecord.setInitWidget();
        break;
    case 4:
        m_AdminPerson.setInitWidget();
        break;
    default:
        break;
    }
}
