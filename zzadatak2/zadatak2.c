#include <stdio.h>
#include <stdlib.h>
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

    if (!ulaz || !izlaz) {
        printf("Greska pri otvaranju fajla.\n");
        return 1;
    }

    int n;
    if (fscanf(ulaz, "%d", &n) != 1 || n <= 0) {
        printf("Neispravan broj filmova.\n");
        fclose(ulaz);
        fclose(izlaz);
        return 1;
    }

    Film *f = malloc(n * sizeof(Film));
    if (!f) {
        printf("Greska pri alokaciji memorije.\n");
        fclose(ulaz);
        fclose(izlaz);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(ulaz, "%99s %lf %lf %lf",
                   f[i].naziv,
                   &f[i].ocena,
                   &f[i].budzet,
                   &f[i].zarada) != 4) {
            printf("Greska pri citanju podataka.\n");
            free(f);
            fclose(ulaz);
            fclose(izlaz);
            return 1;
        }
        f[i].razlika = f[i].zarada - f[i].budzet;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (f[i].ocena < f[j].ocena) {
                Film tmp = f[i];
                f[i] = f[j];
                f[j] = tmp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        fprintf(izlaz, "%s %.2lf %.2lf %.2lf %.2lf\n",
                f[i].naziv,
                f[i].ocena,
                f[i].budzet,
                f[i].zarada,
                f[i].razlika);
    }

    free(f);
    fclose(ulaz);
    fclose(izlaz);
    return 0;
}
