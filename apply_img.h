// Calota Alexandra-Maria, grupa 314CA

#ifndef apply_img_h
#define apply_img_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_img.h"
#include "load_img.h"

// Functie prin care valorile negative devin 0,
// iar cele ce depasesc 255 vor fi limitate la
// aceasta valoare
double clamp(double x)
{
	if (x < 0)
		return 0;
	if (x > 255)
		return 255;
	return x;
}

// Functie care calculeaza valorile pixelului nou
double apply_pixel(double M1[3][3], double M2[3][3])
{
	double s = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			s += M1[i][j] * M2[i][j];
	s = clamp(s);
	return s;
}

// Functie ce salveaza matricea cu valorile efectului corespunzator
// pentru a o putea aplica in apply_pixel
void pregatire_kernel(double **M, int i, int j, double AUX[3][3])
{
	AUX[0][0] = M[i - 1][j - 1];
	AUX[0][1] = M[i - 1][j];
	AUX[0][2] = M[i - 1][j + 1];
	AUX[1][0] = M[i][j - 1];
	AUX[1][1] = M[i][j];
	AUX[1][2] = M[i][j + 1];
	AUX[2][0] = M[i + 1][j - 1];
	AUX[2][1] = M[i + 1][j];
	AUX[2][2] = M[i + 1][j + 1];
}

// Functie de citire a parametrului de efect pentru apply
int parametru_efect(void)
{
	char parametru[20];
	char c;
	scanf("%c", &c);
	if (c == ' ') {
		scanf("%s", parametru);
		if (strcmp(parametru, "EDGE") == 0)
			return 0;
		if (strcmp(parametru, "SHARPEN") == 0)
			return 1;
		if (strcmp(parametru, "BLUR") == 0)
			return 2;
		if (strcmp(parametru, "GAUSSIAN_BLUR") == 0)
			return 3;
		printf("APPLY parameter invalid\n");
		return 4;
	}
	printf("Invalid command\n");
	return 4;
}

