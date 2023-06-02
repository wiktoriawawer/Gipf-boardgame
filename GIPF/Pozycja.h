#pragma once
#include <iostream>
#include <string>
using namespace std;
class Pozycja
{
public:
	int kierunek;
	int rozmiar;
	int xSize;
	int ySize;
	int x1;
	int x2;
	int y1;
	int y2;
	int x;
	int y;
	int** litera;
	int** cyfra;
	Pozycja(int rozmiar);
	void uzupelnij_tabele();
	void wypisz();
	int jaki_kierunek(string pozycje);
	int* znajdz_miejsce(int x, int y);
	int znjadz_kierunek(int litera1=0, int cyfra1=0, int litera2=0, int cyfra2=0);

	bool czy_to_pole_startowe(int x, int y);
	bool czy_to_nie_pole_startowe(int litera, int liczba);
	bool sprawdz_pozycje(string pozycje);

	~Pozycja();
	
};

