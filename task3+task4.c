#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Disc Disc;
struct Disc {
	char* artist;
	int nrPiese;
	float* durate;
};

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

Disc* adaugareInVector(Disc* discuri, int* nrDiscuri, Disc disc) {
	Disc* aux = (Disc*)malloc(sizeof(Disc) * ((*nrDiscuri) + 1));
	for (int i = 0;i < (*nrDiscuri);i++) {
		aux[i] = discuri[i];
	}
	aux[(*nrDiscuri)] = disc;
	(*nrDiscuri)++;
	if (discuri != NULL) {
		free(discuri);
	}
	return aux;
}

Disc* citireVector(const char* numeFisier, int* nrDiscuri) {
	FILE* f = fopen(numeFisier, "r");
	char buffer[100];
	char separator[] = ",\n";
	Disc* discuri = NULL;
	(*nrDiscuri) = 0;
	while (fgets(buffer, 100, f) != NULL) {
		char* token = strtok(buffer, separator);
		Disc disc;
		disc.artist = (char*)malloc(strlen(token) + 1);
		strcpy(disc.artist, token);
		token = strtok(NULL, separator);
		disc.nrPiese = atoi(token);
		disc.durate = (float*)malloc(sizeof(float) * disc.nrPiese);
		for (int i = 0; i < disc.nrPiese; i++) {
			token = strtok(NULL, separator);
			disc.durate[i] = atof(token);
		}
		discuri = adaugareInVector(discuri, nrDiscuri, disc);
	}
	fclose(f);
	return discuri;
}

void citireMatrice(const char* numeFisier, Disc** matrice, int* nrCol, int nrLinii) {
	FILE* f = fopen(numeFisier, "r");
	char buffer[100];
	char separator[] = ",\n";
	while (fgets(buffer, 100, f) != NULL) {
		char* token = strtok(buffer, separator);
		Disc disc;
		disc.artist = (char*)malloc(strlen(token) + 1);
		strcpy(disc.artist, token);
		token = strtok(NULL, separator);
		disc.nrPiese = atoi(token);
		disc.durate = (float*)malloc(sizeof(float) * disc.nrPiese);
		for (int i = 0; i < disc.nrPiese; i++) {
			token = strtok(NULL, separator);
			disc.durate[i] = atof(token);
		}
		matrice[disc.nrPiese - 2] = adaugareInVector(matrice[disc.nrPiese - 2], &(nrCol[disc.nrPiese - 2]), disc);
	}
	fclose(f);
}

void afisareDisc(Disc d) {
	printf("Discul artistului %s are %d piese\n", d.artist, d.nrPiese);
	for (int i = 0;i < d.nrPiese;i++) {
		printf("Durata piesei %d este %.2f\n", i + 1, d.durate[i]);
	}
}

void afisareVector(Disc* v, int n) {
	for (int i = 0;i < n;i++) {
		afisareDisc(v[i]);
		printf("\n");
	}
}

void afisareMatrice(Disc** matrice, int* nrCol, int nrLinii) {
	for (int i = 0;i < nrLinii;i++) {
		printf("Linia %d\n", i + 1);
		for (int j = 0;j < nrCol[i];j++) {
			afisareDisc(matrice[i][j]);
		}
		printf("\n");
	}
}

int cautareVector(int* v, int n, int val) {
	for (int i = 0;i < n;i++) {
		if (v[i] == val) {
			return 1;
		}
	}
	return 0;
}

Disc** sortareLiniiComplicata(Disc** matrice, int** nrCol, int nrLinii) {
	int* nrColVechi = (int*)malloc(sizeof(int) * nrLinii);
	for (int i = 0;i < nrLinii;i++) {
		nrColVechi[i] = (*nrCol)[i];
	}
	for (int i = 0;i < nrLinii - 1;i++) {
		for (int j = i + 1;j < nrLinii;j++) {
			if ((*nrCol)[i] > (*nrCol)[j]) {
				int aux = (*nrCol)[i];
				(*nrCol)[i] = (*nrCol)[j];
				(*nrCol)[j] = aux;
			}
		}
	}
	int* index = (int*)malloc(sizeof(int) * nrLinii);
	for (int i = 0;i < nrLinii;i++) {
		index[i] = 0;
	}
	for (int i = 0;i < nrLinii;i++) {
		for (int j = 0;j < nrLinii;j++) {
			if (nrColVechi[i] == (*nrCol)[j] && cautareVector(index, nrLinii, j) == 0) {
				index[i] = j;
				printf("%d ", j);
			}
		}
	}
	Disc** aux = (Disc*)malloc(sizeof(Disc) * nrLinii);
	for (int i = 0;i < nrLinii;i++) {
		aux[i] = (Disc*)malloc(sizeof(Disc) * (*nrCol)[i]);
		for (int j = 0;j < (*nrCol)[i];j++) {
			aux[i][j] = matrice[index[i]][j];
		}
	}
	return aux;
}

void sortareLiniiMaiBuna(Disc*** matrice, int** nrCol, int nrLinii) {
	for (int i = 0;i < nrLinii - 1;i++) {
		for (int j = i + 1;j < nrLinii;j++) {
			if ((*nrCol)[i] > (*nrCol)[j]) {
				int aux = (*nrCol)[i];
				(*nrCol)[i] = (*nrCol)[j];
				(*nrCol)[j] = aux;

				Disc* daux = (*matrice)[i];
				(*matrice)[i] = (*matrice)[j];
				(*matrice)[j] = daux;
			}
		}
	}
}

void dezalocareMatrice(Disc*** matrice, int** nrCol, int* nrLinii) {
	for (int i = 0;i < (*nrLinii);i++) {
		for (int j = 0;j < (*nrCol)[i];i++) {
			free((*matrice)[i][j].artist);
			free((*matrice)[i][j].durate);
		}
		free((*matrice)[i]);
	}
	free((*nrCol));
	free((*matrice));
	(*nrCol) = NULL;
	(*matrice) = NULL;
	(*nrLinii) = 0;
}

int main()
{
	/*int nrDiscuri = 0;
	Disc* discuri = citireVector("discuri.txt", &nrDiscuri);
	afisareVector(discuri, nrDiscuri);*/
	Disc** matrice;
	int nrLinii = 3;
	int* nrCol = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (Disc*)malloc(sizeof(Disc) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrCol[i] = 0;
		matrice[i] = NULL;
	}
	citireMatrice("discuri.txt", matrice, nrCol, nrLinii);
	afisareMatrice(matrice, nrCol, nrLinii);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	/*Disc** matriceSort = sortareLiniiComplicata(matrice, &nrCol, nrLinii);
	afisareMatrice(matriceSort, nrCol, nrLinii);*/
	sortareLiniiMaiBuna(&matrice, &nrCol, nrLinii);
	afisareMatrice(matrice, nrCol, nrLinii);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	dezalocareMatrice(&matrice, &nrCol, &nrLinii);
	afisareMatrice(matrice, nrCol, nrLinii);
	return 0;
}
