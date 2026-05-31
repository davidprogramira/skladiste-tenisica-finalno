#ifndef DATOTEKA_H
#define DATOTEKA_H

#include "tenisica.h"

void napraviBackup();
void obrisiDatoteku();
void spremiUDatoteku(Tenisica* tenisice, int n);
void ucitajIzDatoteke(Tenisica** tenisice, int* n, int* kapacitet);

#endif