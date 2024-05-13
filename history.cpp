#include "history.h"
#include "ui_history.h"

history::history(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::history),
    model(new QStandardItemModel())
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->tbvHistory->setModel(model);

    gbx[0] = ui->gbx3;
    gbx[1] = ui->gbx4;
    gbx[2] = ui->gbx5;
    gbx[3] = ui->gbx6;
    gbx[4] = ui->gbx7;
    gbx[5] = ui->gbx8;
    pbtn.resize(6);

    for (int i = 0; i < 6; i++) {
        gbx[i]->hide();
        pbtn[i].resize(i + 3);
    }

    pbtn[0][0].push_back(ui->pBtn3_0);
    pbtn[0][0].push_back(ui->pBtn3_1);
    pbtn[0][0].push_back(ui->pBtn3_2);
    pbtn[0][1].push_back(ui->pBtn3_3);
    pbtn[0][1].push_back(ui->pBtn3_4);
    pbtn[0][1].push_back(ui->pBtn3_5);
    pbtn[0][2].push_back(ui->pBtn3_6);
    pbtn[0][2].push_back(ui->pBtn3_7);
    pbtn[0][2].push_back(ui->pBtn3_8);

    pbtn[1][0].push_back(ui->pBtn4_0);
    pbtn[1][0].push_back(ui->pBtn4_1);
    pbtn[1][0].push_back(ui->pBtn4_2);
    pbtn[1][0].push_back(ui->pBtn4_3);
    pbtn[1][1].push_back(ui->pBtn4_4);
    pbtn[1][1].push_back(ui->pBtn4_5);
    pbtn[1][1].push_back(ui->pBtn4_6);
    pbtn[1][1].push_back(ui->pBtn4_7);
    pbtn[1][2].push_back(ui->pBtn4_8);
    pbtn[1][2].push_back(ui->pBtn4_9);
    pbtn[1][2].push_back(ui->pBtn4_10);
    pbtn[1][2].push_back(ui->pBtn4_11);
    pbtn[1][3].push_back(ui->pBtn4_12);
    pbtn[1][3].push_back(ui->pBtn4_13);
    pbtn[1][3].push_back(ui->pBtn4_14);
    pbtn[1][3].push_back(ui->pBtn4_15);

    pbtn[2][0].push_back(ui->pBtn5_0);
    pbtn[2][0].push_back(ui->pBtn5_1);
    pbtn[2][0].push_back(ui->pBtn5_2);
    pbtn[2][0].push_back(ui->pBtn5_3);
    pbtn[2][0].push_back(ui->pBtn5_4);
    pbtn[2][1].push_back(ui->pBtn5_5);
    pbtn[2][1].push_back(ui->pBtn5_6);
    pbtn[2][1].push_back(ui->pBtn5_7);
    pbtn[2][1].push_back(ui->pBtn5_8);
    pbtn[2][1].push_back(ui->pBtn5_9);
    pbtn[2][2].push_back(ui->pBtn5_10);
    pbtn[2][2].push_back(ui->pBtn5_11);
    pbtn[2][2].push_back(ui->pBtn5_12);
    pbtn[2][2].push_back(ui->pBtn5_13);
    pbtn[2][2].push_back(ui->pBtn5_14);
    pbtn[2][3].push_back(ui->pBtn5_15);
    pbtn[2][3].push_back(ui->pBtn5_16);
    pbtn[2][3].push_back(ui->pBtn5_17);
    pbtn[2][3].push_back(ui->pBtn5_18);
    pbtn[2][3].push_back(ui->pBtn5_19);
    pbtn[2][4].push_back(ui->pBtn5_20);
    pbtn[2][4].push_back(ui->pBtn5_21);
    pbtn[2][4].push_back(ui->pBtn5_22);
    pbtn[2][4].push_back(ui->pBtn5_23);
    pbtn[2][4].push_back(ui->pBtn5_24);

    pbtn[3][0].push_back(ui->pBtn6_0);
    pbtn[3][0].push_back(ui->pBtn6_1);
    pbtn[3][0].push_back(ui->pBtn6_2);
    pbtn[3][0].push_back(ui->pBtn6_3);
    pbtn[3][0].push_back(ui->pBtn6_4);
    pbtn[3][0].push_back(ui->pBtn6_5);
    pbtn[3][1].push_back(ui->pBtn6_6);
    pbtn[3][1].push_back(ui->pBtn6_7);
    pbtn[3][1].push_back(ui->pBtn6_8);
    pbtn[3][1].push_back(ui->pBtn6_9);
    pbtn[3][1].push_back(ui->pBtn6_10);
    pbtn[3][1].push_back(ui->pBtn6_11);
    pbtn[3][2].push_back(ui->pBtn6_12);
    pbtn[3][2].push_back(ui->pBtn6_13);
    pbtn[3][2].push_back(ui->pBtn6_14);
    pbtn[3][2].push_back(ui->pBtn6_15);
    pbtn[3][2].push_back(ui->pBtn6_16);
    pbtn[3][2].push_back(ui->pBtn6_17);
    pbtn[3][3].push_back(ui->pBtn6_18);
    pbtn[3][3].push_back(ui->pBtn6_19);
    pbtn[3][3].push_back(ui->pBtn6_20);
    pbtn[3][3].push_back(ui->pBtn6_21);
    pbtn[3][3].push_back(ui->pBtn6_22);
    pbtn[3][3].push_back(ui->pBtn6_23);
    pbtn[3][4].push_back(ui->pBtn6_24);
    pbtn[3][4].push_back(ui->pBtn6_25);
    pbtn[3][4].push_back(ui->pBtn6_26);
    pbtn[3][4].push_back(ui->pBtn6_27);
    pbtn[3][4].push_back(ui->pBtn6_28);
    pbtn[3][4].push_back(ui->pBtn6_29);
    pbtn[3][5].push_back(ui->pBtn6_30);
    pbtn[3][5].push_back(ui->pBtn6_31);
    pbtn[3][5].push_back(ui->pBtn6_32);
    pbtn[3][5].push_back(ui->pBtn6_33);
    pbtn[3][5].push_back(ui->pBtn6_34);
    pbtn[3][5].push_back(ui->pBtn6_35);

    pbtn[4][0].push_back(ui->pBtn7_0);
    pbtn[4][0].push_back(ui->pBtn7_1);
    pbtn[4][0].push_back(ui->pBtn7_2);
    pbtn[4][0].push_back(ui->pBtn7_3);
    pbtn[4][0].push_back(ui->pBtn7_4);
    pbtn[4][0].push_back(ui->pBtn7_5);
    pbtn[4][0].push_back(ui->pBtn7_6);
    pbtn[4][1].push_back(ui->pBtn7_7);
    pbtn[4][1].push_back(ui->pBtn7_8);
    pbtn[4][1].push_back(ui->pBtn7_9);
    pbtn[4][1].push_back(ui->pBtn7_10);
    pbtn[4][1].push_back(ui->pBtn7_11);
    pbtn[4][1].push_back(ui->pBtn7_12);
    pbtn[4][1].push_back(ui->pBtn7_13);
    pbtn[4][2].push_back(ui->pBtn7_14);
    pbtn[4][2].push_back(ui->pBtn7_15);
    pbtn[4][2].push_back(ui->pBtn7_16);
    pbtn[4][2].push_back(ui->pBtn7_17);
    pbtn[4][2].push_back(ui->pBtn7_18);
    pbtn[4][2].push_back(ui->pBtn7_19);
    pbtn[4][2].push_back(ui->pBtn7_20);
    pbtn[4][3].push_back(ui->pBtn7_21);
    pbtn[4][3].push_back(ui->pBtn7_22);
    pbtn[4][3].push_back(ui->pBtn7_23);
    pbtn[4][3].push_back(ui->pBtn7_24);
    pbtn[4][3].push_back(ui->pBtn7_25);
    pbtn[4][3].push_back(ui->pBtn7_26);
    pbtn[4][3].push_back(ui->pBtn7_27);
    pbtn[4][4].push_back(ui->pBtn7_28);
    pbtn[4][4].push_back(ui->pBtn7_29);
    pbtn[4][4].push_back(ui->pBtn7_30);
    pbtn[4][4].push_back(ui->pBtn7_31);
    pbtn[4][4].push_back(ui->pBtn7_32);
    pbtn[4][4].push_back(ui->pBtn7_33);
    pbtn[4][4].push_back(ui->pBtn7_34);
    pbtn[4][5].push_back(ui->pBtn7_35);
    pbtn[4][5].push_back(ui->pBtn7_36);
    pbtn[4][5].push_back(ui->pBtn7_37);
    pbtn[4][5].push_back(ui->pBtn7_38);
    pbtn[4][5].push_back(ui->pBtn7_39);
    pbtn[4][5].push_back(ui->pBtn7_40);
    pbtn[4][5].push_back(ui->pBtn7_41);
    pbtn[4][6].push_back(ui->pBtn7_42);
    pbtn[4][6].push_back(ui->pBtn7_43);
    pbtn[4][6].push_back(ui->pBtn7_44);
    pbtn[4][6].push_back(ui->pBtn7_45);
    pbtn[4][6].push_back(ui->pBtn7_46);
    pbtn[4][6].push_back(ui->pBtn7_47);
    pbtn[4][6].push_back(ui->pBtn7_48);

    pbtn[5][0].push_back(ui->pBtn8_0);
    pbtn[5][0].push_back(ui->pBtn8_1);
    pbtn[5][0].push_back(ui->pBtn8_2);
    pbtn[5][0].push_back(ui->pBtn8_3);
    pbtn[5][0].push_back(ui->pBtn8_4);
    pbtn[5][0].push_back(ui->pBtn8_5);
    pbtn[5][0].push_back(ui->pBtn8_6);
    pbtn[5][0].push_back(ui->pBtn8_7);
    pbtn[5][1].push_back(ui->pBtn8_8);
    pbtn[5][1].push_back(ui->pBtn8_9);
    pbtn[5][1].push_back(ui->pBtn8_10);
    pbtn[5][1].push_back(ui->pBtn8_11);
    pbtn[5][1].push_back(ui->pBtn8_12);
    pbtn[5][1].push_back(ui->pBtn8_13);
    pbtn[5][1].push_back(ui->pBtn8_14);
    pbtn[5][1].push_back(ui->pBtn8_15);
    pbtn[5][2].push_back(ui->pBtn8_16);
    pbtn[5][2].push_back(ui->pBtn8_17);
    pbtn[5][2].push_back(ui->pBtn8_18);
    pbtn[5][2].push_back(ui->pBtn8_19);
    pbtn[5][2].push_back(ui->pBtn8_20);
    pbtn[5][2].push_back(ui->pBtn8_21);
    pbtn[5][2].push_back(ui->pBtn8_22);
    pbtn[5][2].push_back(ui->pBtn8_23);
    pbtn[5][3].push_back(ui->pBtn8_24);
    pbtn[5][3].push_back(ui->pBtn8_25);
    pbtn[5][3].push_back(ui->pBtn8_26);
    pbtn[5][3].push_back(ui->pBtn8_27);
    pbtn[5][3].push_back(ui->pBtn8_28);
    pbtn[5][3].push_back(ui->pBtn8_29);
    pbtn[5][3].push_back(ui->pBtn8_30);
    pbtn[5][3].push_back(ui->pBtn8_31);
    pbtn[5][4].push_back(ui->pBtn8_32);
    pbtn[5][4].push_back(ui->pBtn8_33);
    pbtn[5][4].push_back(ui->pBtn8_34);
    pbtn[5][4].push_back(ui->pBtn8_35);
    pbtn[5][4].push_back(ui->pBtn8_36);
    pbtn[5][4].push_back(ui->pBtn8_37);
    pbtn[5][4].push_back(ui->pBtn8_38);
    pbtn[5][4].push_back(ui->pBtn8_39);
    pbtn[5][5].push_back(ui->pBtn8_40);
    pbtn[5][5].push_back(ui->pBtn8_41);
    pbtn[5][5].push_back(ui->pBtn8_42);
    pbtn[5][5].push_back(ui->pBtn8_43);
    pbtn[5][5].push_back(ui->pBtn8_44);
    pbtn[5][5].push_back(ui->pBtn8_45);
    pbtn[5][5].push_back(ui->pBtn8_46);
    pbtn[5][5].push_back(ui->pBtn8_47);
    pbtn[5][6].push_back(ui->pBtn8_48);
    pbtn[5][6].push_back(ui->pBtn8_49);
    pbtn[5][6].push_back(ui->pBtn8_50);
    pbtn[5][6].push_back(ui->pBtn8_51);
    pbtn[5][6].push_back(ui->pBtn8_52);
    pbtn[5][6].push_back(ui->pBtn8_53);
    pbtn[5][6].push_back(ui->pBtn8_54);
    pbtn[5][6].push_back(ui->pBtn8_55);
    pbtn[5][7].push_back(ui->pBtn8_56);
    pbtn[5][7].push_back(ui->pBtn8_57);
    pbtn[5][7].push_back(ui->pBtn8_58);
    pbtn[5][7].push_back(ui->pBtn8_59);
    pbtn[5][7].push_back(ui->pBtn8_60);
    pbtn[5][7].push_back(ui->pBtn8_61);
    pbtn[5][7].push_back(ui->pBtn8_62);
    pbtn[5][7].push_back(ui->pBtn8_63);

    model->setColumnCount(7);
    ui->tbvHistory->horizontalHeader()->setFont(QFont("song", 13));

    model->setHeaderData(0, Qt::Horizontal, "序号");
    model->setHeaderData(1, Qt::Horizontal, "用户名");
    model->setHeaderData(2, Qt::Horizontal, "游戏模式");
    model->setHeaderData(3, Qt::Horizontal, "总步数");
    model->setHeaderData(4, Qt::Horizontal, "最终成绩");
    model->setHeaderData(5, Qt::Horizontal, "游戏时长");
    model->setHeaderData(6, Qt::Horizontal, "游戏时间");

    ui->tbvHistory->setColumnWidth(0, 60);
    ui->tbvHistory->setColumnWidth(1, 80);
    ui->tbvHistory->setColumnWidth(2, 60);
    ui->tbvHistory->setColumnWidth(3, 100);
    ui->tbvHistory->setColumnWidth(4, 100);
    ui->tbvHistory->setColumnWidth(5, 100);
    ui->tbvHistory->setColumnWidth(6, 198);

    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);

    ui->pBtnContinue->hide();
    r = -1;
    conti = false;
}

