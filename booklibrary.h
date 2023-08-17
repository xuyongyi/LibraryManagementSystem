#ifndef BOOKLIBRARY_H
#define BOOKLIBRARY_H

#include <QWidget>

#include "commdefclass.h"
#include "SuperAdmin/superfunc.h"
#include "Admin/adminfunc.h"
#include "Reader/readerfunc.h"

namespace Ui {
class BookLibrary;
}

class BookLibrary : public QWidget
{
    Q_OBJECT

public:
    explicit BookLibrary(QWidget *parent = 0);
    ~BookLibrary();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget(int userType);	//设置显示界面
    void addClass2Tab();	//添加类到tab

    void paintEvent(QPaintEvent *event);	//画事件

    public slots:
    void slt_Exit();
    void slt_flushTX();

signals:
    void sig_exit();

public:
    int m_userType;	//用户类型(0:超级管理员,1:普通管理员,2:学生/教师)

    SuperFunc m_SuperFunc;	//超级管理员
    AdminFunc m_AdminFunc;	//普通管理员
    ReaderFunc m_ReaderFunc;	//读者

private:
    Ui::BookLibrary *ui;
};

#endif // BOOKLIBRARY_H
