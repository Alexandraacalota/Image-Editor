// Calota Alexandra-Maria, grupa 314CA

#ifndef crop_img_h
#define crop_img_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_img.h"

// Functie de eliberare a memoriei alocate pentru o matrice de tip double
void eliberare_d(double **M, int nr_linii)
{
	for (int i = 0; i < nr_linii; i++)
		free(M[i]); // eliberarea fiecarei linii din matrice
	free(M); // eliberarea matricei
}

// Functie de reducere a imaginii la cea cuprinsa in cadrul
// selectiei curente
// ((*y2) - (*y1)+1) reprezinta nr_linii ai selectiei
// ((*x2) - (*x1)+1) reprezinta nr_coloane ai selectiei
rgb_d crop(rgb_d M, int *nr_linii, int *nr_coloane, int *x1,
		   int *x2, int *y1, int *y2, int tip_imagine)
{
	// in AUX salvam pixelii imaginii aflati intre variabilele
	// de selectie x1, y1, x2, y2
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
	// copiem elementele din imagine in AUX
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
	// eliberaram memoria alocata imaginii initiale
	if (tip_imagine == 0 || tip_imagine == 1) { // alb-negru sau grayscale
		eliberare_d(M.rosu, *nr_linii);
	} else { // color
		eliberare_d(M.rosu, *nr_linii);
		eliberare_d(M.verde, *nr_linii);
		eliberare_d(M.albastru, *nr_linii);
	}
	// alocam din nou memorie pentru matricea M
	if (tip_imagine == 0 || tip_imagine == 1) {
		M.rosu = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
	} else {
		M.rosu = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
		M.verde = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
		M.albastru = malloc(((*y2) - (*y1) + 1) * sizeof(double *));
	}
	for (int i = 0; i <= *y2 - *y1; i++) {
		if (tip_imagine == 0 || tip_imagine == 1) {
			M.rosu[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
		} else {
			M.rosu[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
			M.verde[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
			M.albastru[i] = malloc(((*x2) - (*x1) + 1) * sizeof(double));
		}
	}
	// salvam in M toate elementele din AUX
	for (int i = 0; i <= *y2 - *y1; i++)
		for (int j = 0; j <= *x2 - *x1; j++) {
			if (tip_imagine == 0 || tip_imagine == 1) {
				M.rosu[i][j] = AUX.rosu[i][j];
			} else {
				M.rosu[i][j] = AUX.rosu[i][j];
				M.verde[i][j] = AUX.verde[i][j];
				M.albastru[i][j] = AUX.albastru[i][j];
			}
		}
	// eliberam memoria alocata pentru AUX
	if (tip_imagine == 0 || tip_imagine == 1) { // alb-negru sau grayscale
		for (int i = 0; i <= *y2 - *y1; i++)
			free(AUX.rosu[i]);
		free(AUX.rosu);
	} else { // color
		for (int i = 0; i <= *y2 - *y1; i++) {
			free(AUX.rosu[i]);
			free(AUX.verde[i]);
			free(AUX.albastru[i]);
		}
		free(AUX.rosu);
		free(AUX.verde);
		free(AUX.albastru);
	}
	// salvam in structura noile valori ale detaliilor despre imagine
	(*y2) -= (*y1);
	*y1 = 0;
	(*x2) -= (*x1);
	*x1 = 0;
	*nr_linii = (*y2) + 1;
	*nr_coloane = (*x2) + 1;
	printf("Image cropped\n");
	return M;
}

#endif
