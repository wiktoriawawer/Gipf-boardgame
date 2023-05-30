#pragma once
#include "Gracz.h"
class Gra
{
public:
	int rozmiarplanszy; //S
	int liczba_pionow; // K
	
	
	char nastepny_ruch;
	Gracz* W;//bialy 
	Gracz* B; //czarny 

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
	int zjadz_pion();
	int znjadz_pion();
	void GEN_ALL_POS_MOV_EXT();
	int GEN_ALL_POS_MOV_EXT_NUM();
	void SOLVE_GAME_STATE();
	void WINING_SEQUENCE_EXIST(int N);
	void obsluga_komend();
	bool wczytaj_plansze();
	bool sprawdz_konce_planszy();
	int ilosc_pozycji();

};

