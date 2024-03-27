#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct NodLdi {
    NodLdi* prev;
    NodLdi* next;
    Santier info;
};

struct ListaDubla {
    NodLdi* prim;
    NodLdi* ultim;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;

    return santier;
}

void afisareSantier(Santier santier) {
    printf("\nSantierul %s are %d muncitori si %5.2f m^2", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

float densitate(Santier santier) {
    if (santier.suprafata != 0) {
        return santier.nrMuncitori / santier.suprafata;
    }
    return 0;
}

void inserareInceput(ListaDubla* lista, Santier s) {
    NodLdi* aux = (NodLdi*)malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;
    if (lista->prim != NULL) {
        lista->prim->prev = aux;
    }
    else {
        lista->ultim = aux;
    }
    lista->prim = aux;
}

void afisareLdiDeLaInceput(ListaDubla lista) {
    printf("\n\n\n");
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareSantier(nod->info);
    }
}

//stergere nod cu santierul cu un nume dat
void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier) {
    NodLdi* nod = lista->prim;
    while (nod != NULL) {
        if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
            if (nod->prev == NULL) {
                if (nod->next == NULL) {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else {
                if (nod->next == NULL) {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }
            free(nod->info.numeProiect);
            free(nod);
            nod = NULL;
            //break;
        }
        else {
            nod = nod->next;
        }
    }
}

void stergereListaDli(ListaDubla* lista) {
    if (lista != NULL) {
        NodLdi* aux = lista->prim;
        while (aux != NULL) {
            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

//nr total muncitori
int nrTotalMuncitori(ListaDubla lista) {
    int total = 0;
    NodLdi* i = lista.prim;
    while (i != NULL) {
        total += i->info.nrMuncitori;
        i = i->next;
    }
    return total;
}

//nr muncitori de pe santierele cu suprafata mai mica decat x
int nrMuncitoriSub(ListaDubla lista, float smax) {
    int total = 0;
    NodLdi* i = lista.prim;
    while (i != NULL) {
        if (i->info.suprafata < smax) {
            total += i->info.nrMuncitori;
        }
        i = i->next;
    }
    return total;
}

int main() {

    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 15, 200);
    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    afisareLdiDeLaInceput(lista);
    printf("\n");
    printf("\nNumar total muncitori: %d", nrTotalMuncitori(lista));
    printf("\nNumar total muncitori de pe santierele cu max 300 mp: %d", nrMuncitoriSub(lista, 350));
    /*stergereSantierDupaNume(&lista, "Santier 2");
    afisareLdiDeLaInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 1");
    afisareLdiDeLaInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 3");
    afisareLdiDeLaInceput(lista);*/
    stergereListaDli(&lista);
    afisareLdiDeLaInceput(lista);
    return 0;
}