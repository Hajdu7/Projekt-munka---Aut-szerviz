#ifndef MENU_3_H
#define MENU_3_H

#include "strukt_beolvas.h"
#include "debugmalloc.h"

// Függvény az autó tömb méretének növeléséhez.
Auto *auto_tomb_bovites(Auto *adatok_tomb, int *elemek_szama);

// Függvény amivel felveszünk egy új autót.
void uj_auto_felvevo(Auto *adatok_tomb, int elemek_szama, Auto *uj_auto);

#endif