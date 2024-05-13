#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <vector>
#include <iostream>
using namespace std;
#define ll long long

class Checkerboard
{
private:
    int N; //表示矩阵阶数
    vector<vector<ll>> matrix;

public:
    Checkerboard(int N);
    Checkerboard(vector<vector<ll>>);

    ll up(void);
    ll down(void);
    ll left(void);
    ll right(void);
    pair<int, int> random(); //随机在棋盘上生成一个数字
    ll number(); //按照概率随机

    ll get(int, int); //读取一个格子
    void set(int, int, ll); //设置一个格子
    vector<vector<ll>> getBoard(); //返回棋盘
    void setBoard(vector<vector<ll>>&); //设置棋盘

    int have(void); //判断棋盘上还剩多少个数字
    bool judge(void); //判断是否为死局

    ll getMin(void); //获得棋盘上的最小数字
    ll getMax(void); //获得棋盘上的最大数字
    void delMin(void); //删除棋盘上最小的数字

    void reset();

    friend ostream& operator << (ostream& out, const Checkerboard& c);
};

#endif // CHECKERBOARD_H
