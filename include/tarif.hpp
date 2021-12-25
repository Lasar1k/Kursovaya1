#pragma once
#include <iostream>
class tarif {
    int ID;
    int price;
    int minutes;
    int gb;
    int sms;
    bool good;
public:
    tarif();
    tarif(int id, int a, int b, int c, int d, bool e, bool f);
    tarif(const tarif& cool);
    tarif(tarif&& cool);
    ~tarif() {};
    tarif& operator = (const tarif& cool);
    tarif& operator = (tarif&& cool);
    void set(int id, int a, int b, int c, int d, bool e);
    void check(int a, int b, int c, int d);
    void print (std::ostream & out);
    bool getGoodies();
    int getStuff(char a);
};