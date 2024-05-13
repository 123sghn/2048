#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <list>
#include <string>
#include <set>
#include <map>
#include <QSqlDatabase>
#include <QSqlQuery>
using namespace std;
#define ll long long

extern QSqlDatabase db;
extern QSqlQuery* sql;

class Time;
class Duration {
    friend class Time;

public:
    Duration() : d(0), h(0), min(0), s(0) {}
    Duration(int dd, int hh, int mmin, int ss) : d(dd), h(hh), min(mmin), s(ss) {}

    int getD() const { return d; }
    int getH() const { return h; }
    int getMin() const { return min; }
    int getS() const { return s; }
    string getLen() const;
    Duration operator + (const Duration&) const;

    bool operator < (const Duration&) const;
    bool operator == (const Duration&) const;

private:
    int d, h, min, s;
};

class Time {
public :
    Time(); //直接读取系统时间，存储到类中
    Time(int, int, int, int, int, int); //强制设置时间
    Time(string);
    ~Time() {}

    int getY() const { return y; }
    int getM() const { return m; }
    int getD() const { return d; }
    int getH() const { return h; }
    int getMin() const { return min; }
    int getS() const { return s; }
    void setTime(int, int, int, int, int, int);
    void setTime(const Time&);
    string getTime() const;
    Time operator + (int); //往后推int天数

    Time operator + (const Duration&) const;
    Duration operator - (const Time&) const;

    bool operator < (const Time&) const;
    bool operator == (const Time&) const;

private:
    int y, m, d, h, min, s;
};

class Countup {
public:
    Countup() : h(0), m(0), s(0) {}
    Countup(int x) : h(x / 60 / 60), m(x / 60 % 60), s(x % 60) {}
    Countup(int h, int m, int s) : h(h), m(m), s(s) {}

    void reset();
    string get() const;
    int getVal() const { return h * 3600 + m * 60 + s; }

    Countup& operator ++();
    bool operator < (const Countup&) const; //比较速度，时间长的速度较小
    bool operator == (const Countup&) const;

private:
    int h, m, s;
};

class Game {
public:
    Game() {}
    Game(int md, int at, ll sc, Countup cu, vector<vector<ll>> x) :
        mode(md), attempts(at), score(sc), countup(cu), last(x) {}
    Game(int md, int at, ll sc, string tm, int cu, vector<vector<ll>> x) :
        mode(md), attempts(at), score(sc), time(tm), countup(cu), last(x) {}

    void setMode(int mod) { mode = mod; }
    int getMode() const { return mode; }
    void setAttempts(int at) { attempts = at; }
    int getAttempts() const { return attempts; }
    void setScore(ll sc) { score = sc; }
    ll getScore() const { return score; }
    void setTime(Time tm) { time = tm; }
    Time getTime() const { return time; }
    void setCountup(Countup tc) { countup = tc; }
    Countup getCountup() const { return countup; }

private:
    int mode; //游戏模式（4-四阶，5-五阶）
    int attempts; //总步数
    ll score; //最终成绩
    Time time; //游戏时间
    Countup countup; //游戏时长
public:
    vector<vector<ll>> last; //最终棋盘
};

class Remem {
public:
    static bool getRemID() {
        sql->exec("select remID from Remem;");
        sql->next();
        return sql->value(0).toInt();
    }
    static bool getRemPswd() {
        sql->exec("select remPswd from Remem;");
        sql->next();
        return sql->value(0).toInt();
    }
    static int getID() {
        sql->exec("select id from Remem;");
        sql->next();
        return sql->value(0).toInt();
    }
    static QString getPswd() {
        sql->exec("select pswd from Remem;");
        sql->next();
        return sql->value(0).toString();
    }

    static void setRemID(bool b) {
        sql->exec(QString("update Remem set remID = %1;").arg((int)b));
    }
    static void setRemPswd(bool b) {
        sql->exec(QString("update Remem set remPswd = %1;").arg((int)b));
    }
    static void setID(int x) {
        sql->exec(QString("update Remem set id = %1;").arg(x));
    }
    static void setPassword(QString str) {
        sql->exec(QString("update Remem set pswd = '%1';").arg(str));
    }

};

