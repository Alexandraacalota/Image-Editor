// Calota Alexandra-Maria, grupa 314CA

#ifndef save_img_h
#define save_img_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "struct_img.h"

// Functie de salvare a unei imagini in fisier binar
void salv_binar(info_imagine info, rgb_d M, FILE *out)
{
	for (int i = 0; i < info.nr_linii; i++) {
		for (int j = 0; j < info.nr_coloane; j++) {
			if (info.tip_imagine == 0 || info.tip_imagine == 1) {
				unsigned char aux = (int)round(M.rosu[i][j]);
				fflush(out);
				fwrite(&aux, sizeof(char), 1, out);
			} else {
				unsigned char aux = (int)round(M.rosu[i][j]);
				fwrite(&aux, sizeof(char), 1, out);
				aux = (int)round(M.verde[i][j]);
				fwrite(&aux, sizeof(char), 1, out);
				aux = (int)round(M.albastru[i][j]);
				fwrite(&aux, sizeof(char), 1, out);
				fflush(out);
			}
		}
	}
}

// Functie de salvare a unei imagini in fisier ascii
void salv_ascii(info_imagine info, rgb_d M, FILE *out)
{
	for (int i = 0; i < info.nr_linii; i++) {
		for (int j = 0; j < info.nr_coloane; j++) {
			if (info.tip_imagine == 0 || info.tip_imagine == 1) {
				int aux = (int)M.rosu[i][j];
				fflush(out);
				fprintf(out, "%d ", aux);
			} else {
				int aux = (int)round(M.rosu[i][j]);
				fprintf(out, "%d ", aux);
				aux = (int)round(M.verde[i][j]);
				fprintf(out, "%d ", aux);
				aux = (int)round(M.albastru[i][j]);
				fprintf(out, "%d ", aux);
				fflush(out);
			}
		}
		fprintf(out, "\n");
	}
}

// Functie de salvare a imaginii intr-un fisier
void save(rgb_d M, info_imagine info, char nume_save[50],
		  int tip_fisier_save)
{
	FILE *out = fopen(nume_save, "wt");
	fprintf(out, "P");
	// daca fisierul trebuie sa fie binar
	if (tip_fisier_save == 0) {
		switch (info.tip_imagine) {
		case 0: { // alb-negru
			fprintf(out, "4");
			break;
		}
		case 1: { // gri
			fprintf(out, "5");
			break;
		}
		case 2: { // color
			fprintf(out, "6");
			break;
		}
		}
		// daca fisierul trebuie sa fie ascii
	} else {
		switch (info.tip_imagine) {
		case 0: {
			fprintf(out, "1");
			break;
		}
		case 1: {
			fprintf(out, "2");
			break;
		}
		case 2: {
			fprintf(out, "3");
			break;
		}
		}
	}
	fprintf(out, "\n%d %d\n", info.nr_coloane, info.nr_linii);
	if (info.tip_imagine != 0)
		fprintf(out, "%d\n", info.max);
	if (tip_fisier_save == 0) {
		fclose(out);
		out = fopen(nume_save, "ab");
		// salvarea imaginii in fisier binar
		salv_binar(info, M, out);
		fclose(out);
	} else {
		// salvarea imaginii in fisier ascii
		salv_ascii(info, M, out);
		fclose(out);
	}
}

#endif
