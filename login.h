#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "implementation.h"
#include "home.h"
#include "admin.h"
#include "logon.h"
#include "forget.h"

namespace Ui { class login; }

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget* parent = nullptr);
    ~login();

    void update();
    void closeEvent(QCloseEvent*);

private slots:
    void on_ldtID_textChanged(const QString&); //更新id后将密码清空
    void on_ldtPassword_returnPressed(); //输完密码按enter键登录

    //登录界面、用户主界面/管理员主界面
    void on_pBtnLogin_clicked(); //登录（从登录界面转到用户主界面）
    void fromHome(int, int); //从用户主界面返回登录界面
    void fromAdmin(int, int); //从用户主界面返回登录界面

    //登录界面、注册界面
    void on_pBtnLogon_clicked(); //从登录界面转到注册界面
    void fromLogon(int, int); //从注册界面返回登录界面（未注册）
    void fromLogonSucc(int, int, int, std::string); //从注册界面返回登录界面（成功注册）

    //登录界面、忘记密码界面
    void on_pBtnForget_clicked(); //从登录界面转到忘记密码界面
    void fromForget(int, int); //从忘记密码界面返回登录界面（未修改密码）
    void fromForgetSucc(int, int, int, std::string); //从忘记密码界面返回登录界面（成功修改密码）

    //主界面、登录界面
    void on_pBtnRet_clicked(); //从登录界面返回主界面

    //记住
    void on_cbxID_stateChanged(int); //记住账号
    void on_cbxPswd_stateChanged(int); //记住密码

signals:
    void returnFront(int, int); //信号：从登录界面返回主界面

private:
    Ui::login* ui;
    logon logonForm; //注册界面
    home homeForm; //用户主界面
    forget forgetForm; //忘记密码界面
    admin adminForm; //管理员界面
    void reset();
};

#endif // LOGIN_H
