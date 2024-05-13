#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "implementation.h"
#include "gameS3.h"
#include "gameS4.h"
#include "gameS5.h"
#include "gameS6.h"
#include "gameS7.h"
#include "gameS8.h"
#include "gift.h"
#include "history.h"
#include "rankboard.h"
#include "changepswd.h"
#include "security.h"

namespace Ui { class home; }

class home : public QWidget
{
    Q_OBJECT

public:
    home(QWidget* parent = nullptr);
    ~home();

    void setAccount(int); //初始化界面
    void closeEvent(QCloseEvent*);

private slots:
    //修改用户名
    void on_pBtnName_clicked(); //修改用户名
    void on_ldtName_editingFinished(); //完成修改用户名

    //解锁新模式
    void on_pBtnLockS3_clicked(); //解锁3阶单人游戏
    void on_pBtnLockS4_clicked(); //解锁4阶单人游戏
    void on_pBtnLockS5_clicked(); //解锁5阶单人游戏
    void on_pBtnLockS6_clicked(); //解锁6阶单人游戏
    void on_pBtnLockS7_clicked(); //解锁7阶单人游戏
    void on_pBtnLockS8_clicked(); //解锁8阶单人游戏

    void unlock(int); //解锁新模式

    //用户主界面、游戏界面
    void on_pBtnGameS3_clicked(); //从用户主界面转到3阶单人游戏界面
    void on_pBtnGameS4_clicked(); //从用户主界面转到4阶单人游戏界面
    void on_pBtnGameS5_clicked(); //从用户主界面转到5阶单人游戏界面
    void on_pBtnGameS6_clicked(); //从用户主界面转到6阶单人游戏界面
    void on_pBtnGameS7_clicked(); //从用户主界面转到7阶单人游戏界面
    void on_pBtnGameS8_clicked(); //从用户主界面转到8阶单人游戏界面

    void fromGame(int, int); //从游戏界面返回用户主界面

    //用户主界面、礼包码界面
    void on_pBtnGift_clicked(); //从用户主界面转到礼包码界面
    void fromGift(int, int); //从礼包码界面返回用户主界面

    //用户主界面、历史记录界面
    void on_pBtnHistory_clicked(); //从用户主界面转到历史记录界面
    void fromHistory(int, int); //从历史记录界面返回用户主界面
    void continueGame(int, int, int); //继续原来的游戏

    //用户主界面、排行榜
    void on_pBtnRank_clicked(); //从用户主界面转到排行榜
    void fromRank(int, int); //从排行榜返回用户主界面

    //用户主界面、修改密码界面
    void on_pBtnPassword_clicked(); //从用户主界面转到修改密码界面
    void fromChangepswd(int, int); //从修改密码界面返回用户主界面

    //用户主界面、修改密保界面
    void on_pBtnSecurity_clicked(); //从用户主界面转到修改密保界面
    void fromSecurity(int, int); //从修改密保界面返回用户主界面

    //登录界面、用户主界面
    void on_pBtnRet_clicked(); //从用户主界面返回登录界面

signals:
    void returnLogin(int, int); //信号：从用户主界面返回登录界面

private:
    Ui::home* ui;
    QPushButton* pbtnGame[6];
    QPushButton* pbtnLock[6];

    gameS3 gameS3Form;
    gameS4 gameS4Form;
    gameS5 gameS5Form;
    gameS6 gameS6Form;
    gameS7 gameS7Form;
    gameS8 gameS8Form;

    gift giftForm;
    history historyForm;
    rankboard rankForm;
    changepswd changepswdForm;
    security securityForm;
    int account;
    void reset();
    void update(); //更新界面上的有关用户的信息
};

#endif // HOME_H
