#include "Gra.h"

#include <iostream>
using namespace std;
#define GORAPRAWO 1
#define PRAWO 2
#define DOLPRAWO 3
#define DOLLEWO 4
#define LEWO 5 
#define GORALEWO 6
Gra::Gra() {
	this->B = NULL;
	this->W = NULL;
}
void Gra::LOAD_GAME_BOARD() {
	if (this->B != NULL) {
		//usuiniecie starych graczy !!!
	}
	this->B = new Gracz();
	this->W = new Gracz();
	this->piony = NULL;
	cin >> this->rozmiarplanszy;
	cin >> this->liczba_pionow;
	this->x_plansza = 4 * (rozmiarplanszy - 1) + 1;
	this->y_plansza = 2 * (rozmiarplanszy - 1) + 1;

	this->plansza = (char**)malloc(x_plansza * sizeof(char*));
	for (int i = 0; i < x_plansza; i++) {
		plansza[i] = (char*)malloc(y_plansza * sizeof(char));
	}
	int w;
	if (rozmiarplanszy % 2 == 0) {
		w = 0;
	}
	else {
		w = 1;
	}
	for (int i = 0; i < x_plansza; i++) {
		for (int j = 0; j < y_plansza; j++) {
			if (j+i <= rozmiarplanszy/2) {
				plansza[i][j] = 'X';
			}
			else if (i<=j-rozmiarplanszy) {
				plansza[i][j] = 'X';
			}
			else if ((i + j) % 2 == w) {
				plansza[i][j] = 'X';
			}
			else plansza[i][j] = NULL;
		}
	}
	//this->wyswietl_plansze();

	if (wczytaj()) {
		if (this->W->sprawdz_ilosc_pionkow()) {
			if (this->B->sprawdz_ilosc_pionkow()) {
				int ilosc_pionow = znjadz_pion();
				if (ilosc_pionow == 0) {
					cout << "BOARD_STATE_OK" << endl;
					this->poprawna = true;
				}
				else {
					if (ilosc_pionow == 1) {
						cout << "ERROR_FOUND_" << ilosc_pionow << "_ROW_OF_LENGTH_K" << endl;
					}
					else {
						cout << "ERROR_FOUND_" << ilosc_pionow << "_ROWS_OF_LENGTH_K" << endl;
					}
					
					cout << endl;
					//cout << "Mamy " << znjadz_pion() << "pionow";
				}
				
			}
			else cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
		}
		else cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
	}
	else cout << "WRONG_BOARD_ROW_LENGTH" << endl;
	//this->wyswietl_plansze();
}

void Gra::PRINT_GAME_STATE() {
	if (this->poprawna) {
		cout << this->rozmiarplanszy << " ";
		cout<< this->liczba_pionow<<" ";
		cout<< W->max_ilosc_pionkow<<" ";//GW
		cout<< B->max_ilosc_pionkow<<endl;//GB
		cout<< W->ilosc_rezerwa<<" ";
		cout << B->ilosc_rezerwa<<" ";
		cout<< nastepny_ruch<<endl;
		this->wyswietl_plansze();
	}else {
		cout << "EMPTY_BOARD"<<endl;
	}
	
}
void Gra::GEN_ALL_POS_MOV() {

}

int Gra::GEN_ALL_POS_MOV_NUM() {
	return 0;
}

