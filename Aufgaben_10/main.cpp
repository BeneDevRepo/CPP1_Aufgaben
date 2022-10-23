/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

// 1.1)
struct matrix {
	uint32_t n, m; // Zeilen, Spalten (height, width)
	double *data; // 
};

// Hilfsfunktion um Index-Berechnung nicht zu wiederholen:
inline double& matrix_at(const matrix *const mat, const uint32_t i, const uint32_t j) {
	return mat->data[i * mat->m + j]; // Index-Berechnung
}

// 1.2)
struct matrix neue_matrix(int n, int m) { // "Hoehe", "Breite"
	matrix out;
	out.data = new double[n * m];
	out.n = n;
	out.m = m;
	return out;
}

void delete_matrix(matrix *mat) {
	delete[] mat->data;
}

// 1.3)
void init_rand_matrix(struct matrix m) {
	for(int32_t i = 0; i < m.n; i++) // "y"
		for(int32_t j = 0; j < m.m; j++) // "x"
			matrix_at(&m, i, j) = rand() * 1. / RAND_MAX;
}

// 1.4)
void print_matrix(const matrix *const mat) {
	for(int32_t i = 0; i < mat->n; i++) { // Zeilen ("y")
		for(int32_t j = 0; j < mat->m; j++) // Spalten ("x")
			printf("%.4f  ", matrix_at(mat, i, j));
		printf("\n"); // Umbruch nach jeder Zeile
	}
}

// 2.1)
struct matrix matrix_transpose(struct matrix m) {
	matrix out = neue_matrix(m.m, m.n); // speicher fuer transponierte Matrix (m <-> n austauschen)
	for(int32_t i = 0; i < m.n; i++) // Zeilen von m
		for(int32_t j = 0; j < m.m; j++) // Spalten von m
			matrix_at(&out, j, i) = matrix_at(&m, i, j); // Werte transponiert kopieren
	return out;
}

int main() {
	srand(time(0));

	matrix orig = neue_matrix(3, 2); // Matrix erstellen
	init_rand_matrix(orig); // Matrix mit zufallswerten fuellen

	printf("Matrix:\n");
	print_matrix(&orig); // Matrix drucken

	// 2.2)
	matrix transposed = matrix_transpose(orig); // transponierte Matrix erstellen
	printf("\nTransponierte Matrix:\n");
	print_matrix(&transposed); // transponierte Matrix drucken

	// Matritzenspeicher freigeben
	delete_matrix(&transposed);
	delete_matrix(&orig);
}