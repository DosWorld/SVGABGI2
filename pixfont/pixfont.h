/******************************************************************************/
/*                                                                            */
/*                                  PixFont                                   */
/*                                                                            */
/*                                                                            */
/*  (C) 1993 by Ullrich von Bassewitz                                         */
/*              Zwehrenb�hlstra�e 33                                          */
/*              7400 T�bingen                                                 */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*  Erlaubt die Ausgabe von Text-Strings mit beliebigen Pixelfonts. Die       */
/*  verwendeten Pixel-Fonts m�ssen folgenderma�en aufgebaut sein:             */
/*                                                                            */
/*  Ein Zeichen besteht aus XSize Spalten und YSize Zeilen.                   */
/*  Die Daten f�r die Pixel werden so angeordnet                              */
/*                                                                            */
/*    1. Zeichen:                                                             */
/*      1. Zeile                                                              */
/*      2. Zeile                                                              */
/*      3. Zeile                                                              */
/*      ...                                                                   */
/*                                                                            */
/*    2. Zeichen                                                              */
/*      1. Zeile                                                              */
/*      2. Zeile                                                              */
/*      3. Zeile                                                              */
/*      ...                                                                   */
/*                                                                            */
/*    ...                                                                     */
/*                                                                            */
/*  Die Daten einer Zeile werden jeweils auf volle Bytes aufgerundet, so da�  */
/*  ein 8 Pixel breiter Font ein Byte pro Zeile, ein 9 Pixel breiter 2 Bytes  */
/*  pro Zeile besitzt etc.                                                    */
/*  Das oberste Bit (Bit 7) eines Bytes wird links ausgegeben, jedes folgende */
/*  Bit eine Position weiter rechts.                                          */
/*  Die erste Zeile wird zuoberst ausgegeben, jede folgende darunter.         */
/*                                                                            */
/*  Alle Routinen haben Namen die mit PixFont beginnen.                       */
/*                                                                            */
/*  �nderungen:                                                               */
/*                                                                            */
/*  04.05.93    Uz      Pascal-Version nach C �bersetzt.                      */
/*                                                                            */
/*  06.05.93    Uz      Namen ge�ndert.                                       */
/*                                                                            */
/******************************************************************************/


#ifndef __PIXFONT_H
#define __PIXFONT_H



/* Struktur eines Font-Records */
typedef struct _pixfont {
    void *          FontPtr;    /* Zeiger auf den Font */
    unsigned int    FontXSize;  /* Gr��e des Fonts in X und Y (Pixel) */
    unsigned int    FontYSize;
    unsigned char   FontXMult;  /* Verg��erung in X und Y */
    unsigned char   FontYMult;
    unsigned int    FontColor;  /* Farbe */
    unsigned char   FontHoriz;  /* Ausrichtung des Textes */
    unsigned char   FontVert;
    unsigned int    FontDir;    /* Schreibrichtung */
    unsigned int    FontMem;    /* Gr��e des belegten Speichers */

} PixFont;


/* Handle eines Fonts ist ein Zeiger auf die Kontrolldaten */
typedef PixFont *HFONT;


/********************************* Routinen ***********************************/


/******************************************************************************/
/*                                                                            */
/* PixFontInit:                                                               */
/*                                                                            */
/* Erzeugt einen neues Kontroll-Objekt f�r einen Font und liefert einen       */
/* Zeiger (das Handle) darauf zur�ck. FontData ist der Zeiger auf die         */
/* Font-Daten und kann auch NULL sein, wenn sp�ter ein Font geladen werden    */
/* soll. XSize und YSize sind die Grundgr��e des Fonts in Pixeln. Bei Fehlern */
/* kommt anstelle des Handles ein NULL-Zeiger zur�ck.                         */
/* Als Default wird die Vergr��erung 1 und die aktuelle Zeichenfarbe als      */
/* Fontfarbe gew�hlt.                                                         */
/*                                                                            */
/******************************************************************************/

HFONT PixFontInit (void *FontData, unsigned XSize, unsigned YSize);



/******************************************************************************/
/*                                                                            */
/* PixFontDone:                                                               */
/*                                                                            */
/* L�scht einen Font und gibt evtl. belegten Speicher wieder frei. Das Handle */
/* ist danach ung�ltig und darf nicht mehr verwendet werden.                  */
/*                                                                            */
/******************************************************************************/

void PixFontDone (HFONT Font);



