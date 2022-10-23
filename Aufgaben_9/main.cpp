/*//////////////////////////////////
//  Benedikt Binger
//////////////////////////////////*/

#include <cstdint>
#include <cstdio>
#include <cstring>

uint16_t numDigits(const uint32_t num) { // Anzahl benoetigter Ziffern zur repraesentation eines Integers im Dezimalsystem berechnen
    if (num / 10 == 0) return 1; // Abbruchbedingung
    return 1 + numDigits(num / 10); // letzte Dezimalziffer entfernen und dafuer 1 auf die anzahl der Ziffern addieren
}

uint8_t decDigit(uint32_t num, uint8_t digitIndex) { // Dezimalziffer aus integer extrahieren
	for(; digitIndex--; num /= 10); // sooft durch 10 teilen, bis die gesuchte Ziffer an unsignifikantester Stelle steht
	return num % 10; // Ziffer mittels Modulo isolieren
}

// Aufgabe 1)
void RLEncode(char *const str) { // Ueberschreibt originaltext
	uint32_t readPos = 0;
	uint32_t writePos = 0;
	while(str[readPos]) { // bis Ende des Textes
		// Wenn string zuende oder einzelnes Zeichen: Zeichen ueberspringen:
		if(str[readPos + 1] == 0 || str[readPos + 1] != str[readPos]) {
			str[writePos++] = str[readPos++]; // Zeichen von Leseposition zu Schreibposition kopieren
			continue;
		}

		// Kette aus mindestens 2 gleichen Zeichen gefunden.
		uint32_t len = 2;
		for(; str[readPos + len] && str[readPos + len] == str[readPos]; len++); // Laenge der kette gleicher Zeichen berechnen

		// Zeichen kopieren
		str[writePos++] = str[readPos]; // erstes Zeichen der kette gleicher Zeichen kopieren
		readPos += len; // bis zu nächstem Zeichen nach Kette bzw. Null-Terminator des Textes springen

		// Anzahl der gleichen Zeichen (=Lauflaenge) speichern:
		const uint16_t NUM_DIGITS_LEN = numDigits(len); // Anzahl der zu schreibenden Lauflaengen-Ziffern
		for(uint16_t lenIndex = 0; lenIndex < NUM_DIGITS_LEN; lenIndex++)
			str[writePos++] = '0' + decDigit(len, NUM_DIGITS_LEN - 1 - lenIndex); // Ziffern der Lauflaenge speichern
	}
	str[writePos] = 0; // Ende der Zeichenkette markieren
}

// Aufgabe 3)
void RLDecode(char *const str) { // ueberschreibt originaltext. Voraussetzung: str muss genug speicherplatz fuer den gesamten dekomprimierten Text inklusive 0-terminator haben
	uint32_t numAdditionalChars = 0; // Quantitaet des Laengenzuwachses durch die Dekomprimierung (muss >= 0 sein)
	for(uint32_t i = 0; str[i]; i++) {
		if(str[i] < '0' || str[i] > '9') continue; // Buchstaben und Sonderzeichen ueberspringen

		uint32_t num = 0; // Wert der gefundenen Dezimalzahl
		uint8_t numDigits = 0; // Anzahl der der dezimalziffern der gefundenen Zahl
		for(; str[i] >= '0' && str[i] <= '9'; i++) { // Mehrere aufeinander folgende Ziffern aus kontinuierliche Zahl interpretieren
			(num *= 10) += str[i] - '0'; // Zahl um eine Dezimalstelle nach links verschieben und neue Ziffer anheangen
			numDigits++;
		}

		// Das zeichen vor der zahl nimmt bereits einen Platz ein. Ausserdem kann jede Ziffer durch genau ein Zeichen ersetzt werden:
		numAdditionalChars += num - 1 - numDigits;
	}

	str[strlen(str) + numAdditionalChars] = 0; // Ende der Zeichenkette markieren (muss entweder auf oder hinter bisherigem Nullterminator liegen)

	int32_t readPos = strlen(str)-1; // Am ende des aktuellen textes anfangen zu lesen
	int32_t writePos = strlen(str)-1 + numAdditionalChars; // Am ende es dekomprimierten Textes anfangen zu schreiben

	while(readPos >= 0) { // ende Bis inklusive anfang des Textes; Hinten anfangen da dekomprimierter Text sonst 
		if(str[readPos] < '0' || str[readPos] > '9') { // Wenn string keine Ziffer: Zeichen ueberspringen
			str[writePos--] = str[readPos--]; // Zeichen von Leseposition zu Schreibposition kopieren
			continue;
		}

		// jeweils neue Ziffer extrahieren -> mit Wertigkeit multiplizieren -> auf num addieren -> Wertigkeit fuer naechste Ziffer verzehnfachen:
		uint32_t num = 0; // Anzahl der Wiederholungen des Zeichens
		for(uint32_t digitVal = 1; str[readPos] >= '0' && str[readPos] <= '9'; num += (str[readPos--] - '0') * digitVal, digitVal *= 10);

		const char targetChar = str[readPos--]; // Zu wiederholendes Zeichen
		for(; num; num--)
			str[writePos--] = targetChar; // Zeichen Wiederholen
	}
}

// Aufgabe 2)
int bit_an_stelle(int zahl, int stelle) { // stelle als signierten integer zu uebergeben ist kontraproduktiv; ein uint8_t z.B. wuerde klar vermitteln dass negative Zahlen unerwuenscht sind
	return (zahl >> stelle) & 0x1; // Gewuenschtes Bit an unsignifikanteste Stelle schieben und mit &1 alle anderen Bits loeschen. Alternative: return (zahl & (0x1 << stelle)) != 0; ist UB wenn stelle > sizeof(int)
}

int main() {
	printf("Bits von 25:\n");
	for(uint8_t i = 0; i < 8; i++)
		printf("%d", bit_an_stelle(25, 7-i));
	printf("\n\n");

	char str[200];
	printf("Gib eine Zeichenkette ein: ");
	scanf("%[^\n]", str); // Schlechte Idee weil Bufferoverflow aber ok...
	printf("Die Zeichenkette lautet: %s\n", str);
	RLEncode(str);
	printf("Die komprimierte Zeichenkette lautet: %s\n", str);
	RLDecode(str);
	printf("Die dekomprimierte Zeichenkette lautet: %s\n", str);
}