#include "superperson.h"
#include "ui_superperson.h"

SuperPerson::SuperPerson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperPerson)
{
    ui->setupUi(this);
    setWindowTitle("个人中心");
    QString iconStr = gCurrPath + "/Img/icon.png";
    QIcon icon(iconStr);
    setWindowIcon(icon);
    init();
    connectslots();
}

SuperPerson::~SuperPerson()
{
    delete ui;
}

void SuperPerson::init()	//初始化
{
    ui->le_Value->setEchoMode(QLineEdit::Password); //设置密码显示
}
void SuperPerson::connectslots()	//连接信号与槽
{
    connect(ui->pb_Ok, SIGNAL(clicked()), this, SLOT(slt_OK()));
}
void SuperPerson::setInitWidget(QString label, string value)	//设置显示界面
{
    m_resetValue = value;
    ui->label_1->setText(label);
    QString valueStr = gStr2QStr(value);
    ui->le_Value->setText(valueStr);

}

void SuperPerson::slt_OK()
{
    m_resetValue = gQStr2Str(ui->le_Value->text().trimmed());
    string tempPwd = gQStr2Str(ui->le_Value_2->text().trimmed());
    if (m_resetValue != tempPwd)
    {
        gWarnning("两次输入密码不一致!");
        return;
    }
    if (m_resetValue == "")
    {
        gWarnning("请检查输入值!");
        return;
    }
    ui->le_Value->setText("");
    ui->le_Value_2->setText("");
    emit sig_OK();
}

void SuperPerson::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString picName = gCurrPath + "/Img/bg.jpg";
    painter.drawPixmap(rect(), QPixmap(picName), QRect());
}
