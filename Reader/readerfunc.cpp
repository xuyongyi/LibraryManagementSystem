#include "readerfunc.h"
#include "ui_readerfunc.h"

ReaderFunc::ReaderFunc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderFunc)
{
    ui->setupUi(this);
    init();
    connectslots();
    addClass2Tab();
}

ReaderFunc::~ReaderFunc()
{
    delete ui;
}

void ReaderFunc::init()	//初始化
{
    ui->tabWidget->setTabPosition(QTabWidget::West);//QTabWidget竖向
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}
void ReaderFunc::connectslots()	//连接信号与槽
{
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slt_tabChange(int)));
    connect(&m_ReaderPerson, SIGNAL(sig_Reset()), this, SLOT(slt_Reset()));
}
void ReaderFunc::setInitWidget()	//设置显示界面
{
    m_ReaderWarn.setInitWidget();
    if (m_ReaderWarn.m_Records.size() > 0)
    {
        m_ReaderWarn.show();
    }
    slt_tabChange(0);
}

void ReaderFunc::slt_Reset()
{
    emit sig_Reset();
}

void ReaderFunc::addClass2Tab()	//添加类到tab
{
    QVBoxLayout *lay1 = new QVBoxLayout();
    lay1->addWidget(&m_ReaderBook);
    ui->tab->setLayout(lay1);

    QVBoxLayout *lay2 = new QVBoxLayout();
    lay2->addWidget(&m_ReaderJY);
    ui->tab_2->setLayout(lay2);

    QVBoxLayout *lay3 = new QVBoxLayout();
    lay3->addWidget(&m_ReaderOrder);
    ui->tab_3->setLayout(lay3);

    QVBoxLayout *lay4 = new QVBoxLayout();
    lay4->addWidget(&m_ReaderPerson);
    ui->tab_4->setLayout(lay4);

    QVBoxLayout *lay5 = new QVBoxLayout();
    lay5->addWidget(&m_ReaderTop);
    ui->tab_5->setLayout(lay5);
}

void ReaderFunc::slt_tabChange(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    switch (index)
    {
    case 0:
        m_ReaderBook.setInitWidget();
        break;
    case 1:
        m_ReaderJY.setInitWidget();
        break;
    case 2:
        m_ReaderOrder.setInitWidget();
        break;
    case 3:
        m_ReaderTop.setInitWidget();
        break;
    case 4:
        m_ReaderPerson.setInitWidget();
        break;
    default:
        break;
    }
}
