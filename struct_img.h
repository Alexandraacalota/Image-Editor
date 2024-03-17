// Calota Alexandra-Maria, grupa 314CA

#ifndef struct_h
#define struct_h

typedef struct{
	// valorile pentru fiecare pixel de culoare
	unsigned char **rosu, **verde, **albastru;
} rgb;

typedef struct{
	// valorile pentru fiecare pixel de culoare de tip double
	double **rosu, **verde, **albastru;
} rgb_d;

typedef struct{
	int nr_coloane, nr_linii; // latimea si inaltimea imaginii
	int x1, y1, x2, y2; // variabilele de selectie
	int tip_imagine; // (1 alb negru, 2 gri, 3 color)
	int max;		 // valoarea maxima a intensitatii unei culori
	// imaginea caracterizata pentru fiecare element al ei cu 3 culori
} info_imagine;

#endif
