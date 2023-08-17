#include "adminperson.h"
#include "ui_adminperson.h"

AdminPerson::AdminPerson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPerson)
{
    ui->setupUi(this);
    init();
    connectslots();
}

AdminPerson::~AdminPerson()
{
    delete ui;
}

void AdminPerson::init()	//初始化
{
    ui->le_readerID->setEnabled(false);
    ui->rb_man->setChecked(true);
    m_gender[0] = ui->rb_man;
    m_gender[1] = ui->rb_women;
    ui->label_8->hide();
    ui->label_5->hide();
    ui->comboBox->hide();
    ui->le_readerClassID->hide();
}
void AdminPerson::connectslots()	//连接信号与槽
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slt_resetTX()));
    connect(ui->pb_LookReaderInfo, SIGNAL(clicked()), this, SLOT(slt_Reset()));
}
void AdminPerson::setInitWidget()	//设置显示界面
{
    m_newTX = "";
    showReaderInfoFormInfo(gCurrReader);
}

void AdminPerson::slt_Reset()
{
    gCurrReader.readerPwd = gQStr2Str(ui->le_readerPwd->text());
    gCurrReader.readerName = gQStr2Str(ui->le_readerName->text());
    gCurrReader.readerPhone = gQStr2Str(ui->le_readerPhone->text());
    gCurrReader.readerClassID = gQStr2Str(ui->le_readerClassID->text());
    gCurrReader.readerCollege = gQStr2Str(ui->le_readerCollege->text());
    //gCurrReader.readerType = ui->comboBox->currentIndex();
    QString touxiangName = gCurrPath + "/Img/0.jpg";
    gCurrReader.touxiangName = gQStr2Str(touxiangName);
    if (m_newTX != "")
    {
        gCurrReader.touxiangName = m_newTX;
    }
    if (gCurrReader.readerID == "" || gCurrReader.readerPwd == "" || gCurrReader.readerName == "" \
        || gCurrReader.readerPhone == "" || gCurrReader.readerCollege == "")
    {
        gWarnning("存在未填写项!");
        return;
    }
    m_newTX = "";
    gMySqlFunc.updateReaderInfoTable(gError,gCurrReader);
    gWarnning("修改成功!");
    emit sig_Reset();
    return;
}

void AdminPerson::slt_resetTX()
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

void AdminPerson::showReaderInfoFormInfo(ReaderInfo info)	//显示读者信息信息
{
    ui->le_readerID->setText(gStr2QStr(info.readerID));
    ui->le_readerPwd->setText(gStr2QStr(info.readerPwd));
    ui->le_readerName->setText(gStr2QStr(info.readerName));
    ui->le_readerPhone->setText(gStr2QStr(info.readerPhone));
    ui->le_readerClassID->setText(gStr2QStr(info.readerClassID));
    ui->le_readerCollege->setText(gStr2QStr(info.readerCollege));
    m_gender[info.gender]->setChecked(true);
    gLoadPixmap(ui->l_Touxiang, info.touxiangName);
    return;
}

int AdminPerson::getSexIndex()
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
