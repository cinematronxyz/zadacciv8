#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *ulaz = fopen("piloti.txt", "r");
    FILE *izlaz = fopen("piloti_out.txt", "w");

    if (ulaz == NULL || izlaz == NULL) {
        printf("Greska pri otvaranju fajla.\n");
        return 1;
    }

    char *ime = (char *)malloc(50 * sizeof(char));
    char *prezime = (char *)malloc(50 * sizeof(char));

    if (ime == NULL || prezime == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        fclose(ulaz);
        fclose(izlaz);
        return 1;
    }

    int godine, letovi;

    while (fscanf(ulaz, "%49s %49s %d %d", ime, prezime, &godine, &letovi) == 4) {
        double prosek = (double)letovi / godine;

        if (prosek > 7) {
            for (int i = 0; ime[i] != '\0'; i++) {
                if (ime[i] >= 'a' && ime[i] <= 'z')
                    ime[i] -= 32;
            }

            for (int i = 0; prezime[i] != '\0'; i++) {
                if (prezime[i] >= 'a' && prezime[i] <= 'z')
                    prezime[i] -= 32;
            }
        }

        fprintf(izlaz, "%s %s %.2lf\n", ime, prezime, prosek);
    }

    free(ime);
    free(prezime);

    fclose(ulaz);
    fclose(izlaz);

    return 0;
}