class User {
public:
    static bool checkID(int id) {
        sql->exec(QString("select count(*) from user where id = %1;").arg(id));
        sql->next();
        return sql->value(0).toInt();
    }

    static int getTot() {
        sql->exec("select count(*) from user;");
        sql->next();
        return sql->value(0).toInt();
    }
    static int getID(int r) {
        sql->exec(QString("select id from user order by id asc limit 1 offset %1;").arg(r));
        sql->next();
        return sql->value(0).toInt();
    }
    static void reset(int id) {
        setCoins(id, 0);
        for (int i = 3; i <= 8; i++)
            User::setBest(id, i, -1 + (i == 4));
        sql->exec(QString("delete from game where id = %1;").arg(id));
        sql->exec(QString("delete from giftrecord where id = %1;").arg(id));
        sql->exec(QString("delete from login where id = %1;").arg(id));
        if (Remem::getRemID() && Remem::getID() == id) {
            Remem::setRemID(false);
            Remem::setRemPswd(false);
        }
    }
    static void del(int id) {
        sql->exec(QString("delete from user where id = %1;").arg(id));
        sql->exec(QString("delete from game where id = %1;").arg(id));
        sql->exec(QString("delete from giftrecord where id = %1;").arg(id));
        sql->exec(QString("delete from login where id = %1;").arg(id));
        if (Remem::getRemID() && Remem::getID() == id) {
            Remem::setRemID(false);
            Remem::setRemPswd(false);
        }
    }