history::~history()
{
    delete model;
    delete ui;
}

void history::setAccount(int i)
{
    account = i;
    update();
}

void history::closeEvent(QCloseEvent*)
{
    if (conti) {
        int tr = r;
        reset();
        emit continueGame(x(), y(), tr);
    }
    else {
        reset();
        emit returnHome(x(), y());
    }
}

void history::on_tbvHistory_clicked(const QModelIndex& index) //查看最终棋盘
{
    r = User::getStored(account) - index.row() - 1;
    Game tgame = User::getHistory(account, r).second;
    if (Checkerboard(tgame.last).judge() && !User::getIdentity(account))
        ui->pBtnContinue->show();
    else ui->pBtnContinue->hide();

    int mode = tgame.getMode();
    for (int i = 0; i < 6; i++)
        if (mode - 3 == i) gbx[i]->show();
        else gbx[i]->hide();
    ui->gbxText->hide();

    for (int i = 0; i < mode; i++)
        for (int j = 0; j < mode; j++) {
            ll t = tgame.last[i][j];
            pbtn[mode - 3][i][j]->setText(!t ? "" : numToQString(t));
            //pbtn[mode - 3][i][j]->setFont(QFont("NumberOnly", sizeStyle[mode - 3][t > 2147483648 ? 2 : (t > 131072 ? 131072 : t)]));
            if (t > 2147483648) pbtn[mode - 3][i][j]->setFont(QFont("NumberOnly", sizeStyle[mode - 3][2]));
            else if (t >= 131072) pbtn[mode - 3][i][j]->setFont(QFont("NumberOnly", sizeStyle[mode - 3][65536] - 1));
            else pbtn[mode - 3][i][j]->setFont(QFont("NumberOnly", sizeStyle[mode - 3][t]));
            pbtn[mode - 3][i][j]->setStyleSheet(QString::fromLocal8Bit(colorStyle[t > 4294967296 ? -1 : t].data()));
        }
}

