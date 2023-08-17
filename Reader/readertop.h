#ifndef READERTOP_H
#define READERTOP_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class ReaderTop;
}

class SortData
{
public:
    string id;
    int size;
};

class ReaderTop : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderTop(QWidget *parent = 0);
    ~ReaderTop();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    void sortBookByBorrowSize();	//排序(书籍)
    void sortReaderByBorrowSize();	//排序(读者)

    void setBookInfoHeader();	//设置图书信息信息列表头部显示信息
    void flushBookInfoList();	//刷新图书信息信息列表
    void setReaderInfoHeader();	//设置读者信息信息列表头部显示信息
    void flushReaderInfoList();	//刷新读者信息信息列表

public slots:
    void slt_Book();
    void slt_Reader();

public:
    vector<SortData> m_SortedBookVec;
    vector<SortData> m_SortedReaderVec;

private:
    Ui::ReaderTop *ui;
};

#endif // READERTOP_H
