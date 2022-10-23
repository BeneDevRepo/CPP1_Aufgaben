/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdio.h>

// Explizitere Integertypen, heutzutage eigentlich Standard...
// z.B. uint8_t, uint64_t statt unsigned char, unsigned long long
// #include <stdint.h> // c
#include <cstdint> // c++ wrapper

#define NUM_COLUMNS 4
#define NUM_ROWS (128 / NUM_COLUMNS)

// 1a)
void task1a() {
	for(int y = 0; y < NUM_ROWS; y++) {
		for(int x = 0; x < NUM_COLUMNS; x++)
			printf("%03d ", x * NUM_ROWS + y);
		printf("\n");
	}
}

// 1b)
void task1b() {
	for(int y = 0; y < NUM_ROWS; y++) {
		for(int x = 0; x < NUM_COLUMNS; x++) {
			const int val = x * NUM_ROWS + y;
			printf("%03o %03d %03x  ", val, val, val); // numerischer Wert in Oktal, Dezimal und Hexadezimal drucken
		}
		printf("\n");
	}
}

// 1c)
void task1c() {
	// Zahlensysteme drucken
	for(int x = 0; x < NUM_COLUMNS; x++) {
		printf("Okt Dez Hex Zch");
		if(x < NUM_COLUMNS-1) printf(" | ");
	}
	printf("\n");

	// Trennlinie drucken
	for(int x = 0; x < NUM_COLUMNS * (4*4+2) - 3; x++)
		printf("-");
	printf("\n");

	// die Eigentliche Tabelle drucken
	for(int y = 0; y < NUM_ROWS; y++) {
		for(int x = 0; x < NUM_COLUMNS; x++) {
			const int val = x * NUM_ROWS + y;
			printf("%03o %03d %03x ", val, val, val); // numerischer Wert in Oktal, Dezimal und Hexadezimal drucken

			if(val >= 32 && val <= 126)
				printf(" %c ", (char)val); // Ascii-Zeichen drucken
			else
				printf("..."); // Platzhalter für nicht-druckbare Zeichen

			if(x < NUM_COLUMNS-1) // veertikale Trennlinie fuer letzte Spalte auslassen
				printf(" | ");
		}
		printf("\n");
	}
}

float task2_float() {
	float kontostand = 10000.f;
	for(int i=0; i<50; i++)
		kontostand *= 1.0313f;
	printf("%.10f\n", kontostand);
	return kontostand;
}

double task2_double() {
	double kontostand = 10000.;
	for(int i=0; i<50; i++)
		kontostand *= 1.0313;
	printf("%.10f\n", kontostand);
	return kontostand;
}

int main(int argc, char** argv) {
	// printf("\n");

	// Aufgabe 1a)
	// printf("\n1a)\n");
	// task1a();

	// Aufgabe 1b)
	// printf("\n1b)\n");
	// task1b();

	// Aufgabe 1c)
	printf("\n1c)\n");
	task1c();

	printf("\n2)\n");
	printf("\nfloat:\n");
	task2_float();

	printf("\ndouble:\n");
	task2_double();

	/*
	 * float output: 46692.7773437500
	 * double output: 46692.9042552705
	 * Differenz: ca. 0.1269115205
	 * 
	 * Beobachtung: beträchtlicher Unterschied; float output ist kleiner.
	 * Mit hoher wahrscheinlichkeit is keines de beiden Ergebnisse korrekt,
	 * die Berechnungen mit doubles sollten allerdings näher an der Wahrheit liegen.
	 * In der Realität sollte man für Finanz-Berechnungen natürlich Fixed-Comma Arithmetik nutzen,
	 * um die Präzisions-Schwankungen von Floating-Point-Zahlen zu umgehen.
	 * 
	 */

	printf("\n");

	return 0;
}