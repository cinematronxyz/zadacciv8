#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Grad {
    char naziv[16];
    int indeks;
    struct Grad* sledeci;
} Grad;

Grad* dodajNaPocetak(Grad* glava, char* naziv, int indeks) {
    Grad* novi = (Grad*)malloc(sizeof(Grad));
    if (novi == NULL) return glava;

    strcpy(novi->naziv, naziv);
    novi->indeks = indeks;
    novi->sledeci = glava;

    return novi;
}

void ucitajGradove(Grad** glava) {
    FILE* f = fopen("gradovi.txt", "r");
    char naziv[16];
    int indeks;

    if (f == NULL) return;

    while (fscanf(f, "%s %d", naziv, &indeks) == 2) {
        *glava = dodajNaPocetak(*glava, naziv, indeks);
    }

    fclose(f);
}

void primeniPrognozu(Grad* glava) {
    FILE* f = fopen("prognoza.txt", "r");
    char naziv[16];
    double vetar;

    if (f == NULL) return;

    while (fscanf(f, "%s %lf", naziv, &vetar) == 2) {
        Grad* tek = glava;

        while (tek != NULL) {
            if (strcmp(tek->naziv, naziv) == 0) {
                if (vetar >= 2 && vetar <= 5)
                    tek->indeks = tek->indeks * 0.85;
                else if (vetar > 5)
                    tek->indeks = tek->indeks * 0.75;
                break;
            }
            tek = tek->sledeci;
        }
    }

    fclose(f);
}

char* kategorija(int indeks) {
    if (indeks < 50) return "ODLICAN";
    if (indeks < 100) return "DOBAR";
    if (indeks <= 150) return "PRIHVATLJIV";
    if (indeks < 200) return "ZAGADJEN";
    return "JAKO_ZAGADJEN";
}

void upisiUFajl(Grad* glava) {
    FILE* f = fopen("sutra.txt", "w");

    if (f == NULL) return;

    while (glava != NULL) {
        fprintf(f, "%s %d %s\n",
                glava->naziv,
                glava->indeks,
                kategorija(glava->indeks));
        glava = glava->sledeci;
    }

    fclose(f);
}

void oslobodiListu(Grad* glava) {
    while (glava != NULL) {
        Grad* temp = glava;
        glava = glava->sledeci;
        free(temp);
    }
}

int main() {
    Grad* glava = NULL;

    ucitajGradove(&glava);
    primeniPrognozu(glava);
    upisiUFajl(glava);
    oslobodiListu(glava);

    return 0;
}