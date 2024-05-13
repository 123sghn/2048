#ifndef GIFT_H
#define GIFT_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class gift; }

class gift : public QWidget
{
    Q_OBJECT

public:
    gift(QWidget* parent = nullptr);
    ~gift();

    void setAccount(int i);
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnOK_clicked(); //领取礼包（成功后返回）
    void on_ldtGift_returnPressed();

    //用户主界面、礼包码界面
    void on_pBtnRet_clicked(); //从礼包码界面返回用户主界面

signals:
    void returnHome(int, int); //信号：从礼包码界面返回用户主界面

private:
    Ui::gift* ui;
    int account;
};

#endif // GIFT_H
