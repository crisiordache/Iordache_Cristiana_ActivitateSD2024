#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini)
{
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++)
	{
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL)
		free(masini);
	return aux;
}

void citireMatrice(const char* numeFisier, struct Masina** matrice, int nrLinii, int* nrCol)
{
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char separator[] = ",\n";
	while (fgets(buffer, 100, file) != NULL)
	{
		char* token = strtok(buffer, separator);
		struct Masina m;
		m.id = atoi(token);
		token = strtok(NULL, separator);
		m.producator = (char*)malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, separator);
		m.nrUsi = atoi(token);
		token = strtok(NULL, separator);
		m.pret = atof(token);

		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrCol[m.nrUsi - 2]));


	}
	fclose(file);
	//return matrice;
}

void afisareMatrice(struct Masina** matrice, int* nrCol, int nrLinii)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			printf("%d. %s, %d, %5.2f lei \t", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
		}
		printf("\n");
	}
}

float pretMediuDupaUsi(struct Masina** matrice, int* nrCol, int nrLinii, int nrU)
{
	if (nrU >= 2 && nrU <= 4)
	{
		float s = 0;
		if (nrCol[nrU - 2] != 0)
		{
			for (int i = 0; i < nrCol[nrU - 2]; i++)
			{
				s += matrice[nrU - 2][i].pret;
			}
			return s / nrCol[nrU - 2];
		}
		else
			return 0;
	}
	else
		return 0;
}

void afisareMasina(struct Masina m)
{
	printf("\n%d. %s, %d, %5.2f lei \t", m.id, m.producator, m.nrUsi, m.pret);
}

struct Masina getMasinaByID(struct Masina** matrice, int* nrCol, int nrLinii, int id)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			if (matrice[i][j].id == id)
				return matrice[i][j];
		}
	}
	struct Masina m;
	m.id = -1;
	m.nrUsi = 0;
	m.producator = NULL;
	m.pret = 0;
	return m;
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrCol)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < (*nrCol)[i]; j++)
		{
			free((*matrice)[i][j].producator);
		}
		free((*matrice)[i]);
	}
	free(*nrCol);
	free(*matrice);
	*nrCol = NULL;
	*matrice = NULL;
}

int main()
{
	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	nrCol = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (struct Masina*)malloc(sizeof(struct Masina) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrCol[i] = 0;
		matrice[i] = NULL;
	}
	citireMatrice("masini.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrCol, nrLinii);
	float m = pretMediuDupaUsi(matrice, nrCol, nrLinii, 4);
	printf("\n%5.2f", m);
	struct Masina masina = getMasinaByID(matrice, nrCol, nrLinii, 2);
	afisareMasina(masina);
	dezalocareMatrice(matrice, nrLinii, nrCol);
	return 0;
}