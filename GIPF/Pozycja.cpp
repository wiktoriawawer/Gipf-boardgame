#include "Pozycja.h"
#include <iostream>
#define GORAPRAWO 1
#define PRAWO 2
#define DOLPRAWO 3
#define DOLLEWO 4
#define LEWO 5 
#define GORALEWO 6
using namespace std;
Pozycja::Pozycja(int rozmiar)
{
	xSize = 4 * rozmiar + 1;
	this->rozmiar = rozmiar;
	ySize = 2 * rozmiar + 1;
	kierunek = ' ';
	//inicjalizacja pamieci 
	this->litera = (int**)malloc(xSize * sizeof(int*));
	this->cyfra= (int**)malloc(xSize * sizeof(int*));
	for (int i = 0; i < xSize; i++) {
		litera[i] = (int*)malloc(ySize * sizeof(int));
		cyfra[i] = (int*)malloc(ySize * sizeof(int));
	}

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			litera[x][y] = -1;
			cyfra[x][y] = -1;
		}
		
	}
	this->uzupelnij_tabele();
}

void Pozycja::uzupelnij_tabele() {
	//WERSJA STARA 
	/*
	//sprawdzanie /
	//ustawienie watosci pocztekowych 
	int x = 0;
	int y = rozmiar;
	int x_p = x;
	int y_p = y;
	int litera_ = 0;
	int  cyfra_= 1;
	int ilerazy = rozmiar + 1;
	while (true) {

		x = x_p;
		y = y_p;
		//zaczynamy od elemnetu najbardziej wysunietego /
		//iterujemy do gory w prawo

		//po dojsciu do wiersza zerowego 
		//cofamy sie do do³u itd 
		litera_++;
		cyfra_ = 1;
		while (true) {
			//cout << x << ", " << y <<", "<< litera_ << ", " << cyfra_ << endl;
			cyfra[x][y] = cyfra_;
			litera[x][y] = litera_;

			if (y - 1 >= 0 && x + 1 < xSize) {
				cyfra_++;
				y--;
				x++;
			}
			else {
				break;
			}

		}

		//if (y_p y_p == ySize - 1 && x_p==)
		if (y_p == ySize - 1 && x_p == 4*rozmiar) {
			break;
		}
		else {
			if (y_p + 1 < ySize) {
				y_p++;
				x_p++;
			}
			else {
				x_p += 2;
			}

		}
	}
	*/
	int x = 0,x_p=0,y_p=rozmiar;
	int y = rozmiar;
	int cyfra_ = 1,licznik;
	int cyframax=rozmiar;
	//j odpowiada za litere 
	for (int j = 0; j < 2 * rozmiar + 1; j++) {
		// i odpowiada za liczbe 
		cyfra_ = 1;
		if (j < rozmiar + 1) {
			cyframax++;
		}
		else {
			cyframax--;
		}
		licznik = cyframax;

		x = x_p;
		y = y_p;
		while(true) {

			if (licznik == 0) {
				break;
			}
			cyfra[x][y] = cyfra_;
			litera[x][y] = j+1;
			if (y - 1 >= 0 && x + 1 < xSize) {
				y--;
				x++;
				cyfra_++;
				licznik--;
				
			}
			else {
				break;
			}
		}

		if (y_p == ySize - 1 && x_p == 4 * rozmiar) {
			break;
		}
		else {
			if (y_p + 1 < ySize) {
				y_p++;
				x_p++;
			}
			else {
				x_p += 2;
			}

		}


	}


}
void Pozycja::wypisz() {
	for (int y = 0; y < ySize; y++) {
		for (int x = 0; x < xSize; x++) {
			if (litera[x][y] == -1) {
				cout << " ";
			}else 
				cout << litera[x][y];
		}
		cout << endl;
	}
	for (int y = 0; y < ySize; y++) {
		for (int x = 0; x < xSize; x++) {
		
			if (cyfra[x][y] == -1) {
				cout << " ";
			}else 
				cout << cyfra[x][y];
		}
		cout << endl;
	}
}

