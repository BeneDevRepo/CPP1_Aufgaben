/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void flushInput() {
	for(;;) { int c = getchar(); if(c=='\n' || c==EOF) break; }
}

int main(int argc, char** argv) { // Aufgabe 2
	srand(time(0)); // Zufall initialisieren

	for(;;) {
		printf("Das Spiel beginnt!\n");
		const int val = rand() % 100; // zu erratenden Wert festlegen
		for(;;) {
			printf("Geben sie eine Zahl zwischen 0 und 99 ein: ");
			int guess;
			if(scanf("%d", &guess) != 1) { // falls Fehler beim einlesen des geratenen Werts:
				flushInput(); // Input-buffer leeren
				printf("Zahl konnte nicht gelesen werden. bitte versuchen sie ees erneut!\n"); // Fehlermeldung ausgeben
				continue; // Neue eingabe anfordern
			}
			if(guess < 0 || guess > 99) { // falls geratener Wert ausserhalb des Definitionsbereiches:
				printf("Zahl ausserhalb des erlaubten bereiches. bitte versuchen sie ees erneut!\n"); // Fehlermeldung ausgeben
				continue; // Neue eingabe anfordern
			}
			if(guess == val) { // falls geratener Wert korrek:
				printf("Gut geraten! %d ist richtig!\n\n", guess);
				break; // neues spiel beginnen
			}
			printf("Leider falsch! Die gesuchte Zahl ist "); // geratener Wert war falsch
			printf((val < guess) ? "kleiner\n" : "groesser\n"); // zu gross oder zu klein
		}
	}
	return 0;
}