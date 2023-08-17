#ifndef SUPERADDUSER_H
#define SUPERADDUSER_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class SuperAddUser;
}

class SuperAddUser : public QWidget
{
    Q_OBJECT

public:
    explicit SuperAddUser(QWidget *parent = 0);
    ~SuperAddUser();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//初始化界面显示信息
    ReaderInfo getReaderInfoFormInfo();	//获取读者信息信息
    void clearReaderInfoFormInfo();	//清空读者信息信息
    int isExistReaderInfoKey(string readerID);	//查看关键字是否重复
    int getSexIndex();	//获取性别索引
    void paintEvent(QPaintEvent *event);

    public slots:
    void slt_Back();	//添加槽函数
    void slt_AddReaderInfo();	//添加槽函数
    void slt_ResetTX();	//更改头像

signals:
    void sig_Add();

public:
    QRadioButton *m_gender[2];	//性别
    ReaderInfo mSelectReaderInfoItem;	//被选中的元素
    string m_newTX;

private:
    Ui::SuperAddUser *ui;
};

#endif // SUPERADDUSER_H
