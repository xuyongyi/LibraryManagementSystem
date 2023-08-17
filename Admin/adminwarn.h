#ifndef ADMINWARN_H
#define ADMINWARN_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class AdminWarn;
}

class AdminWarn : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWarn(QWidget *parent = 0);
    ~AdminWarn();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面
    void filterRecords(vector<BookBRRecordInfo> records);	//过滤数据
    void paintEvent(QPaintEvent *event);

    void setUserJYHeader();
    void flushUserJYList(vector<BookBRRecordInfo> records);

public:
    vector<BookBRRecordInfo> m_Records;

private:
    Ui::AdminWarn *ui;
};

#endif // ADMINWARN_H
