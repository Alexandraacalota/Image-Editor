// Calota Alexandra-Maria, grupa 314CA

#ifndef select_img_h
#define select_img_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_img.h"

// Functie citire variabile
void citire_selector(char coord[10], int *ok1, int *okendline)
{
	char caracter;
	scanf("%c", &caracter);
	if (caracter == ' ') {
		scanf("%s", coord);
	} else {
		*ok1 = 0; // nu mai citeste coordonatele urmatoare
		if (caracter == '\n')
			*okendline = 0;
	}
}

// Functie in care citesc argumentele unei comenzi
// dupa ce unul dintre argumentele anterioare a fost invalid
void citire_gunoi(void)
{
	char caracter;
	do {
		fscanf(stdin, "%c", &caracter);
	} while (caracter != '\n');
}

// Functie de verificare a cifrelor din variabilele
// de selectie
int verif_cifre(const char *s)
{
	while (*s) {
		if (isdigit(*s++) == 0)
			return 0;
	}
	return 1;
}

// Functie de selectare a imaginii intre coordonatele
// x1, y1, x2, y2
void select_img(int nr_linii, int nr_coloane, int *x1, int *x2,
				int *y1, int *y2)
{
	int ok1 = 1; // verifica daca pot citi cele 4 coordonate
	int okendline = 1;
	char coord1[20], coord2[20], coord3[20], coord4[20];
	scanf("%s", coord1);
	if (coord1[0] == '-') {
		printf("Invalid set of coordinates\n");
		citire_gunoi();
		return;
	}
	if (strcmp(coord1, "ALL") != 0) {
		// a1 repr. x1 citit, b1 repr. y1 citit
		citire_selector(coord2, &ok1, &okendline);
		if (ok1 == 1)
			citire_selector(coord3, &ok1, &okendline);
		if (ok1 == 1)
			citire_selector(coord4, &ok1, &okendline);
		// daca s au citit toate cele 4 coordonate
		if (ok1 == 1) {
			// verificam daca acestea au fost doar cifre
			if ((verif_cifre(coord1) == 0) || verif_cifre(coord2) == 0 ||
				(verif_cifre(coord3) == 0) || (verif_cifre(coord4) == 0)) {
				printf("Invalid command\n");
				return;
			}
			int a1 = atoi(coord1); // convertirea coordonatelor in int
			int b1 = atoi(coord2);
			int a2 = atoi(coord3);
			int b2 = atoi(coord4);
			if (a2 - a1 == 0 || b2 - b1 == 0) { // nu exista imagine
				printf("Invalid set of coordinates\n");
				return;
			}
			if (a1 > a2) {
				a1 = a1 + a2; // interschimbare coordonate selectie
				a2 = a1 - a2;
				a1 = a1 - a2;
			}
			if (b1 > b2) {
				b1 = b1 + b2; // interschimbare coordonate selectie
				b2 = b1 - b2;
				b1 = b1 - b2;
			}
			a2 = a2 - 1; // deoarece intervalul este [a1, a2)
			b2 = b2 - 1; // deoarece intervalul este [b1, b2)
			// nu exista imagine pentru coordonatele selectate
			if ((0 > a1) || a1 > nr_coloane || (0 > b1) ||
				b1 > nr_linii || (0 > a2) || (a2 + 1 > nr_coloane) ||
				(0 > b2) || (b2 + 1 > nr_linii)) {
				printf("Invalid set of coordinates\n");
				return;
			}
			*x1 = a1; // salvarea selectorului x1 dupa verificari
			*x2 = a2;
			*y1 = b1;
			*y2 = b2;
			printf("Selected %d %d %d %d\n", *x1, *y1, *x2 + 1, *y2 + 1);
		} else if (ok1 == 0) {
			printf("Invalid command\n");
			if (okendline == 1)
				citire_gunoi();
			return;
		}
	} else if (strcmp(coord1, "ALL") == 0) { // SELECT ALL
		*x1 = 0;
		*x2 = nr_coloane - 1;
		*y1 = 0;
		*y2 = nr_linii - 1;
		printf("Selected ALL\n");
	}
}

#endif
