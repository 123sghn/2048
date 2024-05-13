#include "login.h"
#include "ui_login.h"

login::login(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->ldtID->setFocus();

    connect(&homeForm, SIGNAL(returnLogin(int,int)), this, SLOT(fromHome(int, int)));
    connect(&adminForm, SIGNAL(returnLogin(int,int)), this, SLOT(fromAdmin(int,int)));

    connect(&logonForm, SIGNAL(returnLogin(int,int)), this, SLOT(fromLogon(int,int)));
    connect(&logonForm, SIGNAL(returnLoginSucc(int,int,int,std::string)), this, SLOT(fromLogonSucc(int,int,int,std::string)));

    connect(&forgetForm, SIGNAL(returnLogin(int,int)), this, SLOT(fromForget(int,int)));
    connect(&forgetForm, SIGNAL(returnLoginSucc(int,int,int,std::string)), this, SLOT(fromForgetSucc(int,int,int,std::string)));
}

login::~login()
{
    delete ui;
}

void login::update()
{
    ui->cbxID->setChecked(Remem::getRemID());
    if (Remem::getRemID())
        ui->ldtID->setText(intToQString(Remem::getID()));
    ui->cbxPswd->setChecked(Remem::getRemPswd());
    if (Remem::getRemPswd())
        ui->ldtPassword->setText(Remem::getPswd());
}

void login::closeEvent(QCloseEvent*)
{
    reset();
    emit returnFront(x(), y());
}

//#define TESTING
void login::on_ldtID_textChanged(const QString&)
{
    ui->ldtPassword->clear();
    //ui->cbxID->setChecked(true);
    ui->cbxPswd->setChecked(false);

    //调试快速登录用
#ifdef TESTING
    if (!isNumber(ui->ldtID->text()).first) return;
    int t = isNumber(ui->ldtID->text()).second;
    if (User::checkID(t))
        ui->ldtPassword->setText(QString::fromLocal8Bit(User::getPassword(t).data()));
#endif
}

void login::on_ldtPassword_returnPressed() //输完密码按enter键登录
{
    on_pBtnLogin_clicked();
}

void login::on_pBtnLogin_clicked() //登录（从登录界面转到用户主界面）
{
    //空输入
    if (ui->ldtID->text().isEmpty() || ui->ldtPassword->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("未输入账号或密码!"));
        ui->ldtPassword->clear();
    }
    //非整数输入
    else if (!isNumber(ui->ldtID->text()).first) {
        QMessageBox::critical(this, tr("2048"), tr("账号输入错误!"));
        ui->ldtPassword->clear();
    }
    //整数超限
    else if (isNumber(ui->ldtID->text()).second > 99999999 || isNumber(ui->ldtID->text()).second < 0) {
        QMessageBox::critical(this, tr("2048"), tr("账号输入错误!"));
        ui->ldtPassword->clear();
    }
    //账号不存在
    else if (!User::checkID(isNumber(ui->ldtID->text()).second)) {
        QMessageBox::critical(this, tr("2048"), tr("账号不存在!"));
        ui->ldtPassword->clear();
    }
    //账号密码不匹配
    else if (User::getPassword(isNumber(ui->ldtID->text()).second) != //真实密码
             std::string(ui->ldtPassword->text().toLocal8Bit())) {
        QMessageBox::critical(this, tr("2048"), tr("账号或密码错误!"));
        ui->ldtPassword->clear();
    }
    //登录成功
    else {
        int tid = isNumber(ui->ldtID->text()).second;
        Remem::setRemID(ui->cbxID->isChecked());
        Remem::setRemPswd(ui->cbxPswd->isChecked());
        if (Remem::getRemID()) Remem::setID(tid);
        if (Remem::getRemPswd()) Remem::setPassword(ui->ldtPassword->text());

//        rem_data.setRem_id(ui->cbxID->isChecked());
//        rem_data.setRem_pswd(ui->cbxPswd->isChecked());
//        if (rem_data.getRem_id())
//            rem_data.setID(tid);

        if (!User::getIdentity(tid)) { //玩家登录
            if (!User::getEnable(tid)) { //未封号
                this->hide();
                homeForm.move(x(), y());
                homeForm.setAccount(tid);
                reset();
                homeForm.show();
            }
            else {
                string t;
                switch(User::getEnable(tid)) {
                case 1 : t = "该账号被判定为存在使用外挂的行为，已封停账号！\n"; break;
                case 2 : t = "该账号被判定为存在不良的游戏行为，已封停账号！\n"; break;
                case 3 : t = "该账号被判定为存在寻求第三方代练的行为，已封停账号！\n"; break;
                case 4 : t = "该账号被判定为存在游戏时间过长的行为，已封停账号！\n"; break;
                case 5 : t = "该账号存在违规行为，已封停账号！\n"; break;
                }
//                if (peoples[tid]->getDisable() == Time(9999,0,0,0,0,0))
//                    t += "该账号将被永久封停。\n";
//                else t += "该账号将于 " + peoples[tid]->getDisable().getTime() + " 解封。\n";
                t += "请规范游戏行为，共同维护良好的游戏环境。如有异议，请联系管理员解决。";
                QMessageBox::critical(this, tr("2048"), tr(t.c_str()));
            }
        }
        else { //管理员登录
            if (!User::getEnable(tid)) { //未封号
                this->hide();
                adminForm.move(x(), y());
                adminForm.setAccount(tid);
                reset();
                adminForm.show();
            }
            else {
                string t;
                switch(User::getEnable(tid)) {
                case 1 : t = "该账号被判定为存在使用外挂的行为，已封停账号！\n"; break;
                case 2 : t = "该账号被判定为存在不良的游戏行为，已封停账号！\n"; break;
                case 3 : t = "该账号被判定为存在游戏时间过长的行为，已封停账号！\n"; break;
                case 4 : t = "该账号存在违规行为，已封停账号！\n"; break;
                }
//                if (peoples[tid]->getDisable() == Time(9999,0,0,0,0,0))
//                    t += "该账号将被永久封停。\n";
//                else t += "该账号将于 " + peoples[tid]->getDisable().getTime() + " 解封。\n";
                t += "请规范游戏行为，共同维护良好的游戏环境。如有异议，请联系开发人员解决。";
                QMessageBox::critical(this, tr("2048"), tr(t.c_str()));
            }
        }
    }
}

