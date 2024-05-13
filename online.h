#ifndef ONLINE_H
#define ONLINE_H

#include <QWidget>
#include <QStandardItemModel>
#include "implementation.h"

namespace Ui { class online; }

class online : public QWidget
{
    Q_OBJECT

public:
    online(QWidget* parent = nullptr);
    ~online();

    void setAccount(int);
    void closeEvent(QCloseEvent*);

private slots:
    void on_pBtnReset_clicked();

private:
    Ui::online* ui;
    QStandardItemModel* model;
    int account;
    void reset();
    void update();
};

#endif // ONLINE_H
