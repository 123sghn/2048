#ifndef SECURITY_H
#define SECURITY_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class security; }

class security : public QWidget
{
    Q_OBJECT

public:
    security(QWidget* parent = nullptr);
    ~security();

    void setAccount(int);
    void setNewCode();
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnChange_clicked(); //更新验证码

    //修改密保
    void on_pBtnOK_clicked(); //修改密保（成功直接返回）
    void on_ldtCode_returnPressed();
    void on_ldtAnswer_returnPressed();

    //用户主界面、修改密保界面
    void on_pBtnRet_clicked(); //从修改密保界面返回用户主界面


signals:
    void returnHome(int, int); //信号：从修改密保界面返回用户主界面

private:
    Ui::security* ui;
    int codeAnswer;
    int account;
    void reset();
};

#endif // SECURITY_H
