#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
struct Autobuz {
	int linie;
	char* capatLinie;
};

struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(strlen(capat) + 1);
	strcpy(a.capatLinie, capat);
	return a;
}

//functie de inserare la sf in lista principala

void inserareListaPrincipala(NodPrincipal** graf, Autobuz a) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;
	if (*graf != NULL) {
		NodPrincipal* aux = (*graf);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		(*graf) = nod;
	}
}

//functie de cautare dupa linie

NodPrincipal* cautaLinie(NodPrincipal* graf, int linie) {
	while (graf && graf->info.linie != linie) {
		graf = graf->next;
	}
	return graf;
}

//functie de inserare la sf in lista secundara

NodSecundar* inserareListaSecundara(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

//functie de inserare muchie

void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop) {
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);

}

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initializareAutobuz(0, "Romana"));
	inserareListaPrincipala(&graf, initializareAutobuz(1, "Universitate"));
	inserareListaPrincipala(&graf, initializareAutobuz(2, "Unirii"));
	inserareListaPrincipala(&graf, initializareAutobuz(3, "Victoriei"));
	inserareListaPrincipala(&graf, initializareAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
}