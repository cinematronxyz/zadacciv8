#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Radnik {
    int mbr;
    char ime[21];
    char prezime[21];
    double plata;
    struct Radnik* sledeci;
} Radnik;

Radnik* dodajNaPocetak(Radnik* glava, Radnik* novi) {
    novi->sledeci = glava;
    return novi;
}

Radnik* dodajNaKraj(Radnik* glava, Radnik* novi) {
    if (glava == NULL) {
        novi->sledeci = NULL;
        return novi;
    }

    Radnik* tek = glava;
    while (tek->sledeci != NULL)
        tek = tek->sledeci;

    tek->sledeci = novi;
    novi->sledeci = NULL;
    return glava;
}

Radnik* dodajIzaPrvog(Radnik* glava, Radnik* novi) {
    if (glava == NULL)
        return dodajNaPocetak(glava, novi);

    novi->sledeci = glava->sledeci;
    glava->sledeci = novi;
    return glava;
}

Radnik* dodajIspredPoslednjeg(Radnik* glava, Radnik* novi) {
    if (glava == NULL || glava->sledeci == NULL)
        return dodajNaPocetak(glava, novi);

    Radnik* tek = glava;
    while (tek->sledeci->sledeci != NULL)
        tek = tek->sledeci;

    novi->sledeci = tek->sledeci;
    tek->sledeci = novi;
    return glava;
}

Radnik* ucitajRadnike() {
    FILE* f = fopen("radnici.txt", "r");
    if (f == NULL) return NULL;

    Radnik* glava = NULL;
    int red = 0;

    while (1) {
        Radnik* novi = (Radnik*)malloc(sizeof(Radnik));
        if (novi == NULL) break;

        if (fscanf(f, "%d %s %s %lf",
                   &novi->mbr,
                   novi->ime,
                   novi->prezime,
                   &novi->plata) != 4) {
            free(novi);
            break;
        }

        red++;

        if (red == 1)
            glava = dodajNaPocetak(glava, novi);
        else if (red == 2)
            glava = dodajNaKraj(glava, novi);
        else {
            int ostatak = novi->mbr % 4;

            if (ostatak == 0)
                glava = dodajNaPocetak(glava, novi);
            else if (ostatak == 1)
                glava = dodajIzaPrvog(glava, novi);
            else if (ostatak == 2)
                glava = dodajIspredPoslednjeg(glava, novi);
            else
                glava = dodajNaKraj(glava, novi);
        }
    }

    fclose(f);
    return glava;
}

void ispisiPlatuRekurzivno(Radnik* glava) {
    if (glava == NULL)
        return;

    if (glava->plata > 70000)
        printf("%s %s\n", glava->ime, glava->prezime);

    ispisiPlatuRekurzivno(glava->sledeci);
}

void velikaSlova(char* s) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - ('a' - 'A');
        i++;
    }
}

void upisiUFajl(Radnik* glava) {
    FILE* f = fopen("izlaz.txt", "w");
    if (f == NULL) return;

    while (glava != NULL) {
        if (strlen(glava->ime) > 5) {
            char prezimeVeliko[21];
            strcpy(prezimeVeliko, glava->prezime);
            velikaSlova(prezimeVeliko);

            fprintf(f, "%d %s %s %.2lf\n",
                    glava->mbr,
                    glava->ime,
                    prezimeVeliko,
                    glava->plata);
        }
        glava = glava->sledeci;
    }

    fclose(f);
}

void oslobodiListu(Radnik* glava) {
    while (glava != NULL) {
        Radnik* temp = glava;
        glava = glava->sledeci;
        free(temp);
    }
}

int main() {
    Radnik* lista = ucitajRadnike();

    ispisiPlatuRekurzivno(lista);
    upisiUFajl(lista);
    oslobodiListu(lista);

    return 0;
}