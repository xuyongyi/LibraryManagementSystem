#ifndef READERJY_H
#define READERJY_H

#include <QWidget>
#include "../commdefclass.h"
#include "readerwarn.h"

namespace Ui {
class ReaderJY;
}

class ReaderJY : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderJY(QWidget *parent = 0);
    ~ReaderJY();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    void filterDatas(vector<BookBRRecordInfo> datas);
    void setUserJYHeader();
    void flushUserJYList(vector<BookBRRecordInfo> records);

    public slots:
    void slt_Look();	//浏览
    void slt_XJ();	//续借
    void slt_GH();	//归还

    void slt_UserJYSClicked(QTableWidgetItem *);	//列表元素被单击槽函数

public:
    BookBRRecordInfo m_SelectRecord;	//被选中的记录
    vector<BookBRRecordInfo> m_Records;


private:
    Ui::ReaderJY *ui;
};

#endif // READERJY_H
