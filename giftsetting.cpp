#include "giftsetting.h"
#include "ui_giftsetting.h"

giftsetting::giftsetting(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::giftsetting),
    model(new QStandardItemModel())
{
    ui->setupUi(this);
    setFixedSize(1280, 720);

    ui->tbvGift->setModel(model);

    ui->gbxEdit->hide();

    model->setColumnCount(6);
    ui->tbvGift->horizontalHeader()->setFont(QFont("song", 13));

    model->setHeaderData(0, Qt::Horizontal, "礼包兑换码");
    model->setHeaderData(1, Qt::Horizontal, "礼包个数");
    model->setHeaderData(2, Qt::Horizontal, "已兑换数量");
    model->setHeaderData(3, Qt::Horizontal, "礼包金额");
    model->setHeaderData(4, Qt::Horizontal, "失效时间");
    model->setHeaderData(5, Qt::Horizontal, "是否可领取");

    ui->tbvGift->setColumnWidth(0, 100);
    ui->tbvGift->setColumnWidth(1, 100);
    ui->tbvGift->setColumnWidth(2, 100);
    ui->tbvGift->setColumnWidth(3, 100);
    ui->tbvGift->setColumnWidth(4, 198);
    ui->tbvGift->setColumnWidth(5, 80);

    ui->tbvGift->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tbvGift->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tbvGift->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tbvGift->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tbvGift->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    ui->tbvGift->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
}

giftsetting::~giftsetting()
{
    delete model;
    delete ui;
}

void giftsetting::update()
{
    int i = 0, total = Gifts::getTot();
    for (; i < total; i++) {
        string gid = Gifts::getGid(i);

        model->setItem(i, 0, new QStandardItem(QString::fromLocal8Bit(gid.data())));
        model->setItem(i, 1, new QStandardItem(intToQString(Gifts::getN(gid))));
        model->setItem(i, 2, new QStandardItem(intToQString(Gifts::getGot(gid))));
        model->setItem(i, 3, new QStandardItem(intToQString(Gifts::getCoin(gid))));
        model->setItem(i, 4, new QStandardItem(QString::fromLocal8Bit(Gifts::getDdl(gid).getTime().data())));
        if (Gifts::able(gid) && Time() < Gifts::getDdl(gid))
            model->setItem(i, 5, new QStandardItem("√"));
        else model->setItem(i, 5, new QStandardItem(""));

        for (int j = 0; j < 6; j++)
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
    }

    //加一行空的，以便于新建
    for (int j = 0; j < 6; j++)
        model->setItem(i, j, new QStandardItem(""));

    changed = 0;
    ui->pBtnSave->setEnabled(false);
}

void giftsetting::closeEvent(QCloseEvent* event)
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

    reset();
    ui->ldtCode->clear();
    ui->sbxNum->setMinimum(0);
    ui->sbxNum->setValue(0);
    ui->sbxPrice->setValue(1);
    ui->dteFalse->setDate(QDate(2000, 1, 1));
    ui->dteFalse->setTime(QTime(0, 0, 0));
    emit returnAdmin(x(), y());
}

void giftsetting::on_tbvGift_clicked(const QModelIndex& index)
{
    cur = string(model->item(index.row(), 0)->text().toLocal8Bit());
    if (!ui->gbxEdit->isHidden() && cur == string(ui->ldtCode->text().toLocal8Bit())) return;

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

    if (cur == "") { //新建礼包码
        ui->gbxText->hide();
        ui->gbxEdit->show();
        ui->lblSub->setText("新建礼包码");
        ui->ldtCode->clear();
        ui->ldtCode->setEnabled(true);
        ui->sbxNum->setMinimum(0);
        ui->sbxNum->setValue(1);
        ui->sbxPrice->setValue(1);
        Time ttime;
        ttime = ttime + 60;
        ui->dteFalse->setDate(QDate(ttime.getY(), ttime.getM(), ttime.getD()));
        ui->dteFalse->setTime(QTime(23, 59, 59));
        changed = 0;
        ui->pBtnSave->setEnabled(false);
        ui->ldtCode->setFocus();
    }
    else { //修改礼包码
        ui->gbxText->hide();
        ui->gbxEdit->show();
        ui->lblSub->setText("修改礼包码");
        ui->ldtCode->setText(QString::fromLocal8Bit(cur.data()));
        ui->ldtCode->setEnabled(false);
        ui->sbxNum->setMinimum(Gifts::getGot(cur));
        ui->sbxNum->setValue(Gifts::getN(cur));
        ui->sbxPrice->setValue(Gifts::getCoin(cur));
        ui->dteFalse->setDate(QDate(Gifts::getDdl(cur).getY(), Gifts::getDdl(cur).getM(), Gifts::getDdl(cur).getD()));
        ui->dteFalse->setTime(QTime(Gifts::getDdl(cur).getH(), Gifts::getDdl(cur).getMin(), Gifts::getDdl(cur).getS()));
        changed = 0;
        ui->pBtnSave->setEnabled(false);
        ui->sbxNum->setFocus();
    }
}

