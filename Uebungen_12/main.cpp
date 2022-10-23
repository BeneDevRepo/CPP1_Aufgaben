#include <cstdio>
#include <cstdlib>

#include <Windows.h>

#define HOEHE (30)
#define BREITE (30)

void ausgabe(bool spielfeld[HOEHE][BREITE]) {
	// printf("\033[H");
	printf("\x1B[?25l"); // Disable Cursor
	printf("\x1B[0;0H"); // Cursor pos <y=0; x=0>
	for (int y = 0; y < HOEHE; y++) {
		for (int x = 0; x < BREITE; x++) {
            if (spielfeld[y][x])
            // \u2688 ist der Unicode Code für einen schwarzen Block
            // Davon drucken wir 2 nebeneinander
                // printf("\u2588\u2588");
                printf("##");
            else
            // Oder 2 Leerzeichen
                printf("..");
        }
		printf("\n");
	}
	fflush(stdout);
}


void update(bool spielfeld[HOEHE][BREITE]) {

  /*
   * Beachten Sie, dass Sie das "alte" spielfeld nicht ändern dürfen,
   * solange Sie das neue Feld berechnen!
   * Es bietet sich an, ein "temporaeres" Spielfeld anzulegen
   * in dem Sie die Felder für die naechste Runde berechnen
   */


  // Durchlaufen Sie alle Zeilen des Spielfelds

    // Durchlaufen Sie alle Spalten des Spielfelds

      // Zählen Sie, wie viele Nachbarn das aktuelle Feld hat
      // Dazu benötigen Sie eine Zaehlvariable die anfangs auf 0 ist


      /* Nun müssen Sie die Felder um das Aktuelle Feld auswerten
       * Beachten Sie, dass Felder an den Raendern weniger als 8
       * Nachbarfelder haben.
       * Gehen Sie in diesem Fall davon aus, dass die Felder "tot"
       * also nicht besetzt sind
       */


      /* Wenn Sie alle "lebenden" Nachbarfelder gezaehlt haben pruefen
       * sie die folgenden Bedingungen:
       * 1: Wenn das Feld genau 3 lebende Nachbarfelder hat lebt es
       *    in der nächsten Runde
       * 2: Wenn das Feld 2 oder 3 lebende Nachbarfelder hat und selber
       *    lebt, dann lebt es auch in der nächsten Runde
       * Wenn Bedingung 1 und 2 nicht gelten, ist das Feld in der
       * naechsten Runde "tot"
       */


  /* Wenn Sie alle neuen Felder berechnet haben, aktualisieren Sie
   * das Spielfeld. Z.B. durch Kopieren der Werte aus dem temporären
   * in das "richtige" Spielfeld
   */
	bool neues[HOEHE][BREITE]{};

	for (int y = 0; y < HOEHE; y++) {
		for (int x = 0; x < BREITE; x++) {

			int nachbarn = 0;
			for(int oy = -1; oy <= 1; oy++) {
				for(int ox = -1; ox <= 1; ox++) {
					if(ox == 0 && oy == 0) // Zelle selbst nicht als Nachbarn zaehlen
						continue;

					const int ax = x + ox;
					const int ay = y + oy;

					if(ax < 0 || ax > BREITE-1) // Zellen ausserhalb des Spielfeldes ueberspringen
						continue;
					if(ay < 0 || ay > HOEHE-1) // Zellen ausserhalb des Spielfeldes ueberspringen
						continue;

					if(spielfeld[ay][ax])
						nachbarn++;
				}
			}

			if(nachbarn == 3) // Genau drei Nachbarn
				neues[y][x] = true;

			if(spielfeld[y][x] && (nachbarn==2 || nachbarn==3)) // Feld lebt selbst und hat 2 oder 3 lebende Nachbarn
				neues[y][x] = true;
		}
	}

	memcpy(spielfeld, neues, sizeof(bool) * BREITE * HOEHE);
}

int main()
{
    // srand(12); //LEBT!
    srand(0); //STIRBT

	bool spielfeld[HOEHE][BREITE]{};

	// for (int x = 1; x < BREITE-1; x++)
    //     for (int y = 1; y < HOEHE-1; y++)
    //         spielfeld[y][x] = rand() < (RAND_MAX / 10);

	// Gleiter
	spielfeld[5][5] = true;
	spielfeld[5][7] = true;
	spielfeld[6][6] = true;
	spielfeld[6][7] = true;
	spielfeld[7][6] = true;

	// Statisch
	spielfeld[5][6+7] = true;
	spielfeld[5][7+7] = true;
	spielfeld[6][5+7] = true;
	spielfeld[6][8+7] = true;
	spielfeld[7][6+7] = true;
	spielfeld[7][7+7] = true;

	// Blinker
	spielfeld[6][10+8] = true;
	spielfeld[6][10+9] = true;
	spielfeld[6][10+10] = true;

    for (;;) {
		ausgabe(spielfeld);
		update(spielfeld);
		Sleep(200);
	}
  return 0;
}