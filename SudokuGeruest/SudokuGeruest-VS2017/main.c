//=============================================================================
// Dateiname: main.c
// Autor: Robert Heß
// Version: 1.2
// Datum: 23.05.2020
// Beschreibung: Gerüst für ein Sudoku-Programm mit Windows-Benutzeroberfläche
//=============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>	// Headerdatei für Fensteranwendugen
#include "sudoku.h"

#define X_OFFSET 10		// linker Abstand zum Rand des Fensters
#define Y_OFFSET 10		// oberer Abstand zum Rand des Fensters
#define BOX_SIZE 49		// Größe eines Feldes; der Wert sollte sein: 3n+1
#define GAP_SIZE 7		// extra Abstand für 9er-Block

// IDs für die Knöpfe
#define LOAD_BUTTON_ID 1
#define SAVE_BUTTON_ID 2
#define SPECIAL_BUTTON1_ID 3
#define SPECIAL_BUTTON2_ID 4
#define SPECIAL_BUTTON3_ID 5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int getPosition(int *r, int *c, int *element, LPARAM lParam);
void drawWindow(HWND hWnd);
void drawGrid(HDC hdc, int xOff, int yOff, int boxSize, int gapSize);
void drawNumbers(HDC hdc, int xOff, int yOff, int boxSize, int gapSize);

// Hauptprogramm für eine Fensteranwendung
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Sudoku");	// Name der Applikation
	HWND         hWnd;			// Handle für Fenster
	MSG          msg;			// aktuelle Windows-Nachricht
	WNDCLASSEX   wndclassex;	// Beschreibung der Applikation
	int xPosButton = X_OFFSET;	// Zum Berechnen der Position der Tasten

	// Beschreibung der Applikation
	wndclassex.cbSize        = sizeof(WNDCLASSEX);
	wndclassex.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclassex.lpfnWndProc   = &WndProc;
	wndclassex.cbClsExtra    = 0;
	wndclassex.cbWndExtra    = 0;
	wndclassex.hInstance     = hInstance;
	wndclassex.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
	wndclassex.hCursor       = LoadCursor (NULL, IDC_ARROW);
	wndclassex.hbrBackground = CreateSolidBrush(RGB(224, 224, 224));
	wndclassex.lpszMenuName  = NULL;
	wndclassex.lpszClassName = szAppName;
	wndclassex.hIconSm       = wndclassex.hIcon;

	// Applikation beim Betriebssystem registrieren lassen
	if(!RegisterClassEx(&wndclassex))
	{
		MessageBox (NULL, TEXT ("RegisterClassEx fehlgeschlagen!"),
					szAppName, MB_OK | MB_ICONERROR);
		return -1;
	}

	// Ein Fenster für die Applikation erstellen
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,		// erweiterter Fensterstil
		szAppName,					// Name der Fensterklasse
		TEXT ("PRP II - Sudoku"),	// Fenstertitel (Kopfzeile)
		WS_OVERLAPPEDWINDOW,		// Fensterstil
		CW_USEDEFAULT,				// X-Position des Fensters
		CW_USEDEFAULT,				// Y-Position des Fensters
		2*X_OFFSET+9*BOX_SIZE+2*GAP_SIZE+13,	// Fensterbreite
		3*Y_OFFSET+9*BOX_SIZE+2*GAP_SIZE+38+30,	// Fensterhöhe
		NULL,						// übergeordnetes Fenster
		NULL,						// Menü
		hInstance,					// Handle der Applikation
		NULL);						// keine zusätzlichen Parameter

	// Knopf zum Laden eines Sudokus aus einer Datei
	CreateWindow( 
		"BUTTON",					// vordefinierte Fensterklasse 
	    "laden ...",				// Text auf Taste
	    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	// Tastenstil
		xPosButton,					// x-Position
	    2*Y_OFFSET+9*BOX_SIZE+2*GAP_SIZE,	// y-Position
	    70,							// Breite
	    25,							// Höhe
	    hWnd,						// parent window 
	    (HMENU)LOAD_BUTTON_ID,		// Kennung
	    hInstance,					// Handle der Applikation
	    NULL);						// keine zusätzlichen Parameter

	// Position der nächsten Taste berechnen
	xPosButton += 70+10;

