#ifndef MANAGE_H
#define MANAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include "implementation.h"
#include "online.h"

namespace Ui { class manage; }

class manage : public QWidget
{
    Q_OBJECT

public:
    manage(QWidget* parent = nullptr);
    ~manage();

    void setAccount(int);
    void closeEvent(QCloseEvent*);

private slots:
    //搜索相关
    void on_ldtSID_textChanged(const QString&);
    void on_ldtSName_textChanged(const QString&);
    void on_cmbUsers_currentIndexChanged(int);
    void on_cmbNormal_currentIndexChanged(int);
    void on_pBtnSID_clicked();
    void on_pBtnSName_clicked();

    void on_tbvPeople_clicked(const QModelIndex&);

    //修改玩家
    void on_pBtnPSave_clicked();
    void on_ldtPName_textEdited(const QString&);
    void on_sbxCoins_valueChanged(int);
    void on_cmbPDisable_currentIndexChanged(int);

    void on_pBtnS3_clicked();
    void on_pBtnS4_clicked();
    void on_pBtnS5_clicked();
    void on_pBtnS6_clicked();
    void on_pBtnS7_clicked();
    void on_pBtnS8_clicked();

    void on_pBtnPLogin_clicked();
    void on_pBtnPReset_clicked();
    void on_pBtnPClear_clicked();
    void on_pBtnPCancellation_clicked();

    //修改管理员
    void on_pBtnASave_clicked();
    void on_ldtAName_textEdited(const QString&);
    void on_cmbADisable_currentIndexChanged(int);

    void on_pBtnAReset_clicked();
    void on_pBtnACancellation_clicked();

    //管理员主界面、管理用户界面
    void on_pBtnRet_clicked(); //从管理用户界面返回管理员主界面


signals:
    void returnAdmin(int, int); //信号：从管理用户界面返回管理员主界面

private:
    Ui::manage* ui;
    QStandardItemModel* model;
    QPushButton* inform[6];
    online onlineForm;
    int account;
    int changed = 0;
    int identity = 0; //当前显示的是用户(0)，管理员(1)
    bool state[2]; //正常、封禁
    bool kinds[2]; //玩家、管理员
    int cur = 0; //当前处理的人
    void reset(); //清楚表格内所有东西、删除cur(函数)、页面显示恢复
    void update(); //更新表格里的信息
    bool save();
    bool needDisplay(int, string, string);
    void display(); //更新右侧修改区中的信息
};

#endif // MANAGE_H
