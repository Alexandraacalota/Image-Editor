// Calota Alexandra-Maria, grupa 314CA

#ifndef load_img_h
#define load_img_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_img.h"

// Functie de alocare de memorie pentru o matrice de tip uchar**
unsigned char **alocare(int nr_linii, int nr_coloane)
{
	unsigned char **M;
	// alocare memorie pentru matrice
	M = (unsigned char **)malloc(nr_linii * sizeof(unsigned char *));
	if (!M) {
		fprintf(stderr, "Eroare la alocare.\n");
		return NULL;
	}
	// alocare memorie pentru fiecare linie din matrice
	for (int i = 0; i < nr_linii; i++) {
		M[i] = malloc(nr_coloane * sizeof(unsigned char));
		if (!M[i]) {
			fprintf(stderr, "Eroare la alocare.\n");
			while (--i >= 0)
				free(M[i]);
			free(M);
			return NULL;
		}
	}
	return M;
}

// Functie de eliberare memorie alocata pentru o matrice de tip uchar**
void eliberare(unsigned char **M, int nr_linii)
{
	// eliberarea memoriei alocate fiecarei linii din matrice
	for (int i = 0; i < nr_linii; i++)
		free(M[i]);
	// eliberarea memoriei alocate pentru matricea in sine
	free(M);
}

// Functie care verifica existenta comentariilor (#)
void comentarii(FILE *fisier)
{
	char caracter;
	int ok; // daca gaseste un comentariu, devine 1
	int ok_comentariu = 0; // nu am niciun comentariu
	do {
		ok = 0;
		fscanf(fisier, "%c", &caracter);
		if (caracter == '#') {
			ok = 1;
			ok_comentariu = 1;
			while (caracter != '\n')
				fscanf(fisier, "%c", &caracter);
		}
	} while (ok == 1);
	if (ok_comentariu == 0)
		fseek(fisier, -1, SEEK_CUR);
}

// Functie care verifica tipul fisierului in functie de
// "magic word"-ul imaginii
int afla_tip_fisier(char tip[5])
{
	// returneaza 1 daca e de tip P1, P2 sau P3 (ASCII)
	if (strcmp(tip, "P1") == 0 || strcmp(tip, "P2") == 0 ||
		strcmp(tip, "P3") == 0)
		return 1;
	// returneaza 2 daca e de tip P4, P5 sau P6 (binar)
	return 2;
}

// Functie care verifica tipul imaginii in functie de
// "magic word"-ul imaginii
int afla_tip_imagine(char tip[5])
{
	int tip_imagine;
	if (strcmp(tip, "P1") == 0 || strcmp(tip, "P4") == 0)
		tip_imagine = 0; // imagine alb-negru
	if (strcmp(tip, "P2") == 0 || strcmp(tip, "P5") == 0)
		tip_imagine = 1; // imagine in tonuri de gri
	if (strcmp(tip, "P3") == 0 || strcmp(tip, "P6") == 0)
		tip_imagine = 2; // imagine color
	return tip_imagine;
}

// Functie de citire a unei imagini dintr-un fisier ascii
rgb citire_matrice_ASCII(int nr_coloane, int nr_linii,
						 int tip_imagine, FILE *fisier)
{
	rgb imagine;
	if (tip_imagine == 0 || tip_imagine == 1) { // alb-negru sau grayscale
		// alocare memorie pentru matricea alb-negru / grayscale
		imagine.rosu = alocare(nr_linii, nr_coloane + 1);
		for (int i = 0; i < nr_linii; i++)
			for (int j = 0; j < nr_coloane; j++)
				fscanf(fisier, "%hhd", &imagine.rosu[i][j]);
	} else { // color
		// alocare memorie pentru fiecare dintre cele 3 matrici
		imagine.rosu = alocare(nr_linii, nr_coloane + 1);
		imagine.verde = alocare(nr_linii, nr_coloane + 1);
		imagine.albastru = alocare(nr_linii, nr_coloane + 1);
		// citirea elementelor din fisierul ascii
		for (int i = 0; i < nr_linii; i++)
			for (int j = 0; j < nr_coloane; j++)
			{
				fscanf(fisier, "%hhd", &imagine.rosu[i][j]);
				fscanf(fisier, "%hhd", &imagine.verde[i][j]);
				fscanf(fisier, "%hhd", &imagine.albastru[i][j]);
			}
	}
	return imagine; // returneaza imaginea citita din fisierul ascii
}

