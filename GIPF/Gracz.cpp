#include "Gracz.h"

Gracz::Gracz()
{
	this->ilosc_na_planszy = 0;
}

bool Gracz::sprawdz_ilosc_pionkow()
{
	if (ilosc_na_planszy + ilosc_rezerwa > max_ilosc_pionkow) {
		return false;
	}
	return true;
}
