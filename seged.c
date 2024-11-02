#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "menu_2.h"
#include "debugmalloc.h"
#include "strukt_beolvas.h"

// Ki írja, hogy nem található a keresett adattot az "adat bázisban" (tömbben).
void nem_talalt_adat(){
    printf("\n\t\033[0;31m    _      _                           _   _                     \n");
    printf("\t   / \\    | | _____ _ __ ___  ___  ___| |_| |_                   \n");
    printf("\t  / _ \\   | |/ / _ \\ '__/ _ / __|/ _ \\ __| __|                  \n");
    printf("\t / ___ \\  |   <  __/ | |  __/__ \\  __/ |_| |_                   \n");
    printf("\t/_/   \\_\\ |_|\\_\\___|_|  \\___||___/___|\\__|\\__|                  \n");
    printf("\t  __ _  __| | __ _| |_ _ __ /_/ | |  _ __ (_)_ __   ___ ___      \n");
    printf("\t / _` |/ _` |/ _` | __| '__/ _ \\| | | '_ \\| | '_ \\ / __/ __|     \n");
    printf("\t| (_| | (_| | (_| | |_| | | (_) | | | | | | | | | | (__\\__ \\     \n");
    printf("\t \\__,_|\\__,_|\\__,_|\\__|_|  \\___/|_| |_| |_|_|_| |_|\\___|___/     \n");
    printf("\t _        __                        __       _   __              \n");
    printf("\t(_)_ __  / _| ___  _ __ _ __ ___   /_/_  ___(_) /_/     __ _ ____\n");
    printf("\t| | '_ \\| |_ / _ \\| '__| '_ ` _ \\ / _` |/ __| |/ _ \\   / _` |_  / \n");
    printf("\t| | | | |  _| (_) | |  | | | | | | (_| | (__| | (_) | | (_| |/ /  \n");
    printf("\t|_|_| |_|_|_ \\___/|_|  |_| |_| |_|\\__,_|\\___|_|\\___/   \\__,_/___|\n");
    printf("\t  __ _  __| | __ _| |_| |__   /_/_ ___(_)___| |__   __ _ _ __\n");
    printf("\t / _` |/ _` |/ _` | __| '_ \\ / _` |_  / / __| '_ \\ / _` | '_ \\\n");
    printf("\t| (_| | (_| | (_| | |_| |_) | (_| |/ /| \\__ \\ |_) | (_| | | | |\n");
    printf("\t \\__,_|\\__,_|\\__,_|\\__|_.__/ \\__,_/___|_|___/_.__/ \\__,_|_| |_|\n\n");
}

// Ki írja, hogy egy rendszám helytelennül lett megadva.
void helytelen_adat(){
    printf("\n\t\033[0;31m _   _      _       _       _                        _       _   \n");
    printf("\t| | | | ___| |_   _| |_ ___| | ___ _ __     __ _  __| | __ _| |_ \n");
    printf("\t| |_| |/ _ \\ | | | | __/ _ \\ |/ _ \\ '_ \\   / _` |/ _` |/ _` | __|\n");
    printf("\t|  _  |  __/ | |_| | ||  __/ |  __/ | | | | (_| | (_| | (_| | |_ \n");
    printf("\t|_| |_|\\___|_|\\__, |\\__\\___|_|\\___|_| |_|  \\__,_|\\__,_|\\__,_|\\__|\n");
    printf("\t              |___/                                              \n\n");
}

// Törli a console-t, működik Windowson és Linuxon is.
void konzol_torles() {
    // Ebben a függvényben döntjük el, hogy melyik parancsot használjuk
    #ifdef _WIN32
        system("cls"); // Windows esetén
    #else
        system("clear"); // Linux/Unix/Mac esetén
    #endif
}

// Addig vár amedig nem nyomsz le bármilyen karaktert.
void tovabb(char *szoveg_ki_ir) {
    char ch;
    printf("\n%s", szoveg_ki_ir);
    while ((ch = getchar()) != '\n' && ch != EOF); // Ez kiüríti a bemeneti puffert
    getchar(); // Itt várakozik a billentyűleütésre
    konzol_torles();
}

// Segít a puffer kiürítésében
void puffer_urites() {
    tovabb("\033[0;32mNyomj le egy billentyut, a bemeneti buffer uritesehez!");
    konzol_torles();
}

// Egy inputra kapott adatott mit mentén kicseréli mire-re, hogy a txt adat struktúrájának megfelelően lehessen vele a továbbiakban dolgozni.
void karakter_csere(char *keresett, const char *mit, char mire) {
    while (*keresett) {
        if (*keresett == *mit) {
            *keresett = mire;
        }
        keresett++;
    }
}

