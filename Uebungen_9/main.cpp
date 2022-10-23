#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include <time.h>

#include <math.h> // sqrtf()

// 1.)
typedef struct {
	float x, y;
} Punkt;

float dist(Punkt *punkt1, Punkt *punkt2) {
	// A^2 + B^2 = C^2
	// sqrt(A^2 + B^2) = C

	// const float A = (*punkt1).y - (*punkt2).y;
	const float A = punkt1->y - punkt2->y;
	const float B = punkt1->x - punkt2->x;
	const float sqA = A * A;
	const float sqB = B * B;

	const float dist = sqrtf(sqA + sqB);

	return dist;
}

// 3.)
void initPunkte(Punkt *punkte, int numPunkte) {
	for(int i = 0; i < numPunkte; i++) {
		punkte[i].x = rand() * 20. / RAND_MAX - 10;
		punkte[i].y = rand() * 20. / RAND_MAX - 10;
	}
}

int main(int argc, char **argv) {
	srand(time(0));

	const int NUM_PUNKTE = 10;

	// 2.)
	Punkt *punkte = (Punkt*)malloc(sizeof(Punkt) * NUM_PUNKTE);
	// Punkt *punkte = new Punkt[NUM_PUNKTE];

	initPunkte(punkte, NUM_PUNKTE);


	printf("P1: (%f, %f)\n", punkte[0].x, punkte[0].y);
	printf("P2: (%f, %f)\n", punkte[1].x, punkte[1].y);
	printf("Dist(P1, P2): %f\n", dist(punkte+0, punkte+1));

	return 0;
}