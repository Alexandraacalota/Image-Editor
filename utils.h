// Calota Alexandra-Maria, grupa 314CA

#ifndef utils_h
#define utils_h

// Functie de citire a continuarii comenzilor ce afiseaza eroare
void citire_junk(void)
{
	char caracter;
	do {
		fscanf(stdin, "%c", &caracter);
	} while (caracter != '\n');
}

// Functie de citire a comenzii introduse si
// de stabilire a unei valori pentru variabilele
// din switch case-ul din functia main
int citire_comanda(void)
{
	char comanda[150];
	scanf("%s", comanda);
	if (strcmp(comanda, "LOAD") == 0)
		return 0;
	if (strcmp(comanda, "SELECT") == 0)
		return 1;
	if (strcmp(comanda, "ROTATE") == 0)
		return 2;
	if (strcmp(comanda, "CROP") == 0)
		return 3;
	if (strcmp(comanda, "APPLY") == 0)
		return 4;
	if (strcmp(comanda, "SAVE") == 0)
		return 5;
	if (strcmp(comanda, "EXIT") == 0)
		return 6;
	citire_junk();
	return 7;
}

// Functie de citire a numelui si a tipului de fisier
// in care se salveaza imaginea
void citire(char nume_save[50], int *tip_fisier)
{
	scanf("%s", nume_save);
	char c;
	scanf("%c", &c);
	// daca urmatorul caracter citit este spatiu,
	// fisierul nume_save este de tip ascii
	if (c == ' ') {
		scanf("%c", &c);
		if (c == 'a') {
			char aux[150];
			scanf("%s", aux);
			*tip_fisier = 1;
		} else {
			*tip_fisier = 0;
		}
	} else {
		// fisierul nume_save este binar
		*tip_fisier = 0;
	}
}

#endif
