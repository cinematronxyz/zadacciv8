#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char sifra[6];
    double povrsina;
    double cena;
    double cena_m2;
} Parcela;

int main() {
    FILE *ulaz = fopen("parcele.txt", "r");
    FILE *izlaz = fopen("najskuplje.txt", "w");
    if (!ulaz || !izlaz) {
        printf("Greska pri otvaranju fajla!\n");
        return 1;
    }

    Parcela *niz = NULL;
    int count = 0, kapacitet = 0;

    while (1) {
        Parcela p;
        if (fscanf(ulaz, "%5s %lf %lf", p.sifra, &p.povrsina, &p.cena) != 3) break;
        p.cena_m2 = p.cena / p.povrsina;

        if (count >= kapacitet) {
            kapacitet = kapacitet == 0 ? 10 : kapacitet * 2;
            niz = realloc(niz, kapacitet * sizeof(Parcela));
        }
        niz[count++] = p;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (niz[i].cena_m2 < niz[j].cena_m2) {
                Parcela tmp = niz[i];
                niz[i] = niz[j];
                niz[j] = tmp;
            }
        }
    }

    int topN = count < 3 ? count : 3;
    for (int i = 0; i < topN; i++) {
        fprintf(izlaz, "%s (%.2f €/m2)\n", niz[i].sifra, niz[i].cena_m2);
    }

    double minCena = niz[count-1].cena_m2;
    double maxCena = niz[0].cena_m2;
    fprintf(izlaz, "\nNajmanja cena/m2: %.2f\n", minCena);
    fprintf(izlaz, "Najveca cena/m2: %.2f\n", maxCena);

    free(niz);
    fclose(ulaz);
    fclose(izlaz);
    return 0;
}