#ifdef SAVE_BUTTON_INCLUDED
	// Knopf zum Speichern eines Sudokus in eine Datei
	CreateWindow( 
		"BUTTON",					// vordefinierte Fensterklasse 
	    "speichern ...",			// Text auf Taste
	    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	// Tastenstil
	    xPosButton,					// x-Position
	    2*Y_OFFSET+9*BOX_SIZE+2*GAP_SIZE,	// y-Position
	    90,						// button width 
	    25,							// Breite
	    hWnd,						// Höhe
	    (HMENU)SAVE_BUTTON_ID,		// Kennung
	    hInstance,					// Handle der Applikation
	    NULL);						// keine zusätzlichen Parameter

	// Position der nächsten Taste berechnen
	xPosButton += 90+10;
#endif

#ifdef SPECIAL_BUTTON_1_INCLUDED
	// Knopf zum Speichern eines Sudokus in eine Datei
	CreateWindow(
		"BUTTON",					// vordefinierte Fensterklasse 
	    SPECIAL_BUTTON_1_INCLUDED,	// Text auf Taste
	    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	// Tastenstil
	    xPosButton,					// x-Position
	    2*Y_OFFSET+9*BOX_SIZE+2*GAP_SIZE,	// y-Position
	    70,							// Breite
	    25,							// Höhe
	    hWnd,						// parent window
	    (HMENU)SPECIAL_BUTTON1_ID,	// Kennung
	    hInstance,					// Handle der Applikation
	    NULL);						// keine zusätzlichen Parameter

	// Position der nächsten Taste berechnen
	xPosButton += 70+10;
#endif

#ifdef SPECIAL_BUTTON_2_INCLUDED
	// Knopf zum Speichern eines Sudokus in eine Datei
	CreateWindow(
		"BUTTON",					// vordefinierte Fensterklasse 
	    SPECIAL_BUTTON_2_INCLUDED,	// Text auf Taste
	    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	// Tastenstil
	    xPosButton,					// x-Position
	    2*Y_OFFSET+9*BOX_SIZE+2*GAP_SIZE,	// y-Position
	    70,							// Breite
	    25,							// Höhe
	    hWnd,						// parent window
	    (HMENU)SPECIAL_BUTTON2_ID,	// Kennung
	    hInstance,					// Handle der Applikation
	    NULL);						// keine zusätzlichen Parameter

	// Position der nächsten Taste berechnen
	xPosButton += 70+10;
#endif

#ifdef SPECIAL_BUTTON_3_INCLUDED
	// Knopf zum Speichern eines Sudokus in eine Datei
	CreateWindow(
		"BUTTON",					// vordefinierte Fensterklasse 
	    SPECIAL_BUTTON_3_INCLUDED,	// Text auf Taste
	    WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,	// Tastenstil
	    xPosButton,					// x-Position
	    2*Y_OFFSET+9*BOX_SIZE+2*GAP_SIZE,	// y-Position
	    70,							// Breite
	    25,							// Höhe
	    hWnd,						// parent window
	    (HMENU)SPECIAL_BUTTON3_ID,	// Kennung
	    hInstance,					// Handle der Applikation
	    NULL);						// keine zusätzlichen Parameter

	// Position der nächsten Taste berechnen
	xPosButton += 70+10;
#endif

	// Fenster anzeigen und aktualisieren
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	// Nachrichtenschleife aktivieren
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	// Applikation wieder abmelden
	UnregisterClass(szAppName, hInstance);

	return (int)msg.wParam;
}

