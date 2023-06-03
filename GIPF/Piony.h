#pragma once
#include <list>
#include <iostream>
#include <cstddef>
using namespace std;
class Punkt;
class Pion;
class Piony
{
public:
	int ilosc_pionow;
	list<Pion*> lista_pionow;
	Piony();
	~Piony();
	void wypisz();

};
class Punkt {
public:
	int x;
	int y;
	Punkt(int x, int y);
	~Punkt();
};
class Pion {
public:
	list<Punkt*> pion;
	int ilosc_w;
	int ilosc_b;
	Pion();
	void wypisz();
	
	
};