int Pozycja::jaki_kierunek(string pozycje) {

	return znjadz_kierunek();
}
int* Pozycja::znajdz_miejsce(int litera_, int cyfra_) {
	int x, y;
	for (x = 0; x < xSize; x++) {
		for (y = 0; y < ySize; y++) {
			if (litera[x][y] ==litera_  && cyfra[x][y] == cyfra_) {
				int* ret = (int*)malloc(2 * sizeof(int));
				ret[0] = x;
				ret[1] = y;
				return ret;
			}

		}
		if (litera[x][y] == litera_ && cyfra[x][y] == cyfra_) {
			int* ret = (int*)malloc(2 * sizeof(int));
			ret[0] = x;
			ret[1] = y;
			return ret;
		}
	}
	int* ret = (int*)malloc(2 * sizeof(int));
	ret[0] = -1;
	ret[1] = -1;
	return ret;
	
}
int Pozycja::znjadz_kierunek( int litera1, int cyfra1,  int litera2,int cyfra2 ) {
	//this->wypisz();
	int kierunek=-1;
	//szykanie pozycji poczatkowej 
	if (y1 == y2) {
		if (x1 == x2 + 2) {
			kierunek = LEWO;
		}else if (x2 == x1 + 2) {
			kierunek = PRAWO;
		}
	}
	else if (y1 == y2 + 1) {
		if (x1 == x2 + 1) {
			kierunek = GORALEWO;
		}
		else if (x2 == x1 + 1) {
			kierunek = GORAPRAWO;
		}
	}
	else if (y2 == y1 + 1) {
		if (x1 == x2 + 1) {
			kierunek = DOLLEWO;
		}
		else if (x2 == x1 + 1) {
			kierunek = DOLPRAWO;
		}
	}

	this->kierunek = kierunek;
	this->x = x2-2;
	this->y = y2-1;
	return 0;
	
}

bool Pozycja::czy_to_pole_startowe(int  litera, int liczba)
{
	if(litera == 1)
		return true;
	if (litera == 2 * rozmiar + 1)
		return true;
	if (liczba == 1)
		return true;
	if (this->x1 == 0)
		return true;
	for (int x = 3 * rozmiar, y = 0; x < xSize; x++, y++) {
		if (x == this->x1 && y == this->y1)
			return true;
	}
	
	return false;
}

bool Pozycja::czy_to_nie_pole_startowe(int  litera, int liczba)
{
	if (litera == 1)
		return !true;
	if (litera == 2 * rozmiar + 1)
		return !true;
	if (liczba == 1)
		return !true;
	if (this->x2 == 0)
		return !true;
	for (int x = 3 * rozmiar, y = 0; x < xSize; x++, y++) {
		if (x == this->x2 && y == this->y2)
			return !true;
	}

	return !false;
}

bool Pozycja::sprawdz_pozycje(string pozycje)
{
	//this->wypisz();
	char litera1_ = (int)(pozycje[0] - 'a' + 1);
	int cyfra1_ = (int)(pozycje[1] - '1' + 1);
	int* pozycja1 = this->znajdz_miejsce(litera1_,cyfra1_);
	if (pozycja1[0] == -1) {
		cout << "BAD_MOVE_" << pozycje[0] << cyfra1_ << "_IS_WRONG_INDEX" << endl;
		return false;
	}
	this->x1 = pozycja1[0];
	this->y1 = pozycja1[1];
	int litera2_ = (int)(pozycje[3] - 'a' + 1);
	int cyfra2_ = (int)(pozycje[4] - '1' + 1);
	int* pozycja2 = this->znajdz_miejsce(litera2_, cyfra2_);
	if (pozycja2[0] == -1) {
		cout << "BAD_MOVE_" << pozycje[3] << cyfra2_ << "_IS_WRONG_INDEX" << endl;
		return false;
	}
	this->x2 = pozycja2[0];
	this->y2 = pozycja2[1];
	//sprawdzenie czy 1 pole to startowe 
	if (!czy_to_pole_startowe(litera1_, cyfra1_)) {
		cout << "BAD_MOVE_" << pozycje[0] << cyfra1_ <<"_IS_WRONG_STARTING_FIELD" << endl;
		return false;
	}
	//sprawdznei czy 2 pole jest startowym 

	if (!czy_to_nie_pole_startowe(litera2_, cyfra2_)) {
		//gdy x2 to pole startowe 
		cout << "BAD_MOVE_" << pozycje[3] << cyfra1_ << "_IS_WRONG_DESTINATION_FIELD" << endl;
		return false;
	}
	
	//sprawdzeni czy pola sa oddalone od siebie o 2 
	int roznica = 0;
	if (x1 > x2) {
		roznica += x1 - x2;
	}
	else
		roznica += x2 - x1;
	if (y1 > y2) {
		roznica += y1 - y2;
	}
	else
		roznica += y2 - y1;
	if (roznica != 2) {
		cout << "UNKNOWN_MOVE_DIRECTION" << endl;
		return false;
	}

	return true;

	
}

Pozycja::~Pozycja()
{
}
