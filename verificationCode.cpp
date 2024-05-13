#include "implementation.h"
//using namespace std;

pair<string, int> getVerificationCode(void) //计算算式，并且返回算式和计算结果
{
    //return make_pair("÷", 5);

    bool flag = true;
    int a[3], op[2], ans;
    string s;
    string opera[4] = { "+", "-", "×", "÷" };
    opera[2] = string(QString("×").toLocal8Bit());
    opera[3] = string(QString("÷").toLocal8Bit());

    while (flag) {
        flag = false;
        for (int i = 0; i < 3; i++) a[i] = rand() % 10;
        for (int i = 0; i < 2; i++) op[i] = rand() % 4;

        try {
            switch (op[0]) { //第一个符号
            case 0: //+
                switch (op[1]) { //第二个符号
                case 0: ans = a[0] + a[1] + a[2]; break;
                case 1: ans = a[0] + a[1] - a[2]; break;
                case 2: ans = a[0] + a[1] * a[2]; break;
                case 3: //÷
                    if (!a[2]) throw 2;
                    if (a[1] / a[2] != (double)a[1] / a[2]) throw 3;
                    ans = a[0] + a[1] / a[2];
                    break;
                }
                break;
            case 1: //-
                switch (op[1]) { //第二个符号
                case 0: //+
                    if (a[0] < a[1]) throw 1;
                    ans = a[0] - a[1] + a[2];
                    break;
                case 1: ans = a[0] - a[1] - a[2]; break;
                case 2: ans = a[0] - a[1] * a[2]; break;
                case 3: //÷
                    if (!a[2]) throw 2;
                    if (a[1] / a[2] != (double)a[1] / a[2]) throw 3;
                    ans = a[0] - a[1] / a[2];
                    break;
                }
                break;
            case 2: //×
                switch (op[1]) { //第二个符号
                case 0: ans = a[0] * a[1] + a[2]; break;
                case 1: ans = a[0] * a[1] - a[2]; break;
                case 2: ans = a[0] * a[1] * a[2]; break;
                case 3: //÷
                    if (!a[2]) throw 2;
                    ans = a[0] * a[1];
                    if (ans / a[2] != (double)ans / a[2]) throw 3;
                    ans = a[0] * a[1] / a[2];
                    break;
                }
                break;
            case 3: //÷
                if (!a[1]) throw 2;
                if (a[0] / a[1] != (double)a[0] / a[1]) throw 3;
                switch (op[1]) { //第二个符号
                case 0: ans = a[0] / a[1] + a[2]; break;
                case 1: ans = a[0] / a[1] - a[2]; break;
                case 2: ans = a[0] / a[1] * a[2]; break;
                case 3: //÷
                    if (!a[2]) throw 2;
                    ans = a[0] / a[1];
                    if (ans / a[2] != (double)ans / a[2]) throw 3;
                    ans = a[0] / a[1] / a[2];
                    break;
                }
                break;
            }
            if (ans < 0) throw 1;
        }
        catch (int) {
            flag = true;
        }
    }

    ostringstream os;
    os << a[0] << " " << opera[op[0]] << " " << a[1] << " " << opera[op[1]] << " " << a[2];
    s = os.str();

    return make_pair(s, ans);
}