int Gra::znjadz_pion()
{
	int ilosc_pionow = 0;

	//sprawdzzanie poziomo 
	int poprzednia_ilosc = 0;
	char poprzedni_kolor='X';
	for (int j = 0; j < y_plansza; j++) {
		poprzednia_ilosc = 0;
		for (int i = 0; i < x_plansza; i++) {
			
			if (plansza[i][j] == 'X')
				continue;
			if (plansza[i][j] != NULL) {

				if (poprzedni_kolor == plansza[i][j]) {
					poprzednia_ilosc++;
				}
				else {
					poprzednia_ilosc = 1;
					poprzedni_kolor = plansza[i][j];
				}
			}
			else {
				poprzednia_ilosc = 0;
				poprzedni_kolor = 'X';
			}

			if (poprzednia_ilosc == liczba_pionow) {
				////
				ilosc_pionow++;
			}

		}
	}
	//sprawdzanie na ukos
	
	//sprawdzanie \
	//ustawienie watosci pocztekowych 
	int x = 0;
	int y = rozmiarplanszy - 1;
	int x_p = x;
	int y_p = y;
	poprzednia_ilosc = 0;
	poprzedni_kolor = 'X';
	//cout << endl;
	while (true) {
		x = x_p;
		y = y_p;
		//zaczynamy od elemnetu najbardziej wysunietego /
		//iterujemy do gory w prawo

		//po dojsciu do wiersza zerowego 
		//cofamy sie do do³u itd 
		poprzednia_ilosc = 0;
		while (true) {
			//cout << x << "," << y << endl;
			if (plansza[x][y] != NULL) {
				if (poprzednia_ilosc == 0) {
					poprzednia_ilosc = 1;
					poprzedni_kolor = plansza[x][y];
				}
				else {
					
					if (poprzedni_kolor == plansza[x][y]) {
						poprzednia_ilosc++;
					}else{
						poprzednia_ilosc = 1;
						poprzedni_kolor = plansza[x][y];
					}
				}
			}
			else {
				poprzednia_ilosc = 0;
			}
			if (poprzednia_ilosc == this->liczba_pionow) {
				ilosc_pionow++;
			}
			if (y + 1 < y_plansza && x + 1 < x_plansza) {
				y++;
				x++;
			}
			else {
				break;
			}

		}
		if (y_p == 0 && x_p == 3 * rozmiarplanszy - 3 ) {
			break;
		}
		else {
			if (y_p > 0) {
				
				y_p--;
				x_p++;
			}
			else {
				x_p += 2;
			}
			
		}
	 }
	
	//sprawdzeni \

	//sprawdzanie /
	//ustawienie watosci pocztekowych 
	 x = 0;
	 y = rozmiarplanszy - 1;
	 x_p = x;
	y_p = y;
	poprzednia_ilosc = 0;
	poprzedni_kolor = 'X';
	while (true) {
		
		x = x_p;
		y = y_p;
		//zaczynamy od elemnetu najbardziej wysunietego /
		//iterujemy do gory w prawo

		//po dojsciu do wiersza zerowego 
		//cofamy sie do do³u itd 
		poprzednia_ilosc = 0;
		while (true) {
			if (plansza[x][y] != NULL) {
				if (poprzednia_ilosc == 0) {
					poprzednia_ilosc = 1;
					poprzedni_kolor = plansza[x][y];
				}
				else {
					if (poprzedni_kolor == plansza[x][y]) {
						poprzednia_ilosc++;
					}
					else {
						poprzednia_ilosc = 1;
						poprzedni_kolor = plansza[x][y];
					}
				}
			}
			else {
				poprzednia_ilosc = 0;
			}
			if (poprzednia_ilosc == this->liczba_pionow) {
				/////////////////////
				ilosc_pionow++;
			}

			if (y - 1 >= 0 && x + 1 < x_plansza) {
				y--;
				x++;
			}
			else {
				break;
			}

		}

		if (y_p == y_plansza-1 && x_p == 3*rozmiarplanszy-3 ) {
			break;
		}
		else {
			if (y_p +1 < y_plansza) {
				y_p++;
				x_p++;
			}
			else {
				x_p += 2;
			}

		}
	}
	return ilosc_pionow;
}
void Gra::GEN_ALL_POS_MOV_EXT() {

}
int Gra::GEN_ALL_POS_MOV_EXT_NUM() {
	return 0;
}
void Gra::SOLVE_GAME_STATE() {
	//mozliwe die odpowiedzi 
	//"BLACK_HAS_WINING_STRATEGY
	//"WHITE_HAS_WINING_STRATEGY"
}
void Gra::WINING_SEQUENCE_EXIST(int N) {
	
}
void Gra::obsluga_komend()
{
	
	while (true) {
		string komenda;
		cin >> komenda;
		if (komenda[0] == '\x00')
			break;
		if (komenda == "LOAD_GAME_BOARD") {  //+
			this->LOAD_GAME_BOARD();
		}else if (komenda == "WINING_SEQUENCE_EXIST <N>") {
			int N = 90;
			this->WINING_SEQUENCE_EXIST(N);
		}
		else if (komenda == "SOLVE_GAME_STATE") {
			this->SOLVE_GAME_STATE();
		}
		else if (komenda == "PRINT_GAME_BOARD") { ///inprog
			this->PRINT_GAME_STATE();
		}
		else if (komenda == "DO_MOVE") { //in prog  
			string pozycje;
			cin >> pozycje;
			Pozycja poz(this->rozmiarplanszy);
			if (poz.sprawdz_pozycje(pozycje)) {
				poz.jaki_kierunek(pozycje);
				this->zrob_ruch(poz.x, poz.y, poz.kierunek);
			}
		}
		else if (komenda == "GEN_ALL_POS_MOV") {
			this->GEN_ALL_POS_MOV();
		}
		else if (komenda == "GEN_ALL_POS_MOV_NUM") {
			this->GEN_ALL_POS_MOV_NUM();
		}
		else if (komenda == "GEN_ALL_POS_MOV_EXT") {
			this->GEN_ALL_POS_MOV_EXT();
		}
		else if (komenda == "GEN_ALL_POS_MOV_EXT_NUM") {
			this->GEN_ALL_POS_MOV_EXT_NUM();
		}
	}
	
}
Gra::Gra(int const  S, int K)
{

}
void Gra::dodaj_pionka(char color, int col, int row)
{
	plansza[col][row] = color;
	if (color == 'B') {
		this->B->ilosc_na_planszy++;
	}
	else if (color == 'W') {
		this->W->ilosc_na_planszy++;

	}
	else {
	}
}
void Gra::wyswietl_plansze() {

	for (int j = 0; j < y_plansza; j++) {
		for (int i = 0; i < x_plansza; i++) {
			if (plansza[i][j] == NULL) {
				cout << "_";
			}
			else if (plansza[i][j] == 'X')
				cout << " ";
			else if (plansza[i][j] == '*') {

			}				
			else {
				cout << plansza[i][j];
			}
		}
		cout << endl;
	}

}
bool Gra::wczytaj_plansze()
{
	this->poprawna = false;
	cin >> W->max_ilosc_pionkow;//GW
	cin >> B->max_ilosc_pionkow;//GB
	cin >> W->ilosc_rezerwa;
	cin >> B->ilosc_rezerwa;
	cin >> nastepny_ruch;
	//int iloscpozycji = ilosc_pozycji();

	int i = 0;//numer wiersza
	int n = this->rozmiarplanszy;
	int col = this->rozmiarplanszy;
	char x;
	bool ok_wymiar = true;

	//zawsze jest do wczytania (2n)-1 wieszy i kolumn 
	x = getchar();
	if (x != '\n') {
		cout << ")";
	}
	//czytanie kolumn 
	///nowe czytanie planszy
	bool nowalinia = false;
	for (int j = 0; j < y_plansza; j++) {
		nowalinia = false;
		for (int i = 0; i < x_plansza; i++) {
			if (!nowalinia)
				x = getchar();
			else {
				plansza[i][j] = '*';
				continue;
			}
			if (x != '\n') {
				if ( j+ 2 * rozmiarplanszy + 2 <=i ) {
					ok_wymiar = false;
				}
				else if (i + 2 * rozmiarplanszy + 2 <= j) {
					cout << "/";
					ok_wymiar = false;
				}
			}	
			
			if (x == '\n') {
				if (i == 0) {
					i--;
					continue;
				}
				nowalinia = true;
				plansza[i][j] = '*';
			}else if(x==' ') {
				if (plansza[i][j] == 'X')
					continue;
				else {
					 ok_wymiar = false;
				}
					
			}
			else if (x == '_') {
				plansza[i][j] = NULL;
			}
			else {
				//plansza[i][j] = x;
				this->dodaj_pionka(x, i, j);
			}
		}
	}
	if (ok_wymiar)
		ok_wymiar = sprawdz_konce_planszy();

	return ok_wymiar;	
}

