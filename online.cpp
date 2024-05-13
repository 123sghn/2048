#include "online.h"
#include "ui_online.h"

online::online(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::online),
    model(new QStandardItemModel())
{
    ui->setupUi(this);
    setFixedSize(780, 650);
    ui->tbvHistory->setModel(model);

    model->setColumnCount(4);
    ui->tbvHistory->horizontalHeader()->setFont(QFont("song", 14));
    model->setHeaderData(0, Qt::Horizontal, "序号");
    model->setHeaderData(1, Qt::Horizontal, "登录时间");
    model->setHeaderData(2, Qt::Horizontal, "登出时间");
    model->setHeaderData(3, Qt::Horizontal, "在线时长");

    ui->tbvHistory->setColumnWidth(0, 100);
    ui->tbvHistory->setColumnWidth(1, 195);
    ui->tbvHistory->setColumnWidth(2, 195);
    ui->tbvHistory->setColumnWidth(3, 190);

    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tbvHistory->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    ui->pBtnReset->hide();
}

online::~online()
{
    delete model;
    delete ui;
}

void online::setAccount(int i)
{
    account = i;
    ui->lblID->setText("ID: " + intToQString(account));
    update();
}

void online::closeEvent(QCloseEvent*)
{
    reset();
}

void online::on_pBtnReset_clicked()
{
    int t = account;
    reset();
    setAccount(t);
}

void online::reset()
{
    ui->lblNo->show();

    for (int i = User::getLog(account) - 1; i >= 0; i--)
        for (int j = 3; j >= 0; j--) {
            delete model->item(i, j);
        }
    model->removeRows(0, model->rowCount());

    ui->lblID->setText("ID: ");

    account = -1;
}

void online::update()
{
    if (!User::getLog(account)) return;
    ui->lblNo->hide();
    for (int i = User::getLog(account) - 1, j = 0; i >= 0; i--, j++) {
        Time st = User::getLoginTime(account, i);
        Time ed = User::getLogoutTime(account, i);
        Duration d = ed - st;

        model->setItem(j, 0, new QStandardItem(intToQString(j + 1)));
        model->setItem(j, 1, new QStandardItem(QString::fromLocal8Bit(st.getTime().data())));
        model->setItem(j, 2, new QStandardItem(QString::fromLocal8Bit(ed.getTime().data())));
        model->setItem(j, 3, new QStandardItem(QString::fromLocal8Bit(d.getLen().data())));

        for (int k = 0; k < 4; k++)
            model->item(j, k)->setTextAlignment(Qt::AlignCenter);
    }
}
