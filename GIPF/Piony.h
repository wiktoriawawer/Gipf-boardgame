#pragma once
#include <list>
#include <iostream>
#include <cstddef>
using namespace std;
class Punkt;

class Piony
{
public:
	int ilosc_pionow;
	//list<list <Punkt>> lista_pionow;
	Piony();
	~Piony();

};
class Punkt {
public:
	int x;
	int y;
	Punkt(int x, int y);
	~Punkt();
};
