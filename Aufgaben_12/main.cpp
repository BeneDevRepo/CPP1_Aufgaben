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
	mat->n = 0;
	mat->m = 0;
	mat->data = nullptr;
}

// 1.3)
void init_rand_matrix(matrix m) {
	for(int32_t i = 0; i < m.n; i++) // "y"
		for(int32_t j = 0; j < m.m; j++) // "x"
			matrix_at(&m, i, j) = rand() * 1. / RAND_MAX;
}

// 1.4)
void print_matrix(const matrix mat) {
	for(int32_t i = 0; i < mat.n; i++) { // Zeilen ("y")
		for(int32_t j = 0; j < mat.m; j++) // Spalten ("x")
			printf("%.4f  ", matrix_at(&mat, i, j));
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


// 12 -----------------------------
void store_matrix(const matrix *const mat, const char *const fileName) {
	FILE *const fp = fopen(fileName, "w");
	fprintf(fp, "%d %d ", mat->m, mat->n);
	for(int32_t i = 0; i < mat->n; i++) // Zeilen ("y")
		for(int32_t j = 0; j < mat->m; j++) // Spalten ("x")
			fprintf(fp, "%f ", matrix_at(mat, i, j));
	fclose(fp);
}

matrix load_matrix(const char *const fileName) {
	FILE *const fp = fopen(fileName, "r");

	int m, n;
	fscanf(fp, "%d %d ", &m, &n);

	matrix mat = neue_matrix(n, m);

	for(int32_t i = 0; i < mat.n; i++) { // Zeilen ("y")
		for(int32_t j = 0; j < mat.m; j++) { // Spalten ("x")
			fscanf(fp, "%f ", &matrix_at(&mat, i, j));
			// float val;
			// fscanf(fp, "%f ", &val);
			// matrix_at(&mat, i, j) = val;
		}
	}
	fclose(fp);

	return mat;
}

void store_matrix_bin(const matrix *const mat, const char *const fileName) {
	FILE *const fp = fopen(fileName, "wb");

	fwrite(&mat->m, sizeof(int), 1, fp);
	fwrite(&mat->n, sizeof(int), 1, fp);
	fwrite(mat->data, 4, mat->m * mat->n, fp);

	fclose(fp);
}

matrix load_matrix_bin(const char *const fileName) {
	FILE *const fp = fopen(fileName, "rb");

	int m, n;
	fread(&m, sizeof(int), 1, fp);
	fread(&n, sizeof(int), 1, fp);

	matrix mat = neue_matrix(n, m);
	fread(mat.data, 4, mat.m * mat.n, fp);

	fclose(fp);

	return mat;
}

void testMatFunctions() {
	srand(time(0));

	matrix orig = neue_matrix(3, 2); // Matrix erstellen
	init_rand_matrix(orig); // Matrix mit zufallswerten fuellen

	printf("Matrix:\n");
	print_matrix(orig); // Matrix drucken

	// 2.2)
	matrix transposed = matrix_transpose(orig); // transponierte Matrix erstellen
	printf("\nTransponierte Matrix:\n");
	print_matrix(transposed); // transponierte Matrix drucken
	delete_matrix(&transposed);


	// store_matrix(&orig, "Orig.txt");
	store_matrix_bin(&orig, "Orig.bin");

	delete_matrix(&orig);

	orig = load_matrix_bin("Orig.bin");
	// orig = load_matrix("Orig.txt");

	printf("\nMatrix Geladen:\n");
	print_matrix(orig); // Matrix drucken

	delete_matrix(&orig);
}

int main() {
	matrix mat{};

	
	for(bool quit = false; !quit; ) {
		char input;

		for(;;) {
			// printf("\x1B[0;0H"); // Cursor pos <y=0; x=0>
			// printf("\x1B[2J"); // Erase Entire Viewport

			printf("Please choose an action\n");
			printf("c - Create Matrix\n");
			printf("p - Print Matrix\n");
			printf("q - quit\n");
			printf("Your choice: ");

			if(scanf(" %c", &input) != 1) {
				printf("Error reading input\n");
				continue;
			}
			break;
		}

		switch(input) {
			case 'c':
				int n, m;
				printf("Bitte geben sie die Groesse der Matrix an (n m): ");
				scanf("%d %d", &n, &m);
				mat = neue_matrix(n, m);
				init_rand_matrix(mat);
				// printf("Creating Matrix...\n");
				// for(int i = 0; i < 1000000000; i++);
				break;

			case 'p':
				if(!mat.data) {
					printf("Fehler: Keine Matrix vorhanden.\n");
					break;
				}
				print_matrix(mat);
				// printf("Printing Matrix...\n");
				// for(int i=0; i<1000000000; i++);
				break;

			case 'q':
				quit = true;
				break;
		}
	}

	if(mat.data)
		delete_matrix(&mat);
}