#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmalloc.h"
#include "strukt_beolvas.h"

// Beolvassa a txt-ből az adatokat ---> az adatkat taroló tömbbe.
void file_beolvas(const char *filenev, Auto **autok, int *elemek_szama) {
    FILE *file = fopen(filenev, "r");
    if (file == NULL) {
        perror("Nem sikerult megnyitni a file-t!");
        exit(EXIT_FAILURE);
    }

    char sor[256]; // Az aktuális sor tárolására

    // Inicializáljuk az autók tömböt
    *autok = NULL;
    *elemek_szama = 0;

    while (fgets(sor, sizeof(sor), file) != NULL) {
        Auto aktualis;
        // Sor feldarabolása a pontosvesszők alapján
        char *token = strtok(sor, ";");
        strcpy(aktualis.auto_tulaja.nev, token);

        token = strtok(NULL, ";");
        strcpy(aktualis.auto_tulaja.telefonszam, token);

        token = strtok(NULL, ";");
        strcpy(aktualis.rendszam, token);

        token = strtok(NULL, ";");
        strcpy(aktualis.auto_tipusa, token);

        token = strtok(NULL, ";");
        sscanf(token, "%d/%d/%d", &aktualis.elozo_muszaki_idopontja.ev, &aktualis.elozo_muszaki_idopontja.honap, &aktualis.elozo_muszaki_idopontja.nap);

        token = strtok(NULL, ";");
        aktualis.elozo_olaj_csere_km = atoi(token);

        token = strtok(NULL, ";");
        sscanf(token, "%d/%d/%d", &aktualis.elozo_olaj_csere_idopontja.ev, &aktualis.elozo_olaj_csere_idopontja.honap, &aktualis.elozo_olaj_csere_idopontja.nap);

        token = strtok(NULL, ";");
        strcpy(aktualis.alvaz_szam, token);

        token = strtok(NULL, ";");
        aktualis.km_ora_allas = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL) {
            int javitasok_szama = atoi(token);
            aktualis.javitasok_szama = javitasok_szama;
            if (javitasok_szama > 0) {
                aktualis.eddigi_javitasok = (Javitas *)malloc(javitasok_szama * sizeof(Javitas));
                if (aktualis.eddigi_javitasok == NULL) {
                    perror("Nem sikerult memoriat ujra allokalni!");
                    exit(EXIT_FAILURE);
                }

                for (int i = 0; i < javitasok_szama; i++) {
                    token = strtok(NULL, ";");
                    sscanf(token, "%d/%d/%d", &aktualis.eddigi_javitasok[i].mikor.ev, &aktualis.eddigi_javitasok[i].mikor.honap, &aktualis.eddigi_javitasok[i].mikor.nap);

                    token = strtok(NULL, ";");
                    strcpy(aktualis.eddigi_javitasok[i].javitas_tipusa, token);

                    token = strtok(NULL, ";");
                    aktualis.eddigi_javitasok[i].anyag_koltseg = atoi(token);

                    token = strtok(NULL, ";");
                    aktualis.eddigi_javitasok[i].javitas_osszege = atoi(token);
                }
            } else {
                aktualis.javitasok_szama = 0;
                aktualis.eddigi_javitasok = NULL;
            }
        } else {
            aktualis.javitasok_szama = 0;
            aktualis.eddigi_javitasok = NULL;
        }

        // Hozzáadás a dinamikus tömbhöz
        (*elemek_szama)++;
        *autok = (Auto *)realloc(*autok, (*elemek_szama) * sizeof(Auto));
        if (*autok == NULL) {
            perror("Nem sikerult memoriat ujra allokalni!");
            exit(EXIT_FAILURE);
        }

        (*autok)[(*elemek_szama) - 1] = aktualis;
    }

    fclose(file);
}