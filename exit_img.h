// Calota Alexandra-Maria, grupa 314CA

#ifndef exit_img_h
#define exit_img_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_img.h"

// Functie ce inchide programul, eliberand memoria alocata
// imaginii incarcate (daca este cazul)
void exit_img(rgb_d M, int nr_linii, int tip_imagine, int ok)
{
	if (ok == 0) {
		printf("No image loaded\n");
	} else {
		if (tip_imagine == 0 || tip_imagine == 1) { // grayscale
			for (int i = 0; i < nr_linii; i++)
				free(M.rosu[i]);
			free(M.rosu);
		} else { // color
			for (int i = 0; i < nr_linii; i++) {
				free(M.rosu[i]);
				free(M.verde[i]);
				free(M.albastru[i]);
			}
			free(M.rosu);
			free(M.verde);
			free(M.albastru);
		}
	}
}

#endif
