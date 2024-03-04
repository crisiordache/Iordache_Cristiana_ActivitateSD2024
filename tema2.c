#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct BatonCiocolata
{
	char* marca;
	float gramaj;
	int nrKcal;
};

void afisareBatonCiocolata(struct BatonCiocolata bc)
{
	printf("\nBatonul %s are %5.2f g si %d kcal", bc.marca, bc.gramaj, bc.nrKcal);
}

struct BatonCiocolata initializareBatonCiocolata(const char* marca, float gramaj, int nrKcal)
{
	struct BatonCiocolata bc;
	bc.marca = (char*)malloc(sizeof(char*) * (strlen(marca) + 1));
	strcpy(bc.marca, marca);
	bc.gramaj = gramaj;
	bc.nrKcal = nrKcal;
	return bc;
}

void afisareVectorBC(struct BatonCiocolata* vbc, int nrBC)
{
	for (int i = 0;i < nrBC;i ++)
	{
		afisareBatonCiocolata(vbc[i]);
	}
}

struct BatonCiocolata* getBatoaneMari(struct BatoaneCiocolata* vbc, int nrBC, float cantitateMin, int* nrBMari)
{
	*nrBMari = 0;
	for (int i = 0;i < nrBC;i++)
	{
		if (vbc[i].gramaj > cantitateMin)
			(*nrBMari)++;
	}
	struct BatonCiocolata* bMari = (struct BatonCiocolata*)malloc(sizeof(struct BatonCiocolata) * (*nrBMari));
	int index = 0;
	for (int i = 0;i < nrBC;i++)
	{
		if (vbc[i].gramaj > cantitateMin)
			bMari[index++] = initializareBatonCiocolata(vbc[i].marca, vbc[i].gramaj, vbc[i].nrKcal);
	}
	return bMari;
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
	struct BatonCiocolata bc3 = initializareBatonCiocolata("Twix", 53.2, 280);
	struct BatonCiocolata bc4 = initializareBatonCiocolata("KitKat", 62, 237);
	struct BatonCiocolata bc5 = initializareBatonCiocolata("Milky Way", 65.9, 321);
	struct BatonCiocolata bc6 = initializareBatonCiocolata("Fagaras", 34.6, 210);
	struct BatonCiocolata bc7 = initializareBatonCiocolata("Lion", 48, 276);
	int nrBC = 7;
	struct BatonCiocolata* vectorBC = (struct BatonCiocolata*)malloc(sizeof(struct BatonCiocolata) * nrBC);
	vectorBC[0] = bc1;
	vectorBC[1] = bc2;
	vectorBC[2] = bc3;
	vectorBC[3] = bc4;
	vectorBC[4] = bc5;
	vectorBC[5] = bc6;
	vectorBC[6] = bc7;
	afisareVectorBC(vectorBC, nrBC);
	int nrBMari = 0;
	struct BatonCiocolata* batoaneMari = getBatoaneMari(vectorBC, nrBC, 50, nrBMari);
	afisareVectorBC(batoaneMari,nrBMari);
	return 0;
}