// Functie de citire a unei imagini dintr-un fisier binar
rgb citire_matrice_binar(int nr_coloane,
						 int nr_linii, int tip_imagine, FILE *fisier)
{
	rgb imagine;
	if (tip_imagine == 0 || tip_imagine == 1) // alb-negru sau grayscale
	{
		// alocare memorie pentru matricea alb-negru / grayscale
		imagine.rosu = alocare(nr_linii, nr_coloane + 1);
		for (int i = 0; i < nr_linii; i++)
			for (int j = 0; j < nr_coloane; j++)
				fread(&imagine.rosu[i][j], sizeof(unsigned char), 1, fisier);
	}
	else { // color
		// alocare memorie pentru fiecare dintre cele 3 matrici
		imagine.rosu = alocare(nr_linii, nr_coloane + 1);
		imagine.verde = alocare(nr_linii, nr_coloane + 1);
		imagine.albastru = alocare(nr_linii, nr_coloane + 1);
		// citirea elementelor din fisierul binar
		for (int i = 0; i < nr_linii; i++)
			for (int j = 0; j < nr_coloane; j++) {
				fread(&imagine.rosu[i][j], sizeof(unsigned char), 1, fisier);
				fread(&imagine.verde[i][j], sizeof(unsigned char), 1, fisier);
				fread(&imagine.albastru[i][j], sizeof(unsigned char), 1, fisier);
			}
	}
	return imagine; // returneaza imaginea citita din fisierul binar
}

// Functie de incarcare a unei imagini din fisier
rgb incarcare(int *nr_linii, int *nr_coloane, int *x1, int *x2, int *y1,
			  int *y2, int *max, char *nume_fisier, int *tip_imagine, int *ok,
			  int *ok_incarcare)
{
	char tip[5];
	long int pozitie;
	int tip_fisier;
	FILE *fisier;
	rgb M;
	if ((fisier = fopen(nume_fisier, "r"))) {
		comentarii(fisier);
		fscanf(fisier, "%s", tip);
		comentarii(fisier);
		// citire nr_coloane (latime) si nr_linii (inaltime)
		// si, daca este cazul, nr maxim al intensitatii culorii
		if ((strcmp(tip, "P1") == 0) || (strcmp(tip, "P4") == 0))
			fscanf(fisier, "%d%d", nr_coloane, nr_linii);
		if ((strcmp(tip, "P2") == 0) || (strcmp(tip, "P3") == 0) ||
			(strcmp(tip, "P5") == 0) || (strcmp(tip, "P6") == 0)) {
			fscanf(fisier, "%d%d", nr_coloane, nr_linii);
			comentarii(fisier);
			fscanf(fisier, "%d", max);
		}
		comentarii(fisier);
		// pozitia unde incepe matricea
		pozitie = ftell(fisier);
		tip_fisier = afla_tip_fisier(tip);
		*tip_imagine = afla_tip_imagine(tip);
		if (tip_fisier == 1) {
			// citire imagine in ASCII
			M = citire_matrice_ASCII(*nr_coloane, *nr_linii, *tip_imagine,
									 fisier);
			// selecteaza imaginea
			*x1 = 0;
			*y1 = 0;
			*x2 = *nr_coloane - 1;
			*y2 = *nr_linii - 1;
			fprintf(stdout, "Loaded %s\n", nume_fisier);
			*ok = 1;
			fclose(fisier);
		} else if (tip_fisier == 2) {
			//inchide fisierul
			fclose(fisier);
			// deschide fisierul in mod binar
			fisier = fopen(nume_fisier, "rb");
			if (!fisier) {
				fprintf(stdout, "Failed to load %s\n", nume_fisier);
			}
			fseek(fisier, pozitie + 1, SEEK_SET);
			M = citire_matrice_binar(*nr_coloane, *nr_linii, *tip_imagine, fisier);
			// selecteaza imaginea
			*x1 = 0;
			*y1 = 0;
			*x2 = *nr_coloane - 1;
			*y2 = *nr_linii - 1;
			fprintf(stdout, "Loaded %s\n", nume_fisier);
			*ok = 1;
			fclose(fisier);
		}
	}
	else {
		printf("Failed to load %s\n", nume_fisier);
		*ok_incarcare = 0;
		*ok = 0;
	}
	return M;
}

// Functie de alocare de memorie pentru o matrice de tip double**
double **alocare_d(int nr_linii, int nr_coloane)
{
	double **AUX = (double **)malloc(nr_linii * sizeof(double *));
	for (int i = 0; i < nr_linii; i++) {
		AUX[i] = malloc(nr_coloane * sizeof(double));
		if (!AUX[i]) {
			fprintf(stderr, "Eroare la alocare.\n");
			while (--i >= 0)
				free(AUX[i]);
			free(AUX);
		}
	}
	return AUX;
}

// Functie de convertire a elementelor matricei din
// char in double
rgb_d convertire(rgb_d AUX, rgb M, int nr_linii, int nr_coloane,
int tip_imagine)
{
	for (int i = 0; i < nr_linii; i++)
		for (int j = 0; j < nr_coloane; j++) {
			if (tip_imagine == 0 || tip_imagine == 1) {
				AUX.rosu[i][j] = M.rosu[i][j];
			} else {
				AUX.rosu[i][j] = M.rosu[i][j];
				AUX.verde[i][j] = M.verde[i][j];
				AUX.albastru[i][j] = M.albastru[i][j];
			}
		}
	return AUX;
}

#endif
