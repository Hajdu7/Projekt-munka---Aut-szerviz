#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Megnézi egy rendszámról, hogy helyes a Magyar hatosági előírásoknak. Vizsgálja a hosszt és, hogy megfelelő helyen megfelelő karakterek szerepelnek-e!
bool rendszam_csekkolo(char *rendszam, int rendszam_hossza) {
    if (rendszam_hossza == 8) {
        char tiltott_parkapcsolatok[7][3] = {"CS", "GY", "LY", "NY", "SZ", "TY", "ZS"};
        int elso_tipus; // 0 - Magánhangzók, 1 - Vegyes, 2 - Mássalhangzók

        char elsopar[2];
        elsopar[0] = rendszam[0]; // Első betű
        elsopar[1] = rendszam[1]; // Második betű

        // Első pár ellenőrzése
        if (isalpha(elsopar[0]) && isalpha(elsopar[1])) {
            if (strchr("AEIOU", elsopar[0]) && strchr("AEIOU", elsopar[1])) {
                elso_tipus = 0; // Mindkét betű magánhangzó
            } else if (!strchr("AEIOU", elsopar[0]) && !strchr("AEIOU", elsopar[1])) {
                elso_tipus = 2; // Mindkét betű mássalhangzó
            } else {
                elso_tipus = 1; // Vegyes
            }
        } else {
            return false;
        }

        // Ellenőrzés, hogy az első pár nem tartalmazza-e a tiltott párkapcsolatokat
        if (elso_tipus == 2) {
            for (int i = 0; i < 7; i++) {
                if (strcmp(elsopar, tiltott_parkapcsolatok[i]) == 0) {
                    return false;
                }
            }
        } else if (elso_tipus == 1){
            return false;
        }

        if (!isalpha(rendszam[2]) && isalpha(rendszam[3])){
            return false;
        }

        // További ellenőrzések a kötőjel és a számjegyek számára
        if (rendszam[4] != '-') {
            return false;
        }
        for (int i = 5; i < 8; i++) {
            if (!isdigit(rendszam[i])) {
                return false;
            }
        }

        return true;
    } else if (rendszam_hossza == 7) {
        // Ellenőrizze a 7 karakteres rendszámot
        for (int i = 0; i < 3; i++) {
            if (!isalpha(rendszam[i])) {
                return false;
            }
        }
        if (rendszam[3] != '-') {
            return false;
        }
        for (int i = 4; i < 7; i++) {
            if (!isdigit(rendszam[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}