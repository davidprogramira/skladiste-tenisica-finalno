#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "datoteka.h"

void spremiUDatoteku(Tenisica* tenisice, int n) {
    FILE* fp = fopen("skladiste.bin", "wb");
    if (fp == NULL) {
        perror("Greska pri otvaranju datoteke");
        return;
    }
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(tenisice, sizeof(Tenisica), n, fp);

    fseek(fp, 0, SEEK_END);
    long velicina = ftell(fp);
    printf("Datoteka spremljena, velicina: %ld bajtova\n", velicina);

    fclose(fp);
    printf("Podaci uspjesno spremljeni!\n");
}

void ucitajIzDatoteke(Tenisica** tenisice, int* n, int* kapacitet) {
    FILE* fp = fopen("skladiste.bin", "rb");
    if (fp == NULL) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    rewind(fp);

    fread(n, sizeof(int), 1, fp);
    if (*n > *kapacitet) {
        *kapacitet = *n;
        Tenisica* temp = (Tenisica*)realloc(*tenisice, *kapacitet * sizeof(Tenisica));
        if (temp == NULL) {
            perror("Greska pri alokaciji memorije");
            fclose(fp);
            return;
        }
        *tenisice = temp;
    }

    fseek(fp, sizeof(int), SEEK_SET);
    fread(*tenisice, sizeof(Tenisica), *n, fp);

    fclose(fp);
    printf("Podaci uspjesno ucitani!\n");
}

void napraviBackup() {
    if (rename("skladiste.bin", "skladiste_backup.bin") == 0) {
        printf("Backup napravljen: skladiste_backup.bin\n");
    }
    else {
        perror("Greska pri pravljenju backupa");
    }
}

void obrisiDatoteku() {
    if (remove("skladiste_backup.bin") == 0) {
        printf("Backup datoteka obrisana!\n");
    }
    else {
        perror("Greska pri brisanju datoteke");
    }
}