void history::on_tbvHistory_doubleClicked(const QModelIndex& index) //删除记录
{
    if (QMessageBox::question(this, tr("2048"), tr("是否删除该条游戏记录"),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认删除
        r = User::getStored(account) - index.row() - 1;

        for (int j = 5; j >= 0; j--)
            delete model->item(index.row(), j);
        model->removeRow(index.row());
        User::delHistory(account, r);
        reset();
        update();
        QMessageBox::about(this, tr("2048"), tr("已成功删除该记录!"));
    }
}

void history::on_pBtnContinue_clicked() //继续游戏
{
    if (User::getBest(account, User::getHistory(account, r).second.getMode()) < 0) {
        QMessageBox::critical(this, tr("2048"), tr("该模式尚未解锁，请先前往主界面解锁模式!"));
        return;
    }
    conti = true;
    this->close();
}

void history::on_pBtnRet_clicked()
{
    systemclose = false;
    this->close();
}

void history::reset()
{
    for (int i = User::getStored(account) - 1; i >= 0; i--)
        for (int j = 6; j >= 0; j--) {
            delete model->item(i, j);
        }
    model->removeRows(0, model->rowCount());

    ui->lblNo->show();
    ui->gbxText->show();
    ui->pBtnContinue->hide();

    for (int k = 0; k < 6; k++) {
        gbx[k]->hide();
        for (int i = 0; i < k + 3; i++)
            for (int j = 0; j < k + 3; j++) {
                pbtn[k][i][j]->setText("");
                pbtn[k][i][j]->setFont(QFont("NumberOnly", sizeStyle[k][0]));
                pbtn[k][i][j]->setStyleSheet(QString::fromLocal8Bit(colorStyle[0].data()));
            }
    }

    ui->pBtnContinue->hide();
    r = -1;
    conti = false;
}

void history::update()
{
    if (!User::getStored(account)) return;

    ui->lblNo->hide();
    for (int i = User::getStored(account) - 1, j = 0; i >= 0; i--, j++) {
        pair<int, Game> t = User::getHistory(account, i);
        Game& tgame = t.second;

        model->setItem(j, 0, new QStandardItem(intToQString(j + 1)));
        model->setItem(j, 1, new QStandardItem(intToQString(t.first)));
        switch (tgame.getMode()) {
            case 3 : model->setItem(j, 2, new QStandardItem("3×3")); break;
            case 4 : model->setItem(j, 2, new QStandardItem("4×4")); break;
            case 5 : model->setItem(j, 2, new QStandardItem("5×5")); break;
            case 6 : model->setItem(j, 2, new QStandardItem("6×6")); break;
            case 7 : model->setItem(j, 2, new QStandardItem("7×7")); break;
            case 8 : model->setItem(j, 2, new QStandardItem("8×8")); break;
        }
        model->setItem(j, 3, new QStandardItem(intToQString((ll)tgame.getAttempts())));
        model->setItem(j, 4, new QStandardItem(intToQString(tgame.getScore())));
        model->setItem(j, 5, new QStandardItem(QString::fromLocal8Bit(tgame.getCountup().get().data())));
        model->setItem(j, 6, new QStandardItem(QString::fromLocal8Bit(tgame.getTime().getTime().data())));

        for (int k = 0; k <= 6; k++)
            model->item(j, k)->setTextAlignment(Qt::AlignCenter);
    }
}
