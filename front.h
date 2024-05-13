#ifndef FRONT_H
#define FRONT_H

#include <QWidget>
#include "implementation.h"
#include "login.h"
#include "help.h"
#include "version.h"

namespace Ui { class front; }

class front : public QWidget
{
    Q_OBJECT

public:
    front(QWidget* parent = nullptr);
    ~front();

    void closeEvent(QCloseEvent*);

private slots:
    //主界面、登录界面
    void on_pBtnLogin_clicked(); //从主界面转到登录界面
    void fromLogin(int, int); //从登录界面返回主界面

    //主界面、帮助界面
    void on_pBtnHelp_clicked(); //从主界面转到帮助界面
    void fromHelp(int, int); //从帮助界面返回主界面

    //主界面、关于版本界面
    void on_pBtnVersion_clicked(); //显示版本界面

    void on_pBtnExit_clicked(); //退出游戏

private:
    Ui::front* ui;
    login loginForm;
    help helpForm;
    version versionForm;
};

#endif //FRONT_H
