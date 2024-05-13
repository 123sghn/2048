#include "logon.h"
#include "ui_logon.h"

logon::logon(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::logon),
    succ(false)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
}

logon::~logon()
{
    delete ui;
}

void logon::setNewCode() //重置验证码
{
    auto t = getVerificationCode();
    ui->lblFormula->setText(QString::fromLocal8Bit(t.first.data()));
    codeAnswer = t.second;
    ui->ldtCode->clear();
}

void logon::closeEvent(QCloseEvent*)
{
    if (succ) {
        //返回登录界面（并清空当前页面所有信息），并自动填写账号密码
        int tint = isNumber(ui->ldtID->text()).second;
        string tpassword = string(ui->ldtPassword->text().toLocal8Bit());
        reset();
        emit returnLoginSucc(this->x(), this->y(), tint, tpassword);
    }
    else {
        reset();
        emit returnLogin(x(), y());
    }
}

void logon::on_pBtnChange_clicked() //更新验证码
{
    setNewCode();
}

void logon::on_pBtnOK_clicked() //开始注册
{
    //判断输入的验证码是否合法
    //空输入
    if (ui->ldtCode->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("验证码不能为空！"));
        setNewCode();
    }
    //验证码不正确
    else if (!isNumber(ui->ldtCode->text()).first || isNumber(ui->ldtCode->text()).second != codeAnswer) {
        QMessageBox::critical(this, tr("2048"), tr("验证码不正确！"));
        setNewCode();
    }

    //判断输入的账户是否合法
    //空输入
    else if (ui->ldtID->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("账号不能为空！"));
        setNewCode();
    }
    //非整数输入（超出int范围整数输入）
    else if (!isNumber(ui->ldtID->text()).first) {
        QMessageBox::critical(this, tr("2048"), tr("账号应为8位及以内的正整数！"));
        setNewCode();
    }
    //整数超限
    else if (isNumber(ui->ldtID->text()).second > 99999999 || isNumber(ui->ldtID->text()).second <= 0) {
        QMessageBox::critical(this, tr("2048"), tr("账号应为8位及以内的正整数！"));
        setNewCode();
    }
    //ID重复
    else if (User::checkID(isNumber(ui->ldtID->text()).second)) {
        QMessageBox::critical(this, tr("2048"), tr("您输入的账号已存在，请重新输入！"));
        setNewCode();
    }

    //判断输入的用户名是否合法
    //空输入
    else if (ui->ldtName->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("用户名不能为空！"));
        setNewCode();
    }
    //长度超限
    else if (string(ui->ldtName->text().toLocal8Bit()).length() > 16) {
        QMessageBox::critical(this, tr("2048"), tr("用户名的长度应不超过16个字符！"));
        setNewCode();
    }

    //判断输入的密码是否合法
    //空输入
    else if (ui->ldtPassword->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("密码不能为空！"));
        setNewCode();
    }
    //长度问题
    else if (string(ui->ldtPassword->text().toLocal8Bit()).length() < 6 ||
             string(ui->ldtPassword->text().toLocal8Bit()).length() > 16) {
        QMessageBox::critical(this, tr("2048"), tr("密码的长度应在6~16为之间！"));
        setNewCode();
    }

    //判断输入的确认密码是否合法
    //空输入
    else if (ui->ldtCPassword->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("确认密码不能为空！"));
        setNewCode();
    }
    //匹配问题
    else if (ui->ldtCPassword->text() != ui->ldtPassword->text()) {
        QMessageBox::critical(this, tr("2048"), tr("两次输入的密码不匹配，请重新输入！"));
        setNewCode();
    }

    //判断输入的密保问题是否合法
    //空输入
    else if (ui->ldtQuestion->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("密保问题不能为空！"));
        setNewCode();
    }
    //长度超限
    else if (string(ui->ldtQuestion->text().toLocal8Bit()).length() > 50) {
        QMessageBox::critical(this, tr("2048"), tr("密保问题的长度应不超过50个字符！"));
        setNewCode();
    }

    //判断输入的密保答案是否合法
    //空输入
    else if (ui->ldtAnswer->text().isEmpty()) {
        QMessageBox::critical(this, tr("2048"), tr("密保答案不能为空！"));
        setNewCode();
    }
    //长度超限
    else if (string(ui->ldtQuestion->text().toLocal8Bit()).length() > 50) {
        QMessageBox::critical(this, tr("2048"), tr("密保答案的长度应不超过50个字符！"));
        setNewCode();
    }

    else //注册成功
    {
        QString tname = ui->ldtName->text();
        QString tpassword = ui->ldtPassword->text();
        QString tquestion = ui->ldtQuestion->text();
        QString tanswer = ui->ldtAnswer->text();
        int tint = isNumber(ui->ldtID->text()).second;

        if (tquestion == ADMIN_REGISTER && tanswer == ADMIN_REGISTER) {
            sql->exec(QString("insert into user(id, name, password, identity) values(%1, '%2', '%3', 1)").arg(tint).arg(tname).arg(tpassword));
            QMessageBox::about(this, tr("2048"), tr("已成功注册管理员账号！"));
        }
        else {
            sql->exec(QString("insert into user(id, name, password, question, answer) values(%1, '%2', '%3', '%4', '%5')").arg(tint).arg(tname).arg(tpassword).arg(tquestion).arg(tanswer));
            QMessageBox::about(this, tr("2048"), tr("已成功注册账号！"));
        }

        succ = true;
        this->close();
    }

}

void logon::on_ldtAnswer_returnPressed()
{
    on_pBtnOK_clicked();
}

void logon::on_pBtnRet_clicked() //从注册界面返回登录界面（未注册）
{
    systemclose = false;
    this->close();
}

void logon::reset()
{
    succ = false;
    ui->ldtID->clear();
    ui->ldtName->clear();
    ui->ldtPassword->clear();
    ui->ldtCPassword->clear();
    ui->ldtCode->clear();
    ui->lblFormula->setText("验证码");
    ui->ldtQuestion->clear();
    ui->ldtAnswer->clear();
}
