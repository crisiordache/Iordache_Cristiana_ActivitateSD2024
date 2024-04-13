#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Disc Disc;
struct Disc {
	char* artist;
	int nrPiese;
	float* durate;
};

Disc citireDiscTastatura() {
	Disc d;
	printf("\nIntroduceti numele artistului: ");
	char buffer[100];
	gets(buffer, 100, stdin);
	d.artist = (char*)malloc(strlen(buffer) + 1);
	strcpy(d.artist, buffer);
	printf("\nIntroduceti numarul de piese: ");
	scanf("%d", &d.nrPiese);
	d.durate = (float*)malloc(d.nrPiese * sizeof(float));
	for (int i = 0;i < d.nrPiese;i++) {
		printf("\nIntroduceti durata piesei %d: ", i + 1);
		scanf("%f", &d.durate[i]);
	}
	return d;
}

Disc initializareDisc(const char* artist, int nrPiese, float* durate) {
	Disc d;
	d.artist = (char*)malloc(strlen(artist) + 1);
	strcpy(d.artist, artist);
	d.nrPiese = nrPiese;
	d.durate = (float*)malloc(d.nrPiese * sizeof(float));
	for (int i = 0;i < d.nrPiese;i++) {
		d.durate[i] = durate[i];
	}
	return d;
}

void afisareDisc(Disc d) {
	printf("Discul artistului %s are %d piese\n", d.artist, d.nrPiese);
	for (int i = 0;i < d.nrPiese;i++) {
		printf("Durata piesei %d este %.2f\n", i + 1, d.durate[i]);
	}
}

float durataMedie(Disc d) {
	float s = 0;
	for (int i = 0;i < d.nrPiese;i++) {
		s += d.durate[i];
	}
	return s / d.nrPiese;
}

void modificareDurata(Disc* d, float durata, int poz) {
	if (poz >= 0 && poz < d->nrPiese) {
		d->durate[poz] = durata;
	}
}

void afisareVector(Disc* v, int n) {
	for (int i = 0;i < n;i++) {
		afisareDisc(v[i]);
		printf("\n");
	}
}

Disc* filtrareDurataMedie(Disc* v, int n, int* dim) {
	*dim = 0;
	for (int i = 0; i < n; i++) {
		if (durataMedie(v[i]) > 2.5) {
			(*dim)++;
		}
	}
	Disc* vf = (Disc*)malloc(sizeof(Disc) * (*dim));
	int index = 0;
	for (int i = 0; i < n; i++) {
		if (durataMedie(v[i]) > 2.5) {
			vf[index] = initializareDisc(v[i].artist, v[i].nrPiese, v[i].durate);
			index++;
		}
	}
	return vf;
}


void filtrareLungimeNume(Disc* vechi, int nVechi, Disc** nou, int* nNou) {
	(*nNou) = 0;
	for (int i = 0; i < nVechi; i++) {
		if (strlen(vechi[i].artist) > 5) {
			(*nNou)++;
		}
	}
	if ((*nNou) > 0) {
		(*nou) = (Disc*)malloc(sizeof(Disc) * (*nNou));
		int index = 0;
		for (int i = 0; i < nVechi; i++) {
			if (strlen(vechi[i].artist) > 5) {
				(*nou)[index++] = initializareDisc(vechi[i].artist, vechi[i].nrPiese, vechi[i].durate);
			}
		}
	}
}

Disc* concatenare(Disc* v1, int n1, Disc* v2, int n2, int* nc) {
	*nc = n1 + n2;
	Disc* vc = (Disc*)malloc(sizeof(Disc) * (*nc));
	for (int i = 0;i < (*nc);i++) {
		if (i < n1) {
			vc[i] = initializareDisc(v1[i].artist, v1[i].nrPiese, v1[i].durate);
		}
		else {
			vc[i] = initializareDisc(v2[i - n1].artist, v2[i - n1].nrPiese, v2[i - n1].durate);
		}
	}
	return vc;
}

void dezalocareVector(Disc** v, int* n) {
	for (int i = 0; i < *n; i++) {
		free((*v)[i].artist);
		free((*v)[i].durate);
	}
	free(*v);
	(*v) = NULL;
	(*n) = 0;
}

int main()
{
	/*Disc disc = citireDiscTastatura();
	afisareDisc(disc);
	modificareDurata(&disc, 4, 2);
	afisareDisc(disc);*/
	int n = 5;
	float durate1[] = { 2,3.4,2.1 };
	float durate2[] = { 1.2,3.7 };
	float durate3[] = { 5.4,3,2,1.5 };
	Disc d1 = initializareDisc("ABBA", 3, durate1);
	Disc d2 = initializareDisc("Blondie", 2, durate2);
	Disc d3 = initializareDisc("Elvis Presley", 4, durate3);
	Disc d4 = initializareDisc("Patsie Cline", 3, durate1);
	Disc d5 = initializareDisc("Jay Z", 4, durate3);
	Disc* vector = (Disc*)malloc(n * sizeof(Disc));
	vector[0] = d1;
	vector[1] = d2;
	vector[2] = d3;
	vector[3] = d4;
	vector[4] = d5;
	afisareVector(vector, n);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	for (int i = 0;i < n;i++) {
		printf("Discul %d: %5.2f\n", i + 1, durataMedie(vector[i]));
	}
	int dim = 0;
	Disc* vectorNou = filtrareDurataMedie(vector, n, &dim);
	afisareVector(vectorNou, dim);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	Disc* altVector = NULL;
	int altN = 0;
	filtrareLungimeNume(vector, n, &altVector, &altN);
	afisareVector(altVector, altN);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	int nc = 0;
	Disc* vectorConcat = concatenare(vectorNou, dim, altVector, altN, &nc);
	afisareVector(vectorConcat, nc);
	dezalocareVector(&vector, &n);
	dezalocareVector(&vectorNou, &dim);
	dezalocareVector(&altVector, &altN);
	return 0;
}
