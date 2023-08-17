#ifndef READERORDER_H
#define READERORDER_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class ReaderOrder;
}

class ReaderOrder : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderOrder(QWidget *parent = 0);
    ~ReaderOrder();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    void setUserJYHeader();
    void flushUserJYList(vector<OrderInfo> records);

    public slots:
    void slt_Delete();	//删除预约
    void slt_Cancel();	//取消预约

    void slt_UserJYSClicked(QTableWidgetItem *);	//列表元素被单击槽函数

public:
    OrderInfo m_SelectRecord;	//被选中的记录
    vector<OrderInfo> m_Records;


private:
    Ui::ReaderOrder *ui;
};

#endif // READERORDER_H
