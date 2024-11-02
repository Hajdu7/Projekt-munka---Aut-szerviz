#ifndef SEGED_H
#define SEGED_H

#include "strukt_beolvas.h"

// Ki írja, hogy nem található a keresett adattot az "adat bázisban" (tömbben).
void nem_talalt_adat();

// Ki írja, hogy egy rendszám helytelennül lett megadva.
void helytelen_adat();

// Törli a console-t, működik Windowson és Linuxon is.
void konzol_torles();

// Addig vár amedig nem nyomsz le bármilyen karaktert.
void tovabb(char *szoveg_ki_ir);

// Egy inputra kapott adatott mit mentén kicseréli mire-re, hogy a txt adat struktúrájának megfelelően lehessen vele a továbbiakban dolgozni.
void karakter_csere(char *keresett, const char *mit, char mire);

// Segít a puffer kiürítésében
void puffer_urites();

// Kap egy kérdést a program amelyre kettő lehetséges választ lehet adni majd vissza adja melyiket választottuk.
int eldontendo_kerdes(char *kerdes, MenuOpcio *menu, int menu_meret);

// Addig kér be egy rendszámot míg helyesen nem lesz megadva.
char *rendszam_beker(Auto *adatok_tomb, int elemek_szama, const char* cim, const char* mit_ker_be);

// Addig kér be egy dátumot míg helyesen nem lesz megadva.
void datum_beker(void *hova, const char* cim, const char* mit_ker_be, const char* milyen_tipusba);

// Addig kér be egy számot míg helyesen nem lesz megadva.
void beker_szamot(void *hova, const char* cim, const char* mit_ker_be, const char* milyen_tipusba);

// Addig kér be egy maximum 41 karakter hosszú sztringet míg helyesen nem lesz megadva.
void beker_szoveg(void *hova, const char* cim, const char* mit_ker_be, const char* milyen_tipusba);

#endif