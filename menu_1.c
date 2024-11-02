#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "strukt_beolvas.h"

// Ki listázza egy keresett adatnak az összes információját. Ez lehet név vagy rendszám.
bool ki_listazo(FILE *file, Auto *adatok_tomb, int elemek_szama, const char *keresett, const int mit_ki_ir, const char mi_alapjan) {
    bool talalt = false;
    int hanyadik_javitas = 1;

    for (int i = 0; i < elemek_szama; i++) {
        if ((strcmp(adatok_tomb[i].auto_tulaja.nev, keresett) == 0 && mi_alapjan == 'n') || (strcmp(adatok_tomb[i].rendszam, keresett) == 0 && mi_alapjan == 'r')) {
            if (!talalt) {
                fprintf(file, "\n\t>>> Tulajdonos adati <<<\n");
                fprintf(file, "\tNev: %s\n", adatok_tomb[i].auto_tulaja.nev);
                fprintf(file, "\tTelefonszam: +%s\n", adatok_tomb[i].auto_tulaja.telefonszam);
                talalt = true;
            }

            if (mit_ki_ir == 0 || mit_ki_ir == 1) {
                fprintf(file, "\n\t>>> Auto adatai <<<\n");
                fprintf(file, "\tRendszama: %s\n", adatok_tomb[i].rendszam);
                fprintf(file, "\tTipusa: %s\n", adatok_tomb[i].auto_tipusa);
                fprintf(file, "\tElozo muszaki vizsgajanak idopontja: %04d.%02d.%02d\n",
                        adatok_tomb[i].elozo_muszaki_idopontja.ev,
                        adatok_tomb[i].elozo_muszaki_idopontja.honap,
                        adatok_tomb[i].elozo_muszaki_idopontja.nap);
                fprintf(file, "\tElozo olajcsere km-ora allas: %d\n", adatok_tomb[i].elozo_olaj_csere_km);
                fprintf(file, "\tElozo olajcsere idopontja: %04d.%02d.%02d\n",
                        adatok_tomb[i].elozo_olaj_csere_idopontja.ev,
                        adatok_tomb[i].elozo_olaj_csere_idopontja.honap,
                        adatok_tomb[i].elozo_olaj_csere_idopontja.nap);
                fprintf(file, "\tAlvazszam: %s\n", adatok_tomb[i].alvaz_szam);
                fprintf(file, "\tKm-ora allas: %d\n", adatok_tomb[i].km_ora_allas);
            }

            if (mit_ki_ir == 0 || mit_ki_ir == 2) {
                if (adatok_tomb[i].javitasok_szama != 0) {
                    fprintf(file, "\n\t>>> Javitasok <<<\n");
                    for (int j = 0; j < adatok_tomb[i].javitasok_szama; j++) {
                        fprintf(file, "\t(%d)Javitas datuma: %04d.%02d.%02d\n",
                                hanyadik_javitas, adatok_tomb[i].eddigi_javitasok[j].mikor.ev,
                                adatok_tomb[i].eddigi_javitasok[j].mikor.honap,
                                adatok_tomb[i].eddigi_javitasok[j].mikor.nap);
                        fprintf(file, "\t(%d)Javitas tipusa: %s\n", hanyadik_javitas, adatok_tomb[i].eddigi_javitasok[j].javitas_tipusa);
                        fprintf(file, "\t(%d)Anyag koltseg: %d\n", hanyadik_javitas, adatok_tomb[i].eddigi_javitasok[j].anyag_koltseg);
                        fprintf(file, "\t(%d)Javitas osszege: %d\n", hanyadik_javitas, adatok_tomb[i].eddigi_javitasok[j].javitas_osszege);
                        hanyadik_javitas++;
                    }
                } else {
                    fprintf(file, "\n\t>>> Nincs javitas tetel feljegyezve <<<\n");
                }
            }
        }
    }
    return talalt;
}