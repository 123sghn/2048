#include "implementation.h"
#include <QString>

string intToString(int i) {
    ostringstream os;
    os << i;
    return os.str();
}

string intToString(ll i) {
    if (!i) return string("0");
    ll t = i / 10;
    int cnt = 0;
    while (t) {
        t /= 1000;
        cnt++;
    }
    cnt--;
    if (cnt <= 0) return intToString((int)i);
    ll divisor = pow(1000, cnt) / 100;
    t = i / divisor;
    double tt = (double)t / 100;
    string ret;
    ostringstream os;
    os << fixed << setprecision(2) << tt;
    ret = os.str();
    switch (cnt) {
    case 1: ret += "k"; break; //10^3
    case 2: ret += "M"; break; //10^6
    case 3: ret += "G"; break; //10^9
    case 4: ret += "T"; break; //10^12
    case 5: ret += "P"; break; //10^15
    case 6: ret += "E"; break; //10^18
    }
    return ret;
}

string longToString(ll i) {
    ostringstream os;
    os << i;
    return os.str();
}

string numToString(ll i) {
    int base = 5;
    string t = longToString(i);
    string ret = "";
    while ((int)t.length() > base) {
        ret += t.substr(0, base) + '\n';
        t = t.substr(base);
    }
    ret += t;
    return ret;
}

int stringToInt(string s) {
    istringstream is(s);
    int t;
    is >> t;
    return t;
}

QString intToQString(int i) {
    return QString::fromLocal8Bit(intToString(i).data());
}

QString intToQString(ll i) {
    return QString::fromLocal8Bit(intToString(i).data());
}

QString longToQString(ll i) {
    return QString::fromLocal8Bit(longToString(i).data());
}

QString numToQString(ll i) {
    if (i == 4294967296) return "∞";
    return QString::fromLocal8Bit(numToString(i).data());
}

pair<bool, int> isNumber(QString s) //返回输入的是否是数字，以及数字的数值
{
    bool number;
    int val = s.toInt(&number);
    return make_pair(number, val);
}
