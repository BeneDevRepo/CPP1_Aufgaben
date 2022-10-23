/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <stdio.h>

// 1)
int ggt(int a, int b) {
	if(a==0 || b==0)
		return a==0 ? b : a;

	for(int rest; b != 0; b = rest) {
		rest = a % b;
		a = b;
	}
	return a;
}


// 2)
int fakultaet(int n);

int binomialkoeffizient(int n, int k) {
	if(n >= k && k >= 0)
		return fakultaet(n) / (fakultaet(k) * fakultaet(n - k));
	return -1; // ausserhalb des Definitionsbereichs; n und k koennten alternativ unsigniert sein
}

int fakultaet(int n) {
	int res = 1;
	for(; n > 1; n--) // i=1 ueberspringen; res *= 1 unnoetig
		res *= n;
	return res;
}

// Freiwillig: Pascalsches Dreieck
void printPascalTriangle(const int numLines) {
	for(int n = 0; n < numLines; n++) {
		for(int i = 0; i < numLines-1 - n; i++)
			printf("  ");
		printf("n=%d", n);
		for(int k = 0; k <= n; k++)
			printf("%4d", binomialkoeffizient(n, k));
		printf("\n");
	}
}


int main(int argc, char** argv) {
	// Aufgabe 1)
	printf("\n1)\n");
	printf("ggt(4, 6) = %d\n",   ggt(4,  6)); // 2
	printf("ggt(18, 48) = %d\n", ggt(18, 48)); // 6
	printf("ggt(36, 66) = %d\n", ggt(36, 66)); // 6
	printf("ggt(12, 27) = %d\n", ggt(12, 27)); // 3
	printf("ggt(18, 24) = %d\n", ggt(18, 24)); // 6


	// Aufgabe 2)
	printf("\n2)\n");
	printf("0 ueber 0 = %d\n", binomialkoeffizient(0, 0)); // 1
	printf("3 ueber 0 = %d\n", binomialkoeffizient(3, 0)); // 1
	printf("3 ueber 1 = %d\n", binomialkoeffizient(3, 1)); // 3
	printf("4 ueber 2 = %d\n", binomialkoeffizient(4, 2)); // 6
	printf("6 ueber 3 = %d\n", binomialkoeffizient(6, 3)); // 20


	// Fakultät Tests:
	printf("\nFakultaet Testcases:\n");
	for(int i = 0; i <= 10; i++)
		printf("%2d! = %d\n", i, fakultaet(i));


	// Pascalsches Dreieck:
	const int maxN = 7;
	printf("\nPaskalsches Dreieck bis n=%d:\n\n", maxN);
	printPascalTriangle(maxN + 1);
	printf("\n");

	return 0;
}