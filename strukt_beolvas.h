#ifndef STRUKTURA_BEOLVAS_H
#define STRUKTURA_BEOLVAS_H

// Ez a struktúra egy kiegészítő struktúra amely az eldöntendő kérdés függvényben használunk!
typedef struct {
    char karakter;
    char *leiras;
} MenuOpcio;

// Ez a struktúra dátumok precíz eltárolásához szükséges.
typedef struct Datum {
    int ev, honap, nap;
} Datum;

// Ebben a struktúrában eltároljuk egy autónak javítás adatait.
typedef struct Javitas {
    Datum mikor;
    char javitas_tipusa[41]; // 40 karakteres típus plusz egy lezáró null karakter
    int anyag_koltseg;
    int javitas_osszege;
} Javitas;

// Ebben a struktúrában eltároljuk egy autó tulajdonosának adatait.
typedef struct Tulajdonos {
    char nev[41]; // 40 karakteres név plusz egy lezáró null karakter
    char telefonszam [12]; // 12 karakteres telefonszám plus egy lezáró null karakter
} Tulajdonos;

typedef struct Auto {
    Tulajdonos auto_tulaja;
    char rendszam[9]; // 8 karakteres rendszám plusz egy lezáró null karakter
    char auto_tipusa[41]; // 40 karakteres típus plusz egy lezáró null karakter
    Datum elozo_muszaki_idopontja;
    int elozo_olaj_csere_km;
    Datum elozo_olaj_csere_idopontja;
    char alvaz_szam[23]; // 22 karakteres alvázszám amelyet "_" jelekkel választunk el (ennek száma: 6) plusz kell egy lezáró null karakter rakunk a végére
    int km_ora_allas;
    int javitasok_szama; // A javítások számát tárolja
    Javitas *eddigi_javitasok; // Mutató a javításokra
} Auto;


void file_beolvas(const char *filenev, Auto **autok, int *elemek_szama);

#endif