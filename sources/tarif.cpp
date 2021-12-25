include "tarif.h"
tarif::tarif() : ID(0), price(0), minutes(0), gb(0), sms(0), good(0) {}
tarif::tarif(int id, int a, int b, int c, int d, bool e, bool f) : ID(id), price(a), minutes(b), gb(c), sms(d), good(f) {}
tarif::tarif(const tarif& cool) 
{
    ID = cool.ID;
    price = cool.price;
    minutes = cool.minutes;
    gb = cool.gb;
    sms = cool.sms;
    good = cool.good;
}
tarif::tarif(tarif&& cool) 
{
    ID = std::move(cool.ID);
    price = std::move(cool.price);
    minutes = std::move(cool.minutes);
    gb = std::move(cool.gb);
    sms = std::move(cool.sms);
    good = std::move(cool.good);
}
tarif& tarif::operator = (const tarif& cool) 
{
    if (this != &cool) {
        ID = cool.ID;
        price = cool.price;
        minutes = cool.minutes;
        gb = cool.gb;
        sms = cool.sms;
        good = cool.good;
    }
    return *this;
}
tarif& tarif::operator = (tarif&& cool) 
{
    if (this != &cool) {
        ID = std::move(cool.ID);
        price = std::move(cool.price);
        minutes = std::move(cool.minutes);
        gb = std::move(cool.gb);
        sms = std::move(cool.sms);
        good = std::move(cool.good);
    }
    return *this;
}
void tarif::set(int id, int a, int b, int c, int d, bool e) {
    ID = id;
    price = a;
    minutes = b;
    gb = c;
    sms = d;
    good = 1;
}
void tarif::check(int a, int b, int c, int d) {
    if (price > a || minutes < b || gb < c || sms < d) good = 0;
    else good = 1;
}
void tarif::print(std::ostream & out) {
    out << "Тариф №" << ID;
    out << "\nЕжемесячная плата: " << price << " рублей\n";
    out << "Число минут: " << minutes << "\n";
    out << "Число гигабайт: " << gb << "\n";
    out << "Число смс: " << sms << "\n";
}
bool tarif::getGoodies() {
    return good;
}
int tarif::getStuff(char a) {
    switch (a) {
        case 'p': return price;
        case 'm': return minutes;
        case 'g': return gb;
        case 's': return sms;
    }
}