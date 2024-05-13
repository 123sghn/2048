#ifndef GAMES4_H
#define GAMES4_H

#include <QWidget>
#include <QKeyEvent>
#include "implementation.h"
#include "timethread.h"

namespace Ui { class gameS4; }

class gameS4 : public QWidget
{
    Q_OBJECT

public:
    gameS4(QWidget* parent = nullptr);
    ~gameS4();

    void setAccount(int); //初始化界面
    void continueGame(int, Game); //继续之前的游戏
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnRetry_clicked(); //重新开始
    void on_pBtnRetry2_clicked(); //重新开始（游戏失败后）

    void on_pBtnPause_clicked(); //暂停
    void on_pBtnEnd_clicked(); //结束游戏

    //技能
    void on_pBtnLast_clicked(); //退回上一步
    void on_pBtnHammer_clicked(); //敲除一个方块
    void hammer(); //敲除方块

    //用户主界面、游戏界面
    void on_pBtnHome_clicked(); //从游戏界面返回用户主界面
    void on_pBtnHome2_clicked(); //从游戏界面返回用户主界面（游戏失败后）

signals:
    void returnHome(int, int); //信号：从游戏界面返回用户主界面

private:
    Ui::gameS4* ui;
    const int N;
    QPushButton* pbtn[4][4];

    int account; //账号

    int attempts; //总步数
    ll lstscore, score; //总得分
    Checkerboard cb; //棋盘
    bool dead; //是否死亡
    list<pair<vector<vector<ll>>, ll>> step; //记录每一步的操作

    int lastNum; //还剩的退回上一步的次数
    int hammerNum; //还剩的敲除一个方块的次数
    int reviveNum; //还剩的复活次数

    Countup time;
    bool gaming;
    TimeThread tt;

    void reset();
    void update();
    void die(); //死亡结算
    void updateTime();
};

#endif // GAMES4_H
