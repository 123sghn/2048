#include "forget.h"
#include "ui_forget.h"

forget::forget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::forget),
    succ(false)
{
    ui->setupUi(this);
    ui->gbx2->hide();
    ui->gbx3->hide();
    setFixedSize(1280, 720);

    changeID = -1;
}

forget::~forget()
{
    delete ui;
}

void forget::setNewCode()
{
    auto t = getVerificationCode();
    ui->lblFormula->setText(QString::fromLocal8Bit(t.first.data()));
    codeAnswer = t.second;
    ui->ldtCode->clear();
}

void forget::closeEvent(QCloseEvent*)
{
    int tem = changeID;
    if (succ) {
        reset();
        emit returnLoginSucc(x(), y(), tem, User::getPassword(tem));
    }
    else {
        reset();
        emit returnLogin(x(), y());
    }
}

void forget::on_pBtnChange_clicked() //更新验证码
{
    setNewCode();
}

void forget::on_pBtnRet_clicked() //从忘记密码界面返回主界面（未修改密码）
{
    systemclose = false;
    this->close();
}

void forget::on_pBtnOK_clicked() //修改密码（成功直接返回的注册界面）
{
    if(!ui->gbx1->isHidden()) { //第一步
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

        //判断账号输入是否合法
        //空输入
        else if (ui->ldtID->text().isEmpty()) {
            QMessageBox::critical(this, tr("2048"), tr("请先输入账号!"));
            setNewCode();
        }
        //非整数输入（超出int范围整数输入）
        else if (!isNumber(ui->ldtID->text()).first) {
            QMessageBox::critical(this, tr("2048"), tr("账号输入错误!"));
            setNewCode();
        }
        //整数超限
        else if (isNumber(ui->ldtID->text()).second > 99999999 || isNumber(ui->ldtID->text()).second < 0) {
            QMessageBox::critical(this, tr("2048"), tr("账号输入错误!"));
            setNewCode();
        }
        //账号不存在
        else if (!User::checkID(isNumber(ui->ldtID->text()).second)) {
            QMessageBox::critical(this, tr("2048"), tr("账号不存在!"));
            setNewCode();
        }

        else if (User::getIdentity(isNumber(ui->ldtID->text()).second)) {
            QMessageBox::critical(this, tr("2048"), tr("此账号为管理员账号，如果忘记密码，请联系开发人员重置！"));
            systemclose = false;
            this->close();
        }

        else { //进入第二步
            changeID = isNumber(ui->ldtID->text()).second;
            ui->gbx1->hide();
            ui->gbx2->show();
            ui->lblimg1->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            ui->lblQuestion2->setText(QString::fromLocal8Bit(User::getQuestion(changeID).data()));
            ui->ldtAnswer->setFocus();
        }
    }
    else if (!ui->gbx2->isHidden()) { //第二步
        if (string(ui->ldtAnswer->text().toLocal8Bit()) != User::getAnswer(changeID))
            QMessageBox::critical(this, tr("2048"), tr("密保答案错误"));
        else { //进入第三步
            ui->gbx2->hide();
            ui->gbx3->show();
            ui->lblimg2->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            ui->pBtnOK->setText("重置密码");
            ui->ldtPassword->setFocus();
        }
    }
    else { //第三步
        //判断输入的密码是否合法
        //空输入
        if (ui->ldtPassword->text().isEmpty())
            QMessageBox::critical(this, tr("2048"), tr("密码不能为空！"));
        //长度问题
        else if (string(ui->ldtPassword->text().toLocal8Bit()).length() < 6 ||
                 string(ui->ldtPassword->text().toLocal8Bit()).length() > 16)
            QMessageBox::critical(this, tr("2048"), tr("密码的长度应在6~16为之间！"));
        //新密码和旧密码一致
        else if (string(ui->ldtPassword->text().toLocal8Bit()) == User::getPassword(changeID))
            QMessageBox::critical(this, tr("2048"), tr("新密码不能与旧密码一致！"));

        //判断输入的确认密码是否合法
        //空输入
        else if (ui->ldtCPassword->text().isEmpty())
            QMessageBox::critical(this, tr("2048"), tr("确认密码不能为空！"));
        //匹配问题
        else if (ui->ldtCPassword->text() != ui->ldtPassword->text())
            QMessageBox::critical(this, tr("2048"), tr("两次输入的密码不匹配，请重新输入！"));

        else { //重置密码
            User::setPassword(changeID, string(ui->ldtPassword->text().toLocal8Bit()));
            ui->lblimg3->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            QMessageBox::about(this, tr("2048"), tr("已重置密码！"));
            succ = true;
            systemclose = false;
            this->close();
        }
    }
}

void forget::on_ldtCode_returnPressed()
{
    on_pBtnOK_clicked();
}

void forget::on_ldtAnswer_returnPressed()
{
    on_pBtnOK_clicked();
}

void forget::on_ldtCPassword_returnPressed()
{
    on_pBtnOK_clicked();
}

void forget::reset()
{
    changeID = -1;
    succ = false;
    ui->pBtnOK->setText("下 一 步");

    ui->gbx1->show();
    ui->ldtID->clear();
    ui->ldtCode->clear();
    ui->lblFormula->setText("验证码");
    ui->lblimg1->setStyleSheet("border-image: url(:/steps/images/step1.png)");

    ui->gbx2->hide();
    ui->lblQuestion2->setText("密保问题");
    ui->ldtAnswer->clear();
    ui->lblimg2->setStyleSheet("border-image: url(:/steps/images/step2.png)");

    ui->gbx3->hide();
    ui->ldtPassword->clear();
    ui->ldtCPassword->clear();
    ui->lblimg3->setStyleSheet("border-image: url(:/steps/images/step3.png)");

    ui->ldtID->setFocus();
}
