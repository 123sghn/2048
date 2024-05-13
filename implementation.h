#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

//#define TESTING //用于调试过程中的快速登录、清楚登录记录

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
using namespace std;

#include "classes.h"
#include "checkerboard.h"

extern map<ll, string> colorStyle;
extern map<ll, int> sizeStyle[6];
extern bool systemclose;

extern QSqlDatabase db;
extern QSqlQuery* sql;

pair<string, int> getVerificationCode(void); //生成随机的验证码

string intToString(int);
string intToString(long long);
string longToString(long long);
string numToString(long long);
int stringToInt(string);
QString intToQString(int);
QString intToQString(long long);
QString longToQString(long long);
QString numToQString(long long);
pair<bool, int> isNumber(QString);

void initColor();
void initSize();
QString getStyle(long long, int);

#define ll long long
#define MAX_STEP 100 //最大能储存的步数
#define ADMIN_REGISTER "_ADMIN_REGISTER_ACCOUNT_" //新建管理员账号的密钥
#define DEFAULT_SEAL_DURATION 1 //默认封号的天数
#define eps 1e-9
#define cal(x) ((ll)(sqrtl(x / 10) + eps)) //从分数转换为加的金币数量

#endif // IMPLEMENTATION_H
