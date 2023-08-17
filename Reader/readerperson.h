#ifndef READERPERSON_H
#define READERPERSON_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class ReaderPerson;
}

class ReaderPerson : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderPerson(QWidget *parent = 0);
    ~ReaderPerson();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面

    ReaderInfo getReaderInfoFormInfo();	//获取读者信息信息
    void clearReaderInfoFormInfo();	//清空读者信息信息
    void showReaderInfoFormInfo(ReaderInfo info);	//显示读者信息信息
    int getSexIndex();	//获取性别索引

    public slots:
    void slt_ResetReaderInfo();	//修改槽函数
    void slt_resetTX();	//修改头像
    void slt_DelUser();	//注销账号

signals:
    void sig_Reset();

public:
    QRadioButton *m_gender[2];	//性别
    string m_newTX;

private:
    Ui::ReaderPerson *ui;
};

#endif // READERPERSON_H