void login::fromHome(int _x, int _y) //从用户主界面返回登录界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        update();
        this->move(_x, _y);
        this->show();
    }
}

void login::fromAdmin(int _x, int _y) //从用户主界面返回登录界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        update();
        this->move(_x, _y);
        this->show();
    }
}

void login::on_pBtnLogon_clicked() //从登录界面转到注册界面
{
    this->hide();
    logonForm.setNewCode();
    logonForm.move(x(), y());
    logonForm.show();
}

void login::fromLogon(int _x, int _y) //从注册界面返回登录界面（未注册）
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        this->show();
    }
}

void login::fromLogonSucc(int _x, int _y, int id, std::string pswd) //从注册界面返回登录界面（成功注册）
{
    this->move(_x, _y);
    this->show();
    ui->ldtID->setText(intToQString(id));
    ui->ldtPassword->setText(QString::fromLocal8Bit(pswd.data()));
    ui->cbxID->setChecked(true);
    ui->cbxPswd->setChecked(false);
}

void login::on_pBtnForget_clicked() //从登录界面转到忘记密码界面
{
    this->hide();
    forgetForm.setNewCode();
    forgetForm.move(x(), y());
    forgetForm.show();
}

void login::fromForget(int _x, int _y) //从忘记密码界面返回登录界面（未修改密码）
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        this->show();
    }
}

void login::fromForgetSucc(int _x, int _y, int id, std::string pswd) //从忘记密码界面返回登录界面（成功修改密码）
{
    this->move(_x, _y);
    this->show();
    ui->ldtID->setText(intToQString(id));
    ui->ldtPassword->setText(QString::fromLocal8Bit(pswd.data()));
    ui->cbxID->setChecked(true);
    ui->cbxPswd->setChecked(false);
}

void login::on_pBtnRet_clicked() //从登录界面返回主界面
{
    systemclose = false;
    this->close();
}

void login::on_cbxID_stateChanged(int arg1) //记住账号
{
    if (!arg1) ui->cbxPswd->setChecked(false);
}

void login::on_cbxPswd_stateChanged(int arg1) //记住密码
{
    if (arg1) ui->cbxID->setChecked(true);
}

void login::reset()
{
    ui->ldtID->clear();
    ui->ldtPassword->clear();
    ui->ldtID->setFocus();
    ui->cbxID->setChecked(false);
    ui->cbxPswd->setChecked(false);
}
