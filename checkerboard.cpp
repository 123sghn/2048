#include "implementation.h"

Checkerboard::Checkerboard(int n) : N(n)
{
    matrix.resize(N);
    for (int i = 0; i < N; i++)
        matrix[i].resize(N, 0);
    random();
}

Checkerboard::Checkerboard(vector<vector<long long>> x)
{
    matrix = x;
    N = matrix.size();
}

ll Checkerboard::up(void)
{
    ll score = 0; //每一步的得分
    int merge = 0; //每一步合并的次数
    bool move = false; //判断是否为有效移动

    //先把零元素给弄了
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = N - 1; j > 0; j--) //从每一趟中，最后一行开始，从后向前遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一行所有元素
                if (matrix[j - 1][k] == 0 && matrix[j][k] != 0) //如果上一行的这个元素是0，就进行交换
                {
                    swap(matrix[j - 1][k], matrix[j][k]);
                    move = true;
                }

    //然后再考虑合并相同数字的事情
    for (int i = 1; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] == matrix[i - 1][j] && matrix[i][j] != 0 && matrix[i][j] != 4294967296) //如果与上一行元素相等
            {
                matrix[i - 1][j] *= 2; //上一行对应元素×2
                matrix[i][j] = 0; //本行对应元素=0
                score += matrix[i - 1][j]; //得分等于合并后的数字之和
                merge++;
                move = true;
            }

    //然后再把合并后产生的0给弄掉
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = N - 1; j > 0; j--) //从每一趟中，最后一行开始，从后向前遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一行所有元素
                if (matrix[j - 1][k] == 0) //如果上一行的这个元素是0，就进行交换
                    swap(matrix[j - 1][k], matrix[j][k]);

    if (move) //如果移动了，那就随机产生一个新的数字，并且返回分数
    {
        random();
        return score * merge;
    }
    else //如果没有移动,且游戏可以继续进行
        return -1;
}

ll Checkerboard::down(void)
{
    ll score = 0; //每一步的得分
    int merge = 0; //每一步合并的次数
    bool move = false; //判断是否为有效移动

    //先把零元素给弄了
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = 0; j < N - 1; j++) //每一趟中，从第一行开始，从后向前遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一行所有元素
                if (matrix[j + 1][k] == 0 && matrix[j][k] != 0) //如果下一行的这个元素是0，就进行交换
                {
                    swap(matrix[j + 1][k], matrix[j][k]);
                    move = true;
                }

    //然后再考虑合并相同数字的事情
    for (int i = N - 1; i > 0; i--)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] == matrix[i - 1][j] && matrix[i][j] != 0 && matrix[i][j] != 4294967296) //如果与上一行元素相等
            {
                matrix[i][j] *= 2; //本行对应元素×2
                matrix[i - 1][j] = 0; //上一行对应元素=0
                score += matrix[i][j]; //得分等于合并后的数字之和
                merge++;
                move = true;
            }

    //然后再把合并后产生的0给弄掉
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = 0; j < N - 1; j++) //从每一趟中，最后第一行开始，从前向后遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一行所有元素
                if (matrix[j + 1][k] == 0) //如果下一行的这个元素是0，就进行交换
                    swap(matrix[j + 1][k], matrix[j][k]);

    if (move) //如果移动了，那就随机产生一个新的数字，并且返回分数
    {
        random();
        return score * merge;
    }
    else //如果没有移动,且游戏可以继续进行
        return -1;
}

ll Checkerboard::left(void)
{
    ll score = 0; //每一步的得分
    int merge = 0; //每一步合并的次数
    bool move = false; //判断是否为有效移动

    //先把零元素给弄了
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = N - 1; j > 0; j--) //从每一趟中，最后一列开始，从后向前遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一列所有元素
                if (matrix[k][j - 1] == 0 && matrix[k][j] != 0) //如果上一列的这个元素是0，就进行交换
                {
                    swap(matrix[k][j - 1], matrix[k][j]);
                    move = true;
                }

    //然后再考虑合并相同数字的事情
    for (int i = 1; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[j][i] == matrix[j][i - 1] && matrix[j][i] != 0 && matrix[j][i] != 4294967296)//如果与上一列元素相等
            {
                matrix[j][i - 1] *= 2; //上一列对应元素×2
                matrix[j][i] = 0; //本列对应元素=0
                score += matrix[j][i - 1]; //得分等于合并后的数字之和
                merge++;
                move = true;
            }

    //然后再把合并后产生的0给弄掉
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = N - 1; j > 0; j--) //从每一趟中，最后一列开始，从后向前遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一列所有元素
                if (matrix[k][j - 1] == 0) //如果上一列的这个元素是0，就进行交换
                    swap(matrix[k][j - 1], matrix[k][j]);

    if (move) //如果移动了，那就随机产生一个新的数字，并且返回分数
    {
        random();
        return score * merge;
    }
    else //如果没有移动,且游戏可以继续进行
        return -1;
}

