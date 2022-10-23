/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdint.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>


// a)
void fillRandomIntegers_1_100(int *const arr, const uint32_t NUM_INTS) {
	for(uint32_t i = 0; i < NUM_INTS; i++)
		arr[i] = 1 + rand() % 100; // 1 bis einschliesslich 100
}

void swapInt(int *const a, int *const b) { // Tauscht 2 Integer aus
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void selection_sort(int laenge, int a[]) {
	for(uint32_t numSorted = 0; numSorted < laenge-1; numSorted++) { // Schleife bis (Anzahl unsortierter Elemente == 1)
		int minVal = a[numSorted]; // bisher kleinster unsortierter Wert
		uint32_t minIndex = numSorted; // Index des kleinsten unsortierten Werts
		for(uint32_t i = 1; i < laenge - numSorted; i++) { // 1. unsortierten Wert ueberspringen, da er bereits als startwert genutzt wird
			if(a[numSorted + i] < minVal) { // kleiner als bisher kleinster unsortierter Wert -> aktuellen Wert merken
				minVal = a[numSorted + i];
				minIndex = numSorted + i;
			}
		}
		swapInt(a + numSorted, a + minIndex); // a[numSorted] mit kleinstem unsortierten Wert tauschen
	}
}

// c)
void printIntArray(const int *const arr, const uint32_t NUM_INTS) {
	const uint16_t NUM_SPALTEN = 4;
	for(int32_t i = 0; i < NUM_INTS;) {
		for(uint16_t x = 0; x < NUM_SPALTEN && i < NUM_INTS; x++, i++)
			printf("Array[%2d] = %3d   ", i, arr[i]);
		printf("\n");
	}
}

int main() {
	srand(time(0));

	const uint32_t NUM_INTS = 100;
	int arr[NUM_INTS];
	fillRandomIntegers_1_100(arr, NUM_INTS);

	printf("\nZahlen unsortiert:\n");
	printIntArray(arr, NUM_INTS);

	selection_sort(NUM_INTS, arr);

	printf("\nZahlen sortiert:\n");
	printIntArray(arr, NUM_INTS);
}