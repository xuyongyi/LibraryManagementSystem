#ifndef SUPERFUNC_H
#define SUPERFUNC_H

#include <QWidget>
#include "../commdefclass.h"
#include "adminmanagerwidget.h"
#include "supersysset.h"
#include "superperson.h"

namespace Ui {
class SuperFunc;
}

class SuperFunc : public QWidget
{
    Q_OBJECT

public:
    explicit SuperFunc(QWidget *parent = 0);
    ~SuperFunc();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面
    void addClass2Tab();	//添加类到tab

public slots:
    //void slt_tabChange(int );
    void slt_updateConfData();	//更新配置文件数据

    void slt_Admin();	//管理员管理
    void slt_Order();	//预约时长
    void slt_JYSC();	//借阅时长
    void slt_ZNJ();
    void slt_Person();
    void slt_WB();

public:
    AdminManagerWidget m_AdminManagerWidget;
    SuperSysSet m_SuperSysSetOrder;	//预约时长设置
    SuperSysSet m_SuperSysSetJYSC;	//借阅时长设置
    SuperSysSet m_SuperSysSetZNJ;	//滞纳金设置
    SuperPerson m_SuperPerson;
    SuperSysSet m_SuperSysSetWB;	//系统维保设置


private:
    Ui::SuperFunc *ui;
};

#endif // SUPERFUNC_H
