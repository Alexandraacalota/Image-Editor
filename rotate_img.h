// Calota Alexandra-Maria, grupa 314CA

#ifndef rotate_img_h
#define rotate_img_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_img.h"

// Functie de rotire a unei matrice la 90 grade
rgb_d rotire_90_grade(rgb_d M, int nr_linii, int nr_coloane,
					  int tip_imagine)
{
	// Alocam dinamic memorie pentru matricea AUX pe care o
	// vom folosi pentru a stoca elementele matricei M
	rgb_d AUX;
	if (tip_imagine == 0 || tip_imagine == 1) { // alb-negru sau grayscale
		AUX.rosu = malloc(nr_coloane * sizeof(double *));
	} else { // imagine color
		AUX.rosu = malloc(nr_coloane * sizeof(double *));
		AUX.verde = malloc(nr_coloane * sizeof(double *));
		AUX.albastru = malloc(nr_coloane * sizeof(double *));
	}
	for (int i = 0; i < nr_coloane; i++) {
		if (tip_imagine == 0 || tip_imagine == 1) { // alb-negru sau grayscale
			AUX.rosu[i] = malloc(nr_linii * sizeof(double));
		} else { // imagine color
			AUX.rosu[i] = malloc(nr_linii * sizeof(double));
			AUX.verde[i] = malloc(nr_linii * sizeof(double));
			AUX.albastru[i] = malloc(nr_linii * sizeof(double));
		}
	}
	// Salvam in AUX elementele matricei M rotite
	for (int i = 0; i < nr_linii; i++)
		for (int j = 0; j < nr_coloane; j++) {
			if (tip_imagine == 0 || tip_imagine == 1) {
				AUX.rosu[j][nr_linii - i - 1] = M.rosu[i][j];
			} else {
				AUX.rosu[j][nr_linii - i - 1] = M.rosu[i][j];
				AUX.verde[j][nr_linii - i - 1] = M.verde[i][j];
				AUX.albastru[j][nr_linii - i - 1] = M.albastru[i][j];
			}
		}
	// Eliberam memoria matricei M
	for (int i = 0; i < nr_linii; i++) {
		if (tip_imagine == 0 || tip_imagine == 1) {
			free(M.rosu[i]);
		} else {
			free(M.rosu[i]);
			free(M.verde[i]);
			free(M.albastru[i]);
		}
	}
	if (tip_imagine == 0 || tip_imagine == 1) {
		free(M.rosu);
	} else {
		free(M.rosu);
		free(M.verde);
		free(M.albastru);
	}
	return AUX;
}