    static string getName(int id) {
        sql->exec(QString("select name from user where id = %1;").arg(id));
        sql->next();
        return string(sql->value(0).toString().toLocal8Bit());
    }
    static string getPassword(int id) {
        sql->exec(QString("select password from user where id = %1;").arg(id));
        sql->next();
        return string(sql->value(0).toString().toLocal8Bit());
    }
    static int getIdentity(int id) {
        sql->exec(QString("select identity from user where id = %1;").arg(id));
        sql->next();
        return sql->value(0).toInt();
    }
    static int getEnable(int id) {
        sql->exec(QString("select enable from user where id = %1;").arg(id));
        sql->next();
        return sql->value(0).toInt();
    }
    static string getQuestion(int id) {
        sql->exec(QString("select question from user where id = %1;").arg(id));
        sql->next();
        return string(sql->value(0).toString().toLocal8Bit());
    }
    static string getAnswer(int id) {
        sql->exec(QString("select answer from user where id = %1;").arg(id));
        sql->next();
        return string(sql->value(0).toString().toLocal8Bit());
    }
    static ll getCoins(int id) {
        sql->exec(QString("select coins from user where id = %1;").arg(id));
        sql->next();
        return sql->value(0).toLongLong();
    }
    static ll getBest(int id, int mode) {
        sql->exec(QString("select best%1 from user where id = %2;").arg(mode).arg(id));
        sql->next();
        return sql->value(0).toLongLong();
    }
    static int getStored(int id) {
        if (!getIdentity(id))
            sql->exec(QString("select count(*) from game where id = %1;").arg(id));
        else sql->exec(QString("select count(*) from game;"));
        sql->next();
        return sql->value(0).toInt();
    }
    static pair<int, Game> getHistory(int id, int r) {
        if (!getIdentity(id))
            sql->exec(QString("select * from game where id = %1 order by time asc limit 1 offset %2;").arg(id).arg(r));
        else sql->exec(QString("select * from game order by time asc limit 1 offset %1;").arg(r));
        sql->next();
        int cnt = -1;
        int newID = sql->value(++cnt).toInt();
        int mode = sql->value(++cnt).toInt();
        vector<vector<ll>> x(mode, vector<ll>(mode));
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) {
                if (i >= mode || j >= mode) ++cnt;
                else x[i][j] = sql->value(++cnt).toLongLong();
            }
        int attempts = sql->value(++cnt).toInt();
        ll score = sql->value(++cnt).toLongLong();
        string time = string(sql->value(++cnt).toString().toLocal8Bit());
        int countup = sql->value(++cnt).toInt();
        return make_pair(newID, Game(mode, attempts, score, time, countup, x));
    }
    static int getLog(int id) {
        sql->exec(QString("select count(*) from login where id = %1;").arg(id));
        sql->next();
        return sql->value(0).toInt();
    }
    static Time getLoginTime(int id, int r) {
        sql->exec(QString("select loginTime from login where id = %1 order by loginTime asc limit 1 offset %2;").arg(id).arg(r));
        sql->next();
        return Time(string(sql->value(0).toString().toLocal8Bit()));
    }
    static Time getLogoutTime(int id, int r) {
        sql->exec(QString("select logoutTime from login where id = %1 order by loginTime asc limit 1 offset %2;").arg(id).arg(r));
        sql->next();
        if (string(sql->value(0).toString().toLocal8Bit()) == "ONLINE NOW")
            return getLoginTime(id, r);
        return Time(string(sql->value(0).toString().toLocal8Bit()));
    }

    static void setName(int id, string str) {
        sql->exec(QString("update user set name = '%1' where id = %2;").arg(QString::fromLocal8Bit(str.data())).arg(id));
    }
    static void setPassword(int id, string str) {
        sql->exec(QString("update user set password = '%1' where id = %2;").arg(QString::fromLocal8Bit(str.data())).arg(id));
    }
    static void setIdentity(int id, int x) {
        sql->exec(QString("update user set identity = %1 where id = %2;").arg(x).arg(id));
    }
    static void setEnable(int id, int x) {
        sql->exec(QString("update user set enable = %1 where id = %2;").arg(x).arg(id));
    }
    static void setQuestion(int id, string str) {
        sql->exec(QString("update user set question = '%1' where id = %2;").arg(QString::fromLocal8Bit(str.data())).arg(id));
    }
    static void setAnswer(int id, string str) {
        sql->exec(QString("update user set answer = '%1' where id = %2;").arg(QString::fromLocal8Bit(str.data())).arg(id));
    }
    static void setCoins(int id, ll x) {
        sql->exec(QString("update user set coins = %1 where id = %2;").arg(x).arg(id));
    }
    static void setBest(int id, int mode, ll x) {
        sql->exec(QString("update user set best%1 = %2 where id = %3;").arg(mode).arg(x).arg(id));
    }
    static void setLoginTime(int id) {
        sql->exec(QString("insert into login values(%1, '%2', 'ONLINE NOW');").arg(id).arg(QString::fromLocal8Bit(Time().getTime().data())));
    }
    static void setLogoutTime(int id) {
        sql->exec(QString("update login set logoutTime = '%1' where id = %2 and logoutTime = 'ONLINE NOW';").arg(QString::fromLocal8Bit(Time().getTime().data())).arg(id));
    }

    static void addHistory(int id, Game t) {
        QString cmd = "insert into game(id, mode, ";
        for (int i = 0; i < t.getMode(); i++)
            for (int j = 0; j < t.getMode(); j++)
                cmd += QString("posi_%1_%2, ").arg(i).arg(j);
        cmd += QString("attempts, score, time, countup) values(%1, %2, ").arg(id).arg(t.getMode());
        for (int i = 0; i < t.getMode(); i++)
            for (int j = 0; j < t.getMode(); j++)
                cmd += QString("%1, ").arg(t.last[i][j]);
        cmd += QString("%1, %2, '%3', %4);").arg(t.getAttempts()).arg(t.getScore()).arg(QString::fromLocal8Bit(t.getTime().getTime().data())).arg(t.getCountup().getVal());
        sql->exec(cmd);
    }
    static void delHistory(int id, int r) {
        pair<int, Game> g = getHistory(id, r);
        sql->exec(QString("delete from game where id = %1 and time = '%2';").arg(g.first).arg(QString::fromLocal8Bit(g.second.getTime().getTime().data())));
    }

    static int checkRank(int mode, ll score) {
        sql->exec(QString("select score from game where mode = %1 order by score desc;").arg(mode));
        int cnt = 0;
        while (sql->next() && cnt < 50) {
            if (score >= sql->value(0).toInt())
                return cnt;
            cnt++;
        }
        if (cnt < 50) return cnt;
        return -1;
    }
};

