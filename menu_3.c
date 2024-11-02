#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "debugmalloc.h"
#include "strukt_beolvas.h"
#include "seged.h"
#include "menu_2.h"

// Függvény az autó tömb méretének növeléséhez.
Auto *auto_tomb_bovites(Auto *adatok_tomb, int *elemek_szama) {
    // Növeljük a tömb méretét egyel
    *elemek_szama += 1;

    // Realloc használatával növeljük a tömb méretét
    Auto *temp = realloc(adatok_tomb, *elemek_szama * sizeof(Auto));
    if (temp == NULL) {
        perror("Nem sikerult memoriat allokalni!");
        exit(EXIT_FAILURE);
    }

    return temp;
}

// Függvény amivel felveszünk egy új autót.
void uj_auto_felvevo(Auto *adatok_tomb, int elemek_szama, Auto *uj_auto) {
    bool hibas_bemenet;
    bool volt_mar_hiba;

    beker_szoveg(uj_auto, "\t\033[1;0m>>> Adja meg a tulajdonos adatait <<<\n", "\tTeljes nev: ", "auto_tulaja");

    do {
        hibas_bemenet = false;
        volt_mar_hiba = false;
        char temp_telefonszam[12];
                
        printf("\t\033[1;0m>>> Adja meg a tulajdonos adatait <<<\n");
        printf("\tTelefonszam: ");
        if (scanf(" %11[^\n]", temp_telefonszam) != 1) {
            hibas_bemenet = true;
        }

        for (int i = 0; temp_telefonszam[i] != '\0'; i++) {
            if (strchr("ÁÉÍÓÖŐÚÜŰáéóöőüű", temp_telefonszam[i]) != NULL || isalpha(temp_telefonszam[i])) {
                hibas_bemenet = true;
            }
        }
                           
        for (int i = 0; i < elemek_szama; i++) {
            if (strcmp(temp_telefonszam, adatok_tomb[i].auto_tulaja.telefonszam) == 0) {
                if (!volt_mar_hiba) {
                    tovabb("\033[0;31mA telefonszam mar szerepel az adatbazisban. Adj meg egy masikat!");
                    konzol_torles();
                    volt_mar_hiba = true;
                }
                hibas_bemenet = true;
                break;
            }
        }
                            
        if (hibas_bemenet && !volt_mar_hiba) {
            tovabb("\033[0;31mHibas bemenet! A telefonszam nem tartalmazhat ekezetes karaktert vagy betut. Add meg ujra!");
            konzol_torles();
        } else {
            if (strlen(temp_telefonszam) != 11) {
                hibas_bemenet = true;
                tovabb("\033[0;31mHibas bemenet! Telefonszam hossza nem megfelelo!");
                konzol_torles();
            } else {
                strcpy(uj_auto->auto_tulaja.telefonszam, temp_telefonszam);
            }
        }
    } while (hibas_bemenet);
    puffer_urites();

    do {
        hibas_bemenet = false;
        char temp_rendszam[9];
                        
        printf("\t\033[1;0m>>> Adja meg az auto adatait <<<\n");
        printf("\tRendszam: ");
                        
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

            if (rendszam_talalt) {
                tovabb("\033[0;31mA rendszam nem szerepel az adatbazisban. Adj meg egy masikat!");
                hibas_bemenet = true;
                konzol_torles();
            } else {
                strcpy(uj_auto->rendszam, temp_rendszam);
            }
        }
    } while (hibas_bemenet);
    puffer_urites();

    do {
        hibas_bemenet = false;
        char temp_tipus[41];

        printf("\t\033[1;0m>>> Adja meg az auto adatait <<<\n");
        printf("\tTipus: ");
        if (scanf(" %40[^\n]", temp_tipus) != 1) {
            hibas_bemenet = true;
        }
        karakter_csere(temp_tipus, " ", '_');

        for (int i = 0; temp_tipus[i] != '\0'; i++) {
            if (strchr("ÁÉÍÓÖŐÚÜŰáéóöőüű", temp_tipus[i]) != NULL) {
                hibas_bemenet = true;
            }
        }

        if (hibas_bemenet) {
            tovabb("\033[0;31mHibas bemenet! A nev nem tartalmazhat ekezetes karaktert vagy szamot. Add meg ujra!");
            konzol_torles();
        } else {
            strcpy(uj_auto->auto_tipusa, temp_tipus);
        }
    } while (hibas_bemenet);
    puffer_urites();

    datum_beker(uj_auto, "\t\033[1;0m>>> Adja meg az auto adatait <<<\n", "\tElozo muszaki idopontja (ev/honap/nap): ", "elozo_muszaki_idopontja");

    beker_szamot(uj_auto, "\t\033[1;0m>>> Adja meg az auto adatait <<<\n", "\tElozo olajcsere km-ora allas: ", "elozo_olaj_csere_km");

    datum_beker(uj_auto, "\t\033[1;0m>>> Adja meg az auto adatait <<<\n", "\tElozo olajcsere idopontja (ev/honap/nap): ", "elozo_olaj_csere_idopontja");

    do {
        hibas_bemenet = false;
        volt_mar_hiba = false;
        char temp_alvaz_szam[23];

        printf("\t\033[1;0m>>> Adja meg az auto adatait <<<\n");
        printf("\tAlvazszam (XX_X_XXXX_X_X_X_XXXXXX): ");

        if (scanf(" %22[^'\n']", temp_alvaz_szam) != 1) {
            hibas_bemenet = true;
        }

        for (int i = 0; temp_alvaz_szam[i] != '\0'; i++) {
            if (strchr("ÁÉÍÓÖŐÚÜŰáéóöőüű", temp_alvaz_szam[i]) != NULL) {
                hibas_bemenet = true;
            }
        }

        for (int i = 0; i < elemek_szama; i++) {
            if (strcmp(temp_alvaz_szam, adatok_tomb[i].alvaz_szam) == 0) {
                if (!volt_mar_hiba) {
                    tovabb("\033[0;31mEz a alvazszam mar szerepel az adatbazisban. Adj meg egy masikat!");
                    konzol_torles();
                    volt_mar_hiba = true;
                }
                hibas_bemenet = true;
                break;
            }
        }

        if (hibas_bemenet && !volt_mar_hiba) {
            tovabb("\033[0;31mHibas bemenet! Kerem, adja meg helyes formatumba az alvazszamot! XX_X_XXXX_X_X_X_XXXXXX");
            konzol_torles();
        } else {
            if (strlen(temp_alvaz_szam) != 22) {
                hibas_bemenet = true;
                tovabb("\033[0;31mHibas bemenet! Alvazszam hossza nem megfelelo!");
                konzol_torles();
            } else {
                strcpy(uj_auto->alvaz_szam, temp_alvaz_szam);
            }
        }
    } while (hibas_bemenet);
    puffer_urites();

    beker_szamot(uj_auto, "\t\033[1;0m>>> Adja meg az auto adatait <<<\n", "\tKm-ora allas: ", "km_ora_allas");

    uj_auto->javitasok_szama = 0;
    uj_auto->eddigi_javitasok = NULL;
}