//=============================================================================
// Dateiname: sudoku.c
// Ger�st:
//   Autor: Robert Heß
//   Version: 1.2
//   Datum: 23.05.2020
// Ausgestaltung:
//   Autor:		Viktor Terestschuk, Philipp Riefer
//   Version:	1.0
//   Datum:		27.05.2020
// Beschreibung: Einfache Windows-Applikation zum spielen von Sudoku, gesteuert mit der Maus
//=============================================================================

//git commit test from raspberry pi

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>	// Headerdatei f�r Fensteranwendugen
#include <stdio.h>
#include "sudoku.h"

// Definition Struktur
typedef struct {
	int Zahlenwert;
	int Zahlgef;
	int Zahlvorgabe;
	int einsGeraten : 1;
	int zweiGeraten : 1;
	int dreiGeraten : 1;
	int vierGeraten : 1;
	int fuenfGeraten : 1;
	int sechsGeraten : 1;
	int siebenGeraten : 1;
	int achtGeraten : 1;
	int neunGeraten : 1;
	int Versuchswert;
	int Loesungswert;
	int blacklist[10];
} tDaten;

// Funktion Vector
void intVector(tDaten Felder[9][9]);

int Sudoku(tSudokuTask task, int r, int c, int e, char *text, HWND hWnd)
// Diese Funktion wird von der Fensteranwendung an verschiedenen
// Stellen aufgerufen. Im ersten Parameter 'task' steht dabei die
// Aufgabe, die von der Funktion erledigt werden soll. Die anderen
// f�nf Parameter haben die folgenden Bedeutungen:
//				| r			| c			| e			| text		| hWnd
// getNumber	| Zeile		| Spalte	| 0			|			|
// getGuess		| Zeile		| Spalte	| Element	|			|
// getFinished	| Zeile		| Spalte	| 0			|			|
// getProtected	| Zeile		| Spalte	| 0			|			|
// singleClick	| Zeile		| Spalte	| Element	|			|
// doubleClick	| Zeile		| Spalte	| Element	|			|
// loadFile		| 0			| 0			|			| Dateiname	| Handle
// saveFile		| 0			| 0			|			| Dateiname	| Handle
// special1		| 0			| 0			|			|			| Handle
// special2		| 0			| 0			|			|			| Handle
// special3		| 0			| 0			|			|			| Handle
// Spalte:	Spalte im Sudoku (0-8)
// Zeile:	Zeile im Sudoku (0-8)
// Element:	Element innerhalb eines Feldes im Sudoku (0-8)
// Dateiname: Zeiger auf Zeichenkette
// Handle:	Handle des Fensters
{
	static tDaten Felder[9][9] = { 0 };		// Definiert mit static zur dauerhaften Speicherung da die Funktion zwischendurch verlassen wird
	static int firstCall=1;					// Markierung f�r den ersten Aufruf
	int returnValue=0;						// R�ckgabewert der Funktion
	FILE* out = NULL;
	FILE* inp = NULL;
	char FileName[] = "";
	int fehlerAnzahl = 0;

	if(firstCall) {
		intVector(Felder); // Daten initialisiert
		firstCall = 0;
	}

	switch(task) {

	//works
	case getNumber:		// gefundene Ziffer
		returnValue = Felder[r][c].Zahlenwert;//Return welche Zahl gefunden wurde vom User
		break;

	//works
	case getFinished:	// wurde Ziffer schon gefunden?
		returnValue = Felder[r][c].Zahlgef;//Return ob Feld schon gefunden wurde (eingetragen vom User)
		break;

	//works
	case getProtected:	// ist die Ziffer ein Vorgabewert?
		returnValue = Felder[r][c].Zahlvorgabe;//Return ob Feld ein Vorgabewert ist (true / false)
		break;

	//works
	case getGuess:		// geratene Ziffer
		if (e == 0) returnValue = Felder[r][c].einsGeraten;//Wenn erstes Feld abgefragt wird, Wert von einsGeraten (true / false) zur�ckgeben
		else if (e == 1) returnValue = Felder[r][c].zweiGeraten;
		else if (e == 2) returnValue = Felder[r][c].dreiGeraten;
		else if (e == 3) returnValue = Felder[r][c].vierGeraten;
		else if (e == 4) returnValue = Felder[r][c].fuenfGeraten;
		else if (e == 5) returnValue = Felder[r][c].sechsGeraten;
		else if (e == 6) returnValue = Felder[r][c].siebenGeraten;
		else if (e == 7) returnValue = Felder[r][c].achtGeraten;
		else if (e == 8) returnValue = Felder[r][c].neunGeraten;
		else returnValue = 0;
		break;

	//works
	case singleClick:	// einfacher Mausklick
		if (!Felder[r][c].Zahlvorgabe) {//Falls das Feld keine Vorgabe war
			//welches Feld angeklickt wurde (h�tte man auch mit switch cases machen k�nnen, aber keine lust das nochmal zu �ndern)
			if (e == 0) {//Falls erstes Feld angeklickt wurde
				if (Felder[r][c].einsGeraten) {//Falls das Feld schon geraten wurde
					Felder[r][c].einsGeraten = 0;//Entraten (abw�hlen (siehe Trump))
				}
				else Felder[r][c].einsGeraten = 1;//Falls Feld noch nicht angew�hlt wurde, anw�hlen
			}
			if (e == 1) {
				if (Felder[r][c].zweiGeraten) {
					Felder[r][c].zweiGeraten = 0;
				}
				else Felder[r][c].zweiGeraten = 1;
			}
			if (e == 2) {
				if (Felder[r][c].dreiGeraten) {
					Felder[r][c].dreiGeraten = 0;
				}
				else Felder[r][c].dreiGeraten = 1;
			}
			if (e == 3) {
				if (Felder[r][c].vierGeraten) {
					Felder[r][c].vierGeraten = 0;
				}
				else Felder[r][c].vierGeraten = 1;
			}
			if (e == 4) {
				if (Felder[r][c].fuenfGeraten) {
					Felder[r][c].fuenfGeraten = 0;
				}
				else Felder[r][c].fuenfGeraten = 1;
			}
			if (e == 5) {
				if (Felder[r][c].sechsGeraten) {
					Felder[r][c].sechsGeraten = 0;
				}
				else Felder[r][c].sechsGeraten = 1;
			}
			if (e == 6) {
				if (Felder[r][c].siebenGeraten) {
					Felder[r][c].siebenGeraten = 0;
				}
				else Felder[r][c].siebenGeraten = 1;
			}
			if (e == 7) {
				if (Felder[r][c].achtGeraten) {
					Felder[r][c].achtGeraten = 0;
				}
				else Felder[r][c].achtGeraten = 1;
			}
			if (e == 8) {
				if (Felder[r][c].neunGeraten) {
					Felder[r][c].neunGeraten = 0;
				}
				else Felder[r][c].neunGeraten = 1;
			}
		}
		break;

	//works
	case doubleClick:	// doppelter Mausklick
		if (!Felder[r][c].Zahlvorgabe) {//Falls Feld keine Vorgabe ist
			if (Felder[r][c].Zahlgef) {//Falls Zahl gefunden wurde
				Felder[r][c].Zahlgef = 0;//Zahl gefunden = false (0)
			}
			else {//Falls Zahl nicht gefunden wurde
				Felder[r][c].Zahlgef = 1;//Zahl gefunden = true (1)
				Felder[r][c].Zahlenwert = e + 1;//Zahlenwert auf das angeklickte Feld setzen. +1 weil if(arrays start at 1) trump = goodPresident;
			}
		}
		break;

	//works
	case loadFile://Sudoku aus Datei laden
		inp = fopen((const char*)text, "rb");//inp Datei wird ge�ffnet als Lesen, Bin�r

		// Spielfeld leeren
		for (int i = 0; i < 9; i++) {//Reihe
			for (int j = 0; j < 9; j++) {//Spalte

				Felder[i][j].Zahlenwert = 0;//Leeres Feld (0 -> leeres Feld)
				Felder[i][j].Zahlvorgabe = 0;//Zahl ist keine Vorgabe
				Felder[i][j].Zahlgef = 0;//Zahl nicht gefunden
				//Keine Zahl wurde geraten (false, 0)
				Felder[i][j].einsGeraten = 0;
				Felder[i][j].zweiGeraten = 0;
				Felder[i][j].dreiGeraten = 0;
				Felder[i][j].vierGeraten = 0;
				Felder[i][j].fuenfGeraten = 0;
				Felder[i][j].sechsGeraten = 0;
				Felder[i][j].siebenGeraten = 0;
				Felder[i][j].achtGeraten = 0;
				Felder[i][j].neunGeraten = 0;
			}
		}

		// Spielfeld mit den Werten aus der eingelesenen Datei f�llen
		for (int i = 0; i < 9; i++) {//Reihe
			for (int j = 0; j < 9; j++) {//Spalte
				fscanf(inp, "%1d", &Felder[i][j].Zahlenwert);// Zahlenwert in das jeweilige Feld schreiben
				//Steht in dem Feld eine Zahl wird diese Fett und schreibgesch�tzt eingetragen
				if (Felder[i][j].Zahlenwert) {//Falls der Zahlenwert true ist (!= 0) (Falls das Feld eine Zahl hat)
					Felder[i][j].Zahlvorgabe = 1;//Zahl ist vorgegeben
					Felder[i][j].Zahlgef = 1;//Zahl ist gefunden
				}
			}
		}
		break;

	//works, but doesnt allow the user to change user-put numbers after saving and reopening. after reopening all numbers are protected.
	case saveFile:		// Sudoku in Datei speichern
		out = fopen((const char*)text, "wt");//Datei �ffnen, in welche geschrieben werden soll
		if(out==NULL) {//Falls Datei out nicht ge�ffnet werden konnte
			printf("Konnte Ausgabedatei nicht \224ffnen: %s\n", (const char*)text);//Error message mit Dateinamen
			return -1;//Return Fehlercode
		}

		for(i=0; i<9; i++) {
			for(j=0; j<9; j++) {
				fprintf(out, "%d", Felder[i][j].Zahlenwert);//Zahlenwerte nacheinander in das Dokument schreiben
			}
			fprintf(out, "\n" );//Zeilenumbruch nach 9 Zahlen, weil Sudoku ist 9x9
		}
		if(out) fclose(out);//Falls Dokument "out" offen ist, erfolgt das Schlie�en des Dokumentes

		break;

	//check button?
	case special1:		// Reaktion auf Spezialtaste 1

		
		/*******************************************
		going to use a brute force solver (recursive, backtracking) until i get hold of a better algorithm
		*******************************************/

		int tx = 0;
		int ty = 0;
		int falscheZahl = 0;
		int error = 0;
		int x = 0;
		int y = 0;
		int rightbacktrackmove = 0;
		int numberfound = 0;

		while (x < 9)
		{
			y = 0;
			while (y < 9)
			{
				if (Felder[x][y].Zahlvorgabe) Felder[x][y].Loesungswert = Felder[x][y].Zahlenwert;
				else {
					//clear blacklist here???
					int i = 0;
					while(!numberfound)
					{
						Felder[x][y].Versuchswert = i + 1;
						if (Felder[x][y].blacklist[Felder[x][y].Versuchswert]) falscheZahl = 1;//falls die zahl schon geblacklisted wurde
						if (!falscheZahl) {
							//check row
							for (tx = 0; tx < 9; tx++) if (Felder[x][y].Versuchswert == Felder[tx][y].Loesungswert) falscheZahl = 1;
							//check column
							for (ty = 0; ty < 9; ty++) if (Felder[x][y].Versuchswert == Felder[x][ty].Loesungswert) falscheZahl = 1;

							//check square
							if (x < 3) tx = 0;
							else if (x < 6) tx = 3;
							else tx = 6;

							if (y < 3) ty = 0;
							else if (y < 6) ty = 3;
							else ty = 6;

							for (int n = tx; n < (tx + 3); n++)
							{
								for (int m = ty; m < (ty + 3); m++)
								{
									if (Felder[x][y].Versuchswert == Felder[tx][ty].Loesungswert) falscheZahl = 1;
								}
							}
						}

						if (!falscheZahl) {
							Felder[x][y].Loesungswert = Felder[x][y].Versuchswert;
						}
						else if (falscheZahl && i == 8) {//backtrack
							rightbacktrackmove = 0;
							while (!rightbacktrackmove) {
								if (!y) {
									y = 8;
									if (x) x -= 1;
									else error = 1;
								}
								else
								{
									y -= 1;
								}
								if (!Felder[x][y].Zahlvorgabe) {//richtiger backtrack move, also nicht auf protected feld
									rightbacktrackmove = 1;
									Felder[x][y].blacklist[Felder[x][y].Loesungswert] = 1; //zahl die in dem vorherigen feld war wird geblacklisted, damit diese nicht nochmal drankommen kann
								}
							}
						}
						if (i < 8) i++;
						else i = 0;
					}
				}
				y++;
			}
			x++;
		}

		if (error) MessageBox(hWnd, "Sudoku nicht lösbar", "Error", MB_OK);
		break;

	//autofill/refresh all suggestions?
	case special2:		// Reaktion auf Spezialtaste 2
		MessageBox(hWnd, "Autofill Suggestions (idiot mode)", "Info", MB_OK);
		break;

	//refresh user input suggestions?
	case special3:		// Reaktion auf Spezialtaste 3
		MessageBox(hWnd, "Refresh Suggestions", "Info", MB_OK);
		break;
	}

	return returnValue;
}