class Gifts {
public:
    static bool checkID(string gid) {
        sql->exec(QString("select count(*) from gift where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
        sql->next();
        return sql->value(0).toInt();
    }

    static int getTot() {
        sql->exec("select count(*) from gift;");
        sql->next();
        return sql->value(0).toInt();
    }
    static string getGid(int r) {
        sql->exec(QString("select gid from gift order by gid asc limit 1 offset %1;").arg(r));
        sql->next();
        return string(sql->value(0).toString().toLocal8Bit());
    }

    static int getN(string gid) {
        sql->exec(QString("select n from gift where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
        sql->next();
        return sql->value(0).toInt();
    }
    static int getCoin(string gid) {
        sql->exec(QString("select coin from gift where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
        sql->next();
        return sql->value(0).toInt();
    }
    static Time getDdl(string gid) {
        sql->exec(QString("select ddl from gift where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
        sql->next();
        return Time(string(sql->value(0).toString().toLocal8Bit()));
    }
    static int getGot(string gid) {
        sql->exec(QString("select count(*) from giftrecord where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
        sql->next();
        return sql->value(0).toInt();
    }

    static void setN(string gid, int n) {
        sql->exec(QString("update gift set n = %1 where gid = '%2';").arg(n).arg(QString::fromLocal8Bit(gid.data())));
    }
    static void setCoin(string gid, int coin) {
        sql->exec(QString("update gift set coin = %1 where gid = '%2';").arg(coin).arg(QString::fromLocal8Bit(gid.data())));
    }
    static void setDdl(string gid, Time ddl) {
        sql->exec(QString("update gift set ddl = '%1' where gid = '%2';").arg(QString::fromLocal8Bit(ddl.getTime().data())).arg(QString::fromLocal8Bit(gid.data())));
    }

    static void del(string gid) {
        sql->exec(QString("delete from gift where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
        sql->exec(QString("delete from giftrecord where gid = '%1';").arg(QString::fromLocal8Bit(gid.data())));
    }

    static bool judge(string gid, int id) { //返回这个人是否使用过这个礼包码
        sql->exec(QString("select count(*) from giftrecord where gid = '%1' and id = %2;").arg(QString::fromLocal8Bit(gid.data())).arg(id));
        sql->next();
        return sql->value(0).toInt();
    }
    static bool able(string gid) { //判断礼包是否能领取
        return getGot(gid) < getN(gid);
    }
    static void add(string gid, int id) {
        sql->exec(QString("insert into giftrecord values('%1', %2)").arg(QString::fromLocal8Bit(gid.data())).arg(id));
    }
};

class Honor {
public:
    static int getSize(int mode) {
        sql->exec(QString("select count(*) from game where mode = %1;").arg(mode));
        sql->next();
        return sql->value(0).toInt();
    }
    static pair<int, Game> getRank(int mode, int r) {
        sql->exec(QString("select * from game where mode = %1 order by score desc limit 1 offset %2;").arg(mode).arg(r - 1));
        sql->next();
        int cnt = -1;
        int newID = sql->value(++cnt).toInt();
        ++cnt;
        vector<vector<ll>> x(mode, vector<ll>(mode));
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) {
                if (i >= mode || j >= mode) ++cnt;
                else x[i][j] = sql->value(++cnt).toLongLong();
            }
        int attempts = sql->value(++cnt).toInt();
        ll score = sql->value(++cnt).toLongLong();
        string time = string(sql->value(++cnt).toString().toLocal8Bit());
        int countup = sql->value(++cnt).toInt();
        return make_pair(newID, Game(mode, attempts, score, time, countup, x));
    }
    static void delRank(int mode, int r) {
        pair<int, Game> g = getRank(mode, r);
        sql->exec(QString("delete from game where id = %1 and time = '%2';").arg(g.first).arg(QString::fromLocal8Bit(g.second.getTime().getTime().data())));
    }
};

#endif // CLASSES_H
