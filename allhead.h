#ifndef ALLHEAD_H
#define ALLHEAD_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <iostream>
#include <QDebug>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <io.h>
#include <direct.h>

#include <QDir>
#include <QFile>
#include <QSettings>
#include <QProcess>
#include <QTimer>
#include <QTextCodec>
#include <QPixmap>
#include <QPainter>
#include <QLineEdit>
#include <QLabel>
#include <windows.h>
#include <QFileDialog>

#include <QDateTime>
#include <QMessageBox>
#include <QUuid>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QQueue>
#include <QMap>
#include <QVector>
#include <QTableWidgetItem>
#include <QRadioButton>
#include <QHeaderView>
#include <QComboBox>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include "mysql.h"
//#pragma comment(lib,"libmysql.lib")

using namespace std;

class ReaderInfo	//读者信息
{
public:
    int id;	//数据库主键
    string readerID;	//读者账号(唯一值,需要手动输入)
    string readerPwd;	//密码
    string readerName;	//读者姓名
    int gender;	//性别
    string readerPhone;	//手机号
    int readerType;	//读者类型(0:学生,1:教师,2:普通管理员)
    string readerClassID;	//读者年级
    string readerCollege;	//读者院系
    string readerMajor;	//读者专业
    int borrowBookSize;	//借阅书籍数量
    int readBookSize;	//读书量
    int existNoReturn;	//存在未归还图书(0:没有,1:有)
    string touxiangName;	//头像
};


class BookInfo {	//图书信息
public:
    int id;
    string bookID;	//图书编号(唯一值,条形码)
    string bookIndex;	//图书索引号
    string bookClassID;	//书籍分类号
    string bookName;	//图书名称
    string bookAuth;	//图书作者
    string bookPublish;	//出版社
    string bookPushDate;	//图书发布时间
    string bookISBN;	//图书ISBN号
    string bookDesc;	//图书简短介绍
    string bookLanguage;	//图书语言
    float bookPrice;	//图书价格
    string bookType;	//图书分类
    int totalSize;	//总数量
    int noBorrowSize;	//未借出数量
    int borrowedSize; //借出数量
};


class BookBRRecordInfo	//图书借还记录
{
public:
    int id;
    string borrowID;	//借阅编号(时间)
    string readerID;	//读者ID
    string bookID;	//图书编号(唯一值,条形码)
    string bookISBN;	//图书ISBN号
    string borrowTime;	//借书时间
    string returnTime;	//理论归还时间
    string realTime;	//实际归还时间
    int returnStat;		//归还状态(0:未归还,1:已归还)
    int warnDays;		//警告天数
};

class OrderInfo //预约信息
{
public:
    int id;
    string orderID;	//预约编号(时间)
    string readerID;	//读者ID
    string bookID;	//图书编号(唯一值,条形码)
    string orderTime;	//预约时间
    string orderFinishTime;	//预约结束时间
    int orderStat;	//预约后已借阅图书(0:未借阅,1:已借阅)
    int isOverTime;	//已超时
    int waitStat;	//状态(1:等待,0:取消)
};

class ConfInfo
{
public:
    string superID;		//超级管理员账号
    string superPwd;	//超级管理员密码
    string order;	//预约时长
    string jysc;	//借阅时长
    string znj;		//滞纳金
    string wbTime;	//维保时间
};

class WBInfo
{
public:
    string wbStartTime;		//超级管理员账号
    string wbStopTime;	//超级管理员密码
};

#endif // ALLHEAD_H
