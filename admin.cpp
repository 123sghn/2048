#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->ldtName->hide();

    connect(&manageForm, SIGNAL(returnAdmin(int,int)), this, SLOT(fromManage(int,int)));
    connect(&historyForm, SIGNAL(returnHome(int,int)), this, SLOT(fromHistory(int,int)));
    connect(&systemForm, SIGNAL(returnAdmin(int,int)), this, SLOT(fromSystem(int,int)));
    connect(&giftsettingForm, SIGNAL(returnAdmin(int,int)), this, SLOT(fromGiftsetting(int,int)));
    connect(&rankForm, SIGNAL(returnHome(int,int)), this, SLOT(fromRank(int,int)));
    connect(&changepswdForm, SIGNAL(returnHome(int,int)), this, SLOT(fromChangepswd(int,int)));
}

admin::~admin()
{
    delete ui;
}

void admin::setAccount(int i)
{
    account = i;
    update();
}

void admin::closeEvent(QCloseEvent*)
{
    reset();
    emit returnLogin(x(), y());
}

void admin::on_pBtnName_clicked() //修改用户名
{
    if (ui->ldtName->isHidden()) {
        ui->lblName->hide();
        ui->ldtName->show();
        ui->pBtnName->setToolTip("取消修改用户名");
    }
    else
        update();
}

void admin::on_ldtName_editingFinished() //完成修改用户名
{
    if (ui->ldtName->isHidden()) return;

    //判断输入的用户名是否合法
    //空输入
    if (ui->ldtName->text().isEmpty()) {
        update();
        QMessageBox::critical(this, tr("2048"), tr("用户名不能为空！"));
    }
    //长度超限
    else if (string(ui->ldtName->text().toLocal8Bit()).length() > 16) {
        update();
        QMessageBox::critical(this, tr("2048"), tr("用户名的长度应不超过16个字符！"));
    }

    //成功修改用户名
    else {
        User::setName(account, string(ui->ldtName->text().toLocal8Bit()));
        update();
        QMessageBox::about(this, tr("2048"), tr("已成功更改用户名！"));
    }
}

void admin::on_pBtnRet_clicked() //从管理员主界面返回登录界面
{
    systemclose = false;
    this->close();
}

void admin::on_pBtnPlayer_clicked() //从管理员主界面转到管理用户界面
{
    this->hide();
    update();
    manageForm.move(x(), y());
    manageForm.show();
    manageForm.setAccount(account);
}

void admin::fromManage(int _x, int _y) //从管理用户界面返回管理员主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void admin::on_pBtnHistory_clicked() //从管理员主界面转到历史记录界面
{
    this->hide();
    update();
    historyForm.move(x(), y());
    historyForm.show();
    historyForm.setAccount(account);
}

void admin::fromHistory(int _x, int _y) //从历史记录界面返回用户管理员主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void admin::on_pBtnSystem_clicked() //从管理员主界面转到系统设置界面
{
    this->hide();
    update();
    systemForm.move(x(), y());
    systemForm.setAccount(account);
    systemForm.show();
}

void admin::fromSystem(int _x, int _y) //从系统设置界面返回管理员主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void admin::on_pBtnGift_clicked() //从管理员主界面转到礼包兑换码设置界面
{
    this->hide();
    update();
    giftsettingForm.move(x(), y());
    giftsettingForm.show();
    giftsettingForm.update();
}

void admin::fromGiftsetting(int _x, int _y) //从礼包兑换码设置界面返回管理员主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void admin::on_pBtnRank_clicked() //从管理员主界面转到排行榜
{
    this->hide();
    update();
    rankForm.move(x(), y());
    rankForm.show();
    rankForm.setEditable(true);
    rankForm.update(4);
}

void admin::fromRank(int _x, int _y) //从排行榜返回管理员主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void admin::on_pBtnPassword_clicked() //从管理员主界面转到修改密码界面
{
    this->hide();
    update();
    changepswdForm.move(x(), y());
    changepswdForm.setAccount(account);
    changepswdForm.show();
}

void admin::fromChangepswd(int _x, int _y) //从修改密码界面返回管理员主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void admin::reset()
{
    ui->ldtName->hide();
    ui->ldtName->clear();
    ui->lblName->show();
    ui->lblName->setText("name");
    ui->pBtnName->setToolTip("修改用户名");
    account = -1;
}

void admin::update()
{
    ui->lblName->setText(QString::fromLocal8Bit(User::getName(account).data()));
    ui->lblName->show();
    ui->ldtName->hide();
    ui->ldtName->clear();
    ui->pBtnName->setToolTip("修改用户名");
}

