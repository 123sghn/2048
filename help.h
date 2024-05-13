#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QGroupBox>
#include "implementation.h"

namespace Ui { class help; }

class help : public QWidget
{
    Q_OBJECT

public:
    help(QWidget* parent = nullptr);
    ~help();

    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnPlayer_clicked(); //切换到玩家帮助
    void on_pBtnAdmin_clicked(); //切换到管理员帮助

    void on_pBtnPre_clicked(); //上一页
    void on_pBtnNxt_clicked(); //下一页

    //主界面、帮助界面
    void on_pBtnRet_clicked(); //从帮助界面返回主界面

signals:
    void returnFront(int, int); //信号：从帮助界面返回主界面

private:
    Ui::help* ui;
    QGroupBox* gbx[2][13];

    int status; //0表示用户，1表示管理员
    int page;
    int maxpage[2];
    int last;
    void reset();
    void update();
};

#endif // HELP_H
