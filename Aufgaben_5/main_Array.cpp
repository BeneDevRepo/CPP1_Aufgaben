/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/


#include <stdio.h>
#include <iostream>

void flushInput() {
	for(;;) { int c = getchar(); if(c=='\n' || c==EOF) break; }
}

int main(int argc, char** argv) { // Aufgabe 2
	const int MAX_ELEMENTS = 10;
	int a[MAX_ELEMENTS]; // Array

	int size = -1;
	// Groesse abfragen
	for(;;) {
		printf("Groesse: ");
		if(scanf("%d", &size) != 1) { // groesse einlesen
			printf("Input-Fehler, bitte versuchen sie es erneut!\n"); // fehler
			flushInput();
			continue;
		}
		if(size < 0 || size > MAX_ELEMENTS) { // bounds-check
			printf("Ungueltige Arraygroesse <%d>, bitte waehlen sie eine andere Groesse!\n", size); // fehler
			flushInput();
			continue;
		}
		break;
	}

	// Elemente einlesen
	for(int i = 0; i < size; i++) {
		printf("%d. Element: ", i + 1);
		if(scanf("%d", a + i) != 1) { // Element einlesen
			printf("Integer konnte nicht gelesen werden, bitte versuchen sie es erneut!\n"); // fehler
			flushInput();
			i--;
		}
	}

	// Elemente ausgeben
	for(int i = 0; i < size; i++)
		printf("a[%d] = %d\n", i, a[i]);

	return 0;
}