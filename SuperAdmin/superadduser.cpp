#include "superadduser.h"
#include "ui_superadduser.h"

SuperAddUser::SuperAddUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperAddUser)
{
    ui->setupUi(this);
    setWindowTitle("添加图书管理员");
    QString iconStr = gCurrPath + "/Img/icon.png";
    QIcon icon(iconStr);
    setWindowIcon(icon);
    init();
    connectslots();
}

SuperAddUser::~SuperAddUser()
{
    delete ui;
}

void SuperAddUser::init()	//初始化
{
    ui->rb_man->setChecked(true);
    m_gender[0] = ui->rb_man;
    m_gender[1] = ui->rb_women;
    ui->label_5->hide();
    ui->le_readerClassID->hide();
}
void SuperAddUser::connectslots()	//连接信号与槽
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slt_ResetTX()));
    connect(ui->pb_AddReaderInfo, SIGNAL(clicked()), this, SLOT(slt_AddReaderInfo()));
    connect(ui->pb_Back, SIGNAL(clicked()), this, SLOT(slt_Back()));
}
void SuperAddUser::setInitWidget()	//初始化界面显示信息
{

    m_newTX = "";
    clearReaderInfoFormInfo();
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);//结合数据库,从数据库中查找信息

    string moren = gQStr2Str(gCurrPath) + "/Img/0.jpg";
    gLoadPixmap(ui->l_Touxiang, moren);
}

void SuperAddUser::slt_Back()	//添加槽函数
{
    this->close();
}
void SuperAddUser::slt_AddReaderInfo()	//添加槽函数
{
    ReaderInfo info = getReaderInfoFormInfo();
    if (info.readerID == "" || info.readerPwd == "" || info.readerName == "" || info.readerPhone == "" || info.readerCollege == "")
    {
        gWarnning("存在未填写项!");
        return;
    }
    if (isExistReaderInfoKey(info.readerID))
    {
        gWarnning("readerID已存在,添加失败!");
        return;
    }
    gMySqlFunc.insertReaderInfoTable(gError, info);
    gMySqlFunc.searchReaderInfoTable(gError, gAllReaders);//结合数据库,从数据库中查找信息
    clearReaderInfoFormInfo();
    emit sig_Add();
    return;
}
void SuperAddUser::slt_ResetTX()	//更改头像
{
    QString filename = QFileDialog::getOpenFileName(NULL, "导入文件", "./Img", "*.*");
    qDebug() << filename;
    if (filename == "")
    {
        return;
    }
    m_newTX = gQStr2Str(filename);
    gLoadPixmap(ui->l_Touxiang, m_newTX);
    return;
}

ReaderInfo SuperAddUser::getReaderInfoFormInfo()	//获取读者信息信息
{
    ReaderInfo info;
    string readerID = gQStr2Str(ui->le_readerID->text());
    string readerPwd = gQStr2Str(ui->le_readerPwd->text());
    string readerName = gQStr2Str(ui->le_readerName->text());
    string readerPhone = gQStr2Str(ui->le_readerPhone->text());
    string readerClassID = gQStr2Str(ui->le_readerClassID->text());
    string readerCollege = gQStr2Str(ui->le_readerCollege->text());
    int borrowBookSize = 0;
    int readBookSize = 0;
    int existNoReturn = 0;
    QString touxiangName = gCurrPath + "/Img/0.jpg";
    info.readerID = readerID;
    info.readerPwd = readerPwd;
    info.readerName = readerName;
    info.gender = getSexIndex();
    info.readerPhone = readerPhone;
    info.readerType = 2;
    info.readerClassID = readerClassID;
    info.readerCollege = readerCollege;
    info.borrowBookSize = borrowBookSize;
    info.readBookSize = readBookSize;
    info.existNoReturn = existNoReturn;
    info.touxiangName = m_newTX;
    if (m_newTX == "")
    {
        info.touxiangName = gQStr2Str(touxiangName);
    }
    return info;
}
void SuperAddUser::clearReaderInfoFormInfo()	//清空读者信息信息
{
    ui->le_readerID->setText("");
    ui->le_readerPwd->setText("");
    ui->le_readerName->setText("");
    ui->le_readerPhone->setText("");
    ui->le_readerClassID->setText("");
    ui->le_readerCollege->setText("");
    ui->l_Touxiang->clear();
    m_newTX = "";
}
int SuperAddUser::isExistReaderInfoKey(string readerID)	//查看关键字是否重复
{
    map<string, ReaderInfo>::iterator iter = gAllReaders.begin();
    for (;iter != gAllReaders.end();iter++)
    {
        if (iter->second.readerID == readerID)
        {
            return 1;
        }
    }
    return 0;
}
int SuperAddUser::getSexIndex()	//获取性别索引
{
    for (int m = 0;m < 2;m++)
    {
        if (m_gender[m]->isChecked())
        {
            return m;
        }
    }
    return 0;
}

void SuperAddUser::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString picName = gCurrPath + "/Img/bg.jpg";
    painter.drawPixmap(rect(), QPixmap(picName), QRect());
}
