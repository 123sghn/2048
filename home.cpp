#include "home.h"
#include "ui_home.h"

home::home(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->ldtName->hide();

    pbtnGame[0] = ui->pBtnGameS3;
    pbtnGame[1] = ui->pBtnGameS4;
    pbtnGame[2] = ui->pBtnGameS5;
    pbtnGame[3] = ui->pBtnGameS6;
    pbtnGame[4] = ui->pBtnGameS7;
    pbtnGame[5] = ui->pBtnGameS8;

    pbtnLock[0] = ui->pBtnLockS3;
    pbtnLock[1] = ui->pBtnLockS4;
    pbtnLock[2] = ui->pBtnLockS5;
    pbtnLock[3] = ui->pBtnLockS6;
    pbtnLock[4] = ui->pBtnLockS7;
    pbtnLock[5] = ui->pBtnLockS8;

    connect(&gameS3Form, SIGNAL(returnHome(int,int)), this, SLOT(fromGame(int,int)));
    connect(&gameS4Form, SIGNAL(returnHome(int,int)), this, SLOT(fromGame(int,int)));
    connect(&gameS5Form, SIGNAL(returnHome(int,int)), this, SLOT(fromGame(int,int)));
    connect(&gameS6Form, SIGNAL(returnHome(int,int)), this, SLOT(fromGame(int,int)));
    connect(&gameS7Form, SIGNAL(returnHome(int,int)), this, SLOT(fromGame(int,int)));
    connect(&gameS8Form, SIGNAL(returnHome(int,int)), this, SLOT(fromGame(int,int)));

    connect(&giftForm, SIGNAL(returnHome(int,int)), this, SLOT(fromGift(int,int)));
    connect(&historyForm, SIGNAL(returnHome(int,int)), this, SLOT(fromHistory(int,int)));
    connect(&historyForm, SIGNAL(continueGame(int,int,int)), this, SLOT(continueGame(int,int,int)));
    connect(&rankForm, SIGNAL(returnHome(int,int)), this, SLOT(fromRank(int,int)));
    connect(&changepswdForm, SIGNAL(returnHome(int,int)), this, SLOT(fromChangepswd(int,int)));
    connect(&securityForm, SIGNAL(returnHome(int,int)), this, SLOT(fromSecurity(int,int)));
}

home::~home()
{
    delete ui;
}

void home::setAccount(int i)
{
    account = i;
    User::setLoginTime(account);
    update();
}

void home::closeEvent(QCloseEvent*)
{
    User::setLogoutTime(account);
//    writePeople(account);
    reset();
    emit returnLogin(x(), y());
}

void home::on_pBtnName_clicked() //修改用户名
{
    if (ui->ldtName->isHidden()) {
        if (QMessageBox::question(this, tr("2048"), tr("是否花费100金币修改用户名"),
                                  QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认修改
            if (User::getCoins(account) < 100) //金币不够
                QMessageBox::critical(this, tr("2048"), tr("金币不足！\n请通过游戏获取金币 或 输入礼包兑换码兑换金币"));
            else { //可以修改
                ui->lblName->hide();
                ui->ldtName->show();
                ui->pBtnName->setToolTip("取消修改用户名");
            }
        }
    }
    else
        update();
}

void home::on_ldtName_editingFinished() //完成修改用户名
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

    //成功修改用户名，并扣除相应的金币
    else {
        User::setName(account, string(ui->ldtName->text().toLocal8Bit()));
        User::setCoins(account, User::getCoins(account) - 100);
        update();
        QMessageBox::about(this, tr("2048"), tr("已成功更改用户名！"));
    }
}

void home::on_pBtnLockS3_clicked() //解锁3阶单人游戏
{
    unlock(3);
}

void home::on_pBtnLockS4_clicked() //解锁4阶单人游戏
{
    unlock(4);
}

void home::on_pBtnLockS5_clicked() //解锁5阶单人游戏
{
    unlock(5);
}

void home::on_pBtnLockS6_clicked() //解锁6阶单人游戏
{
    unlock(6);
}

void home::on_pBtnLockS7_clicked() //解锁7阶单人游戏
{
    unlock(7);
}

void home::on_pBtnLockS8_clicked() //解锁8阶单人游戏
{
    unlock(8);
}

