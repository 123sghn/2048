#include "rankboard.h"
#include "ui_rankboard.h"

#define ABLE "QPushButton\n{\n	color: rgb(115, 110, 100);\n	background-color: rgb(251, 248, 239);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(219, 210, 200);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}"
#define DISABLE "QPushButton\n{\n	color: rgb(115, 110, 100);\n	background-color: rgb(219, 210, 200);\n	border-radius: 5px;\n}\n"

rankboard::rankboard(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::rankboard),
    model(new QStandardItemModel())
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->tbvRanklist->setModel(model);

    model->setColumnCount(5);
    ui->tbvRanklist->horizontalHeader()->setFont(QFont("song", 13));

    model->setHeaderData(0, Qt::Horizontal, "排名");
    model->setHeaderData(1, Qt::Horizontal, "用户名");
    model->setHeaderData(2, Qt::Horizontal, "最终成绩");
    model->setHeaderData(3, Qt::Horizontal, "游戏时长");
    model->setHeaderData(4, Qt::Horizontal, "游戏时间");

    ui->tbvRanklist->setColumnWidth(0, 100);
    ui->tbvRanklist->setColumnWidth(1, 200);
    ui->tbvRanklist->setColumnWidth(2, 100);
    ui->tbvRanklist->setColumnWidth(3, 100);
    ui->tbvRanklist->setColumnWidth(4, 198);

    ui->tbvRanklist->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tbvRanklist->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tbvRanklist->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tbvRanklist->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tbvRanklist->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);

    pbtn[0] = ui->pBtn3;
    pbtn[1] = ui->pBtn4;
    pbtn[2] = ui->pBtn5;
    pbtn[3] = ui->pBtn6;
    pbtn[4] = ui->pBtn7;
    pbtn[5] = ui->pBtn8;

    cur = -1;
}

rankboard::~rankboard()
{
    delete model;
    delete ui;
}

void rankboard::setEditable(bool b) {
    if (b) ui->tbvRanklist->setSelectionMode(QAbstractItemView::SingleSelection);
    else ui->tbvRanklist->setSelectionMode(QAbstractItemView::NoSelection);
}

void rankboard::update(int mode)
{
    cur = mode;
    for (int i = 0; i < 6; i++) {
        if (mode - 3 == i) {
            pbtn[i]->setEnabled(false);
            pbtn[i]->setStyleSheet(DISABLE);
        }
        else {
            pbtn[i]->setEnabled(true);
            pbtn[i]->setStyleSheet(ABLE);
        }
    }

    pair<int, Game> first, second, third;
    switch (Honor::getSize(mode)) { //显示左边奖牌下的名字
    case 0 :
        ui->lblNo->show();
        ui->lblGoldName->clear();
        ui->lblGoldScore->clear();
        ui->lblSliverName->clear();
        ui->lblSliverScore->clear();
        ui->lblBronzeName->clear();
        ui->lblBronzeScore->clear();
        break;
    case 1 :
        ui->lblNo->hide();
        first = Honor::getRank(mode, 1);
        ui->lblGoldName->setText(QString::fromLocal8Bit(User::getName(first.first).data()));
        ui->lblGoldScore->setText(intToQString(first.second.getScore()));
        ui->lblSliverName->clear();
        ui->lblSliverScore->clear();
        ui->lblBronzeName->clear();
        ui->lblBronzeScore->clear();
        break;
    case 2 :
        ui->lblNo->hide();
        first = Honor::getRank(mode, 1);
        second = Honor::getRank(mode, 2);
        ui->lblGoldName->setText(QString::fromLocal8Bit(User::getName(first.first).data()));
        ui->lblGoldScore->setText(intToQString(first.second.getScore()));
        ui->lblSliverName->setText(QString::fromLocal8Bit(User::getName(second.first).data()));
        ui->lblSliverScore->setText(intToQString(second.second.getScore()));
        ui->lblBronzeName->clear();
        ui->lblBronzeScore->clear();
        break;
    default:
        ui->lblNo->hide();
        first = Honor::getRank(mode, 1);
        second = Honor::getRank(mode, 2);
        third = Honor::getRank(mode, 3);
        ui->lblGoldName->setText(QString::fromLocal8Bit(User::getName(first.first).data()));
        ui->lblGoldScore->setText(intToQString(first.second.getScore()));
        ui->lblSliverName->setText(QString::fromLocal8Bit(User::getName(second.first).data()));
        ui->lblSliverScore->setText(intToQString(second.second.getScore()));
        ui->lblBronzeName->setText(QString::fromLocal8Bit(User::getName(third.first).data()));
        ui->lblBronzeScore->setText(intToQString(third.second.getScore()));
    }

    for (int i = 0; i < min(30, Honor::getSize(mode)); i++) {
        pair<int, Game> tr = Honor::getRank(mode, i + 1);
        model->setItem(i, 0, new QStandardItem(intToQString(i + 1)));
        model->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit(User::getName(tr.first).data())));
        model->setItem(i, 2, new QStandardItem(intToQString(tr.second.getScore())));
        model->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit(tr.second.getCountup().get().data())));
        model->setItem(i, 4, new QStandardItem(QString::fromLocal8Bit(tr.second.getTime().getTime().data())));

        for (int j = 0; j < 5; j++)
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
    }
}

void rankboard::closeEvent(QCloseEvent*)
{
    reset();
    cur = -1;
    ui->tbvRanklist->setSelectionMode(QAbstractItemView::NoSelection);
    emit returnHome(x(), y());
}

void rankboard::on_pBtn3_clicked() //展示3阶排行榜
{
    reset();
    update(3);
}

void rankboard::on_pBtn4_clicked() //展示4阶排行榜
{
    reset();
    update(4);
}

void rankboard::on_pBtn5_clicked() //展示5阶排行榜
{
    reset();
    update(5);
}

void rankboard::on_pBtn6_clicked() //展示6阶排行榜
{
    reset();
    update(6);
}

void rankboard::on_pBtn7_clicked() //展示7阶排行榜
{
    reset();
    update(7);
}

void rankboard::on_pBtn8_clicked() //展示8阶排行榜
{
    reset();
    update(8);
}

void rankboard::on_tbvRanklist_doubleClicked(const QModelIndex& index)
{
    if (ui->tbvRanklist->selectionMode() == QAbstractItemView::NoSelection) return;

    if (QMessageBox::question(this, tr("2048"), tr("是否删除该条排行榜记录"),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认删除
        int t = isNumber(model->item(index.row(), 0)->text()).second;
        Honor::delRank(cur, t);
        reset();
        update(cur);
        QMessageBox::about(this, tr("2048"), tr("已成功删除该记录!"));
    }
}

void rankboard::on_pBtnRet_clicked() //从排行榜返回用户主界面
{
    systemclose = false;
    this->close();
}

void rankboard::reset()
{
    for (int i = 0; i < 6; i++) {
        pbtn[i]->setEnabled(true);
        pbtn[i]->setStyleSheet(ABLE);
    }

    for (int i = model->rowCount() - 1; i >= 0; i--)
        for (int j = 4; j >= 0; j--) {
            delete model->item(i, j);
        }
    model->removeRows(0, model->rowCount());

    ui->lblGoldName->setText("gold name");
    ui->lblGoldScore->setText("gold score");
    ui->lblSliverName->setText("sliver name");
    ui->lblSliverScore->setText("sliver score");
    ui->lblBronzeName->setText("bronze name");
    ui->lblBronzeScore->setText("bronze score");
    ui->lblNo->show();
}
