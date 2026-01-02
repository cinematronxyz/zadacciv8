#include <stdio.h>
#include <string.h>
typedef struct {
	char sifra[6];
	double povrsina;
	double cena;
} Parcela;

int main() {
	FILE *ulaz = fopen("parcele.txt", "r");
	FILE *izlaz = fopen("najskuplje.txt", "w");
	Parcela p, top[3];
	int i, j, count = 0;
	
	for (i = 0; i < 3; i++) top[i].cena = -1;
	
	while (fscanf(ulaz, "%5s %lf %lf", p.sifra, &p.povrsina, &p.cena) == 3) {
		double cena_m2 = p.cena / p.povrsina;
		for (i = 0; i < 3; i++) {
		if (cena_m2 > top[i].cena) {
			for (j = 2; j > i; j--) top[j] = top[j - 1];
			strcpy(top[i].sifra, p.sifra);
			top[i].cena = cena_m2;
			break;
		}
	}
}

for (i = 0; i < 3; i++) fprintf(izlaz, "%s\n", top[i].sifra);
fclose(ulaz);
fclose(izlaz);
return 0;
}
