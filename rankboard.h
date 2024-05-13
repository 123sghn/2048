#ifndef RANKBOARD_H
#define RANKBOARD_H

#include <QWidget>
#include <QStandardItemModel>
#include "implementation.h"

namespace Ui { class rankboard; }

class rankboard : public QWidget
{
    Q_OBJECT

public:
    rankboard(QWidget* parent = nullptr);
    ~rankboard();

    void setEditable(bool b);
    void update(int);
    void closeEvent(QCloseEvent*);

private slots:
    //切换展示的排行榜
    void on_pBtn3_clicked(); //展示3阶排行榜
    void on_pBtn4_clicked(); //展示4阶排行榜
    void on_pBtn5_clicked(); //展示5阶排行榜
    void on_pBtn6_clicked(); //展示6阶排行榜
    void on_pBtn7_clicked(); //展示7阶排行榜
    void on_pBtn8_clicked(); //展示8阶排行榜

    void on_tbvRanklist_doubleClicked(const QModelIndex&);

    //用户主界面、排行榜
    void on_pBtnRet_clicked(); //从排行榜返回用户主界面

signals:
    void returnHome(int, int); //信号：从排行榜返回用户主界面

private:
    Ui::rankboard* ui;
    QStandardItemModel* model;
    QPushButton* pbtn[6];
    int cur;
    void reset();
};

#endif // RANKBOARD_H
