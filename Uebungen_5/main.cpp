#include <stdio.h>
#include <stdlib.h>

void flushInput() {
	for(;;) { int c = getchar(); if(/*c=='\r' || */c=='\n' || c==EOF) break; }
}




int val;

void setRandom() {
	val = rand() % 100;
}

bool guessRandom(int num) {
	if(num == val) {
		printf("Gut geraten! %d ist richtig!\n", num);
		return true;
	}
	printf("Leider falsch! Die gesuchte Zahl ist ");
	printf((val < num) ? "kleiner\n" : "groesser\n");
	return false;
}

void playNumberGuess() {
	setRandom();
	for(;;) {
		int guess;
		printf("Geben sie eine Zahl zwischen 0 und 99 ein: ");
		if(scanf("%d", &guess) != 1) {
			flushInput();
			printf("Zahl konnte nicht gelesen werden. bitte versuchen sie ees erneut!\n");
			continue;
		}
		if(guess < 0 || guess > 99) {
			printf("Zahl ausserhalb des erlaubten bereiches. bitte versuchen sie ees erneut!\n");
			continue;
		}
		if(guessRandom(guess))
			break;
	}
}



int sum0K(int k) {
	if(k<=1)
		return k;
	return k + sum0K(k-1);
}



int fibRecCalls;

long long fibRec(int n) {
	fibRecCalls++;
	if(n==1 || n==2)
		return 1;
	return fibRec(n-1) + fibRec(n-2);
}

int main(int argc, char** argv) {
	// printf("Summe bis %d: %d", 60, sum0K(60));

	for(int n = 35; n <= 40; n++) {
		fibRecCalls = 0;
		long long fib = fibRec(n);
		printf("Fibonacci(%d) = %d mit %lld Funktionsaufrufen\n", n, fib, fibRecCalls);
	}



	// srand(0);
	// for(;;) {
	// 	printf("\nMoegen die Spiele beginnen!\n");
	// 	playNumberGuess();
	// }
	return 0;
}