#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Cristiana Cris;
struct Cristiana {
	int nrPisici;
	char* vibe;
};

typedef struct Nod Nod;
struct Nod {
	Cris info;
	Nod* next;
};

Cris initializareCris(int nr, const char* vibe) {
	Cris c;
	c.nrPisici = nr;
	c.vibe = (char*)malloc(strlen(vibe) + 1);
	strcpy(c.vibe, vibe);
	return c;
}

void afisareCris(Cris c) {
	printf("Cris %s are %d pisici\n", c.vibe, c.nrPisici);
}

void adaugareInceput(Nod** lista, Cris c) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = c;
	nod->next = (*lista);
	(*lista) = nod;
}

void adaugareSfarsit(Nod** lista, Cris c) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = c;
	nod->next = NULL;
	if (*lista) {
		Nod* aux = *lista;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		*lista = nod;
	}
}

void afisareLista(Nod* lista) {
	while (lista != NULL) {
		afisareCris(lista->info);
		lista = lista->next;
	}
}

Cris vibeCheck(Nod** lista, const char* vibe) {
	Nod* aux = *lista;
	Nod* prev = NULL;
	while (aux && strcmp(aux->info.vibe, vibe) != 0) {
		prev = aux;
		aux = aux->next;
	}
	if (aux == NULL) {
		return initializareCris(-1, "-");
	}
	else {
		if (prev == NULL) {
			(*lista) = aux->next;
		}
		else {
			prev->next = aux->next;
		}
		Cris c = initializareCris(aux->info.nrPisici, aux->info.vibe);
		free(aux->info.vibe);
		free(aux);
		return c;
	}
}

void stergereLista(Nod** lista) {
	while (*lista) {
		Nod* aux = (*lista)->next;
		free((*lista)->info.vibe);
		free((*lista));
		(*lista) = aux;
	}
	*lista = NULL;
}

typedef struct NodListaDubla Nod2;
struct NodListaDubla {
	Cris info;
	Nod2* next;
	Nod2* prev;
};

typedef struct ListaDubluInlantuita ListaD;
struct ListaDubluInlantuita {
	Nod2* prim;
	Nod2* ultim;
};

void adaugareInceput2(ListaD* ld, Cris c) {
	Nod2* nod = (Nod2*)malloc(sizeof(Nod2));
	nod->info = c;
	nod->next = ld->prim;
	nod->prev = NULL;
	if (ld->prim != NULL) {
		ld->prim->prev = nod;
	}
	else {
		ld->ultim = nod;
	}
	ld->prim = nod;
}

void adaugareSfarsit2(ListaD* ld, Cris c) {
	Nod2* nod = (Nod2*)malloc(sizeof(Nod2));
	nod->info = c;
	nod->next = NULL;
	nod->prev = ld->ultim;
	if (ld->ultim != NULL) {
		ld->ultim->next = nod;
	}
	else {
		ld->prim = nod;
	}
	ld->ultim = nod;
}

void afisareLista2(ListaD ld) {
	Nod2* aux = ld.prim;
	while (aux) {
		afisareCris(aux->info);
		aux = aux->next;
	}
}

Cris pisiCheck(ListaD* ld, int nr) {
	Nod2* aux = ld->prim;
	while (aux) {
		if (aux->info.nrPisici == nr) {
			if (aux->prev == NULL) {
				if (aux->next == NULL) {
					ld->prim = NULL;
					ld->ultim = NULL;
				}
				else {
					ld->prim = aux->next;
					aux->next->prev = NULL;
				}
			}
			else {
				if (aux->next == NULL) {
					ld->ultim = aux->prev;
					aux->prev->next = NULL;
				}
				else {
					aux->next->prev = aux->prev;
					aux->prev->next = aux->next;
				}
			}
			Cris c = initializareCris(aux->info.nrPisici, aux->info.vibe);
			free(aux->info.vibe);
			free(aux);
			aux = NULL;
			return c;
		}
		else {
			aux = aux->next;
		}
	}
	return initializareCris(-1, "-");
}

int main() {
	Cris c1 = initializareCris(0, "sad");
	Cris c2 = initializareCris(1, "meh");
	Cris c3 = initializareCris(2, "ok");
	Cris c4 = initializareCris(3, "cute");
	Cris c5 = initializareCris(4, "EUPHORIA");
	/*Nod* lista1 = NULL;
	adaugareInceput(&lista1, c1);
	adaugareInceput(&lista1, c2);
	adaugareInceput(&lista1, c3);
	adaugareInceput(&lista1, c4);
	adaugareInceput(&lista1, c5);
	afisareLista(lista1);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++\n\n");
	Nod* lista2 = NULL;
	adaugareSfarsit(&lista2, c1);
	adaugareSfarsit(&lista2, c2);
	adaugareSfarsit(&lista2, c3);
	adaugareSfarsit(&lista2, c4);
	adaugareSfarsit(&lista2, c5);
	afisareLista(lista2);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++\n\n");
	Cris c6 = vibeCheck(&lista1, "meh");
	Cris c7 = vibeCheck(&lista1, "nu");
	afisareCris(c6);
	afisareCris(c7);*/
	ListaD ld;
	ld.prim = NULL;
	ld.ultim = NULL;
	adaugareInceput2(&ld, c1);
	adaugareInceput2(&ld, c2);
	adaugareInceput2(&ld, c3);
	adaugareInceput2(&ld, c4);
	adaugareInceput2(&ld, c5);
	afisareLista2(ld);
	Cris c6 = pisiCheck(&ld, 2);
	afisareLista2(ld);
	return 0;
}