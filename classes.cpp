#include "implementation.h"

//Duration
string Duration::getLen() const
{
    ostringstream os;
    if (d) os << d << "d " << h << "h " << min << "min " << s << "s";
    else if (h) os << h << "h " << min << "min " << s << "s";
    else if (min) os << min << "min " << s << "s";
    else os << s << "s";
    return os.str();
}

Duration Duration::operator + (const Duration& t) const
{
    Duration ans(d + t.d, h + t.h, min + t.min, s + t.s);
    while (ans.s >= 60) ans.s -= 60, ans.min++;
    while (ans.min >= 60) ans.min -= 60, ans.h++;
    while (ans.h >= 24) ans.h -= 24, ans.d++;
    return ans;
}

bool Duration::operator < (const Duration& tt) const
{
    if (d != tt.d) return d < tt.d;
    if (h != tt.h) return h < tt.h;
    if (min != tt.min) return min < tt.min;
    return s < tt.s;
}

bool Duration::operator == (const Duration& tt) const
{
    return d == tt.d && h == tt.h && min == tt.min && s == tt.s;
}

//Time
Time::Time()
{
    time_t timep;
    struct tm* p; //时间信息存储在tm结构里
    time(&timep);
    p = localtime(&timep);
    y = p->tm_year + 1900;
    m = p->tm_mon + 1;
    d = p->tm_mday;
    h = p->tm_hour;
    min = p->tm_min;
    s = p->tm_sec;
}

Time::Time(int y, int m, int d, int h, int min, int s) :
    y(y), m(m), d(d), h(h), min(min), s(s)
{

}

Time::Time(string str)
{
    y = stoi(str.substr(0, 4));
    m = stoi(str.substr(5, 2));
    d = stoi(str.substr(8, 2));
    h = stoi(str.substr(11, 2));
    min = stoi(str.substr(14, 2));
    s = stoi(str.substr(17, 2));
}


void Time::setTime(int yy, int mm, int dd, int hh, int mmin, int ss)
{
    y = yy, m = mm, d = dd, h = hh, min = mmin, s = ss;
}

void Time::setTime(const Time& t)
{
    y = t.y, m = t.m, d = t.d, h = t.h, min = t.min, s = t.s;
}

string Time::getTime() const
{
    ostringstream os;
    os << setw(4) << setfill('0') << y << "-" <<
          setw(2) << setfill('0') << m << "-" <<
          setw(2) << setfill('0') << d << " " <<
          setw(2) << setfill('0') << h << ":" <<
          setw(2) << setfill('0') << min << ":" <<
          setw(2) << setfill('0') << s;
    return os.str();
}

Time Time:: operator + (int day) //往后加多少天，考虑闰年这些事情
{
    Time t = *this;

    int month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    while (day)
    {
        if (t.y % 400 == 0 || (t.y % 4 == 0 && t.y % 100 != 0)) //判断闰年
            month[2] = 29;
        else month[2] = 28;

        if (day + t.d > month[t.m])
        {
            day = day + t.d - month[t.m] -1;
            t.m++;
            t.d = 1;
        }
        else
        {
            t.d += day;
            day = 0;
        }

        if (t.m > 12)
        {
            t.m -= 12;
            t.y++;
        }
    }
    return t;
}

Time Time::operator + (const Duration& t) const {
    int month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (y % 400 == 0 || (y % 4 == 0 && y % 100)) month[2] = 29;
    else month[2] = 28;

    Time ans(y, m, d + t.d, h + t.h, min + t.min, s + t.s);
    while (ans.s >= 60) ans.min++, ans.s -= 60;
    while (ans.min >= 60) ans.h++, ans.min -= 60;
    while (ans.h >= 24) ans.d++, ans.h -= 24;

    while (ans.d > month[ans.m]) {
        ans.d -= month[ans.m], ans.m++;
        while (ans.m > 12) {
            ans.y++, ans.m -= 12;
            if (ans.y % 400 == 0 || (ans.y % 4 == 0 && ans.y % 100)) month[2] = 29;
            else month[2] = 28;
        }
    }
    return ans;
}

Duration Time::operator - (const Time& t) const {
    if (*this < t) return Duration();

    int month[13] = { 31,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (y % 400 == 0 || (y % 4 == 0 && y % 100)) month[2] = 29;
    else month[2] = 28;

    Duration ans;
    Time a(*this), b(t);
    if (a.s >= b.s) ans.s = a.s - b.s;
    else ans.s = a.s + 60 - b.s, a.min--;
    if (a.min >= b.min) ans.min = a.min - b.min;
    else ans.min = a.min + 60 - b.min, a.h--;
    if (a.h >= b.h) ans.h = a.h - b.h;
    else ans.h = a.h + 24 - b.h, a.d--;
    if (a.d >= b.d) ans.d = a.d - b.d;
    else a.m--, ans.d = a.d + month[a.m] - b.d;
    if (!a.m) a.m += 12, a.y--;

    if (b.y % 400 == 0 || (b.y % 4 == 0 && b.y % 100)) month[2] = 29;
    else month[2] = 28;
    while (a.y != b.y || a.m != b.m) {
        ans.d += month[b.m++];
        if (b.m > 12) {
            b.m -= 12, b.y++;
            if (b.y % 400 == 0 || (b.y % 4 == 0 && b.y % 100)) month[2] = 29;
            else month[2] = 28;
        }
    }
    return ans;
}

bool Time::operator < (const Time& tt) const
{
    if (y != tt.y) return y < tt.y;
    if (m != tt.m) return m < tt.m;
    if (d != tt.d) return d < tt.d;
    if (h != tt.h) return h < tt.h;
    if (min != tt.min) return min < tt.min;
    return s < tt.s;
}

bool Time::operator ==(const Time& tt) const
{
    return y == tt.y && m == tt.m && d == tt.d && h == tt.h && min == tt.min && s == tt.s;
}

//Countup
void Countup::reset()
{
    h = m = s = 0;
}

string Countup::get() const
{
    ostringstream os;
    os << setw(2) << setfill('0') << h << ":" <<
          setw(2) << setfill('0') << m << ":" <<
          setw(2) << setfill('0') << s;
    return os.str();
}

Countup& Countup::operator ++ ()
{
    s++;
    if (s >= 60) s -= 60, m++;
    if (m >= 60) m -= 60, h++;
    return *this;
}

bool Countup::operator < (const Countup& tc) const
{
    if (h != tc.h) return h < tc.h;
    if (m != tc.m) return m < tc.m;
    return s < tc.s;
}

bool Countup::operator == (const Countup& tc) const
{
    return h == tc.h && m == tc.m &&  s == tc.s;
}
