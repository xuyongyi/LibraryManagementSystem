#ifndef ADMINPERSON_H
#define ADMINPERSON_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class AdminPerson;
}

class AdminPerson : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPerson(QWidget *parent = 0);
    ~AdminPerson();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//设置显示界面
    void showReaderInfoFormInfo(ReaderInfo info);	//显示读者信息信息
    int getSexIndex();	//获取性别索引

    public slots:
    void slt_Reset();
    void slt_resetTX();

signals:
    void sig_Reset();

public:
    QRadioButton *m_gender[2];	//性别
    string m_newTX;

private:
    Ui::AdminPerson *ui;
};

#endif // ADMINPERSON_H
