#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    float xl = 0; float yl = 0; float xr = 0; float yr = 0; //Будущие ответы

    string xyn;
    string xy; //Здесь будем хранить текущие координаты
    ifstream file("in.txt");

    getline(file, xyn); //Получили координаты направляющего вектора (пока что строку)
    string x_n = ""; string y_n = "";

    int i = 0; //Счетчик
    while (xyn[i] != char(32)) { x_n += xyn[i]; i += 1; }

    i += 1;
    while (i < xyn.size()) { y_n += xyn[i]; i += 1; }

    float xn = stod(x_n); float yn = stod(y_n); //Координаты направляющего вектора в виде float
    float cosl = round((xn * xn + yn * yn) / (sqrt(xn * xn + yn * yn) * sqrt(xn * xn + yn * yn)) * 10000000000) / 10000000000;
    float cosp = round((xn * xn + yn * yn) / (sqrt(xn * xn + yn * yn) * sqrt(xn * xn + yn * yn)) * 10000000000) / 10000000000;

    while (getline(file, xy)) {
        if ((xy == "") || (xy[0] == char(32))) { continue; }

        string xv = ""; string yv = "";

        i = 0; //Счетчик
        while (xy[i] != char(32)) { xv += xy[i]; i += 1; }

        i += 1;
        while (i < xy.size()) { yv += xy[i]; i += 1; }

        float x = stod(xv); float y = stod(yv); //На текущей итерации работаем с этими значениями

        if (yn * x < xn * y) {
            float vsl = round((xn * x + yn * y) / (sqrt(xn * xn + yn * yn) * sqrt(x * x + y * y)) * 10000000000) / 10000000000;
            if (vsl <= cosl) { cosl = vsl; xl = x; yl = y; }
        }

        if (yn * x >= xn * y) {
            float vsp = round((xn * x + yn * y) / (sqrt(xn * xn + yn * yn) * sqrt(x * x + y * y)) * 10000000000) / 10000000000;
            if (vsp <= cosp) { cosp = vsp; xr = x; yr = y; }
        }
    }

    cout << "Leftmost: " << xl << " " << yl << endl;
    cout << "Rightmost: " << xr << " " << yr << endl;

    ofstream out_file("result.txt");
    out_file << "Leftmost: " << xl << " " << yl << endl;
    out_file << "Rightmost: " << xr << " " << yr << endl;

    return 0;
}
