/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <cstdio>
#include <cstdint>

// Farbfunktion (Koordinaten stehen jeweils fuer Bloecke von 32*32 Pixeln um x und y nicht in jeder Funktion durch 32 teilen zu muessen)
// parameter: x, y, Wert der Farbe Weiss
// rueckgabe: Graustufenwert zwischen 0 und inklusive whitePoint
using Pattern = uint8_t(*)(const uint32_t x, const uint32_t y, const uint8_t whitePoint);
// typedef uint8_t(*Pattern)(const uint32_t x, const uint32_t y, const uint8_t whitePoint); // unleserliche C-Alternative zu using

// 2)
uint8_t horizontal_lines(const uint32_t x, const uint32_t y, const uint8_t whitePoint) {
	return (y & 1) ? 0 : whitePoint; //	jeder 2. Horizontale Streifen schwarz, ansonsten weiss (schwarz wenn y ungerade)
}

// 3)
uint8_t checkerboard(const uint32_t x, const uint32_t y, const uint8_t whitePoint) {
	return ((x & 1) ^ (y & 1)) ? whitePoint : 0; // weiss wenn x oder y ungerade und die jeweils andere Achse gerade ist; ansonsten schwarz
}

// 4)
uint8_t checkerboard_fade(const uint32_t x, const uint32_t y, const uint8_t whitePoint) {
	// Schwarz von oben links nach unten rechts zeilenweise linear zwischen 0 und whitePoint interpolieren:
	const uint32_t blockIndex = y * 8 + x;
	const uint32_t blackCol = blockIndex * whitePoint / (8 * 8);
	return ((x & 1) ^ (y & 1)) ? whitePoint : blackCol;
}

// 2, 3, 4)
void storePattern(const Pattern pattern, const uint32_t width, const uint32_t height, const char *const filename, const int8_t whitePoint) {
	FILE *fp = fopen(filename, "w"); // Datei (Ascii-Modus)

	fprintf(fp, "P2\n"); // Format (Graustufen ascii)
	fprintf(fp, "%u %u\n", width, height); // Breite + Hoehe
	fprintf(fp, "%hhu\n", whitePoint); // wert fuer Weiss

	for(uint32_t y = 0; y < height; y++) {
		for(uint32_t x = 0; x < width; x++)
			fprintf(fp, "%d ", (int)pattern(x / 32, y / 32, whitePoint)); // Pixelwert (in 32*32 Pixel bloecken) berechnen + speichern
		fprintf(fp, "\n"); // Zeilenumbruch nach Pixelzeile
	}

	fclose(fp); // Datei schliessen
}

// 5)
void storePatternBinary(const Pattern pattern, const uint32_t width, const uint32_t height, const char *const filename, const int8_t whitePoint) {
	FILE *fp = fopen(filename, "wb"); // Datei (binaer-Modus)

	fprintf(fp, "P5\n"); // Format (Graustufen binaer)
	fprintf(fp, "%u %u\n", width, height); // Breite + Hoehe
	fprintf(fp, "%hhu\n", whitePoint); // wert fuer Weiss

	for(uint32_t y = 0; y < height; y++)
		for(uint32_t x = 0; x < width; x++)
			fputc(pattern(x / 32, y / 32, whitePoint), fp); // Pixelwert (in 32*32 Pixel bloecken) berechnen + binaer speichern

	fclose(fp); // Datei schliessen
}

int main() {
	storePattern(horizontal_lines,        256, 256, "lines.pgm",                    255); // 2.
	storePattern(checkerboard,            256, 256, "checkerboard.pgm",             255); // 3.
	storePattern(checkerboard_fade,       256, 256, "checkerboard_fade.pgm",        255); // 4.
	storePatternBinary(checkerboard_fade, 256, 256, "checkerboard_fade_binary.pgm", 255); // 5.
}