#include "systemsetting.h"
#include "ui_systemsetting.h"
#include <QFileInfo>
#include <QFileDialog>

systemsetting::systemsetting(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::systemsetting)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
}

systemsetting::~systemsetting()
{
    delete ui;
}

void systemsetting::setAccount(int i)
{
    account = i;
    update();
    if (!account) {
        ui->gbxDatas->setEnabled(true);
    }
    else {
        ui->gbxDatas->setEnabled(false);
    }
}

void systemsetting::closeEvent(QCloseEvent*)
{
    reset();
    emit returnAdmin(x(), y());
}

void systemsetting::on_pBtnBackup_clicked()
{
    QString to = QFileDialog::getSaveFileName(this, tr("选择备份系统的位置"), ".","*.db");
    if (to.isEmpty()) return;
    if (QFile::copy("2048.db", to))
        QMessageBox::about(this, tr("2048"), tr("已成功备份系统！"));
    else QMessageBox::critical(this, tr("2048"), tr("备份系统发生错误！"));
}

void systemsetting::on_pBtnRecover_clicked()
{
    QString from = QFileDialog::getOpenFileName(this, tr("选择恢复系统的位置"), ".","*.db");
    if (from.isEmpty()) return;

    db.close();
    QSqlDatabase::removeDatabase("2048.db");
    delete sql;

    QFile file("2048.db");
    if (file.exists()) {
        file.remove();
    }

    if (QFile::copy(from, "2048.db")){
        QMessageBox::about(this, tr("2048"), tr("已成功恢复系统！\n重启系统后生效！"));
        exit(0);
    }
    else {
        QMessageBox::critical(this, tr("2048"), tr("恢复系统发生错误！"));
        exit(0);
    }
}

void systemsetting::on_pBtnReset_clicked()
{
    if (QMessageBox::warning(this, tr("2048"), tr("是否重置系统？"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {

        sql->exec("delete from game");
        sql->exec("delete from gift");
        sql->exec("delete from giftrecord");
        sql->exec("delete from login");
        sql->exec("delete from Remem");
        sql->exec("insert into Remem(remID, remPswd) values (0, 0);");
        sql->exec("delete from user where id != 0");

        QMessageBox::about(this, tr("2048"), tr("已成功重置系统！"));
    }
}

void systemsetting::on_pBtnRet_clicked() //从游戏设置界面返回管理员主界面
{
    systemclose = false;
    this->close();
}

void systemsetting::reset()
{
    ui->gbxDatas->setEnabled(true);
}

