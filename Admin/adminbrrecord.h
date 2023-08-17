#ifndef ADMINBRRECORD_H
#define ADMINBRRECORD_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class AdminBRRecord;
}

class AdminBRRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AdminBRRecord(QWidget *parent = 0);
    ~AdminBRRecord();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    void setUserHeader();
    void flushUserList(map<string, ReaderInfo> readers);
    void setBookHeader();
    void flushBookList(map<string, BookInfo> books);
    void flushAllData();	//刷新所有的数据
    void calcBeginEndTime(QDateTime curr,int zq,string &start,string &end); //计算开始结束时间

    public slots:
    void slt_LookUser();	//浏览读者
    void slt_FindUser();	//查询读者
    void slt_LookBook();	//浏览书籍
    void slt_FindBook();	//查询书籍

    void slt_UserSClicked(QTableWidgetItem *);	//列表元素被单击槽函数
    void slt_BookSClicked(QTableWidgetItem *);	//列表元素被单击槽函数

    void slt_JY();	//借阅
    void slt_Order();	//预约

public:
    ReaderInfo m_SelectUser;	//被选中的用户
    BookInfo m_SelectBook;	//被选中的图书
    BookBRRecordInfo m_SelectRecord;	//被选中的记录
    int m_currRecordWidgetIndex;	//当前窗体索引


private:
    Ui::AdminBRRecord *ui;
};

#endif // ADMINBRRECORD_H