/******************************************************************************/
/*                                                                            */
/* PixFontLoad:                                                               */
/*                                                                            */
/* L�dt die Fontdaten aus einer Datei. Falls zuvor bereits Speicher f�r       */
/* andere Fontdaten belegt war wird dieser zuvor freigegeben. Der R�ckgabe-   */
/* code ist 0 wenn der Font erfolgreich geladen werden konnte, ansonsten      */
/* kommt ein Wert != 0 zur�ck (errno wenn gr��er 0, -1 bei allgemeinen        */
/* Fehlern).                                                                  */
/*                                                                            */
/******************************************************************************/

int PixFontLoad (HFONT Font, char *Name, unsigned XSize, unsigned YSize);



/******************************************************************************/
/*                                                                            */
/* PixFontSetFont:                                                            */
/*                                                                            */
/* Setzt die Fontdaten neu. Falls zuvor bereits Speicher f�r andere Fontdaten */
/* belegt war wird dieser zuvor freigegeben. XSize und YSize sind die         */
/* Grundgr��e des Fonts in Pixeln.                                            */
/*                                                                            */
/******************************************************************************/

void PixFontSetFont (HFONT Font, void *FontData, unsigned XSize, unsigned YSize);



/******************************************************************************/
/*                                                                            */
/* PixFontSetScale:                                                           */
/*                                                                            */
/* Setzt die Vergr��erung f�r einen Font. XMult ist die Skalierung in X-,     */
/* YMult die Vergr��erung in Y-Richtung.                                      */
/*                                                                            */
/******************************************************************************/

void PixFontSetScale (HFONT Font, unsigned char XMult, unsigned char YMult);



/******************************************************************************/
/*                                                                            */
/* PixFontSetDirection:                                                       */
/*                                                                            */
/* Setzt die Ausgaberichtung f�r den Font. Zul�ssige Werte sind HORIZ_DIR     */
/* (horizontale Ausgabe) und VERT_DIR (vertikale Ausgabe).                    */
/*                                                                            */
/******************************************************************************/

void PixFontSetDirection (HFONT Font, unsigned Dir);



/******************************************************************************/
/*                                                                            */
/* PixFontSetColor:                                                           */
/*                                                                            */
/* Setzt die Farbe f�r die Textausgabe. Der farbwert wird auf die maximal     */
/* unterst�tzte Farbe des Adapters begrenzt.                                  */
/*                                                                            */
/******************************************************************************/

void PixFontSetColor (HFONT Font, unsigned Color);



/******************************************************************************/
/*                                                                            */
/* PixFontSetJustify:                                                         */
/*                                                                            */
/* Legt die Ausrichtung des Fonts bei der Ausgabe fest. Die Parameter         */
/* entsprechen denen der Funktion settextjustify.                             */
/*                                                                            */
/******************************************************************************/

void PixFontSetJustify (HFONT Font, unsigned Horiz, unsigned Vert);



/******************************************************************************/
/*                                                                            */
/* PixFontWriteXY:                                                            */
/*                                                                            */
/* Gibt einen Text an den �bergebenen Koordinaten aus. Ein eventuell          */
/* gesetztes Fenster wird ber�cksichtigt. Die Ausgabe erfolgt mit den zuvor   */
/* vorgenommenen Einstellungen f�r Farbe, Vergr��erung und Ausrichtung.       */
/*                                                                            */
/******************************************************************************/

void PixFontWriteXY (HFONT Font, int X, int Y, char *S);



/******************************************************************************/
/*                                                                            */
/* Get8x14FontPtr:                                                            */
/*                                                                            */
/* Gibt einen Zeiger auf den 8x14-Font einer VGA zur�ck. ACHTUNG: Der Aufruf  */
/* hat nur dann Erfolg wenn eine VGA im System ist. Dies wird aber von der    */
/* Routine nicht explizit �berpr�ft. Ist dies nicht der Fall, so ist der      */
/* zur�ckgegebene Zeiger ung�ltig.                                            */
/*                                                                            */
/******************************************************************************/

void * Get8x14FontPtr (void);



/******************************************************************************/
/*                                                                            */
/* Get8x16FontPtr:                                                            */
/*                                                                            */
/* Gibt einen Zeiger auf den 8x16-Font einer VGA zur�ck. ACHTUNG: Der Aufruf  */
/* hat nur dann Erfolg wenn eine VGA im System ist. Dies wird aber von der    */
/* Routine nicht explizit �berpr�ft. Ist dies nicht der Fall, so ist der      */
/* zur�ckgegebene Zeiger ung�ltig.                                            */
/*                                                                            */
/******************************************************************************/

void * Get8x16FontPtr (void);



/* Ende von PIXFONT.H */
#endif






