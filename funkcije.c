#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"
#include "tenisica.h"

int brojOperacija = 0;

Tenisica* rekurzivnaPretraga(Tenisica* tenisice, int n, int id, int index) {
    if (index >= n) return NULL;
    if (tenisice[index].id == id) return &tenisice[index];
    return rekurzivnaPretraga(tenisice, n, id, index + 1);
}

void dodajTenisicu(Tenisica** tenisice, int* n, int* kapacitet) {
    if (*n >= *kapacitet) {
        *kapacitet *= 2;
        Tenisica* temp = (Tenisica*)realloc(*tenisice, *kapacitet * sizeof(Tenisica));
        if (temp == NULL) {
            perror("Greska pri realokaciji memorije");
            return;
        }
        *tenisice = temp;
    }
    Tenisica t;
    t.id = *n + 1;
    printf("Brend: ");
    scanf(" %49[^\n]", t.brend);
    printf("Model: ");
    scanf(" %49[^\n]", t.model);
    printf("Velicina: ");
    scanf("%f", &t.velicina);
    printf("Cijena: ");
    scanf("%f", &t.cijena);
    printf("Kolicina: ");
    scanf("%d", &t.kolicina);
    (*tenisice)[*n] = t;
    (*n)++;
    brojOperacija++;
    printf("Tenisica uspjesno dodana!\n");
}

void ispisTenisica(Tenisica* tenisice, int n) {
    if (n == 0) {
        printf("Skladiste je prazno!\n");
        return;
    }
    printf("\n--- POPIS TENISICA ---\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d\n", tenisice[i].id);
        printf("Brend: %s\n", tenisice[i].brend);
        printf("Model: %s\n", tenisice[i].model);
        printf("Velicina: %.1f\n", tenisice[i].velicina);
        printf("Cijena: %.2f\n", tenisice[i].cijena);
        printf("Kolicina: %d\n", tenisice[i].kolicina);
        ispisLinije();
    }
}

void urediTenisicu(Tenisica* tenisice, int n) {
    if (n == 0) {
        printf("Skladiste je prazno!\n");
        return;
    }
    int id;
    printf("Unesite ID tenisice koju zelite urediti: ");
    scanf("%d", &id);
    Tenisica* t = rekurzivnaPretraga(tenisice, n, id, 0);
    if (t != NULL) {
        printf("Novi brend: ");
        scanf(" %49[^\n]", t->brend);
        printf("Novi model: ");
        scanf(" %49[^\n]", t->model);
        printf("Nova velicina: ");
        scanf("%f", &t->velicina);
        printf("Nova cijena: ");
        scanf("%f", &t->cijena);
        printf("Nova kolicina: ");
        scanf("%d", &t->kolicina);
        brojOperacija++;
        printf("Tenisica uspjesno uredena!\n");
    }
    else {
        printf("Tenisica s ID-om %d nije pronadena!\n", id);
    }
}

void obrisiTenisicu(Tenisica** tenisice, int* n) {
    if (*n == 0) {
        printf("Skladiste je prazno!\n");
        return;
    }
    int id;
    printf("Unesite ID tenisice koju zelite obrisati: ");
    scanf("%d", &id);
    for (int i = 0; i < *n; i++) {
        if ((*tenisice)[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                (*tenisice)[j] = (*tenisice)[j + 1];
            }
            (*n)--;
            brojOperacija++;
            printf("Tenisica uspjesno obrisana!\n");
            return;
        }
    }
    printf("Tenisica s ID-om %d nije pronadena!\n", id);
}

void bsearchPretraga(Tenisica* tenisice, int n) {
    if (n == 0) {
        printf("Skladiste je prazno!\n");
        return;
    }
    qsort(tenisice, n, sizeof(Tenisica), usporediBrend);
    char brend[50];
    printf("Unesite brend za pretragu (bsearch): ");
    scanf(" %49[^\n]", brend);
    Tenisica kljuc;
    strcpy(kljuc.brend, brend);
    Tenisica* rezultat = (Tenisica*)bsearch(&kljuc, tenisice, n, sizeof(Tenisica), usporediBrend);
    if (rezultat != NULL) {
        printf("ID: %d | Brend: %s | Model: %s | Velicina: %.1f | Cijena: %.2f | Kolicina: %d\n",
            rezultat->id, rezultat->brend, rezultat->model,
            rezultat->velicina, rezultat->cijena, rezultat->kolicina);
    }
    else {
        printf("Tenisica s brendom '%s' nije pronadena!\n", brend);
    }
}

