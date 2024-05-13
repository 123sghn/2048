#include "gameS4.h"
#include "ui_gameS4.h"

gameS4::gameS4(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::gameS4),
    N(4), //确定棋盘阶数
    cb(4) //建立棋盘
{
    ui->setupUi(this);
    setFixedSize(1280, 720);

    pbtn[0][0] = ui->pBtn0;
    pbtn[0][1] = ui->pBtn1;
    pbtn[0][2] = ui->pBtn2;
    pbtn[0][3] = ui->pBtn3;
    pbtn[1][0] = ui->pBtn4;
    pbtn[1][1] = ui->pBtn5;
    pbtn[1][2] = ui->pBtn6;
    pbtn[1][3] = ui->pBtn7;
    pbtn[2][0] = ui->pBtn8;
    pbtn[2][1] = ui->pBtn9;
    pbtn[2][2] = ui->pBtn10;
    pbtn[2][3] = ui->pBtn11;
    pbtn[3][0] = ui->pBtn12;
    pbtn[3][1] = ui->pBtn13;
    pbtn[3][2] = ui->pBtn14;
    pbtn[3][3] = ui->pBtn15;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            connect(pbtn[i][j], SIGNAL(clicked()), this, SLOT(hammer()));

    connect(&tt, &TimeThread::addTime, this, &gameS4::updateTime);

    reset();
}

gameS4::~gameS4()
{
    delete ui;
}

void gameS4::setAccount(int i) //初始化界面
{
    account = i;
    reset();
    update();
}

void gameS4::continueGame(int i, Game g) //继续之前的游戏
{
    account = i;
    reset();
    lstscore = g.getScore();
    attempts = g.getAttempts();
    time = g.getCountup();
    score = g.getScore();
    cb = g.last;
    gaming = true;
    update();
    tt.start();
    ui->pBtnPause->setEnabled(true);
    ui->pBtnEnd->setEnabled(true);
}

