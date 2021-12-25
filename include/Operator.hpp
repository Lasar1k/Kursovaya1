#ifndef _OPERATOR_H
#define _OPERATOR_H

#include <iostream>
#include "tarif.h"
class Operator {
public:
	std::string name;
	int col; // число тарифов у оператора
	tarif* plan;
	bool good; // чёрный список
public:
	Operator();
	Operator(std::string imya, int num, tarif* temp, bool okey);
	Operator(const Operator& temp);
	Operator(Operator&& temp);
	~Operator();
	Operator& operator = (const Operator& cool);
	Operator& operator = (Operator&& cool);
	void set_col(int k);
	void tarif_filter(int a, int b, int c, int d);
	void print(std::ostream & out);
};
#endif