ll Checkerboard::right(void)
{
    ll score = 0; //每一步的得分
    int merge = 0; //每一步合并的次数
    bool move = false; //判断是否为有效移动

    //先把零元素给弄了
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = 0; j < N - 1; j++) //从每一趟中，最后第一行开始，从前向后遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一列所有元素
                if (matrix[k][j + 1] == 0 && matrix[k][j] != 0) //如果下一列的这个元素是0，就进行交换
                {
                    swap(matrix[k][j + 1], matrix[k][j]);
                    move = true;
                }

    //然后再考虑合并相同数字的事情
    for (int i = N - 1; i > 0; i--)
        for (int j = 0; j < N; j++)
            if (matrix[j][i] == matrix[j][i - 1] && matrix[j][i] != 0 && matrix[j][i] != 4294967296) //如果与上列元素相等
            {
                matrix[j][i] *= 2; //这一列对应元素×2
                matrix[j][i - 1] = 0; //上一列对应元素=0
                score += matrix[j][i]; //得分等于合并后的数字之和
                merge++;
                move = true;
            }

    //然后再把合并后产生的0给弄掉
    for (int i = 0; i < N - 1; i++) //从i=0开始，共N-1趟
        for (int j = 0; j < N - 1; j++) //从每一趟中，最后第一行开始，从前向后遍历
            for (int k = 0; k < N; k++) //这层循环遍历每一列所有元素
                if (matrix[k][j + 1] == 0) //如果下一列的这个元素是0，就进行交换
                    swap(matrix[k][j + 1], matrix[k][j]);

    if (move) //如果移动了，那就随机产生一个新的数字，并且返回分数
    {
        random();
        return score * merge;
    }
    else //如果没有移动,且游戏可以继续进行
        return -1;
}

pair<int ,int> Checkerboard::random()
{
    pair<int, int>* zero = new pair<int, int>[N * N];
    int k = 0;
    for (int i = 0; i < N; i++) //找到棋盘上为0的位置
        for (int j = 0; j < N; j++)
            if (matrix[i][j] == 0)
            {
                zero[k].first = i;
                zero[k++].second = j;
            }

    pair<int, int> temp;
    if (k == 0) { //如果棋盘满了
        delete[] zero;
        temp.first = temp.second = -1;
        return temp;
    }

    temp = zero[rand() % k]; //随机找一个棋盘上为0的位置
    delete[] zero;

    matrix[temp.first][temp.second] = number(); //在该位置上随机生成一个数字
    return temp;
}

ll Checkerboard::number()
{
    return 1 << (rand() % 2 + 1);
}

ll Checkerboard::get(int r, int c)
{
    return matrix[r][c];
}

void Checkerboard::set(int i, int j, ll t)
{
    matrix[i][j] = t;
}

vector<vector<ll>> Checkerboard::getBoard(void)
{
    return matrix;
}

void Checkerboard::setBoard(vector<vector<ll>>& x)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = x[i][j];
}

int Checkerboard::have()
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j])
                cnt++;
    return cnt;
}

bool Checkerboard::judge(void)
{
    if (have() < N * N)
        return true;

    for (int i = 0; i < N; i++) //遍历行，看每行是否有可以合并的
        for (int j = 0; j < N - 1; j++) {
            if (matrix[i][j] == 4294967296 || matrix[i][j + 1] == 4294967296) continue;
            if (matrix[i][j] == matrix[i][j + 1])
                return true;
        }

    for (int j = 0; j < N; j++) //遍历列，看每列是否有可以合并的
        for (int i = 0; i < N - 1; i++) {
            if (matrix[i][j] == 4294967296 || matrix[i + 1][j] == 4294967296) continue;
            if (matrix[i][j] == matrix[i + 1][j])
                return true;
        }

    return false;
}

ll Checkerboard::getMin()
{
    ll mini = 0x7fffffffffffffff;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j])
                mini = min(mini, matrix[i][j]);
    return mini;
}

ll Checkerboard::getMax()
{
    ll maxi = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j])
                maxi = max(maxi, matrix[i][j]);
    return maxi;
}

void Checkerboard::delMin()
{
    ll mini = getMin();
    int cnt = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] == mini)
                cnt++;
    int row, col;
    if (cnt == N * N)
        row = rand() % N, col = rand() % N;
    else row = col = -1;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] == mini && !(row == i && col == j))
                matrix[i][j] = 0;
}

void Checkerboard::reset()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = 0;
    random();
}

ostream& operator <<(ostream& out, const Checkerboard& c)
{
    for (int i = 0; i < c.N; i++)
    {
        for (int j = 0; j < c.N; j++)
            out << setw(4) << c.matrix[i][j] << " ";
        out << endl;
    }
    return out;
}
