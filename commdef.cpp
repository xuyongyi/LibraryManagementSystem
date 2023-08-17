#include "commdef.h"

string gError;
ReaderInfo gCurrReader;
QString gCurrPath;	//存储图片路径
map<string, ReaderInfo> gAllReaders;	//所有的读者;
map<string, BookInfo> gAllBooks;		//所有的图书
vector<BookBRRecordInfo> gAllRecord;

ConfInfo gConfInfo;	//配置信息(借阅时长,滞纳金等)
WBInfo gWBInfo;		//维保信息
QStringList gBookLanguage;	//书籍语言
QStringList gBookClass;		//书籍分类
QStringList gReaderType;		//读者类型
QStringList gFindCond;		//查找书籍条件
QStringList gFindReaderCond;		//查找读者条件
QStringList gSex;

QString gStr2QStr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string gQStr2Str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void gSetTableWidgetMode(QTableWidget *tw)
{
    //tw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //tw->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tw->setSelectionMode(QAbstractItemView::SingleSelection);
    tw->setSelectionBehavior(QAbstractItemView::SelectRows);	//整行选中
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);	//设置不可编辑
}

void gWarnning(string info)
{
    QString error = QString::fromStdString(info);
    //QMessageBox::warning(NULL, "Warning", error, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    QMessageBox box(QMessageBox::Warning, "警告", error);
    box.setStandardButtons(QMessageBox::Ok);
    box.setButtonText(QMessageBox::Ok, QString("确 定"));
    //box.setButtonText(QMessageBox::Cancel, QString("取 消"));
    box.exec();
    return;
}

int gWarnningDel(string info)
{
    QString error = QString::fromStdString(info);
    //QMessageBox::warning(NULL, "Warning", error, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    QMessageBox box(QMessageBox::Warning, "警告", error);
    box.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok, QString("确 定"));
    box.setButtonText(QMessageBox::Cancel, QString("取 消"));
    int button = box.exec();
    if (button == QMessageBox::Ok)
    {
        return 1;
    }
    return 0;
}

void gAddList2CB(QComboBox *cb, QStringList list)
{
    cb->clear();
    cb->addItems(list);
}

string gGetDateTimemsStr()
{
    return gQStr2Str(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
}

void gLoadPixmap(QLabel *lb, string name)	//加载图片(头像,logo等)
{
    QString picName = gStr2QStr(name);
    QPixmap *pixmap = new QPixmap(picName);
    pixmap->scaled(lb->size(), Qt::KeepAspectRatio);
    lb->setScaledContents(true);
    lb->setPixmap(*pixmap);
}
