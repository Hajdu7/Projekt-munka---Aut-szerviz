#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "debugmalloc.h"
#include "strukt_beolvas.h"

// Struktúra a rendezési paraméterek tárolásához
struct RendezesParameterek {
    int szures_modja;
    int rendezes_modja;
};

struct RendezesParameterek *global_rendezes_parameterek;

// Dátum összehasonlító függvény.
int datum_osszehasonlito(struct Datum datum_1, struct Datum datum_2) {
    if (datum_1.ev != datum_2.ev) {
        return (datum_1.ev < datum_2.ev) ? -1 : 1;
    }

    if (datum_1.honap != datum_2.honap) {
        return (datum_1.honap < datum_2.honap) ? -1 : 1;
    }

    if (datum_1.nap != datum_2.nap) {
        return (datum_1.nap < datum_2.nap) ? -1 : 1;
    }

    return 0;
}

// Autó összehasonlító függvény
int auto_asc_or_desc(const void *auto_1, const void *auto_2) {
    const struct Auto *a = (const struct Auto *)auto_1;
    const struct Auto *b = (const struct Auto *)auto_2;
    const struct RendezesParameterek *rendezes_parameterek = global_rendezes_parameterek;  // globális változó

    int eredmeny;

    if (rendezes_parameterek->szures_modja == 0) {
        eredmeny = datum_osszehasonlito(a->elozo_olaj_csere_idopontja, b->elozo_olaj_csere_idopontja);
    } else {
        eredmeny = datum_osszehasonlito(a->elozo_muszaki_idopontja, b->elozo_muszaki_idopontja);
    }

    return (rendezes_parameterek->rendezes_modja == 0) ? eredmeny : -eredmeny;
}

// Autó kiíró függvény
void kiir_auto(const struct Auto *auto_adat, int szures_modja) {
    printf("Idopont: %04d.%02d.%02d \t Az auto rendszama: %s\n",
           szures_modja == 0 ? auto_adat->elozo_olaj_csere_idopontja.ev : auto_adat->elozo_muszaki_idopontja.ev,
           szures_modja == 0 ? auto_adat->elozo_olaj_csere_idopontja.honap : auto_adat->elozo_muszaki_idopontja.honap,
           szures_modja == 0 ? auto_adat->elozo_olaj_csere_idopontja.nap : auto_adat->elozo_muszaki_idopontja.nap,
           auto_adat->rendszam);
}

// Aktuális időpont és előző vizsga óta megvizsgálja el telt el annyi idő, hogy szükséges újra vizsgáztatni.
int idopont_ellenorzo(struct Datum idopont, int szures_modja) {
    time_t ma;
    struct tm* aktualis_datum_tm;

    time(&ma);
    aktualis_datum_tm = localtime(&ma);

    // Átalakítjuk a Datum struktúrát tm struktúrává
    struct tm idopont_tm = {
            .tm_year = idopont.ev - 1900,
            .tm_mon = idopont.honap - 1,
            .tm_mday = idopont.nap,
            .tm_hour = 0,
            .tm_min = 0,
            .tm_sec = 0,
            .tm_isdst = -1,
    };

    // Az eltelt idő számolása napokban
    long int eltelt_ido_napok = difftime(ma, mktime(&idopont_tm)) / (60 * 60 * 24);

    // Ellenőrizzük, hogy eltelt-e a megadott időtartam
    return eltelt_ido_napok >= (szures_modja == 0 ? 365 : 730); // 365 nap = 1 év, 730 nap = 2 év
}

// Autó rendező függvény
void rendez_auto_tomb(struct Auto *adatok_tomb, int elemek_szama, int szures_modja, int rendezes_modja) {
    // Ideiglenes tömb létrehozása
    struct Auto *ideiglenes_tomb = malloc(elemek_szama * sizeof(struct Auto));
    if (ideiglenes_tomb == NULL) {
        // Hiba történt a memóriafoglalas soran
        fprintf(stderr, "Hiba a memoriafoglalas soran.\n");
        exit(EXIT_FAILURE);
    }

    // Struktúra létrehozása a rendezési paraméterekkel
    struct RendezesParameterek rendezes_parameterek = {szures_modja, rendezes_modja};

    // Globális változó beállítása
    global_rendezes_parameterek = &rendezes_parameterek;

    // A qsort függvény használata a rendezéshez
    qsort(adatok_tomb, elemek_szama, sizeof(struct Auto), (int (*)(const void *, const void *))auto_asc_or_desc);

    // Csak azokat az autókat másoljuk az ideiglenes tömbbe, amelyek megfelelnek az időköznek
    int ideiglenes_index = 0;
    for (int i = 0; i < elemek_szama; i++) {
        if (idopont_ellenorzo(szures_modja == 0 ? adatok_tomb[i].elozo_olaj_csere_idopontja : adatok_tomb[i].elozo_muszaki_idopontja, szures_modja)
            && (szures_modja == 1 || (szures_modja == 0 && (adatok_tomb[i].km_ora_allas - adatok_tomb[i].elozo_olaj_csere_km) >= 20000))) {
            ideiglenes_tomb[ideiglenes_index++] = adatok_tomb[i];
        }
    }

    // Ellenőrizzük, hogy találtunk-e autót
    if (ideiglenes_index == 0) {
        printf("Nincs olyan auto, amelynek le lenne jarva a vizsgaja.\n");
    } else {
        // Kiírás a rendezett tömbről
        for (int i = 0; i < ideiglenes_index; i++) {
            kiir_auto(&ideiglenes_tomb[i], szures_modja);
        }
    }

    // Ideiglenes tömb felszabadítása
    free(ideiglenes_tomb);
}