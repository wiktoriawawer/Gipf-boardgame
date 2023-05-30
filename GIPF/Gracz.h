#pragma once
#include<string>
#include<list>
using namespace std;
class Gracz
{	
public:
	int ilosc_rezerwa;
	int ilosc_na_planszy;
	int max_ilosc_pionkow; //GW,GB
	//lista pozycji na plnaszy 
	string kolor;
	Gracz();
	bool sprawdz_ilosc_pionkow();
};