bool Gra::wczytaj() {
	this->poprawna = false;
	cin >> W->max_ilosc_pionkow;//GW
	cin >> B->max_ilosc_pionkow;//GB
	cin >> W->ilosc_rezerwa;
	cin >> B->ilosc_rezerwa;
	cin >> nastepny_ruch;
	//int iloscpozycji = ilosc_pozycji();

	int i = 0;//numer wiersza
	//int n = this->rozmiarplanszy;
	int col = this->rozmiarplanszy;
	char x;
	bool ok_wymiar = true;

	//zawsze jest do wczytania (2n)-1 wieszy i kolumn 
	//x = getchar();
	//czytanie kolumn 
	///nowe czytanie planszy
	bool nowalinia = false;
	string linia;
	getline(cin, linia);
	int s_size = linia.length();
	int ilosc_spacji_na_poczatku = rozmiarplanszy-1;
	int ilosc_miejsc_w_lini = rozmiarplanszy;
	int licznik = 0;
	for (int j = 0; j < y_plansza; j++) {
		licznik = 0;
		getline(cin, linia);
		s_size = linia.length();
		if (s_size < ilosc_spacji_na_poczatku) {
			ok_wymiar = false;
			 break;
		}
		for (licznik; licznik < ilosc_spacji_na_poczatku; licznik++) {
			if (linia[licznik] != ' ')
				ok_wymiar = false;
		}
		if (s_size < licznik+2*ilosc_miejsc_w_lini-1) {
			ok_wymiar = false;
			break;
		}
		for (int w = 0; w < ilosc_miejsc_w_lini; w++) {
			if (linia[licznik] == '_') {
				plansza[licznik][j] = NULL;
			}
			else {
				//plansza[licznik][j] = linia[licznik];
				this->dodaj_pionka(linia[licznik], licznik, j);
			}
			licznik++;

			if (w < ilosc_miejsc_w_lini - 1) {
				if (linia[licznik] != ' ')
					ok_wymiar = false;
				licznik++;
			}

		}
		
		if (licznik != s_size) {
			int i = licznik;
			for (i; i < s_size; i++) {
				if (linia[i] != ' ')
					ok_wymiar = false;
			}
		}

		//this->wyswietl_plansze();
		for (int w=0; w < ilosc_spacji_na_poczatku; w++) {
			plansza[licznik][j] = '*';
			licznik++;
		}
		if (j < rozmiarplanszy -1) {
			ilosc_spacji_na_poczatku--;
			ilosc_miejsc_w_lini++;
		}
		else {
			ilosc_spacji_na_poczatku++;
			ilosc_miejsc_w_lini--;
		}
	}

	return ok_wymiar;
}


