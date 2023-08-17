#ifndef ADMINFUNC_H
#define ADMINFUNC_H

#include <QWidget>
#include "../commdefclass.h"
#include "adminbook.h"
#include "adminuser.h"
#include "adminbrrecord.h"
#include "adminperson.h"
#include "adminreturnrecord.h"
#include "../customtabstyle.h"

namespace Ui {
class AdminFunc;
}

class AdminFunc : public QWidget
{
    Q_OBJECT

public:
    explicit AdminFunc(QWidget *parent = 0);
    ~AdminFunc();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面
    void addClass2Tab();	//添加类到tab

    public slots:
    void slt_tabChange(int);
    void slt_Reset();

signals:
    void sig_Reset();

public:
    AdminBook m_AdminBook;	//图书管理
    AdminUser m_AdminUser;	//用户管理
    AdminBRRecord m_AdminBRRecord;	//借阅记录管理
    AdminReturnRecord m_AdminReturnRecord;	//归还/续约记录
    AdminPerson m_AdminPerson;	//个人中心



private:
    Ui::AdminFunc *ui;
};

#endif // ADMINFUNC_H
