#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class systemsetting; }

class systemsetting : public QWidget
{
    Q_OBJECT

public:
    systemsetting(QWidget* parent = nullptr);
    ~systemsetting();

    void setAccount(int);
    void closeEvent(QCloseEvent*);

private slots:

    //数据文件设置
    void on_pBtnBackup_clicked();
    void on_pBtnRecover_clicked();
    void on_pBtnReset_clicked();

    //管理员主界面、游戏设置界面
    void on_pBtnRet_clicked(); //从游戏设置界面返回管理员主界面

signals:
    void returnAdmin(int, int); //信号：从游戏设置界面返回管理员主界面

private:
    Ui::systemsetting* ui;
    int account;
    void reset();
};

#endif // SYSTEMSETTING_H
