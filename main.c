#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "debugmalloc.h"
#include "strukt_beolvas.h"
#include "seged.h"
#include "menu_0.h"
#include "menu_1.h"
#include "menu_2.h"
#include "menu_3.h"
#include "menu_4.h"
#include "menu_5.h"
#include "menu_6.h"

int main(void) {
    // Létrehozzuk az adatokat tartalmazó tömböt.
    Auto *adatok_tomb = NULL;
    int elemek_szama = 0;

    // Ellenőrizzük a beolvasandó file elérési útvonalát.
    const char *fajlnev = "auto.txt";
    FILE *ellenorzes = fopen(fajlnev, "r");
    if (ellenorzes == NULL) {
        perror("A file nem talalhato. Ellenorizd az eleresi utvonalat.");
        exit(EXIT_FAILURE);
    }
    fclose(ellenorzes);

    // Beolvassuk file tartalmát a tömbünkbe.
    file_beolvas(fajlnev, &adatok_tomb, &elemek_szama);

    // Menü rendszer ahol az adat tömbünkbe beolvasott adatokat használva tudunk a számokkal megadott függvényeket használatba venni!
    char menupont[7];
    int menupont_szam;
    do {
        printf("\n\t\033[1;0m    _         _    __                           _     \n");
        printf("\t   / \\  _   _| |_ /_/    ___ _______ _ ____   _(_)____\n");
        printf("\t  / _ \\| | | | __/ _ \\  / __|_  / _ \\ '__\\ \\ / / |_  /\n");
        printf("\t / ___ \\ |_| | || (_) | \\__ \\/ /  __/ |   \\   /| |/ / \n");
        printf("\t/_/   \\_\\__,_|\\__\\___/  |___/___\\___|_|    \\_/ |_/___|\n");

        printf("\n\n\t[0] - Autok rangsorolasa forgalmi/olajcsere lejarata szerint\n");
        printf("\t[1] - Ugyfel neve szerinti ki listazas\n");
        printf("\t[2] - Rendszam szerinti kereses (talalt eseten a javitasok ki iratasa)\n");
        printf("\t[3] - Uj auto rogzitese\n");
        printf("\t[4] - Javitas hozzadasa egy autohoz\n");
        printf("\t[5] - Meglevo auto torlese\n");
        printf("\t[6] - Fileba kiiras\n");
        printf("\t[7] - Kilepes\n\n");

        printf("\tValassz egy menu pontot [0-7]: ");
        fgets(menupont, sizeof(menupont), stdin);
        menupont[strlen(menupont) - 1] = '\0'; // Eltávolítjuk a sorvége karaktert

        int menu_hossza = strlen(menupont);

        if (menu_hossza == 1 && isdigit(menupont[0])) {
            menupont_szam = menupont[0] - '0'; // Karakter számjegy átalakítása számra
        } else {
            konzol_torles();
            printf("\t>>> Ervenytelen menu pontot adott meg, valassz ujra! <<<\n");
            continue; // Az érvénytelen választás esetén visszatérünk a ciklus elejére
        }

        switch (menupont_szam) {
            case 0:
                {
                    konzol_torles();

                    MenuOpcio menu_of[] = {
                        {'o', "Olajcsere"},
                        {'f', "Forgalmi"},
                    };
                    int menu_of_meret = sizeof(menu_of) / sizeof(menu_of[0]);
                    int valasztott_opcio_of = eldontendo_kerdes("Valassz egy opciot, ami alapjan rangsorolni szeretnel:", menu_of, menu_of_meret);


                    MenuOpcio menu_nc[] = {
                        {'n', "Novekvo"},
                        {'c', "Csokkeno"}
                    };
                    int menu_nc_meret = sizeof(menu_nc) / sizeof(menu_nc[0]);
                    int valasztott_opcio_nc = eldontendo_kerdes("Valassz egy opciot, ami alapjan rangsorolni szeretnel:", menu_nc, menu_nc_meret);

                    printf("\nA rangsorolasra kivalasztott opcio: %s\n", menu_of[valasztott_opcio_of].leiras);
                    printf("A rangsorolasra kivalasztott opcio: %s\n", menu_nc[valasztott_opcio_nc].leiras);

                    printf("\n");
                    rendez_auto_tomb(adatok_tomb, elemek_szama, valasztott_opcio_of, valasztott_opcio_nc);

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 1:
                {
                    konzol_torles();

                    // A keresett név bekérése!
                    char nev[41];
                    printf("Adja meg a nevet: ");
                    scanf(" %40[^\n]", nev);

                    // A keresett név adatinak kiírása!
                    karakter_csere(nev, " ", '_');
                    if (!ki_listazo(stdout, adatok_tomb, elemek_szama, nev, 0, 'n')) {
                        nem_talalt_adat();
                    }

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 2:
                {
                    konzol_torles();

                    // A keresett rendszám bekérése!
                    char rendszam[9];
                    printf("Adja meg a rendszamot: ");
                    scanf(" %8[^\n]", rendszam);

                    // A keresett rendszám adatinak kiírása!
                    int rendszam_hossza = strlen(rendszam);
                    bool rendzsam_helyessege = rendszam_csekkolo(rendszam, rendszam_hossza);
                    if (rendzsam_helyessege)
                    {
                        if (!ki_listazo(stdout, adatok_tomb, elemek_szama, rendszam, 2, 'r')) {
                            nem_talalt_adat();
                        }
                    } else {
                        helytelen_adat();
                    }

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 3:
                {
                    konzol_torles();

                    // Új autó létrehozása
                    Auto *uj_auto = (Auto *) malloc(sizeof(Auto));
                    if (uj_auto == NULL) {
                        perror("Nem sikerult memoriat allokalni!");
                        exit(EXIT_FAILURE);
                    }

                    uj_auto_felvevo(adatok_tomb, elemek_szama, uj_auto);
                    printf("\t\033[1;0mAz ujonnan felvett auto adatai:");
                    ki_listazo(stdout, uj_auto, elemek_szama, uj_auto->rendszam, 1, 'r');

                    adatok_tomb = auto_tomb_bovites(adatok_tomb, &elemek_szama);
                    adatok_tomb[elemek_szama - 1] = *uj_auto;
                    free(uj_auto);

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 4:
                {
                    konzol_torles();

                    struct Javitas *uj_javitas = (struct Javitas *)malloc(sizeof(struct Javitas));
                    if (uj_javitas == NULL) {
                        perror("Nem sikerult memoriat allokalni!");
                        exit(EXIT_FAILURE);
                    }

                    // Rendszám beolvasása
                    char *temp_4 = uj_javitas_felvevo(adatok_tomb, elemek_szama, uj_javitas);
                    free(uj_javitas);

                    printf("\t\033[1;0m>>> Az ujonnan felvett javitassokkal frissitett adatok <<<\n\n");
                    ki_listazo(stdout, adatok_tomb, elemek_szama, temp_4, 2, 'r');
                    free(temp_4);

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 5:
                {
                    konzol_torles();

                    auto_torlo(&adatok_tomb, &elemek_szama);

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 6:
                {
                    konzol_torles();
                    
                    ki_ir_fileba(adatok_tomb, elemek_szama);
                    printf("Az \"auto_adatok.txt\"-be lett ki irva az adatok_tomb jelenlegi adatai!\n");

                    tovabb("\033[0;32mNyomj le egy billentyut a folytatashoz!");
                }
                break;
            case 7:
                {
                    konzol_torles();
                    printf("\n\t       _                    _   _   __  _    __                \n");
                    printf("\t__   _(_)___ _______  _ __ | |_| | /_/_| |_ /_/_ ___ _ __ __ _ \n");
                    printf("\t\\ \\ / / / __|_  / _ \\| '_ \\| __| |/ _` | __/ _` / __| '__/ _` |\n");
                    printf("\t \\   /| \\__ \\/ / (_) | | | | |_| | (_| | || (_| \\__ \\ | | (_| |\n");
                    printf("\t  \\_/ |_|___/___\\___/|_| |_|\\__|_|\\__,_|\\__\\__,_|___/_|  \\__,_|\n\n\n");
                }
                break;
            default:
                {
                    konzol_torles();
                    printf("\t>>> Ervenytelen menu pontot adott meg, valassz ujra! <<<");
                }
                break;
        }
    } while (menupont_szam != 7);

    for (int i = 0; i < elemek_szama; i++) {
        printf("%s\n", adatok_tomb[i].rendszam);
        if (adatok_tomb[i].eddigi_javitasok != NULL) {
            printf("-");
            free(adatok_tomb[i].eddigi_javitasok);
        }
    }
    free(adatok_tomb);

    return 0;
}