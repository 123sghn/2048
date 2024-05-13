#include "manage.h"
#include "ui_manage.h"
#include <QListView>

#define UNLOCK "QPushButton\n{\n	color: rgb(115, 110, 100);\n	border-image: url(:/interface/images/unlocked.png);\n	background-color: rgb(219, 210, 200);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(203, 191, 180);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}"
#define LOCK "QPushButton\n{\n	color: rgb(115, 110, 100);\n	border-image: url(:/interface/images/locked.png);\n	background-color: rgb(219, 210, 200);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(203, 191, 180);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}"

manage::manage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::manage),
    model(new QStandardItemModel())
{
    ui->setupUi(this);
    setFixedSize(1280, 720);
    ui->tbvPeople->setModel(model);
    ui->gbxPlayer->hide();
    ui->gbxAdmin->hide();

    model->setColumnCount(4);
    ui->tbvPeople->horizontalHeader()->setFont(QFont("song", 14));

    model->setHeaderData(0, Qt::Horizontal, "账号");
    model->setHeaderData(1, Qt::Horizontal, "用户名");
    model->setHeaderData(2, Qt::Horizontal, "类型");
    model->setHeaderData(3, Qt::Horizontal, "状态");

    ui->tbvPeople->setColumnWidth(0, 100);
    ui->tbvPeople->setColumnWidth(1, 198);
    ui->tbvPeople->setColumnWidth(2, 100);
    ui->tbvPeople->setColumnWidth(3, 80);

    ui->tbvPeople->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tbvPeople->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tbvPeople->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tbvPeople->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    inform[0] = ui->pBtnS3;
    inform[1] = ui->pBtnS4;
    inform[2] = ui->pBtnS5;
    inform[3] = ui->pBtnS6;
    inform[4] = ui->pBtnS7;
    inform[5] = ui->pBtnS8;

    ui->cmbUsers->setView(new QListView());
    ui->cmbNormal->setView(new QListView());

    ui->cmbPDisable->setView(new QListView());
    ui->cmbADisable->setView(new QListView());
}

manage::~manage()
{
    delete model;
    delete ui->cmbUsers->view();
    delete ui->cmbNormal->view();
    delete ui->cmbPDisable->view();
    delete ui->cmbADisable->view();
    delete ui;
}

void manage::setAccount(int i)
{
    account = i;
    state[0] = state[1] = true;
    if (!account) {
        ui->cmbUsers->setEnabled(true);
        ui->cmbUsers->setCurrentIndex(0);
        kinds[0] = kinds[1] = true;
    }
    else {
        ui->cmbUsers->setEnabled(false);
        ui->cmbUsers->setCurrentIndex(1);
        kinds[0] = true, kinds[1] = false;
    }
    update();
}

