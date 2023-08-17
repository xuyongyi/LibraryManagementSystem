#ifndef READERFUNC_H
#define READERFUNC_H

#include <QWidget>
#include "../commdefclass.h"
#include "readerbook.h"
#include "readerjy.h"
#include "readerorder.h"
#include "readerperson.h"
#include "readerwarn.h"
#include "readertop.h"
#include "../customtabstyle.h"

namespace Ui {
class ReaderFunc;
}

class ReaderFunc : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderFunc(QWidget *parent = 0);
    ~ReaderFunc();

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
    ReaderBook m_ReaderBook;	//图书管理
    ReaderJY m_ReaderJY;	//借还管理
    ReaderOrder m_ReaderOrder;	//预约管理
    ReaderTop m_ReaderTop;	//排行榜
    ReaderPerson m_ReaderPerson;	//个人中心
    ReaderWarn m_ReaderWarn;	//逾期提醒

private:
    Ui::ReaderFunc *ui;
};

#endif // READERFUNC_H
