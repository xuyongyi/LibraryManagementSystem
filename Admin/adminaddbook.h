#ifndef ADMINADDBOOK_H
#define ADMINADDBOOK_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class AdminAddBook;
}

class AdminAddBook : public QWidget
{
    Q_OBJECT

public:
    explicit AdminAddBook(QWidget *parent = 0);
    ~AdminAddBook();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//初始化界面显示信息
    BookInfo getBookInfoFormInfo();	//获取图书信息信息
    void clearBookInfoFormInfo();	//清空图书信息信息
    int isExistBookInfoKey(string bookID);	//查看关键字是否重复
    void paintEvent(QPaintEvent *event);

    public slots:
    void slt_AddBookInfo();	//添加槽函数
    void slt_Back();	//返回
signals:
    void sig_Add();


private:
    Ui::AdminAddBook *ui;
};

#endif // ADMINADDBOOK_H
