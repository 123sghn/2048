#include "security.h"
#include "ui_security.h"

security::security(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::security)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->gbx2->hide();
}

security::~security()
{
    delete ui;
}

void security::setAccount(int i)
{
    account = i;
    setNewCode();
    ui->ldtPswd->setFocus();
}

void security::setNewCode()
{
    auto t = getVerificationCode();
    ui->lblFormula->setText(QString::fromLocal8Bit(t.first.data()));
    codeAnswer = t.second;
    ui->ldtCode->clear();
}

void security::closeEvent(QCloseEvent*)
{
    reset();
    emit returnHome(x(), y());
}

void security::on_pBtnChange_clicked() //更新验证码
{
    setNewCode();
}

void security::on_pBtnOK_clicked() //修改密保
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
        else if (ui->ldtPswd->text().isEmpty()) {
            QMessageBox::critical(this, tr("2048"), tr("请输入密码!"));
            setNewCode();
        }
        //账号密码不匹配
        else if (User::getPassword(account) != //真实密码
                 std::string(ui->ldtPswd->text().toLocal8Bit())) {
            QMessageBox::critical(this, tr("2048"), tr("密码错误!"));
            setNewCode();
        }

        else { //进入第二步
            ui->gbx1->hide();
            ui->gbx2->show();
            ui->lblimg1->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            ui->pBtnOK->setText("修改密保");
            ui->ldtQuestion->setFocus();
        }
    }
    else { //第二步
        //判断输入的密保问题是否合法
        //空输入
        if (ui->ldtQuestion->text().isEmpty())
            QMessageBox::critical(this, tr("2048"), tr("密保问题不能为空！"));
        //长度超限
        else if (string(ui->ldtQuestion->text().toLocal8Bit()).length() > 50)
            QMessageBox::critical(this, tr("2048"), tr("密保问题的长度应不超过50个字符！"));

        //判断输入的密保答案是否合法
        //空输入
        else if (ui->ldtAnswer->text().isEmpty())
            QMessageBox::critical(this, tr("2048"), tr("密保答案不能为空！"));
        //长度超限
        else if (string(ui->ldtAnswer->text().toLocal8Bit()).length() > 50)
            QMessageBox::critical(this, tr("2048"), tr("密保答案的长度应不超过50个字符！"));

        else { //修改密保
            User::setQuestion(account, string(ui->ldtQuestion->text().toLocal8Bit()));
            User::setAnswer(account, string(ui->ldtAnswer->text().toLocal8Bit()));
            ui->lblimg2->setStyleSheet("border-image: url(:/steps/images/stepfin.png)");
            QMessageBox::about(this, tr("2048"), tr("已修改密保！"));

            systemclose = false;
            this->close();
        }
    }
}

void security::on_ldtCode_returnPressed()
{
    on_pBtnOK_clicked();
}

void security::on_ldtAnswer_returnPressed()
{
    on_pBtnOK_clicked();
}

void security::on_pBtnRet_clicked() //从修改密保界面返回用户主界面
{
    systemclose = false;
    this->close();
}

void security::reset()
{
    ui->pBtnOK->setText("下 一 步");

    ui->gbx1->show();
    ui->ldtPswd->clear();
    ui->ldtCode->clear();
    ui->lblFormula->setText("验证码");
    ui->lblimg1->setStyleSheet("border-image: url(:/steps/images/step1.png)");

    ui->gbx2->hide();
    ui->ldtQuestion->clear();
    ui->ldtAnswer->clear();
    ui->lblimg2->setStyleSheet("border-image: url(:/steps/images/step2.png)");
}