void manage::closeEvent(QCloseEvent* event)
{
    if (changed) {
        bool isSaved;
        switch(QMessageBox::warning(this, tr("2048"), tr("是否保存修改？"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes)) {
        case QMessageBox::Yes :
            isSaved = save();
            if(!isSaved) { event->ignore(); systemclose = true; return; } //如果保存失败，中断关闭窗口的程序
            break;
        case QMessageBox::No : break;
        default: event->ignore(); systemclose = true; return;
        }
    }

    ui->ldtSID->clear();
    ui->ldtSName->clear();
    ui->cmbNormal->setCurrentIndex(0);
    state[0] = state[1] = true;
    ui->cmbUsers->setEnabled(true);
    ui->cmbUsers->setCurrentIndex(0);
    kinds[0] = kinds[1] = true;


    ui->gbxText->show();

    ui->gbxPlayer->hide();
    ui->lblPID->setText("ID: ");
    ui->ldtPName->clear();
    ui->cmbPDisable->setCurrentIndex(0);
    ui->sbxCoins->setValue(0);
    for (int i = 0; i < 6; i++)
        inform[i]->setStyleSheet(LOCK);

    ui->gbxAdmin->hide();
    ui->lblAID->setText("ID: ");
    ui->ldtAName->clear();
    ui->cmbADisable->setCurrentIndex(0);

    reset();
    emit returnAdmin(x(), y());
}

void manage::on_ldtSID_textChanged(const QString&)
{
    update();
}

void manage::on_ldtSName_textChanged(const QString&)
{
    update();
}

void manage::on_cmbUsers_currentIndexChanged(int index)
{
    switch (index) {
    case 0 : kinds[0] = kinds[1] = 1; break;
    case 1 : kinds[0] = 1; kinds[1] = 0; break;
    case 2 : kinds[0] = 0; kinds[1] = 1; break;
    }
    update();
}

void manage::on_cmbNormal_currentIndexChanged(int index)
{
    switch (index) {
    case 0 : state[0] = state[1] = 1; break;
    case 1 : state[0] = 1; state[1] = 0; break;
    case 2 : state[0] = 0; state[1] = 1; break;
    }
    update();
}

void manage::on_pBtnSID_clicked()
{
    ui->ldtSID->clear();
}

void manage::on_pBtnSName_clicked()
{
    ui->ldtSName->clear();
}

void manage::on_tbvPeople_clicked(const QModelIndex& index)
{
    int t = isNumber(model->item(index.row(), 0)->text()).second;
    if (t == cur) return;

    if (changed) {
        bool isSaved;
        switch(QMessageBox::warning(this, tr("2048"), tr("是否保存修改？"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes)) {
        case QMessageBox::Yes :
            isSaved = save();
            if(!isSaved) return;
            break;
        case QMessageBox::No : break;
        default: return;
        }
    }

    ui->gbxText->hide();
    identity = User::getIdentity(t);
    cur = t;

    display();
}

void manage::on_pBtnPSave_clicked()
{
    save();
}

void manage::on_ldtPName_textEdited(const QString&)
{
    changed |= 1;
    if (string(ui->ldtPName->text().toLocal8Bit()) == User::getName(cur))
        changed &= ~1;
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_sbxCoins_valueChanged(int)
{
    changed |= (1 << 1);
    if (ui->sbxCoins->value() == User::getCoins(cur))
        changed &= ~(1 << 1);
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_cmbPDisable_currentIndexChanged(int)
{
    changed |= (1 << 2);
    if (ui->cmbPDisable->currentIndex() == User::getEnable(cur))
        changed &= ~(1 << 2);
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnS3_clicked()
{
    int mode = 3;
    changed |= (1 << mode);
    if (inform[mode - 3]->styleSheet() == LOCK) { //解锁
        inform[mode - 3]->setStyleSheet(UNLOCK);
        if (User::getBest(cur, mode) >= 0) { //原先已解锁，相当于按了两次，不做修改
            inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, mode)));
            changed &= ~(1 << mode);
        }
        else {
            if (User::getBest(cur, mode) == -1)
                inform[mode - 3]->setToolTip("已解锁，最高分：0");
            else inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(-User::getBest(cur, mode)));
        }
    }
    else {
        inform[mode - 3]->setStyleSheet(LOCK);
        inform[mode - 3]->setToolTip("未解锁");
        if (User::getBest(cur, mode) < 0) //原先未解锁，相当于按了两次，不做修改
            changed &= ~(1 << mode);
    }
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnS4_clicked()
{
    int mode = 4;
    changed |= (1 << mode);
    if (inform[mode - 3]->styleSheet() == LOCK) { //解锁
        inform[mode - 3]->setStyleSheet(UNLOCK);
        if (User::getBest(cur, mode) >= 0) { //原先已解锁，相当于按了两次，不做修改
            inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, mode)));
            changed &= ~(1 << mode);
        }
        else {
            if (User::getBest(cur, mode) == -1)
                inform[mode - 3]->setToolTip("已解锁，最高分：0");
            else inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(-User::getBest(cur, mode)));
        }
    }
    else {
        inform[mode - 3]->setStyleSheet(LOCK);
        inform[mode - 3]->setToolTip("未解锁");
        if (User::getBest(cur, mode) < 0) //原先未解锁，相当于按了两次，不做修改
            changed &= ~(1 << mode);
    }
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnS5_clicked()
{
    int mode = 5;
    changed |= (1 << mode);
    if (inform[mode - 3]->styleSheet() == LOCK) { //解锁
        inform[mode - 3]->setStyleSheet(UNLOCK);
        if (User::getBest(cur, mode) >= 0) { //原先已解锁，相当于按了两次，不做修改
            inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, mode)));
            changed &= ~(1 << mode);
        }
        else {
            if (User::getBest(cur, mode) == -1)
                inform[mode - 3]->setToolTip("已解锁，最高分：0");
            else inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(-User::getBest(cur, mode)));
        }
    }
    else {
        inform[mode - 3]->setStyleSheet(LOCK);
        inform[mode - 3]->setToolTip("未解锁");
        if (User::getBest(cur, mode) < 0) //原先未解锁，相当于按了两次，不做修改
            changed &= ~(1 << mode);
    }
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnS6_clicked()
{
    int mode = 6;
    changed |= (1 << mode);
    if (inform[mode - 3]->styleSheet() == LOCK) { //解锁
        inform[mode - 3]->setStyleSheet(UNLOCK);
        if (User::getBest(cur, mode) >= 0) { //原先已解锁，相当于按了两次，不做修改
            inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, mode)));
            changed &= ~(1 << mode);
        }
        else {
            if (User::getBest(cur, mode) == -1)
                inform[mode - 3]->setToolTip("已解锁，最高分：0");
            else inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(-User::getBest(cur, mode)));
        }
    }
    else {
        inform[mode - 3]->setStyleSheet(LOCK);
        inform[mode - 3]->setToolTip("未解锁");
        if (User::getBest(cur, mode) < 0) //原先未解锁，相当于按了两次，不做修改
            changed &= ~(1 << mode);
    }
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnS7_clicked()
{
    int mode = 7;
    changed |= (1 << mode);
    if (inform[mode - 3]->styleSheet() == LOCK) { //解锁
        inform[mode - 3]->setStyleSheet(UNLOCK);
        if (User::getBest(cur, mode) >= 0) { //原先已解锁，相当于按了两次，不做修改
            inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, mode)));
            changed &= ~(1 << mode);
        }
        else {
            if (User::getBest(cur, mode) == -1)
                inform[mode - 3]->setToolTip("已解锁，最高分：0");
            else inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(-User::getBest(cur, mode)));
        }
    }
    else {
        inform[mode - 3]->setStyleSheet(LOCK);
        inform[mode - 3]->setToolTip("未解锁");
        if (User::getBest(cur, mode) < 0) //原先未解锁，相当于按了两次，不做修改
            changed &= ~(1 << mode);
    }
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnS8_clicked()
{
    int mode = 8;
    changed |= (1 << mode);
    if (inform[mode - 3]->styleSheet() == LOCK) { //解锁
        inform[mode - 3]->setStyleSheet(UNLOCK);
        if (User::getBest(cur, mode) >= 0) { //原先已解锁，相当于按了两次，不做修改
            inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, mode)));
            changed &= ~(1 << mode);
        }
        else {
            if (User::getBest(cur, mode) == -1)
                inform[mode - 3]->setToolTip("已解锁，最高分：0");
            else inform[mode - 3]->setToolTip("已解锁，最高分：" + intToQString(-User::getBest(cur, mode)));
        }
    }
    else {
        inform[mode - 3]->setStyleSheet(LOCK);
        inform[mode - 3]->setToolTip("未解锁");
        if (User::getBest(cur, mode) < 0) //原先未解锁，相当于按了两次，不做修改
            changed &= ~(1 << mode);
    }
    if (changed) ui->pBtnPSave->setEnabled(true);
    else ui->pBtnPSave->setEnabled(false);
}

