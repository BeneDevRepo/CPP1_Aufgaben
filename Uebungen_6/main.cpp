#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>
// #include <math.h>

void printArrayU8(const uint8_t *const array, const uint32_t NUM_INTS) {
	for(uint32_t i = 0; i < NUM_INTS; i++) {
		for(uint8_t j = 0; j < array[i]; j++)
			printf((j==0) ? "8" : (j==array[i]-1) ? "0" : "=");
		printf("\n");
	}
}

void glaette(uint8_t *const arr, const uint32_t NUM_INTS) {
	uint8_t backlog[] = { arr[0], arr[1] };
	for(uint32_t i = 2; i < NUM_INTS-2; i++) {
		uint16_t sum = backlog[0] + backlog[1] + arr[i] + arr[i + 1] + arr[i + 2];
		backlog[0] = backlog[1];
		backlog[1] = arr[2 + i];
		arr[2 + i] = sum / 5;
	}
}

int main(int argc, char** argv) {
	const uint32_t NUM_ZAHLEN = 20;

	// Array fuellen
	srand(time(0));
	uint8_t zahlen[NUM_ZAHLEN];
	for(uint32_t i = 0; i < NUM_ZAHLEN; i++)
		zahlen[i] = rand() % 20;

	// Array ausgeben
	printf("-----------------------------   Zahlen:\n");
	printArrayU8(zahlen, NUM_ZAHLEN);

	// Mittelwerte berechnen
	glaette(zahlen, NUM_ZAHLEN);

	// Mittelwerte Ausgeben
	printf("----------------------------   Gefiltert:\n");
	printArrayU8(zahlen, NUM_ZAHLEN);

	return 0;
}