void pretraziTenisice(Tenisica* tenisice, int n) {
    if (n == 0) {
        printf("Skladiste je prazno!\n");
        return;
    }
    int izbor;
    printf("\n--- PRETRAGA ---\n");
    printf("1. Po brendu\n");
    printf("2. Po velicini\n");
    printf("3. Po cijeni\n");
    printf("4. Po ID-u (rekurzivno)\n");
    printf("5. Po brendu (bsearch)\n");
    printf("Odabir: ");
    scanf("%d", &izbor);
    char brend[50];
    float velicina, cijena;
    int pronadeno = 0;
    int id;
    Tenisica* rezultat;
    switch (izbor) {
    case 1:
        printf("Unesite brend: ");
        scanf(" %49[^\n]", brend);
        for (int i = 0; i < n; i++) {
            if (strcmp(tenisice[i].brend, brend) == 0) {
                printf("ID: %d | Brend: %s | Model: %s | Velicina: %.1f | Cijena: %.2f | Kolicina: %d\n",
                    tenisice[i].id, tenisice[i].brend, tenisice[i].model,
                    tenisice[i].velicina, tenisice[i].cijena, tenisice[i].kolicina);
                pronadeno = 1;
            }
        }
        break;
    case 2:
        printf("Unesite velicinu: ");
        scanf("%f", &velicina);
        for (int i = 0; i < n; i++) {
            if (tenisice[i].velicina == velicina) {
                printf("ID: %d | Brend: %s | Model: %s | Velicina: %.1f | Cijena: %.2f | Kolicina: %d\n",
                    tenisice[i].id, tenisice[i].brend, tenisice[i].model,
                    tenisice[i].velicina, tenisice[i].cijena, tenisice[i].kolicina);
                pronadeno = 1;
            }
        }
        break;
    case 3:
        printf("Unesite cijenu: ");
        scanf("%f", &cijena);
        for (int i = 0; i < n; i++) {
            if (tenisice[i].cijena == cijena) {
                printf("ID: %d | Brend: %s | Model: %s | Velicina: %.1f | Cijena: %.2f | Kolicina: %d\n",
                    tenisice[i].id, tenisice[i].brend, tenisice[i].model,
                    tenisice[i].velicina, tenisice[i].cijena, tenisice[i].kolicina);
                pronadeno = 1;
            }
        }
        break;
    case 4:
        printf("Unesite ID: ");
        scanf("%d", &id);
        rezultat = rekurzivnaPretraga(tenisice, n, id, 0);
        if (rezultat != NULL) {
            printf("ID: %d | Brend: %s | Model: %s | Velicina: %.1f | Cijena: %.2f | Kolicina: %d\n",
                rezultat->id, rezultat->brend, rezultat->model,
                rezultat->velicina, rezultat->cijena, rezultat->kolicina);
            pronadeno = 1;
        }
        break;
    case 5:
        bsearchPretraga(tenisice, n);
        pronadeno = 1;
        break;
    default:
        printf("Nepostojeca opcija!\n");
        return;
    }
    if (!pronadeno) {
        printf("Nije pronadena nijedna tenisica!\n");
    }
}

static int usporediBrend(const void* a, const void* b) {
    const Tenisica* ta = (const Tenisica*)a;
    const Tenisica* tb = (const Tenisica*)b;
    return strcmp(ta->brend, tb->brend);
}

static int usporediCijenu(const void* a, const void* b) {
    const Tenisica* ta = (const Tenisica*)a;
    const Tenisica* tb = (const Tenisica*)b;
    if (ta->cijena < tb->cijena) return -1;
    if (ta->cijena > tb->cijena) return 1;
    return 0;
}

static int usporediVelicinu(const void* a, const void* b) {
    const Tenisica* ta = (const Tenisica*)a;
    const Tenisica* tb = (const Tenisica*)b;
    if (ta->velicina < tb->velicina) return -1;
    if (ta->velicina > tb->velicina) return 1;
    return 0;
}

static int usporediKolicinu(const void* a, const void* b) {
    const Tenisica* ta = (const Tenisica*)a;
    const Tenisica* tb = (const Tenisica*)b;
    return ta->kolicina - tb