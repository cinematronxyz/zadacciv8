#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[50];
    char prezime[50];
    int brojPobeda;
    int brojPolPozicija;
} Vozac;

Vozac* ucitajVozace(int* brojVozaca) {
    FILE* ulaz;
    Vozac* niz;
    Vozac* pomocni;
    Vozac temp;
    int i;

    *brojVozaca = 0;
    niz = NULL;

    ulaz = fopen("drivers.txt", "r");
    if (ulaz == NULL) {
        printf("Greska pri otvaranju fajla drivers.txt\n");
        return NULL;
    }

    while (fscanf(ulaz, "%s %s %d %d",
                  temp.ime,
                  temp.prezime,
                  &temp.brojPobeda,
                  &temp.brojPolPozicija) == 4) {

        pomocni = (Vozac*)realloc(niz, (*brojVozaca + 1) * sizeof(Vozac));
        if (pomocni == NULL) {
            fclose(ulaz);
            free(niz);
            return NULL;
        }

        niz = pomocni;
        niz[*brojVozaca] = temp;
        (*brojVozaca)++;
    }

    fclose(ulaz);
    return niz;
}

void ispisiPolPozicije(Vozac* niz, int brojVozaca) {
    int i;

    printf("Osvajaci barem jedne pol pozicije:\n");

    for (i = 0; i < brojVozaca; i++) {
        if (niz[i].brojPolPozicija > 0) {
            printf("%s %s %d %d\n",
                   niz[i].ime,
                   niz[i].prezime,
                   niz[i].brojPobeda,
                   niz[i].brojPolPozicija);
        }
    }
}

void sortirajVozace(Vozac* niz, int brojVozaca) {
    int i, j;
    Vozac temp;

    for (i = 0; i < brojVozaca - 1; i++) {
        for (j = i + 1; j < brojVozaca; j++) {

            if (niz[i].brojPobeda < niz[j].brojPobeda ||
               (niz[i].brojPobeda == niz[j].brojPobeda &&
                niz[i].brojPolPozicija < niz[j].brojPolPozicija)) {

                temp = niz[i];
                niz[i] = niz[j];
                niz[j] = temp;
            }
        }
    }
}

void upisiUFajl(Vozac* niz, int brojVozaca) {
    FILE* izlaz;
    int i;

    izlaz = fopen("results.txt", "w");
    if (izlaz == NULL) {
        printf("Greska pri otvaranju fajla results.txt\n");
        return;
    }

    for (i = 0; i < brojVozaca; i++) {
        fprintf(izlaz, "%s %s %d %d\n",
                niz[i].ime,
                niz[i].prezime,
                niz[i].brojPobeda,
                niz[i].brojPolPozicija);
    }

    fclose(izlaz);
}

int main() {
    Vozac* vozaci;
    int brojVozaca;

    vozaci = ucitajVozace(&brojVozaca);
    if (vozaci == NULL) {
        return 1;
    }

    ispisiPolPozicije(vozaci, brojVozaca);

    sortirajVozace(vozaci, brojVozaca);

    upisiUFajl(vozaci, brojVozaca);

    free(vozaci);

    return 0;
}