void manage::on_pBtnPLogin_clicked()
{
    onlineForm.setWindowModality(Qt::ApplicationModal);
    onlineForm.move(x() + 250, y() + 35);
    onlineForm.setAccount(cur);
    onlineForm.show();
}

void manage::on_pBtnPReset_clicked()
{
    string ques = "是否重置账号" + intToString(cur) + "的密码？";
    if (QMessageBox::question(this, tr("2048"), tr(ques.c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {
        User::setPassword(cur, "123456");
        QMessageBox::about(this, tr("2048"), tr("重置密码成功！"));
    }
}

void manage::on_pBtnPClear_clicked()
{
    string ques = "是否清除账号" + intToString(cur) + "的所有游戏信息？";
    if (QMessageBox::question(this, tr("2048"), tr(ques.c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {
        User::reset(cur);
        display();
        QMessageBox::about(this, tr("2048"), tr("已清除该玩家的所有游戏信息！"));
    }
}

void manage::on_pBtnPCancellation_clicked()
{
    string ques = "是否注销账号" + intToString(cur) + "？";
    if (QMessageBox::question(this, tr("2048"), tr(ques.c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {
        User::del(cur);
        reset(); update();
        QMessageBox::about(this, tr("2048"), tr("已成功注销该账号！"));
    }
}

void manage::on_pBtnASave_clicked()
{
    save();
}

void manage::on_ldtAName_textEdited(const QString&)
{
    changed |= 1;
    if (string(ui->ldtAName->text().toLocal8Bit()) == User::getName(cur))
        changed &= ~1;
    if (changed) ui->pBtnASave->setEnabled(true);
    else ui->pBtnASave->setEnabled(false);
}

void manage::on_cmbADisable_currentIndexChanged(int)
{
    changed |= (1 << 2);
    if (ui->cmbADisable->currentIndex() == User::getEnable(cur))
        changed &= ~(1 << 2);
    if (changed) ui->pBtnASave->setEnabled(true);
    else ui->pBtnASave->setEnabled(false);
}

void manage::on_pBtnAReset_clicked()
{
    string ques = "是否重置账号" + intToString(cur) + "的密码？";
    if (QMessageBox::question(this, tr("2048"), tr(ques.c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {
        User::setPassword(cur, "123456");
        QMessageBox::about(this, tr("2048"), tr("重置密码成功！"));
    }
}

void manage::on_pBtnACancellation_clicked()
{
    string ques = "是否注销账号" + intToString(cur) + "？";
    if (QMessageBox::question(this, tr("2048"), tr(ques.c_str()),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {
        User::del(cur);
        reset(); update();
        QMessageBox::about(this, tr("2048"), tr("已成功注销该账号！"));
    }
}

void manage::on_pBtnRet_clicked() //从管理用户界面返回管理员主界面
{
    systemclose = false;
    this->close();
}

void manage::reset() //清楚表格内所有东西、删除cur、页面显示恢复
{
    for (int i = model->rowCount() - 1; i >= 0; i--)
        for (int j = 3; j >= 0; j--) {
            delete model->item(i, j);
        }
    model->removeRows(0, model->rowCount());

    ui->lblNo->show();
    ui->lblNo->setText("暂无任何人员数据");

    ui->gbxText->show();
    ui->gbxPlayer->hide();
    ui->gbxAdmin->hide();

    changed = 0;
    cur = 0;
    identity = 0;
}

void manage::update()
{
    //每次更新前需要把原先的表格删除
    for (int i = model->rowCount() - 1; i >= 0; i--)
        for (int j = 2; j >= 0; j--) {
            delete model->item(i, j);
        }
    model->removeRows(0, model->rowCount());

    string tid = string(ui->ldtSID->text().toLocal8Bit());
    string tname = string(ui->ldtSName->text().toLocal8Bit());

    bool haveUsers = false;

    int i = 0, total = User::getTot();
    for (int r = 0; r < total; r++) {
        int id = User::getID(r);
        if ((User::getIdentity(id) && account != 0) || id == 0) continue; //当且仅当主管理员登录会显示管理员账号
        haveUsers = true;
        if (!needDisplay(id, tid, tname)) continue; //判断账号和用户名是否满足显示要求
        if (!state[(bool)User::getEnable(id)]) continue; //判断状态是否满足显示要求
        if (!kinds[User::getIdentity(id)]) continue; //判断玩家/管理员是否满足显示要求

        model->setItem(i, 0, new QStandardItem(intToQString(id)));
        model->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit(User::getName(id).data())));
        if (User::getIdentity(id))
            model->setItem(i, 2, new QStandardItem("管理员"));
        else model->setItem(i, 2, new QStandardItem("玩家"));

        if (!User::getEnable(id))
            model->setItem(i, 3, new QStandardItem("√"));
        else model->setItem(i, 3, new QStandardItem(""));

        for (int j = 0; j < 4; j++)
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);

        i++;
    }

    if (haveUsers) {
        if (model->rowCount()) {
            ui->lblNo->setText("暂无任何人员数据");
            ui->lblNo->hide();
        }
        else {
            ui->lblNo->setText("未搜索到满足条件的人员");
            ui->lblNo->show();
        }
    }
    else {
        ui->lblNo->setText("暂无任何人员数据");
        ui->lblNo->show();
    }
}

bool manage::save()
{
    bool flag = false;

    //判断输入的用户名是否合法
    //空输入
    if (ui->ldtPName->text().isEmpty() && ui->ldtAName->text().isEmpty())
        QMessageBox::critical(this, tr("2048"), tr("用户名不能为空！"));
    //长度超限
    else if (string(ui->ldtPName->text().toLocal8Bit()).length() > 16 ||
             string(ui->ldtAName->text().toLocal8Bit()).length() > 16)
        QMessageBox::critical(this, tr("2048"), tr("用户名的长度应不超过16个字符！"));

    else { //修改成功
        flag = true;

        if (!identity) { //用户修改成功
            User::setName(cur, string(ui->ldtPName->text().toLocal8Bit()));
            User::setEnable(cur, ui->cmbPDisable->currentIndex());
            User::setCoins(cur, ui->sbxCoins->value());
            for (int i = 3; i <= 8; i++)
                if (inform[i - 3]->styleSheet() == LOCK)
                    User::setBest(cur, i, User::getBest(cur, i) == 0 ? -1 : -abs(User::getBest(cur, i)));
                else if (User::getBest(cur, i) < 0) //原先未解锁，操作后解锁
                    User::setBest(cur, i, User::getBest(cur, i) == -1 ? 0 : abs(User::getBest(cur, i)));
        }

        else { //管理员修改成功
            User::setName(cur, string(ui->ldtAName->text().toLocal8Bit()));
            User::setEnable(cur, ui->cmbADisable->currentIndex());
        }

        string out = "已成功更新账号" + intToString(cur) + "的以下信息：\n";
        for (int i = 0; i < 15; i++)
            if ((changed >> i) & 1)
                switch(i) {
                case 0 : out += " · 用户名\n"; break;
                case 1 : out += " · 金币数量\n"; break;
                case 2 : out += " · 用户状态\n"; break;
                case 3 :
                case 4 :
                case 5 :
                case 6 :
                case 7 :
                case 8 : i = 8; out += " · 单人游戏解锁状态\n"; break;
                case 9 :
                case 10 :
                case 11 :
                case 12 :
                case 13 :
                case 14 : i = 14; out += " · 双人游戏解锁状态\n"; break;
                }
        out = out.substr(0, out.length() - 1);
        int tcur = cur, tident = identity;
        reset(); update(); //reset用false防止二次写入带来的清空数据
        cur = tcur, identity = tident;
        display();
        QMessageBox::about(this, tr("2048"), tr(out.c_str()));
    }

    return flag;
}

bool manage::needDisplay(int jid, string id, string name)
{
    if (id != "" && intToString(jid).find(id) == string::npos) return false;
    if (!name.length()) return true;

    string jn = User::getName(jid);
    if (jn.find(name) == string::npos) return false; //如果没找到，直接return false;

    //排除名字是汉字，但是前一个汉字的第二个ascii码和后一个汉字的第一个ascii组成新的汉字的情况
    bool flag = false;
    for (int i = 0; i <= (int)jn.length() - (int)name.length(); i++)
    {
        int index = 0;
        string tname(name.length(), '0');
        for (int j = i; j < i + (int)name.length(); j++)
            tname[index++] = jn[j];
        if (jn[i] <= 0) //如果是汉字，第一个ascii码值小于0
            i++;
        if (tname == name)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

void manage::display()
{
    ui->gbxText->hide();

    if (!User::getIdentity(cur)) { //修改玩家
        ui->gbxPlayer->show();
        ui->gbxAdmin->hide();
        ui->lblPID->setText("ID: " + intToQString(cur));
        ui->ldtPName->setText(QString::fromLocal8Bit(User::getName(cur).data()));
        ui->cmbPDisable->setCurrentIndex(User::getEnable(cur));

        ui->sbxCoins->setValue(User::getCoins(cur));
        for (int i = 3; i <= 8; i++) {
            if (User::getBest(cur, i) >= 0) {
                inform[i - 3]->setStyleSheet(UNLOCK);
                inform[i - 3]->setToolTip("已解锁，最高分：" + intToQString(User::getBest(cur, i)));
            }
            else {
                inform[i - 3]->setStyleSheet(LOCK);
                inform[i - 3]->setToolTip("未解锁");
            }
        }
    }
    else { //修改管理员
        ui->gbxAdmin->show();
        ui->gbxPlayer->hide();
        ui->lblAID->setText("ID: " + intToQString(cur));
        ui->ldtAName->setText(QString::fromLocal8Bit(User::getName(cur).data()));
        ui->cmbADisable->setCurrentIndex(User::getEnable(cur));
    }

    changed = 0;
    ui->pBtnPSave->setEnabled(false);
    ui->pBtnASave->setEnabled(false);
}
