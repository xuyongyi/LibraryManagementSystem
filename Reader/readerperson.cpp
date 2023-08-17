#include "readerperson.h"
#include "ui_readerperson.h"

ReaderPerson::ReaderPerson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderPerson)
{
    ui->setupUi(this);
    init();
    connectslots();
}

ReaderPerson::~ReaderPerson()
{
    delete ui;
}

void ReaderPerson::init()	//初始化
{
    ui->rb_man->setChecked(true);
    m_gender[0] = ui->rb_man;
    m_gender[1] = ui->rb_women;
}
void ReaderPerson::connectslots()	//连接信号与槽
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slt_resetTX()));
    connect(ui->pb_Regis, SIGNAL(clicked()), this, SLOT(slt_ResetReaderInfo()));
    connect(ui->pb_Del, SIGNAL(clicked()), this, SLOT(slt_DelUser()));
}
void ReaderPerson::setInitWidget()	//设置显示界面
{
    m_newTX = "";
    showReaderInfoFormInfo(gCurrReader);
}

void ReaderPerson::slt_DelUser()
{
    vector<BookBRRecordInfo> datas;
    gMySqlFunc.searchSingleBookBRRecordInfoTableStr(gError, datas,"readerID",gCurrReader.readerID);
    for (int m = 0;m < datas.size();m++)
    {
        if (datas[m].returnStat == 0)	//存在未归还书籍
        {
            gWarnning("存在尚未归还的书籍,不能注销!");
            return;
        }
        //计算是否有滞纳金
        if (datas[m].returnTime <= datas[m].realTime)
        {
            gWarnning("存在尚还清的滞纳金,不能注销!");
            return;
        }
    }
    if(gWarnningDel("确认注销?")== 0)
    {
        return;
    }
    gMySqlFunc.deleteReaderInfoTable(gError, gCurrReader); //删除当前账户
    gMySqlFunc.deleteCondTableStr(gError, "BookBRRecordInfo", "readerID", gCurrReader.readerID);	//删除借阅记录
    gMySqlFunc.deleteCondTableStr(gError, "OrderInfo", "readerID", gCurrReader.readerID);	//删除预订
    exit(0);
}

void ReaderPerson::slt_ResetReaderInfo()	//修改槽函数
{
    ReaderInfo info = getReaderInfoFormInfo();
    info.id = gCurrReader.id;
    info.borrowBookSize = gCurrReader.borrowBookSize;
    info.readBookSize = gCurrReader.readBookSize;
    info.existNoReturn = gCurrReader.existNoReturn;
    if (info.readerID == "" || info.readerPwd == "" || info.readerName == "" || info.readerPhone == "" || info.readerClassID == "" || info.readerCollege == "" || info.readerCollege == "" || info.touxiangName == "")
    {
        gWarnning("存在未填写项!");
        return;
    }
    gCurrReader = info;
    gMySqlFunc.updateReaderInfoTable(gError, info);
    emit sig_Reset();
    gWarnning("修改成功!");
    m_newTX = "";
    return;
}

void ReaderPerson::slt_resetTX()
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

ReaderInfo ReaderPerson::getReaderInfoFormInfo()	//获取读者信息信息
{
    int n = 0;
    ReaderInfo info;
    string readerID = gQStr2Str(ui->le_readerID->text());
    string readerPwd = gQStr2Str(ui->le_readerPwd->text());
    string readerName = gQStr2Str(ui->le_readerName->text());
    string readerPhone = gQStr2Str(ui->le_readerPhone->text());
    string readerClassID = gQStr2Str(ui->le_readerClassID->text());
    string readerCollege = gQStr2Str(ui->le_readerCollege->text());
    info.readerID = readerID;
    info.readerPwd = readerPwd;
    info.readerName = readerName;
    info.gender = getSexIndex();
    info.readerPhone = readerPhone;
    info.readerType = gCurrReader.readerType;
    info.readerClassID = readerClassID;
    info.readerCollege = readerCollege;
    info.touxiangName = gCurrReader.touxiangName;
    if(m_newTX != "")
    {
        info.touxiangName =m_newTX;
    }
    return info;
}
void ReaderPerson::clearReaderInfoFormInfo()	//清空读者信息信息
{
    ui->le_readerID->setText("");
    ui->le_readerPwd->setText("");
    ui->le_readerName->setText("");
    ui->le_readerPhone->setText("");
    ui->le_readerClassID->setText("");
    ui->le_readerCollege->setText("");
}
void ReaderPerson::showReaderInfoFormInfo(ReaderInfo info)	//显示读者信息信息
{
    ui->le_readerID->setText(gStr2QStr(info.readerID));
    ui->le_readerPwd->setText(gStr2QStr(info.readerPwd));
    ui->le_readerName->setText(gStr2QStr(info.readerName));
    ui->le_readerPhone->setText(gStr2QStr(info.readerPhone));
    ui->le_readerClassID->setText(gStr2QStr(info.readerClassID));
    ui->le_readerCollege->setText(gStr2QStr(info.readerCollege));
    m_gender[info.gender]->setChecked(true);
    gLoadPixmap(ui->l_Touxiang, info.touxiangName);
}

int ReaderPerson::getSexIndex()
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
