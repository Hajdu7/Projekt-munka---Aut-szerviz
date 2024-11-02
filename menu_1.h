#ifndef MENU_1_H
#define MENU_1_H

#include <stdbool.h>
#include "strukt_beolvas.h"

// Ki listázza egy keresett adatnak az összes információját. Ez lehet név vagy rendszám.
bool ki_listazo(FILE *file, Auto *adatok_tomb, int elemek_szama, const char *keresett, const int mit_ki_ir, const char mi_alapjan);

#endif