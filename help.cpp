#include "help.h"
#include "ui_help.h"

help::help(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);

    gbx[0][0] = ui->gbxPlayer;
    gbx[0][1] = ui->gbxP1;
    gbx[0][2] = ui->gbxP2;
    gbx[0][3] = ui->gbxP3;
    gbx[0][4] = ui->gbxP4;
    gbx[0][5] = ui->gbxP5;
    gbx[0][6] = ui->gbxP6;
    gbx[0][7] = ui->gbxP7;
    gbx[0][8] = ui->gbxP8;
    gbx[0][9] = ui->gbxP9;
    gbx[0][10] = ui->gbxP10;

    gbx[1][0] = ui->gbxAdmin;
    gbx[1][1] = ui->gbxA1;
    gbx[1][2] = ui->gbxA2;
    gbx[1][3] = ui->gbxA3;
    gbx[1][4] = ui->gbxA4;
    gbx[1][5] = ui->gbxA5;
    gbx[1][6] = ui->gbxA6;
    gbx[1][7] = ui->gbxA7;

    maxpage[0] = 10;
    maxpage[1] = 7;
    reset();
}

help::~help()
{
    delete ui;
}

void help::closeEvent(QCloseEvent*)
{
    reset();
    emit returnFront(x(), y());
}

void help::on_pBtnPlayer_clicked() //切换到玩家帮助
{
    status = 0;
    swap(page, last);
    update();
}

void help::on_pBtnAdmin_clicked() //切换到管理员帮助
{
    status = 1;
    swap(page, last);
    update();
}

void help::on_pBtnPre_clicked() //上一页
{
    page--;
    update();
}

void help::on_pBtnNxt_clicked() //下一页
{
    page++;
    update();
}

void help::on_pBtnRet_clicked() //从帮助界面返回主界面
{
    systemclose = false;
    this->close();
}

void help::reset()
{
    status = 0;
    page = 1;
    last = 1;
    update();
}

void help::update()
{
    //处理GroupBox
    for (int i = 0; i < 2; i++)
        for (int j = 0; j <= maxpage[i]; j++)
            if (status == i && (!j || page == j))
                gbx[i][j]->show();
            else gbx[i][j]->hide();

    //处理左边的选择
    if (!status) { //玩家帮助
        ui->pBtnPlayer->setEnabled(false);
        ui->pBtnPlayer->setStyleSheet("QPushButton\n{\n	color: rgb(115, 110, 100);\n	background-color: rgb(219, 210, 200);\n	border-radius: 5px;\n}\n");
        ui->pBtnAdmin->setEnabled(true);
        ui->pBtnAdmin->setStyleSheet("QPushButton\n{\n	color: rgb(115, 110, 100);\n	background-color: rgb(251, 248, 239);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(219, 210, 200);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}");
    }
    else { //管理员帮助
        ui->pBtnPlayer->setEnabled(true);
        ui->pBtnPlayer->setStyleSheet("QPushButton\n{\n	color: rgb(115, 110, 100);\n	background-color: rgb(251, 248, 239);\n	border-radius: 5px;\n}\n\nQPushButton:hover\n{\n	background-color: rgb(219, 210, 200);\n}\n\nQPushButton:pressed\n{\n	background-color: rgb(187, 173, 160);\n	padding-left: 3px;\n	padding-top: 3px;\n}");
        ui->pBtnAdmin->setEnabled(false);
        ui->pBtnAdmin->setStyleSheet("QPushButton\n{\n	color: rgb(115, 110, 100);\n	background-color: rgb(219, 210, 200);\n	border-radius: 5px;\n}\n");
    }

    //处理下面的按钮
    ui->pBtnPre->setEnabled(page != 1);
    ui->pBtnNxt->setEnabled(page != maxpage[status]);
    ui->lblPage->setText("Page " + intToQString(page) + " of " + intToQString(maxpage[status]));
}
