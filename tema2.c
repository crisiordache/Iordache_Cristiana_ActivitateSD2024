#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct BatonCiocolata
{
	char* marca;
	float gramaj;
	int nrKcal;
};

void afisareBatonCiocolata(struct BatonCiocolata* bc)
{
	printf("\nMarca: ");
	if (bc->marca != NULL)
		printf(bc->marca);
	else
		printf("-");
	printf("\nGramaj: %5.2f", bc->gramaj);
	printf("\nNumarul de calorii: %d", bc->nrKcal);
}

struct BatonCiocolata citireBatonCiocolata()
{
	struct BatonCiocolata bc;
	printf("\nIntroduceti marca: ");
	bc.marca = (char*)malloc(50);
	fgets(bc.marca, 50, stdin);
	printf("\nIntroduceti gramajul: ");
	scanf("%f", &bc.gramaj);
	printf("\nIntroduceti numarul de calorii: ");
	scanf("%i", &bc.nrKcal);
	return bc;
}

float caloriiPerGram(struct BatonCiocolata* bc)
{
	return bc->nrKcal / bc->gramaj;
}

void schimbaMarca(struct BatonCiocolata* bc, const char* marca)
{
	if (marca != NULL)
	{
		free(bc->marca);
		bc->marca = NULL;
		bc->marca = (char*)malloc(strlen(marca) + 1);
		strcpy(bc->marca, marca);
		printf("\nNoua marca este %s", bc->marca);
	}
	else
		printf("\nNu s-a produs nicio modificare");
}

struct BatonCiocolata initializareBatonCiocolata(const char* marca, float gramaj, int nrKcal)
{
	struct BatonCiocolata bc;
	if (marca != NULL)
	{
		bc.marca = (char*)malloc(strlen(marca) + 1);
		strcpy(bc.marca, marca);
	}
	else
	{
		bc.marca = (char*)malloc(strlen("N/A") + 1);
		strcpy(bc.marca, "N/A");
	}
	if (gramaj > 0)
		bc.gramaj = gramaj;
	else
		bc.marcaj = 0;
	if (nrKcal > 0)
		bc.nrKcal = nrKcal;
	else
		bc.nrKcal = 0;
	return bc;
}

void dezalocareBatonCiocolata(struct BatonCiocolata* bc)
{
	free(bc->marca);
	bc->marca = NULL;
}

int main()
{
	struct BatonCiocolata bc1;
	bc1.marca = (char*)malloc(strlen("Mars") + 1);
	strcpy(bc1.marca, "Mars");
	bc1.gramaj = 50.7;
	bc1.nrKcal = 236;
	struct BatonCiocolata bc2 = initializareBatonCiocolata("Snickers", 68.5, 291);
	afisareBatonCiocolata(bc2);
	return 0;
}