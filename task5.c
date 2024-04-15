#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Disc Disc;
struct Disc {
	char* artist;
	int nrPiese;
	float durata;
};

typedef struct Nod Nod;
struct Nod {
	Disc info;
	Nod* next;
};

Nod* adaugareInceput(Nod* lista, Disc d) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = d;
	nod->next = lista;
	return nod;
}

void adaugareSfarsit(Nod** lista, Disc d) {
	if (*lista == NULL) {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = d;
		nod->next = NULL;
		*lista = nod;
	}
	else {
		Nod* current = *lista;
		while (current->next != NULL) {
			current = current->next;
		}
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = d;
		nod->next = NULL;
		current->next = nod;
	}
}

void afiseazaDisc(Disc d) {
	printf("Discul artistului %s are %d piese si dureaza %.2f minute.\n", d.artist, d.nrPiese, d.durata);
}

Nod* citireFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	char buffer[100];
	char separator[] = ",\n";
	Nod* lista = NULL;
	while (fgets(buffer, 100, f) != NULL) {
		Disc d;
		char* token = strtok(buffer, separator);
		d.artist = (char*)malloc(strlen(token) + 1);
		strcpy(d.artist, token);
		token = strtok(NULL, separator);
		d.nrPiese = atoi(token);
		token = strtok(NULL, separator);
		d.durata = atof(token);
		adaugareSfarsit(&lista, d);
	}
	fclose(f);
	return lista;
}

void afisareLista(Nod* lista) {
	while (lista != NULL) {
		afiseazaDisc(lista->info);
		lista = lista->next;
	}
}

void stergereNodDupaIndex(Nod** lista, int poz) {
	Nod* aux = (*lista);
	if (poz == 1) {
		Nod* nodSters = (*lista);
		(*lista) = (*lista)->next;
		free(nodSters);
	}
	else {
		int index = 1;
		while (aux->next != NULL && index < poz - 2) {
			index++;
			aux = aux->next;
		}
		if (aux == NULL || aux->next == NULL) {
			printf("Nu exista pozitia %d\n", poz);
		}
		else {
			Nod* nodSters = aux->next;
			aux->next = aux->next->next;
			free(nodSters);
		}
	}
}

Disc* adaugareVector(Disc* v, int* n, Disc d) {
	Disc* vNou = (Disc*)malloc(sizeof(Disc) * ((*n) + 1));
	for (int i = 0;i < *n;i++) {
		vNou[i] = v[i];
	}
	vNou[*n] = d;
	(*n)++;
	free(v);
	return vNou;
}

Disc* discuriMelodiiPeste10Min(Nod* lista, int* n) {
	*n = 0;
	Disc* v = NULL;
	while (lista != NULL) {
		if (lista->info.durata / lista->info.nrPiese >= 10) {
			v = adaugareVector(v, n, lista->info);
		}
		lista = lista->next;
	}
	return v;
}

void sortareLista(Nod** lista) {
	if (*lista != NULL && (*lista)->next != NULL) {
		Nod* listaSort = NULL;
		Nod* aux = *lista;

		while (aux != NULL) {
			Nod* next = aux->next;
			if (listaSort == NULL || strlen(aux->info.artist) < strlen(listaSort->info.artist)) {
				aux->next = listaSort;
				listaSort = aux;
			}
			else {
				Nod* temp = listaSort;
				while (temp->next != NULL && strlen(temp->next->info.artist) < strlen(aux->info.artist)) {
					temp = temp->next;
				}
				aux->next = temp->next;
				temp->next = aux;
			}
			aux = aux->next;
		}

		*lista = listaSort;
	}
}


void inserareSortata(Nod** lista, Disc d) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = d;
	nou->next = NULL;

	if (*lista == NULL || strlen(d.artist) < strlen((*lista)->info.artist)) {
		nou->next = *lista;
		*lista = nou;
		return;
	}

	Nod* current = *lista;
	while (current->next != NULL && strlen(current->next->info.artist) < strlen(d.artist)) {
		current = current->next;
	}

	nou->next = current->next;
	current->next = nou;
}


int main() {
	Nod* lista = NULL;
	lista = citireFisier("discuri.txt");
	afisareLista(lista);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	stergereNodDupaIndex(&lista, 2);
	stergereNodDupaIndex(&lista, 8);
	afisareLista(lista);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	int n;
	Disc* discuri = discuriMelodiiPeste10Min(lista, &n);
	for (int i = 0;i < n;i++) {
		afiseazaDisc(discuri[i]);
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	Disc d;
	d.artist = "cristiana";
	d.nrPiese = 10;
	d.durata = 45;
	sortareLista(&lista);
	inserareSortata(&lista, d);
	afisareLista(lista);
	return 0;
}