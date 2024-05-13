#ifndef LOGON_H
#define LOGON_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class logon; }

class logon : public QWidget
{
    Q_OBJECT

public:
    logon(QWidget* parent = nullptr);
    ~logon();

    void setNewCode(); //重置验证码
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnChange_clicked(); //更新验证码

    void on_ldtAnswer_returnPressed();

    //登录界面、注册界面
    void on_pBtnOK_clicked(); //开始注册（若注册成功，返回登录界面，并自动填写账号密码）
    void on_pBtnRet_clicked(); //从注册界面返回登录界面（未注册）

signals:
    void returnLogin(int, int); //信号：从注册界面返回登录界面（未注册）
    void returnLoginSucc(int, int, int, std::string); //信号：从注册界面返回登录界面（已注册）

private:
    Ui::logon* ui;
    int codeAnswer;
    bool succ;
    void reset(); //重置界面
};

#endif // LOGON_H
