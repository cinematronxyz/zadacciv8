#include <stdio.h>

int main() {
    FILE *ulaz = fopen("ulaz.c", "r");
    FILE *izlaz = fopen("izlaz.c", "w");

    if (ulaz == NULL || izlaz == NULL) {
        printf("Greska pri otvaranju datoteke\n");
        return 1;
    }

    int c, sledeci;
    int linijski = 0;
    int blokovski = 0;

    while ((c = fgetc(ulaz)) != EOF) {

        if (linijski) {
            if (c == '\n') {
                linijski = 0;
                fputc(c, izlaz);
            }
            continue;
        }

        if (blokovski) {
            if (c == '*') {
                sledeci = fgetc(ulaz);
                if (sledeci == '/') {
                    blokovski = 0;
                } else {
                    ungetc(sledeci, ulaz);
                }
            }
            continue;
        }

        if (c == '/') {
            sledeci = fgetc(ulaz);

            if (sledeci == '/') {
                linijski = 1;
                continue;
            } else if (sledeci == '*') {
                blokovski = 1;
                continue;
            } else {
                fputc(c, izlaz);
                ungetc(sledeci, ulaz);
                continue;
            }
        }

        fputc(c, izlaz);
    }

    fclose(ulaz);
    fclose(izlaz);

    return 0;
}