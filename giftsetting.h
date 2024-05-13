#ifndef GIFTSETTING_H
#define GIFTSETTING_H

#include <QWidget>
#include <QStandardItemModel>
#include "implementation.h"

namespace Ui { class giftsetting; }

class giftsetting : public QWidget
{
    Q_OBJECT

public:
    giftsetting(QWidget* parent = nullptr);
    ~giftsetting();

    void update();
    void closeEvent(QCloseEvent*);

private slots:
    void on_tbvGift_clicked(const QModelIndex&); //单击修改
    void on_tbvGift_doubleClicked(const QModelIndex&); //双击删除

    void on_pBtnSave_clicked(); //保存

    void on_ldtCode_textChanged(const QString&);
    void on_sbxNum_valueChanged(int);
    void on_sbxPrice_valueChanged(int);
    void on_dteFalse_dateTimeChanged(const QDateTime&);

    //管理员主界面、礼包兑换码设置界面
    void on_pBtnRet_clicked(); //从礼包兑换码设置界面返回管理员主界面

signals:
    void returnAdmin(int, int); //信号：从礼包兑换码设置界面返回管理员主界面

private:
    Ui::giftsetting* ui;
    QStandardItemModel* model;
    int changed;
    string cur;
    void reset();
    bool save();
};

#endif // GIFTSETTING_H
