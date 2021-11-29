#include <iostream>
#include <cmath>
#include <fstream>


int main(int argc, char** argv) {
    double y_0 = 0, v_x = 0, v_y = 0, g = 9.81, answer = 0;
    double check, tmp, t_collision;
    int direction = 1;
    int n = 0;
    std::ifstream in_prev(R"(C:\Users\Thomas_Maddison\CLionProjects\Homework2\in.txt)");
    if (in_prev.is_open()){
        in_prev >> y_0;
        in_prev >> v_x;
        in_prev >> v_y;
        double t_end = (v_y+sqrt(v_y*v_y+2*g*y_0))/g;
        while ((!in_prev.eof()) && (check <= v_x*t_end)) {
            in_prev >> check;
            in_prev >> tmp;
            n++;
        }
    }
    in_prev.close();
    auto*X = new double[n];
    auto*Y = new double[n];

    std::ifstream in(R"(C:\Users\Thomas_Maddison\CLionProjects\Homework2\in.txt)");
    if (in.is_open()){
        in >> y_0;
        in >> v_x;
        in >> v_y;
        int i = 0;
        double t_end = (v_y+sqrt(v_y*v_y+2*g*y_0))/g;
        while ((!in.eof()) && (X[i - 1] <= v_x*t_end)) {
            in >> X[i];
            in >> Y[i];
            i++;
        }
    }
    in.close();

    double A_x = v_x, A_y = v_y, B_x = 0, B_y = y_0;
    double t_end = (v_y+sqrt(v_y*v_y+2*g*y_0))/g;

    for (int i = 0; (i >= 0) && (i <= n - 1); i = i + direction){
        t_collision = (X[i] - B_x)/A_x;
        if (t_collision <= t_end) {
            if ((-g * t_collision * t_collision/2 + A_y * t_collision + B_y) <= Y[i]) {
                B_x = 2*A_x*t_collision + B_x;
                A_x = -A_x;
                direction = (-1)*direction;
            }
        }else{
            break;
        }
    }

    double coordinate_final = A_x*t_end + B_x;

    for (int i = 0; i <= n - 2; i++){
        if ((coordinate_final >= X[i]) && (coordinate_final <= X[i + 1])){
            answer = i + 1;
            break;
        }
    }

    if (coordinate_final > X[n - 1]){
        answer = n;
    }

    if (coordinate_final < X[0]){
        answer = 0;
    }

    delete[] X;
    delete[] Y;
    std::cout << answer << std::endl;
}
