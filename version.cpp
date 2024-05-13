#include "version.h"
#include "ui_version.h"

version::version(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::version)
{
    ui->setupUi(this);
    setFixedSize(400, 380);

    ui->lblVersion->setText("版本号：v.2.1.0");
    ui->lblTime->setText("更新日期：2024-05-12");
}

version::~version()
{
    delete ui;
}
