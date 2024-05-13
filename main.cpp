#include <QApplication>

#include <QSqlDatabase>
#include <QSqlQuery>

QSqlDatabase db;
QSqlQuery* sql;

#include "implementation.h"
#include "front.h"

std::map<ll, string> colorStyle;
std::map<ll, int> sizeStyle[6];
bool systemclose;

int main(int argc, char *argv[])
{
//    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
//        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    systemclose = true;
    srand((unsigned)time(NULL));
    initColor();
    initSize();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("2048.db");

    if (!db.open()) {
        QMessageBox::critical(0, "数据库打开失败", "无法建立与数据库的链接", QMessageBox::Cancel);
        exit(0);
    }

    sql = new QSqlQuery();

    if (!db.tables().contains("user")) {
        sql->exec("create table user(id integer not null primary key, name text, password text not null, identity integer default 0, enable integer default 0,"
                  "question text, answer text, coins integer default 0, best3 integer default -1, best4 integer default 0, best5 integer default -1, best6 integer default -1, best7 integer default -1, best8 integer default -1);");
        sql->exec("insert into user(id, name, password, identity) values(0, 'Administrator', 'admin', 1);");
    }

    if (!db.tables().contains("game")) {
        QString temp;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                temp += QString("posi_") + (char)('0' + i) + "_" + (char)('0' + j) + " integer, ";
        sql->exec("create table game(id integer not null, mode integer not null, " + temp + "attempts integer not null, score integer not null, time text not null, countup int not null);");
    }

    if (!db.tables().contains("login")) {
        sql->exec("create table login(id integer not null, loginTime text, logoutTime text);");
    }

    if (!db.tables().contains("gift")) {
        sql->exec("create table gift(gid text not null primary key, n integer not null, coin integer not null, ddl text);");
    }

    if (!db.tables().contains("giftrecord")) {
        sql->exec("create table giftrecord(gid integer not null, id integer not null);");
    }

    if (!db.tables().contains("Remem")) {
        sql->exec("create table Remem(remID integer not null, remPswd integer not null, id integer, pswd text);");
        sql->exec("insert into Remem(remID, remPswd) values (0, 0);");
    }

//    sql->exec("insert into user(id, name, password) values(1, 'Administrator', 'admin')");
//    sql->exec("insert into user(id, name, password) values(2, 'Administrator', 'admin')");
//    sql->exec(QString("select * from user"));

//    qDebug() << sql->exec(QString("select * from user where id = -1")) << '\n';

//    while (sql->next()) {
//        qDebug() << sql->value(0).toString();
//        qDebug() << sql->value(1).toString();
//        qDebug() << sql->value(2).toString();
//    }

//    User::setCoins(1, 998244353998244353);

    QApplication a(argc, argv);
    front frt;
    frt.show();
    return a.exec();
}

/*
    从QString转换为string：
        string(xxx.toLocal8Bit());
    从string转换为QString：
        QString::fromLocal8Bit(xxx.data()));
*/