void gameS4::keyPressEvent(QKeyEvent* e)
{
    if (dead) return;
    if (ui->gbxCheckerboard->isEnabled()) return;
    if (attempts && !gaming) return; //游戏暂停，阻止操作

    //记录下每步操作
    step.push_back(make_pair(cb.getBoard(), score));

    ll t = -1;
    switch(e->key()) {
    case Qt::Key_A :
    case Qt::Key_Left : t = cb.left(); break;
    case Qt::Key_D :
    case Qt::Key_Right : t = cb.right(); break;
    case Qt::Key_W :
    case Qt::Key_Up : t = cb.up(); break;
    case Qt::Key_S :
    case Qt::Key_Down : t = cb.down(); break;
    default : step.pop_back(); return; //无效按键操作，把存下的棋盘删了
    }
    if (t != -1) {
        attempts++;
        score += t;
    }
    else {
        step.pop_back();
        return;
    }

    if (step.size() > MAX_STEP)
        step.pop_front();

    if (!gaming) { //第一次开始游戏
        gaming = true;
        tt.start();
        ui->pBtnPause->setEnabled(true);
        ui->pBtnEnd->setEnabled(true);
    }

    update(); //先更新一下棋盘
    if (!cb.judge()) { //判断是否死亡，并询问是否需要复活
        tt.terminate();
        if (reviveNum && QMessageBox::question(this, tr("2048"), tr(("是否花费500金币删除所有最小数字\n\n一局内最多使用1次（" + intToString(2 - reviveNum) + "/1）").c_str()),
                                               QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认复活
            if (User::getCoins(account) < 500) { //金币不够
                QMessageBox::critical(this, tr("2048"), tr("金币不足！\n请通过游戏获取金币 或 输入礼包兑换码兑换金币"));
                dead = true;
                gaming = false;
            }
            else { //复活并继续游戏
                tt.start();
                cb.delMin();
                attempts++;
                reviveNum--;
                User::setCoins(account, User::getCoins(account) - 500);
            }
        }
        else {
            dead = true;
            gaming = false;
        }
        update(); //第二次更新棋盘（复活 或 死亡）
    }

    if (dead) die();
}

void gameS4::closeEvent(QCloseEvent* event)
{
    if (!attempts || dead) {
        event->accept();
    }
    else {
        tt.terminate();
        if (QMessageBox::warning(this, tr("2048"), tr("是否退出游戏\n（退出游戏不会保存游戏的任何信息）"),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认退出
            event->accept();
        }
        else {
            event->ignore();
            systemclose = true;
            tt.start();
            return;
        }
    }

    reset();
    account = -1;
    emit returnHome(x(), y());
}

void gameS4::on_pBtnRetry_clicked() //重新开始
{
    if (!attempts || dead) {
        reset();
        update();
    }
    else {
        tt.terminate();
        if (QMessageBox::warning(this, tr("2048"), tr("是否重新开始游戏\n（重新开始游戏不会保存游戏的任何信息）"),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认重新开始
            reset();
            update();
        }
        else tt.start();
    }
}

void gameS4::on_pBtnRetry2_clicked() //重新开始（游戏失败后）
{
    reset();
    update();
}

void gameS4::on_pBtnPause_clicked() //暂停
{
    if (gaming) { //正在游戏中，暂停
        gaming = false;
        tt.terminate();
        ui->pBtnPause->setStyleSheet("QPushButton\n{\n	border-image: url(:/interface/images/start.png);\n	background-color: rgb(251, 248, 239);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(219, 210, 200);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}");
    }
    else { //恢复游戏
        gaming = true;
        tt.start();
        ui->pBtnPause->setStyleSheet("QPushButton\n{\n	border-image: url(:/interface/images/pause.png);\n	background-color: rgb(251, 248, 239);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(219, 210, 200);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}");
    }
    update();
}

void gameS4::on_pBtnEnd_clicked() //结束游戏
{
    tt.terminate();
    if (QMessageBox::warning(this, tr("2048"), tr("是否结束本局游戏"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认重新开始
        dead = true;
        gaming = false;
        tt.terminate();
        die();
    }
    else tt.start();
}

void gameS4::on_pBtnLast_clicked() //退回上一步
{
    tt.terminate();
    if (QMessageBox::question(this, tr("2048"), tr(("是否花费300金币退回上一步\n\n一局内最多使用3次（" + intToString(4 - lastNum) + "/3）").c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认退回上一步
        if (User::getCoins(account) < 300) //金币不够
            QMessageBox::critical(this, tr("2048"), tr("金币不足！\n请通过游戏获取金币 或 输入礼包兑换码兑换金币"));
        else {
            User::setCoins(account, User::getCoins(account) - 300);
            cb.setBoard(step.back().first);
            score = step.back().second;
            step.pop_back();
            attempts++;
            lastNum--;
            update();
        }
    }
    tt.start();
}

void gameS4::on_pBtnHammer_clicked() //敲除一个方块
{
    if (ui->gbxCheckerboard->isEnabled()) {
        update();
        return;
    }

    tt.terminate();
    if (QMessageBox::question(this, tr("2048"), tr(("是否花费300金币敲除一个方块\n\n一局内最多使用3次（" + intToString(4 - hammerNum) + "/3）").c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认退回上一步
        if (User::getCoins(account) < 300) //金币不够
            QMessageBox::critical(this, tr("2048"), tr("金币不足！\n请通过游戏获取金币 或 输入礼包兑换码兑换金币"));
        else {
            ui->gbxCheckerboard->setEnabled(true);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    if (cb.get(i,j) != 0)
                        pbtn[i][j]->setEnabled(true);
        }
    }
    tt.start();
}

void gameS4::hammer() //敲除方块
{
    QPushButton* obj = dynamic_cast<QPushButton*>(sender());
    int r = -1, c = -1;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (obj == pbtn[i][j])
                r = i, c = j;
    User::setCoins(account,User::getCoins(account) - 300);
    attempts++;
    step.push_back(make_pair(cb.getBoard(), score));
    cb.set(r, c, 0);
    hammerNum--;
    update();
}

void gameS4::on_pBtnHome_clicked() //从游戏界面返回用户主界面
{
    systemclose = false;
    this->close();
}

void gameS4::on_pBtnHome2_clicked() //从游戏界面返回用户主界面（游戏失败后）
{
    systemclose = false;
    this->close();
}

void gameS4::reset()
{
    lastNum = 3;
    hammerNum = 3;
    reviveNum = 1;

    //重置游戏结束的界面
    ui->gbxOver->hide();
    ui->lblScore->setText("1234567890");
    ui->lblRecord->setText("new record");
    ui->lblAddCoins->setText("add coins");

    //重置游戏界面
    ui->lblAttempts->setText("attempts");
    ui->lblAttempts->setToolTip("操作次数");
    time.reset();
    gaming = false;
    tt.terminate();
    ui->lblTime->setText("time");
    ui->lblBest->setText("best");
    ui->lblBest->setToolTip("最佳记录");
    ui->lblCoins->setText("coins");
    ui->lblCoins->setToolTip("金币数量");
    ui->lblCur->setText("current");
    ui->lblCur->setToolTip("");
    ui->gbxCheckerboard->setEnabled(false);
    ui->pBtnHammer->setEnabled(false);
    ui->pBtnLast->setEnabled(false);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            pbtn[i][j]->setText("");
            pbtn[i][j]->setFont(QFont("NumberOnly", sizeStyle[N - 3][0]));
            pbtn[i][j]->setStyleSheet(QString::fromLocal8Bit(colorStyle[0].data()));
        }
    attempts = 0;
    lstscore = score = 0;
    cb.reset();
    step.clear();
    dead = false;

    ui->pBtnPause->setEnabled(false);
    ui->pBtnPause->setStyleSheet("QPushButton\n{\n	border-image: url(:/interface/images/pause.png);\n	background-color: rgb(251, 248, 239);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(219, 210, 200);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}");
    ui->pBtnEnd->setEnabled(false);
}

void gameS4::update()
{
    ui->lblBest->setText(intToQString(User::getBest(account, N)));
    ui->lblBest->setToolTip("最佳记录：" + longToQString(User::getBest(account, N)));
    ui->lblCoins->setText(intToQString(User::getCoins(account)));
    ui->lblCoins->setToolTip("金币数量：" + longToQString(User::getCoins(account)));
    ui->lblAttempts->setText(intToQString((ll)attempts));
    ui->lblAttempts->setToolTip("操作次数：" + intToQString(attempts));
    ui->lblTime->setText(QString::fromLocal8Bit(time.get().data()));
    ui->lblCur->setText(intToQString(score));
    ui->lblCur->setToolTip("当前得分：" + longToQString(score));
    ui->gbxCheckerboard->setEnabled(false);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            ll t = cb.get(i, j);
            pbtn[i][j]->setEnabled(false);
            pbtn[i][j]->setText(!t ? "" : numToQString(t));
            //pbtn[i][j]->setFont(QFont("NumberOnly", sizeStyle[N - 3][t > 2147483648 ? 2 : (t > 131072 ? 131072 : t)]));
            if (t > 2147483648) pbtn[i][j]->setFont(QFont("NumberOnly", sizeStyle[N - 3][2]));
            else if (t >= 131072) pbtn[i][j]->setFont(QFont("NumberOnly", sizeStyle[N - 3][65536] - 1));
            else pbtn[i][j]->setFont(QFont("NumberOnly", sizeStyle[N - 3][t]));
            pbtn[i][j]->setStyleSheet(QString::fromLocal8Bit(colorStyle[t > 4294967296 ? -1 : t].data()));
        }
    if (!attempts || !lastNum || step.empty() || dead || !gaming) ui->pBtnLast->setEnabled(false); //如果未进行过任何操作，上一步技能禁用
    else ui->pBtnLast->setEnabled(true);
    if (!hammerNum || cb.have() <= 1 || dead || !gaming) ui->pBtnHammer->setEnabled(false); //如果场上只剩下一个数字，敲除方块按钮禁用
    else ui->pBtnHammer->setEnabled(true);
}

void gameS4::die() //死亡结算
{
    ui->gbxOver->show();
    ui->lblScore->setText(longToQString(score));

    int isRanked;
    if ((isRanked = User::checkRank(N, score)) != -1) { //进入记录榜
        if (score > User::getBest(account, N)) //刷新最高分记录
            User::setBest(account, N, score);
        ui->lblRecord->setText("排行榜 " + intToQString(isRanked + 1));
    }
    else if (score > User::getBest(account, N)) { //刷新最高分记录
        User::setBest(account, N, score);
    }
    else {
        ui->lblRecord->setText(longToQString(User::getBest(account, N)));
    }

    User::setCoins(account, User::getCoins(account) + cal(score) - cal(lstscore));
    ui->lblAddCoins->setText("+ " + intToQString(cal(score)));
    update();

    ui->pBtnPause->setEnabled(false);
    ui->pBtnEnd->setEnabled(false);

    User::addHistory(account, Game(N, attempts, score, time, cb.getBoard()));
}

void gameS4::updateTime()
{
    ui->lblTime->setText(QString::fromLocal8Bit((++time).get().data()));
}
