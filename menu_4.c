#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "strukt_beolvas.h"
#include "seged.h"

// Függvény amivel felveszünk egy új javítást egy autóhoz.
char *uj_javitas_felvevo(Auto *adatok_tomb, int elemek_szama, Javitas *uj_javitas) {

    char *rendszam = rendszam_beker(adatok_tomb, elemek_szama, "\033[1;0mMelyik rendszamu autohoz szeretnel uj javitast felvenni: ", "");
    konzol_torles();

    datum_beker(uj_javitas, "\t\033[1;0m>>> Javitasok <<<\n", "\tJavitas idopontja (ev/honap/nap): ", "mikor");

    beker_szoveg(uj_javitas, "\t\033[1;0m>>> Javitasok <<<\n", "\tJavitas tipusa: ", "javitas_tipusa");

    beker_szamot(uj_javitas, "\t\033[1;0m>>> Javitasok <<<\n", "\tAnyag koltseg: ", "anyag_koltseg");

    beker_szamot(uj_javitas, "\t\033[1;0m>>> Javitasok <<<\n", "\tJavitas osszege: ", "javitas_osszege");

    for (int i = 0; i < elemek_szama; i++) {
        if (strcmp(rendszam, adatok_tomb[i].rendszam) == 0) {
            // Növeljük a javítások számát 1-gyel
            adatok_tomb[i].javitasok_szama++;

            // Realloc csak akkor szükséges, ha már van korábban javítás rögzítve
            adatok_tomb[i].eddigi_javitasok = realloc(adatok_tomb[i].eddigi_javitasok, adatok_tomb[i].javitasok_szama * sizeof(struct Javitas));

            // Ellenőrzés, hogy a realloc sikeres volt-e
            if (adatok_tomb[i].eddigi_javitasok == NULL) {
                perror("Nem sikerult memoriat ujraallokalni!");
                exit(EXIT_FAILURE);
            }

            // Másoljuk be az új javítást
            memcpy(&adatok_tomb[i].eddigi_javitasok[adatok_tomb[i].javitasok_szama - 1], uj_javitas, sizeof(struct Javitas));

            break;
        }
    }

    return rendszam;
}