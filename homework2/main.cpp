#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2) { cout << "There aren't any arguments or there are more arguments than we expect."; }
    else
    {
        ifstream file(argv[1]);

        //Извлекаем h0
        string str;
        getline(file, str);
        float h0 = stof(str);

        //Извлекаем vx и vy
        string str1; string str2;
        getline(file, str);
        int i = 0; //Счетчик
        while (str[i] != char(32)) { str1 += str[i]; i += 1; }
        i += 1;
        while (i < str.size()) { str2 += str[i]; i += 1; }
        float vx = stof(str1); float vy = stof(str2);
        
        //Создадим динамические массивы
        int n = 0; //Размер обоих массивов
        vector<float> xk = { 0 }; vector<float> hk = { 0 };
        while (getline(file, str))
        {
            n = n + 1;
            str1 = ""; str2 = "";
            i = 0; //Счетчик
            while (str[i] != char(32)) { str1 += str[i]; i += 1; }
            i += 1;
            while (i < str.size()) { str2 += str[i]; i += 1; }
            xk.push_back(stof(str1)); hk.push_back(stof(str2));
        }
        
        //Теперь физика
        float g = 9.81;
        int gran = 0; //Будущий ответ, пока примем за 0 (номер перегородки)

        float x = 0; float y = h0; //Текущее положение, в цикле будем обновлять
        bool flag = 0; //Показатель столкновения со стенкой
        
        while (true)
        {
            flag = 0;

            if (vx == 0) { break; }
            
            if (vx > 0) { //Идем слева направо
                for (int i = gran + 1; i < xk.size(); i++) {
                    if ((y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x)) >= 0 && (y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x)) <= hk[i]) {
                        flag = 1;
                        y = y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x);
                        vy = vy - g * (xk[i] - x) / vx;
                        vx = -vx;
                        gran = i;
                        x = xk[i];
                    }
                    if (flag == 1) { break; }
                }
                if (y == 0) { break; }
            }

            else {
                if (vx < 0) { //Идем справа налево
                    if (x == 0 || x == xk[1]) { gran = 0; break; }
                    else {
                        for (int i = gran - 1; i > 0; i--) {
                            if ((y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x) >= 0) && (y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x)) <= hk[i]) {
                                flag = 1;
                                y = y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x);
                                vy = vy - g * (xk[i] - x) / vx;
                                vx = -vx;
                                gran = i;
                                x = xk[i];
                            }
                            if (flag == 1) { break; }
                        }
                        if (y == 0) { break; }
                    }
                }
            }

            bool flag1 = 0;

            if (flag == 0) { //То есть столкновения не произошло
                if (vx > 0) {
                    if (gran != xk.size() - 1) {
                        for (int i = gran; i < xk.size() - 1; i++) {
                            if ((y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x)) * (y + vy / vx * (xk[i + 1] - x) - g / (2 * vx * vx) * (xk[i + 1] - x) * (xk[i + 1] - x)) < 0) {
                                gran = i;
                                flag1 = 1;
                                break;
                            }
                        }
                        if (flag1 == 0) { gran = xk.size() - 1; }
                    }
                    else { gran = xk.size() - 1; }
                }

                if (vx < 0) {
                    if (xk.size() > 2) {
                        for (int i = gran; i > 1; i--) {
                            if ((y + vy / vx * (xk[i] - x) - g / (2 * vx * vx) * (xk[i] - x) * (xk[i] - x)) * (y + vy / vx * (xk[i - 1] - x) - g / (2 * vx * vx) * (xk[i - 1] - x) * (xk[i - 1] - x)) < 0) {
                                gran = i - 1;
                                flag1 = 1;
                                break;
                            }
                        }
                        if (flag1 == 0) { gran = 0; }
                    }
                }
                
                break;
            }
            
        }

        cout << gran;
    }
    
    return 0;
}