void home::unlock(int mode) //解锁新模式
{
    if (QMessageBox::question(this, tr("2048"), tr(("是否花费500金币解锁2048的" +
                                                    intToString(mode) + "×" + intToString(mode) + "单人模式").c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认解锁
        if (User::getCoins(account) < 500) //金币不够
            QMessageBox::critical(this, tr("2048"), tr("金币不足！\n请通过游戏获取金币 或 输入礼包兑换码兑换金币"));
        else {
            User::setBest(account, mode, User::getBest(account, mode) == -1 ? 0 : abs(User::getBest(account, mode)));
            User::setCoins(account, User::getCoins(account) - 500);
            update();
            QMessageBox::about(this, tr("2048"), tr(("已成功解锁2048的" + intToString(mode) + "×" + intToString(mode) + "单人模式！").c_str()));
        }
    }
}

void home::on_pBtnGameS3_clicked() //从用户主界面转到3阶单人游戏界面
{
    this->hide();
    update();
    gameS3Form.move(x(), y());
    gameS3Form.setAccount(account);
    gameS3Form.show();
}

void home::on_pBtnGameS4_clicked() //从用户主界面转到4阶单人游戏界面
{
    this->hide();
    update();
    gameS4Form.move(x(), y());
    gameS4Form.setAccount(account);
    gameS4Form.show();
}

void home::on_pBtnGameS5_clicked() //从用户主界面转到5阶单人游戏界面
{
    this->hide();
    update();
    gameS5Form.move(x(), y());
    gameS5Form.setAccount(account);
    gameS5Form.show();
}

void home::on_pBtnGameS6_clicked() //从用户主界面转到6阶单人游戏界面
{
    this->hide();
    update();
    gameS6Form.move(x(), y());
    gameS6Form.setAccount(account);
    gameS6Form.show();
}

void home::on_pBtnGameS7_clicked() //从用户主界面转到7阶单人游戏界面
{
    this->hide();
    update();
    gameS7Form.move(x(), y());
    gameS7Form.setAccount(account);
    gameS7Form.show();
}

void home::on_pBtnGameS8_clicked() //从用户主界面转到8阶单人游戏界面
{
    this->hide();
    update();
    gameS8Form.move(x(), y());
    gameS8Form.setAccount(account);
    gameS8Form.show();
}


void home::fromGame(int _x, int _y) //从游戏界面返回用户主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void home::on_pBtnGift_clicked() //从用户主界面转到礼包码界面
{
    this->hide();
    update();
    giftForm.move(x(), y());
    giftForm.setAccount(account);
    giftForm.show();
}

void home::fromGift(int _x, int _y) //从礼包码界面返回用户主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void home::on_pBtnHistory_clicked() //从用户主界面转到历史记录界面
{
    this->hide();
    update();
    historyForm.move(x(), y());
    historyForm.show();
    historyForm.setAccount(account);
}

void home::fromHistory(int _x, int _y) //从历史记录界面返回用户主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void home::continueGame(int _x, int _y, int r) //继续原来的游戏
{
    Game g = User::getHistory(account, r).second;
    User::delHistory(account, r);

    switch (g.getMode()) {
    case 3:
        gameS3Form.move(_x, _y);
        gameS3Form.show();
        gameS3Form.continueGame(account, g);
        break;
    case 4:
        gameS4Form.move(_x, _y);
        gameS4Form.show();
        gameS4Form.continueGame(account, g);
        break;
    case 5:
        gameS5Form.move(_x, _y);
        gameS5Form.show();
        gameS5Form.continueGame(account, g);
        break;
    case 6:
        gameS6Form.move(_x, _y);
        gameS6Form.show();
        gameS6Form.continueGame(account, g);
        break;
    case 7:
        gameS7Form.move(_x, _y);
        gameS7Form.show();
        gameS7Form.continueGame(account, g);
        break;
    case 8:
        gameS8Form.move(_x, _y);
        gameS8Form.show();
        gameS8Form.continueGame(account, g);
        break;
    }
}

void home::on_pBtnRank_clicked() //从用户主界面转到排行榜
{
    this->hide();
    update();
    rankForm.move(x(), y());
    rankForm.show();
    rankForm.setEditable(false);
    rankForm.update(4);
}

void home::fromRank(int _x, int _y) //从排行榜返回用户主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void home::on_pBtnPassword_clicked() //从用户主界面转到修改密码界面
{
    this->hide();
    update();
    changepswdForm.move(x(), y());
    changepswdForm.setAccount(account);
    changepswdForm.show();
}

void home::fromChangepswd(int _x, int _y) //从修改密码界面返回用户主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void home::on_pBtnSecurity_clicked() //从用户主界面转到修改密保界面
{
    this->hide();
    update();
    securityForm.move(x(), y());
    securityForm.setAccount(account);
    securityForm.show();
}

void home::fromSecurity(int _x, int _y) //从修改密保界面返回用户主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        update();
        this->show();
    }
}

void home::on_pBtnRet_clicked() //从用户主界面返回登录界面
{
    systemclose = false;
    this->close();
}

void home::reset()
{
    ui->ldtName->hide();
    ui->ldtName->clear();
    ui->lblName->show();
    ui->lblName->setText("name");
    ui->pBtnName->setToolTip("修改用户名");
    ui->lblCoins->setText("coins");
    ui->lblCoins->setToolTip("金币数量");
    ui->pBtnLockS3->show();
    ui->pBtnLockS4->show();
    ui->pBtnLockS5->show();
    ui->pBtnLockS6->show();
    ui->pBtnLockS7->show();
    ui->pBtnLockS8->show();
    ui->pBtnGameS3->setEnabled(false);
    ui->pBtnGameS4->setEnabled(false);
    ui->pBtnGameS5->setEnabled(false);
    ui->pBtnGameS6->setEnabled(false);
    ui->pBtnGameS7->setEnabled(false);
    ui->pBtnGameS8->setEnabled(false);
    account = -1;
}

void home::update()
{
    ui->lblName->setText(QString::fromLocal8Bit(User::getName(account).data()));
    ui->lblCoins->setText(intToQString(User::getCoins(account)));
    ui->lblCoins->setToolTip("金币数量：" + longToQString(User::getCoins(account)));
    for (int i = 3; i <= 8; i++) {
        if (User::getBest(account, i) >= 0) {
            pbtnGame[i - 3]->setEnabled(true);
            pbtnLock[i - 3]->hide();
        }
        else {
            pbtnGame[i - 3]->setEnabled(false);
            pbtnLock[i - 3]->show();
        }
    }
    ui->lblName->show();
    ui->ldtName->hide();
    ui->ldtName->clear();
    ui->pBtnName->setToolTip("修改用户名");
}
