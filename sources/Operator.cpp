#include "Operator.h"
Operator::Operator() {
    name = "";
    col = 0;
    plan = nullptr;
    good = 1;
}
Operator::Operator(std::string imya, int num, tarif* temp, bool okey) {
    name = imya;
    col = num;
    plan = temp;
    good = okey;
}
Operator::Operator(const Operator& cool) {
    name = cool.name;
    col = cool.col;
    plan = cool.plan;
    good = cool.good;
}
Operator::Operator(Operator&& cool) {
    name = std::move(cool.name);
    good = std::move(cool.good);
    col = std::move(cool.col);
    plan = nullptr;
    std::swap(plan, cool.plan);
}
Operator::~Operator() {}
Operator& Operator::operator = (const Operator& cool) {
    if (this != &cool) {
        name = cool.name;
        col = cool.col;
        plan = cool.plan;
        good = cool.good;
    }
    return *this;
}
Operator& Operator::operator = (Operator&& cool) {
    if (this != &cool) {
        name = std::move(cool.name);
        good = std::move(cool.good);
        col = std::move(cool.col);
        plan = nullptr;
        std::swap(plan, cool.plan);
    }
    return *this;
}
void Operator::set_col(int k) {
    col = k;
    plan = new tarif[k];
}
void Operator::tarif_filter(int a, int b, int c, int d) {
    for (int i = 0; i < col; i++) {
        plan[i].check(a, b, c, d);
    }
}
void Operator::print(std::ostream & out) {
    out << "Оператор " << name << "\n";
    int k = 0;
    for (int i = 0; i < col; i++) {
        if(plan[i].getGoodies() == true){plan[i].print(out);
        k++;}
    }
    if (k == 0) out << "К сожалению, у данного оператора нет тарифов, удовлетворяющих вашим фильтрам\n";
}