#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "strukt_beolvas.h"
#include "seged.h"

// Függvény a törlendő adatt kiválasztására.
void auto_torlo(Auto **adatok_tomb, int *elemek_szama) {
    char *rendszam = rendszam_beker(*adatok_tomb, *elemek_szama, "\033[1;0mMelyik rendszamu autohoz szeretnel uj javitast felvenni: ", "");

    for (int i = 0; i < *elemek_szama; i++) {
        if (strcmp(rendszam, (*adatok_tomb)[i].rendszam) == 0) {
            // Megtaláltuk az autót, most töröljük az adatait
            // A törölés utáni elemeket át kell másolni a tömbben, majd csökkentjük az elemek számát
            free(adatok_tomb[i]->eddigi_javitasok);

            for (int j = i; j < *elemek_szama - 1; j++) {
                (*adatok_tomb)[j] = (*adatok_tomb)[j + 1];
            }

            // Csökkentjük az elemek számát
            (*elemek_szama)--;

            // Új méretre való átméretezés az adatok_tomb
            Auto *uj_adatok_tomb = realloc(*adatok_tomb, *elemek_szama * sizeof(Auto));
            if (uj_adatok_tomb == NULL) {
                perror("Nem sikerult memoriat ujra allokalni!");
                exit(EXIT_FAILURE);
            }

            // Frissítjük az adatok_tomb pointer-t az újra allokált tömbre
            *adatok_tomb = uj_adatok_tomb;

            printf("\033[1;0mA(z) %s rendszamu auto torolve lett az adatbazisbol!\n", rendszam);
            break;
        }
    }
    free(rendszam);
}
