#include "front.h"
#include "ui_front.h"

front::front(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::front)
{
    ui->setupUi(this);
    setFixedSize(1280, 720);

    connect(&loginForm, SIGNAL(returnFront(int,int)), this, SLOT(fromLogin(int,int)));
    connect(&helpForm, SIGNAL(returnFront(int,int)), this, SLOT(fromHelp(int,int)));
}

front::~front()
{
    delete ui;
}

void front::closeEvent(QCloseEvent*)
{

}

void front::on_pBtnLogin_clicked() //从主界面转到登录界面
{
    this->hide();
    loginForm.move(x(), y());
    loginForm.update();
    loginForm.show();
}

void front::fromLogin(int _x, int _y) //从登录界面返回主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        this->show();
    }
}

void front::on_pBtnHelp_clicked() //从主界面转到帮助界面
{
    this->hide();
    helpForm.move(x(), y());
    helpForm.show();
}

void front::fromHelp(int _x, int _y) //从帮助界面返回主界面
{
    if (systemclose) this->close();
    else {
        systemclose = true;
        this->move(_x, _y);
        this->show();
    }
}

void front::on_pBtnVersion_clicked() //显示版本界面
{
    versionForm.setWindowModality(Qt::ApplicationModal);
    versionForm.move(x() + 440, y() + 170);
    versionForm.show();
}

void front::on_pBtnExit_clicked() //退出游戏
{
    this->close();
}