// Functie de copiere a unei matrici AUX, intr-o alta
// matrice M
void copiere_matrice(double M[3][3], double AUX[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			M[i][j] = AUX[i][j];
}

// Functie de initializare a valorilor pixelilor din kernel
// pentru parametrul EDGE
void initializare_efect0(double M[3][3])
{
	double AUX[3][3] = {
		{-1.0, -1.0, -1.0},
		{-1.0, 8.0, -1.0},
		{-1.0, -1.0, -1.0}};
	copiere_matrice(M, AUX);
}

// Functie de initializare a valorilor pixelilor din kernel
// pentru parametrul SHARPEN
void initializare_efect1(double M[3][3])
{
	double AUX[3][3] = {
		{0.0, -1.0, 0.0},
		{-1.0, 5.0, -1.0},
		{0.0, -1.0, 0.0}};
	copiere_matrice(M, AUX);
}

// Functie de initializare a valorilor pixelilor din kernel
// pentru parametrul BLUR
void initializare_efect2(double M[3][3])
{
	double AUX[3][3] = {
		{1.0 / 9, 1.0 / 9, 1.0 / 9},
		{1.0 / 9, 1.0 / 9, 1.0 / 9},
		{1.0 / 9, 1.0 / 9, 1.0 / 9}};
	copiere_matrice(M, AUX);
}

// Functie de initializare a valorilor pixelilor din kernel
// pentru parametrul GAUSSIAN_BLUR
void initializare_efect3(double M[3][3])
{
	double AUX[3][3] = {
		{1.0 / 16, 1.0 / 8, 1.0 / 16},
		{1.0 / 8, 1.0 / 4, 1.0 / 8},
		{1.0 / 16, 1.0 / 8, 1.0 / 16}};
	copiere_matrice(M, AUX);
}

// Functie de aplicare a editului pentru fiecare pixel
void aplicare_edit(rgb_d img_editata, rgb_d M, int nr_linii, int nr_coloane,
				   int i, int j, double AUX[3][3], int tip_efect,
				   double EFECT[4][3][3])
{
	// omitem marginile exterioare ale imaginii
	if (i != 0 && i != nr_linii - 1 && j != 0 && j != nr_coloane - 1) {
		pregatire_kernel(M.rosu, i, j, AUX);
		img_editata.rosu[i][j] = apply_pixel(AUX, EFECT[tip_efect]);
		pregatire_kernel(M.verde, i, j, AUX);
		img_editata.verde[i][j] = apply_pixel(AUX, EFECT[tip_efect]);
		pregatire_kernel(M.albastru, i, j, AUX);
		img_editata.albastru[i][j] = apply_pixel(AUX, EFECT[tip_efect]);
	}
}

// Functie ce aplica peste selectie un nucleu de imagine
rgb_d apply(rgb_d M, int tip_imagine, int x1, int x2, int y1, int y2,
			int nr_linii, int nr_coloane, int tip_efect)
{
	rgb_d img_editata;
	// alocare memorie pentru matricele in care vom salva
	// imaginea editata
	img_editata.rosu = malloc(nr_linii * sizeof(double *));
	img_editata.verde = malloc(nr_linii * sizeof(double *));
	img_editata.albastru = malloc(nr_linii * sizeof(double *));
	for (int i = 0; i < nr_linii; i++) {
		img_editata.rosu[i] = malloc((nr_coloane) * sizeof(double));
		img_editata.verde[i] = malloc(nr_coloane * sizeof(double));
		img_editata.albastru[i] = malloc(nr_coloane * sizeof(double));
		if (!img_editata.rosu[i] || !img_editata.verde[i] ||
			!img_editata.albastru[i]) {
			fprintf(stderr, "Eroare la alocare.\n");
			while (--i >= 0) {
				free(img_editata.rosu[i]);
				free(img_editata.verde[i]);
				free(img_editata.albastru[i]);
			}
			free(img_editata.rosu);
			free(img_editata.verde);
			free(img_editata.albastru);
		}
	}
	double AUX[3][3];
	double EFECT[4][3][3]; // matrice 3D pentru stocarea nucleelor de imagine
	// initializarea fiecarui nucleu cu valorile corespunzatoare
	initializare_efect0(EFECT[0]);
	initializare_efect1(EFECT[1]);
	initializare_efect2(EFECT[2]);
	initializare_efect3(EFECT[3]);
	if (tip_imagine == 1) { // grayscale
		printf("Easy, Charlie Chaplin\n");
	} else {
		for (int i = y1; i <= y2; i++)
			for (int j = x1; j <= x2; j++) {
				// apicam editul pentru fiecare pixel al imaginii
				aplicare_edit(img_editata, M, nr_linii, nr_coloane, i, j,
							  AUX, tip_efect, EFECT);
				}
		// copiem fiecare pixel din imaginea editata inapoi in M
		for (int i = y1; i <= y2; i++)
			for (int j = x1; j <= x2; j++) {
				if (i != 0 && i != nr_linii - 1 && j != 0 &&
					j != nr_coloane - 1) {
					M.rosu[i][j] = img_editata.rosu[i][j];
					M.verde[i][j] = img_editata.verde[i][j];
					M.albastru[i][j] = img_editata.albastru[i][j];
				}
			}
		if (tip_efect == 0)
			printf("APPLY EDGE done\n");
		if (tip_efect == 1)
			printf("APPLY SHARPEN done\n");
		if (tip_efect == 2)
			printf("APPLY BLUR done\n");
		if (tip_efect == 3)
			printf("APPLY GAUSSIAN_BLUR done\n");
	}
	// eliberarea memoriei alocate pentru imaginea editata
	eliberare_d(img_editata.rosu, nr_linii);
	eliberare_d(img_editata.verde, nr_linii);
	eliberare_d(img_editata.albastru, nr_linii);
	return M;
}

#endif
