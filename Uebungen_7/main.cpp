#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include <time.h>

// #include <memory.h>

int main(int argc, char** argv) {
	srand(time(0));

	const uint16_t NUM_ZAHLEN = 6;
	uint16_t zahlen[NUM_ZAHLEN];

	const uint16_t NUM_MIN = 1;
	const uint16_t NUM_MAX = 49;

	for(uint16_t i = 0; i < NUM_ZAHLEN; i++) {
		bool einzigartig;
		do {
			zahlen[i] = NUM_MIN + rand() % (NUM_MAX - NUM_MIN + 1);
			einzigartig = true;
			for(uint16_t j = 0; j < i; j++)
				if(zahlen[i] == zahlen[j])
					einzigartig = false;
		} while (!einzigartig);
	}

	for(uint16_t i = 0; i < NUM_ZAHLEN; i++)
		printf("Zahl %hu: %hu\n", i, zahlen[i]);

	return 0;
}