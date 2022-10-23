/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdio.h>

void reverse_str(char puffer[], int laenge);
int my_strlen(char puffer[]);

int main(void) {
	// Zeichenkette mit maximal 199 Zeichen
	char puffer[200];
	while(1) {
		printf("Geben Sie eine Zeichenkette ein:\n");
		int anz = scanf("%[^\n]", puffer);
		getchar(); // Konsumiere '\n'
		if(anz != 1) {
			printf("Ende\n");
			break;
		}
		int laenge = my_strlen(puffer);
		reverse_str(puffer, laenge);
		printf("%s\n", puffer);
	}
	return 0;
}

int my_strlen(char puffer[]) {
	int len = 0;
	for(; puffer[len]; len++); // laenge erhoehen, solange das Zeichen nach <len> zeichen kein Null-Terminator ist
	return len;
}

void reverse_str(char puffer[], int laenge) {
	// tausche jedes Element (i Zeichen vom Start des Arrays entfernt)
	// mit dem dem gegenueberliegenden Element (i Zeichen vom Ende des Arrays entfernt)
	for(int i = 0; i < laenge / 2; i++) { // bei ungerader laenge wird (laenge / 2) abgerundet und das mittlere Element ignoriert.
		// Elemente austauschen:

		// XOR Swap
		// puffer[i] ^= puffer[laenge-1-i]; // lhs = lhs XOR rhs
		// puffer[laenge-1-i] ^= puffer[i]; // rhs = rhs XOR lhs => rhs = rhs XOR (lhs XOR rhs) => <rhs = lhs>
		// puffer[i] ^= puffer[laenge-1-i]; // lhs = lhs XOR rhs => lhs = (lhs XOR rhs) XOR lhs => <lhs = rhs>

		// Alternativer (langweiliger) austausch
		const char tmp = puffer[i]; // puffer[i] speichern
		puffer[i] = puffer[laenge-1-i]; // puffer[i] mit gegenueberliegendem Element ueberschreiben
		puffer[laenge-1-i] = tmp; // Gegenueberliegendes Element durch tmp ersetztn
	}
}