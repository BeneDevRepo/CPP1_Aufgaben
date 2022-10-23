/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdio.h>

// Harmonische Reihe
double harmonicSequence(const int k) { // 1/1 + 1/2 + 1/3 + 1/4 + 1/5 ...
	double sum = 0;
	for(int i = 1; i <= k; i++)
		sum += 1. / i;
	return sum;
}

// Alternierende harmonische Reihe
double alternatingHarmonicSequence(const int k) { // 1/1 - 1/2 + 1/3 - 1/4 + 1/5 ...
	double sum = 0;
	for(int i = 1; i <= k; i++) {
		const int fac = i%2==1 ? 1 : -1; // (-1) ^ (i+1) -> i ungerade: 1; i gerade: -1
		sum += fac *  (1. / i);
	}
	return sum;
}

// Leibnitz-Reihe
double leibnitzSequence(const int k) { // 1/1 - 1/3 + 1/5 - 1/7 ...
	double sum = 0;
	for(int i = 1; i <= k; i++) {
		const int fac = i%2==1 ? 1 : -1; // (-1) ^ (i+1) -> i ungerade: 1; i gerade: -1
		sum += fac * (1. / (2. * i - 1));
	}
	return sum;
}

// Geometrische Reihe
double geometricSequence(const int k) { // 1/1 + 1/2 + 1/4 + 1/8 ...
	double sum = 0;
	for(int i = 0; i < k; i++) {
		double element = 1.;
		for(int p = 0; i - p; p++, element /= 2); // element = 1 * ((1/2) ^ i) => element=1; divide by 2 <i> times
		sum += element;
	}
	return sum;
}

int main(int argc, char** argv) {
	printf("\n\n");

	printf("Harmonische Reihe: ");
	printf("%.6f", harmonicSequence(1000)); // Harmonische Reihe

	printf("\n\n");

	printf("Alternierende Harmonische Reihe: ");
	printf("%.6f", alternatingHarmonicSequence(1000)); // Alternierende harmonische Reihe

	printf("\n\n");

	printf("Leibnitz Reihe: ");
	printf("%.6f", leibnitzSequence(1000)); // Leibnitz-Reihe

	printf("\n\n");

	printf("Geometrische Reihe: ");
	printf("%.6f", geometricSequence(1000)); // Geometrische Reihe

	printf("\n\n");

	return 0;
}