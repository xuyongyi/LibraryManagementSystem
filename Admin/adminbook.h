#ifndef ADMINBOOK_H
#define ADMINBOOK_H

#include <QWidget>
#include "../commdefclass.h"
#include "adminaddbook.h"

namespace Ui {
class AdminBook;
}

class AdminBook : public QWidget
{
    Q_OBJECT

public:
    explicit AdminBook(QWidget *parent = 0);
    ~AdminBook();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//初始化界面显示信息
    BookInfo getBookInfoFormInfo();	//获取图书信息信息
    void clearBookInfoFormInfo();	//清空图书信息信息
    void showBookInfoFormInfo(BookInfo info);	//显示图书信息信息
    void setBookInfoHeader();	//设置图书信息信息列表头部显示信息
    void flushBookInfoList();	//刷新图书信息信息列表
    int isExistBookInfoKey(string bookID);	//查看关键字是否重复

    public slots:
    void slt_AddBookInfo();	//添加槽函数
    void slt_DelBookInfo();	//删除槽函数
    void slt_ResetBookInfo();	//修改槽函数
    void slt_SearchBookInfo();	//关键字查询槽函数
    void slt_LookBookInfo();	//浏览槽函数
    void slt_ClearBookInfo();	//清空槽函数
    void slt_BookInfoSClicked(QTableWidgetItem *);	//列表元素被单击槽函数
    void slt_flushData();

public:
    BookInfo mSelectBookInfoItem;	//被选中的元素
    AdminAddBook m_AdminAddBook;


private:
    Ui::AdminBook *ui;
};

#endif // ADMINBOOK_H
