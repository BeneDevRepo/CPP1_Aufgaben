/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdio.h>

// #define bool int
// typedef enum { false=0, true=!false} bool;

bool isPrime(const int n) {
	if(n < 2)
		return false;

	for(int i = 2; i < n/2; i++)
		if(n % i == 0)
			return false;

	return true;
}

void drawPyramid(const int maxWidth) {
	for(int width = 1; width <= maxWidth; width += 2) {
		for(int i = 0; i < (maxWidth-width)/2; i++)
			printf(" ");

		printf("*");

		for(int i = 0; i < width-2; i++)
			printf(" ");

		if(width > 1)
			printf("*");

		printf("\n");
	}
}

int main(int argc, char** argv) {
	// int n = 44777;
	// for(int n = 1; n <= 50; n++)
	// 	printf("%d is %s\n", n, isPrime(n) ? "Prime" : "not Prime");

	for(int i=1; i<=11; i+=2) {
		printf("\nPyramid width (width = %d):\n", i);
		drawPyramid(i);
	}

	return 0;
}