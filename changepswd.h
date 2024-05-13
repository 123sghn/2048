#ifndef CHANGEPSWD_H
#define CHANGEPSWD_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class changepswd; }

class changepswd : public QWidget
{
    Q_OBJECT

public:
    changepswd(QWidget* parent = nullptr);
    ~changepswd();

    void setAccount(int);
    void setNewCode();
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnChange_clicked(); //更新验证码

    //修改密码
    void on_pBtnOK_clicked(); //修改密码（成功直接返回）
    void on_ldtCode_returnPressed();
    void on_ldtCPassword_returnPressed();

    //用户/管理员主界面、修改密码界面
    void on_pBtnRet_clicked(); //从修改密码界面返回用户/管理员主界面


signals:
    void returnHome(int, int); //信号：从修改密码界面返回用户/管理员主界面

private:
    Ui::changepswd* ui;
    int codeAnswer;
    int account;
    void reset();
};

#endif // CHANGEPSWD_H