// Die Hauptnachrichtenschleife 
// Funktion zum Behandeln der Nachrichten vom Betriebssystem
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int x1, y1, n1;	// Position im Sudoku beim Drücken der Maus
	int x2, y2, n2;			// Position im Sudoku beim Loslassen der Maus
	RECT rect;				// Region, die neu gezeichnet werden soll
	char Filter[] =			// Dateifilter für Dialog
		"Sudoku-Datei (*.sdk)\0*.sdk\0" "Alle Dateien (*.*)\0*.*\0";
	char FileName[301]="";	// Dateiname
	char title[20];			// Titel für Dialog
	OPENFILENAME FileData = {	// Informationen Für Dateidialog:
	    sizeof(OPENFILENAME),// Größe dieser Struktur
	    hWnd,				// Eigentümer-Fenster dieses Dialogs
	    0,					// Zugehörige Applikation
	    Filter,				// Dateifilter
	    NULL,				// Letzter gewählter Dateityp
	    0,					// Läange des letzten gewähllen Dateityps
	    0,					// Index des gewählten Dateityps
	    FileName,			// Dateiname mit Pfad
	    300,				// maximale Länge des Dateinamens mit Pfad
	    NULL,				// Dateiname ohne Pfad
	    0,					// maximale Länge des Dateinamens ohne Pfad
	    NULL,				// Anfangsverzeichnis
	    title,				// Titel in Kopfzeile
	    OFN_FILEMUSTEXIST,	// Eigenschaften des Dialogs
	    0,					// Offset bis Dateiname
	    0,					// Offset bis Endung
	    "sdk",				// Standard-Endung
	    0,					// Daten für die 'Hook'-Prozedur
	    NULL,				// Zeiger auf 'Hook'-Prozedur
	    NULL				// Name des Templates
	}; 

	// Verzweigung auf die Nachrichten
	switch(message)
	{

	case WM_PAINT:		// Fenster zeichnen
		drawWindow(hWnd);
		return 0;

	case WM_CLOSE:		// X-Taste am Fenster
		if(MessageBox(hWnd, "Wollen Sie wirklich aufhören?", "Frage:", MB_YESNO)==IDYES)
			DestroyWindow(hWnd);
		else return 0;
		break;

	case WM_DESTROY:	// Beenden der Applikation
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:// linke Maustaste gedrückt
	   if(getPosition(&y1, &x1, &n1, lParam)) x1 = -1;
	   break;

	case WM_LBUTTONUP:	// linke Maustaste losgelassen
		if(getPosition(&y2, &x2, &n2, lParam)) x2 = -1;
		if(x1>=0 && x2>=0 && x1==x2 && y1==y2 && n1==n2) {
			Sudoku(singleClick, y1, x1, n1, NULL, hWnd);
			rect.left = X_OFFSET+x1*BOX_SIZE+x1/3*GAP_SIZE+3;
			rect.top = X_OFFSET+y1*BOX_SIZE+y1/3*GAP_SIZE+3;
			rect.right = rect.left+BOX_SIZE-6;
			rect.bottom = rect.top+BOX_SIZE-6;
			RedrawWindow(hWnd, &rect, NULL, RDW_ERASE|RDW_INVALIDATE);
		}
		break;
	case WM_LBUTTONDBLCLK:// linke Maustaste doppelklick
		if(!getPosition(&y1, &x1, &n1, lParam)){
			Sudoku(doubleClick, y1, x1, n1, NULL, hWnd);
			rect.left = X_OFFSET+x1*BOX_SIZE+x1/3*GAP_SIZE+3;
			rect.top = X_OFFSET+y1*BOX_SIZE+y1/3*GAP_SIZE+3;
			rect.right = rect.left+BOX_SIZE-6;
			rect.bottom = rect.top+BOX_SIZE-6;
			RedrawWindow(hWnd, &rect, NULL, RDW_ERASE|RDW_INVALIDATE);
		}
		break;

	case WM_COMMAND:	// allgemeinder Befehl
		if(HIWORD(wParam)==BN_CLICKED) {

			// Verzweigung auf Art des Befehls
			switch(LOWORD(wParam)) {

			case LOAD_BUTTON_ID:	// die Taste 'Laden..' betätigt
				strcpy(title, "Sudoku laden");
				if(GetOpenFileName(&FileData)) {
					Sudoku(loadFile, 0, 0, 0, FileData.lpstrFile, hWnd);
					RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
				}
				break;

			case SAVE_BUTTON_ID:	// die Taste 'Speichern...' betätigt
				strcpy(title, "Sudoku speichern");
				if(GetSaveFileName(&FileData)) {
					Sudoku(saveFile, 0, 0, 0, FileData.lpstrFile, hWnd);
				}
				break;

			case SPECIAL_BUTTON1_ID:// Spezialtaste 1 betätigt
				Sudoku(special1, 0, 0, 0, NULL, hWnd);
				RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
				break;

			case SPECIAL_BUTTON2_ID:// Spezialtaste 2 betätigt
				Sudoku(special2, 0, 0, 0, NULL, hWnd);
				RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
				break;

			case SPECIAL_BUTTON3_ID:// Spezialtaste 3 betätigt
				Sudoku(special3, 0, 0, 0, NULL, hWnd);
				RedrawWindow(hWnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE);
				break;
			}
		}
		break;
	}

	// Standard-Behandlung der Nachricht aufrufen
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Position im Sudoku ermitteln
int getPosition(int *r, int *c, int *element, LPARAM lParam)
{
	int xpos=LOWORD(lParam);	// x-Position der Maus
	int ypos=HIWORD(lParam);	// y-Position der Maus
	int found;					// Position gefunden

	// Finde c-Position im Feld
	found = 0;
	*c = 0;
	while(!found && *c<9) {
		found = xpos>X_OFFSET+*c*BOX_SIZE+*c/3*GAP_SIZE+2
			&& xpos<X_OFFSET+(*c+1)*BOX_SIZE+*c/3*GAP_SIZE-2;
		if(!found) (*c)++;
	}
	if(!found) return -1;

	// Finde r-Position im Feld
	found = 0;
	*r = 0;
	while(!found && *r<9) {
		found = ypos>Y_OFFSET+*r*BOX_SIZE+*r/3*GAP_SIZE+2
			&& ypos<Y_OFFSET+(*r+1)*BOX_SIZE+*r/3*GAP_SIZE-2;
		if(!found) (*r)++;
	}
	if(!found) return -1;

	// Finde Element im Feld
	xpos -= X_OFFSET+*c*BOX_SIZE+*c/3*GAP_SIZE+2;
	ypos -= Y_OFFSET+*r*BOX_SIZE+*r/3*GAP_SIZE+2;
	*element = 0;
	found = 0;
	while(!found && *element<3) {
		found = xpos>*element*(BOX_SIZE-4)/3;
		found = found && xpos<(*element+1)*(BOX_SIZE-4)/3;
		if(!found) (*element)++;
	}
	if(*element>=3) return -1;
	found = 0;
	while(!found && *element<9) {
		found = ypos>*element/3*(BOX_SIZE-4)/3;
		found = found && ypos<(*element/3+1)*(BOX_SIZE-4)/3;
		if(!found) *element += 3;
	}
	if(*element>=9) return -1;

	// Position gefunden
	return 0;
}

