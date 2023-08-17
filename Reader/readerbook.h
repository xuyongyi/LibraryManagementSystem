#ifndef READERBOOK_H
#define READERBOOK_H

#include <QWidget>
#include "../commdefclass.h"
#include "readerwarn.h"

namespace Ui {
class ReaderBook;
}

class ReaderBook : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderBook(QWidget *parent = 0);
    ~ReaderBook();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    void calcBeginEndTime(QDateTime curr, int zq, string &start, string &end); //计算开始结束时间
    void clearBookInfoFormInfo();	//清空图书信息信息
    void showBookInfoFormInfo(BookInfo info);	//显示图书信息信息
    void setBookInfoHeader();	//设置图书信息信息列表头部显示信息
    void flushBookInfoList();	//刷新图书信息信息列表
    //void flushBookInfoListSort();	//刷新图书信息信息列表(排序)

    public slots:
    void slt_Search();
    void slt_Look();
    void slt_Borrow();	//借阅
    void slt_Order();	//预约
    void slt_BookInfoSClicked(QTableWidgetItem *);	//列表元素被单击槽函数

public:
    BookInfo m_SelectBook;	//被选中的元素
    ReaderWarn m_ReaderWarn;	//逾期提醒

private:
    Ui::ReaderBook *ui;
};

#endif // READERBOOK_H
