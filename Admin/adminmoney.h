#ifndef ADMINMONEY_H
#define ADMINMONEY_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class AdminMoney;
}

class AdminMoney : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMoney(QWidget *parent = 0);
    ~AdminMoney();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    void filterRecords(vector<BookBRRecordInfo> records);	//过滤数据

    void setUserJYHeader();
    void flushUserJYList(vector<BookBRRecordInfo> records);
    void paintEvent(QPaintEvent *event);

    public slots:
    void slt_Money();
    void slt_UserSClicked(QTableWidgetItem *);	//列表元素被单击槽函数


public:
    vector<BookBRRecordInfo> m_Records;
    BookBRRecordInfo m_SelectUserJL;


private:
    Ui::AdminMoney *ui;
};

#endif // ADMINMONEY_H
