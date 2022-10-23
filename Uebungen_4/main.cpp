#include <stdio.h>

int fibo(int);
int fiboRec(int);

int fibo(int n) {
	if(n == 0)
		return 0;
	int fib1 = 1, fib2 = 1; // fib(n-2), fib(n-1)
	for(int i = 0; i < n-2; i++) {
		int newFib = fib1 + fib2;
		fib1 = fib2;
		fib2 = newFib;
	}
	return fib2;
}



int fiboRec(int n) {
	if(n == 0)
		return 0;
	if(n <= 2)
		return 1;
	return fiboRec(n-1) + fiboRec(n-2);
}

void printIntArray(int* arr, int num) {
	for(int i=0; i<num; i++)
		printf("a[%d] = %d\n", i, arr[i]);
}

int main(int argc, char** argv) {
	printf("\nIterative Fibonacci:\n");
	for(int i = 1; i <= 10; i++)
		printf("Fibo(%d) = %d\n", i, fibo(i));

	printf("\nRecursive Fibonacci:\n");
	for(int i = 1; i <= 10; i++)
		printf("Fibo(%d) = %d\n", i, fiboRec(i));

	// const int n = 45;
	// printf("\nFibo(%d) = %d\n", n, fiboRec(n));


	const int NUM_ZAHLEN = 10;

	printf("\n1. + 2. + 3.)\n");
	int zahlen[NUM_ZAHLEN]; // 1.
	for(int i = 0; i < NUM_ZAHLEN; zahlen[i++]=1); // 2.
	printIntArray(zahlen, NUM_ZAHLEN); // 3.

	// 4.
	printf("\n4.)\n");
	{
		int neueZahlen[NUM_ZAHLEN] = {0};
		for(int i = 0; i < NUM_ZAHLEN; i++)
			for(int j = 0; j <= i; j++)
				neueZahlen[i] += zahlen[j];
		for(int i = 0; i < NUM_ZAHLEN; i++)
			zahlen[i] = neueZahlen[i];
	}
	printIntArray(zahlen, NUM_ZAHLEN); // 3.

	// 5.
	printf("\n5.)\n");
	for(int i = 0; i < NUM_ZAHLEN / 2; i++) {
		int tmp = zahlen[i];
		zahlen[i] = zahlen[NUM_ZAHLEN-1-i];
		zahlen[NUM_ZAHLEN-1-i] = tmp;
	}
	printIntArray(zahlen, NUM_ZAHLEN); // 3.

	return 0;
}




