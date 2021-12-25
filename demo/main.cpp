#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "tarif.cpp"
#include "Operator.cpp"
int Find_with_name(std::vector<Operator> & vec, std::string temp) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].name == temp) return i;
    }
    std::cerr << "Ошибка: такого оператора не существует";
}
void Filter(std::vector<Operator>& vec, int a, int b, int c, int d) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i].tarif_filter(a, b, c, d);
    }
}
void print(std::vector<Operator>& vec, std::ostream & out) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i].print(out);
        std::cout << "\n";
    }
}
double getWeight(double min_price, double price, double max_price) { // для минут, гб, смс
    double k = (price - min_price) / (max_price - min_price) * 10;
    if (k > 10) return 10;
    else if (k < 0) return 0;
    else return k;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int N; // количество операторов
    std::vector<Operator> TeleOpers;
    std::ifstream in("Входные данные.txt");
    if (!in) {
        std::cerr << "Ошибка: не удалось загрузить данные об операторах";
    }
    in >> N;//вводим количество операторов
    TeleOpers.resize(N);
    int temp_1, temp_2, temp_3, temp_4, temp_5, ka;
    bool temp_6;
    for (int i = 0; i < N; i++) {
        in >> TeleOpers[i].name;
        in >> ka; // количество тарифов у i-того оператора
        TeleOpers[i].set_col(ka);
        for (int j = 0; j < TeleOpers[i].col; j++) {
            in >> temp_1;
            in >> temp_2;
            in >> temp_3;
            in >> temp_4;
            in >> temp_5;
            in >> temp_6;
            TeleOpers[i].plan[j].set(temp_1, temp_2, temp_3, temp_4, temp_5, temp_6);
        }
    }

    std::string User_prev_op;
    int num;
    char a;
    std::cout << "Ваш предыдущий оператор вам нравился? Y/N\n";
    std::cin >> a;
    if (a == 'N') {
        std::cout << "Введите название вашего предыдущего оператора чтобы мы его не предлагали\n";
        std::cin >> User_prev_op;
        num = Find_with_name(TeleOpers, User_prev_op);
        TeleOpers.erase(TeleOpers.begin() + num);
    }
    int price, minutes, gb, sms;
    std::cout << "Цена вашего тарифа должна быть не более: ";
    std::cin >> price;
    std::cout << std::endl << "Минимальное количество минут должно быть равно: ";
    std::cin >> minutes;
    std::cout << std::endl << "Минимальное количество гигабайт в тарифе: ";
    std::cin >> gb;
    std::cout << std::endl << "Минимальное количество смс: ";
    std::cin >> sms;
    std::cout << std::endl;

    Filter(TeleOpers, price, minutes, gb, sms);
    std::cout << "Тарифные планы, удовлетворяющие вашим запросам: \n";
    print(TeleOpers, std::cout);
   
    std::vector<double> tarif_weights(4);
    double min_p = 10000, max_p = 0, min_g = 10000, max_g = 0, min_s = 10000, max_s = 0, min_m = 10000, max_m = 0;
    for (int i = 0; i < TeleOpers.size(); i++) {
        if (TeleOpers[i].good == 1) {
            for (int j = 0; j < TeleOpers[i].col; j++) {
                if (TeleOpers[i].plan[j].getGoodies() == 1) {
                    if (TeleOpers[i].plan[j].getStuff('p') > max_p) max_p = TeleOpers[i].plan[j].getStuff('p');
                    if (TeleOpers[i].plan[j].getStuff('p') < min_p) min_p = TeleOpers[i].plan[j].getStuff('p');
                    if (TeleOpers[i].plan[j].getStuff('g') > max_g) max_g = TeleOpers[i].plan[j].getStuff('g');
                    if (TeleOpers[i].plan[j].getStuff('g') < min_g) min_g = TeleOpers[i].plan[j].getStuff('g');
                    if (TeleOpers[i].plan[j].getStuff('m') > max_m) max_m = TeleOpers[i].plan[j].getStuff('m');
                    if (TeleOpers[i].plan[j].getStuff('m') < min_m) min_m = TeleOpers[i].plan[j].getStuff('m');
                    if (TeleOpers[i].plan[j].getStuff('s') > max_s) max_s = TeleOpers[i].plan[j].getStuff('s');
                    if (TeleOpers[i].plan[j].getStuff('s') < min_s) min_s = TeleOpers[i].plan[j].getStuff('s');
                }
            }
        }
    }

    tarif_weights[0] = 9;
    tarif_weights[1] = 5;
    tarif_weights[2] = 7;
    tarif_weights[3] = 3;

    double k = 0;

    std::vector<std::vector<double>> tabl;
    tabl.resize(4);
    int m = 0; // общее количество подходящих тарифов// число столбцов в таблице с 4 строками
    for (int i = 0; i < TeleOpers.size(); i++) {
        if (TeleOpers[i].good == 1) {
            for (int j = 0; j < TeleOpers[i].col; j++) {
                if (TeleOpers[i].plan[j].getGoodies() == 1) {
                    k = (max_p - TeleOpers[i].plan[j].getStuff('p')) / (max_p - min_p) * 10;
                    if (k > 10) k = 10;
                    else if (k < 0)  k = 0;
                    tabl[0].push_back(k);
                    tabl[1].push_back(getWeight(min_m, TeleOpers[i].plan[j].getStuff('m'), max_m));
                    tabl[2].push_back(getWeight(min_g, TeleOpers[i].plan[j].getStuff('g'), max_g));
                    tabl[3].push_back(getWeight(min_s, TeleOpers[i].plan[j].getStuff('s'), max_s));
                    m++;
                }
            }
        }
    }
    double MAX_t = 0, MIN_t = 10000;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 4; j++) {
            if (tabl[j][i] < MIN_t) MIN_t = tabl[j][i];
            if (tabl[j][i] > MAX_t) MAX_t = tabl[j][i];
        }
        for (int j = 0; j < 4; j++) {
            tabl[j][i] = (tabl[j][i] - MIN_t) / (MAX_t - MIN_t);
        }
        MAX_t = 0; MIN_t = 10000;
    }

    std::vector<double> weightsss(m);
    for (int i = 0; i < m; i++) {
        weightsss[i] = tabl[0][i] * tarif_weights[0] + tabl[1][i] * tarif_weights[1] + tabl[2][i] * tarif_weights[2] + tabl[3][i] * tarif_weights[3];
    }
    double kaaa = 0;
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (weightsss[i] > kaaa) { kaaa = weightsss[i]; count = i; }
    }

    std::cout << "\nС учётом ваших предпочтений мы предлагаем вам приобрести \n";

    int count_new = -1;
    for (int i = 0; i < TeleOpers.size(); i++) {
        if (TeleOpers[i].good == 1) {
            for (int j = 0; j < TeleOpers[i].col; j++) {
                if (TeleOpers[i].plan[j].getGoodies() == 1) {
                    count_new++;
                    if (count_new == count) {
                        std::cout << "Тариф " << TeleOpers[i].name << "\n";
                        TeleOpers[i].plan[j].print(std::cout);
                        return 0;
                    }
                }
            }
        }
    }
}