#pragma once
#include "Gracz.h"
#include "Piony.h"
#include "Pozycja.h"
class Gra
{
public:
	int rozmiarplanszy; //S
	int liczba_pionow; // K
	
	bool poprawna;
	char nastepny_ruch;
	Gracz* W;//bialy 
	Gracz* B; //czarny 
	Piony* piony;
	char** plansza; 
	int x_plansza;
	int y_plansza;

	Gra(int S, int K);
	void dodaj_pionka(char color, int col, int row);
	void wyswietl_plansze();
	Gra();
	void LOAD_GAME_BOARD();
	void PRINT_GAME_STATE();
	void GEN_ALL_POS_MOV();
	int GEN_ALL_POS_MOV_NUM();
	int znjadz_pion();
	void GEN_ALL_POS_MOV_EXT();
	int GEN_ALL_POS_MOV_EXT_NUM();
	void SOLVE_GAME_STATE();
	void WINING_SEQUENCE_EXIST(int N);
	void obsluga_komend();
	bool wczytaj_plansze();
	bool wczytaj();
	bool sprawdz_konce_planszy();
	int ilosc_pozycji();
	void kolejny_ruch();
	bool przesuniecie(int x, int y, int kierunek);
	void zbierz_pion(int x, int y, int kierunek);
	void zbierz_pion();
	void zrob_ruch(int x, int y, int kierunek);

};