//Vektor, welcher die Felder[9][9] initialisiert, also das Sudoku initialisiert. Nicht nur die Zahlenwerte sondern auch die Wertigkeit der Zahlen (Vorgegeben / vom User geraten)
void intVector(tDaten Felder[9][9]) {

	int i;
	int j;

	//Sudoku wird initialisiert mit den Werten des Sudokus aus der Aufgabenstellung
	Felder[0][0].Zahlenwert = 0;
	Felder[0][1].Zahlenwert = 2;
	Felder[0][2].Zahlenwert = 6;
	Felder[0][3].Zahlenwert = 0;
	Felder[0][4].Zahlenwert = 0; 
	Felder[0][5].Zahlenwert = 0;
	Felder[0][6].Zahlenwert = 8;
	Felder[0][7].Zahlenwert = 1;
	Felder[0][8].Zahlenwert = 0;

	Felder[1][0].Zahlenwert = 3;
	Felder[1][1].Zahlenwert = 0;
	Felder[1][2].Zahlenwert = 0;
	Felder[1][3].Zahlenwert = 7;
	Felder[1][4].Zahlenwert = 0;
	Felder[1][5].Zahlenwert = 8;
	Felder[1][6].Zahlenwert = 0;
	Felder[1][7].Zahlenwert = 0;
	Felder[1][8].Zahlenwert = 6;

	Felder[2][0].Zahlenwert = 4;
	Felder[2][1].Zahlenwert = 0;
	Felder[2][2].Zahlenwert = 0;
	Felder[2][3].Zahlenwert = 0;
	Felder[2][4].Zahlenwert = 5;
	Felder[2][5].Zahlenwert = 0;
	Felder[2][6].Zahlenwert = 0;
	Felder[2][7].Zahlenwert = 0;
	Felder[2][8].Zahlenwert = 7;

	Felder[3][0].Zahlenwert = 0;
	Felder[3][1].Zahlenwert = 5;
	Felder[3][2].Zahlenwert = 0;
	Felder[3][3].Zahlenwert = 1;
	Felder[3][4].Zahlenwert = 0;
	Felder[3][5].Zahlenwert = 7;
	Felder[3][6].Zahlenwert = 0;
	Felder[3][7].Zahlenwert = 9;
	Felder[3][8].Zahlenwert = 0;

	Felder[4][0].Zahlenwert = 0;
	Felder[4][1].Zahlenwert = 0;
	Felder[4][2].Zahlenwert = 3;
	Felder[4][3].Zahlenwert = 9;
	Felder[4][4].Zahlenwert = 0;
	Felder[4][5].Zahlenwert = 5;
	Felder[4][6].Zahlenwert = 1;
	Felder[4][7].Zahlenwert = 0;
	Felder[4][8].Zahlenwert = 0;

	Felder[5][0].Zahlenwert = 0;
	Felder[5][1].Zahlenwert = 4;
	Felder[5][2].Zahlenwert = 0;
	Felder[5][3].Zahlenwert = 3;
	Felder[5][4].Zahlenwert = 0;
	Felder[5][5].Zahlenwert = 2;
	Felder[5][6].Zahlenwert = 0;
	Felder[5][7].Zahlenwert = 5;
	Felder[5][8].Zahlenwert = 0;

	Felder[6][0].Zahlenwert = 1;
	Felder[6][1].Zahlenwert = 0;
	Felder[6][2].Zahlenwert = 0;
	Felder[6][3].Zahlenwert = 0;
	Felder[6][4].Zahlenwert = 3;
	Felder[6][5].Zahlenwert = 0;
	Felder[6][6].Zahlenwert = 0;
	Felder[6][7].Zahlenwert = 0;
	Felder[6][8].Zahlenwert = 2;

	Felder[7][0].Zahlenwert = 5;
	Felder[7][1].Zahlenwert = 0;
	Felder[7][2].Zahlenwert = 0;
	Felder[7][3].Zahlenwert = 2;
	Felder[7][4].Zahlenwert = 0;
	Felder[7][5].Zahlenwert = 4;
	Felder[7][6].Zahlenwert = 0;
	Felder[7][7].Zahlenwert = 0;
	Felder[7][8].Zahlenwert = 9;

	Felder[8][0].Zahlenwert = 0;
	Felder[8][1].Zahlenwert = 3;
	Felder[8][2].Zahlenwert = 8;
	Felder[8][3].Zahlenwert = 0;
	Felder[8][4].Zahlenwert = 0;
	Felder[8][5].Zahlenwert = 0;
	Felder[8][6].Zahlenwert = 4;
	Felder[8][7].Zahlenwert = 6;
	Felder[8][8].Zahlenwert = 0;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {//Alle Felder auf vom User geraten = false (0) setzen, bei allen Zahlen
			Felder[i][j].einsGeraten = 0;
			Felder[i][j].zweiGeraten = 0;
			Felder[i][j].dreiGeraten = 0;
			Felder[i][j].vierGeraten = 0;
			Felder[i][j].fuenfGeraten = 0;
			Felder[i][j].sechsGeraten = 0;
			Felder[i][j].siebenGeraten = 0;
			Felder[i][j].achtGeraten = 0;
			Felder[i][j].neunGeraten = 0;
			Felder[i][j].Zahlgef = 0;

			//Falls das Feld schon eine Zahl drin hat die true ist (gr��er als 0)
			if (Felder[i][j].Zahlenwert) {
				//Es ist eine Vorgabe = true (1)
				Felder[i][j].Zahlvorgabe = 1;
				//Die Zahl wurde gefunden = true (1)
				Felder[i][j].Zahlgef = 1;
			}
			else Felder[i][j].Zahlvorgabe = 0;//ansonsten ist es keine vorgabe (false, 0)
		}
	}
}