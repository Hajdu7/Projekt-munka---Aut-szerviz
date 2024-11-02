#ifndef MENU_0_H
#define MENU_0_H

#include "strukt_beolvas.h"

// Dátum összehasonlító függvény.
int datum_osszehasonlito(struct Datum datum_1, struct Datum datum_2);

// Autó rendező függvény
void rendez_auto_tomb(struct Auto *adatok_tomb, int elemek_szama, int szures_modja, int rendezes_modja);

#endif