// Fensterinhalt zeichnen
void drawWindow(HWND hWnd)
{
	HDC hdc;		// Handle für Zeichenumgebung
	PAINTSTRUCT ps;	// Informationen zum Zeichnen

	// Zeichnen beginnen
	hdc = BeginPaint(hWnd, &ps);

	// Inhalt zeichnen
	drawGrid(hdc, X_OFFSET, Y_OFFSET, BOX_SIZE, GAP_SIZE);
	drawNumbers(hdc, X_OFFSET, Y_OFFSET, BOX_SIZE, GAP_SIZE);

	// Zeichnen beenden
	EndPaint(hWnd, &ps);
}

// Gitter für Sudoku zeichnen
void drawGrid(HDC hdc, int xOff, int yOff, int boxSize, int gapSize)
{
	POINT oldPos;	// vorherige Cursor-Position
	int i, ix, iy;	// lokale Laufvariablen
	HPEN hGrey[5];	// fünf Grautöne
	HPEN hOldPen;	// verheriger Stift

	// Stifte vorbereiten
	for(i=0; i<5; i++)
		hGrey[i] = CreatePen(PS_SOLID, 1, RGB(224+15*(i-2), 224+15*(i-2), 224+15*(i-2)));
	hOldPen = SelectObject(hdc, hGrey[0]);
	MoveToEx(hdc, 0, 0, &oldPos);

	// äußeren Rand zeichnen
	for(i=1; i<=2; i++) {
		// helle Seite
		SelectObject(hdc, hGrey[2+i]);
		MoveToEx(hdc, xOff-i, yOff+9*boxSize+2*gapSize+i, NULL);
		LineTo(hdc, xOff-i, yOff-i);
		LineTo(hdc, xOff+9*boxSize+2*gapSize+i+1, yOff-i);
		// dunkle Seite
		SelectObject(hdc, hGrey[2-i]);
		MoveToEx(hdc, xOff-i+1, yOff+9*boxSize+2*gapSize+i, NULL);
		LineTo(hdc, xOff+9*boxSize+2*gapSize+i, yOff+9*boxSize+2*gapSize+i);
		LineTo(hdc, xOff+9*boxSize+2*gapSize+i, yOff-i);
	}

	// inneren Rand zeichnen
	for(i=2; i>=1; i--) {
		// hellen Rand zeichnen
		SelectObject(hdc, hGrey[2+i]);
		for(ix=0; ix<9; ix++) {
			for(iy=0; iy<9; iy++) {
				MoveToEx(hdc, xOff+(ix+1)*boxSize-i+ix/3*gapSize, yOff+iy*boxSize+i+iy/3*gapSize, NULL);
				LineTo(hdc, xOff+(ix+1)*boxSize-i+ix/3*gapSize, yOff+(iy+1)*boxSize-i+iy/3*gapSize);
				LineTo(hdc, xOff+ix*boxSize+i-1+ix/3*gapSize, yOff+(iy+1)*boxSize-i+iy/3*gapSize);
			}
		}
		// dunklen Rand zeichnen
		SelectObject(hdc, hGrey[2-i]);
		for(ix=0; ix<9; ix++) {
			for(iy=0; iy<9; iy++) {
				MoveToEx(hdc, xOff+(ix+1)*boxSize-i-1+ix/3*gapSize, yOff+iy*boxSize+i+iy/3*gapSize, NULL);
				LineTo(hdc, xOff+ix*boxSize+i+ix/3*gapSize, yOff+iy*boxSize+i+iy/3*gapSize);
				LineTo(hdc, xOff+ix*boxSize+i+ix/3*gapSize, yOff+(iy+1)*boxSize-i+iy/3*gapSize);
			}
		}
	}

	// Linien innerhalb der Box zeichnen
	SelectObject(hdc, hGrey[1]);
	for(ix=0; ix<9; ix++) {
		for(iy=0; iy<9; iy++) {
			if(!Sudoku(getFinished, iy, ix, 0, NULL, 0)) {
				// horizontale Linien
				MoveToEx(hdc, xOff+ix*boxSize+ix/3*gapSize+3, yOff+iy*boxSize+iy/3*gapSize+(boxSize+3)/3, NULL);
				LineTo(hdc,   xOff+(ix+1)*boxSize+ix/3*gapSize-2, yOff+iy*boxSize+iy/3*gapSize+(boxSize+3)/3);
				MoveToEx(hdc, xOff+ix*boxSize+ix/3*gapSize+3, yOff+iy*boxSize+iy/3*gapSize+2*boxSize/3, NULL);
				LineTo(hdc,   xOff+(ix+1)*boxSize+ix/3*gapSize-2, yOff+iy*boxSize+iy/3*gapSize+2*boxSize/3);
				// vertikale Linien
				MoveToEx(hdc, xOff+ix*boxSize+ix/3*gapSize+(boxSize+3)/3, yOff+iy*boxSize+iy/3*gapSize+3, NULL);
				LineTo(hdc,   xOff+ix*boxSize+ix/3*gapSize+(boxSize+3)/3, yOff+(iy+1)*boxSize+iy/3*gapSize-2);
				MoveToEx(hdc, xOff+ix*boxSize+ix/3*gapSize+2*boxSize/3, yOff+iy*boxSize+iy/3*gapSize+3, NULL);
				LineTo(hdc,   xOff+ix*boxSize+ix/3*gapSize+2*boxSize/3, yOff+(iy+1)*boxSize+iy/3*gapSize-2);
			}
		}
	}

	// Aufräumen
	SelectObject(hdc, hOldPen);
	MoveToEx(hdc, oldPos.x, oldPos.y, NULL);
}

