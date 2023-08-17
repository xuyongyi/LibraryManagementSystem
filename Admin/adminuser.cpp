#include "adminuser.h"
#include "ui_adminuser.h"

AdminUser::AdminUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminUser)
{
    ui->setupUi(this);
    init();
    connectslots();
}

AdminUser::~AdminUser()
{
    delete ui;
}

void AdminUser::init()
{

    ui->comboBox->addItem("学生");
    ui->comboBox->addItem("教师");
    ui->rb_man->setChecked(true);
    m_gender[0] = ui->rb_man;
    m_gender[1] = ui->rb_women;
    setReaderInfoHeader();
    gSetTableWidgetMode(ui->tw_ReaderInfo);
}

void AdminUser::connectslots()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slt_ResetTX()));
    connect(ui->pb_AddReaderInfo, SIGNAL(clicked()), this, SLOT(slt_AddReaderInfo()));
    connect(ui->pb_DelReaderInfo, SIGNAL(clicked()), this, SLOT(slt_DelReaderInfo()));
    connect(ui->pb_ResetReaderInfo, SIGNAL(clicked()), this, SLOT(slt_ResetReaderInfo()));
    connect(ui->pb_SearchReaderInfo, SIGNAL(clicked()), this, SLOT(slt_SearchReaderInfo()));
    connect(ui->pb_LookReaderInfo, SIGNAL(clicked()), this, SLOT(slt_LookReaderInfo()));
    connect(ui->pb_ClearReaderInfo, SIGNAL(clicked()), this, SLOT(slt_ClearReaderInfo()));
    connect(ui->tw_ReaderInfo, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(slt_ReaderInfoSClicked(QTableWidgetItem *)));

    connect(&m_AdminAddUser, SIGNAL(sig_Add()), this, SLOT(slt_flushUsers()));
}

void AdminUser::setInitWidget()
{
    m_newTX = "";
    gAddList2CB(ui->cb_Cond, gFindReaderCond);
    clearReaderInfoFormInfo();
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);//结合数据库,从数据库中查找信息
    flushReaderInfoList();
}

ReaderInfo AdminUser::getReaderInfoFormInfo()
{
    int n = 0;
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
    info.readerType = mSelectReaderInfoItem.readerType;
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

void AdminUser::clearReaderInfoFormInfo()
{
    int m = 0;
    ui->le_readerID->setText("");
    ui->le_readerPwd->setText("");
    ui->le_readerName->setText("");
    ui->le_readerPhone->setText("");
    ui->le_readerClassID->setText("");
    ui->le_readerCollege->setText("");
    mSelectReaderInfoItem.id = -1;
    ui->l_Touxiang->clear();
}

void AdminUser::showReaderInfoFormInfo(ReaderInfo info)
{
    int m = 0;
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

void AdminUser::setReaderInfoHeader()
{
    QStringList headers;
    headers << ("学号/职工号") << ("密码") << ("读者姓名") << ("性别") << ("手机号")  << ("读者年级") << ("读者院系") << ("读者院系") << ("借阅书籍数量") << ("读书量") << ("存在未归还图书")/* << ("读者类型")*/;
    ui->tw_ReaderInfo->setColumnCount(headers.size());
    //ui->tw_ReaderInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tw_ReaderInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_ReaderInfo->setHorizontalHeaderLabels(headers);
}

void AdminUser::flushReaderInfoList()
{
    ui->tw_ReaderInfo->setRowCount(gAllReaders.size());
    int row = 0;
    map<string, ReaderInfo>::iterator iter = gAllReaders.begin();
    for (;iter != gAllReaders.end();iter++)
    {
        ReaderInfo info = iter->second;
        ui->tw_ReaderInfo->setItem(row, 0, new QTableWidgetItem(gStr2QStr(info.readerID)));
        ui->tw_ReaderInfo->setItem(row, 1, new QTableWidgetItem(gStr2QStr(info.readerPwd)));
        ui->tw_ReaderInfo->setItem(row, 2, new QTableWidgetItem(gStr2QStr(info.readerName)));
        ui->tw_ReaderInfo->setItem(row, 3, new QTableWidgetItem(gSex[info.gender]));
        ui->tw_ReaderInfo->setItem(row, 4, new QTableWidgetItem(gStr2QStr(info.readerPhone)));
        ui->tw_ReaderInfo->setItem(row, 5, new QTableWidgetItem(gStr2QStr(info.readerClassID)));
        ui->tw_ReaderInfo->setItem(row, 6, new QTableWidgetItem(gStr2QStr(info.readerCollege)));
        ui->tw_ReaderInfo->setItem(row, 7, new QTableWidgetItem(gStr2QStr(info.readerCollege)));
        ui->tw_ReaderInfo->setItem(row, 8, new QTableWidgetItem(QString::number(info.borrowBookSize)));
        ui->tw_ReaderInfo->setItem(row, 9, new QTableWidgetItem(QString::number(info.readBookSize)));
        ui->tw_ReaderInfo->setItem(row, 10, new QTableWidgetItem(QString::number(info.existNoReturn)));
        //ui->tw_ReaderInfo->setItem(row, 11, new QTableWidgetItem(gReaderType[info.readerType]));
        row++;
    }
}

int AdminUser::isExistReaderInfoKey(string readerID)	//查看关键字是否重复
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

int AdminUser::getSexIndex()
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

void AdminUser::slt_AddReaderInfo()
{
    m_AdminAddUser.setInitWidget();
    m_AdminAddUser.show();
    /*ReaderInfo info = getReaderInfoFormInfo();
    if (info.readerID == "" || info.readerPwd == "" || info.readerName == "" || info.readerPhone == "" || info.readerClassID == "" || info.readerCollege == "" || info.touxiangName == "")
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
    flushReaderInfoList();
    return;*/
}

void AdminUser::slt_DelReaderInfo()
{
    if (mSelectReaderInfoItem.id == -1)
    {
        gWarnning("请先选择要删除的读者信息!");
        return;
    }
    if(gWarnningDel("确认删除?") == 0)
    {
        return;
    }
    gMySqlFunc.deleteReaderInfoTable(gError, mSelectReaderInfoItem);
    gMySqlFunc.deleteCondTableStr(gError, "BookBRRecordInfo", "readerID", mSelectReaderInfoItem.readerID);	//删除借阅记录
    gMySqlFunc.deleteCondTableStr(gError, "OrderInfo", "readerID", mSelectReaderInfoItem.readerID);	//删除预订

    //根据实际需要增加删除关联的数据库数据信息代码
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);
    clearReaderInfoFormInfo();
    flushReaderInfoList();
    return;
}

void AdminUser::slt_ResetReaderInfo()
{
    if (mSelectReaderInfoItem.id == -1)
    {
        gWarnning("请先选择要删除的读者信息!");
        return;
    }
    ReaderInfo info = getReaderInfoFormInfo();
    info.id = mSelectReaderInfoItem.id;
    if (info.readerID == "" || info.readerPwd == "" || info.readerName == "" || info.readerPhone == "" || info.readerClassID == "" || info.readerCollege == "" || info.readerCollege == "" || info.touxiangName == "")
    {
        gWarnning("存在未填写项!");
        return;
    }
    if (info.readerID != mSelectReaderInfoItem.readerID)
    {
        if (isExistReaderInfoKey(info.readerID))//关键字发生变化
        {
            gWarnning("readerID已存在,修改失败!");
            return;
        }
    }
    gMySqlFunc.updateReaderInfoTable(gError, info);
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);
    clearReaderInfoFormInfo();
    flushReaderInfoList();
    return;
}

