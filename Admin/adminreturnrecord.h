#ifndef ADMINRETURNRECORD_H
#define ADMINRETURNRECORD_H

#include <QWidget>
#include "../commdefclass.h"
#include "adminmoney.h"
#include "adminwarn.h"

namespace Ui {
class AdminReturnRecord;
}

class AdminReturnRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AdminReturnRecord(QWidget *parent = 0);
    ~AdminReturnRecord();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//初始化界面显示信息

    void setUserHeader();
    void flushUserList(map<string, ReaderInfo> readers);
    void setUserJYHeader();
    void flushUserJYList(vector<BookBRRecordInfo> records);
    void flushAllData();	//刷新所有的数据

    public slots:
    void slt_LookUser();	//浏览读者
    void slt_FindUser();	//查询读者
    void slt_LookUserJY();	//浏览读者借阅情况
    void slt_FindUserJY();	//查询读者借阅情况

    void slt_UserSClicked(QTableWidgetItem *);	//列表元素被单击槽函数
    void slt_UserJYSClicked(QTableWidgetItem *);	//列表元素被单击槽函数

    void slt_XJ();	//续借
    void slt_GH();	//归还
    void slt_Warn();	//到期提醒
    void slt_Money();	//罚款信息

public:
    ReaderInfo m_SelectUser;	//被选中的用户
    BookBRRecordInfo m_SelectRecord;	//被选中的记录
    AdminWarn m_AdminWarn;
    AdminMoney m_AdminMoney;


private:
    Ui::AdminReturnRecord *ui;
};

#endif // ADMINRETURNRECORD_H
