#ifndef SUPERPERSON_H
#define SUPERPERSON_H

#include <QWidget>
#include "../commdefclass.h"

namespace Ui {
class SuperPerson;
}

class SuperPerson : public QWidget
{
    Q_OBJECT

public:
    explicit SuperPerson(QWidget *parent = 0);
    ~SuperPerson();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget(QString label,string value);	//设置显示界面
    void paintEvent(QPaintEvent *event);

signals:
    void sig_OK();	//发送修改信号

    public slots:
    void slt_OK();

public:
    string m_resetValue;	//修改后的值

private:
    Ui::SuperPerson *ui;
};

#endif // SUPERPERSON_H
