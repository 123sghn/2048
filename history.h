#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QGroupBox>
#include <QStandardItemModel>
#include "implementation.h"

namespace Ui { class history; }

class history : public QWidget
{
    Q_OBJECT

public:
    history(QWidget* parent = nullptr);
    ~history();

    void setAccount(int);
    void closeEvent(QCloseEvent*);

private slots:
    void on_tbvHistory_clicked(const QModelIndex &index); //查看最终棋盘
    void on_tbvHistory_doubleClicked(const QModelIndex &index); //删除记录
    void on_pBtnContinue_clicked(); //继续游戏

    //用户主界面、历史记录界面
    void on_pBtnRet_clicked(); //从历史记录界面返回用户主界面

signals:
    void returnHome(int, int); //信号：从历史记录界面返回用户主界面
    void continueGame(int, int, int); //信号：继续原来的游戏

private:
    Ui::history* ui;
    QGroupBox* gbx[6];
    vector<vector<vector<QPushButton*>>> pbtn;
    int r;
    bool conti;
    int account;
    QStandardItemModel *model;
    void reset();
    void update();
};

#endif // HISTORY_H
