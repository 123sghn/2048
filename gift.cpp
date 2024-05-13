#include "gift.h"
#include "ui_gift.h"

gift::gift(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::gift)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
}

gift::~gift()
{
    delete ui;
}

void gift::setAccount(int i)
{
    account = i;
}

void gift::closeEvent(QCloseEvent*)
{
    account = -1;
    ui->ldtGift->clear();
    emit returnHome(x(), y());
}

void gift::on_pBtnOK_clicked() //领取礼包（成功后返回）
{
    string t = string(ui->ldtGift->text().toLocal8Bit());
    //没有礼包码
    if (!Gifts::checkID(t)) {
        QMessageBox::critical(this, tr("2048"), tr("该礼包码不存在！"));
        ui->ldtGift->clear();
    }
    //已领取过该礼包
    else if (Gifts::judge(t, account)) {
        QMessageBox::critical(this, tr("2048"), tr("你已领过该礼包，请勿重复领取！"));
        ui->ldtGift->clear();
    }
    //礼包码已失效
    else if (!(Time() < Gifts::getDdl(t))) {
        QMessageBox::critical(this, tr("2048"), tr("该礼包码已失效！"));
        ui->ldtGift->clear();
    }
    //礼包领完了
    else if (!Gifts::able(t)) {
        QMessageBox::critical(this, tr("2048"), tr("该礼包码被领完了！"));
        ui->ldtGift->clear();
    }

    //成功领取
    else {
        Gifts::add(t, account);
        User::setCoins(account, User::getCoins(account) + Gifts::getCoin(t));
        QMessageBox::about(this, tr("2048"), tr("已成功领取该礼包码！"));
        systemclose = false;
        this->close();
    }
}

void gift::on_ldtGift_returnPressed()
{
    on_pBtnOK_clicked();
}

void gift::on_pBtnRet_clicked() //从礼包码界面返回用户主界面
{
    systemclose = false;
    this->close();
}
