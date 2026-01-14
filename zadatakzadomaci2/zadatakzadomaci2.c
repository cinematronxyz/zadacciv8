#include <stdio.h>
#include <stdbool.h>

int main() {
    FILE *ulaz = fopen("ulaz.c", "r");
    FILE *izlaz = fopen("izlaz.c", "w");

    if (!ulaz || !izlaz) {
        printf("Greska pri otvaranju datoteke\n");
        return 1;
    }

    int c, sledeci;
    bool linijski = false;
    bool blokovski = false;

    while ((c = fgetc(ulaz)) != EOF) {

        if (linijski) {
            if (c == '\n') {
                linijski = false;
                fputc(c, izlaz);
            }
            continue;
        }

        if (blokovski) {
            if (c == '*') {
                sledeci = fgetc(ulaz);
                if (sledeci == '/') {
                    blokovski = false;
                } else {
                    ungetc(sledeci, ulaz);
                }
            }
            continue;
        }

        if (c == '/') {
            sledeci = fgetc(ulaz);

            if (sledeci == '/') {
                linijski = true;
                continue;
            } else if (sledeci == '*') {
                blokovski = true;
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
