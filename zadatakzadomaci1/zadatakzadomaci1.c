#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AKT 1000
#define MAX_OPIS 81

typedef struct {
    int start;
    int end;
    char opis[MAX_OPIS];
} Aktivnost;

int time_to_min(int h, int m) {
    return h * 60 + m;
}

void write_activity(FILE *f, Aktivnost a) {
    fprintf(f, "%02d:%02d %02d:%02d %s\n",
            a.start / 60, a.start % 60,
            a.end / 60, a.end % 60,
            a.opis);
}

int main() {
    FILE *fin = fopen("kalendar.txt", "r");  
    if (!fin) {
        printf("Greska pri otvaranju kalendar.txt\n");
        return 1;
    }

    Aktivnost a[MAX_AKT];
    int n = 0;

    while (!feof(fin)) {
        int h1, m1, h2, m2;
        char opis[MAX_OPIS];

        if (fscanf(fin, "%d:%d %d:%d ", &h1, &m1, &h2, &m2) != 4)
            break;

        fgets(opis, MAX_OPIS, fin);
        opis[strcspn(opis, "\n")] = 0;

        a[n].start = time_to_min(h1, m1);
        a[n].end   = time_to_min(h2, m2);
        strncpy(a[n].opis, opis, MAX_OPIS);

        n++;
    }

    fclose(fin);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i].start > a[j].start ||
               (a[i].start == a[j].start && a[i].end > a[j].end)) {
                Aktivnost tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }

    FILE *fs = fopen("kalendar_sortirano.txt", "w");
    for (int i = 0; i < n; i++)
        write_activity(fs, a[i]);
    fclose(fs);

    Aktivnost rez[MAX_AKT];
    int r = 0;

    for (int i = 0; i < n; i++) {
        if (r == 0) {
            rez[r++] = a[i];
        } else {
            if (a[i].start < rez[r - 1].end) {
                continue;
            } else {
                rez[r++] = a[i];
            }
        }
    }

    FILE *fr = fopen("kalendar_revidirano.txt", "w");
    for (int i = 0; i < r; i++)
        write_activity(fr, rez[i]);
    fclose(fr);

    return 0;
}
