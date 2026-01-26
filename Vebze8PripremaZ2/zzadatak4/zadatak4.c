#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *ulaz = fopen("ulaz.txt", "r");
    FILE *izlaz = fopen("izlaz.txt", "w");

    if (ulaz == NULL || izlaz == NULL) {
        printf("Greska pri otvaranju fajla.\n");
        return 1;
    }

    char **linije = NULL;
    char buffer[129];
    int n = 0, i;

    while (fgets(buffer, sizeof(buffer), ulaz)) {
        char **tmp = realloc(linije, (n + 1) * sizeof(char *));
        if (tmp == NULL) {
            printf("Greska pri alokaciji memorije.\n");
            return 1;
        }
        linije = tmp;

        linije[n] = malloc(strlen(buffer) + 1);
        if (linije[n] == NULL) {
            printf("Greska pri alokaciji memorije.\n");
            return 1;
        }

        strcpy(linije[n], buffer);
        n++;
    }

    for (i = n; i > 0; i--) {
        fputs(linije[i - 1], izlaz);
        free(linije[i - 1]);
    }

    free(linije);

    fclose(ulaz);
    fclose(izlaz);

    return 0;
}