// Kap egy kérdést a program amelyre kettő lehetséges választ lehet adni majd vissza adja melyiket választottuk.
int eldontendo_kerdes(char *kerdes, MenuOpcio *menu, int menu_meret) {
    // A melyik_opcio-t return-őli a függvény! Amely vissza adja hányadik számú opciót választotta a felhasználó a struktúrában definiáltak közül. {0. vagy 1.}
    int melyik_opcio = -1;
    bool hibas_valasz = false;

    do {
        if (hibas_valasz) {
            konzol_torles();
            printf("Hibas opcio, kerlek valassz ujra!\n");
        }

        printf("%s\n", kerdes);
        for (int i = 0; i < menu_meret; i++) {
            printf("%c) %s\n", menu[i].karakter, menu[i].leiras);
        }

        char menupont[256]; // Elég nagy hely az input fogadásához

        if (fgets(menupont, sizeof(menupont), stdin) == NULL) {
            exit(1);
        }

        int karakterek_szama = strlen(menupont);

        if (karakterek_szama == 2 && menupont[1] == '\n') {
            char valasztott_karakter = menupont[0];
            for (int i = 0; i < menu_meret; i++) {
                if (tolower(valasztott_karakter) == tolower(menu[i].karakter)) {
                    melyik_opcio = i;
                    break;
                }
            }
        } else {
            hibas_valasz = true;
        }
    } while (melyik_opcio == -1);

    konzol_torles();
    return melyik_opcio;
}

// Addig kér be egy rendszámot míg helyesen nem lesz megadva.
char *rendszam_beker(Auto *adatok_tomb, int elemek_szama, const char* cim, const char* mit_ker_be) {
    bool hibas_bemenet;
    char* rendszam = (char*)malloc(9 * sizeof(char));

    do {
        hibas_bemenet = false;
        char temp_rendszam[9];

        printf("%s", cim);
        printf("%s", mit_ker_be);

        if (scanf(" %8[^\n]", temp_rendszam) != 1 || (strlen(temp_rendszam) != 8 && strlen(temp_rendszam) != 7)) {
            tovabb("\033[0;31mHibas bemenet! A rendszam tul rovid/hosszu lett. Add meg ujra!");
            hibas_bemenet = true;
            konzol_torles();
        } else if (!rendszam_csekkolo(temp_rendszam, strlen(temp_rendszam))) {
            tovabb("\033[0;31mHibas bemenet! A rendszam nem felel meg a Magyar hatosagi eloirasoknak. Add meg ujra!");
            hibas_bemenet = true;
            konzol_torles();
        } else {
            bool rendszam_talalt = false;
            for (int i = 0; i < elemek_szama; i++) {
                if (strcmp(temp_rendszam, adatok_tomb[i].rendszam) == 0) {
                    rendszam_talalt = true;
                    break;
                }
            }

            if (!rendszam_talalt) {
                tovabb("\033[0;31mA rendszam nem szerepel az adatbazisban. Adj meg egy masikat!");
                hibas_bemenet = true;
                konzol_torles();
            } else {
                strcpy(rendszam, temp_rendszam);
            }
        }
    } while (hibas_bemenet);

    return rendszam;
}

// Addig kér be egy dátumot míg helyesen nem lesz megadva.
void datum_beker(void *hova, const char* cim, const char* mit_ker_be, const char* milyen_tipusba) {
    bool hibas_bemenet;

    do {
        hibas_bemenet = false;
        Datum temp_datum;

        printf("%s", cim);
        printf("%s", mit_ker_be);

        if (scanf("%d/%d/%d", &temp_datum.ev, &temp_datum.honap, &temp_datum.nap) != 3 ||
            temp_datum.honap < 1 || temp_datum.honap > 12 ||
            temp_datum.nap < 1 || temp_datum.nap > 31) {
            hibas_bemenet = true;
            tovabb("\n\033[0;31mHibas bemenet! Kerem, adja meg helyes formatumba az ertekeket! ev/honap/nap");
            konzol_torles();
        } else {
            // Cast-oljuk vissza az eredeti típusra (Auto vagy Javitas)
            if (strcmp(milyen_tipusba, "elozo_muszaki_idopontja") == 0) {
                Auto *auto_ptr = (Auto *)hova;
                auto_ptr->elozo_muszaki_idopontja.ev = temp_datum.ev;
                auto_ptr->elozo_muszaki_idopontja.honap = temp_datum.honap;
                auto_ptr->elozo_muszaki_idopontja.nap = temp_datum.nap;
            } else if (strcmp(milyen_tipusba, "elozo_olaj_csere_idopontja") == 0) {
                Auto *auto_ptr = (Auto *)hova;
                auto_ptr->elozo_olaj_csere_idopontja.ev = temp_datum.ev;
                auto_ptr->elozo_olaj_csere_idopontja.honap = temp_datum.honap;
                auto_ptr->elozo_olaj_csere_idopontja.nap = temp_datum.nap;
            } else if (strcmp(milyen_tipusba, "mikor") == 0) {
                Javitas *javitas_ptr = (Javitas *)hova;
                javitas_ptr->mikor.ev = temp_datum.ev;
                javitas_ptr->mikor.honap = temp_datum.honap;
                javitas_ptr->mikor.nap = temp_datum.nap;
            }
        }
    } while (hibas_bemenet);
    puffer_urites();
}

