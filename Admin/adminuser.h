#ifndef ADMINUSER_H
#define ADMINUSER_H

#include <QWidget>
#include "../commdefclass.h"
#include "adminadduser.h"

namespace Ui {
class AdminUser;
}

class AdminUser : public QWidget
{
    Q_OBJECT

public:
    explicit AdminUser(QWidget *parent = 0);
    ~AdminUser();

    void init();	//初始化
    void connectslots();	//连接信号与槽
    void setInitWidget();	//初始化界面显示信息
    ReaderInfo getReaderInfoFormInfo();	//获取读者信息信息
    void clearReaderInfoFormInfo();	//清空读者信息信息
    void showReaderInfoFormInfo(ReaderInfo info);	//显示读者信息信息
    void setReaderInfoHeader();	//设置读者信息信息列表头部显示信息
    void flushReaderInfoList();	//刷新读者信息信息列表
    int isExistReaderInfoKey(string readerID);	//查看关键字是否重复
    int getSexIndex();	//获取性别索引

    public slots:
    void slt_AddReaderInfo();	//添加槽函数
    void slt_DelReaderInfo();	//删除槽函数
    void slt_ResetReaderInfo();	//修改槽函数
    void slt_SearchReaderInfo();	//关键字查询槽函数
    void slt_LookReaderInfo();	//浏览槽函数
    void slt_ClearReaderInfo();	//清空槽函数
    void slt_ReaderInfoSClicked(QTableWidgetItem *);	//列表元素被单击槽函数
    void slt_ResetTX();	//更改头像
    void slt_flushUsers();

public:
    QRadioButton *m_gender[2];	//性别
    ReaderInfo mSelectReaderInfoItem;	//被选中的元素
    string m_newTX;
    AdminAddUser m_AdminAddUser;

private:
    Ui::AdminUser *ui;
};

#endif // ADMINUSER_H
