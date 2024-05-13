#ifndef FORGET_H
#define FORGET_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class forget; }

class forget : public QWidget
{
    Q_OBJECT

public:
    forget(QWidget* parent = nullptr);
    ~forget();

    void setNewCode(); //重置验证码
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnChange_clicked(); //更新验证码

    //重置密码
    void on_pBtnRet_clicked(); //从忘记密码界面返回主界面（未修改密码）
    void on_ldtCode_returnPressed();
    void on_ldtAnswer_returnPressed();
    void on_ldtCPassword_returnPressed();

    //登录界面、忘记密码界面
    void on_pBtnOK_clicked(); //修改密码（成功直接返回的注册界面）


signals:
    void returnLogin(int, int); //信号：从忘记密码界面返回登录界面（未修改密码）
    void returnLoginSucc(int, int, int, std::string); //信号：从忘记密码界面返回登录界面（成功修改密码）

private:
    Ui::forget* ui;
    int codeAnswer;
    int changeID;
    bool succ;
    void reset();
};

#endif // FORGET_H