bool Gra::sprawdz_konce_planszy() {
	int w = +1;
	int miejsce=x_plansza-rozmiarplanszy;
	for (int j = 0; j < y_plansza; j++) {

		if (j == rozmiarplanszy )
			w = -1;
		miejsce += w;
		for (int i = 0; i < x_plansza; i++) {
			if (i >= miejsce) {
				if (plansza[i][j] != '*')
					return false;
			}
			else {
				if (plansza[i][j] == '*')
					return false;
			}
				
		}
	}
	return true;

}
int Gra::ilosc_pozycji() {


	int n = this->rozmiarplanszy;
	int ret=0;
	for (n; n <( (2 * n)-1); n++) {
		ret += n;
	}
	ret += ret;
	ret += (2 * n) - 1;
	return ret;
}
void Gra::kolejny_ruch() {
	if (this->nastepny_ruch == 'W') {
		this->W->ilosc_rezerwa--;
		nastepny_ruch = 'B';
	}
	else {
		this->B->ilosc_rezerwa--;
		nastepny_ruch = 'W';
	}
}

bool Gra::przesuniecie(int x, int y, int kierunek) {
	
	char poprzedni; 
	char popmocnicza;
	poprzedni = plansza[x][y];
	if (kierunek == LEWO) {
		poprzedni = plansza[x][y];
		int ok = 0;
		for (int i = x - 2; i >= 0; i -= 2) {
			if (plansza[i][y] == NULL) {
				ok = 1;
				break;
			}
			else if (plansza[i][y] == 'X') {
				break;
			}
		}
		if (ok == 0) {
			return false;
		}
		for (int i = x-2; i >= 0;i-=2) {
			if (plansza[i][y] == NULL) {
				plansza[i][y] = poprzedni;
				return true;
			}
			else if (plansza[i][y] == 'X') {
				return false;
			}
			else {
				popmocnicza = plansza[i][y];
				plansza[i][y] = poprzedni;
				poprzedni = popmocnicza;
			}
		}
		return false;
	}
	else if (kierunek == PRAWO) {
		poprzedni = plansza[x][y];
		int ok = 0;
		for (int i = x + 2; i < x_plansza; i += 2) {
			if (plansza[i][y] == NULL) {
				ok = 1;
				break;
			}
			else if (plansza[i][y] == '*') {
				break;
			}
		}
		if (ok == 0) {
			return false;
		}

		for (int i = x + 2; i <x_plansza; i+=2) {
			if (plansza[i][y] == NULL) {
				plansza[i][y] = poprzedni;
				return true;
			}
			else if (plansza[i][y] == '*') {

				return false;
			}
			else {
				popmocnicza = plansza[i][y];
				plansza[i][y] = poprzedni;
				poprzedni = popmocnicza;
			}
		}
		return false;
	}
	else if (kierunek == GORALEWO) {

		int i = x - 1;
		int j = y - 1;
		int ok = 0;
		while (true) {
			if (plansza[i][j] == NULL) {
				ok = 1;
				break;
			}
			else if (plansza[i][j] == 'X') {
				break;
			}
			if (j - 1 >= 0 && i - 1 >= 0) {
				j--;
				i--;
			}
			else break;
		}
		if (ok == 0)
			return false;

		i = x - 1;
		j = y - 1;
		while (true) {
			if (plansza[i][j] == NULL) {
				plansza[i][j] = poprzedni;
				return true;
			}
			else if (plansza[i][j] == 'X') {
				return false;
			}
			else {
				popmocnicza = plansza[i][j];
				plansza[i][j] = poprzedni;
				poprzedni = popmocnicza;
			}
			if (j -1 >=0 && i - 1 >= 0) {
				j--;
				i--;
			}
			else {
				return false;
			}
		}
	}
	else if (kierunek==DOLPRAWO){
		int i = x + 1;
		int j = y + 1;
		int ok = 0;
		while (true) {
			if (plansza[i][j] == NULL) {
				ok = 1;
				break;
			}
			else if (plansza[i][j] == '*') {
				break;
			}
			if (j + 1 < y_plansza && i + 1 < x_plansza) {
				j++;
				i++;
			}
			else {
				break;
			}

		}
		if (ok == 0) return false;
		i = x + 1;
		j = y + 1;
		while (true) {
			if (plansza[i][j] == NULL) {
				plansza[i][j] = poprzedni;
				return true;
			}
			else if (plansza[i][j] == '*') {
				return false;
			}
			else {
				popmocnicza = plansza[i][j];
				plansza[i][j] = poprzedni;
				poprzedni = popmocnicza;
			}
			if (j + 1 < y_plansza && i + 1 < x_plansza) {
				j++;
				i++;
			}
			else {
				return false;
			}

		}
	}
	else if (kierunek==GORAPRAWO){
		int ok = 0;
		int i = x + 1;
		int j = y - 1;
		while (true) {
			if (plansza[i][j] == NULL) {
				ok = 1;
				break;
			}
			else if (plansza[i][j] == '*') {
				break;
			}			
			if (j - 1 >= 0 && i + 1 < x_plansza) {
				j--;
				i++;
			}
			else {
				break;
			}

		}
		 i = x + 1;
		 j = y - 1;
		 if (ok == 0) {
			 return false;
		 }
		while (true) {
			if (plansza[i][j] == NULL) {
				plansza[i][j] = poprzedni;
				return true;
			}
			else if (plansza[i][j] == '*') {
				return false;
			}
			else {
				popmocnicza = plansza[i][j];
				plansza[i][j] = poprzedni;
				poprzedni = popmocnicza;
			}
			if (j - 1 >= 0 && i + 1 <x_plansza) {
				j--;
				i++;
			}
			else {
				return false;
			}

		}
	}
	else if(kierunek==DOLLEWO){
		int i = x - 1;
		int j = y + 1;
		int ok = 0;
		while (true) {
			if (plansza[i][j] == NULL) {
				ok = 1;
				break;
			}
			else if (plansza[i][j] == 'X') {
				break;
			}
			
			if (j + 1 < y_plansza && i - 1 >= 0) {
				j++;
				i--;
			}
			else {
				break;
			}

		}
		if (ok == 0)
			return false;
		 i = x - 1;
		 j = y + 1;



		while (true) {
			if (plansza[i][j] == NULL) {
				plansza[i][j] = poprzedni;
				return true;
			}
			else if (plansza[i][j] == 'X') {
				return false;
			}
			else {
				popmocnicza = plansza[i][j];
				plansza[i][j] = poprzedni;
				poprzedni = popmocnicza;
			}
			if (j + 1 <y_plansza && i - 1 >= 0) {
				j++;
				i--;
			}
			else {
				return false;
			}

		}
	}
	else if (kierunek == -1) {
		return false;
	}
	return false;
}