// Addig kér be egy számot míg helyesen nem lesz megadva.
void beker_szamot(void *hova, const char* cim, const char* mit_ker_be, const char* milyen_tipusba) {
    bool hibas_bemenet;
    do {
        hibas_bemenet = false;
        char temp_int[12];

        printf("%s", cim);
        printf("%s", mit_ker_be);

        if (fgets(temp_int, sizeof(temp_int), stdin) == NULL) {
            perror("\033[0;31mHiba történt az adatok beolvasása során.");
            exit(EXIT_FAILURE);
        }

        temp_int[strcspn(temp_int, "\n")] = '\0';

        // Ellenőrizzük, hogy a beolvasott szöveg csak számokat tartalmaz-e
        for (int i = 0; temp_int[i] != '\0'; i++) {
            if (!isdigit(temp_int[i])) {
                hibas_bemenet = true;
                break;
            }
        }

        if (hibas_bemenet) {
            tovabb("\033[0;31mHibas bemenet! A javitas osszege csak szamot tartalmazhat. Add meg ujra!\n");
            konzol_torles();
        } else {
            // Cast-oljuk vissza az eredeti típusra (Auto vagy Javitas)
            if (strcmp(milyen_tipusba, "km_ora_allas") == 0) {
                Auto *auto_ptr = (Auto *)hova;
                auto_ptr->km_ora_allas = atoi(temp_int);
            } else if (strcmp(milyen_tipusba, "elozo_olaj_csere_km") == 0) {
                Auto *auto_ptr = (Auto *)hova;
                auto_ptr->elozo_olaj_csere_km = atoi(temp_int);
            } else if (strcmp(milyen_tipusba, "javitas_osszege") == 0) {
                Javitas *javitas_ptr = (Javitas *)hova;
                javitas_ptr->javitas_osszege = atoi(temp_int);
            } else if (strcmp(milyen_tipusba, "anyag_koltseg") == 0) {
                Javitas *javitas_ptr = (Javitas *)hova;
                javitas_ptr->anyag_koltseg = atoi(temp_int);
            }
        }
    } while (hibas_bemenet);
    puffer_urites();
}

// Addig kér be egy maximum 41 karakter hosszú sztringet míg helyesen nem lesz megadva.
void beker_szoveg(void *hova, const char* cim, const char* mit_ker_be, const char* milyen_tipusba) {
    bool hibas_bemenet;

    do {
        hibas_bemenet = false;
        char temp_szoveg[41];

        printf("%s", cim);
        printf("%s", mit_ker_be);

        if (scanf(" %40[^\n]", temp_szoveg) != 1) {
            hibas_bemenet = true;
        }
        karakter_csere(temp_szoveg, " ", '_');

        for (int i = 0; temp_szoveg[i] != '\0'; i++) {
            if (strchr("ÁÉÍÓÖŐÚÜŰáéóöőüű", temp_szoveg[i]) != NULL || isdigit(temp_szoveg[i])) {
                hibas_bemenet = true;
            }
        }

        if (hibas_bemenet) {
            tovabb("\033[0;31mHibas bemenet! A nev nem tartalmazhat ekezetes karaktert vagy szamot. Add meg ujra!");
            konzol_torles();
        } else {
            // Cast-oljuk vissza az eredeti típusra (Auto vagy Javitas)
            if (strcmp(milyen_tipusba, "auto_tulaja") == 0) {
                Auto *auto_ptr = (Auto *)hova;
                strcpy(auto_ptr->auto_tulaja.nev, temp_szoveg);
            } else if (strcmp(milyen_tipusba, "javitas_tipusa") == 0) {
                Javitas *javitas_ptr = (Javitas *)hova;
                strcpy(javitas_ptr->javitas_tipusa, temp_szoveg);
            }
        }


    } while (hibas_bemenet);
    puffer_urites();
}