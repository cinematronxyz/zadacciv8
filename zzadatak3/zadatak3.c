#include <stdio.h>
#include <string.h>

int main() {
    FILE *ulaz = fopen("piloti.txt", "r");
    FILE *izlaz = fopen("piloti_out.txt", "w");

    if (ulaz == NULL || izlaz == NULL) {
        printf("Greska pri otvaranju fajla.\n");
        return 1;
    }

    char ime[50], prezime[50];
    int godine, letovi, i;

    while (fscanf(ulaz, "%s %s %d %d", ime, prezime, &godine, &letovi) == 4) {
        double prosek = (double)letovi / godine;

        if (prosek > 7) {
            for (i = 0; ime[i]; i++) {
                if (ime[i] >= 'a' && ime[i] <= 'z')
                    ime[i] -= 32;
            }

            for (i = 0; prezime[i]; i++) {
                if (prezime[i] >= 'a' && prezime[i] <= 'z')
                    prezime[i] -= 32;
            }
        }

        fprintf(izlaz, "%s %s %.2lf\n", ime, prezime, prosek);
    }

    fclose(ulaz);
    fclose(izlaz);

    return 0;
}
