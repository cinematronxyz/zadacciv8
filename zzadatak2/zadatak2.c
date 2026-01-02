#include <stdio.h>
#include <string.h>

typedef struct {
    char naziv[100];
    double ocena;
    double budzet;
    double zarada;
    double razlika;
} Film;

int main() {
    FILE *ulaz = fopen("filmovi.txt", "r");
    FILE *izlaz = fopen("najpopularniji.txt", "w");

    if (ulaz == NULL || izlaz == NULL) {
        printf("Greska pri otvaranju fajla.\n");
        return 1;
    }

    Film f[100];
    int n = 0, i, j;
    char line[256];

    while (n < 100 && fgets(line, sizeof(line), ulaz)) {

        if (sscanf(line, " %99[^0-9] %lf %lf %lf",
                   f[n].naziv,
                   &f[n].ocena,
                   &f[n].budzet,
                   &f[n].zarada) == 4) {

            size_t len = strlen(f[n].naziv);
            if (len > 0 && f[n].naziv[len - 1] == ' ')
                f[n].naziv[len - 1] = '\0';

            if (f[n].ocena > 7) {
                f[n].razlika = f[n].zarada - f[n].budzet;
                n++;
            }
        }
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (f[j].razlika > f[i].razlika) {
                Film tmp = f[i];
                f[i] = f[j];
                f[j] = tmp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        fprintf(izlaz, "%s %.2lf %.2lf %.2lf %.2lf\n",
                f[i].naziv,
                f[i].ocena,
                f[i].budzet,
                f[i].zarada,
                f[i].razlika);
    }

    fclose(ulaz);
    fclose(izlaz);

    return 0;
}