// Functie de rotire a unei selectii
// folosind functia de rotire a imaginii complete
// Am cosiderat selectia o imagine de sine statatoare,
// am rotit-o si am inlocuit selectia originala cu cea rotita
rgb_d rotire_90_grade_sel(rgb_d M, int *x1, int *x2, int *y1,
						  int *y2, int tip_imagine)
{
	rgb_d AUX;
	if (tip_imagine == 0 || tip_imagine == 1) { // alb-negru sau grayscale
		AUX.rosu = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
	} else { // color
		AUX.rosu = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
		AUX.verde = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
		AUX.albastru = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
	}
	for (int i = 0; i <= (*y2) - (*y1); i++) {
		if (tip_imagine == 0 || tip_imagine == 1) {
			AUX.rosu[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
		} else {
			AUX.rosu[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
			AUX.verde[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
			AUX.albastru[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
		}
	}
	for (int i = *y1; i <= *y2; i++)
		for (int j = *x1; j <= *x2; j++) {
			if (tip_imagine == 0 || tip_imagine == 1) {
				AUX.rosu[i - *y1][j - *x1] = M.rosu[i][j];
			} else {
				AUX.rosu[i - *y1][j - *x1] = M.rosu[i][j];
				AUX.verde[i - *y1][j - *x1] = M.verde[i][j];
				AUX.albastru[i - *y1][j - *x1] = M.albastru[i][j];
			}
		}
	AUX = rotire_90_grade(AUX, *y2 - *y1 + 1, *x2 - *x1 + 1, tip_imagine);
	for (int i = *y1; i <= *y2; i++)
		for (int j = *x1; j <= *x2; j++) {
			if (tip_imagine == 0 || tip_imagine == 1) {
				M.rosu[i][j] = AUX.rosu[i - *y1][j - *x1];
			} else {
				M.rosu[i][j] = AUX.rosu[i - *y1][j - *x1];
				M.verde[i][j] = AUX.verde[i - *y1][j - *x1];
				M.albastru[i][j] = AUX.albastru[i - *y1][j - *x1];
			}
		}
	for (int i = 0; i <= *y2 - *y1; i++) {
		if (tip_imagine == 0 || tip_imagine == 1) {
			free(AUX.rosu[i]);
		} else {
			free(AUX.rosu[i]);
			free(AUX.verde[i]);
			free(AUX.albastru[i]);
		}
	}
	if (tip_imagine == 0 || tip_imagine == 1) {
		free(AUX.rosu);
	} else {
		free(AUX.rosu);
		free(AUX.verde);
		free(AUX.albastru);
	}
	return M;
}

// Functie de rotire a unei matrice
rgb_d rotire(rgb_d M, int *nr_linii, int *nr_coloane, int *x1,
			 int *y1, int *x2, int *y2, int tip_imagine, int ok)
{
	int unghi, unghi_poz;
	// citim unghiul de rotire
	fscanf(stdin, "%d", &unghi);
	// daca nu avem o imagine incarcata
	if (ok == 0) {
		fprintf(stdout, "No image loaded\n");
	} else { // daca avem o imagine incarcata
		// daca este un unghi negativ, il transformam
		// in unghiul pozitiv corespunzator rotatiei
		if (unghi < 0 && (unghi > -360))
			unghi_poz = 360 + unghi;
		else
			unghi_poz = unghi;
		// Daca intreaga imagine este selectata
		if ((*x1 == 0) && (*x2 == *nr_coloane - 1) &&
			(*y1 == 0) && (*y2 == *nr_linii - 1)) {
			if (unghi_poz > 0 && (unghi_poz < 360 && unghi_poz % 90 == 0)) {
				for (int i = 0; i < unghi_poz / 90; i++) {
					M = rotire_90_grade(M, *nr_linii, *nr_coloane,
										tip_imagine);
					*nr_linii = (*nr_linii) + (*nr_coloane);
					*nr_coloane = (*nr_linii) - (*nr_coloane);
					*nr_linii = (*nr_linii) - (*nr_coloane);
					*x2 = *nr_coloane - 1;
					*y2 = *nr_linii - 1;
				}
				fprintf(stdout, "Rotated %d\n", unghi);
			} else if (unghi_poz == 360 || unghi_poz == -360 ||
					   unghi_poz == 0) {
				fprintf(stdout, "Rotated %d\n", unghi);
			} else {
				fprintf(stdout, "Unsupported rotation angle\n");
			}
			// Pentru o selectie patratica a imaginii
		} else if ((*x2 - *x1) == (*y2 - *y1)) {
			if (unghi_poz > 0 && (unghi_poz < 360 && unghi_poz % 90 == 0)) {
				for (int i = 0; i < unghi_poz / 90; i++)
					M = rotire_90_grade_sel(M, x1, x2, y1, y2, tip_imagine);
				fprintf(stdout, "Rotated %d\n", unghi);
			} else if (unghi_poz == 360 || unghi_poz == -360 ||
					   unghi_poz == 0) {
				fprintf(stdout, "Rotated %d\n", unghi);
			} else {
				fprintf(stdout, "Unsupported rotation angle\n");
			}
		} else {
			printf("The selection must be square\n");
		}
	}
	return M;
}

#endif
