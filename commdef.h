#ifndef COMMDEF_H
#define COMMDEF_H

#include "allhead.h"

extern string gError;
extern QString gStr2QStr(const string str);
extern string gQStr2Str(const QString qstr);

extern void gSetTableWidgetMode(QTableWidget *tw);
extern void gWarnning(string info);
extern int gWarnningDel(string info);
extern void gAddList2CB(QComboBox *cb, QStringList list);
extern string gGetDateTimemsStr();	//获取时间,yyyyMMddhhmmsszzz
extern void gLoadPixmap(QLabel *lb,string name);	//加载图片(头像,logo等)


extern ReaderInfo gCurrReader;	//当前登录账号
extern QString gCurrPath;	//存储图片路径
extern map<string, ReaderInfo> gAllReaders;	//所有的读者;
extern map<string, BookInfo> gAllBooks;		//所有的图书
extern vector<BookBRRecordInfo> gAllRecord;		//所有的读者借阅
extern QStringList gSex;    //性别

extern ConfInfo gConfInfo;	//配置信息(借阅时长,滞纳金等)
extern WBInfo gWBInfo;		//维保信息
extern QStringList gBookLanguage;	//书籍语言
extern QStringList gBookClass;		//书籍分类
extern QStringList gReaderType;		//读者类型
extern QStringList gFindCond;		//查找书籍条件
extern QStringList gFindReaderCond;		//查找读者条件


#endif // COMMDEF_H
