#include "changepswd.h"
#include "ui_changepswd.h"

changepswd::changepswd(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::changepswd)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->gbx2->hide();
}

changepswd::~changepswd()
{
    delete ui;
}

void changepswd::setAccount(int i)
{
    account = i;
    setNewCode();
    ui->ldtOld->setFocus();
}

void changepswd::setNewCode()
{
    auto t = getVerificationCode();
    ui->lblFormula->setText(QString::fromLocal8Bit(t.first.data()));
    codeAnswer = t.second;
    ui->ldtCode->clear();
}

void changepswd::closeEvent(QCloseEvent*)
{
    reset();
    emit returnHome(x(), y());
}

void changepswd::on_pBtnChange_clicked() //更新验证码
{
    setNewCode();
}

void changepswd::on_pBtnOK_clicked() //修改密码
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

        //判断输入的密码是否合法
        //空输入
        else if (ui->ldtOld->text().isEmpty()) {
            QMessageBox::critical(this, tr("2048"), tr("请输入密码!"));
            setNewCode();
        }
        //账号密码不匹配
        else if (User::getPassword(account) != //真实密码
                 std::string(ui->ldtOld->text().toLocal8Bit())) {
            QMessageBox::critical(this, tr("2048"), tr("密码错误!"));
            setNewCode();
        }

        else { //进入第二步
            ui->gbx1->hide();
            ui->gbx2->show();
            ui->lblimg1->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            ui->pBtnOK->setText("修改密码");
            ui->ldtPassword->setFocus();
        }
    }
    else { //第二步
        //判断输入的密码是否合法
        //空输入
        if (ui->ldtPassword->text().isEmpty())
            QMessageBox::critical(this, tr("2048"), tr("密码不能为空！"));
        //长度问题
        else if (string(ui->ldtPassword->text().toLocal8Bit()).length() < 6 ||
                 string(ui->ldtPassword->text().toLocal8Bit()).length() > 16)
            QMessageBox::critical(this, tr("2048"), tr("密码的长度应在6~16为之间！"));
        //新密码和旧密码一致
        else if (string(ui->ldtPassword->text().toLocal8Bit()) == User::getPassword(account))
            QMessageBox::critical(this, tr("2048"), tr("新密码不能与旧密码一致！"));

        //判断输入的确认密码是否合法
        //空输入
        else if (ui->ldtCPassword->text().isEmpty())
            QMessageBox::critical(this, tr("2048"), tr("确认密码不能为空！"));
        //匹配问题
        else if (ui->ldtCPassword->text() != ui->ldtPassword->text())
            QMessageBox::critical(this, tr("2048"), tr("两次输入的密码不匹配，请重新输入！"));

        else { //修改密码
            User::setPassword(account, string(ui->ldtPassword->text().toLocal8Bit()));
            ui->lblimg2->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            QMessageBox::about(this, tr("2048"), tr("已修改密码！"));

            systemclose = false;
            this->close();
        }
    }
}

void changepswd::on_ldtCode_returnPressed()
{
    on_pBtnOK_clicked();
}

void changepswd::on_ldtCPassword_returnPressed()
{
    on_pBtnOK_clicked();
}

void changepswd::on_pBtnRet_clicked() //从修改密码界面返回用户/管理员主界面
{
    systemclose = false;
    this->close();
}

void changepswd::reset()
{
    ui->pBtnOK->setText("下 一 步");

    ui->gbx1->show();
    ui->ldtOld->clear();
    ui->ldtCode->clear();
    ui->lblFormula->setText("验证码");
    ui->lblimg1->setStyleSheet("border-image: url(:/steps/images/step1.png)");

    ui->gbx2->hide();
    ui->ldtPassword->clear();
    ui->ldtCPassword->clear();
    ui->lblimg2->setStyleSheet("border-image: url(:/steps/images/step2.png)");
}
