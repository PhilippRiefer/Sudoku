//=============================================================================
// Dateiname: sudoku.h
// Gerüst:
//   Autor: Robert Heß
//   Version: 1.2
//   Datum: 23.05.2020
// Ausgestaltung:
//   Autor:		Viktor Terestschuk, Philipp Riefer
//   Version:	1.0
//   Datum:		27.05.2020
// Beschreibung: Einfache Windows-Applikation zum spielen von Sudoku, gesteuert mit der Maus
//=============================================================================

// Die beiden folgenden und die letzte Zeile verhindern,
// dass die Definitionen mehrfach erfolgen
#ifndef FUNCTION_SUDOKU_BY_STUDENT_XXX_INCLUDED
#define FUNCTION_SUDOKU_BY_STUDENT_XXX_INCLUDED

// Die folgenden vier Zeilen können Sie einzeln durch
// Kommentarzeichen aktivieren oder deaktivieren, um dem Programm
// nach Bedarf weitere Tasten hinzuzufügen. Drei der vier Tasten
// können mit individuellem Text versehen werden.


#define SAVE_BUTTON_INCLUDED //Save button wurde mit einprogrammiert


//#define SPECIAL_BUTTON_1_INCLUDED "Spezial 1"
//#define SPECIAL_BUTTON_2_INCLUDED "Spezial 2"
//#define SPECIAL_BUTTON_3_INCLUDED "Spezial 3"

// Diese Aufzählung listet alle Aufgaben auf, mit der die Funktion
// Sudoku aufgerufen werden kann.
typedef enum {
	getNumber,
	getGuess,
	getFinished,
	getProtected,
	singleClick, doubleClick,
	loadFile, saveFile,
	special1, special2, special3
} tSudokuTask;

// Die Funktion Sudoku muss auf alle Anfragen des Benutzers reagieren.
int Sudoku(tSudokuTask task, int r, int c, int e, char *text, HWND hWnd);
// Der erste Parameter gibt die zu erledigende Aufgabe an.
// Die Bedeutung der anderen fünf Parameter ist unterschiedlich:
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

#endif // #ifndef FUNCTION_SUDOKU_BY_STUDENT_XXX_INCLUDED