void giftsetting::on_tbvGift_doubleClicked(const QModelIndex& index)
{
    if (index.row() == model->rowCount() - 1) return;

    //开始删除
    if (QMessageBox::question(this, tr("2048"), tr("是否删除该礼包码"),
                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) { //确认删除
        string t = string(model->item(index.row(), 0)->text().toLocal8Bit());

        for (int j = 5; j >= 0; j--)
            delete model->item(index.row(), j);
        model->removeRow(index.row());

        Gifts::del(t);
        reset();
        update();
        QMessageBox::about(this, tr("2048"), tr("已成功删除该礼包码!"));
    }
}

void giftsetting::on_pBtnSave_clicked()
{
    save();
}

void giftsetting::on_ldtCode_textChanged(const QString&)
{
    changed |= 1;
    ui->pBtnSave->setEnabled(true);
}

void giftsetting::on_sbxNum_valueChanged(int)
{
    changed |= (1 << 1);
    if (cur != "" && ui->sbxNum->value() == Gifts::getN(cur))
        changed &= ~(1 << 1);
    if (changed) ui->pBtnSave->setEnabled(true);
    else ui->pBtnSave->setEnabled(false);
}

void giftsetting::on_sbxPrice_valueChanged(int)
{
    changed |= (1 << 2);
    if (cur != "" && ui->sbxPrice->value() == Gifts::getCoin(cur))
        changed &= ~(1 << 1);
    if (changed) ui->pBtnSave->setEnabled(true);
    else ui->pBtnSave->setEnabled(false);
}

void giftsetting::on_dteFalse_dateTimeChanged(const QDateTime&)
{
    changed |= (1 << 3);
    if (cur != "" && ui->dteFalse->date() == QDate(Gifts::getDdl(cur).getY(), Gifts::getDdl(cur).getM(), Gifts::getDdl(cur).getD()) &&
        ui->dteFalse->time() == QTime(Gifts::getDdl(cur).getH(), Gifts::getDdl(cur).getMin(), Gifts::getDdl(cur).getS()))
        changed &= ~(1 << 3);
    if (changed) ui->pBtnSave->setEnabled(true);
    else ui->pBtnSave->setEnabled(false);
}

void giftsetting::on_pBtnRet_clicked() //从礼包兑换码设置界面返回管理员主界面
{
    systemclose = false;
    this->close();
}

void giftsetting::reset()
{
    ui->gbxText->show();

    ui->gbxEdit->hide();
    ui->lblSub->setText("新建礼包码");
    ui->ldtCode->setEnabled(true);
    //ui->dteFalse->setDate(QDate(2000, 1, 1));
    //ui->dteFalse->setTime(QTime(0, 0, 0));

    for (int i = model->rowCount() - 1; i >= 0; i--)
        for (int j = 4; j >= 0; j--) {
            delete model->item(i, j);
        }
    model->removeRows(0, model->rowCount());

    changed = 0;
    cur = "";
    ui->pBtnSave->setEnabled(false);
    ui->ldtCode->setFocus();
}

bool giftsetting::save()
{
    int flag = false;

    //先判断修改的是否符合条件
    //判断输入的礼包码是否合法
    //空输入
    if (ui->ldtCode->text().isEmpty())
        QMessageBox::critical(this, tr("2048"), tr("礼包码不能为空！"));
    //长度超限
    else if (string(ui->ldtCode->text().toLocal8Bit()).length() > 8)
        QMessageBox::critical(this, tr("2048"), tr("礼包码的长度应不超过8个字符！"));
    //礼包码重复（仅限新建礼包码）
    else if (ui->lblSub->text() == "新建礼包码" && //判断是不是在新建
             Gifts::checkID(string(ui->ldtCode->text().toLocal8Bit()))) //判断是否重复
        QMessageBox::critical(this, tr("2048"), tr("您输入的礼包码已存在，请重新输入！"));

    else { //满足全部条件
        flag = true;
        string ts = string(ui->ldtCode->text().toLocal8Bit());
        int tn = ui->sbxNum->value();
        int tc = ui->sbxPrice->value();
        Time tt(ui->dteFalse->date().year(), ui->dteFalse->date().month(), ui->dteFalse->date().day(),
                ui->dteFalse->time().hour(), ui->dteFalse->time().minute(), ui->dteFalse->time().second());
        if (ui->lblSub->text() == "新建礼包码") { //新建
            sql->exec(QString("insert into gift values('%1', %2, %3, '%4');").arg(QString::fromLocal8Bit(ts.data())).arg(tn).arg(tc).arg(QString::fromLocal8Bit(tt.getTime().data())));
            reset(); update();
            QMessageBox::about(this, tr("2048"), tr("已成功新建礼包码！"));
        }
        else { //修改
            Gifts::setN(ts, tn);
            Gifts::setCoin(ts, tc);
            Gifts::setDdl(ts, tt);
            string out = "已成功更新以下信息：\n";
            for (int i = 1; i < 4; i++)
                if ((changed >> i) & 1)
                    switch(i) {
                    case 1 : out += " · 礼包码的数量\n"; break;
                    case 2 : out += " · 礼包码的金额\n"; break;
                    case 3 : out += " · 礼包码的失效日期\n"; break;
                    }
            out = out.substr(0, out.length() - 1);
            reset(); update();
            QMessageBox::about(this, tr("2048"), tr(out.c_str()));
        }
    }

    return flag;
}