// Nummern des Sudokus schreiben
void drawNumbers(HDC hdc, int xOff, int yOff, int boxSize, int gapSize)
{
	int ix, iy, i;		// lokale Laufvariablen
	char Text[2];		// aktuelle Nummer
	RECT rect;			// Feld, in das die Nummer geschrieben werden soll
	int oldBkMode;		// alter Hintergrund-Modus
	HFONT bigThickFont;	// große fette Schrift
	HFONT bigThinFont;	// große dünne Schrift
	HFONT smallFont;	// kleine Schrift
	HFONT oldFont;		// vorherige Schrift

	// Texteinstellungen
	oldBkMode = SetBkMode(hdc, TRANSPARENT);
	bigThickFont = CreateFont(boxSize, 0, 0, 0, 800, FALSE, FALSE,
		FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_SWISS, "Arial");
	bigThinFont = CreateFont(boxSize, 0, 0, 0, 200, FALSE, FALSE,
		FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_SWISS, "Arial");
	smallFont = CreateFont(boxSize/3, 0, 0, 0, 500, FALSE, FALSE,
		FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_SWISS, "Arial");
	oldFont = SelectObject(hdc, smallFont);
	Text[1] = '\0';

	// große Zahlen schreiben
	for(ix=0; ix<9; ix++) {
		for(iy=0; iy<9; iy++) {
			if(Sudoku(getFinished, iy, ix, 0, NULL, 0)) {
				if(Sudoku(getProtected, iy, ix, 0, NULL, 0)) SelectObject(hdc, bigThickFont);
				else SelectObject(hdc, bigThinFont);
				Text[0] = '0'+Sudoku(getNumber, iy, ix, 0, NULL, 0);
				rect.left = xOff+ix*boxSize+ix/3*gapSize+3;
				rect.top = yOff+iy*boxSize+iy/3*gapSize+3;
				rect.right = xOff+(ix+1)*boxSize+ix/3*gapSize-2;
				rect.bottom = yOff+(iy+1)*boxSize+iy/3*gapSize-2;
				DrawText(hdc, Text, (int)strlen(Text), &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}
		}
	}

	// kleine Zahlen schreiben
	SelectObject(hdc, smallFont);
	for(ix=0; ix<9; ix++) {
		for(iy=0; iy<9; iy++) {
			if(!Sudoku(getFinished, iy, ix, 0, NULL, 0)) {
				for(i=0; i<9; i++) {
					if(Sudoku(getGuess, iy, ix, i, NULL, 0)) {
						rect.left = xOff+ix/3*gapSize+ix*boxSize+i%3*(boxSize-3)/3+4;
						rect.top = yOff+iy*boxSize+iy/3*gapSize+i/3*(boxSize-3)/3+3;
						rect.right = rect.left+(boxSize-8)/3;
						rect.bottom = rect.top+(boxSize-8)/3;
						Text[0] = '0'+i+1;
						DrawText(hdc, Text, (int)strlen(Text), &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
					}
				}
			}
		}
	}

	// Aufräumen
	SetBkMode(hdc, oldBkMode);
	SelectObject(hdc, oldFont);
	DeleteObject(bigThickFont);
}