void Gra::zbierz_pion(int x, int y, int kierunek) {
	int w=0;
	int b=0;
	int i = x, j = y;
	if (kierunek == PRAWO || kierunek == LEWO ) {
		//idziemy w prawo
		while (true) {
			if (plansza[i][j] == 'W') {
				w++;
				plansza[i][j] = NULL;
			}else if (plansza[i][j] == 'B') {
				b++;
				plansza[i][j] = NULL;
			}
			else break;

			if (i + 1 < x_plansza) {
				i++;
			}
			else break;
		}
		//idziemy w lewo
		i = x-1;
		j = y;
		while (true) {
			if (plansza[i][j] == 'W') {
				w++;
				plansza[i][j] = NULL;
			}
			else if (plansza[i][j] == 'B') {
				b++;
				plansza[i][j] = NULL;
			}
			else break;
			
			if (i - 1>=0) {
				i--;
			}
			else break;
		}
	}
	else if (kierunek == GORAPRAWO||kierunek==DOLLEWO) { // =/

		//idziemy w gore
		while (true) {
			if (plansza[i][j] == 'W') {
				w++;
				plansza[i][j] = NULL;
			}
			else if (plansza[i][j] == 'B') {
				b++;
				plansza[i][j] = NULL;
			}
			else break;

			if ( i + 1 < x_plansza && j - 1 >= 0 ){
				j--;
				i++;
			}
			else break;
		}
		//idziemy w dol
		i = x - 1;
		j = y+1;
		while (true) {
			if (plansza[i][j] == 'W') {
				w++;
				plansza[i][j] = NULL;
			}
			else if (plansza[i][j] == 'B') {
				b++;
				plansza[i][j] = NULL;
			}
			else break;

			if (i - 1 >= 0 && j + 1 <y_plansza) {
				i--;
				j++;
			}
			else break;
		}

	}
	else if (kierunek == GORALEWO || kierunek == DOLPRAWO) {//  =\\\
		//idziemy w gore
		while (true) {
			if (plansza[i][j] == 'W') {
				w++;
				plansza[i][j] = NULL;
			}
			else if (plansza[i][j] == 'B') {
				b++;
				plansza[i][j] = NULL;
			}
			else break;

			if (i - 1 >= 0 && j - 1 >= 0) {
				j--;
				i--;
			}
			else break;
		}
		//idziemy w dol
		i = x + 1;
		j = y + 1;
		while (true) {
			if (plansza[i][j] == 'W') {
				w++;
				plansza[i][j] = NULL;
			}
			else if (plansza[i][j] == 'B') {
				b++;
				plansza[i][j] = NULL;
			}
			else break;

			if (i + 1 < x_plansza && j + 1 < y_plansza) {
				i++;
				j++;
			}
			else break;
		}
	}

	if (w > b) {
		this->W->ilosc_rezerwa += w;
	}
	else {
		this->B->ilosc_rezerwa += b;
	}


}
void Gra::zbierz_pion() {
	//wiemy ze jest tylko 1 wiec jak zbiore to wychodze !! 
	int ilosc_pionow = 0;
	//sprawdzzanie poziomo 
	int poprzednia_ilosc = 0;
	char poprzedni_kolor = 'X';
	for (int j = 0; j < y_plansza; j++) {
		poprzednia_ilosc = 0;
		for (int i = 0; i < x_plansza; i++) {

			if (plansza[i][j] == 'X')
				continue;
			if (plansza[i][j] != NULL) {

				if (poprzedni_kolor == plansza[i][j]) {
					poprzednia_ilosc++;
				}
				else {
					poprzednia_ilosc = 1;
					poprzedni_kolor = plansza[i][j];
				}
			}
			else {
				poprzednia_ilosc = 0;
				poprzedni_kolor = 'X';
			}
			if (poprzednia_ilosc == liczba_pionow) {
				this->zbierz_pion(i, j, PRAWO);	
				return;
			}
		}
	}
	//sprawdzanie na ukos

	//sprawdzanie \
	//ustawienie watosci pocztekowych 
	int x = 0;
	int y = rozmiarplanszy - 1;
	int x_p = x;
	int y_p = y;
	poprzednia_ilosc = 0;
	poprzedni_kolor = 'X';
	while (true) {
		x = x_p;
		y = y_p;
		poprzednia_ilosc = 0;
		while (true) {
			if (plansza[x][y] != NULL) {
				if (poprzednia_ilosc == 0) {
					poprzednia_ilosc = 1;
					poprzedni_kolor = plansza[x][y];
				}
				else {

					if (poprzedni_kolor == plansza[x][y]) {
						poprzednia_ilosc++;
					}
					else {
						poprzednia_ilosc = 1;
						poprzedni_kolor = plansza[x][y];
					}
				}
			}
			else {
				poprzednia_ilosc = 0;
			}
			if (poprzednia_ilosc == this->liczba_pionow) {
				this->zbierz_pion(x, y, GORALEWO);
				return;
			}
			if (y + 1 < y_plansza && x + 1 < x_plansza) {
				y++;
				x++;
			}
			else break;
			
		}
		if (y_p == 0 && x_p == 3 * rozmiarplanszy - 3) break;
		else {
			if (y_p > 0) {
				y_p--;
				x_p++;
			}
			else {
				x_p += 2;
			}
		}
	}
	//sprawdzeni \

	//sprawdzanie /
	//ustawienie watosci pocztekowych 
	x = 0;
	y = rozmiarplanszy - 1;
	x_p = x;
	y_p = y;
	poprzednia_ilosc = 0;
	poprzedni_kolor = 'X';
	while (true) {
		x = x_p;
		y = y_p;
		//zaczynamy od elemnetu najbardziej wysunietego /
		//iterujemy do gory w prawo
		//po dojsciu do wiersza zerowego 
		//cofamy sie do do³u itd 
		poprzednia_ilosc = 0;
		while (true) {
			if (plansza[x][y] != NULL) {
				if (poprzednia_ilosc == 0) {
					poprzednia_ilosc = 1;
					poprzedni_kolor = plansza[x][y];
				}
				else {
					if (poprzedni_kolor == plansza[x][y]) {
						poprzednia_ilosc++;
					}
					else {
						poprzednia_ilosc = 1;
						poprzedni_kolor = plansza[x][y];
					}
				}
			}
			else {
				poprzednia_ilosc = 0;
			}
			if (poprzednia_ilosc == this->liczba_pionow) {
				this->zbierz_pion(x, y, GORAPRAWO);
				return;
			}

			if (y - 1 >= 0 && x + 1 < x_plansza) {
				y--;
				x++;
			}
			else {
				break;
			}
		}
		if (y_p == y_plansza - 1 && x_p == 3 * rozmiarplanszy - 3) {
			break;
		}
		else {
			if (y_p + 1 < y_plansza) {
				y_p++;
				x_p++;
			}
			else {
				x_p += 2;
			}

		}
	}
	cout << "nie udalosie";
}
void Gra::zrob_ruch(int x, int y, int kierunek)
{
	if (plansza[x][y] == NULL) {
		plansza[x][y] = nastepny_ruch;
		this->kolejny_ruch();
		return;
	}
	else {
		if (przesuniecie(x, y, kierunek)) {
			plansza[x][y] = nastepny_ruch;
			this->kolejny_ruch();
			int piony = znjadz_pion();
			if (piony == 0) {
				cout << "MOVE_COMMITTED" << endl;
			}
			else if (piony == 1) {
				this->zbierz_pion();
				cout << "MOVE_COMMITTED" << endl;
			}
			else {
				cout << "wiecej nix 2 piony";
			}
		}
		else {
			cout <<"BAD_MOVE_ROW_IS_FULL"<<endl;
		}
	}

}
