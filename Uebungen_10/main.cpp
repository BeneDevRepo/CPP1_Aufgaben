#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include <time.h>

// #include <math.h> // sqrtf()


constexpr uint32_t STR_LEN = 20;
constexpr uint32_t NUM_STRS = 10;

int main(int argc, char **argv) {
	srand(time(0));

	char str[STR_LEN];

	FILE *fp = fopen("Output.txt", "wb");

	for(uint32_t n = 0; n < NUM_STRS; n++) {
		for(uint32_t i = 0; i < STR_LEN; i++)
			str[i] = 'A' + rand() % 26;

		// Konsole:
		for(uint32_t i = 0; i < STR_LEN; i++)
			printf("%c", str[i]);
		printf("\n");

		// Datei:
		fwrite(str, sizeof(char), STR_LEN, fp);
		fwrite("\n", sizeof(char), 1, fp);
	}

	fclose(fp);

	return 0;
}