void AdminUser::slt_SearchReaderInfo()
{
    int condIndex = ui->cb_Cond->currentIndex();
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);
    QString key = ui->le_Key->text().trimmed();
    if (key == "")
    {
        gWarnning("请输入查询关键字!");
        return;
    }
    map<string, ReaderInfo> temp = gAllReaders;
    gAllReaders.clear();
    map<string, ReaderInfo>::iterator iter = temp.begin();
    for (;iter != temp.end();iter++)
    {
        ReaderInfo info = iter->second;
        QString condStr;
        if (condIndex == 0)
        {
            QString readerID = gStr2QStr(info.readerID);
            QString readerPwd = gStr2QStr(info.readerPwd);
            QString readerName = gStr2QStr(info.readerName);
            QString readerPhone = gStr2QStr(info.readerPhone);
            QString readerClassID = gStr2QStr(info.readerClassID);
            QString readerCollege = gStr2QStr(info.readerCollege);
            QString touxiangName = gStr2QStr(info.touxiangName);

            if (readerID.contains(key) || readerPwd.contains(key) || readerName.contains(key) || readerPhone.contains(key) || readerClassID.contains(key) || readerCollege.contains(key) || readerCollege.contains(key) || touxiangName.contains(key))
            {
                gAllReaders[iter->first] = info;
            }
            return;
        }
        else if (condIndex == 1)
        {
            condStr = gStr2QStr(info.readerID);
        }
        else if (condIndex == 2)
        {
            condStr = gStr2QStr(info.readerName);
        }
        else if (condIndex == 3)
        {
            condStr = gStr2QStr(info.readerPhone);
        }
        else if (condIndex == 4)
        {
            condStr = gStr2QStr(info.readerClassID);
        }
        else if (condIndex == 5)
        {
            condStr = gStr2QStr(info.readerCollege);
        }
        if (condStr.contains(key))
        {
            gAllReaders[iter->first] = info;
        }
    }
    clearReaderInfoFormInfo();
    flushReaderInfoList();
    return;
}

void AdminUser::slt_LookReaderInfo()
{
    gMySqlFunc.searchSingleReaderInfoTableIntNo(gError, gAllReaders,"readerType",2);
    clearReaderInfoFormInfo();
    flushReaderInfoList();
}

void AdminUser::slt_ClearReaderInfo()
{
    clearReaderInfoFormInfo();
}

void AdminUser::slt_ReaderInfoSClicked(QTableWidgetItem *item)
{
    int count = item->row();
    int row = 0;
    map<string, ReaderInfo>::iterator iter = gAllReaders.begin();
    for (;iter != gAllReaders.end();iter++)
    {
        if (row == count)
        {
            mSelectReaderInfoItem = iter->second;
            showReaderInfoFormInfo(mSelectReaderInfoItem);
            break;
        }
        row++;
    }
}

void AdminUser::slt_ResetTX()	//更改头像
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

void AdminUser::slt_flushUsers()
{
    setInitWidget();
}
