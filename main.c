// Calota Alexandra-Maria, grupa 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "struct_img.h"
#include "load_img.h"
#include "select_img.h"
#include "rotate_img.h"
#include "crop_img.h"
#include "save_img.h"
#include "exit_img.h"
#include "apply_img.h"

// Switch case-ul este folosit pentru apelarea functiilor programului
// prin intermediul tipului comenzii returnat de functia
// citire_comanda
int main(void)
{
	info_imagine info; // contine detaliile imaginii
	rgb_d M;		   // contine imaginea cu pixeli de tip double
	int comanda;
	int ok = 0, ok_exit = 0; // ok = 0 daca nu exista imagine incarcata
	do {
		comanda = citire_comanda();
		switch (comanda) {
		case 0: {
			rgb AUX;
			int ok_incarcare = 1;
			char nume_fisier[100];
			scanf("%s", nume_fisier);
			if (ok == 1) {
				// eliberarea memoriei alocate pentru imaginea deja incarcata
				if (info.tip_imagine == 0 || info.tip_imagine == 1) {
					eliberare_d(M.rosu, info.nr_linii);
				} else {
					eliberare_d(M.rosu, info.nr_linii);
					eliberare_d(M.verde, info.nr_linii);
					eliberare_d(M.albastru, info.nr_linii);
				}
			}
			AUX = incarcare(&info.nr_linii, &info.nr_coloane, &info.x1,
							&info.x2, &info.y1, &info.y2, &info.max,
							nume_fisier, &info.tip_imagine, &ok,
							&ok_incarcare);
			if (ok_incarcare == 1) {
				if (info.tip_imagine == 0 || info.tip_imagine == 1) {
					M.rosu = alocare_d(info.nr_linii, info.nr_coloane);
				} else {
					M.rosu = alocare_d(info.nr_linii, info.nr_coloane);
					M.verde = alocare_d(info.nr_linii, info.nr_coloane);
					M.albastru = alocare_d(info.nr_linii, info.nr_coloane);
				}
				M = convertire(M, AUX, info.nr_linii, info.nr_coloane,
							   info.tip_imagine);
				if (info.tip_imagine == 0 || info.tip_imagine == 1) {
					eliberare(AUX.rosu, info.nr_linii);
				} else {
					eliberare(AUX.rosu, info.nr_linii);
					eliberare(AUX.verde, info.nr_linii);
					eliberare(AUX.albastru, info.nr_linii);
				}
			}
			break;
		}
		case 1: {
			if (ok == 0) {
				printf("No image loaded\n");
				citire_junk();
				break;
			}
			select_img(info.nr_linii, info.nr_coloane, &info.x1, &info.x2,
					   &info.y1, &info.y2);
			break;
		}
		case 2: {
			M = rotire(M, &info.nr_linii, &info.nr_coloane, &info.x1,
					   &info.y1, &info.x2, &info.y2, info.tip_imagine, ok);
			break;
		}
		case 3: {
			if (ok == 0) {
				printf("No image loaded\n");
				citire_junk();
				break;
			}
			M = crop(M, &info.nr_linii, &info.nr_coloane, &info.x1, &info.x2,
					 &info.y1, &info.y2, info.tip_imagine);
			break;
		}
		case 4: {
			if (ok == 0) {
				printf("No image loaded\n");
				citire_junk();
				break;
			}
			int tip_efect = parametru_efect();
			if (tip_efect <= 3) {
				M = apply(M, info.tip_imagine, info.x1, info.x2, info.y1,
						  info.y2, info.nr_linii, info.nr_coloane, tip_efect);
			}
			break;
		}
		case 5: {
			char nume_save[50];
			int tip_fisier_save;
			if (ok == 0) {
				printf("No image loaded\n");
				citire_junk();
			} else {
				citire(nume_save, &tip_fisier_save);
				save(M, info, nume_save, tip_fisier_save);
				printf("Saved %s\n", nume_save);
			}
			break;
		}
		case 6: {
			exit_img(M, info.nr_linii, info.tip_imagine, ok);
			ok_exit = 1;
			break;
		}
		case 7: {
			printf("Invalid command\n");
			break;
		}
		}
	} while (ok_exit == 0);
	return 0;
}
