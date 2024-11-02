#include <stdio.h>
#include <stdlib.h>

#include "menu_1.h"
#include "strukt_beolvas.h"


void ki_ir_fileba(Auto *adatok_tomb, int elemek_szama) {
    FILE *file = fopen("auto_adatok.txt", "w");
    if (file == NULL) {
        perror("Nem sikerult megnyitni a file-t!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < elemek_szama; ++i) {
        fprintf(file, "----------------------------------------------------------------------------");
        ki_listazo(file, adatok_tomb, elemek_szama, adatok_tomb[i].auto_tulaja.nev, 0, 'n');
    }

    fclose(file);
}
