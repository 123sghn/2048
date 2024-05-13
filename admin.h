#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "implementation.h"
#include "manage.h"
#include "history.h"
#include "systemsetting.h"
#include "giftsetting.h"
#include "rankboard.h"
#include "changepswd.h"

namespace Ui { class admin; }

class admin : public QWidget
{
    Q_OBJECT

public:
    admin(QWidget* parent = nullptr);
    ~admin();

    void setAccount(int);
    void closeEvent(QCloseEvent*);

private slots:
    //修改用户名
    void on_pBtnName_clicked(); //修改用户名
    void on_ldtName_editingFinished(); //完成修改用户名

    //登录界面、管理员主界面
    void on_pBtnRet_clicked(); //从管理员主界面返回登录界面

    //管理员主界面、管理用户界面
    void on_pBtnPlayer_clicked(); //从管理员主界面转到管理用户界面
    void fromManage(int, int); //从管理用户界面返回管理员主界面

    //管理员主界面、历史记录界面
    void on_pBtnHistory_clicked(); //从管理员主界面转到历史记录界面
    void fromHistory(int, int); //从历史记录界面返回用户管理员主界面

    //管理员主界面、系统设置界面
    void on_pBtnSystem_clicked(); //从管理员主界面转到系统设置界面
    void fromSystem(int, int); //从系统设置界面返回管理员主界面

    //管理员主界面、礼包兑换码设置界面
    void on_pBtnGift_clicked(); //从管理员主界面转到礼包兑换码设置界面
    void fromGiftsetting(int, int); //从礼包兑换码设置界面返回管理员主界面

    //管理员主界面、排行榜
    void on_pBtnRank_clicked(); //从管理员主界面转到排行榜
    void fromRank(int, int); //从排行榜返回管理员主界面

    //管理员主界面、修改密码界面
    void on_pBtnPassword_clicked(); //从管理员主界面转到修改密码界面
    void fromChangepswd(int, int); //从修改密码界面返回管理员主界面

signals:
    void returnLogin(int, int); //信号：从管理员主界面返回登录界面

private:
    Ui::admin* ui;
    int account;
    manage manageForm;
    history historyForm;
    systemsetting systemForm;
    giftsetting giftsettingForm;
    rankboard rankForm;
    changepswd changepswdForm;
    void reset();
    void update();
};

#endif // ADMIN_H
