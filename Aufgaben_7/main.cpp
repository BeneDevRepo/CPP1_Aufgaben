/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdlib.h> // fuer rand() u. srand()
#include <stdint.h> // Aussagekraeftigere u. portablere Integer (typedefs)
#include <stdio.h>
#include <math.h> // fuer fabsf()
// #include <time.h> // fuer srand(time(0));

// a / b)
void fillWithRandomFloats(float *const arr, const uint32_t NUM_FLOATS) {
	for(uint32_t i = 0; i < NUM_FLOATS; i++)
		arr[i] = rand() * 10. / RAND_MAX;
}

// c)
float min(const float *const arr, const uint32_t NUM_FLOATS) {
	float minVal = arr[0]; // kleinstes Element bisher
	for(uint32_t i = 1; i < NUM_FLOATS; i++)
		if(arr[i] < minVal) // Wenn aktuelles Element kleiner
			minVal = arr[i]; // aktuelles Element festhalten
	return minVal;
}

// d)
float max(const float *const arr, const uint32_t NUM_FLOATS) {
	float maxVal = arr[0]; // groesstes Element bisher
	for(uint32_t i = 1; i < NUM_FLOATS; i++)
		if(arr[i] > maxVal) // Wenn aktuelles Element groesser
			maxVal = arr[i]; // aktuelles Element festhalten
	return maxVal;
}

// e)
float arithmeticMean(const float *const arr, const uint32_t NUM_FLOATS) {
	float sum = 0; // summe aller Elemente
	for(uint32_t i = 0; i < NUM_FLOATS; i++)
		sum += arr[i]; // aktuelles Element aufaddieren
	return sum / NUM_FLOATS; // Durch Anzzahl der Elemente Teilen
}

// f)
float meanAbsoluteDeviation(const float *const arr, const uint32_t NUM_FLOATS) {
	const float mean = arithmeticMean(arr, NUM_FLOATS); // arithmetischer Mittelwert
	float absDiv = 0; // Absolute Abweichung vom arithmetischen Mittelwert
	for(uint32_t i = 0; i < NUM_FLOATS; i++)
		absDiv += fabsf(arr[i] - mean);
	return absDiv / NUM_FLOATS; // durch Anzahl der Werte teilen um Mittlere absolute abweichung vom arithmetischen Mittel zu erhalten
}

// g)
int main() {
	srand(0); // oder srand(time(0));
	const uint32_t NUM_FLOATS = 100;
	float arr[NUM_FLOATS];
	fillWithRandomFloats(arr, NUM_FLOATS);

	// printf("Zahlen:\n");
	// printArray(arr, NUM_FLOATS, 10);

	printf("Minimum: %f\n", min(arr, NUM_FLOATS));
	printf("Maximum: %f\n", max(arr, NUM_FLOATS));
	printf("Mittelwert: %f\n", arithmeticMean(arr, NUM_FLOATS));
	printf("Mittlere Absolute Abweichung: %f\n", meanAbsoluteDeviation(arr, NUM_FLOATS));
}