#ifndef READERWARN_H
#define READERWARN_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class ReaderWarn;
}

class ReaderWarn : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderWarn(QWidget *parent = 0);
    ~ReaderWarn();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面
    void filterRecords(vector<BookBRRecordInfo> records);	//过滤数据
    void paintEvent(QPaintEvent *event);

    void setInitWidget1();	//设置显示界面
    void filterRecords1(vector<BookBRRecordInfo> records);	//过滤数据

    void setUserJYHeader();
    void flushUserJYList(vector<BookBRRecordInfo> records);

public:
    vector<BookBRRecordInfo> m_Records;

private:
    Ui::ReaderWarn *ui;
};

#endif // READERWARN_H
