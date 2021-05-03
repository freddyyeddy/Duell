// Demo.cpp = Duell.cpp     erstellt 22.01.2005                Roland Studer
//                          geändert 04.11.2006 für V.S. 2005  Roland Studer
//                          geändert 21.01.2010 für V.S. 2005  Roland Studer
// Renamed to Duell.cpp              31.12.2011                Matthias Kläy
// # include "StdAfx.h"  // neu am 04.11 2006    -> 21.01.2010 ist nun nicht
//   mehr nötig, wenn C/C++ -> Advanced -> Disable Specific Warnings -> 4996
// geändert am 23.01.2010

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <windows.h>
# include "ddraw.h"
# include "ddutil.h"
# include "DSound.h"
# include "DSUtil.h"
# include "resource.h"

const int duell_nettobreite = 640;  // Breite des Inneren des Haupfensters
const int duell_nettohoehe  = 400;  // Hoehe des Inneren des Hauptfensters
int duell_bruttobreite;             // Breite des gesamten Haupfensters (incl. Rahmen)
int duell_bruttohoehe;              // Hoehe des gesamten Haupfensters (incl. Rahmen)
struct FieldCommon
	{
	int FIELD[10][9];				// Das Duell-Spielfeld
	int FIGW[10][9];				// Eigenschaftstabelle für weisse Würfel
	int FIGR[10][9];				// Eigenschaftstabelle für schwarze Würfel
	int KINGW[10];					// Eigenschaftstabelle für weissen Königs-Würfel
	int KINGR[10];					// Eigenschaftstabelle für schwarzen Königs-Würfel
	int IBW, IBR, IPW, IPR, IRW, IRR; // Bewertungs-Werte
	int FIGTW, FIGTR, KNGTW, KNGTR; // Kosten-Werte der Figuren
	int COSTW, COSTR, COSTO, COSTN; // Total-Kosten
	};
FieldCommon W0, S0, W1, H1, S1, W2, H2, S2, W3, H3, S3, S4, S5;
bool XFIRST;
char ILINE[10];
char GraphicText0[25];
char GraphicText1[25];
char GraphicText2[25];
char GraphicText3[25];
char GraphicText4[25];
char GraphicText5[25];
char GraphicText6[25];
char GraphicText7[30];
char GraphicText8[25];
char GraphicText9[25];
char BLANK[25]="                       \0";
char DATBUF[10];
int IHILFW[7], IHILFR[7];
int CO[19];							// Kosten-Faktoren
int PFL=0, WTHR1, WTHR2;			// Schwellen für Bewertung
char INP, INN, ILOOK;
bool W1FLAG, W2FLAG, W3FLAG, W4FLAG, CHFLAG;
int IS;								// Vorzeichen-Steuerung
int Flags=31;	
HCURSOR hold_cursor;
char Path_Buffer[256];
char Dummy;
long int color, hold_color;
int spc, hold_spc;
bool TextFlag;
FILE *pfRR;
bool registered=FALSE;
char infoText1[40]="Sharewareversion-V1.8\0";
char infoText2[40]="nicht registrierte Version von DUELL\0";
char infoText3[24]="ohne Serienummer\0";
// aus EVENT
unsigned int MoX, MoY, fwKeys;
unsigned int M2X=420, M2Y=0;
int M1Flags=0, M2Flags=0;
char str[61];
bool JumpPM, JumpCM;
bool Done=FALSE;
bool DoneOK=FALSE;
bool Exit=FALSE;
bool InpOK=FALSE;
bool StartOK=FALSE;
int PMLabel, CMLabel;
unsigned int MOVENO;
char Space[25]="<Space> -> Weiter      \0";
char SpaceNewGame[25]="<Space> -> New Game    \0";
char ESC[25]="<ESC> -> Abbruch oder  \0";
char DMW[25]="DUELL-MATT für Weiss   \0";
char DMB[25]="DUELL-MATT für Schwarz \0";
char WCM[25]="Ohne Züge vom Computer \0";
char WPM[25]="Ohne Züge von Personen \0";
char PZG[25]="Personen-Zug           \0";
char IllMove[25]="Nicht erlaubter Zug !! \0";
char TSTD[16]="Test, ob DUELL\0";
char BCH;
char IRAND;
bool FileOpen=FALSE;;
bool allowed=FALSE;
bool back, spec;
int xtmp, ytmp, Hxtmp, Hytmp;
int CT, CM, CH, CV;
int HilF;
int OldField, NewField;
int HILO, HILN, ICLINE, HCOST, IRET;
int HIRET;
bool HXFIRST, MARK=FALSE;
int u1, Mark_on=1;
int IDXA, IDYA, ITOT;
bool ERR, ENDLP, HXF;
// aus INTPRL
int HXI, HYI, XKI, YKI, DXI, DYI, IVAL, IDIST;
int IXO, IYO, IXN, IYN, IQ, IERR;
// aus Move
int HXM, HYM, WXM, WYM;
int ITX, ITY, ILX, ILY, IKX, IKY;
int HILFFL, IZW, IZR, NRACT, NRBEAT;
int NRACT_hold, NRBEAT_hold, hold_wert;
bool FSXY, FSYX, IPWFL, IPRFL, ISWFL, ISRFL, IDWFL, IDRFL;
int IVALN, ISXY, ISYX;
bool ENDLP_M, JUMP_M;
// aus RDAIDA
int HXD, HYD, XKD, YKD;
bool ENDLP_D;
// aus REMINS
int HXE, HYE, XKE, YKE;
// aus COST
int HXS, HYS, IXH, IYH;
int I13W, I14W, I15W, I13R, I14R, I15R;
int IDISTW, IDISTR;
int IPKTOT, IHIL;
int KX[5], KY[5], IPKNG[5];
// aus CONRET (Variant 0 und 1 und 2)
int HXC, HYC, FXC, FYC, VXC, VYC, WXC, WYC;
int ITWC, ITRC, HRC, ILIMC, ICC, IVC;
bool NoCutC;
int IVALC;
// aus CONRET (Variant 3)
int HXR, HYR, FXR, FYR, VXR, VYR, WXR, WYR;
int ITWR, ITRR, HRR, ILIMR, ICR, IVR;
bool NoCutR;
int IVALR;
// aus TRY
int HXT, HYT, FXT, FYT, VXT, VYT, WXT, WYT, DXT, DYT;
int ITWT, ITRT, HRT;
bool ENDLP_T;
int ICTOT, ILIMT;
int IVALT;
int ICT, IVT;
// aus WTHR1Change
int HILFFG, XHG, YHG, HXG, HYG;
int ZWG, ZRG, PKTOTG, PKOWNG;
int GX[5], GY[5], GPKNG[5], GPKNGO[5];
int IDISTG, IVALG;
// aus GameProtocol
FILE *pfPW;
FILE *pfPR;
char TEXT[33];
char Prot[33]="Protokoll_vom_DUELL___________ \0";
char Line[33]="______________________________ \0";
char Zurk[33]="_Zug-Rücknahme________________ \0";
char Pchg[33]="_Parameter-Wechsel_ab_hier____ \0";
char Osch[33]="_ohne_Schwellen_______________ \0";
char hold_filename[256];
// aus INPSTR
bool K_Flag=FALSE, EndInp=FALSE;
int JCount;
char H_GraphicText[25]="                       \0";
// aus SHOW
FILE *pfHW;
bool FileOpenGameShowfile=FALSE;
char Tch[4];
char ShowEnd[23]="Ende des Schrittes\0";
char ShowTitle[35]="Zuschauen, wie der Computer denkt\0";
char ShowLine[35]="---------------------------------\0";
bool V0_done=FALSE;

HINSTANCE duell_instance;			// Instanz der Duell Applikation
HWND duell_window;					// Das Hauptfenster von Duell
HMENU duell_menu;					// Das Menu von Duell
HDC duell_dc;						// Geräte-Kontext

const int sound_start		= 0;	// Sound fuer neues Spiel
const int sound_compmove	= 1;	// Sound Ende Computer-Zug
const int sound_fold		= 2;	// Sound beim Klappen der Würfel
const int sound_persmove	= 3;	// Sound Ende Personen-Zug
const int sound_win			= 4;	// Sound für gewonnenes Spiel
const int sound_duell		= 5;	// Sound für Ankündigung von Duell
const int anzahl_sounds		= 6;	// Anzahl Sounds

char *soundfiles[anzahl_sounds] = 
	{ 
		"du_start.wav",
		"du_compmove.wav",
		"du_fold.wav",
		"du_persmove.wav",
		"du_win.wav",
		"du_duell.wav"
	};

class sounds
	{
	private:
		CSoundManager smgr;
		CSound *snd[anzahl_sounds];
	public:
		int on;
		sounds();
		int init( HWND wnd);
		void play( int snr);
		~sounds();
	};
sounds::sounds() 
	{
		int i;
		for( i = 0; i < anzahl_sounds; i++)
			snd[i] = 0;
		on = 1;
	}
int sounds::init( HWND wnd)
	{
		HRESULT ret;
		int i;
		ret = smgr.Initialize( wnd, DSSCL_PRIORITY, 2, 22050, 16);
		if( ret < 0)
			return ret;
		for( i = 0; i < anzahl_sounds; i++)
		{
			ret = smgr.Create( snd+i, soundfiles[i]);
			if( ret < 0)
				return ret;
		}
		return S_OK;
	}
sounds::~sounds()
	{
		int i;
		for( i = 0; i < anzahl_sounds; i++)
		{
			if( snd[i])
				delete snd[i];
		}
	}
void sounds::play( int i)
	{
		if( !on)
			return;
		if( snd[i]->IsSoundPlaying())
		{
			snd[i]->Stop();
			snd[i]->Reset();
		}
		snd[i]->Play(0,0);
	}

sounds duell_sounds;

class display
	{
	private:
		CDisplay dsply; 
		CSurface *hgrnd;
		CSurface *whitefield;
		CSurface *blackfield;
		CSurface *markfield;
		CSurface *warnfield;
		CSurface *whitekingfield;
		CSurface *blackkingfield;
		CSurface *whitecube[25];
		CSurface *blackcube[25];
	public:
		display();
		void free_all();
		~display() {free_all();}
		HRESULT init( HWND wnd);
        void hintergrund() { dsply.Blt( 0, 0, hgrnd);}
		void weissstein( int z, int s, int val) { dsply.Blt( 24+s*44, 24+z*44, whitecube[val]);}
		void schwarzstein( int z, int s, int val) { dsply.Blt( 24+s*44, 24+z*44, blackcube[val]);}
		void weissfeld( int z, int s) { dsply.Blt( 24+s*44, 24+z*44, whitefield);}
		void schwarzfeld( int z, int s) { dsply.Blt( 24+s*44, 24+z*44, blackfield);}
		void markfeld( int z, int s) { dsply.Blt( 24+s*44, 24+z*44, markfield);}
		void warnfeld( int z, int s) { dsply.Blt( 24+s*44, 24+z*44, warnfield);}
		void WKfeld() { dsply.Blt( 24+4*44, 24+7*44, whitekingfield);}
		void BKfeld() { dsply.Blt( 24+4*44, 24+0*44, blackkingfield);}
		void update(){ dsply.UpdateBounds();}
		HRESULT cooperative(){return dsply.GetDirectDraw()->TestCooperativeLevel();}
		HRESULT restore();
		HRESULT present();
	};
display::display()
	{
		int i;
		hgrnd = 0;
		whitefield = 0;
		blackfield = 0;
		markfield = 0;
		warnfield = 0;
		whitekingfield = 0;
		blackkingfield = 0;
		for( i = 0; i < 25; i++)
			whitecube[i] = 0;
		for( i = 0; i < 25; i++)
			blackcube[i] = 0;
	}
void display::free_all()
	{
		int i;
		if( hgrnd)
			delete hgrnd;
		if( whitefield)
			delete whitefield;
		if( blackfield)
			delete blackfield;
		if( markfield)
			delete markfield;
		if( warnfield)
			delete warnfield;
		if( whitekingfield)
			delete whitekingfield;
		if( blackkingfield)
			delete blackkingfield;
		for( i = 0; i < 25; i++)
		{
			if( whitecube[i])
				delete whitecube[i];
		}
		for( i = 0; i < 25; i++)
		{
			if( blackcube[i])
				delete blackcube[i];
		}	
	}
HRESULT display::init( HWND wnd)
	{
		HRESULT hr;
		int i;
		char fname[20];
		hr = dsply.CreateWindowedDisplay( wnd, duell_nettobreite, duell_nettohoehe );
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &hgrnd, "du_hgrnd.bmp", duell_nettobreite, duell_nettohoehe);
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &whitefield, "du_WF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &blackfield, "du_BF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &markfield, "du_MarkF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &warnfield, "du_WarnF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &whitekingfield, "du_WKF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = dsply.CreateSurfaceFromBitmap( &blackkingfield, "du_BKF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		for( i = 0; i < 25; i++)
		{
			sprintf( fname, "du_WC_%d.bmp", i);
			hr = dsply.CreateSurfaceFromBitmap( &whitecube[i], fname, 45, 45);
			if( hr < 0)
				return hr;
		}
		for( i = 0; i < 25; i++)
		{
			sprintf( fname, "du_BC_%d.bmp", i);
			hr = dsply.CreateSurfaceFromBitmap( &blackcube[i], fname, 45, 45);
			if( hr < 0)
				return hr;
		}
		return S_OK;
	}
HRESULT display::restore()
	{
		HRESULT hr;
		int i;
		char fname[20];
		hr = dsply.GetDirectDraw()->RestoreAllSurfaces();
		if( hr < 0)
			return hr;
		hr = hgrnd->DrawBitmap( "du_hgrnd.bmp", duell_nettobreite, duell_nettohoehe);
		if( hr < 0)
			return hr;
		hr = whitefield->DrawBitmap( "du_WF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = blackfield->DrawBitmap( "du_BF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = markfield->DrawBitmap( "du_MarkF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = warnfield->DrawBitmap( "du_WarnF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = whitekingfield->DrawBitmap( "du_WKF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		hr = blackkingfield->DrawBitmap( "du_BKF.bmp", 45, 45);
		if( hr < 0)
			return hr;
		for( i = 0; i < 25; i++)
		{
			sprintf( fname, "du_WC_%d.bmp", i);
			hr = whitecube[i]->DrawBitmap( fname, 45, 45);
			if( hr < 0)
				return hr;
		}
		for( i = 0; i < 25; i++)
		{
			sprintf( fname, "du_BC_%d.bmp", i);
			hr = blackcube[i]->DrawBitmap( fname, 45, 45);
			if( hr < 0)
				return hr;
		}
		MessageBox( duell_window, "Surfaces restauriert", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		present();				
		return S_OK;
	}
HRESULT display::present()
	{
		HRESULT hr;
		hr = dsply.Present();
		if( hr == DDERR_SURFACELOST )
			return restore();
		return hr; 
	}

display duell_display;

class GameSituation
	{
	private:
		char filename[256];
	public:
		GameSituation(){}
		void WriteGameSituation();
		void ReadGameSituation();
	};
void GameSituation::WriteGameSituation()
	{
		FILE *pfS;
		int I, J;
		OPENFILENAME ofnS = 
		{
			sizeof(OPENFILENAME),
			duell_window,
			NULL,
			"Duell-dls-Dateien (.dls)\0*.dls\0\0",
			NULL,
			0,
			1,
			filename, 256,
			NULL, 0,
			NULL,
			"Spielfeld speichern",
			0, 0, 1, "dls\0", 0, NULL, NULL
		};
		if (GetSaveFileName(&ofnS))
		{
			pfS = fopen( filename, "w");
			fprintf(pfS, "%d ", IRET);
			fprintf(pfS, "%d ", MOVENO);
			fprintf(pfS, "%d\n\n", IS);
			for (J = 8; J >= 1; J--)
			{
				for (I = 1; I <= 9; I++)
				{
					fprintf(pfS, "%d ", W0.FIELD[I][J]);
				}
				fprintf(pfS, "\n");
			}
			fprintf(pfS, "\n");
			for (J = 1; J <= 8; J++)
			{
				for (I = 1; I <= 9; I++)
				{
					fprintf(pfS, "%d ", W0.FIGW[I][J]);
				}
				fprintf(pfS, "\n");
			}
			fprintf(pfS, "\n");
			for (J = 1; J <= 8; J++)
			{
				for (I = 1; I <= 9; I++)
				{
					fprintf(pfS, "%d ", W0.FIGR[I][J]);
				}
				fprintf(pfS, "\n");
			}
			fprintf(pfS, "\n");
			for (I = 1; I <= 9; I++)
			{
				fprintf(pfS, "%d ", W0.KINGW[I]);
			}
			fprintf(pfS, "\n");
			for (I = 1; I <= 9; I++)
			{
				fprintf(pfS, "%d ", W0.KINGR[I]);
			}
			fprintf(pfS, "\n\n");
			fprintf(pfS, "%d ", W0.IBW);
			fprintf(pfS, "%d ", W0.IBR);
			fprintf(pfS, "%d ", W0.IPW);
			fprintf(pfS, "%d ", W0.IPR);
			fprintf(pfS, "%d ", W0.IRW);
			fprintf(pfS, "%d\n\n", W0.IRR);
			fprintf(pfS, "%d ", W0.FIGTW);
			fprintf(pfS, "%d ", W0.FIGTR);
			fprintf(pfS, "%d ", W0.KNGTW);
			fprintf(pfS, "%d\n\n", W0.KNGTR);
			fprintf(pfS, "%d ", W0.COSTW);
			fprintf(pfS, "%d ", W0.COSTR);
			fprintf(pfS, "%d ", W0.COSTO);
			fprintf(pfS, "%d\n\n", W0.COSTN);
			for (I = 1; I <= 18; I++)
			{
				fprintf(pfS, "%d ", CO[I]);
			}
			fprintf(pfS, "\n\n");
			fprintf(pfS, "%d ", W1FLAG);
			fprintf(pfS, "%d ", W2FLAG);
			fprintf(pfS, "%d ", W3FLAG);
			fprintf(pfS, "%d\n\n", W4FLAG);
			fprintf(pfS, "%d ", WTHR1);
			fprintf(pfS, "%d ", WTHR2);
			fprintf(pfS, "%d\n\n", PFL);
			fprintf(pfS, "%c ", INP);
			fprintf(pfS, "%c ", INN);
			fprintf(pfS, "%c\n", ILOOK);
			fclose(pfS);
		}
	}
void GameSituation::ReadGameSituation()
	{
		FILE *pfS;
		int I, J;
		OPENFILENAME ofnS = 
		{
			sizeof(OPENFILENAME),
			duell_window,
			NULL,
			"Duell-dls-Dateien (.dls)\0*.dls\0\0",
			NULL,
			0,
			1,
			filename, 256,
			NULL, 0,
			NULL,
			"Spielfeld laden",
			OFN_FILEMUSTEXIST, 0, 1, NULL, 0, NULL, NULL
		};
		if (GetOpenFileName(&ofnS))
		{
			pfS = fopen( filename, "r");
			fscanf(pfS, "%d", &IRET);
			fscanf(pfS, "%d", &MOVENO);
			fscanf(pfS, "%d", &IS);
			for (J = 8; J >= 1; J--)
			{
				for (I = 1; I <= 9; I++)
				{
					fscanf(pfS, "%d", &W0.FIELD[I][J]);
				}
			}
			for (J = 1; J <= 8; J++)
			{
				for (I = 1; I <= 9; I++)
				{
					fscanf(pfS, "%d", &W0.FIGW[I][J]);
				}
			}
			for (J = 1; J <= 8; J++)
			{
				for (I = 1; I <= 9; I++)
				{
					fscanf(pfS, "%d", &W0.FIGR[I][J]);
				}
			}
			for (I = 1; I <= 9; I++)
			{
				fscanf(pfS, "%d", &W0.KINGW[I]);
			}
			for (I = 1; I <= 9; I++)
			{
				fscanf(pfS, "%d", &W0.KINGR[I]);
			}
			fscanf(pfS, "%d", &W0.IBW);
			fscanf(pfS, "%d", &W0.IBR);
			fscanf(pfS, "%d", &W0.IPW);
			fscanf(pfS, "%d", &W0.IPR);
			fscanf(pfS, "%d", &W0.IRW);
			fscanf(pfS, "%d", &W0.IRR);
			fscanf(pfS, "%d", &W0.FIGTW);
			fscanf(pfS, "%d", &W0.FIGTR);
			fscanf(pfS, "%d", &W0.KNGTW);
			fscanf(pfS, "%d", &W0.KNGTR);
			fscanf(pfS, "%d", &W0.COSTW);
			fscanf(pfS, "%d", &W0.COSTR);
			fscanf(pfS, "%d", &W0.COSTO);
			fscanf(pfS, "%d", &W0.COSTN);
			for (I = 1; I <= 18; I++)
			{
				fscanf(pfS, "%d", &CO[I]);
			}
			fscanf(pfS, "%d", &W1FLAG);
			fscanf(pfS, "%d", &W2FLAG);
			fscanf(pfS, "%d", &W3FLAG);
			fscanf(pfS, "%d", &W4FLAG);
			fscanf(pfS, "%d", &WTHR1);
			fscanf(pfS, "%d", &WTHR2);
			fscanf(pfS, "%d", &PFL);
			fscanf(pfS, "%c", &Dummy);
			fscanf(pfS, "%c", &Dummy);
			fscanf(pfS, "%c", &INP);
			fscanf(pfS, "%c", &Dummy);
			fscanf(pfS, "%c", &INN);
			fscanf(pfS, "%c", &Dummy);
			fscanf(pfS, "%c", &ILOOK);
			fscanf(pfS, "%c", &Dummy);
			fclose(pfS);
		}
	}

GameSituation mein_spielfeld;

class GameProtocol
	{
	private:
		char filename[256];
	public:
		GameProtocol(){}
		void WriteGameProtocol();
		void ReadGameProtocol();
		void WriteMove(char& PoC, char& WoB);
		void CloseProtocol();
		void UpdateProtocol();
		void WriteString(char* ss);
		void WriteLn();
	};
void GameProtocol::WriteGameProtocol()
	{
		struct tm *newtime;
		time_t aclock;
		char buf[28];
		if (!FileOpen)
		{	
			int I;
			OPENFILENAME ofnP = 
			{
				sizeof(OPENFILENAME),
				duell_window,
				NULL,
				"Duell-dlp-Dateien (.dlp)\0*.dlp\0\0",
				NULL,
				0,
				1,
				filename, 256,
				NULL, 0,
				NULL,
				"Protokoll speichern",
				0, 0, 1, "dlp\0", 0, NULL, NULL
			};
			if (GetSaveFileName(&ofnP))
			{
				strcpy(hold_filename, filename);
				pfPW = fopen( filename, "a");
				FileOpen = TRUE;
				CheckMenuItem( duell_menu, ID_WRITEPROT, MF_CHECKED);
				WriteString(Prot);
				// Datum protokollieren
				time( &aclock ); // Get time in seconds
				// Convert time to struct tm form
				newtime = localtime( &aclock );
                // Print local time as a string
				// printf( "The current date and time are: %s",
				// asctime( newtime ) );
				strcpy(buf, asctime( newtime ));
				TEXT[0] = buf[8];
				TEXT[1] = buf[9];
				TEXT[2] = '-';
				TEXT[3] = buf[4];
				TEXT[4] = buf[5];
				if (TEXT[4] == 'c')
					TEXT[4] = 'k';
				TEXT[5] = buf[6];
				if (TEXT[5] == 'y')
					TEXT[5] = 'i';
				else if (TEXT[5] == 'c')
					TEXT[5] = 'z';
				TEXT[6] = '-';
				TEXT[7] = buf[22];
				TEXT[8] = buf[23];
				TEXT[9] = '_';
				TEXT[10] = '_';
				TEXT[11] = '_';
				TEXT[12] = buf[11];
				TEXT[13] = buf[12];
				TEXT[14] = buf[13];
				TEXT[15] = buf[14];
				TEXT[16] = buf[15];
				for (I = 17; I <= 29; I++)
				{
					TEXT[I] = '_';
				}
				TEXT[30] = '\0';				
				WriteString(TEXT);
				WriteLn();
				WriteString(Line);
				WriteString(Line);
				WriteLn();
				if ((INP == 'N') || (IS == -1))
					WriteString(Line);
				// darf hier noch nicht geschlossen werden
				// fclose(pfPW);
			}
		}
		else
			MessageBox( duell_window, "Spiel-Protokoll ist bereits geöffnet", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}
void GameProtocol::ReadGameProtocol()
	{
		OPENFILENAME ofnP = 
		{
			sizeof(OPENFILENAME),
			duell_window,
			NULL,
			"Duell-dlp-Dateien (.dlp)\0*.dlp\0\0",
			NULL,
			0,
			1,
			filename, 256,
			NULL, 0,
			NULL,
			"Protokoll lesen",
			OFN_FILEMUSTEXIST, 0, 1, NULL, 0, NULL, NULL
		};
		if (GetOpenFileName(&ofnP))
		{
			if ((FileOpen) && (strcmp(hold_filename, filename) == 0))
				fclose(pfPW);
			pfPR = fopen( filename, "r");
			ShellExecute(NULL, "open", "NOTEPAD.EXE", ofnP.lpstrFile, NULL, SW_SHOWNORMAL);
			fclose(pfPR);
			if ((FileOpen) && (strcmp(hold_filename, filename) == 0))
				pfPW = fopen( hold_filename, "a");
		}
	}
void GameProtocol::WriteMove(char& PoC, char& WoB)
	{
		unsigned int H1, H2, H3, H;
		DATBUF[0] = PoC;
		DATBUF[1] = ':';
		DATBUF[2] = '_';
		DATBUF[3] = WoB;
		DATBUF[4] = ':';
		DATBUF[5] = '_';
		if ((PoC == 'C') && (WoB == 'W') && (INN != 'S'))
			MOVENO = MOVENO + 1;
		H1 = MOVENO / 1000;
		if (H1 == 0)
			DATBUF[6] = '_';
		else
			DATBUF[6] = (char)((unsigned int)(H1) + (unsigned int)('0'));
		H = MOVENO % 1000;
		H2 = H / 100;
		if ((H2 == 0) && (H1 == 0))
			DATBUF[7] = '_';
		else
			DATBUF[7] = (char)((unsigned int)(H2) + (unsigned int)('0'));
		H = H % 100;
		H3 = H / 10;
		if ((H3 == 0) && (H2 == 0) && (H1 == 0))
			DATBUF[8] = '_';
		else
			DATBUF[8] = (char)((unsigned int)(H3) + (unsigned int)('0'));
		DATBUF[9] = '\0';
		WriteString(DATBUF);
		H = H % 10;
		DATBUF[0] = (char)((unsigned int)(H) + (unsigned int)('0'));
		DATBUF[1] = '.';
		DATBUF[2] = '_';
		DATBUF[3] = 'Z';
		DATBUF[4] = 'u';
		DATBUF[5] = 'g';
		DATBUF[6] = ':';
		DATBUF[7] = '_';
		DATBUF[8] = '_';
		WriteString(DATBUF);
		DATBUF[0] = ILINE[0];
		DATBUF[1] = ILINE[1];
		DATBUF[2] = ILINE[2];
		DATBUF[3] = ILINE[3];
		DATBUF[4] = ILINE[4];
		if (ILINE[5] == ' ')
			DATBUF[5] = '_';
		else
			DATBUF[5] = ILINE[5];
		if (ILINE[6] == ' ')
			DATBUF[6] = '_';
		else
			DATBUF[6] = ILINE[6];
		DATBUF[7] = '_';
		DATBUF[8] = '_';
		WriteString(DATBUF);
		DATBUF[0] = '_';
		DATBUF[1] = '_';
		DATBUF[2] = '_';
		DATBUF[3] = ' ';
		DATBUF[4] = '\0';
		WriteString(DATBUF);
		if ((PoC == 'C') && (WoB == 'W') && (INN != 'S'))
			MOVENO = MOVENO - 1;
	}
void GameProtocol::CloseProtocol()
	{
		unsigned int i;
		if (abs(IRET) == 15)
			IS = -IS;
		if (IS == -1)
		{
			WriteString(Line);
			WriteLn();
		}
		strcpy(TEXT, "_Stufe:_\0");
		WriteString(TEXT);
		if (ILOOK == 'J')
			strcpy(TEXT, "_voraus_\0");
		else
			strcpy(TEXT, "_normal_\0");
		WriteString(TEXT);
		strcpy(TEXT, "_Zufall:\0");
		WriteString(TEXT);
		if (IRAND == 'J')
			strcpy(TEXT, "__ein_ \0");
		else
			strcpy(TEXT, "__aus_ \0");
		WriteString(TEXT);
		if (ILOOK == 'J')
		{
			strcpy(TEXT, "_Schwell\0");
			WriteString(TEXT);
			strcpy(TEXT, "en:_____\0");
			WriteString(TEXT);
			strcpy(TEXT, "_");
			itoa(WTHR1, DATBUF, 10);
			for (i=1; i<4+1-strlen(DATBUF); i++)
				strcat(TEXT, "_\0");
			strcat(TEXT, DATBUF);
			if (WTHR1 > 0)
				TEXT[4-strlen(DATBUF)] = '+';
			TEXT[5] = '_';
			TEXT[6] = '_';
			TEXT[7] = '_';
			TEXT[8] = '\0';
			WriteString(TEXT);
			strcpy(TEXT, "_");
			itoa(WTHR2, DATBUF, 10);
			for (i=1; i<4+1-strlen(DATBUF); i++)
				strcat(TEXT, "_\0");
			strcat(TEXT, DATBUF);
			if (WTHR2 > 0)
				TEXT[4-strlen(DATBUF)] = '+';
			TEXT[5] = '_';
			TEXT[6] = ' ';
			TEXT[7] = '\0';
			WriteString(TEXT);
		}
		else
			WriteString(Osch);
		WriteLn();    
		WriteString(Line);
		WriteString(Line);
		WriteLn();    
		fclose(pfPW);
		if (abs(IRET) == 15)
			IS = -IS;
		FileOpen = FALSE;
	}
void GameProtocol::UpdateProtocol()
	{
		unsigned int i;
		if (IS == -1)
		{
			WriteString(Line);
			WriteLn();
		}
		strcpy(TEXT, "_Stufe:_\0");
		WriteString(TEXT);
		if (ILOOK == 'J')
			strcpy(TEXT, "_voraus_\0");
		else
			strcpy(TEXT, "_normal_\0");
		WriteString(TEXT);
		strcpy(TEXT, "_Zufall:\0");
		WriteString(TEXT);
		if (IRAND == 'J')
			strcpy(TEXT, "__ein_ \0");
		else
			strcpy(TEXT, "__aus_ \0");
		WriteString(TEXT);
		if (ILOOK == 'J')
		{
			strcpy(TEXT, "_Schwell\0");
			WriteString(TEXT);
			strcpy(TEXT, "en:_____\0");
			WriteString(TEXT);
			strcpy(TEXT, "_");
			itoa(WTHR1, DATBUF, 10);
			for (i=1; i<4+1-strlen(DATBUF); i++)
				strcat(TEXT, "_\0");
				strcat(TEXT, DATBUF);
			if (WTHR1 > 0)
				TEXT[4-strlen(DATBUF)] = '+';
			TEXT[5] = '_';
			TEXT[6] = '_';
			TEXT[7] = '_';
			TEXT[8] = '\0';
			WriteString(TEXT);
			strcpy(TEXT, "_");
			itoa(WTHR2, DATBUF, 10);
			for (i=1; i<4+1-strlen(DATBUF); i++)
				strcat(TEXT, "_\0");
			strcat(TEXT, DATBUF);
			if (WTHR2 > 0)
				TEXT[4-strlen(DATBUF)] = '+';
			TEXT[5] = '_';
			TEXT[6] = ' ';
			TEXT[7] = '\0';
			WriteString(TEXT);
		}
		else
			WriteString(Osch);
		WriteLn();    
		WriteString(Pchg);
		WriteString(Line);
		WriteLn();    		
		if (IS == -1)
		{
			WriteString(Line);
		}
	}
void GameProtocol::WriteString(char* ss)
	{
		int i;
		char Buf[33];
		i = 0;
		while (*ss)
		{
			Buf[i] = *ss++;
			i++;
		}
		Buf[i] = '\0';
		fprintf(pfPW, "%s", Buf);
	}
void GameProtocol::WriteLn()
	{
		fprintf(pfPW, "\n");
	}

GameProtocol mein_protokoll;

class GameShowfile
	{
	private:
		char filename[256];
	public:
		GameShowfile(){}
		void WriteGameShowfile(int Variant);
		void ReadGameShowfile();
		void CloseGameShowfile();
		void WriteStringShowfile(char* ss);
		void WriteLnShowfile();
		void ShowPossibleMoves(int K, int is, int& IC, int& IV, FieldCommon& SFld, char* TXT);
		void ShowInfoCosts(FieldCommon& SFld, char* TXT);
		void CalVal(int& Int);
	};
void GameShowfile::WriteGameShowfile(int Variant)
	{
		char Buf[272];
		if (!FileOpenGameShowfile)
		{	
			strcpy(Buf, Path_Buffer);
			strcat(Buf, "\\ShowInfo.txt\0");
			if (Variant == 0)
			{
				pfHW = fopen(Buf, "w");
				V0_done = TRUE;
			}
			else if ((Variant == 1) && (V0_done))
			{
				pfHW = fopen(Buf, "a");
				V0_done = FALSE;
			}
			else if ((Variant == 1) && (!V0_done))
				pfHW = fopen(Buf, "w");
			else if (Variant == 2)
			{
				if (INN == 'S')
					pfHW = fopen(Buf, "w");
				else
					pfHW = fopen(Buf, "a");
			}
			FileOpenGameShowfile = TRUE;
			WriteStringShowfile(ShowTitle);
			WriteLnShowfile();
			WriteStringShowfile(ShowLine);
			WriteLnShowfile();
			WriteStringShowfile(GraphicText0);
			WriteLnShowfile();
			WriteStringShowfile(GraphicText1);
			WriteLnShowfile();
		}
		else
			MessageBox( duell_window, "ShowInfo.txt ist bereits geöffnet", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
	}
void GameShowfile::ReadGameShowfile()
	{
		ShellExecute(NULL, "open", "NOTEPAD.EXE", "ShowInfo.txt", Path_Buffer, SW_SHOWNORMAL);
	}
void GameShowfile::CloseGameShowfile()
	{
		WriteStringShowfile(GraphicText2);
		WriteLnShowfile();			
		WriteStringShowfile(ShowEnd);
		WriteLnShowfile();
		WriteLnShowfile();
		fclose(pfHW);
		FileOpenGameShowfile = FALSE;
	}
void GameShowfile::WriteStringShowfile(char* ss)
	{
		int i;
		char Buf[62];
		i = 0;
		while (*ss)
		{
			Buf[i] = *ss++;
			i++;
		}
		Buf[i] = '\0';
		fprintf(pfHW, "%s", Buf);
	}
void GameShowfile::WriteLnShowfile()
	{
		fprintf(pfHW, "\n");
	}
void GameShowfile::ShowPossibleMoves(int K, int is, int& IC, int& IV, FieldCommon& SFld, char* TXT)
	{
		unsigned int i;
		char Buf[62];
		strcpy(Buf, TXT);
		strcat(Buf, " Würfel Nr");
		if (is == 1)
			strcat(Buf, " +");
		else
			strcat(Buf, " -");
		itoa(K, DATBUF, 10);
		strcat(Buf, DATBUF);
		strcat(Buf, " hat");
		itoa(IC, DATBUF, 10);
		for (i=1; i<3+1-strlen(DATBUF); i++)
			strcat(Buf, " \0");
		strcat(Buf, DATBUF);
		strcat(Buf, " mögliche Züge aus");
		itoa(IV, DATBUF, 10);
		for (i=1; i<3+1-strlen(DATBUF); i++)
			strcat(Buf, " \0");
		strcat(Buf, DATBUF);
		strcat(Buf, " Variationen \0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
		if (TXT[0] == 'S')
			strcpy(Buf,"*** \0");
		else if (TXT[0] == 'K')
			strcpy(Buf,"--- \0");
		else
			strcpy(Buf,"    \0");
		strcat(Buf, "Max. Bewertung bisher: \0");
		if (NoCutC)
			strcat(Buf, "     \0");
		else
			strcat(Buf, "aCut \0");
		if (NoCutR)
			strcat(Buf, "     \0");
		else
			strcat(Buf, "bCut \0");
		strcat(Buf, "Alt = \0");
		itoa(SFld.COSTO, DATBUF, 10);
		for (i=1; i<5+1-strlen(DATBUF); i++)
			strcat(Buf, " \0");
		strcat(Buf, DATBUF);
		strcat(Buf, " Neu = \0");
		itoa(SFld.COSTN, DATBUF, 10);
		for (i=1; i<5+1-strlen(DATBUF); i++)
			strcat(Buf, " \0");
		strcat(Buf, DATBUF);
		strcat(Buf, " \0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
	}
void GameShowfile::ShowInfoCosts(FieldCommon& SFld, char* TXT)
	{
		unsigned int i; 
		int st;
		int I, J;
		char Buf[62];
		strcpy(Buf, TXT);
		strcat(Buf, "       ");
		strcat(Buf, "I  N  F  O  R  M  A  T  I  O  N  :\0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
		strcpy(Buf, "        Weisse Figuren:\0");
		strcat(Buf, "          \0");
		strcat(Buf, "        Schwarze Figuren:\0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
		for (I = 1; I <= 8; I++)
		{
			strcpy(Buf, "\0");
			for (J = 1; J <= 9; J++)
			{
				CalVal(SFld.FIGW[J][I]);
				strcat(Buf, Tch);
			}
			strcat(Buf, "      \0");
			for (J = 1; J <= 9; J++)
			{
				CalVal(SFld.FIGR[J][I]);
				strcat(Buf, Tch);
			}
			strcat(Buf, "\0");
			WriteStringShowfile(Buf);
			WriteLnShowfile();
		}
		strcpy(Buf, "        Weisser König: \0");
		strcat(Buf, "          \0");
		strcat(Buf, "        Schwarzer König:\0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
		strcpy(Buf, "\0");
		for (J = 1; J <= 9; J++)
		{
			CalVal(SFld.KINGW[J]);
			strcat(Buf, Tch);
		}
		strcat(Buf, "      \0");
		for (J = 1; J <= 9; J++)
		{
			CalVal(SFld.KINGR[J]);
			strcat(Buf, Tch);
		}
		strcat(Buf, "\0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
		strcpy(Buf, "Spielfeld:\0");
		strcat(Buf, "                       \0");
		strcat(Buf, "Bewertung:\0");
		WriteStringShowfile(Buf);
		WriteLnShowfile();
		for (I = 8; I >= 1; I--)
		{
			strcpy(Buf, "\0");
			for (J = 1; J <= 9; J++)
			{
				CalVal(SFld.FIELD[J][I]);
				strcat(Buf, Tch);
			}
			switch(I)
			{
			case 8: strcat(Buf, "              ");
					strcat(Buf, "für Weiss:\0");
					break;
			case 7: strcat(Buf, "      ");
					for (J = 1; J <= 6; J++)
					{
						CalVal(IHILFW[J]);
						strcat(Buf, Tch);
					}
					CalVal(SFld.IBW);
					strcat(Buf, Tch);
					CalVal(SFld.IPW);
					strcat(Buf, Tch);
					CalVal(SFld.IRW);
					strcat(Buf, Tch);
					strcat(Buf, "\0");
					break;
			case 6: strcat(Buf, "    ");
					itoa(SFld.FIGTW, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, " ");
					itoa(SFld.KNGTW, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					st = SFld.IBW * CO[13] + SFld.IPW * CO[14]
						+ SFld.IRW * CO[15];
					strcat(Buf, " ");
					itoa(st, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					st = SFld.COSTW - SFld.FIGTW - SFld.KNGTW - st;
					strcat(Buf, " ");
					itoa(st, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, " ");
					itoa(SFld.COSTW, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, "\0");
					break;
			case 5: strcat(Buf, "              ");
					strcat(Buf, "für Schwarz:\0");
					break;
			case 4: strcat(Buf, "      ");
					for (J = 1; J <= 6; J++)
					{
						CalVal(IHILFR[J]);
						strcat(Buf, Tch);
					}
					CalVal(SFld.IBR);
					strcat(Buf, Tch);
					CalVal(SFld.IPR);
					strcat(Buf, Tch);
					CalVal(SFld.IRR);
					strcat(Buf, Tch);
					strcat(Buf, "\0");
					break;
			case 3: strcat(Buf, "    ");
					itoa(SFld.FIGTR, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, " ");
					itoa(SFld.KNGTR, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					st = SFld.IBR * CO[13] + SFld.IPR * CO[14]
						+ SFld.IRR * CO[15];
					strcat(Buf, " ");
					itoa(st, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					st = SFld.COSTR - SFld.FIGTR - SFld.KNGTR - st;
					strcat(Buf, " ");
					itoa(st, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, " ");
					itoa(SFld.COSTR, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, "\0");
					break;
			case 2: strcat(Buf, "      ");
					strcat(Buf, "Total der Bewertung:\0");
					break;
			case 1: strcat(Buf, "            ");
					strcat(Buf, "Alt =");
					itoa(SFld.COSTO, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, " Neu =");
					itoa(SFld.COSTN, DATBUF, 10);
					for (i=1; i<5+1-strlen(DATBUF); i++)
						strcat(Buf, " \0");
					strcat(Buf, DATBUF);
					strcat(Buf, "\0");
					break;
			}
			WriteStringShowfile(Buf);
			WriteLnShowfile();
		}
	}
void GameShowfile::CalVal(int& Int)
	{
		char ch;
		unsigned int i;
		if (Int > 0)
			ch = '+';
		else if (Int < 0)
			ch = '-';
		else
			ch = ' ';
		i = (unsigned int)(abs(Int));
		Tch[1] = (char)((unsigned int)(i/10) + (unsigned int)('0'));
		if (Tch[1] == '0')
		{
			Tch[0] = ' ';
			Tch[1] = ch;
		}
		else
			Tch[0] = ch;
		Tch[2] = (char)((unsigned int)(i%10) + (unsigned int)('0'));
		Tch[3] = '\0';
	}

GameShowfile mein_showfile;

class Registeredfile
	{
	private:
		char filename[256];
	public:
		Registeredfile(){}
		void ReadRegisteredfile();
	};
void Registeredfile::ReadRegisteredfile()
	{
		char Buf[272];
		char infoBuf[40];
		strcpy(Buf, Path_Buffer);
		strcat(Buf, "\\Registered.txt\0");
		if ((pfRR = fopen(Buf, "r")) == NULL)
			registered = FALSE;
		else
		{
			registered = TRUE;
			fscanf(pfRR, "%12s", infoBuf);
			strcpy(infoText1, infoBuf);
			strcat(infoText1, " \0");
			fscanf(pfRR, "%7s", infoBuf);
			strcat(infoText1, infoBuf);
			strcat(infoText1, " \0");
			fscanf(pfRR, "%3s", infoBuf);
			strcat(infoText1, infoBuf);
			strcat(infoText1, " \0");
			fscanf(pfRR, "%10s", infoBuf);
			strcat(infoText1, infoBuf);
			strcat(infoText1, "\0");
			fscanf(pfRR, "%3s", infoBuf);
			strcpy(infoText2, infoBuf);
			strcat(infoText2, " \0");
			fscanf(pfRR, "%16s", infoBuf);
			strcat(infoText2, infoBuf);
			strcat(infoText2, " \0");
			fscanf(pfRR, "%17s", infoBuf);
			strcat(infoText2, infoBuf);
			strcat(infoText2, "\0");
			fscanf(pfRR, "%12s", infoBuf);
			strcpy(infoText3, infoBuf);
			strcat(infoText3, " \0");
			fscanf(pfRR, "%8s", infoBuf);
			strcat(infoText3, infoBuf);
			strcat(infoText3, "\0");
			fclose(pfRR);
		}
	}

Registeredfile mein_registeredfile;

class duell
	{
		enum direct {left, right, up, down};
	private:
		int Tab[25][4];			// Würfel-Klapp-Tabelle
		int FOL1[13][13];		// Würfel Endwert-Tabelle 1
		int FOL2[13][13];		// Würfel Endwert-Tabelle 2
		int FOL3[13][13];		// Würfel Endwert-Tabelle 2
		int FOL4[13][13];		// Würfel Endwert-Tabelle 4
		int prod;
		direct FoldDirect;
		int result;
		DWORD time;				// Zeitreferenz
		int speed;				// Geschwindigkeit		
		void initialisieren();
		void display_spielfeld();
	public:
		int spiel_laeuft;		// Indikator, dass das Spiel laeuft
		duell(){ srand( GetTickCount()); initialisieren();}
		void start();
		void display();
		int step();
		void reset_timer(){time = timeGetTime();}
		int FoldCube(int x, int y);
		void TestLeft();
		void TestRight();
		void TestUp();
		void TestDown();
		void Spec();
		void MoveOrBeat();
		void LeftTry();
		void RightTry();
		void UpTry();
		void DownTry();
		void retour();
		void DuellStart();
		void MoveText(unsigned int MNR, char STR[4]);
		void InpOKWait();
		void CheckState();
		void PMLabelCase();
		void CMLabelCase();
		void PersonMove();
		void ComputerMove();
		void DuellEnd();
		void DrawBoard();
		void UpdateField(int& JXa, int& JYa);
		void UpdateBoard(int& JXF, int& JYF, int& JXT, int& JYT);
		void ShowBoard();
		void ShowMove();
		void ShowCosts(int costo, int costn);
		void ShowCompMove();
		void TestMove();
		void ErrTest();
		void WhiteOrBlackLoop(int VORZ, FieldCommon& LFld);
		void InterpretLine();
		int ISIGN(unsigned int I, int K);
		bool FXY(FieldCommon& FFld, int IXF, int IYF, int IX, int IY);
		bool FYX(FieldCommon& FFld, int IXF, int IYF, int IX, int IY);
		int NEWV(int IXD, int IYD, int FIELDA, int is);
		void Hold(FieldCommon& FCFrom, FieldCommon& FCTo);
		void Move(FieldCommon& MFld, int& IXO, int&IYO, int& IXN,
					int& IYN, int& DXI, int& DYI, int& IS, int& IRET);
		void FigNoAct(int VORZ, FieldCommon& AFld, int& IXO, int& IYO);
		void RemFig(int VORZ, FieldCommon& RFld);
		void InsFig(int VORZ, FieldCommon& IFld, int& IXN, int& IYN);
		void FigNoBeat(int VORZ, FieldCommon& BFld, int& IXN, int& IYN);
		void TabvwabrsCalc(int VORZ, FieldCommon& TFld);
		void AttDefCalc(int VORZ, FieldCommon& TFld, int& IZa,
                    bool& IPaFL, bool& ISaFL, bool& IDaFL);
		void LoopIRa(FieldCommon& TFld, int& VORZ, int& I);
		void LoopIRaPlus(FieldCommon& TFld, int& VORZ, int& I, int& J);
		void LoopIRaMinus(FieldCommon& TFld, int& VORZ, int& I, int& J);
		void LoopIPaMinus(FieldCommon& TFld, int& VORZ, int& I);
		void LoopIPa(FieldCommon& TFld, int& VORZ, int& I, bool& ISaFL);
		void LoopIPaPlus(FieldCommon& TFld, int& VORZ, int& I, bool& ISaFL);
		void LoopIPb(FieldCommon& TFld, int& VORZ, bool& IDaFL);
		void LoopIPbPlus(FieldCommon& TFld, int& VORZ, int& K, bool& IDaFL);
		bool SXY(FieldCommon& SFld, int IXF, int IYF, int IX, int IY, int& ISXY);
		bool SYX(FieldCommon& SFld, int IXF, int IYF, int IX, int IY, int& ISYX);
		void RemOldInsNew(int RI, FieldCommon& OFld, int& IXc, int& IYc, int& NR);
		void DistVal(int Variant, int I, int& VORZ, FieldCommon& DFld,
			int& IXc, int& IYc, int& NR, int& RI);
		void OwnRel(int VORZ, FieldCommon& RFld,
			int& IXc, int& IYc, int& NR, int& RI);
		void OppRel(int VORZ, FieldCommon& RFld,
			int& IXc, int& IYc, int& NR, int& RI);
		void OldLineRemDANewLineInsDA(int RI, int DA, FieldCommon& LFld,
			int& IXc, int& IYc, int& NR);
		void XLineTest(int PM, int VORZ, FieldCommon& XFld, int& I,
			int& RI, int& DA, int& IXc, int& IYc, int& NR) ;
		void XDistVal(int Variant, FieldCommon& DFld, int& I, int& J, bool& Jump,
			int& RI, int& DA, int& PM, int& VORZ, int& IXc, int& IYc);
		void YLineTest(int PM, int VORZ, FieldCommon& YFld, int& I,
			int& RI, int& DA, int& IXc, int& IYc, int& NR) ;
		void YDistVal(int Variant, FieldCommon& DFld, int& I, int& J, bool& JUmp,
			int& RI, int& DA, int& PM, int& VORZ, int& IXc, int& IYc);		
		void Cost(FieldCommon& CFld, int& IS);
		void FigKngCost(int VORZ, FieldCommon& KFld);
		void RestCost(int VORZ, FieldCommon& RFld);
		void Contra(int Variant, int is, FieldCommon& WaFld, FieldCommon& WbFld,
						FieldCommon& HaFld, FieldCommon& HbFld);
		void ConPossible(int Variant, int is, FieldCommon& WaFld,
						FieldCommon& WbFld, FieldCommon& HaFld,
						FieldCommon& HbFld);
		void ReTry(int is, FieldCommon& WaFld, FieldCommon& WbFld,
						FieldCommon& HaFld, FieldCommon& HbFld);
		void RetPossible(int is, FieldCommon& WaFld,
						FieldCommon& WbFld, FieldCommon& HaFld,
						FieldCommon& HbFld);
		void Try(int& IRET);
		void ValFig(int VORZ, FieldCommon& WaFld, int& K, bool& JUMP);
		void NewPos(int VORZ, FieldCommon& WaFld,
					FieldCommon& HaFld, int& K);
		void TryPossib(bool& JUMP);
		void WTHR1Change(int VORZ, FieldCommon& GFld, bool& WFL);
		bool FieldEqual();
	};
void duell::initialisieren()
	{
		int z, s;
		strcpy(str,"Grundzustand\0");
		for( z = 0; z <= 8; z++)
		{
			for( s = 0; s <= 9; s++)
				W0.FIELD[s][z] = 0;
		}
		W0.FIELD[1][1] = 53; W0.FIELD[1][8] = -51;
		W0.FIELD[2][1] = 13; W0.FIELD[2][8] = -11;
		W0.FIELD[3][1] = 23; W0.FIELD[3][8] = -21;
		W0.FIELD[4][1] = 61; W0.FIELD[4][8] = -63;
		W0.FIELD[5][1] = 15; W0.FIELD[5][8] = -15;
		W0.FIELD[6][1] = 61; W0.FIELD[6][8] = -63;
		W0.FIELD[7][1] = 23; W0.FIELD[7][8] = -21;
		W0.FIELD[8][1] = 13; W0.FIELD[8][8] = -11;
		W0.FIELD[9][1] = 53; W0.FIELD[9][8] = -51;

		Tab[0][0] = 15; Tab[0][1] = 15; Tab[0][2] = 15; Tab[0][3] = 15;
		Tab[1][0] = 21; Tab[1][1] = 51; Tab[1][2] = 41; Tab[1][3] = 31;
		Tab[2][0] = 42; Tab[2][1] = 32; Tab[2][2] = 52; Tab[2][3] = 22;
		Tab[3][0] = 53; Tab[3][1] = 23; Tab[3][2] = 33; Tab[3][3] = 43;
		Tab[4][0] = 34; Tab[4][1] = 44; Tab[4][2] = 24; Tab[4][3] = 54;
		Tab[5][0] = 63; Tab[5][1] = 11; Tab[5][2] = 42; Tab[5][3] = 34;
		Tab[6][0] = 43; Tab[6][1] = 31; Tab[6][2] = 12; Tab[6][3] = 64;
		Tab[7][0] = 13; Tab[7][1] = 61; Tab[7][2] = 32; Tab[7][3] = 44;
		Tab[8][0] = 33; Tab[8][1] = 41; Tab[8][2] = 62; Tab[8][3] = 14;
		Tab[9][0] = 22; Tab[9][1] = 54; Tab[9][2] = 11; Tab[9][3] = 61;
		Tab[10][0] = 12; Tab[10][1] = 62; Tab[10][2] = 51; Tab[10][3] = 23;
		Tab[11][0] = 52; Tab[11][1] = 24; Tab[11][2] = 63; Tab[11][3] = 13;
		Tab[12][0] = 64; Tab[12][1] = 14; Tab[12][2] = 21; Tab[12][3] = 53;
		Tab[13][0] = 24; Tab[13][1] = 52; Tab[13][2] = 61; Tab[13][3] = 11;
		Tab[14][0] = 62; Tab[14][1] = 12; Tab[14][2] = 53; Tab[14][3] = 21;
		Tab[15][0] = 54; Tab[15][1] = 22; Tab[15][2] = 13; Tab[15][3] = 63;
		Tab[16][0] = 14; Tab[16][1] = 64; Tab[16][2] = 23; Tab[16][3] = 51;
		Tab[17][0] = 11; Tab[17][1] = 63; Tab[17][2] = 44; Tab[17][3] = 32;
		Tab[18][0] = 41; Tab[18][1] = 33; Tab[18][2] = 64; Tab[18][3] = 12;
		Tab[19][0] = 61; Tab[19][1] = 13; Tab[19][2] = 34; Tab[19][3] = 42;
		Tab[20][0] = 31; Tab[20][1] = 43; Tab[20][2] = 14; Tab[20][3] = 62;
		Tab[21][0] = 23; Tab[21][1] = 53; Tab[21][2] = 31; Tab[21][3] = 41;
		Tab[22][0] = 32; Tab[22][1] = 42; Tab[22][2] = 54; Tab[22][3] = 24;
		Tab[23][0] = 51; Tab[23][1] = 21; Tab[23][2] = 43; Tab[23][3] = 33;
		Tab[24][0] = 44; Tab[24][1] = 34; Tab[24][2] = 22; Tab[24][3] = 52;

		CO[0]  =  1; CO[1]  =   5; CO[2]  =   1; CO[3]  =   6; CO[4]  =   3;
		CO[5]  = -4; CO[6]  =   2; CO[7]  =   5; CO[8]  =   1; CO[9]  = -60;
		CO[10] =  2; CO[11] = -30; CO[12] = -20; CO[13] =  40; CO[14] =  40;
		CO[15] = 40; CO[16] = -30; CO[17] = -10; CO[18] = -10;

		W0.FIGW[0][0] = 0;
		W0.FIGW[1][0] = 0; W0.FIGW[2][0] = 0; W0.FIGW[3][0] = 0;
		W0.FIGW[4][0] = 0; W0.FIGW[5][0] = 0; W0.FIGW[6][0] = 0;
		W0.FIGW[7][0] = 0; W0.FIGW[8][0] = 0; W0.FIGW[9][0] = 0;

		W0.FIGW[0][1] = 0;
		W0.FIGW[1][1] = 1; W0.FIGW[2][1] = 1; W0.FIGW[3][1] = 1;
		W0.FIGW[4][1] = 0; W0.FIGW[5][1] = 0; W0.FIGW[6][1] = 0;
		W0.FIGW[7][1] = 1; W0.FIGW[8][1] = 0; W0.FIGW[9][1] = 0;

		W0.FIGW[0][2] = 0;
		W0.FIGW[1][2] = 1; W0.FIGW[2][2] = 2; W0.FIGW[3][2] = 1;
		W0.FIGW[4][2] = 0; W0.FIGW[5][2] = 0; W0.FIGW[6][2] = 0;
		W0.FIGW[7][2] = 0; W0.FIGW[8][2] = 0; W0.FIGW[9][2] = 2;

		W0.FIGW[0][3] = 0;
		W0.FIGW[1][3] = 1; W0.FIGW[2][3] = 3; W0.FIGW[3][3] = 1;
		W0.FIGW[4][3] = 0; W0.FIGW[5][3] = 0; W0.FIGW[6][3] = 0;
		W0.FIGW[7][3] = 1; W0.FIGW[8][3] = 0; W0.FIGW[9][3] = 0;

		W0.FIGW[0][4] = 0;
		W0.FIGW[1][4] = 1; W0.FIGW[2][4] = 4; W0.FIGW[3][4] = 1;
		W0.FIGW[4][4] = 0; W0.FIGW[5][4] = 0; W0.FIGW[6][4] = 0;
		W0.FIGW[7][4] = 1; W0.FIGW[8][4] = 0; W0.FIGW[9][4] = 0;

		W0.FIGW[0][5] = 0;
		W0.FIGW[1][5] = 1; W0.FIGW[2][5] = 6; W0.FIGW[3][5] = 1;
		W0.FIGW[4][5] = 0; W0.FIGW[5][5] = 0; W0.FIGW[6][5] = 0;
		W0.FIGW[7][5] = 1; W0.FIGW[8][5] = 0; W0.FIGW[9][5] = 0;

		W0.FIGW[0][6] = 0;
		W0.FIGW[1][6] = 1; W0.FIGW[2][6] = 7; W0.FIGW[3][6] = 1;
		W0.FIGW[4][6] = 0; W0.FIGW[5][6] = 0; W0.FIGW[6][6] = 0;
		W0.FIGW[7][6] = 1; W0.FIGW[8][6] = 0; W0.FIGW[9][6] = 0;

		W0.FIGW[0][7] = 0;
		W0.FIGW[1][7] = 1; W0.FIGW[2][7] = 8; W0.FIGW[3][7] = 1;
		W0.FIGW[4][7] = 0; W0.FIGW[5][7] = 0; W0.FIGW[6][7] = 0;
		W0.FIGW[7][7] = 0; W0.FIGW[8][7] = 0; W0.FIGW[9][7] = 2;

		W0.FIGW[0][8] = 0;
		W0.FIGW[1][8] = 1; W0.FIGW[2][8] = 9; W0.FIGW[3][8] = 1;
		W0.FIGW[4][8] = 0; W0.FIGW[5][8] = 0; W0.FIGW[6][8] = 0;
		W0.FIGW[7][8] = 1; W0.FIGW[8][8] = 0; W0.FIGW[9][8] = 0;

		W0.FIGR[0][0] = 0;
		W0.FIGR[1][0] = 0; W0.FIGR[2][0] = 0; W0.FIGR[3][0] = 0;
		W0.FIGR[4][0] = 0; W0.FIGR[5][0] = 0; W0.FIGR[6][0] = 0;
		W0.FIGR[7][0] = 0; W0.FIGR[8][0] = 0; W0.FIGR[9][0] = 0;

		W0.FIGR[0][1] = 0;
		W0.FIGR[1][1] = 1; W0.FIGR[2][1] = 1; W0.FIGR[3][1] = 8;
		W0.FIGR[4][1] = 0; W0.FIGR[5][1] = 0; W0.FIGR[6][1] = 0;
		W0.FIGR[7][1] = 1; W0.FIGR[8][1] = 0; W0.FIGR[9][1] = 0;

		W0.FIGR[0][2] = 0;
		W0.FIGR[1][2] = 1; W0.FIGR[2][2] = 2; W0.FIGR[3][2] = 8;
		W0.FIGR[4][2] = 0; W0.FIGR[5][2] = 0; W0.FIGR[6][2] = 0;
		W0.FIGR[7][2] = 0; W0.FIGR[8][2] = 0; W0.FIGR[9][2] = 2;

		W0.FIGR[0][3] = 0;
		W0.FIGR[1][3] = 1; W0.FIGR[2][3] = 3; W0.FIGR[3][3] = 8;
		W0.FIGR[4][3] = 0; W0.FIGR[5][3] = 0; W0.FIGR[6][3] = 0;
		W0.FIGR[7][3] = 1; W0.FIGR[8][3] = 0; W0.FIGR[9][3] = 0;

		W0.FIGR[0][4] = 0;
		W0.FIGR[1][4] = 1; W0.FIGR[2][4] = 4; W0.FIGR[3][4] = 8;
		W0.FIGR[4][4] = 0; W0.FIGR[5][4] = 0; W0.FIGR[6][4] = 0;
		W0.FIGR[7][4] = 1; W0.FIGR[8][4] = 0; W0.FIGR[9][4] = 0;

		W0.FIGR[0][5] = 0;
		W0.FIGR[1][5] = 1; W0.FIGR[2][5] = 6; W0.FIGR[3][5] = 8;
		W0.FIGR[4][5] = 0; W0.FIGR[5][5] = 0; W0.FIGR[6][5] = 0;
		W0.FIGR[7][5] = 1; W0.FIGR[8][5] = 0; W0.FIGR[9][5] = 0;

		W0.FIGR[0][6] = 0;
		W0.FIGR[1][6] = 1; W0.FIGR[2][6] = 7; W0.FIGR[3][6] = 8;
		W0.FIGR[4][6] = 0; W0.FIGR[5][6] = 0; W0.FIGR[6][6] = 0;
		W0.FIGR[7][6] = 1; W0.FIGR[8][6] = 0; W0.FIGR[9][6] = 0;

		W0.FIGR[0][7] = 0;
		W0.FIGR[1][7] = 1; W0.FIGR[2][7] = 8; W0.FIGR[3][7] = 8;
		W0.FIGR[4][7] = 0; W0.FIGR[5][7] = 0; W0.FIGR[6][7] = 0;
		W0.FIGR[7][7] = 0; W0.FIGR[8][7] = 0; W0.FIGR[9][7] = 2;

		W0.FIGR[0][8] = 0;
		W0.FIGR[1][8] = 1; W0.FIGR[2][8] = 9; W0.FIGR[3][8] = 8;
		W0.FIGR[4][8] = 0; W0.FIGR[5][8] = 0; W0.FIGR[6][8] = 0;
		W0.FIGR[7][8] = 1; W0.FIGR[8][8] = 0; W0.FIGR[9][8] = 0;

		W0.KINGW[0] = 0;
		W0.KINGW[1] = 1;  W0.KINGW[2] = 5;  W0.KINGW[3] = 1;
		W0.KINGW[4] = 0;  W0.KINGW[5] = 0;  W0.KINGW[6] = 0;
		W0.KINGW[7] = 2;  W0.KINGW[8] = 0;  W0.KINGW[9] = 0;

		W0.KINGR[0] = 0;
		W0.KINGR[1] = 1;  W0.KINGR[2] = 5;  W0.KINGR[3] = 8;
		W0.KINGR[4] = 0;  W0.KINGR[5] = 0;  W0.KINGR[6] = 0;
		W0.KINGR[7] = 2;  W0.KINGR[8] = 0;  W0.KINGR[9] = 0;

		W0.IBW = 0; W0.IBR = 0;
		W0.IPW = 0; W0.IPR = 0;
		W0.IRW = 0; W0.IRR = 0;
		WTHR1 = 0; WTHR2 = 120;

		FOL1[0][0]   = 0;
		FOL1[1][0]   = 0;  FOL1[2][0]   = 0;  FOL1[3][0]   = 0;
		FOL1[4][0]   = 0;  FOL1[5][0]   = 0;  FOL1[6][0]   = 0;
		FOL1[7][0]   = 0;  FOL1[8][0]   = 0;  FOL1[9][0]   = 0;
		FOL1[10][0]  = 0;  FOL1[11][0]  = 0;  FOL1[12][0]  = 0;

		FOL1[0][1]   = 0;
		FOL1[1][1]   = 51; FOL1[2][1]   = 21; FOL1[3][1]   = 51;
		FOL1[4][1]   = 51; FOL1[5][1]   = 22; FOL1[6][1]   = 54;
		FOL1[7][1]   = 41; FOL1[8][1]   = 41; FOL1[9][1]   = 63;
		FOL1[10][1]  = 11; FOL1[11][1]  = 13; FOL1[12][1]  = 13;

		FOL1[0][2]   = 0;
		FOL1[1][2]   = 41; FOL1[2][2]   = 41; FOL1[3][2]   = 43;
		FOL1[4][2]   = 13; FOL1[5][2]   = 13; FOL1[6][2]   = 62;
		FOL1[7][2]   = 64; FOL1[8][2]   = 44; FOL1[9][2]   = 44;
		FOL1[10][2]  = 34; FOL1[11][2]  = 32; FOL1[12][2]  = 11;

		FOL1[0][3]   = 0;
		FOL1[1][3]   = 12; FOL1[2][3]   = 62; FOL1[3][3]   = 63;
		FOL1[4][3]   = 63; FOL1[5][3]   = 23; FOL1[6][3]   = 53;
		FOL1[7][3]   = 44; FOL1[8][3]   = 44; FOL1[9][3]   = 54;
		FOL1[10][3]  = 22; FOL1[11][3]  = 24; FOL1[12][3]  = 52;

		FOL1[0][4]   = 0;
		FOL1[1][4]   = 53; FOL1[2][4]   = 24; FOL1[3][4]   = 52;
		FOL1[4][4]   = 43; FOL1[5][4]   = 43; FOL1[6][4]   = 61;
		FOL1[7][4]   = 13; FOL1[8][4]   = 11; FOL1[9][4]   = 11;
		FOL1[10][4]  = 44; FOL1[11][4]  = 42; FOL1[12][4]  = 32;

		FOL1[0][5]   = 0;
		FOL1[1][5]   = 52; FOL1[2][5]   = 24; FOL1[3][5]   = 43;
		FOL1[4][5]   = 43; FOL1[5][5]   = 13; FOL1[6][5]   = 61;
		FOL1[7][5]   = 11; FOL1[8][5]   = 11; FOL1[9][5]   = 13;
		FOL1[10][5]  = 13; FOL1[11][5]  = 11; FOL1[12][5]  = 63;

		FOL1[0][6]   = 0;
		FOL1[1][6]   = 61; FOL1[2][6]   = 12; FOL1[3][6]   = 14;
		FOL1[4][6]   = 34; FOL1[5][6]   = 34; FOL1[6][6]   = 44;
		FOL1[7][6]   = 42; FOL1[8][6]   = 13; FOL1[9][6]   = 13;
		FOL1[10][6]  = 11; FOL1[11][6]  = 63; FOL1[12][6]  = 41;

		FOL1[0][7]   = 0;
		FOL1[1][7]   = 51; FOL1[2][7]   = 21; FOL1[3][7]   = 42;
		FOL1[4][7]   = 42; FOL1[5][7]   = 24; FOL1[6][7]   = 52;
		FOL1[7][7]   = 54; FOL1[8][7]   = 22; FOL1[9][7]   = 34;
		FOL1[10][7]  = 34; FOL1[11][7]  = 23; FOL1[12][7]  = 53;

		FOL1[0][8]   = 0;
		FOL1[1][8]   = 41; FOL1[2][8]   = 63; FOL1[3][8]   = 11;
		FOL1[4][8]   = 13; FOL1[5][8]   = 13; FOL1[6][8]   = 34;
		FOL1[7][8]   = 32; FOL1[8][8]   = 42; FOL1[9][8]   = 42;
		FOL1[10][8]  = 62; FOL1[11][8]  = 64; FOL1[12][8]  = 11;

		FOL1[0][9]   = 0;
		FOL1[1][9]   = 63; FOL1[2][9]   = 11; FOL1[3][9]   = 13;
		FOL1[4][9]   = 13; FOL1[5][9]   = 11; FOL1[6][9]   = 11;
		FOL1[7][9]   = 61; FOL1[8][9]   = 13; FOL1[9][9]   = 43;
		FOL1[10][9]  = 43; FOL1[11][9]  = 24; FOL1[12][9]  = 52;

		FOL1[0][10]  = 0;
		FOL1[1][10]  = 44; FOL1[2][10]  = 34; FOL1[3][10]  = 32;
		FOL1[4][10]  = 11; FOL1[5][10]  = 11; FOL1[6][10]  = 13;
		FOL1[7][10]  = 61; FOL1[8][10]  = 43; FOL1[9][10]  = 43;
		FOL1[10][10] = 52; FOL1[11][10] = 24; FOL1[12][10] = 53;

		FOL1[0][11]  = 0;
		FOL1[1][11]  = 54; FOL1[2][11]  = 22; FOL1[3][11]  = 24;
		FOL1[4][11]  = 52; FOL1[5][11]  = 32; FOL1[6][11]  = 32;
		FOL1[7][11]  = 51; FOL1[8][11]  = 21; FOL1[9][11]  = 13;
		FOL1[10][11] = 13; FOL1[11][11] = 64; FOL1[12][11] = 14;

		FOL1[0][12]  = 0;
		FOL1[1][12]  = 11; FOL1[2][12]  = 44; FOL1[3][12]  = 42;
		FOL1[4][12]  = 32; FOL1[5][12]  = 32; FOL1[6][12]  = 12;
		FOL1[7][12]  = 14; FOL1[8][12]  = 63; FOL1[9][12]  = 63;
		FOL1[10][12] = 33; FOL1[11][12] = 31; FOL1[12][12] = 31;

		FOL2[0][0]   = 0;
		FOL2[1][0]   = 0;  FOL2[2][0]   = 0;  FOL2[3][0]   = 0;
		FOL2[4][0]   = 0;  FOL2[5][0]   = 0;  FOL2[6][0]   = 0;
		FOL2[7][0]   = 0;  FOL2[8][0]   = 0;  FOL2[9][0]   = 0;
		FOL2[10][0]  = 0;  FOL2[11][0]  = 0;  FOL2[12][0]  = 0;

		FOL2[0][1]   = 0;
		FOL2[1][1]   = 32; FOL2[2][1]   = 42; FOL2[3][1]   = 54;
		FOL2[4][1]   = 54; FOL2[5][1]   = 12; FOL2[6][1]   = 62;
		FOL2[7][1]   = 42; FOL2[8][1]   = 42; FOL2[9][1]   = 33;
		FOL2[10][1]  = 41; FOL2[11][1]  = 12; FOL2[12][1]  = 12;

		FOL2[0][2]   = 0;
		FOL2[1][2]   = 52; FOL2[2][2]   = 11; FOL2[3][2]   = 13;
		FOL2[4][2]   = 53; FOL2[5][2]   = 53; FOL2[6][2]   = 54;
		FOL2[7][2]   = 52; FOL2[8][2]   = 64; FOL2[9][2]   = 64;
		FOL2[10][2]  = 53; FOL2[11][2]  = 51; FOL2[12][2]  = 14;

		FOL2[0][3]   = 0;
		FOL2[1][3]   = 32; FOL2[2][3]   = 42; FOL2[3][3]   = 21;
		FOL2[4][3]   = 21; FOL2[5][3]   = 61; FOL2[6][3]   = 13;
		FOL2[7][3]   = 64; FOL2[8][3]   = 64; FOL2[9][3]   = 43;
		FOL2[10][3]  = 31; FOL2[11][3]  = 33; FOL2[12][3]  = 41;

		FOL2[0][4]   = 0;
		FOL2[1][4]   = 52; FOL2[2][4]   = 14; FOL2[3][4]   = 64;
		FOL2[4][4]   = 44; FOL2[5][4]   = 44; FOL2[6][4]   = 31;
		FOL2[7][4]   = 43; FOL2[8][4]   = 14; FOL2[9][4]   = 14;
		FOL2[10][4]  = 23; FOL2[11][4]  = 21; FOL2[12][4]  = 12;

		FOL2[0][5]   = 0;
		FOL2[1][5]   = 64; FOL2[2][5]   = 14; FOL2[3][5]   = 44;
		FOL2[4][5]   = 44; FOL2[5][5]   = 43; FOL2[6][5]   = 31;
		FOL2[7][5]   = 14; FOL2[8][5]   = 14; FOL2[9][5]   = 12;
		FOL2[10][5]  = 12; FOL2[11][5]  = 41; FOL2[12][5]  = 33;

		FOL2[0][6]   = 0;
		FOL2[1][6]   = 23; FOL2[2][6]   = 22; FOL2[3][6]   = 24;
		FOL2[4][6]   = 14; FOL2[5][6]   = 14; FOL2[6][6]   = 23;
		FOL2[7][6]   = 21; FOL2[8][6]   = 12; FOL2[9][6]   = 12;
		FOL2[10][6]  = 41; FOL2[11][6]  = 33; FOL2[12][6]  = 42;

		FOL2[0][7]   = 0;
		FOL2[1][7]   = 11; FOL2[2][7]   = 63; FOL2[3][7]   = 62;
		FOL2[4][7]   = 62; FOL2[5][7]   = 33; FOL2[6][7]   = 41;
		FOL2[7][7]   = 43; FOL2[8][7]   = 31; FOL2[9][7]   = 14;
		FOL2[10][7]  = 14; FOL2[11][7]  = 61; FOL2[12][7]  = 13;

		FOL2[0][8]   = 0;
		FOL2[1][8]   = 42; FOL2[2][8]   = 33; FOL2[3][8]   = 41;
		FOL2[4][8]   = 12; FOL2[5][8]   = 12; FOL2[6][8]   = 53;
		FOL2[7][8]   = 51; FOL2[8][8]   = 62; FOL2[9][8]   = 62;
		FOL2[10][8]  = 54; FOL2[11][8]  = 52; FOL2[12][8]  = 51;

		FOL2[0][9]   = 0;
		FOL2[1][9]   = 33; FOL2[2][9]   = 41; FOL2[3][9]   = 12;
		FOL2[4][9]   = 12; FOL2[5][9]   = 14; FOL2[6][9]   = 14;
		FOL2[7][9]   = 31; FOL2[8][9]   = 43; FOL2[9][9]   = 44;
		FOL2[10][9]  = 44; FOL2[11][9]  = 14; FOL2[12][9]  = 64;

		FOL2[0][10]  = 0;
		FOL2[1][10]  = 64; FOL2[2][10]  = 53; FOL2[3][10]  = 51;
		FOL2[4][10]  = 14; FOL2[5][10]  = 14; FOL2[6][10]  = 43;
		FOL2[7][10]  = 31; FOL2[8][10]  = 44; FOL2[9][10]  = 44;
		FOL2[10][10] = 64; FOL2[11][10] = 14; FOL2[12][10] = 52;

		FOL2[0][11]  = 0;
		FOL2[1][11]  = 43; FOL2[2][11]  = 31; FOL2[3][11]  = 33;
		FOL2[4][11]  = 41; FOL2[5][11]  = 12; FOL2[6][11]  = 12;
		FOL2[7][11]  = 11; FOL2[8][11]  = 63; FOL2[9][11]  = 53;
		FOL2[10][11] = 53; FOL2[11][11] = 44; FOL2[12][11] = 34;

		FOL2[0][12]  = 0;
		FOL2[1][12]  = 14; FOL2[2][12]  = 23; FOL2[3][12]  = 21;
		FOL2[4][12]  = 12; FOL2[5][12]  = 12; FOL2[6][12]  = 22;
		FOL2[7][12]  = 24; FOL2[8][12]  = 21; FOL2[9][12]  = 21;
		FOL2[10][12] = 63; FOL2[11][12] = 61; FOL2[12][12] = 22;

		FOL3[0][0]   = 0;
		FOL3[1][0]   = 0;  FOL3[2][0]   = 0;  FOL3[3][0]   = 0;
		FOL3[4][0]   = 0;  FOL3[5][0]   = 0;  FOL3[6][0]   = 0;
		FOL3[7][0]   = 0;  FOL3[8][0]   = 0;  FOL3[9][0]   = 0;
		FOL3[10][0]  = 0;  FOL3[11][0]  = 0;  FOL3[12][0]  = 0;

		FOL3[0][1]   = 0;
		FOL3[1][1]   = 23; FOL3[2][1]   = 53; FOL3[3][1]   = 53;
		FOL3[4][1]   = 53; FOL3[5][1]   = 52; FOL3[6][1]   = 24;
		FOL3[7][1]   = 43; FOL3[8][1]   = 43; FOL3[9][1]   = 13;
		FOL3[10][1]  = 61; FOL3[11][1]  = 11; FOL3[12][1]  = 11;

		FOL3[0][2]   = 0;
		FOL3[1][2]   = 33; FOL3[2][2]   = 31; FOL3[3][2]   = 33;
		FOL3[4][2]   = 61; FOL3[5][2]   = 61; FOL3[6][2]   = 14;
		FOL3[7][2]   = 12; FOL3[8][2]   = 34; FOL3[9][2]   = 34;
		FOL3[10][2]  = 42; FOL3[11][2]  = 44; FOL3[12][2]  = 13;

		FOL3[0][3]   = 0;
		FOL3[1][3]   = 62; FOL3[2][3]   = 12; FOL3[3][3]   = 11;
		FOL3[4][3]   = 11; FOL3[5][3]   = 53; FOL3[6][3]   = 23;
		FOL3[7][3]   = 34; FOL3[8][3]   = 34; FOL3[9][3]   = 22;
		FOL3[10][3]  = 54; FOL3[11][3]  = 52; FOL3[12][3]  = 24;

		FOL3[0][4]   = 0;
		FOL3[1][4]   = 51; FOL3[2][4]   = 54; FOL3[3][4]   = 22;
		FOL3[4][4]   = 41; FOL3[5][4]   = 41; FOL3[6][4]   = 11;
		FOL3[7][4]   = 63; FOL3[8][4]   = 13; FOL3[9][4]   = 13;
		FOL3[10][4]  = 32; FOL3[11][4]  = 34; FOL3[12][4]  = 42;

		FOL3[0][5]   = 0;
		FOL3[1][5]   = 22; FOL3[2][5]   = 54; FOL3[3][5]   = 41;
		FOL3[4][5]   = 41; FOL3[5][5]   = 63; FOL3[6][5]   = 11;
		FOL3[7][5]   = 13; FOL3[8][5]   = 13; FOL3[9][5]   = 11;
		FOL3[10][5]  = 11; FOL3[11][5]  = 61; FOL3[12][5]  = 13;

		FOL3[0][6]   = 0;
		FOL3[1][6]   = 13; FOL3[2][6]   = 64; FOL3[3][6]   = 62;
		FOL3[4][6]   = 44; FOL3[5][6]   = 44; FOL3[6][6]   = 32;
		FOL3[7][6]   = 34; FOL3[8][6]   = 11; FOL3[9][6]   = 11;
		FOL3[10][6]  = 61; FOL3[11][6]  = 13; FOL3[12][6]  = 43;

		FOL3[0][7]   = 0;
		FOL3[1][7]   = 21; FOL3[2][7]   = 51; FOL3[3][7]   = 32;
		FOL3[4][7]   = 32; FOL3[5][7]   = 52; FOL3[6][7]   = 24;
		FOL3[7][7]   = 22; FOL3[8][7]   = 54; FOL3[9][7]   = 44;
		FOL3[10][7]  = 44; FOL3[11][7]  = 53; FOL3[12][7]  = 23;

		FOL3[0][8]   = 0;
		FOL3[1][8]   = 43; FOL3[2][8]   = 13; FOL3[3][8]   = 61;
		FOL3[4][8]   = 11; FOL3[5][8]   = 11; FOL3[6][8]   = 42;
		FOL3[7][8]   = 44; FOL3[8][8]   = 32; FOL3[9][8]   = 32;
		FOL3[10][8]  = 14; FOL3[11][8]  = 12; FOL3[12][8]  = 63;

		FOL3[0][9]   = 0;
		FOL3[1][9]   = 13; FOL3[2][9]   = 61; FOL3[3][9]   = 11;
		FOL3[4][9]   = 11; FOL3[5][9]   = 13; FOL3[6][9]   = 13;
		FOL3[7][9]   = 11; FOL3[8][9]   = 63; FOL3[9][9]   = 41;
		FOL3[10][9]  = 41; FOL3[11][9]  = 54; FOL3[12][9]  = 22;

		FOL3[0][10]  = 0;
		FOL3[1][10]  = 34; FOL3[2][10]  = 42; FOL3[3][10]  = 44;
		FOL3[4][10]  = 13; FOL3[5][10]  = 13; FOL3[6][10]  = 63;
		FOL3[7][10]  = 11; FOL3[8][10]  = 41; FOL3[9][10]  = 41;
		FOL3[10][10] = 22; FOL3[11][10] = 54; FOL3[12][10] = 51;

		FOL3[0][11]  = 0;
		FOL3[1][11]  = 22; FOL3[2][11]  = 54; FOL3[3][11]  = 52;
		FOL3[4][11]  = 24; FOL3[5][11]  = 42; FOL3[6][11]  = 42;
		FOL3[7][11]  = 21; FOL3[8][11]  = 51; FOL3[9][11]  = 61;
		FOL3[10][11] = 61; FOL3[11][11] = 14; FOL3[12][11] = 64;

		FOL3[0][0]   = 0;
		FOL3[1][12]  = 13; FOL3[2][12]  = 32; FOL3[3][12]  = 34;
		FOL3[4][12]  = 42; FOL3[5][12]  = 42; FOL3[6][12]  = 64;
		FOL3[7][12]  = 62; FOL3[8][12]  = 11; FOL3[9][12]  = 11;
		FOL3[10][12] = 43; FOL3[11][12] = 41; FOL3[12][12] = 43;

		FOL4[0][0]   = 0;
		FOL4[1][0]   = 0;  FOL4[2][0]   = 0;  FOL4[3][0]   = 0;
		FOL4[4][0]   = 0;  FOL4[5][0]   = 0;  FOL4[6][0]   = 0;
		FOL4[7][0]   = 0;  FOL4[8][0]   = 0;  FOL4[9][0]   = 0;
		FOL4[10][0]  = 0;  FOL4[11][0]  = 0;  FOL4[12][0]  = 0;

		FOL4[0][1]   = 0;
		FOL4[1][1]   = 44; FOL4[2][1]   = 34; FOL4[3][1]   = 52;
		FOL4[4][1]   = 52; FOL4[5][1]   = 64; FOL4[6][1]   = 14;
		FOL4[7][1]   = 44; FOL4[8][1]   = 44; FOL4[9][1]   = 43;
		FOL4[10][1]  = 31; FOL4[11][1]  = 14; FOL4[12][1]  = 14;

		FOL4[0][2]   = 0;
		FOL4[1][2]   = 24; FOL4[2][2]   = 61; FOL4[3][2]   = 63;
		FOL4[4][2]   = 23; FOL4[5][2]   = 23; FOL4[6][2]   = 24;
		FOL4[7][2]   = 22; FOL4[8][2]   = 14; FOL4[9][2]   = 14;
		FOL4[10][2]  = 21; FOL4[11][2]  = 23; FOL4[12][2]  = 12;

		FOL4[0][3]   = 0;
		FOL4[1][3]   = 42; FOL4[2][3]   = 32; FOL4[3][3]   = 51;
		FOL4[4][3]   = 51; FOL4[5][3]   = 13; FOL4[6][3]   = 61;
		FOL4[7][3]   = 14; FOL4[8][3]   = 14; FOL4[9][3]   = 31;
		FOL4[10][3]  = 43; FOL4[11][3]  = 41; FOL4[12][3]  = 33;

		FOL4[0][4]   = 0;
		FOL4[1][4]   = 54; FOL4[2][4]   = 62; FOL4[3][4]   = 12;
		FOL4[4][4]   = 42; FOL4[5][4]   = 42; FOL4[6][4]   = 41;
		FOL4[7][4]   = 33; FOL4[8][4]   = 12; FOL4[9][4]   = 12;
		FOL4[10][4]  = 51; FOL4[11][4]  = 53; FOL4[12][4]  = 62;

		FOL4[0][5]   = 0;
		FOL4[1][5]   = 12; FOL4[2][5]   = 62; FOL4[3][5]   = 42;
		FOL4[4][5]   = 42; FOL4[5][5]   = 33; FOL4[6][5]   = 41;
		FOL4[7][5]   = 12; FOL4[8][5]   = 12; FOL4[9][5]   = 14;
		FOL4[10][5]  = 14; FOL4[11][5]  = 31; FOL4[12][5]  = 43;

		FOL4[0][6]   = 0;
		FOL4[1][6]   = 53; FOL4[2][6]   = 52; FOL4[3][6]   = 54;
		FOL4[4][6]   = 64; FOL4[5][6]   = 64; FOL4[6][6]   = 51;
		FOL4[7][6]   = 53; FOL4[8][6]   = 14; FOL4[9][6]   = 14;
		FOL4[10][6]  = 31; FOL4[11][6]  = 43; FOL4[12][6]  = 44;

		FOL4[0][7]   = 0;
		FOL4[1][7]   = 63; FOL4[2][7]   = 11; FOL4[3][7]   = 12;
		FOL4[4][7]   = 12; FOL4[5][7]   = 41; FOL4[6][7]   = 33;
		FOL4[7][7]   = 31; FOL4[8][7]   = 43; FOL4[9][7]   = 64;
		FOL4[10][7]  = 64; FOL4[11][7]  = 13; FOL4[12][7]  = 61;

		FOL4[0][8]   = 0;
		FOL4[1][8]   = 44; FOL4[2][8]   = 43; FOL4[3][8]   = 31;
		FOL4[4][8]   = 14; FOL4[5][8]   = 14; FOL4[6][8]   = 21;
		FOL4[7][8]   = 23; FOL4[8][8]   = 12; FOL4[9][8]   = 12;
		FOL4[10][8]  = 24; FOL4[11][8]  = 22; FOL4[12][8]  = 21;

		FOL4[0][9]   = 0;
		FOL4[1][9]   = 43; FOL4[2][9]   = 31; FOL4[3][9]   = 14;
		FOL4[4][9]   = 14; FOL4[5][9]   = 12; FOL4[6][9]   = 12;
		FOL4[7][9]   = 41; FOL4[8][9]   = 33; FOL4[9][9]   = 42;
		FOL4[10][9]  = 42; FOL4[11][9]  = 62; FOL4[12][9]  = 12;

		FOL4[0][10]  = 0;
		FOL4[1][10]  = 14; FOL4[2][10]  = 21; FOL4[3][10]  = 23;
		FOL4[4][10]  = 12; FOL4[5][10]  = 12; FOL4[6][10]  = 33;
		FOL4[7][10]  = 41; FOL4[8][10]  = 42; FOL4[9][10]  = 42;
		FOL4[10][10] = 12; FOL4[11][10] = 62; FOL4[12][10] = 54;

		FOL4[0][11]  = 0;
		FOL4[1][11]  = 31; FOL4[2][11]  = 43; FOL4[3][11]  = 41;
		FOL4[4][11]  = 33; FOL4[5][11]  = 62; FOL4[6][11]  = 62;
		FOL4[7][11]  = 63; FOL4[8][11]  = 11; FOL4[9][11]  = 23;
		FOL4[10][11] = 23; FOL4[11][11] = 34; FOL4[12][11] = 44;

		FOL4[0][12]  = 0;
		FOL4[1][12]  = 12; FOL4[2][12]  = 51; FOL4[3][12]  = 53;
		FOL4[4][12]  = 62; FOL4[5][12]  = 62; FOL4[6][12]  = 52;
		FOL4[7][12]  = 54; FOL4[8][12]  = 51; FOL4[9][12]  = 51;
		FOL4[10][12] = 13; FOL4[11][12] = 11; FOL4[12][12] = 54;

		KX[0] = 0; KY[0] = 0; IPKNG[0] = 0;

// Test Anfang
		for( z = 0; z <= 8; z++)
		{
			for( s = 0; s <= 9; s++)
				S5.FIELD[s][z] = 0;
		}
// Test Ende

		spiel_laeuft = 0;
	}
void duell::start()
	{
		duell_sounds.play(sound_start);
		initialisieren();
		spiel_laeuft = 1;
		reset_timer(); 
		speed = 3;
		Done = FALSE;
		DoneOK = FALSE;
		Flags = 31;
		DuellStart();
		Exit = FALSE;
		InpOK = FALSE;
		InpOKWait();
		// falls ~InpOK dann Events bearbeiten
	}
void duell::display_spielfeld()
	{
		int z, s, l, IHH, ID, IM, IV;
		l = 1;
		for( z = 8; z >= 1; z--)
		{
			for( s = 1; s <= 9; s++)
			{
				if( W0.FIELD[s][z] )
				{
					IHH = abs(W0.FIELD[s][z]);
					if ( IHH == 15 ) IV = 0;
					else
					{
						ID = IHH / 10;
						IM = IHH % 10;
						IV = (ID - 1) * 4 + IM;
					}
				}
				if ( W0.FIELD[s][z] > 0 ) duell_display.weissstein( (8-z), (s-1), IV);
				else if ( W0.FIELD[s][z] < 0 ) duell_display.schwarzstein( (8-z), (s-1), IV);
				else
				{
					if ( l % 2 == 0 ) duell_display.weissfeld( (8-z), (s-1));
					else duell_display.schwarzfeld( (8-z), (s-1));
				}
				l++;
			}
		}
		if (W0.FIELD[5][1] == 0) duell_display.WKfeld();
		if (W0.FIELD[5][8] == 0) duell_display.BKfeld();
	}
void duell::display()
	{
		if (!TextFlag)
		{
			duell_display.hintergrund();
			display_spielfeld();
			duell_display.present();
		}
		hold_color = GetTextColor(duell_dc);
		hold_spc = GetTextCharacterExtra(duell_dc);
		spc = 1;
		SetTextCharacterExtra(duell_dc, spc);
		if (TextFlag)
		{
			color = 0x000000FF; // rot
			SetTextColor(duell_dc, color);
			if (Flags == 28)
			{
				SetTextColor(duell_dc, hold_color);
			}
		}
		TextOut(duell_dc, 438, 140, GraphicText0, strlen(GraphicText0));
		color = 0x00009800; // grün
		SetTextColor(duell_dc, color);
		TextOut(duell_dc, 438, 162, GraphicText1, strlen(GraphicText1));
		color = 0x00FF0000; // blau
		SetTextColor(duell_dc, color);
		TextOut(duell_dc, 438, 184, GraphicText2, strlen(GraphicText2));
		color = 0x000000FF; // rot
		SetTextColor(duell_dc, color);
		TextOut(duell_dc, 438, 228, GraphicText3, strlen(GraphicText3));
		TextOut(duell_dc, 438, 250, GraphicText4, strlen(GraphicText4));
		TextOut(duell_dc, 438, 272, GraphicText5, strlen(GraphicText5));
		TextOut(duell_dc, 438, 294, GraphicText6, strlen(GraphicText6));
		SetTextColor(duell_dc, hold_color);
		TextOut(duell_dc, 438, 316, GraphicText7, strlen(GraphicText7));
		color = 0x000000FF; // rot
		SetTextColor(duell_dc, color);
		TextOut(duell_dc, 438, 338, GraphicText8, strlen(GraphicText8));
		color = 0x00FF0000; // blau
		SetTextColor(duell_dc, color);
		TextOut(duell_dc, 438, 360, GraphicText9, strlen(GraphicText9));
		SetTextColor(duell_dc, hold_color);
		SetTextCharacterExtra(duell_dc, hold_spc);
	}
int duell::step()
	{
		DWORD now;
		int pixel;
		int diff;
		now = timeGetTime();
		diff = (now-time)*speed;
		pixel = diff/5000;
		if( !pixel)
			return 0;
		time = now - diff%5000/speed;
		return 1;
	}
int duell::FoldCube(int x, int y)
	{
		int Value;
		int l;
		int IHH, ID, IM, IV, x_Offset, y_Offset;
		l = (8 - y) * 9 + x;
		if ( l % 2 == 0 ) duell_display.weissfeld( (8-y), (x-1));
		else duell_display.schwarzfeld( (8-y), (x-1));
		IHH = abs(W0.FIELD[x][y]);
		if (IHH == 15) IV = 0;
		else
		{
			ID = IHH / 10;
			IM = IHH % 10;
			IV = (ID - 1) * 4 + IM;
		}
		switch (FoldDirect)
		{
		case left:	x_Offset = -1;
					y_Offset = 0;
					Value = Tab[IV][0];
					break;
		case right: x_Offset = +1;
					y_Offset = 0;
					Value = Tab[IV][1];
					break;
		case up:	x_Offset = 0;
					y_Offset = -1;
					Value = Tab[IV][2];
					break;
		case down:	x_Offset = 0;
					y_Offset = +1;
					Value = Tab[IV][3];
					break;
		}
		if (OldField != 0) back = TRUE;
		if (!back)
		{
			if ( Value == 15 ) IV = 0;
			else
			{
				ID = Value / 10;
				IM = Value % 10;
				IV = (ID - 1) * 4 + IM;
			}
			if (W0.FIELD[x][y] > 0) 
				duell_display.weissstein( (8-y+y_Offset), (x-1+x_Offset), IV);
			else if (W0.FIELD[x][y] < 0)
			{
				Value = -Value;
				duell_display.schwarzstein( (8-y+y_Offset), (x-1+x_Offset), IV);
			}
		}
		W0.FIELD[x][y] = OldField;
		if ((W0.FIELD[x][y] == 0) && (x == 5))
		{
			if (y == 1) duell_display.WKfeld();
			if (y == 8) duell_display.BKfeld();
		}
		return Value;
	}
void duell::TestLeft()
	{
		if (CT == 0)
		{
			CH = CH - 1;
			CT = CT + 1;
			XFIRST = TRUE;
		}
		else
		{
			if (CV == 0)
			{
				if (CH <= 0) CT = CT + 1;
				else CT = CT - 1;
				CH = CH - 1;
			}
			else
			{
				if ((FoldDirect == up) || (FoldDirect == down))
				{
					if (CH == 0)
					{
						CT = CT + 1;
						CH = CH - 1;
					}
					else back = TRUE;
				}
				else
				{
					if (CH <= 0) CT = CT + 1;
					else CT = CT - 1;
					CH = CH - 1;
				}
			}
		}
		if ((CT <= CM) && (!back))
		{
			FoldDirect = left;
			W0.FIELD[xtmp][ytmp] = FoldCube(xtmp+1, ytmp);
			if (back) W0.FIELD[xtmp][ytmp] = NewField;
		}
		else
		{
			W0.FIELD[xtmp+1][ytmp] = OldField;
			back = TRUE;
			Spec();
		}
	}
void duell::TestRight()
	{
		if (CT == 0)
		{
			CH = CH + 1;
			CT = CT + 1;
			XFIRST = TRUE;
		}
		else
		{
			if (CV == 0)
			{
				if (CH >= 0) CT = CT + 1;
				else CT = CT - 1;
				CH = CH + 1;
			}
			else
			{
				if ((FoldDirect == up) || (FoldDirect == down))
				{
					if (CH == 0)
					{
						CT = CT + 1;
						CH = CH + 1;
					}
					else back = TRUE;
				}
				else
				{
					if (CH >= 0) CT = CT + 1;
					else CT = CT - 1;
					CH = CH + 1;
				}
			}
		}
		if ((CT <= CM) && (!back))
		{
			FoldDirect = right;
			W0.FIELD[xtmp][ytmp] = FoldCube(xtmp-1, ytmp);
			if (back) W0.FIELD[xtmp][ytmp] = NewField;
		}
		else
		{
			W0.FIELD[xtmp-1][ytmp] = OldField;
			back = TRUE;
			Spec();
		}
	}
void duell::TestUp()
	{
		if (CT == 0)
		{
			CV = CV + 1;
			CT = CT + 1;
			XFIRST = FALSE;
		}
		else
		{
			if (CH == 0)
			{
				if (CV >= 0) CT = CT + 1;
				else CT = CT - 1;
				CV = CV + 1;
			}
			else
			{
				if ((FoldDirect == left) || (FoldDirect == right))
				{
					if (CV == 0)
					{
						CT = CT + 1;
						CV = CV + 1;
					}
					else back = TRUE;
				}
				else
				{
					if (CV >= 0) CT = CT + 1;
					else CT = CT - 1;
					CV = CV + 1;
				}
			}
		}
		if ((CT <= CM) && (!back))
		{
			FoldDirect = up;
			W0.FIELD[xtmp][ytmp] = FoldCube(xtmp, ytmp-1);
			if (back) W0.FIELD[xtmp][ytmp] = NewField;
		}
		else
		{
			W0.FIELD[xtmp][ytmp-1] = OldField;
			back = TRUE;
			Spec();
		}
	}
void duell::TestDown()
	{
		if (CT == 0)
		{
			CV = CV - 1;
			CT = CT + 1;
			XFIRST = FALSE;
		}
		else
		{
			if (CH == 0)
			{
				if (CV <= 0) CT = CT + 1;
				else CT = CT - 1;
				CV = CV - 1;
			}
			else
			{
				if ((FoldDirect == left) || (FoldDirect == right))
				{
					if (CV == 0)
					{
						CT = CT + 1;
						CV = CV - 1;
					}
					else back = TRUE;
				}
				else
				{
					if (CV <= 0) CT = CT + 1;
					else CT = CT - 1;
					CV = CV - 1;
				}
			}
		}
		if ((CT <= CM) && (!back))
		{
			FoldDirect = down;
			W0.FIELD[xtmp][ytmp] = FoldCube(xtmp, ytmp+1);
			if (back) W0.FIELD[xtmp][ytmp] = NewField;
		}
		else
		{
			W0.FIELD[xtmp][ytmp+1] = OldField;
			back = TRUE;
			Spec();
		}
	}
void duell::Spec()
	{
		if (CM < 0)
		{
			if (IS > 0) strcpy(str,"Weiss muss ziehen\0");
			else strcpy(str,"Schwarz muss ziehen\0");
			spec = TRUE;
		}
		else
		{
			if (CT > CM)
			{
				strcpy(str,"Unerlaubte Anzahl Würfel-Klappungen\0");
				spec = TRUE;
			}
		}
	}
void duell::MoveOrBeat()
	{
		if (NewField == 0) ILINE[2] = '-';
		else ILINE[2] = 'x';
	}
void duell::LeftTry()
	{
		xtmp = xtmp - 1;
		if (xtmp > 0)
		{
			prod = W0.FIELD[xtmp][ytmp] * HilF;
			if (prod <= 0)
			{
				OldField = NewField;
				NewField = W0.FIELD[xtmp][ytmp];
				MoveOrBeat();
				M2X = (xtmp - 1) * 44 + 24;
				TestLeft();
			}
			else
			{
				W0.FIELD[xtmp+1][ytmp] = NewField;
				back = TRUE;
			}
		}
		else
		{
			W0.FIELD[xtmp+1][ytmp] = NewField;
			back = TRUE;
		}
		if (back)  xtmp = xtmp + 1;
	}
void duell::RightTry()
	{
		xtmp = xtmp + 1;
		if (xtmp < 10)
		{
			prod = W0.FIELD[xtmp][ytmp] * HilF;
			if (prod <= 0)
			{
				OldField = NewField;
				NewField = W0.FIELD[xtmp][ytmp];
				MoveOrBeat();
				M2X = (xtmp - 1) * 44 + 24;
				TestRight();
			}
			else
			{
				W0.FIELD[xtmp-1][ytmp] = NewField;
				back = TRUE;
			}
		}
		else
		{
			W0.FIELD[xtmp-1][ytmp] = NewField;
			back = TRUE;
		}
		if (back)  xtmp = xtmp - 1;
	}
void duell::UpTry()
	{
		ytmp = ytmp + 1;
		if (ytmp < 9)
		{
			prod = W0.FIELD[xtmp][ytmp] * HilF;
			if (prod <= 0)
			{
				OldField = NewField;
				NewField = W0.FIELD[xtmp][ytmp];
				MoveOrBeat();
				M2Y = (8 - ytmp) * 44 + 24;
				TestUp();
			}
			else
			{
				W0.FIELD[xtmp][ytmp-1] = NewField;
				back = TRUE;
			}
		}
		else
		{
			W0.FIELD[xtmp][ytmp-1] = NewField;
			back = TRUE;
		}
		if (back)  ytmp = ytmp - 1;
	}
void duell::DownTry()
	{
		ytmp = ytmp - 1;
		if (ytmp > 0)
		{
			prod = W0.FIELD[xtmp][ytmp] * HilF;
			if (prod <= 0)
			{
				OldField = NewField;
				NewField = W0.FIELD[xtmp][ytmp];
				MoveOrBeat();
				M2Y = (8 - ytmp) * 44 + 24;
				TestDown();
			}
			else
			{
				W0.FIELD[xtmp][ytmp+1] = NewField;
				back = TRUE;
			}
		}
		else
		{
			W0.FIELD[xtmp][ytmp+1] = NewField;
			back = TRUE;
		}
		if (back)  ytmp = ytmp + 1;
	}
void duell::retour()
	{
		M2X = 420;
		M2Y = 0;
		M2Flags = 0;
		W0.FIELD[Hxtmp][Hytmp] = HilF;;
		if (!spec) strcpy(str,"Diese Art von Zug ist nicht erlaubt\0");
	}
void duell::DuellStart()
	{
		// Initialisation
		IS = 1;
		MOVENO = 0;
		CHFLAG = FALSE;
		ILOOK = 'N';
		PFL = 0;
		INN = 'J';
		INP = 'J';
		JumpPM = FALSE;
		JumpCM = FALSE;
		strcpy(GraphicText0, BLANK);
		strcpy(GraphicText1, BLANK);
		strcpy(GraphicText2, BLANK);
		strcpy(GraphicText3, BLANK);
		strcpy(GraphicText4, BLANK);
		strcpy(GraphicText5, BLANK);
		strcpy(GraphicText6, BLANK);
		strcpy(GraphicText7, BLANK);
		strcpy(GraphicText8, BLANK);
		strcpy(GraphicText9, BLANK);
		PMLabel = 1;
		IRAND = 'J';
		FileOpen = FALSE;
		FileOpenGameShowfile = FALSE;
		K_Flag = FALSE;
		NoCutC = TRUE;
		NoCutR = TRUE;
		W0.COSTO = 0;
		W0.COSTN = 0;
		// Computing the cost of the start position
		Cost(W0, IS);
		// Typing of the start costs
		ShowCosts(W0.COSTO, W0.COSTN);
		display();
	}
void duell::MoveText(unsigned int MNR, char STR[4])
	{
		unsigned int i;
		char mnr[4];
		strcpy(GraphicText0, BLANK);
		strcpy(GraphicText0, STR);
		itoa(MNR, mnr, 10);
		for (i=1; i<3+1-strlen(mnr); i++)
			strcat(GraphicText0, " \0");
		strcat(GraphicText0, mnr);
		strcat(GraphicText0, ". Zug  ?   \0");
		strcpy(H_GraphicText, GraphicText0);
		display();
  	}
void duell::InpOKWait()
	{
		PMLabelCase();
		if (Flags == 28)
		{
			strcpy(GraphicText0, H_GraphicText);
			strcat(GraphicText0,"<Maus> \0");
			strcpy(GraphicText3, BLANK);
			strcpy(GraphicText4, BLANK);
			strcpy(GraphicText5, BLANK);
			strcpy(GraphicText6, BLANK);
			display();
		}
	}
void duell::CheckState()
	{
		if (InpOK)
		{
			if (!JumpPM)
				PersonMove();
			JumpPM = FALSE;
			if (!Exit)
			{
				CMLabelCase();
				if (!JumpCM)
					ComputerMove();
			}
		}
		else
			InpOKWait();
		if ((Exit) && (InpOK))
		{
			if (!Done)
				DuellEnd();
		}
		else
		{
			InpOK = FALSE;
			InpOKWait();
		}
		if ((Done) && (Exit) && (InpOK))
		{
			if (DoneOK)
				PostMessage( duell_window, WM_COMMAND, ID_DUELL_NEUESSPIEL, 0);
		}
		else
		{
			Exit = FALSE;
			InpOK = FALSE;
			InpOKWait();
		}
	}
void duell::PMLabelCase()
	{
		switch (PMLabel)
		{
		case 1:
			IS = 1;
			if ((INP == 'N') || (INN == 'S'))
			{
				CMLabel = 1;
				InpOK = TRUE;
				JumpPM = TRUE;
				if (INN == 'S')
				{
					MOVENO = MOVENO + 1;
					MoveText(MOVENO, "W:\0");
					strcpy(GraphicText9, Space);
				}
			}
			else
			{
				MOVENO = MOVENO + 1;
				MoveText(MOVENO, "W:\0");
			}
			break;
		case 2:
			MoveText(MOVENO, "W:\0");
			break;
		case 3:
			IS = -1;
			if (INN == 'J')
				MOVENO = MOVENO + 1;
			if (INN == 'S')
			{
				CMLabel = 2;
				InpOK = TRUE;
				JumpPM = TRUE;
				MoveText(MOVENO, "S:\0");
				strcpy(GraphicText9, Space);
			}
			else
				MoveText(MOVENO, "S:\0");
			break;
		case 4:
			MoveText(MOVENO, "S:\0");
			break;
		case 5:
			CMLabel = 1;
			InpOK = TRUE;
			JumpPM = TRUE;
			break;
		default:
			break;
		}
		if (IS == 1)
			PMLabel = 2;
		else
			PMLabel = 4;
	}
void duell::CMLabelCase()
	{
		if (INN != 'J')
		{
			switch (CMLabel)
			{
			case 1:
				PMLabel = 3;
				break;
			case 2:
				PMLabel = 1;
				break;
			default:
				break;
			}
			if (PFL > 1)
				DrawBoard();
		}
	}
void duell::PersonMove()
	{
		char p, w, b;
		if (PFL > 0)
		{
			mein_showfile.WriteGameShowfile(1);
		}
		CHFLAG = TRUE; // zuständig für Zug-Rücknahme-Möglichkeit
		// Update of the FIELD and of all tables
		// FIGW or FIGR show for a given figure:
	    //  a) number of attacks on not defensed opposing figures
		//  b) number of attacks on defensed opposing figures
	    //  c) number of DUELLs by this figure (1=one-way/2=zwo-way)
		//  d) number of defensing own figures (incl. own king)
	    //  e) number of attacks of opposing figures (incl. opp. king)
		//  f) number of defended own figures
	    // KINGW or KINGR show:
		//  r) number of attacks on not defensed opposing figures
	    //  s) number of attacks on defensed opposing figures
		//  t) number of attacks of opposing figures (DUELL's)
	    //  u) number of defended own figures by the king
		//  v) number of lines with only one single opposing figure
	    //     on it whereby an opposing figure is on DUELL-distance
		//  w) number of lines with only one single own figure on it
	    //     (=blocked figure) on it whereby an opposing figure is
		//     on DUELL-distance
		strcpy(GraphicText2, BLANK);
		strcpy(GraphicText2, PZG) ;
		Hold(W0, S1);
		S1.COSTO = W0.COSTO;
		// Move as given by the user
		W0.COSTO = -W0.COSTN;
		IRET = 0;
		Move(W0, IXO, IYO, IXN, IYN, DXI, DYI, IS, IRET);
		// Computing of the cost for a given game-situation with
		// weighting factors CO (sum over all figures and king)
		Cost(W0, IS);
		// Output of the game-situation with the cost
		MARK = TRUE;
		UpdateBoard(IXO, IYO, IXN, IYN);
		MARK = FALSE;
		ShowCosts(W0.COSTO, W0.COSTN);
		if (IRET == 15)
		{
			strcpy(GraphicText9, BLANK);
			strcpy(GraphicText9, DMB);
			if (strlen(GraphicText1) == 20)
				strcat(GraphicText1, " +\0");
			else if (strlen(GraphicText1) == 21)
				strcat(GraphicText1, "+\0");
			ILINE[6] = '+';
		}
		if (IRET == -15)
		{
			strcpy(GraphicText9, BLANK);
			strcpy(GraphicText9, DMW);
			if (strlen(GraphicText1) == 20)
				strcat(GraphicText1, " +\0");
			else if (strlen(GraphicText1) == 21)
				strcat(GraphicText1, "+\0");
			ILINE[6] = '+';
		}
		if (ILINE[5] == '+')
			duell_sounds.play(sound_duell);
		p = 'P';
		w = 'W';
		b = 'S';
		if ((IS == 1) && (FileOpen))
			mein_protokoll.WriteMove(p, w);
		else if ((IS == -1) && (FileOpen))
		{
			mein_protokoll.WriteMove(p, b);
			mein_protokoll.WriteLn();
		}
		if (abs(IRET) == 15)
			Exit = TRUE;
		if (PFL >= 2)
		{
			// Show the cost infos of the game-situation
			mein_showfile.ShowInfoCosts(W0, "P.-Zug:");
		}
		if (!Exit)
		{
			if (IS == 1)
				CMLabel = 1;
			else
				CMLabel = 2;
		}
		if (PFL > 0)
		{
			mein_showfile.CloseGameShowfile();
			if (INN == 'N')
				mein_showfile.ReadGameShowfile();
		}
		if (INN == 'N')
		{
			strcpy(GraphicText2, BLANK);
			strcpy(GraphicText2, WCM) ;
		}
	}
void duell::ComputerMove()
	{
		char c, w, b;
		if (PFL > 0)
			mein_showfile.WriteGameShowfile(2);
		// Computing of the best computer move
		if (INN != 'S')
		{
			if (INP == 'N')
				IS = 1;
			else
				IS = -1;
		}
		W0.COSTO = -W0.COSTN;
		strcpy(GraphicText2, BLANK);
		strcpy(GraphicText2, "Computer ist am denken\0") ;
		IRET = 0;
		Try(IRET);
		// Computing of the cost for a given game-situation with
		// weighting factors CO (sum over all figures and king), i.e.
		// [ 5a)+b)+6c)+3d)-4e)+2f)+5r)+s)-60t)+2u)-30v)-20w)+RestCost ]
		Cost(W0, IS);
		// Output of the computer move
		if (IRET == 15)
		{
			strcpy(GraphicText9, BLANK);
			strcpy(GraphicText9, DMB);
			ILINE[6] = '+';
		}
		if (IRET == -15)
		{
			strcpy(GraphicText9, BLANK);
			strcpy(GraphicText9, DMW);
			ILINE[6] = '+';
		}
		ShowCompMove();
		if (ILINE[5] == '+')
			duell_sounds.play(sound_duell);
		c = 'C';
		w = 'W';
		b = 'S';
		if ((IS == 1) && (FileOpen))
			mein_protokoll.WriteMove(c, w);
		else if ((IS == -1) && (FileOpen))
		{
			mein_protokoll.WriteMove(c, b);
			mein_protokoll.WriteLn();
		}
		// Output of the game-situation with the cost
		MARK = TRUE;
		UpdateBoard(IXO, IYO, IXN, IYN);
		MARK = FALSE;
		ShowCosts(W0.COSTO, W0.COSTN);
		if (abs(IRET) == 15)
			Exit = TRUE;
		if (PFL >= 2)
		{
			// Show the cost infos of the game-situation
			mein_showfile.ShowInfoCosts(W0, "C.-Zug:") ;
		}
		if (!Exit)
		{
			// Next move
			if (INN != 'S')
			{
				if (INP == 'N')
					PMLabel = 3;
				else
					PMLabel = 1;
			}
		}
		if (PFL > 0)
		{
			mein_showfile.CloseGameShowfile();
			mein_showfile.ReadGameShowfile();
		}
	}
void duell::DuellEnd()
	{
		// Exit ?
		strcpy(GraphicText0, BLANK);
		duell_sounds.play(sound_win);
		Done = TRUE;
		// Program finished or aborted
		strcpy(GraphicText6, BLANK);
		strcpy(GraphicText6, "DUELL beendigt\0");
		strcpy(GraphicText8, SpaceNewGame);
		display();
		JumpCM = TRUE;
		JumpPM = TRUE;
	}
void duell::DrawBoard()
	{
		display_spielfeld();
		duell_display.present();
	}
void duell::UpdateBoard(int& JXF, int& JYF, int& JXT, int& JYT)
	{
		int i, j;
		int IXF, IYF, IXT, IYT;
		if ((MARK) && (Mark_on == 1))
		{
			if (XFIRST)
			{
				if ((JXT-JXF) > 0)
				{
					for (i = JXF; i <= JXT; i++)
						duell_display.markfeld((8-JYF), (i-1));
				}
				else if ((JXT-JXF) < 0)
				{
					for (i = JXF; i >= JXT; i--)
						duell_display.markfeld((8-JYF), (i-1));
				}
				if ((JYT-JYF) > 0)
				{
					for (i = JYF; i <= JYT; i++)
						duell_display.markfeld((8-i), (JXT-1));
				}
				else if ((JYT-JYF) < 0)
				{
					for (i = JYF; i >= JYT; i--)
						duell_display.markfeld((8-i), (JXT-1));
				}
			}
			else
			{
				if ((JYT-JYF) > 0)
				{
					for (i = JYF; i <= JYT; i++)
						duell_display.markfeld((8-i), (JXF-1));
				}
				else if ((JYT-JYF) < 0)
				{
					for (i = JYF; i >= JYT; i--)
						duell_display.markfeld((8-i), (JXF-1));
				}
				if ((JXT-JXF) > 0)
				{
					for (i = JXF; i <= JXT; i++)
						duell_display.markfeld((8-JYT), (i-1));
				}
				else if ((JXT-JXF) < 0)
				{
					for (i = JXF; i >= JXT; i--)
						duell_display.markfeld((8-JYT), (i-1));
				}
			}
			UpdateField(JXT, JYT);
			duell_display.present();
			Sleep(400);
			if (ILINE[5] == '+')
			{
				if (IS == 1)
				{
					IXT = W0.KINGR[2];
					IYT = W0.KINGR[3];
					for (j = 1; j <= 8; j++)
					{
						if (W0.FIGW[1][j] != 0)
						{
							if (W0.FIGW[6][j] != 0)
							{
								IXF = W0.FIGW[2][j];
								IYF = W0.FIGW[3][j];
								if (W0.FIGW[6][j] == 1)
								{
									if (FXY(W0, IXF, IYF, IXT-IXF, IYT-IYF))
									{
										if ((IXT-IXF) > 0)
										{
											for (i = (IXF+1); i <= (IXT-1); i++)
												duell_display.warnfeld((8-IYF), (i-1));
											u1 = 0;					
										}
										else if ((IXT-IXF) < 0)
										{
											for (i = (IXF-1); i >= (IXT+1); i--)
												duell_display.warnfeld((8-IYF), (i-1));
											u1 = 0;					
										}
										else if ((IXT-IXF) == 0)
											u1 = 1;
										if ((IYT-IYF) > 0)
										{
											for (i = (IYF+u1); i <= (IYT-1); i++)
												duell_display.warnfeld((8-i), (IXT-1));
										}
										else if ((IYT-IYF) < 0)
										{
											for (i = (IYF-u1); i >= (IYT+1); i--)
												duell_display.warnfeld((8-i), (IXT-1));
										}
									}
									else
									{
										if ((IYT-IYF) > 0)
										{
											for (i = (IYF+1); i <= (IYT-1); i++)
												duell_display.warnfeld((8-i), (IXF-1));
											u1 = 0;					
										}
										else if ((IYT-IYF) < 0)
										{
											for (i = (IYF-1); i >= (IYT+1); i--)
												duell_display.warnfeld((8-i), (IXF-1));
											u1 = 0;					
										}
										else if ((IYT-IYF) == 0)
											u1 = 1;
										if ((IXT-IXF) > 0)
										{
											for (i = (IXF+u1); i <= (IXT-1); i++)
												duell_display.warnfeld((8-IYT), (i-1));
										}
										else if ((IXT-IXF) < 0)
										{
											for (i = (IXF-u1); i >= (IXT+1); i--)
												duell_display.warnfeld((8-IYT), (i-1));
										}
									}
								}
								else if (W0.FIGW[6][j] == 2)
								{
									if ((IXT-IXF) > 0)
									{
										for (i = (IXF+1); i <= (IXT-1); i++)
											duell_display.warnfeld((8-IYF), (i-1));
									}
									else if ((IXT-IXF) < 0)
									{
										for (i = (IXF-1); i >= (IXT+1); i--)
											duell_display.warnfeld((8-IYF), (i-1));
									}
									if ((IYT-IYF) > 0)
									{
										for (i = IYF; i <= (IYT-1); i++)
											duell_display.warnfeld((8-i), (IXT-1));
									}
									else if ((IYT-IYF) < 0)
									{
										for (i = IYF; i >= (IYT+1); i--)
											duell_display.warnfeld((8-i), (IXT-1));
									}
									if ((IYT-IYF) > 0)
									{
										for (i = (IYF+1); i <= (IYT-1); i++)
											duell_display.warnfeld((8-i), (IXF-1));
									}
									else if ((IYT-IYF) < 0)
									{
										for (i = (IYF-1); i >= (IYT+1); i--)
											duell_display.warnfeld((8-i), (IXF-1));
									}
									if ((IXT-IXF) > 0)
									{
										for (i = IXF; i <= (IXT-1); i++)
											duell_display.warnfeld((8-IYT), (i-1));
									}
									else if ((IXT-IXF) < 0)
									{
										for (i = IXF; i >= (IXT+1); i--)
											duell_display.warnfeld((8-IYT), (i-1));
									}
								}
							}
						}
					}
				}
				else
				{
					IXT = W0.KINGW[2];
					IYT = W0.KINGW[3];
					for (j = 1; j <= 8; j++)
					{
						if (W0.FIGR[1][j] != 0)
						{
							if (W0.FIGR[6][j] != 0)
							{
								IXF = W0.FIGR[2][j];
								IYF = W0.FIGR[3][j];
								if (W0.FIGR[6][j] == 1)
								{
									if (FXY(W0, IXF, IYF, IXT-IXF, IYT-IYF))
									{
										if ((IXT-IXF) > 0)
										{
											for (i = (IXF+1); i <= (IXT-1); i++)
												duell_display.warnfeld((8-IYF), (i-1));
											u1 = 0;					
										}
										else if ((IXT-IXF) < 0)
										{
											for (i = (IXF-1); i >= (IXT+1); i--)
												duell_display.warnfeld((8-IYF), (i-1));
											u1 = 0;					
										}
										else if ((IXT-IXF) == 0)
											u1 = 1;
										if ((IYT-IYF) > 0)
										{
											for (i = (IYF+u1); i <= (IYT-1); i++)
												duell_display.warnfeld((8-i), (IXT-1));
										}
										else if ((IYT-IYF) < 0)
										{
											for (i = (IYF-u1); i >= (IYT+1); i--)
												duell_display.warnfeld((8-i), (IXT-1));
										}
									}
									else
									{
										if ((IYT-IYF) > 0)
										{
											for (i = (IYF+1); i <= (IYT-1); i++)
												duell_display.warnfeld((8-i), (IXF-1));
											u1 = 0;					
										}
										else if ((IYT-IYF) < 0)
										{
											for (i = (IYF-1); i >= (IYT+1); i--)
												duell_display.warnfeld((8-i), (IXF-1));
											u1 = 0;					
										}
										else if ((IYT-IYF) == 0)
											u1 = 1;
										if ((IXT-IXF) > 0)
										{
											for (i = (IXF+u1); i <= (IXT-1); i++)
												duell_display.warnfeld((8-IYT), (i-1));
										}
										else if ((IXT-IXF) < 0)
										{
											for (i = (IXF-u1); i >= (IXT+1); i--)
												duell_display.warnfeld((8-IYT), (i-1));
										}
									}
								}
								else if (W0.FIGR[6][j] == 2)
								{
									if ((IXT-IXF) > 0)
									{
										for (i = (IXF+1); i <= (IXT-1); i++)
											duell_display.warnfeld((8-IYF), (i-1));
									}
									else if ((IXT-IXF) < 0)
									{
										for (i = (IXF-1); i >= (IXT+1); i--)
											duell_display.warnfeld((8-IYF), (i-1));
									}
									if ((IYT-IYF) > 0)
									{
										for (i = IYF; i <= (IYT-1); i++)
											duell_display.warnfeld((8-i), (IXT-1));
									}
									else if ((IYT-IYF) < 0)
									{
										for (i = IYF; i >= (IYT+1); i--)
											duell_display.warnfeld((8-i), (IXT-1));
									}
									if ((IYT-IYF) > 0)
									{
										for (i = (IYF+1); i <= (IYT-1); i++)
											duell_display.warnfeld((8-i), (IXF-1));
									}
									else if ((IYT-IYF) < 0)
									{
										for (i = (IYF-1); i >= (IYT+1); i--)
											duell_display.warnfeld((8-i), (IXF-1));
									}
									if ((IXT-IXF) > 0)
									{
										for (i = IXF; i <= (IXT-1); i++)
											duell_display.warnfeld((8-IYT), (i-1));
									}
									else if ((IXT-IXF) < 0)
									{
										for (i = IXF; i >= (IXT+1); i--)
											duell_display.warnfeld((8-IYT), (i-1));
									}
								}
							}
						}
					}
				}
				duell_display.present();
				Sleep(500);
			}
		}
		UpdateField(JXF, JYF);
		UpdateField(JXT, JYT);
		duell_display.present();
	}
void duell::UpdateField(int& JXa, int& JYa)
	{
		int l, IHH, ID, IM, IV;
		if (W0.FIELD[JXa][JYa] == 0)
		{
			l = (8 - JYa) * 9 + JXa;
			if ((l % 2) == 0)
			{
				if ((JXa == 5) && (JYa == 1))
					duell_display.WKfeld();
				else
					duell_display.weissfeld((8-JYa), (JXa-1));
			}
			else
			{
				if ((JXa == 5) && (JYa == 8))
					duell_display.BKfeld();
				else
					duell_display.schwarzfeld((8-JYa), (JXa-1));
			}
		}
		else
		{
			IHH = abs(W0.FIELD[JXa][JYa]);
			if (IHH == 15) IV = 0;
			else
			{
				ID = IHH / 10;
				IM = IHH % 10;
				IV = (ID -1) * 4 + IM;
			}
			if (W0.FIELD[JXa][JYa] > 0)
				duell_display.weissstein((8-JYa), (JXa-1), IV);
			else
				duell_display.schwarzstein((8-JYa), (JXa-1), IV);
		}
	}
void duell::ShowBoard()
	{
		DrawBoard();
		if (CHFLAG)
		{
			if (((MOVENO > 1) && (IS == 1)) || ((MOVENO > 0) && (IS == -1)))
			{
				if (INN == 'J')
				{
					IS = -IS;
					ShowCompMove();
					IS = -IS;
				}
				else
					ShowMove();
			}
		}
		ShowCosts(W0.COSTO, W0.COSTN);
	}
void duell::ShowMove()
	{
		// Interpretation of the mouse move
		ILINE[1] = (char)((unsigned int)(IYO) + (unsigned int)('0'));
		ILINE[4] = (char)((unsigned int)(IYN) + (unsigned int)('0'));
		if (IXO == IXN)
		{
			ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('@'));
			ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('@'));
		}
		else if (IYO == IYN)
		{
			ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('`'));
			ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('`'));
		}
		else
		{
			if (XFIRST)
			{
				ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('`'));
				ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('@'));
			}
			else
			{
				ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('@'));
				ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('`'));
			}
		}
		ILINE[7] = '\0';
		strcpy(GraphicText1, BLANK);
		strcpy(GraphicText1,"Ihr Zug ist :  \0");
		strcat(GraphicText1, ILINE);
	}
void duell::ShowCosts(int costo, int costn)
	{
		unsigned int i;
		strcpy(GraphicText7, "Alt =  \0");
		itoa(costo, DATBUF, 10);
		for (i=1; i<6+1-strlen(DATBUF); i++)
			strcat(GraphicText7, " \0");
		strcat(GraphicText7, DATBUF);
		strcat(GraphicText7, "   Neu =  \0");
		itoa(costn, DATBUF, 10);
		for (i=1; i<6+1-strlen(DATBUF); i++)
			strcat(GraphicText7, " \0");
		strcat(GraphicText7, DATBUF);
	}
void duell::ShowCompMove()
	{
		duell_sounds.play(sound_compmove);
		strcpy(GraphicText2, BLANK);
		if (IS == 1)
			strcpy(GraphicText2, "W: Comp. Zug:  \0");
		else
			strcpy(GraphicText2, "S: Comp. Zug:  \0");
		strcat(GraphicText2, ILINE);
	}
void duell::TestMove()
	{
		IERR = 0;
		InterpretLine();
		ErrTest();
	}
void duell::ErrTest()
	{
		// Fehler- und andere Meldungen abhängig von IERR
		switch(IERR)
		{
		case 0:
			InpOK = TRUE;
			break;
		case 1:
			strcpy(GraphicText5, IllMove);
			duell_sounds.play(sound_persmove);
			break;
		case 2:
			strcpy(GraphicText6, BLANK);
			strcpy(GraphicText6, "DUELL ?\0");
			strcpy(GraphicText5, IllMove);
			duell_sounds.play(sound_persmove);
			break;
		case 3:
			strcpy(GraphicText3, BLANK);
			strcpy(GraphicText4, BLANK);
			strcpy(GraphicText3, "DUELL-MATT: Schlag den\0");
			strcpy(GraphicText4, "König im nächsten Zug!\0");
			duell_sounds.play(sound_persmove);
			InpOK = TRUE;
			break;
		case 4:
			strcpy(GraphicText6, BLANK);
			strcpy(GraphicText6, "DUELL-MATT ?\0");
			strcpy(GraphicText5, IllMove);
			duell_sounds.play(sound_persmove);
			break;
		default:
			break;
		}
	}
void duell::WhiteOrBlackLoop(int VORZ, FieldCommon& LFld)
	{
		int I, H1_I;
		ENDLP = FALSE;
		for (I = 1; I <= 8; I++)
		{
			if (VORZ == 1)
				H1_I = LFld.FIGW[1][I];
			else
				H1_I = LFld.FIGR[1][I];
			if ((H1_I != 0) && (!ERR) && (!ENDLP))
			{
				if (VORZ ==1)
				{
					HXI = LFld.FIGW[2][I];
					HYI = LFld.FIGW[3][I];
				}
				else
				{
					HXI = LFld.FIGR[2][I];
					HYI = LFld.FIGR[3][I];
				}
				if ((HXI == IXO) && (HYI == IYO))
				{
					HXI = IXN;
					HYI = IYN;
				}
				IVAL = VORZ * (W0.FIELD[HXI][HYI] / 10);
				IDIST = abs(XKI-HXI) + abs(YKI-HYI);
				if (IVAL == IDIST)
				{
					if (FXY(W0, HXI, HYI, XKI-HXI, YKI-HYI) ||
						FYX(W0, HXI, HYI, XKI-HXI ,YKI-HYI))
					{
						if ((ILINE[5] != '+') || (IQ <= 5))
							ERR = TRUE;
						else
							ENDLP = TRUE;
					}
				}
			}
		}
		if (!ENDLP)
		{
			if (ILINE[5] == '+')
				ERR = TRUE;
		}
	}
void duell::InterpretLine()
	{
		// Initialisation
		IXO = 0;
		IYO = 0;
		IXN = 0;
		IYN = 0;
		ERR = FALSE;
		IERR = 0;
		ICLINE = 0;
		XFIRST = TRUE;
		// Tests for the input line
		if ((ILINE[0] <= '@') || (ILINE[0] >= 'J'))
		{
			if ((ILINE[0] <= '`') || (ILINE[0] >= 'j'))
				ERR = TRUE;
			else
				IXO = (int)(ILINE[0]) - (int)('`');
		}
		else
		{
			IXO = (int)(ILINE[0]) - (int)('@');
			ICLINE = IXO;
			XFIRST = FALSE;
		}
		if (!ERR)
		{
			if ((ILINE[1] <= '0') || (ILINE[1] >= '9'))
				ERR = TRUE;
			else
			{
				IYO = (int)(ILINE[1]) - (int)('0');
				if ((W0.FIELD[IXO][IYO] == 0) || ((W0.FIELD[IXO][IYO]*IS) <= 0))
					ERR = TRUE;
				else if (!((ILINE[2] == '-') ||
						(ILINE[2] == 'X') || (ILINE[2] == 'x')))
					ERR = TRUE;
				else
				{
					if (ILINE[2] == 'X')
						ILINE[2] = 'x';
					if ((ILINE[3] <= '@') || (ILINE[3] >= 'J'))
					{
						if ((ILINE[3] <= '`') || (ILINE[3] >= 'j'))
							ERR = TRUE;
						else
						{
							IXN = (int)(ILINE[3]) - (int)('`');
							if (IXO == IXN)
								ERR = TRUE;
							else if (ICLINE == 0)
								XFIRST = FALSE;
						}
					}
					else
					{
						IXN = (int)(ILINE[3]) - (int)('@');
						if ((IXO == IXN) && (XFIRST))
							ERR = TRUE;
						else if ((ICLINE != 0) && (IXN != IXO))
							ERR = TRUE;
						else
						{
							ICLINE = IXN;
							XFIRST = TRUE;
						}
					}
					if (!ERR)
					{
						if ((ILINE[4] <= '0') || (ILINE[4] >= '9'))
							ERR = TRUE;
						else
						{
							IYN = (int)(ILINE[4]) - (int)('0');
							if ((IYO == IYN) && (ICLINE != 0))
								ERR = TRUE;
							else if ((ILINE[1] != ILINE[4]) && (ICLINE = 0))
								ERR = TRUE;
							else if ((ILINE[2] == '-') && (W0.FIELD[IXN][IYN] != 0))
								ERR = TRUE;
							else if (((ILINE[2] == 'X') || (ILINE[2] == 'x')) &&
									((W0.FIELD[IXN][IYN]*IS) > 0))
								ERR = TRUE;
							else
							{
								DXI = IXN - IXO;
								DYI = IYN - IYO;
								IDXA = abs(DXI);
								IDYA = abs(DYI);
								ITOT = IDXA + IDYA;
								if (((W0.FIELD[IXO][IYO]*IS) / 10) != ITOT)
									ERR = TRUE;
								else if (ICLINE == IXO)
								{
									if (!(FYX(W0, IXO, IYO, DXI, DYI)))
										ERR = TRUE;
									else if (!(FXY(W0, IXO, IYO, DXI, DYI)))
										ERR = TRUE;
								}
							}
						}
					}
				}
			}
		}
		if (ERR)
			IERR = 1;
		if (!ERR)
		{
			// Test if DUELL or if DUELL-MATE
			HILN = W0.FIELD[IXN][IYN];
			W0.FIELD[IXN][IYN] = NEWV(DXI, DYI, W0.FIELD[IXO][IYO], IS);
			if (IS == 1)
			{
				XKI = W0.KINGR[2];
				YKI = W0.KINGR[3];
			}
			else
			{
				XKI = W0.KINGW[2];
				YKI = W0.KINGW[3];
			}
			HILO = W0.FIELD[IXO][IYO];
			W0.FIELD[IXO][IYO] = 0;
			if (IS == 1)
				WhiteOrBlackLoop(1, W0);
			else
				WhiteOrBlackLoop(-1, W0);
			if (ERR)
			{
				IERR = 2;
				W0.FIELD[IXO][IYO] = HILO;
				W0.FIELD[IXN][IYN] = HILN;
			}
		}
		if (!ERR)
		{
			W0.FIELD[IXO][IYO] = HILO;
			W0.FIELD[IXN][IYN] = HILN;
			if (IQ >= 6)
			{
				if (((ILINE[5] == '+') || (ILINE[6] == '+')))
				{
					Hold(W0, S0);
					HXF = XFIRST;
					HCOST = W0.COSTO;
					W0.COSTO = -W0.COSTN;
					Move(W0, IXO, IYO, IXN, IYN, DXI, DYI, IS, IRET);
					Cost(W0, IS);
					W3FLAG = FALSE;
					W4FLAG = FALSE;
					Hold(W0, W1);
					if ((ILINE[6] == '+') && (IQ == 7))
					{
						strcpy(GraphicText2, TSTD);
						strcat(GraphicText2,"-MATT ?\0");
					}
					else
					{
						strcpy(GraphicText2, TSTD);
						strcat(GraphicText2, " ?\0");
					}
					HIRET = IRET;
					Contra(0, IS, W1, W2, H1, H2);
					IRET = HIRET;
					Hold(S0, W0);
					XFIRST = HXF;
					W0.COSTO = HCOST;
					strcpy(GraphicText2, BLANK);
					if (IS == 1)
					{
						if ((S2.KINGR[6] != 0) && (S2.KINGW[1] != 0))
							IERR = 3;
						else
							IERR = 4;
					}
					else
					{
						if ((S2.KINGW[6] != 0) && (S2.KINGR[1] != 0))
							IERR = 3;
						else
							IERR = 4;
					}
					if ((IERR == 3) && ((ILINE[6] != '+') || (IQ < 7)))
						IERR = 4;
					else if ((IERR == 4) && ((ILINE[6] != '+') || (IQ < 7)))
						IERR = 0;
				}
				else
					IERR = 1;
			}
		}
	}
int duell::ISIGN(unsigned int I, int K)
	{
		int VAL;
		if ((I == 0) || (K == 0))
			VAL = (int)(I);
		else
			VAL = (int)(I) * (K / (abs(K)));
		return VAL;
	}
bool duell::FXY(FieldCommon& FFld, int IXF, int IYF, int IX, int IY)
	{
		// Checks if the way over the x-y-line is free and on the board
		int IXZ, IYZ;
		bool RES, JUMP;
		unsigned int I, IFROM;
		JUMP = FALSE;
		IXZ = IXF + IX;
		IYZ = IYF + IY;
		if ((IXZ <= 0) || (IXZ > 9))
			RES = FALSE;
		else if ((IYZ <= 0) || (IYZ > 8))
			RES = FALSE;
		else
		{
			if (!((IX == 0) || (IX == 1) || (IX == -1)))
			{
				for (I = 1; I <= (unsigned int)(abs(IX)-1); I++)
				{
					if ((!JUMP) && (FFld.FIELD[IXF+ISIGN(I,IX)][IYF] != 0))
						JUMP = TRUE;
				}
			}
			if (!JUMP)
			{
				if ((IY == 0) || ((IX == 0) && ((IY == 1) || (IY == -1))))
					RES = TRUE;
				else
				{
					RES = TRUE;
					if (IX == 0)
						IFROM = 1;
					else
						IFROM = 0;
					for (I = IFROM; I <= (unsigned int)(abs(IY)-1); I++)
					{
						if ((!JUMP) && (FFld.FIELD[IXZ][IYF+ISIGN(I,IY)] != 0))
						{
							JUMP = TRUE;
							RES = FALSE;
						}
					}
				}
			}
			else
				RES = FALSE;
		}
		return RES;
	}
bool duell::FYX(FieldCommon& FFld, int IXF, int IYF, int IX, int IY)
	{
		// Checks if the way over the y-x-line is free and on the board
		int IXZ, IYZ;
		bool RES, JUMP;
		unsigned int I, IFROM;
		JUMP = FALSE;
		IXZ = IXF + IX;
		IYZ = IYF + IY;
		if ((IXZ <= 0) || (IXZ > 9))
			RES = FALSE;
		else if ((IYZ <= 0) || (IYZ > 8))
			RES = FALSE;
		else
		{
			if (!((IY == 0) || (IY == 1) || (IY == -1)))
			{
				for (I = 1; I <= (unsigned int)(abs(IY)-1); I++)
				{
					if ((!JUMP) && (FFld.FIELD[IXF][IYF+ISIGN(I,IY)] != 0))
						JUMP = TRUE;
				}
			}
			if (!JUMP)
			{
				if ((IX == 0) || ((IY == 0) && ((IX == 1) || (IX == -1))))
					RES = TRUE;
				else
				{
					RES = TRUE;
					if (IY == 0)
						IFROM = 1;
					else
						IFROM = 0;
					for (I = IFROM; I <= (unsigned int)(abs(IX)-1); I++)
					{
						if ((!JUMP) && (FFld.FIELD[IXF+ISIGN(I,IX)][IYZ] != 0))
						{
							JUMP = TRUE;
							RES = FALSE;
						}
					}
				}
			}
			else
				RES = FALSE;
		}
		return RES;
	}
int duell::NEWV(int IXD, int IYD, int FIELDA, int is)
	{
		// Gives new cube value by a table lookup
		int VAL, IVALV, IH, MX, MY, IX, IY;
		unsigned int IIH;
		IH = is * FIELDA;
		IVALV = IH % 10;
		if (IVALV != 5)
		{
			if (XFIRST)
			{
				MX = 2 * IXD;
				IIH = (unsigned int)(2 * abs(IYD) - 1);
				MY = ISIGN(IIH,IYD);
			}
			else
			{
				IIH = (unsigned int)(2 * abs(IXD) - 1);
				MX = ISIGN(IIH,IXD);
				MY = 2 * IYD;
			}
			if (MX > 0)
			{
				if (MY >= 0)
				{
					IX = MX;
					IY = MY + 1;
				}
				else
				{
					IX = 13 - MX;
					IY = MY + 13;
				}
			}
			else
			{
				if (MY >= 0)
				{
					IX = 1 - MX;
					IY = MY + 1;
				}
				else
				{
					IX = MX + 12;
					IY = MY + 13;
				}
			}
		}
		switch(IVALV)
		{
		case 1:
			VAL = is * FOL1[IX][IY];
			break;
		case 2:
			VAL = is * FOL2[IX][IY];
			break;
		case 3:
			VAL = is * FOL3[IX][IY];
			break;
		case 4:
			VAL = is * FOL4[IX][IY];
			break;
		case 5:
			VAL = is * 15;
		default:
			break;
		}
		return VAL;
	}
void duell::Hold(FieldCommon& FCFrom, FieldCommon& FCTo)
	{
		// Copies the information fields of one state to other fields
		int I, J;
		for (I = 1; I <= 8; I++)
		{
			for (J = 1; J <= 9; J++)
			{
				FCTo.FIELD[J][I] = FCFrom.FIELD[J][I];
				FCTo.FIGW[J][I]  = FCFrom.FIGW[J][I];
				FCTo.FIGR[J][I]  = FCFrom.FIGR[J][I];
			}
		}
		for (J = 1; J <= 9; J++)
		{
			FCTo.KINGW[J] = FCFrom.KINGW[J];
			FCTo.KINGR[J] = FCFrom.KINGR[J];
		}
		FCTo.IBW = FCFrom.IBW;
		FCTo.IBR = FCFrom.IBR;
		FCTo.IPW = FCFrom.IPW;
		FCTo.IPR = FCFrom.IPR;
		FCTo.IRW = FCFrom.IRW;
		FCTo.IRR = FCFrom.IRR;
		FCTo.FIGTW = FCFrom.FIGTW;
		FCTo.FIGTR = FCFrom.FIGTR;
		FCTo.KNGTW = FCFrom.KNGTW;
		FCTo.KNGTR = FCFrom.KNGTR;
		FCTo.COSTW = FCFrom.COSTW;
		FCTo.COSTR = FCFrom.COSTR;
		FCTo.COSTN = FCFrom.COSTN;
	}
void duell::Move(FieldCommon& MFld, int& IXO, int&IYO, int& IXN,
					int& IYN, int& DXI, int& DYI, int& IS, int& IRET)
	{
		// Moving of a figure, detatching of old relations and fixing of
		// new relations
		int I;
		// For all figures of white and black: b):=b)+a) and then a):=0 
		IRET = 0;
		MFld.IBW = 0;
		MFld.IBR = 0;
		MFld.IPW = 0;
		MFld.IPR = 0;
		MFld.IRW = 0;
		MFld.IRR = 0;
		IZW = 0;
		IZR = 0;
		IPWFL = FALSE;
		IPRFL = FALSE;
		ISWFL = FALSE;
		ISRFL = FALSE;
		IDWFL = FALSE;
		IDRFL = FALSE;
		ENDLP_M = FALSE;
		if (IS == 1)
			FigNoAct(1, MFld, IXO, IYO);
		else
			FigNoAct(-1, MFld, IXO, IYO);
		for (I = 1; I <= 8; I++)
		{
			if (MFld.FIGW[1][I] != 0)
			{
				MFld.FIGW[5][I] = MFld.FIGW[5][I] + MFld.FIGW[4][I];
				MFld.FIGW[4][I] = 0;
			}
			if (MFld.FIGR[1][I] != 0)
			{
				MFld.FIGR[5][I] = MFld.FIGR[5][I] + MFld.FIGR[4][I];
				MFld.FIGR[4][I] = 0;
			}
		}
		MFld.KINGW[5] = MFld.KINGW[5] + MFld.KINGW[4];
		MFld.KINGW[4] = 0;
		MFld.KINGW[8] = 0;
		MFld.KINGW[9] = 0;
		MFld.KINGR[5] = MFld.KINGR[5] + MFld.KINGR[4];
		MFld.KINGR[4] = 0;
		MFld.KINGR[8] = 0;
		MFld.KINGR[9] = 0;
		// Removing of all relations of the moving figure at the old position
		RemOldInsNew(-1, MFld, IXO, IYO, NRACT);
		// Remove figure from the old position but store old information
		HILFFL = NEWV(DXI, DYI, MFld.FIELD[IXO][IYO], IS);
		MFld.FIELD[IXO][IYO] = 0;
		if (IS == 1)
			RemFig(1, MFld);
		else
			RemFig(-1, MFld);
		// Update for the lines of the old position (figure not yet at the
		// new position)
		OldLineRemDANewLineInsDA(1, -1, MFld, IXO, IYO, NRACT);
		OldLineRemDANewLineInsDA(1, 1, MFld, IXO, IYO, NRACT);
		if (MFld.FIELD[IXN][IYN] == 0)
		{
			// Update for the lines of the new position (figure not yet at the
			// new position)
			OldLineRemDANewLineInsDA(-1, -1, MFld, IXN, IYN, NRACT);
			OldLineRemDANewLineInsDA(-1, 1, MFld, IXN, IYN, NRACT);
		}
		else
		{
			// Remove beated opposing figure from the new position
			ENDLP_M = FALSE;
			if (IS == 1)
			{
				FigNoBeat(1, MFld, IXN, IYN);
				if ((!W1FLAG) && (!W2FLAG))
					hold_wert = MFld.FIGR[7][-NRBEAT];
			}
			else
			{
				FigNoBeat(-1, MFld, IXN, IYN);
				if ((!W1FLAG) && (!W2FLAG))
					hold_wert = MFld.FIGW[7][NRBEAT];
			}
			RemOldInsNew(-1, MFld, IXN, IYN, NRBEAT);
			MFld.FIELD[IXN][IYN] = 0;
			if (NRBEAT > 0)
			{
				if (NRBEAT != 9)
					MFld.FIGW[1][NRBEAT] = 0;
				else
					MFld.KINGW[1] = 0;
			}
			else
			{
				if (NRBEAT != -9)
					MFld.FIGR[1][-NRBEAT] = 0;
				else
					MFld.KINGR[1] = 0;
			}
		}
		// Install figure at the new position and restore field information
		MFld.FIELD[IXN][IYN] = HILFFL;
		if (IS == 1)
			InsFig(1, MFld, IXN, IYN);
		else
			InsFig(-1, MFld, IXN, IYN);
		RemOldInsNew(1, MFld, IXN, IYN, NRACT);
		// Calculating of v) and w) for both kings, and then
		// for all figures where e) > d), building of a) of the opposing
		// figures and after that b) := b) - a), and of r) of the opposing
		// king and after that s) := s) - r)
		// for white
		TabvwabrsCalc(1, MFld);
		// for black
		TabvwabrsCalc(-1, MFld);
		// Computing of possible attacks and indirect defenses
		// for white
		AttDefCalc(1, MFld, IZW, IPWFL, ISWFL, IDWFL);
		// for black
		AttDefCalc(-1, MFld, IZR, IPRFL, ISRFL, IDRFL);
		// Final changes
		if ((IPWFL) && (IS == -1) && (MFld.IBR == 0))
			MFld.IPW = MFld.IPW + 1; // inc MFld.IPW
		if ((IPRFL) && (IS == 1) &&  (MFld.IBW == 0))
			MFld.IPR = MFld.IPR + 1; // inc MFld.IPR
		if ((MFld.IBW == 4) && (IZW >= IZR))
			MFld.IBW = MFld.IBW + 1; // inc MFld.IBW
		if ((MFld.IBW >= 4) && ((MFld.IPW+MFld.IRW) < (MFld.IPR+MFld.IRR)))
			MFld.IBW = MFld.IBW - 2; // 2*dec MFld.IBW
		if ((MFld.IBR == 4) && (IZR >= IZW))
			MFld.IBR = MFld.IBR + 1; // inc MFld.IBR
		if ((MFld.IBR >= 4) && ((MFld.IPR+MFld.IRR) < (MFld.IPW+MFld.IRW)))
			MFld.IBR = MFld.IBR - 2; // 2*dec MFld.IBR
		if (MFld.IPW < MFld.IRR)
			MFld.IRR = MFld.IPW;
		if (MFld.IPR < MFld.IRW)
			MFld.IRW = MFld.IPR;
	}
void duell::FigNoAct(int VORZ, FieldCommon& AFld, int& IXO, int& IYO)
	{
		int I, H1_I, H2_I, H3_I;
		NRACT = VORZ * 9;
		for (I = 1; I <= 8; I++)
		{
			if (VORZ == 1)
			{
				H1_I = AFld.FIGW[1][I];
				H2_I = AFld.FIGW[2][I];
				H3_I = AFld.FIGW[3][I];
			}
			else
			{
				H1_I = AFld.FIGR[1][I];
				H2_I = AFld.FIGR[2][I];
				H3_I = AFld.FIGR[3][I];
			}
			if ((!ENDLP_M) && (H1_I != 0) &&
				(IXO == H2_I) && (IYO == H3_I))
			{
				NRACT = VORZ * I;
				ENDLP_M = TRUE;
			}
		}
		if ((!W1FLAG) && (!W2FLAG))
			NRACT_hold = NRACT;
	}
void duell::RemFig(int VORZ, FieldCommon& RFld)
	{
		if (NRACT == (VORZ * 9))
		{
			if (VORZ == 1)
			{
				RFld.KINGW[2] = -6;
				RFld.KINGW[3] = -6;
			}
			else
			{
				RFld.KINGR[2] = -6;
				RFld.KINGR[3] = -6;
			}
		}
		else
		{
			if (VORZ == 1)
			{
				RFld.FIGW[2][NRACT] = -6;
				RFld.FIGW[3][NRACT] = -6;
			}
			else
			{
				RFld.FIGR[2][-NRACT] = -6;
				RFld.FIGR[3][-NRACT] = -6;
			}
		}
	}
void duell::InsFig(int VORZ, FieldCommon& IFld, int& IXN, int& IYN)
	{
		if (NRACT == (VORZ * 9))
		{
			if (VORZ == 1)
			{
				IFld.KINGW[2] = IXN;
				IFld.KINGW[3] = IYN;
			}
			else
			{
				IFld.KINGR[2] = IXN;
				IFld.KINGR[3] = IYN;
			}
		}
		else
		{
			if (VORZ == 1)
			{
				IFld.FIGW[2][NRACT] = IXN;
				IFld.FIGW[3][NRACT] = IYN;
			}
			else
			{
				IFld.FIGR[2][-NRACT] = IXN;
				IFld.FIGR[3][-NRACT] = IYN;
			}
		}
	}
void duell::FigNoBeat(int VORZ, FieldCommon& BFld, int& IXN, int& IYN)
	{
		int I, H1_I, H2_I, H3_I;
		NRBEAT = -(VORZ * 9);
		if (VORZ == 1)
			BFld.IBW = 4; // set BFld.IBW
		else
			BFld.IBR = 4; // set BFld.IBR
		for (I = 1; I <= 8; I++)
		{
			if (VORZ == -1)
			{
				H1_I = BFld.FIGW[1][I];
				H2_I = BFld.FIGW[2][I];
				H3_I = BFld.FIGW[3][I];
			}
			else
			{
				H1_I = BFld.FIGR[1][I];
				H2_I = BFld.FIGR[2][I];
				H3_I = BFld.FIGR[3][I];
			}
			if ((!ENDLP_M) && (H1_I != 0) &&
				(IXN == H2_I) && (IYN == H3_I))
			{
				NRBEAT = -(VORZ * I);
				ENDLP_M = TRUE;
			}
		}
		if (!ENDLP_M)
		{
			if (VORZ == 1)
				BFld.IBW = 100; // opposing king beated
			else
				BFld.IBR = 100; // opposing king beated
		}
		if ((!W1FLAG) && (!W2FLAG))
			NRBEAT_hold = NRBEAT;
	}
void duell::TabvwabrsCalc(int VORZ, FieldCommon& TFld)
	{
		int I, J;
		int H1_I, H7_I, H8_I, H1_J, K1;
		for (I = 1; I <= 9; I++)
		{
			JUMP_M = FALSE;
			if (I == 9)
			{
				if (VORZ == 1)
				{
					K1 = TFld.KINGW[1];
					WXM = TFld.KINGW[2];
					WYM = TFld.KINGW[3];
				}
				else
				{
					K1 = TFld.KINGR[1];
					WXM = TFld.KINGR[2];
					WYM = TFld.KINGR[3];
				}
				if (K1 == 0)
					IRET = VORZ * 15;
				if (VORZ == 1)
				{
					if ((WXM == 5) && (WYM == 8))
						IRET = -15;
				}
				else
				{
					if ((WXM == 5) && (WYM == 1))
						IRET = 15;
				}
			}
			else
			{
				if (VORZ == 1)
				{
					H1_I = TFld.FIGW[1][I];
					H7_I = TFld.FIGW[7][I];
					H8_I = TFld.FIGW[8][I];
				}
				else
				{
					H1_I = TFld.FIGR[1][I];
					H7_I = TFld.FIGR[7][I];
					H8_I = TFld.FIGR[8][I];
				}

				if ((H1_I == 0) || (H8_I <= H7_I))
					JUMP_M = TRUE;
				else
				{
					if (VORZ == 1)
					{
						WXM = TFld.FIGW[2][I];
						WYM = TFld.FIGW[3][I];
					}
					else
					{
						WXM = TFld.FIGR[2][I];
						WYM = TFld.FIGR[3][I];
					}
				}
			}
			if (!JUMP_M)
			{
				for (J = 1; J <= 8; J++)
				{
					if (VORZ == -1)
						H1_J = TFld.FIGW[1][J];
					else
						H1_J = TFld.FIGR[1][J];
					if (H1_J != 0)
					{
						if (VORZ == -1)
						{
							HXM = TFld.FIGW[2][J];
							HYM = TFld.FIGW[3][J];
						}
						else
						{
							HXM = TFld.FIGR[2][J];
							HYM = TFld.FIGR[3][J];
						}
						IDIST = abs(HXM-WXM) + abs(HYM-WYM);
						IVAL = - (VORZ * (TFld.FIELD[HXM][HYM] / 10));
						if (IDIST == IVAL)
						{
							if (I != 9)
							{
								if (FYX(TFld, WXM, WYM, HXM-WXM, HYM-WYM) ||
									FXY(TFld, WXM, WYM, HXM-WXM, HYM-WYM))
								{
									if (VORZ == -1)
									{
										// inc a) of opposing figure J
										TFld.FIGW[4][J] = TFld.FIGW[4][J] + 1;
										// dec b) of opposing figure J
										TFld.FIGW[5][J] = TFld.FIGW[5][J] - 1;
									}
									else
									{
										// inc a) of opposing figure J
										TFld.FIGR[4][J] = TFld.FIGR[4][J] + 1;
										// dec b) of opposing figure J
										TFld.FIGR[5][J] = TFld.FIGR[5][J] - 1;
									}
								}
							}
							else
							{
								FSXY = FALSE;
								FSYX = FALSE;
								if (WYM != HYM)
									FSXY = SXY(TFld, WXM, WYM, HXM-WXM, HYM-WYM, ISXY);
								if ((WYM == HYM) || ((WYM != HYM) && (WXM != HXM)))
									FSYX = SYX(TFld, WXM, WYM, HXM-WXM, HYM-WYM, ISYX);
								if (FSXY && (ISXY == -VORZ))
								{
									if (VORZ == 1)
										TFld.KINGW[8] = TFld.KINGW[8] + 1; // inc v)
									else
										TFld.KINGR[8] = TFld.KINGR[8] + 1; // inc v)
								}
								else if (FSXY && (ISXY == VORZ))
								{
									if (VORZ == 1)
										TFld.KINGW[9] = TFld.KINGW[9] + 1; // inc w)
									else
										TFld.KINGR[9] = TFld.KINGR[9] + 1; // inc w)
								}
								if (FSYX && (ISYX == -VORZ))
								{
									if (VORZ == 1)
										TFld.KINGW[8] = TFld.KINGW[8] + 1; // inc v)
									else
										TFld.KINGR[8] = TFld.KINGR[8] + 1; // inc v)
								}
								else if (FSYX && (ISYX == VORZ))
								{
									if (VORZ == 1)
										TFld.KINGW[9] = TFld.KINGW[9] + 1; // inc w)
									else
										TFld.KINGR[9] = TFld.KINGR[9] + 1; // inc w)
								}
							}
						}
					}
				}
				if (I != 9)
				{
					if (VORZ == -1)
					{
						HXM = TFld.KINGW[2];
						HYM = TFld.KINGW[3];
					}
					else
					{
						HXM = TFld.KINGR[2];
						HYM = TFld.KINGR[3];
					}
					IDIST = abs(HXM-WXM) + abs(HYM-WYM);
					if (IDIST == 1)
					{
						if (VORZ == -1)
						{
							TFld.KINGW[4] = TFld.KINGW[4] + 1; // inc r) of opposing king
							TFld.KINGW[5] = TFld.KINGW[5] - 1; // dec s) of opposing king
						}
						else
						{
							TFld.KINGR[4] = TFld.KINGR[4] + 1; // inc r) of opposing king
							TFld.KINGR[5] = TFld.KINGR[5] - 1; // dec s) of opposing king
						}
					}
				}
			}
		}
	}
void duell::AttDefCalc(int VORZ, FieldCommon& TFld, int& IZa,
                    bool& IPaFL, bool& ISaFL, bool& IDaFL)
	{
		int I, H1_I, H4_I, H6_I, H7_I, H8_I, K4, K6, K8, K9, IB;
		for (I = 1; I <= 9; I++)
		{
			if (I != 9)
			{
				if (VORZ == 1)
					H1_I = TFld.FIGW[1][I];
				else
					H1_I = TFld.FIGR[1][I];
				if (H1_I == 0)
				{
					if (VORZ == 1)
						IZW = IZW + 1;
					else
						IZR = IZR + 1;
				}
				else
				{
					if (VORZ == 1)
					{
						H4_I = TFld.FIGW[4][I];
						H6_I = TFld.FIGW[6][I];
						H7_I = TFld.FIGW[7][I];
						H8_I = TFld.FIGW[8][I];
						K6 = TFld.KINGW[6];
						K8 = TFld.KINGW[8];
						K9 = TFld.KINGW[9];
						IB = TFld.IBW;
					}
					else
					{
						H4_I = TFld.FIGR[4][I];
						H6_I = TFld.FIGR[6][I];
						H7_I = TFld.FIGR[7][I];
						H8_I = TFld.FIGR[8][I];
						K6 = TFld.KINGR[6];
						K8 = TFld.KINGR[8];
						K9 = TFld.KINGR[9];
						IB = TFld.IBR;
					}
					if ((H4_I != 0) && (H7_I >= H8_I))
					{
						if (VORZ == 1)
							TFld.IPW = TFld.IPW + 1; // inc TFld.IPW
						else
							TFld.IPR = TFld.IPR + 1; // inc TFld.IPR
					}
					if (VORZ == 1)
					{
						WXM = TFld.FIGW[2][I];
						WYM = TFld.FIGW[3][I];
					}
					else
					{
						WXM = TFld.FIGR[2][I];
						WYM = TFld.FIGR[3][I];
					}
					if (H8_I == (H7_I+1))
						LoopIRa(TFld, VORZ, I);
					if (H4_I != 0)
					{
						HILFFL = TFld.FIELD[WXM][WYM];
						TFld.FIELD[WXM][WYM] = 0;
						ENDLP_M = FALSE;
						JUMP_M = FALSE;
						LoopIPaMinus(TFld, VORZ, I);
						if (!JUMP_M)
						{
							IPaFL = TRUE;
							TFld.FIELD[WXM][WYM] = HILFFL;
							if ((((H8_I == H7_I) && (K9 >= 1)) ||
								((H8_I == (H7_I-1)) && (K9 >= 2))) &&
								(K6 == 0))
							{
								ISaFL = FALSE;
								JUMP_M = FALSE;
								LoopIPa(TFld, VORZ, I, ISaFL);
							}
						}
					}
					if ((K8 != 0) && (H8_I != 0) &&
						(!IDaFL) && (K6 == 0))
					{
						JUMP_M = FALSE;
						LoopIPb(TFld, VORZ, IDaFL);
					}
					if ((H6_I != 0) && (H7_I < H8_I) && (IB == 0))
					{
						if (VORZ == -1)
							TFld.IPW = TFld.IPW + 2; // 2*inc TFld.IPW
						else
							TFld.IPR = TFld.IPR + 2; // 2*inc TFld.IPR
					}
				}
			}
			else
			{
				if (VORZ == 1)
					K4 = TFld.KINGW[4];
				else
					K4 = TFld.KINGR[4];
				if (K4 != 0)
				{
					if (VORZ == 1)
						TFld.IPW = TFld.IPW + 1; // inc TFld.IPW
					else
						TFld.IPR = TFld.IPR + 1; // inc TFld.IPR
				}
			}
		}
	}
void duell::LoopIRa(FieldCommon& TFld, int& VORZ, int& I)
	{
		int J, H1_J;
		for (J = 1; J <= 9; J++)
		{
			JUMP_M = FALSE;
			if (J == 9)
			{
				if (VORZ == -1)
				{
					HXM = TFld.KINGW[2];
					HYM = TFld.KINGW[3];
				}
				else
				{
					HXM = TFld.KINGR[2];
					HYM = TFld.KINGR[3];
				}
				IVAL = 1;
			}
			else
			{
				if (VORZ == -1)
					H1_J = TFld.FIGW[1][J];
				else
					H1_J = TFld.FIGR[1][J];
				if (H1_J == 0)
					JUMP_M = TRUE;
				else
				{
					if (VORZ == -1)
					{
						HXM = TFld.FIGW[2][J];
						HYM = TFld.FIGW[3][J];
					}
					else
					{
						HXM = TFld.FIGR[2][J];
						HYM = TFld.FIGR[3][J];
					}
					IVAL = - (VORZ * (TFld.FIELD[HXM][HYM] / 10));
				}
			}
			if (!JUMP_M)
			{
				IDIST = abs(WXM-HXM) + abs(WYM-HYM);
				if (IDIST == IVAL)
				{
					if (FXY(TFld, HXM, HYM, WXM-HXM, WYM-HYM) ||
						FYX(TFld, HXM, HYM, WXM-HXM, WYM-HYM))
						LoopIRaPlus(TFld, VORZ, I, J);
				}
			}
		}
	}
void duell::LoopIRaPlus(FieldCommon& TFld, int& VORZ, int& I, int& J)
	{
		int K, H1_K, K6, K9;
		bool Jump;
		for (K = 1; K <= 8; K++)
		{
			if (VORZ == 1)
				H1_K = TFld.FIGW[1][K];
			else
				H1_K = TFld.FIGR[1][K];
			if ((K != I) && (H1_K != 0))
			{
				if (VORZ == 1)
				{
					ITX = TFld.FIGW[2][K];
					ITY = TFld.FIGW[3][K];
				}
				else
				{
					ITX = TFld.FIGR[2][K];
					ITY = TFld.FIGR[3][K];
				}
				if ((ITX == HXM) || (ITY = HYM))
				{
					IDIST = abs(WXM-ITX) + abs(WYM-ITY);
					if (IDIST > IVAL)
					{
						IVALN = VORZ * (TFld.FIELD[ITX][ITY] / 10);
						if (IDIST == IVALN)
						{
							Jump = FALSE;
							if (ITX != HXM)
							{
								if (SXY(TFld, ITX, ITY, WXM-ITX, WYM-ITY, ISXY))
								{
									if (FYX(TFld, ITX, ITY, WXM-ITX, WYM-ITY))
										Jump = TRUE;
								}
								else
									Jump = TRUE;
							}
							else
							{
								if (SYX(TFld, ITX, ITY, WXM-ITX, WYM-ITY, ISYX))
								{
									if (FXY(TFld, ITX, ITY, WXM-ITX, WYM-ITY))
										Jump = TRUE;
								}
								else
									Jump = TRUE;
							}
							if (!Jump)
							{
								if (VORZ == 1)
								{
									TFld.IRW = TFld.IRW + 1; // inc TFld.IRW
									K6 = TFld.KINGW[6];
									K9 = TFld.KINGW[9];
								}
								else
								{
									TFld.IRR = TFld.IRR + 1; // inc TFld.IRR
									K6 = TFld.KINGR[6];
									K9 = TFld.KINGR[9];
								}
								if ((K9 != 0) && (K6 == 0))
								{
									HILFFL = TFld.FIELD[ITX][ITY];
									TFld.FIELD[ITX][ITY] = 0;
									ENDLP_M = FALSE;
									LoopIRaMinus(TFld, VORZ, I, J);
									TFld.FIELD[ITX][ITY] = HILFFL;
								}
							}
						}
					}
				}
			}
		}
	}
void duell::LoopIRaMinus(FieldCommon& TFld, int& VORZ, int& I, int& J)
	{
		int L, H1_L;
		for (L = 1; L <= 8; L++)
		{
			if (VORZ == -1)
				H1_L = TFld.FIGW[1][L];
			else
				H1_L = TFld.FIGR[1][L];
			if ((!ENDLP_M) && (L != J) && (H1_L != 0))
			{
				if (VORZ == -1)
				{
					ILX = TFld.FIGW[2][L];
					ILY = TFld.FIGW[3][L];
				}
				else
				{
					ILX = TFld.FIGR[2][L];
					ILY = TFld.FIGR[3][L];
				}
				IVALN = - (VORZ * (TFld.FIELD[ILX][ILY] / 10));
				if (VORZ == 1)
				{
					IKX = TFld.KINGW[2];
					IKY = TFld.KINGW[3];
				}
				else
				{
					IKX = TFld.KINGR[2];
					IKY = TFld.KINGR[3];
				}
				IDIST = abs(IKX-ILX) + abs(IKY-ILY);
				if ((IDIST == IVALN))
				{
					if (FXY(TFld, ILX, ILY, IKX-ILX, IKY-ILY) ||
						FYX(TFld, ILX, ILY, IKX-ILX, IKY-ILY))
					{
						if (VORZ == 1)
							TFld.IRW = TFld.IRW - 1; // dec TFld.IRW
						else
							TFld.IRR = TFld.IRR - 1; // dec TFld.IRR
						ENDLP_M = TRUE;
					}
				}
			}
		}
	}
void duell::LoopIPaMinus(FieldCommon& TFld, int& VORZ, int& I)
	{
		int L, H1_L, H7_I, H8_I, K6;
		for (L = 1; L <= 8; L++)
		{
			if (VORZ == -1)
				H1_L = TFld.FIGW[1][L];
			else
				H1_L = TFld.FIGR[1][L];
			if ((!JUMP_M) && (!ENDLP_M) && (H1_L != 0))
			{
				if (VORZ == -1)
				{
					ILX = TFld.FIGW[2][L];
					ILY = TFld.FIGW[3][L];
				}
				else
				{
					ILX = TFld.FIGR[2][L];
					ILY = TFld.FIGR[3][L];
				}
				IVAL = - (VORZ * (TFld.FIELD[ILX][ILY] / 10));
				if (VORZ == 1)
				{
					IKX = TFld.KINGW[2];
					IKY = TFld.KINGW[3];
				}
				else
				{
					IKX = TFld.KINGR[2];
					IKY = TFld.KINGR[3];
				}
				IDIST = abs(IKX-ILX) + abs(IKY-ILY);
				if (IDIST == IVAL)
				{
					if (FXY(TFld, ILX, ILY, IKX-ILX, IKY-ILY) ||
						FYX(TFld, ILX, ILY, IKX-ILX, IKY-ILY))
					{
						if (VORZ == 1)
						{
							H7_I = TFld.FIGW[7][I];
							H8_I = TFld.FIGW[8][I];
							K6 = TFld.KINGW[6];
						}
						else
						{
							H7_I = TFld.FIGR[7][I];
							H8_I = TFld.FIGR[8][I];
							K6 = TFld.KINGR[6];
						}
						if ((H7_I < H8_I) || (K6 != 0))
							ENDLP_M = TRUE;
						else
						{
							if (VORZ == 1)
								TFld.IPW = TFld.IPW - 1; // dec TFld.IPW
							else
								TFld.IPR = TFld.IPR - 1; // dec TFld.IPR
							TFld.FIELD[WXM][WYM] = HILFFL;
							ENDLP_M = TRUE;
							JUMP_M = TRUE;
						}
					}
				}
			}
		}
	}
void duell::LoopIPa(FieldCommon& TFld, int& VORZ, int& I, bool& ISaFL)
	{
		int K, H1_K;
		for (K = 1; K <= 8; K++)
		{
			if (VORZ == 1)
				H1_K = TFld.FIGW[1][K];
			else
				H1_K = TFld.FIGR[1][K];
			if ((!JUMP_M) && (K != I) && (H1_K != 0))
			{
				if (VORZ == 1)
				{
					ITX = TFld.FIGW[2][K];
					ITY = TFld.FIGW[3][K];
				}
				else
				{
					ITX = TFld.FIGR[2][K];
					ITY = TFld.FIGR[3][K];
				}
				IVAL = VORZ * (TFld.FIELD[ITX][ITY] / 10);
				IDIST = abs(WXM-ITX) + abs(WYM-ITY);
				if (IDIST == IVAL)
				{
					if (FXY(TFld, ITX, ITY, WXM-ITX, WYM-ITY) ||
						FYX(TFld, ITX, ITY, WXM-ITX, WYM-ITY))
					{
						HILFFL = TFld.FIELD[ITX][ITY];
						TFld.FIELD[ITX][ITY] = 0;
						ENDLP_M = FALSE;
						LoopIPaPlus(TFld, VORZ, I, ISaFL);
						if (!ENDLP_M)
							TFld.FIELD[ITX][ITY] = HILFFL;
					}
				}
			}
		}
	}
void duell::LoopIPaPlus(FieldCommon& TFld, int& VORZ, int& I, bool& ISaFL)
	{
		int L, H1_L, H7_I, H8_I, K9;
		for (L = 1; L <= 8; L++)
		{
			if (VORZ == -1)
				H1_L = TFld.FIGW[1][L];
			else
				H1_L = TFld.FIGR[1][L];
			if ((!ENDLP_M) && (H1_L != 0))
			{
				if (VORZ == -1)
				{
					ILX = TFld.FIGW[2][L];
					ILY = TFld.FIGW[3][L];
				}
				else
				{
					ILX = TFld.FIGR[2][L];
					ILY = TFld.FIGR[3][L];
				}
				IVAL = - (VORZ * (TFld.FIELD[ILX][ILY] / 10));
				if (VORZ == 1)
				{
					IKX = TFld.KINGW[2];
					IKY = TFld.KINGW[3];
				}
				else
				{
					IKX = TFld.KINGR[2];
					IKY = TFld.KINGR[3];
				}
				IDIST = abs(IKX-ILX) + abs(IKY-ILY);
				if (IDIST == IVAL)
				{
					if (FXY(TFld, ILX, ILY, IKX-ILX, IKY-ILY) ||
						FYX(TFld, ILX, ILY, IKX-ILX, IKY-ILY))
					{
						if (VORZ == 1)
							TFld.IPW = TFld.IPW - 1; // dec TFld.IPW
						else
							TFld.IPR = TFld.IPR - 1; // dec TFld.IPR
						TFld.FIELD[ITX][ITY] = HILFFL;
						if (VORZ == 1)
						{
							H7_I = TFld.FIGW[7][I];
							H8_I = TFld.FIGW[8][I];
							K9 = TFld.KINGW[9];
						}
						else
						{
							H7_I = TFld.FIGR[7][I];
							H8_I = TFld.FIGR[8][I];
							K9 = TFld.KINGR[9];
						}
						if ((H8_I == (H7_I-1))
							&& (K9 >= 2) && (!ISaFL))
						{
							if (VORZ == 1)
								TFld.IPW = TFld.IPW + 1; // inc TFld.IPW
							else
								TFld.IPR = TFld.IPR + 1; // inc TFld.IPR
							ISaFL = TRUE;
							ENDLP_M = TRUE;
						}
						else
						{
							ENDLP_M = TRUE;
							JUMP_M = TRUE;
						}
					}
				}
			}
		}
	}
void duell::LoopIPb(FieldCommon& TFld, int& VORZ, bool& IDaFL)
	{
		int K, H1_K;
		for (K = 1; K <= 8; K++)
		{
			if (VORZ == -1)
				H1_K = TFld.FIGW[1][K];
			else
				H1_K = TFld.FIGR[1][K];
			if ((!JUMP_M) && (H1_K != 0))
			{
				if (VORZ == -1)
				{
					ITX = TFld.FIGW[2][K];
					ITY = TFld.FIGW[3][K];
				}
				else
				{
					ITX = TFld.FIGR[2][K];
					ITY = TFld.FIGR[3][K];
				}
				IVAL = - (VORZ * (TFld.FIELD[ITX][ITY] / 10));
				IDIST = abs(WXM-ITX) + abs(WYM-ITY);
				if (IDIST == IVAL)
				{
					if (FXY(TFld, ITX, ITY, WXM-ITX, WYM-ITY) ||
						FYX(TFld, ITX, ITY, WXM-ITX, WYM-ITY))
					{
						HILFFL = TFld.FIELD[ITX][ITY];
						TFld.FIELD[ITX][ITY] = 0;
						ENDLP_M = FALSE;
						LoopIPbPlus(TFld, VORZ, K, IDaFL);
						if (!ENDLP_M)
							TFld.FIELD[ITX][ITY] = HILFFL;
					}
				}
			}
		}
	}
void duell::LoopIPbPlus(FieldCommon& TFld, int& VORZ, int& K, bool& IDaFL)
	{
		int L, H1_L;
		for (L = 1; L <= 8; L++)
		{
			if (VORZ == -1)
				H1_L = TFld.FIGW[1][L];
			else
				H1_L = TFld.FIGR[1][L];
			if ((!ENDLP_M) && (L != K) && (H1_L != 0))
			{
				if (VORZ == -1)
				{
					ILX = TFld.FIGW[2][L];
					ILY = TFld.FIGW[3][L];
				}
				else
				{
					ILX = TFld.FIGR[2][L];
					ILY = TFld.FIGR[3][L];
				}
				IVAL = - (VORZ * (TFld.FIELD[ILX][ILY] / 10));
				if (VORZ == 1)
				{
					IKX = TFld.KINGW[2];
					IKY = TFld.KINGW[3];
				}
				else
				{
					IKX = TFld.KINGR[2];
					IKY = TFld.KINGR[3];
				}
				IDIST = abs(IKX-ILX) + abs(IKY-ILY);
				if (IDIST == IVAL)
				{
					if (FXY(TFld, ILX, ILY, IKX-ILX, IKY-ILY) ||
						FYX(TFld, ILX, ILY, IKX-ILX, IKY-ILY))
					{
						TFld.FIELD[ITX][ITY] = HILFFL;
						if (VORZ == -1)
							TFld.IPW = TFld.IPW + 1; // inc TFld.IPW
						else
							TFld.IPR = TFld.IPR + 1; // inc TFld.IPR
						IDaFL = TRUE;
						ENDLP_M = TRUE;
						JUMP_M = TRUE;
					}
				}
			}
		}
	}
bool duell::SXY(FieldCommon& SFld, int IXF, int IYF, int IX, int IY, int& ISXY)
	{
		// Checks if the way over the x-y-line is occupied
		// only by one own or one opposing figure
		int ICOUNT;
		bool RES, JUMP;
		unsigned int I, IFROM;
		JUMP = FALSE;
		ISXY = 0;
		ICOUNT = 0;
		if (!((IX == 0) || (IX == 1) || (IX == -1)))
		{
			for (I = 1; I <= (unsigned int)(abs(IX)-1); I++)
			{
				if ((!JUMP) && (SFld.FIELD[IXF+ISIGN(I,IX)][IYF] != 0))
				{
					if (SFld.FIELD[IXF+ISIGN(I,IX)][IYF] > 0)
						ISXY = 1;
					else
						ISXY = -1;
					ICOUNT = ICOUNT + 1;
					if (ICOUNT > 1)
						JUMP = TRUE;
				}
			}
		}
		if (!JUMP)
		{
			if (IY != 0)
			{
				if (!((IX == 0) && ((IY == 1) || (IY == -1))))
				{
					if (IX == 0)
						IFROM = 1;
					else
						IFROM = 0;
					for (I = IFROM; I <= (unsigned int)(abs(IY)-1); I++)
					{
						if ((!JUMP) && (SFld.FIELD[IXF+IX][IYF+ISIGN(I,IY)] != 0))
						{
							if (SFld.FIELD[IXF+IX][IYF+ISIGN(I,IY)] > 0)
								ISXY = 1;
							else
								ISXY = -1;
							ICOUNT = ICOUNT + 1;
							if (ICOUNT > 1)
								JUMP = TRUE;
						}
					}
					if ((!JUMP) && (ICOUNT != 0))
						RES = TRUE;
					else
						RES = FALSE;
				}
				else
					RES = FALSE;
			}
			else
			{
				if ((IX == 1) || (IX == -1))
					RES = FALSE;
				else
					RES = TRUE;
			}
		}
		else
			RES = FALSE;
		return RES;
	}
bool duell::SYX(FieldCommon& SFld, int IXF, int IYF, int IX, int IY, int& ISYX)
	{
		// Checks if the way over the y-x-line is occupied
		// only by one own or one opposing figure
		int ICOUNT;
		bool RES, JUMP;
		unsigned int I, IFROM;
		JUMP = FALSE;
		ISYX = 0;
		ICOUNT = 0;
		if (!((IY == 0) || (IY == 1) || (IY == -1)))
		{
			for (I = 1; I <= (unsigned int)(abs(IY)-1); I++)
			{
				if ((!JUMP) && (SFld.FIELD[IXF][IYF+ISIGN(I,IY)] != 0))
				{
					if (SFld.FIELD[IXF][IYF+ISIGN(I,IY)] > 0)
						ISYX = 1;
					else
						ISYX = -1;
					ICOUNT = ICOUNT + 1;
					if (ICOUNT > 1)
						JUMP = TRUE;
				}
			}
		}
		if (!JUMP)
		{
			if (IX != 0)
			{
				if (!((IY == 0) && ((IX == 1) || (IX == -1))))
				{
					if (IY == 0)
						IFROM = 1;
					else
						IFROM = 0;
					for (I = IFROM; I <= (unsigned int)(abs(IX)-1); I++)
					{
						if ((!JUMP) && (SFld.FIELD[IXF+ISIGN(I,IX)][IYF+IY] != 0))
						{
							if (SFld.FIELD[IXF+ISIGN(I,IX)][IYF+IY] > 0)
								ISYX = 1;
							else
								ISYX = -1;
							ICOUNT = ICOUNT + 1;
							if (ICOUNT > 1)
								JUMP = TRUE;
						}
					}
					if ((!JUMP) && (ICOUNT != 0))
						RES = TRUE;
					else
						RES = FALSE;
				}
				else
					RES = FALSE;
			}
			else
			{
				if ((IY == 1) || (IY == -1))
					RES = FALSE;
				else
					RES = TRUE;
			}
		}
		else
			RES = FALSE;
		return RES;
	}
void duell::RemOldInsNew(int RI, FieldCommon& OFld, int& IXc, int& IYc, int& NR)
	{
		// RI = -1 : Removing of all relations of the moving figure
		//			 at the old position
		// RI = +1 : Install figure at the new position and build new
		//			 relations
		// 1) to the own figures and the own king
		if (NR > 0)
		// white
			OwnRel(1, OFld, IXc, IYc, NR, RI);
		else
		// black
			OwnRel(-1, OFld, IXc, IYc, NR, RI);
		// 2) to the opposing figures and the opposing king
		if (NR > 0)
		// white
			OppRel(1, OFld, IXc, IYc, NR, RI);
		else
		// black
			OppRel(-1, OFld, IXc, IYc, NR, RI);
	}
void duell::DistVal(int Variant, int I, int& VORZ, FieldCommon& DFld,
						int& IXc, int& IYc, int& NR, int& RI)
	{
		bool JUMP, jump;
		if (IDIST == IVAL)
		{
			JUMP = FALSE;
		    jump = FALSE;
			if (HXE != IXc)
			{
				if (FXY(DFld, IXc, IYc, HXE-IXc, HYE-IYc))
					jump = TRUE;
				if ((HYE == IYc) && (!jump))
					JUMP = TRUE;
			}
			if ((!JUMP) && (!jump))
			{
				if (!FYX(DFld, IXc, IYc, HXE-IXc, HYE-IYc))
					JUMP = TRUE;
			}
			if (!JUMP)
			{
				if (Variant == 1)
				{
					if (VORZ == 1)
					{
						// dec or inc own d)
						DFld.FIGW[7][NR] = DFld.FIGW[7][NR] + RI;
						// dec or inc own f) of fig I
						DFld.FIGW[9][I] = DFld.FIGW[9][I] + RI;
					}
					else
					{
						// dec or inc own d)
						DFld.FIGR[7][-NR] = DFld.FIGR[7][-NR] + RI;
						// dec or inc own f) of fig I
						DFld.FIGR[9][I] = DFld.FIGR[9][I] + RI;
					}
				}
				else if (Variant == 2)
				{
					if (VORZ == 1)
					{
						// dec or inc own f)
						DFld.FIGW[9][NR] = DFld.FIGW[9][NR] + RI;
						// dec or inc own d) of fig I
						DFld.FIGW[7][I] = DFld.FIGW[7][I] + RI;
					}
					else
					{
						// dec or inc own f)
						DFld.FIGR[9][-NR] = DFld.FIGR[9][-NR] + RI;
						// dec or inc own d) of fig I
						DFld.FIGR[7][I] = DFld.FIGR[7][I] + RI;
					}
				}
				else if (Variant == 3)
				{
					if (VORZ == 1)
					{
						// dec or inc b) of opposing figure I
						DFld.FIGR[5][I] = DFld.FIGR[5][I] + RI;
						// dec or inc own e)
						DFld.FIGW[8][NR] = DFld.FIGW[8][NR] + RI;
					}
					else
					{
						// dec or inc b) of opposing figure I
						DFld.FIGW[5][I] = DFld.FIGW[5][I] + RI;
						// dec or inc own e)
						DFld.FIGR[8][-NR] = DFld.FIGR[8][-NR] + RI;
					}
				}
				else if (Variant == 4)
				{
					if (VORZ == 1)
					{
						// dec or inc e) of opposing figure I
						DFld.FIGR[8][I] = DFld.FIGR[8][I] + RI;
						// dec or inc own b)
						DFld.FIGW[5][NR] = DFld.FIGW[5][NR] + RI;
					}
					else
					{
						// dec or inc e) of opposing figure I
						DFld.FIGW[8][I] = DFld.FIGW[8][I] + RI;
						// dec or inc own b)
						DFld.FIGR[5][-NR] = DFld.FIGR[5][-NR] + RI;
					}
				}
			}
		}
	}
void duell::OwnRel(int VORZ, FieldCommon& RFld,
					int& IXc, int& IYc, int& NR, int& RI)
	{
		int I, H1_I, K2, K3;
		if (VORZ*NR != 9)
		{
			if (VORZ == 1)
			{
				K2 = RFld.KINGW[2];
				K3 = RFld.KINGW[3];
			}
			else
			{
				K2 = RFld.KINGR[2];
				K3 = RFld.KINGR[3];
			}
			if ((((K2 == IXc+1) || (K2 == IXc-1)) &&
				(K3 == IYc)) || ((K2 == IXc) &&
				((K3 == IYc+1) || (K3 == IYc-1))))
			{
				if (VORZ == 1)
				{
					// dec or inc own u)
					RFld.KINGW[7] = RFld.KINGW[7] + RI;
					// dec or inc own d)
					RFld.FIGW[7][NR] = RFld.FIGW[7][NR] + RI;
				}
				else
				{
					// dec or inc own u)
					RFld.KINGR[7] = RFld.KINGR[7] + RI;
					// dec or inc own d)
					RFld.FIGR[7][-NR] = RFld.FIGR[7][-NR] + RI;
				}
			}
			for (I = 1; I <= 8; I++)
			{
				if (VORZ == 1)
					H1_I = RFld.FIGW[1][I];
				else
					H1_I = RFld.FIGR[1][I];
				if ((VORZ*NR != I) && (H1_I != 0))
				{
					if (VORZ == 1)
					{
						HXE = RFld.FIGW[2][I];
						HYE = RFld.FIGW[3][I];
					}
					else
					{
						HXE = RFld.FIGR[2][I];
						HYE = RFld.FIGR[3][I];
					}
					IDIST = abs(HXE-IXc) + abs(HYE-IYc);
					IVAL = VORZ * (RFld.FIELD[HXE][HYE] / 10);
					DistVal(1, I, VORZ, RFld, IXc, IYc, NR, RI);
					IVAL = VORZ * (RFld.FIELD[IXc][IYc] / 10);
					DistVal(2, I, VORZ, RFld, IXc, IYc, NR, RI);
				}
			}
		}
		else
		{
			if (RI == -1)
			{
				if (VORZ == 1)
					RFld.KINGW[7] = 0; // own u) to zero
				else
					RFld.KINGR[7] = 0; // own u) to zero
			}
			for (I = 1; I <= 8; I++)
			{
				if (VORZ == 1)
					H1_I = RFld.FIGW[1][I];
				else
					H1_I = RFld.FIGR[1][I];
				if (H1_I != 0)
				{
					if (VORZ == 1)
					{
						HXE = RFld.FIGW[2][I];
						HYE = RFld.FIGW[3][I];
					}
					else
					{
						HXE = RFld.FIGR[2][I];
						HYE = RFld.FIGR[3][I];
					}
					IDIST = abs(HXE-IXc) + abs(HYE-IYc);
					if (IDIST == 1)
					{
						if (VORZ == 1)
							// dec or inc own d) of figure I
							RFld.FIGW[7][I] = RFld.FIGW[7][I] + RI;
						else
							// dec or inc own d) of figure I
							RFld.FIGR[7][I] = RFld.FIGR[7][I] + RI;
						if (RI == 1)
						{
							if (VORZ == 1)
								// inc own u)
								RFld.KINGW[7] = RFld.KINGW[7] + 1;
							else
								// inc own u)
								RFld.KINGR[7] = RFld.KINGR[7] + 1;
						}
					}
				}
			}
		}  
	}
void duell::OppRel(int VORZ, FieldCommon& RFld,
					int& IXc, int& IYc, int& NR, int& RI)
	{
		int I, H6, K2, K3, H1_I;
		bool Jump;
		if (VORZ*NR != 9)
		{
			if (VORZ == -1)
			{
				K2 = RFld.KINGW[2];
				K3 = RFld.KINGW[3];
			}
			else
			{
				K2 = RFld.KINGR[2];
				K3 = RFld.KINGR[3];
			}
			if ((((K2 == IXc+1) || (K2 == IXc-1)) &&
				(K3 == IYc)) || ((K2 == IXc) &&
				((K3 == IYc+1) || (K3 == IYc-1))))
			{
				if (VORZ == 1)
				{
					// dec or inc opposing s)
					RFld.KINGR[5] = RFld.KINGR[5] + RI;
					// dec or inc own e)
					RFld.FIGW[8][NR] = RFld.FIGW[8][NR] + RI;
				}
				else
				{
					// dec or inc opposing s)
					RFld.KINGW[5] = RFld.KINGW[5] + RI;
					// dec or inc own e)
					RFld.FIGR[8][-NR] = RFld.FIGR[8][-NR] + RI;
				}
			}
			if (RI == -1)
			{
				if (VORZ == 1)
					H6 = RFld.FIGW[6][NR];
				else
					H6 = RFld.FIGR[6][-NR];
				if (H6 != 0)
				{
					if (VORZ == 1)
					{
						// own c) to zero
						RFld.FIGW[6][NR] = 0;
						// dec t) of opposing king
						RFld.KINGR[6] = RFld.KINGR[6] - 1;
					}
					else
					{
						// own c) to zero
						RFld.FIGR[6][-NR] = 0;
						// dec t) of opposing king
						RFld.KINGW[6] = RFld.KINGW[6] - 1;
					}
				}
			}
			else if (RI == 1)
			{
				if (VORZ == -1)
				{
					XKE = RFld.KINGW[2];
					YKE = RFld.KINGW[3];
				}
				else
				{
					XKE = RFld.KINGR[2];
					YKE = RFld.KINGR[3];
				}
				IVAL = VORZ * (RFld.FIELD[IXc][IYc] / 10);
				IDIST = abs(XKE-IXc) + abs(YKE-IYc);
				if (IVAL == IDIST)
				{
					if (FYX(RFld, IXc, IYc, XKE-IXc, YKE-IYc) ||
						FXY(RFld, IXc, IYc, XKE-IXc, YKE-IYc))
					{
						if ((IXc != XKE) && (IYc != YKE))
						{
							if (FYX(RFld, IXc, IYc, XKE-IXc, YKE-IYc) &&
								FXY(RFld, IXc, IYc, XKE-IXc, YKE-IYc))
							{
								if (VORZ == 1)
									// inc own c) for 2-way DUELL
									RFld.FIGW[6][NR] = RFld.FIGW[6][NR] + 1;
								else
									// inc own c) for 2-way DUELL
									RFld.FIGR[6][-NR] = RFld.FIGR[6][-NR] + 1;
							}
						}
						if (VORZ == 1)
						{
							// inc own c)
							RFld.FIGW[6][NR] = RFld.FIGW[6][NR] + 1;
							// inc t) of opposing king
							RFld.KINGR[6] = RFld.KINGR[6] + 1;
						}
						else
						{
							// inc own c)
							RFld.FIGR[6][-NR] = RFld.FIGR[6][-NR] + 1;
							// inc t) of opposing king
							RFld.KINGW[6] = RFld.KINGW[6] + 1;
						}
					}
				}
			}
			for (I = 1; I <= 8; I++)
			{
				Jump = FALSE;
				if (VORZ == -1)
					H1_I = RFld.FIGW[1][I];
				else
					H1_I = RFld.FIGR[1][I];
				if (H1_I != 0)
				{
					if (VORZ == -1)
					{
						HXE = RFld.FIGW[2][I];
						HYE = RFld.FIGW[3][I];
					}
					else
					{
						HXE = RFld.FIGR[2][I];
						HYE = RFld.FIGR[3][I];
					}
					if ((HXE != -6) && (HYE != -6))
						IVAL = - VORZ * (RFld.FIELD[HXE][HYE] / 10);
					else
						Jump = TRUE;
				}
				else
					Jump = TRUE;
				if (!Jump)
				{
					IDIST = abs(HXE-IXc) + abs(HYE-IYc);
					DistVal(3, I, VORZ, RFld, IXc, IYc, NR, RI);
					IVAL = VORZ * (RFld.FIELD[IXc][IYc] / 10);
					DistVal(4, I, VORZ, RFld, IXc, IYc, NR, RI);
				}
			}
		}
		else
		{
			if (RI == -1)
			{
				if (VORZ == 1)
				{
					RFld.KINGW[5] = 0; // own s) to zero
					RFld.KINGW[6] = 0; // own t) to zero
				}
				else
				{
					RFld.KINGR[5] = 0; // own s) to zero
					RFld.KINGR[6] = 0; // own t) to zero
				}
			}
			for (I = 1; I <= 8; I++)
			{
				if (VORZ == -1)
					H1_I = RFld.FIGW[1][I];
				else
					H1_I = RFld.FIGR[1][I];
				if (H1_I != 0)
				{
					if (RI == -1)
					{
						if (VORZ == -1)
							// c) of opposing figure I to zero
							RFld.FIGW[6][I] = 0;
						else
							// c) of opposing figure I to zero
							RFld.FIGR[6][I] = 0;
					}
					if (VORZ == -1)
					{
						HXE = RFld.FIGW[2][I];
						HYE = RFld.FIGW[3][I];
					}
					else
					{
						HXE = RFld.FIGR[2][I];
						HYE = RFld.FIGR[3][I];
					}
					IDIST = abs(HXE-IXc) + abs(HYE-IYc);
					if (IDIST == 1)
					{
						if (VORZ == -1)
							// dec or inc e) of opposing figure I
							RFld.FIGW[8][I] = RFld.FIGW[8][I] + RI;
						else
							// dec or inc e) of opposing figure I
							RFld.FIGR[8][I] = RFld.FIGR[8][I] + RI;
						if (RI == 1)
						{
							if (VORZ == 1)
								// inc own s)
								RFld.KINGW[5] = RFld.KINGW[5] + 1;
							else
								// inc own s)
								RFld.KINGR[5] = RFld.KINGR[5] + 1;
						}
					}
					if (RI == 1)
					{
						IVAL = - VORZ * (RFld.FIELD[HXE][HYE] / 10);
						if (IDIST == IVAL)
						{
							if ((IXc != HXE) && ( IYc != HYE))
							{
								if (FYX(RFld, HXE, HYE, IXc-HXE, IYc-HYE) &&
									FXY(RFld, HXE, HYE, IXc-HXE, IYc-HYE))
								{
									if (VORZ == -1)
										// inc c) of opposing fig I for 2-way DUELL
										RFld.FIGW[6][I] = RFld.FIGW[6][I] + 1;
									else
										// inc c) of opposing fig I for 2-way DUELL
										RFld.FIGR[6][I] = RFld.FIGR[6][I] + 1;
								}
							}
							if (FYX(RFld, HXE, HYE, IXc-HXE, IYc-HYE) ||
								FXY(RFld, HXE, HYE, IXc-HXE, IYc-HYE))
							{
								if (VORZ == 1)
								{
									// inc c) of opposing figure I
									RFld.FIGR[6][I] = RFld.FIGR[6][I] + 1;
									// inc t) of own king
									RFld.KINGW[6] = RFld.KINGW[6] + 1;
								}
								else
								{
									// inc c) of opposing figure I
									RFld.FIGW[6][I] = RFld.FIGW[6][I] + 1;
									// inc t) of own king
									RFld.KINGR[6] = RFld.KINGR[6] + 1;
								}
							}
						}
					}
				}
			}
			if (RI == 1)
			{
				if (VORZ == -1)
				{
					XKE = RFld.KINGW[2];
					YKE = RFld.KINGW[3];
				}
				else
				{
					XKE = RFld.KINGR[2];
					YKE = RFld.KINGR[3];
				}
				if (((IXc == XKE) && ((IYc == YKE+1) || (IYc == YKE-1))) ||
					((IYc == YKE) && ((IXc == XKE+1) || (IXc == XKE-1))))
				{
					if (VORZ == 1)
						// inc t) of own king
						RFld.KINGW[6] = RFld.KINGW[6] + 1;
					else
						// inc t) of own king
						RFld.KINGR[6] = RFld.KINGR[6] + 1;
				}
			}
		}
	}
void duell::OldLineRemDANewLineInsDA(int RI, int DA, FieldCommon& LFld,
									  int& IXc, int& IYc, int& NR)
	{
		// Update for the lines of the old or new position (figure not yet at the
		// new position)
		// RI = +1 : Remove update ;   RI = -1 : Install update ;
		// DA = -1 : Defend update ;   DA = +1 : Attack  update
		int I;
		// Update for the line IXc
		// Lower IXc-Line Part
		if (IXc != 1)
		{
			ENDLP_D = FALSE;
			for (I = (IXc-1); I >= 1; I--)
			{
				if ((!ENDLP_D) && (LFld.FIELD[I][IYc] != 0))
				{
					if (LFld.FIELD[I][IYc] > 0)
						// white
						XLineTest(-1, 1, LFld, I, RI, DA, IXc, IYc, NR);
					else
						// black
						XLineTest(-1, -1, LFld, I, RI, DA, IXc, IYc, NR);
				}
			}
		}
		// Higher IXc-Line Part
		if (IXc != 9)
		{
			ENDLP_D = FALSE;
			for (I = (IXc+1); I <= 9; I++)
			{
				if ((!ENDLP_D) && (LFld.FIELD[I][IYc] != 0))
				{
					if (LFld.FIELD[I][IYc] > 0)
						// white
						XLineTest(1, 1, LFld, I, RI, DA, IXc, IYc, NR);
					else
						// black
						XLineTest(1, -1, LFld, I, RI, DA, IXc, IYc, NR);
				}
			}
		}
		// Update for the line IYc
		// Lower IYc-Line Part
		if (IYc != 1)
		{
			ENDLP_D = FALSE;
			for (I = (IYc-1); I >= 1; I--)
			{
				if ((!ENDLP_D) && (LFld.FIELD[IXc][I] != 0))
				{
					if (LFld.FIELD[IXc][I] > 0)
						// white
						YLineTest(-1, 1, LFld, I, RI, DA, IXc, IYc, NR);
					else
						// black
						YLineTest(-1, -1, LFld, I, RI, DA, IXc, IYc, NR);
				}
			}
		}
		// Higher IYc-Line Part
		if (IYc != 8)
		{
			ENDLP_D = FALSE;
			for (I = (IYc+1); I <=  8; I++)
			{
				if ((!ENDLP_D) && (LFld.FIELD[IXc][I] != 0))
				{
					if (LFld.FIELD[IXc][I] > 0)
						// white
						YLineTest(1, 1, LFld, I, RI, DA, IXc, IYc, NR);
					else
						// black
						YLineTest(1, -1, LFld, I, RI, DA, IXc, IYc, NR);
				}
			}
		}
	}
void duell::XLineTest(int PM, int VORZ, FieldCommon& XFld, int& I,
			int& RI, int& DA, int& IXc, int& IYc, int& NR)
	{
		int J, L, NM, H1_J, H1_L, H2_L, H3_L;
		bool Jump;
		for (J = 1; J <= 8; J++)
		{
			Jump = FALSE;
			if (VORZ*DA == -1)
				H1_J = XFld.FIGW[1][J];
			else
				H1_J = XFld.FIGR[1][J];
			if ((H1_J != 0) && (J != -VORZ*DA*NR))
			{
				if (VORZ*DA == -1)
				{
					HXD = XFld.FIGW[2][J];
					HYD = XFld.FIGW[3][J];
				}
				else
				{
					HXD = XFld.FIGR[2][J];
					HYD = XFld.FIGR[3][J];
				}
				if (((HXD >= IXc) && (PM == -1)) ||
					((HXD <= IXc) && (PM == 1) && ((HYD != IYc) || (IXc == 1))))
				{
					IDIST = abs(HXD-I) + abs(HYD-IYc);
					IVAL = - (VORZ * DA * (XFld.FIELD[HXD][HYD] / 10));
					XDistVal(1, XFld, I, J, Jump, RI, DA, PM, VORZ, IXc, IYc);
					if (!Jump)
					{
						IVAL = VORZ * (XFld.FIELD[I][IYc] / 10);
						XDistVal(2, XFld, I, J, Jump, RI, DA, PM, VORZ, IXc, IYc);
					}
				}
			}
		}
		if (DA == 1)
		{
			// Test to install or remove a possible moving-off DUELL
			if (VORZ*DA == -1)
			{
				XKD = XFld.KINGW[2];
				YKD = XFld.KINGW[3];
			}
			else
			{
				XKD = XFld.KINGR[2];
				YKD = XFld.KINGR[3];
			}
			if (((XKD >= IXc) && (PM == -1)) ||
				((XKD <= IXc) && (PM == 1) && ((YKD != IYc) || (IXc == 1))))
			{
				IDIST = abs(XKD-I) + abs(YKD-IYc);
				IVAL = VORZ * (XFld.FIELD[I][IYc] / 10);
				if (IDIST == IVAL)
				{
					Jump = FALSE;
					for (L = 1; L <= 8; L++)
					{
						if (VORZ*DA == 1)
						{
							H1_L = XFld.FIGW[1][L];
							H2_L = XFld.FIGW[2][L];
							H3_L = XFld.FIGW[3][L];
						}
						else
						{
							H1_L = XFld.FIGR[1][L];
							H2_L = XFld.FIGR[2][L];
							H3_L = XFld.FIGR[3][L];
						}
						if ((!Jump) && (H1_L != 0))
						{
							if ((I == H2_L) && (IYc == H3_L))
							{
								NM = L;
								Jump = TRUE;
							}
						}
					}
					if (Jump)
					{
						if (FXY(XFld, I, IYc, XKD-I, YKD-IYc))
						{
							if ((YKD == IYc) || (!FYX(XFld, I, IYc, XKD-I, YKD-IYc)))
							{
								// it is or was 2-way DUELL
								if (VORZ*DA == -1)
									// inc or dec t) of opposing king (DUELL)
									XFld.KINGW[6] = XFld.KINGW[6] + RI;
								else
									// inc or dec t) of opposing king (DUELL)
									XFld.KINGR[6] = XFld.KINGR[6] + RI;
							}
							if (VORZ*DA == 1)
								// inc or dec c) of own figure NM                    
								XFld.FIGW[6][NM] = XFld.FIGW[6][NM] + RI;
							else
								// inc or dec c) of own figure NM                    
								XFld.FIGR[6][NM] = XFld.FIGR[6][NM] + RI;
						}
					}
				}
			}
		}
		ENDLP_D = TRUE;
	}
void duell::XDistVal(int Variant, FieldCommon& DFld, int& I, int& J, bool& Jump,
			int& RI, int& DA, int& PM, int& VORZ, int& IXc, int& IYc)
	{
		int K, NM, H1_K, H2_K, H3_K;
		bool JUMP, jump;
		if (IDIST == IVAL)
		{
			JUMP = FALSE;
			if (((HYD != IYc) && (PM == -1)) ||
				(((HYD != IYc) || (IXc != 1)) && (PM == 1) && (Variant == 1)) ||
				((PM == 1) && (Variant == 2)))
			{
				if (FYX(DFld, I, IYc, HXD-I, HYD-IYc))
				{
					if (DA == 1)
					{
						if (((DFld.FIELD[I][IYc] != VORZ*15) && (Variant == 1)) ||
							(Variant == 2))
							JUMP = TRUE;
					}
					else
						JUMP = TRUE;
				}
			}
			if (!JUMP)
			{
				if (!FXY(DFld, I, IYc, HXD-I, HYD-IYc))
					JUMP = TRUE;
			}
			if (!JUMP)
			{
				jump = FALSE;
				NM = 9;
				for (K = 1; K <= 8; K++)
				{
					if (DA == 1)
					{
						if (VORZ*DA == 1)
						{
							H1_K = DFld.FIGW[1][K];
							H2_K = DFld.FIGW[2][K];
							H3_K = DFld.FIGW[3][K];
						}
						else
						{
							H1_K = DFld.FIGR[1][K];
							H2_K = DFld.FIGR[2][K];
							H3_K = DFld.FIGR[3][K];
						}
						if ((!jump) && (H1_K != 0))
						{
							if ((I == H2_K) && (IYc == H3_K))
							{
								NM = K;
								jump = TRUE;
							}
						}
					}
					else
					{
						if (VORZ*DA == -1)
						{
							H1_K = DFld.FIGW[1][K];
							H2_K = DFld.FIGW[2][K];
							H3_K = DFld.FIGW[3][K];
						}
						else
						{
							H1_K = DFld.FIGR[1][K];
							H2_K = DFld.FIGR[2][K];
							H3_K = DFld.FIGR[3][K];
						}
						if ((!jump) && (H1_K != 0))
						{
							if ((I == H2_K) && (IYc == H3_K))
							{
								NM = K;
								jump = TRUE;
							}
						}
					}
				}
				if (!jump)
				{
					if ((DA == 1) && (Variant == 1))
					{
						if ((HYD == IYc) || (!FYX(DFld, I, IYc, HXD-I, HYD-IYc)))
						{
							// it is or was 2-way DUELL
							if (VORZ*DA == 1)
								// inc or dec t) of own king (DUELL)
								DFld.KINGW[6] = DFld.KINGW[6] + RI;
							else
								// inc or dec t) of own king (DUELL)
								DFld.KINGR[6] = DFld.KINGR[6] + RI;
						}
						if (VORZ*DA == -1)
							// inc or dec c) of opposing figure J
							DFld.FIGW[6][J] = DFld.FIGW[6][J] + RI;
						else
							// inc or dec c) of opposing figure J
							DFld.FIGR[6][J] = DFld.FIGR[6][J] + RI;
					}
					JUMP = TRUE;
					Jump = TRUE;
				}
				if (!JUMP)
				{
					if (Variant == 1)
					{
						if (DA == 1)
						{
							if (VORZ*DA == 1)
							{
								// inc or dec e) of own figure NM
								DFld.FIGW[8][NM] = DFld.FIGW[8][NM] + RI;
								// inc or dec b) of opposing fig. J
								DFld.FIGR[5][J] = DFld.FIGR[5][J] + RI;
							}
							else
							{
								// inc or dec e) of own figure NM
								DFld.FIGR[8][NM] = DFld.FIGR[8][NM] + RI;
								// inc or dec b) of opposing fig. J
								DFld.FIGW[5][J] = DFld.FIGW[5][J] + RI;
							}
						}
						else
						{
							if (VORZ*DA == -1)
							{
								// inc or dec d) of own figure NM
								DFld.FIGW[7][NM] = DFld.FIGW[7][NM] + RI;
								// inc or dec f) of own figure J
								DFld.FIGW[9][J] = DFld.FIGW[9][J] + RI;
							}
							else
							{
								// inc or dec d) of own figure NM
								DFld.FIGR[7][NM] = DFld.FIGR[7][NM] + RI;
								// inc or dec f) of own figure J
								DFld.FIGR[9][J] = DFld.FIGR[9][J] + RI;
							}
						}
					}
					else if (Variant == 2)
					{
						if (DA == 1)
						{
							if (VORZ*DA == 1)
							{
								// inc or dec b) of own figure NM
								DFld.FIGW[5][NM] = DFld.FIGW[5][NM] + RI;
								// inc or dec e) of opposing fig. J
								DFld.FIGR[8][J] = DFld.FIGR[8][J] + RI;
							}
							else
							{
								// inc or dec b) of own figure NM
								DFld.FIGR[5][NM] = DFld.FIGR[5][NM] + RI;
								// inc or dec e) of opposing fig. J
								DFld.FIGW[8][J] = DFld.FIGW[8][J] + RI;
							}
						}
						else
						{
							if (VORZ*DA == -1)
							{
								// inc or dec f) of own figure NM
								DFld.FIGW[9][NM] = DFld.FIGW[9][NM] + RI;
								// inc or dec d) of own figure J
								DFld.FIGW[7][J] = DFld.FIGW[7][J] + RI;
							}
							else
							{
								// inc or dec f) of own figure NM
								DFld.FIGR[9][NM] = DFld.FIGR[9][NM] + RI;
								// inc or dec d) of own figure J
								DFld.FIGR[7][J] = DFld.FIGR[7][J] + RI;
							}
						}
					}
				}
			}
		}
	}
void duell::YLineTest(int PM, int VORZ, FieldCommon& YFld, int& I,
			int& RI, int& DA, int& IXc, int& IYc, int& NR)
	{
		int J, L, NM, H1_J, H1_L, H2_L, H3_L;
		bool Jump;
		for (J = 1; J <= 8; J++)
		{
			Jump = FALSE;
			if (VORZ*DA == -1)
				H1_J = YFld.FIGW[1][J];
			else
				H1_J = YFld.FIGR[1][J];
			if ((H1_J != 0) && (J != -VORZ*DA*NR))
			{
				if (VORZ*DA == -1)
				{
					HXD = YFld.FIGW[2][J];
					HYD = YFld.FIGW[3][J];
				}
				else
				{
					HXD = YFld.FIGR[2][J];
					HYD = YFld.FIGR[3][J];
				}
				if (((HYD > IYc) && (PM == -1)) ||
					((HYD < IYc) && (PM == 1) && ((HXD != IXc) || (IYc == 1))))
				{
					IDIST = abs(HXD-IXc) + abs(HYD-I);
					IVAL = - (VORZ * DA * (YFld.FIELD[HXD][HYD] / 10));
					YDistVal(1, YFld, I, J, Jump, RI, DA, PM, VORZ, IXc, IYc);
					if (!Jump)
					{
						IVAL = VORZ * (YFld.FIELD[IXc][I] / 10);
						YDistVal(2, YFld, I, J, Jump, RI, DA, PM, VORZ, IXc, IYc);
					}
				}
			}
		}
		if (DA == 1)
		{
			// Test to install or remove a possible moving-off DUELL
			if (VORZ*DA == -1)
			{
				XKD = YFld.KINGW[2];
				YKD = YFld.KINGW[3];
			}
			else
			{
				XKD = YFld.KINGR[2];
				YKD = YFld.KINGR[3];
			}
			if (((YKD > IYc) && (PM == -1)) ||
				((YKD < IYc) && (PM == 1) && ((XKD != IXc) || (IYc == 1))))
			{
				IDIST = abs(XKD-IXc) + abs(YKD-I);
				IVAL = VORZ * (YFld.FIELD[IXc][I] / 10);
				if (IDIST == IVAL)
				{
					Jump = FALSE;
					for (L = 1; L <= 8; L++)
					{
						if (VORZ*DA == 1)
						{
							H1_L = YFld.FIGW[1][L];
							H2_L = YFld.FIGW[2][L];
							H3_L = YFld.FIGW[3][L];
						}
						else
						{
							H1_L = YFld.FIGR[1][L];
							H2_L = YFld.FIGR[2][L];
							H3_L = YFld.FIGR[3][L];
						}
						if ((!Jump) && (H1_L != 0))
						{
							if ((IXc == H2_L) && (I == H3_L))
							{
								NM = L;
								Jump = TRUE;
							}
						}
					}
					if (Jump)
					{
						if (FYX(YFld, IXc, I, XKD-IXc, YKD-I))
						{
							if ((XKD == IXc) || (!FXY(YFld, IXc, I, XKD-IXc, YKD-I)))
							{
								// it is or was 2-way DUELL
								if (VORZ*DA == -1)
									// inc or dec t) of opposing king (DUELL)
									YFld.KINGW[6] = YFld.KINGW[6] + RI;
								else
									// inc or dec t) of opposing king (DUELL)
									YFld.KINGR[6] = YFld.KINGR[6] + RI;
							}
							if (VORZ*DA == 1)
								// inc or dec c) of own figure NM                    
								YFld.FIGW[6][NM] = YFld.FIGW[6][NM] + RI;
							else
								// inc or dec c) of own figure NM                    
								YFld.FIGR[6][NM] = YFld.FIGR[6][NM] + RI;
						}
					}
				}
			}
		}
		ENDLP_D = TRUE;
	}
void duell::YDistVal(int Variant, FieldCommon& DFld, int& I, int& J, bool& Jump,
			int& RI, int& DA, int& PM, int& VORZ, int& IXc, int& IYc)
	{
		int K, NM, H1_K, H2_K, H3_K;
		bool JUMP, jump;
		if (IDIST == IVAL)
		{
			JUMP = FALSE;
			if (((HXD != IXc) && (PM == -1)) ||
				(((HXD != IXc) || (IYc != 1)) && (PM == 1) && (Variant == 1)) ||
				((PM == 1) && (Variant == 2)))
			{
				if (FXY(DFld, IXc, I, HXD-IXc, HYD-I))
				{
					if (DA == 1)
					{
						if (((DFld.FIELD[IXc][I] != VORZ*15) && (Variant == 1)) ||
							(Variant == 2))
							JUMP = TRUE;
					}
					else
						JUMP = TRUE;
				}
			}
			if (!JUMP)
			{
				if (!FYX(DFld, IXc, I, HXD-IXc, HYD-I))
					JUMP = TRUE;
			}
			if (!JUMP)
			{
				jump = FALSE;
				NM = 9;
				for (K = 1; K <= 8; K++)
				{
					if (DA == 1)
					{
						if (VORZ*DA == 1)
						{
							H1_K = DFld.FIGW[1][K];
							H2_K = DFld.FIGW[2][K];
							H3_K = DFld.FIGW[3][K];
						}
						else
						{
							H1_K = DFld.FIGR[1][K];
							H2_K = DFld.FIGR[2][K];
							H3_K = DFld.FIGR[3][K];
						}
						if ((!jump) && (H1_K != 0))
						{
							if ((IXc == H2_K) && (I == H3_K))
							{
								NM = K;
								jump = TRUE;
							}
						}
					}
					else
					{
						if (VORZ*DA == -1)
						{
							H1_K = DFld.FIGW[1][K];
							H2_K = DFld.FIGW[2][K];
							H3_K = DFld.FIGW[3][K];
						}
						else
						{
							H1_K = DFld.FIGR[1][K];
							H2_K = DFld.FIGR[2][K];
							H3_K = DFld.FIGR[3][K];
						}
						if ((!jump) && (H1_K != 0))
						{
							if ((IXc == H2_K) && (I == H3_K))
							{
								NM = K;
								jump = TRUE;
							}
						}
					}
				}
				if (!jump)
				{
					if ((DA == 1) && (Variant == 1))
					{
						if ((HXD == IXc) || (!FXY(DFld, IXc, I, HXD-IXc, HYD-I)))
						{
							// it is or was 2-way DUELL
							if (VORZ*DA == 1)
								// inc or dec t) of own king (DUELL)
								DFld.KINGW[6] = DFld.KINGW[6] + RI;
							else
								// inc or dec t) of own king (DUELL)
								DFld.KINGR[6] = DFld.KINGR[6] + RI;
						}
						if (VORZ*DA == -1)
							// inc or dec c) of opposing figure J
							DFld.FIGW[6][J] = DFld.FIGW[6][J] + RI;
						else
							// inc or dec c) of opposing figure J
							DFld.FIGR[6][J] = DFld.FIGR[6][J] + RI;
					}
					JUMP = TRUE;
					Jump = TRUE;
				}
				if (!JUMP)
				{
					if (Variant == 1)
					{
						if (DA == 1)
						{
							if (VORZ*DA == 1)
							{
								// inc or dec e) of own figure NM
								DFld.FIGW[8][NM] = DFld.FIGW[8][NM] + RI;
								// inc or dec b) of opposing fig. J
								DFld.FIGR[5][J] = DFld.FIGR[5][J] + RI;
							}
							else
							{
								// inc or dec e) of own figure NM
								DFld.FIGR[8][NM] = DFld.FIGR[8][NM] + RI;
								// inc or dec b) of opposing fig. J
								DFld.FIGW[5][J] = DFld.FIGW[5][J] + RI;
							}
						}
						else
						{
							if (VORZ*DA == -1)
							{
								// inc or dec d) of own figure NM
								DFld.FIGW[7][NM] = DFld.FIGW[7][NM] + RI;
								// inc or dec f) of own figure J
								DFld.FIGW[9][J] = DFld.FIGW[9][J] + RI;
							}
							else
							{
								// inc or dec d) of own figure NM
								DFld.FIGR[7][NM] = DFld.FIGR[7][NM] + RI;
								// inc or dec f) of own figure J
								DFld.FIGR[9][J] = DFld.FIGR[9][J] + RI;
							}
						}
					}
					else if (Variant == 2)
					{
						if (DA == 1)
						{
							if (VORZ*DA == 1)
							{
								// inc or dec b) of own figure NM
								DFld.FIGW[5][NM] = DFld.FIGW[5][NM] + RI;
								// inc or dec e) of opposing fig. J
								DFld.FIGR[8][J] = DFld.FIGR[8][J] + RI;
							}
							else
							{
								// inc or dec b) of own figure NM
								DFld.FIGR[5][NM] = DFld.FIGR[5][NM] + RI;
								// inc or dec e) of opposing fig. J
								DFld.FIGW[8][J] = DFld.FIGW[8][J] + RI;
							}
						}
						else
						{
							if (VORZ*DA == -1)
							{
								// inc or dec f) of own figure NM
								DFld.FIGW[9][NM] = DFld.FIGW[9][NM] + RI;
								// inc or dec d) of own figure J
								DFld.FIGW[7][J] = DFld.FIGW[7][J] + RI;
							}
							else
							{
								// inc or dec f) of own figure NM
								DFld.FIGR[9][NM] = DFld.FIGR[9][NM] + RI;
								// inc or dec d) of own figure J
								DFld.FIGR[7][J] = DFld.FIGR[7][J] + RI;
							}
						}
					}
				}
			}
		}
	}
void duell::Cost(FieldCommon& CFld, int& IS)
	{
		// Computing of the cost of a given game-situation
		IZW = 0;
		IZR = 0;
		IHIL = 0;
		// Base costs for white
		FigKngCost(1, CFld);
		// Base costs for black
		FigKngCost(-1, CFld);
		// Test for white
		RestCost(1, CFld);
		CFld.COSTW = CFld.FIGTW + CFld.KNGTW + I13W + I14W + I15W + IDISTW;
		// Test for black
		RestCost(-1, CFld);
		CFld.COSTR = CFld.FIGTR + CFld.KNGTR + I13R + I14R + I15R + IDISTR;
		// New costs
		CFld.COSTN = IS * (CFld.COSTW-CFld.COSTR);
		if (IS == 1)
		{
			if (CFld.KINGW[6] != 0)
				CFld.COSTN = CFld.COSTN - 1000; // it is DUELL for black
			// ReTry für Züge ohne Schlag-Potential für Weiss bei Try
			if ((W2FLAG) && (W1.IBW == 0))
			{
				// erst Schlag-Potential für Weiss bei ReTry vorhanden
				if ((IZW >= IZR) && (CFld.IBW != 0))
					// force beating black figure
					CFld.COSTN = CFld.COSTN - WTHR2;
				// Schlag-Potential von Schwarz bei Kontra vorhanden
				if (W2.IBR != 0)
					// avoid beating white figure
					CFld.COSTN = CFld.COSTN - WTHR2;
			}
			// avoid or force beating black figure
			if ((W2FLAG) && (W1.IBW > 0))
			{
				if (hold_wert > W1.FIGW[7][NRACT_hold])
					CFld.COSTN = CFld.COSTN - WTHR2;
				else if (hold_wert < W1.FIGW[7][NRACT_hold])
					CFld.COSTN = CFld.COSTN + WTHR2;
			}
		}
		else
		{
			if (CFld.KINGR[6] != 0)
				CFld.COSTN = CFld.COSTN - 1000; // it is DUELL for white
			// ReTry für Züge ohne Schlag-Potential für Schwarz bei Try
			if ((W2FLAG) && (W1.IBR == 0))
			{
				// erst Schlag-Potential für Schwarz bei ReTry vorhanden
				if ((IZR >= IZW) && (CFld.IBR != 0))
					// force beating white figure
					CFld.COSTN = CFld.COSTN - WTHR2;
				// Schlag-Potential von Weiss bei Kontra vorhanden
				if (W2.IBW != 0)
					// avoid beating black figure
					CFld.COSTN = CFld.COSTN - WTHR2;
			}
			// avoid or force beating white figure
			if ((W2FLAG) && (W1.IBR > 0))
			{
				if (hold_wert > W1.FIGR[7][-NRACT_hold])
					CFld.COSTN = CFld.COSTN - WTHR2;
				else if (hold_wert < W1.FIGR[7][-NRACT_hold])
					CFld.COSTN = CFld.COSTN + WTHR2;
			}
		}
	}
void duell::FigKngCost(int VORZ, FieldCommon& KFld)
	{
		int I, J, H1_J;
		if (VORZ == 1)
		{
			KFld.FIGTW = 0;
			KFld.KNGTW = 0;
		}
		else
		{
			KFld.FIGTR = 0;
			KFld.KNGTR = 0;
		}
		for (I = 4; I <= 9; I++)
		{
			for (J = 1; J <= 8; J++)
			{
				if (VORZ == 1)
					H1_J = KFld.FIGW[1][J];
				else
					H1_J = KFld.FIGR[1][J];
				if ((H1_J == 0) && (I == 4))
				{
					if (VORZ == 1)
						IZW = IZW + 1;
					else
						IZR = IZR + 1;
				}
				if (H1_J != 0)
				{
					if (VORZ == 1)
						IHIL = IHIL + KFld.FIGW[I][J];
					else
						IHIL = IHIL + KFld.FIGR[I][J];
				}
			}
			if (VORZ == 1)
			{
				IHILFW[I-3] = IHIL;
				KFld.FIGTW = KFld.FIGTW + IHIL * CO[I-3];
				KFld.KNGTW = KFld.KNGTW + KFld.KINGW[I] * CO[I+3];
			}
			else
			{
				IHILFR[I-3] = IHIL;
				KFld.FIGTR = KFld.FIGTR + IHIL * CO[I-3];
				KFld.KNGTR = KFld.KNGTR + KFld.KINGR[I] * CO[I+3];
			}
			IHIL = 0;
		}
	} 
void duell::RestCost(int VORZ, FieldCommon& RFld)
	{
		int I, J, MF1, MF2, MF3, MF4, MF5, MF6, H_IZ, H1_J;
		bool Jump;
		if (VORZ == 1)
		{
			I13W = RFld.IBW;
			I13W = I13W * CO[13];
			I14W = RFld.IPW;
			I14W = I14W * CO[14];
			I15W = RFld.IRW;
			I15W = I15W * CO[15];
			HXS = RFld.KINGW[2];
			HYS = RFld.KINGW[3];
			H_IZ = IZW;
		}
		else
		{
			I13R = RFld.IBR;
			I13R = I13R * CO[13];
			I14R = RFld.IPR;
			I14R = I14R * CO[14];
			I15R = RFld.IRR;
			I15R = I15R * CO[15];
			HXS = RFld.KINGR[2];
			HYS = RFld.KINGR[3];
			H_IZ = IZR;
		}
		if (H_IZ <= 4)
		{
			if (VORZ == 1)
				IDISTW = (HYS-1) * CO[16];
			else
				IDISTR = (8-HYS) * CO[16];
		}
		if (H_IZ > 4)
		{
			if (VORZ == 1)
				IDISTW = abs(5-HXS) * CO[17] + (8-HYS) * CO[18];
			else
				IDISTR = abs(5-HXS) * CO[17] + (HYS-1) * CO[18];
		}
		if (H_IZ > 6)
		{
			if (VORZ == 1)
				IDISTW = IDISTW * 3;
			else
				IDISTR = IDISTR * 3;
		}
		if (H_IZ > 4)
		{
			KX[1] = HXS + 1;
			KX[2] = HXS;
			KX[3] = HXS - 1;
			KX[4] = HXS;
			KY[1] = HYS;
			KY[3] = HYS;
			if (VORZ == 1)
			{
				KY[2] = HYS + 1;
				KY[4] = HYS - 1;
			}
			else
			{
				KY[2] = HYS - 1;
				KY[4] = HYS + 1;
			}
			HILFFL = RFld.FIELD[HXS][HYS];
			RFld.FIELD[HXS][HYS] = 0;
			IPKTOT = 0;
			for (I = 1; I <= 4; I++)
			{
				IPKNG[I] = 0;
				if ((KX[I] <= 0) || (KX[I] > 9) ||
					(KY[I] <= 0) || (KY[I] > 8))
					IPKNG[I] = 1;
				if (IPKNG[I] != 1)
				{
					if ((VORZ * RFld.FIELD[KX[I]][KY[I]]) > 0)
						IPKNG[I] = 1;
				}
				if (IPKNG[I] != 1)
				{
					for (J = 1; J <= 9; J++)
					{
						Jump = FALSE;
						if (J == 9)
						{
							if (VORZ == -1)
							{
								IXH = RFld.KINGW[2];
								IYH = RFld.KINGW[3];
							}
							else
							{
								IXH = RFld.KINGR[2];
								IYH = RFld.KINGR[3];
							}
							IVAL = 1;
						}
						else
						{
							if (VORZ == -1)
								H1_J = RFld.FIGW[1][J];
							else
								H1_J = RFld.FIGR[1][J];
							if (H1_J != 0)
							{
								if (VORZ == -1)
								{
									IXH = RFld.FIGW[2][J];
									IYH = RFld.FIGW[3][J];
								}
								else
								{
									IXH = RFld.FIGR[2][J];
									IYH = RFld.FIGR[3][J];
								}
								IVAL = - VORZ * (RFld.FIELD[IXH][IYH] / 10);
							}
							else
								Jump = TRUE;
						}
						if (!Jump)
						{
							IDIST = abs(KX[I]-IXH) + abs(KY[I]-IYH);
							if (IDIST == IVAL)
							{
								if (FXY(RFld, IXH, IYH, KX[I]-IXH, KY[I]-IYH) ||
									FYX(RFld, IXH, IYH, KX[I]-IXH, KY[I]-IYH))
									IPKNG[I] = 1;
							}
						}
					}
				}
				IPKTOT = IPKTOT + IPKNG[I];
			}
			RFld.FIELD[HXS][HYS] = HILFFL;
			if (VORZ == 1)
				IDISTW = IDISTW + IPKNG[1] * CO[17] + IPKNG[2] * CO[18] * 2
							+ IPKNG[3] * CO[17] + IPKNG[4] * CO[18];
			else
				IDISTR = IDISTR + IPKNG[1] * CO[17] + IPKNG[2] * CO[18] * 2
							+ IPKNG[3] * CO[17] + IPKNG[4] * CO[18];
			if (HXS < 5)
			{
				if (VORZ == 1)
					IDISTW = IDISTW + IPKNG[1] * CO[17];
				else
					IDISTR = IDISTR + IPKNG[1] * CO[17];
			}
			if (HXS > 5)
			{
				if (VORZ == 1)
					IDISTW = IDISTW + IPKNG[3] * CO[17];
				else
					IDISTR = IDISTR + IPKNG[3] * CO[17];
			}
			if (H_IZ > 6)
			{
				if (((VORZ == 1) && (HYS > 4)) ||
					((VORZ == -1) && (HYS < 5)))
				{
					MF1 = 2;  MF2 = 4;  MF3 = 4;
					MF4 = 4;  MF5 = 5;  MF6 = 5;
				}
				else
				{
					MF1 = 1;  MF2 = 2;  MF3 = 2;
					MF4 = 5;  MF5 = 1;  MF6 = 1;
				}
				if (HXS < 5)
				{
					if (VORZ == 1)
						IDISTW = IDISTW + IPKNG[1] * CO[17] * MF1
								+ IPKNG[2] * CO[18] * MF2;
					else
						IDISTR = IDISTR + IPKNG[1] * CO[17] * MF1
								+ IPKNG[2] * CO[18] * MF2;
				}
				if (HXS > 5)
				{
					if (VORZ == 1)
						IDISTW = IDISTW + IPKNG[3] * CO[17] * MF1
								+ IPKNG[2] * CO[18] * MF2;
					else
						IDISTR = IDISTR + IPKNG[3] * CO[17] * MF1
								+ IPKNG[2] * CO[18] * MF2;
				}
				if (HXS == 5)
				{
					if (VORZ == 1)
						IDISTW = IDISTW + IPKNG[2] * CO[18] * MF3;
					else
						IDISTR = IDISTR + IPKNG[2] * CO[18] * MF3;
				}
				if (IPKTOT == 4)
				{
					if (VORZ == 1)
						IDISTW = IDISTW + CO[16] * MF4;
					else
						IDISTR = IDISTR + CO[16] * MF4;
				}
				for (J = 1; J <= 8; J++)
				{
					if (VORZ == 1)
						H1_J = RFld.FIGW[1][J];
					else
						H1_J = RFld.FIGR[1][J];
					if (H1_J != 0)
					{
						if (VORZ == 1)
						{
							IXH = RFld.FIGW[2][J];
							IYH = RFld.FIGW[3][J];
							HXS = RFld.KINGR[2];
							HYS = RFld.KINGR[3];
						}
						else
						{
							IXH = RFld.FIGR[2][J];
							IYH = RFld.FIGR[3][J];
							HXS = RFld.KINGW[2];
							HYS = RFld.KINGW[3];
						}
						IVAL = VORZ * (RFld.FIELD[IXH][IYH] / 10);
						IDIST = abs(HXS-IXH) + abs(HYS-IYH);
						if (IDIST > IVAL)
						{
							if (VORZ == 1)
								I = 1;
							else
								I = 8;
							IDIST = abs(5-IXH) + abs(I-IYH);
							if (IDIST < IVAL)
							{
								if (VORZ == 1)
									IDISTW = IDISTW - CO[16] * MF5;
								else
									IDISTR = IDISTR - CO[16] * MF5;
							}
							if (IDIST == 0)
							{
								if (VORZ == 1)
									IDISTW = IDISTW - CO[16] * MF6;
								else
									IDISTR = IDISTR - CO[16] * MF6;
							}
						}
					}
				}
			}
		}
	}
void duell::Contra(int Variant, int is, FieldCommon& WaFld, FieldCommon& WbFld,
										FieldCommon& HaFld, FieldCommon& HbFld)
	{
		// Routine to find the best Contra-Move for the player or
		// for the computer
		int K;
		bool JumpC;
		if (Variant == 0)
		{
			if (PFL > 0)
			{
				mein_showfile.WriteGameShowfile(0);
			}
		}
		Hold(WaFld, WbFld);
		Hold(WaFld, HbFld);
		// Initialisation
		NoCutC = TRUE;
		is = -is;
		if (!W3FLAG)
		{
			if (Variant <= 1)
				S2.COSTO = -WaFld.COSTN;
			else if (Variant == 2)
				H1.COSTN = -32000;
			W3FLAG = TRUE;
		}
		if (Variant <= 1)
			H2.COSTN = -32000;
		else if (Variant == 2)
			H2.COSTN = 32000;
		WbFld.COSTO = -WaFld.COSTN;
		HbFld.COSTO = -WaFld.COSTN;
		for (K = 1; K <= 9; K++)
		{
			if (NoCutC)
			{
				JumpC = FALSE;
				if (is == 1)
				{
					if (K != 9)
					{
						if (WbFld.FIGW[1][K] != 0)
						{
							HXC = WbFld.FIGW[2][K];
							HYC = WbFld.FIGW[3][K];
							IVALC = WbFld.FIELD[HXC][HYC] / 10;
						}
						else
							JumpC = TRUE;
					}
					else
					{
// Test Anfang
						if (WbFld.KINGW[1] != 0)
						{
						    HXC = WbFld.KINGW[2];
						    HYC = WbFld.KINGW[3];
						    IVALC = 1;
					    }
						else
							JumpC = TRUE;
					}
// Test Ende
				}
				else
				{
					if (K != 9)
					{
						if (WbFld.FIGR[1][K] != 0)
						{
							HXC = WbFld.FIGR[2][K];
							HYC = WbFld.FIGR[3][K];
							IVALC = - (WbFld.FIELD[HXC][HYC] / 10);
						}
						else
					       JumpC = TRUE;
					}
					else
					{
// Test Anfang
						if (WbFld.KINGR[1] != 0)
						{
						    HXC = WbFld.KINGR[2];
						    HYC = WbFld.KINGR[3];
						    IVALC = 1;
					    }
						else
							JumpC = TRUE;
					}
// Test Ende
				}
				if (!JumpC)
				{
					IVC = IVALC * 8 - 4;
					ICC = 0;
					// Check for VXC>0 AND VYC>0 for X-Y-lines
					XFIRST = TRUE; FXC = -1; FYC = 1;
					VXC = IVALC - 1; VYC = 1;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC - 1;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC>0 and VYC>0 for Y-X-lines
					XFIRST = FALSE; VXC = IVALC; VYC = 0;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC<0 and VYC>0 for X-Y-lines
					XFIRST = TRUE; FXC = -1; FYC = -1;
					VXC = 0; VYC = IVALC;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC<0 and VYC>0 for Y-X-lines
					XFIRST = FALSE; VXC = -1; VYC = IVALC - 1;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC - 1;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC<0 and VYC<0 for X-Y-lines
					XFIRST = TRUE; FXC = 1; FYC = -1;
					VXC = 1 - IVALC; VYC = -1;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC - 1;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC<0 and VYC<0 for Y-X-lines
					XFIRST = FALSE; VXC = -IVALC; VYC = 0;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC>0 and VYC<0 for X-Y-lines
					XFIRST = TRUE; FXC = 1; FYC = 1;
					VXC = 0; VYC = -IVALC;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXC>0 and VYC<0 for Y-X-lines
					XFIRST = FALSE; VXC = 1; VYC = 1 - IVALC;
					WXC = HXC + VXC; WYC = HYC + VYC;
					ILIMC = IVALC - 1;
					ConPossible(Variant, is, WaFld, WbFld, HaFld, HbFld);
					if (PFL > 0)
					{
						mein_showfile.ShowPossibleMoves(K, is, ICC, IVC, HbFld, "Kontra:");
					}
				}
			}
		}
		if (NoCutC)
		{
			if (Variant == 2)
			{
				if (IRAND == 'J')
					HRC = rand()%25 - 12;
				else
					HRC = 0;
			}
			if (Variant <= 1)
			{
				Hold(H2, S2);
				Hold(W1, H1);
			}
			else if (Variant == 2)
			{
				if (((IRAND == 'N') && (is != 1)) ||
					((IRAND == 'J') && (HRC > 0)) || (H2.COSTN != H1.COSTN))
				{
					if (H2.COSTN >= H1.COSTN)
					{
						W1.COSTN = H2.COSTN;
						Hold(W1, H1);
						Hold(S2, S4);
						Hold(S3, S5);
					}
				}
			}
		}
		is = -is;
		NoCutC = TRUE;
		if (Variant == 0)
		{
			if (PFL > 0)
				mein_showfile.CloseGameShowfile();
		}
	}
void duell::ConPossible(int Variant, int is, FieldCommon& WaFld,
						FieldCommon& WbFld, FieldCommon& HaFld,
						FieldCommon& HbFld)
	{
		// Routine to help to find the best contra-move for the player or
		// for the computer
		int J;
		bool JUMPC;
		if ((ILIMC > 0) && (NoCutC))
		{
			for (J = 1; J <= ILIMC; J++)
			{
				if (NoCutC)
				{
					JUMPC = FALSE; 
					if ((XFIRST) &&  !(FXY(WbFld,HXC,HYC,VXC,VYC)))
						JUMPC = TRUE;
					else if ((!XFIRST) && !(FYX(WbFld,HXC,HYC,VXC,VYC)))
						JUMPC = TRUE;
					else if (WbFld.FIELD[WXC][WYC]*is > 0)
						JUMPC = TRUE; // own figure
					if (!JUMPC)
					{
						ICC = ICC + 1;
						Move(WbFld, HXC, HYC, WXC, WYC, VXC, VYC, is, IRET);
						Cost(WbFld, is);
						ITWC = I13W + I14W + I15W;
						ITRC = I13R + I14R + I15R;
						if (PFL >= 3)
						{
							strcpy(DATBUF, "Kontra:\0");
							mein_showfile.ShowInfoCosts(WbFld, DATBUF);
						}
						if (IRAND == 'J')
							HRC = rand()%25 - 12;
						else
							HRC = 0;
						if (Variant == 2)
						{
							W2FLAG = TRUE;
							ReTry(is, W2, W3, H2, H3);
							W2FLAG = FALSE;
							if (((IRAND == 'N') && (is != 1)) ||
								((IRAND == 'J') && (HRC < 0)) || (H3.COSTN != H1.COSTN))
							{
// Test Anfang
//?								if (H3.COSTN < H1.COSTN)
								if (H3.COSTN <= H1.COSTN)
// Test Ende
									NoCutC = FALSE; // Alpha-Cutoff
							}
						}
						else
						{
							// for Variant 0 and 1
							if (((IRAND == 'N') && (is != 1)) ||
								((IRAND == 'J') && (HRC > 0)) ||
								(WbFld.COSTN != HbFld.COSTN))
							{
								if (WbFld.COSTN >= HbFld.COSTN)
									Hold(WbFld, HbFld);
							}
						}
						Hold(WaFld, WbFld);
					}
					VXC = VXC + FXC;
					VYC = VYC + FYC;
					WXC = HXC + VXC;
					WYC = HYC + VYC;
				}
			}
		}		  
	}
void duell::ReTry(int is, FieldCommon& WaFld, FieldCommon& WbFld,
						FieldCommon& HaFld, FieldCommon& HbFld)
	{
		// Routine to find the best Re-Try-Move for the computer
		int K;
		bool JumpR;
		Hold(WaFld, WbFld);
		Hold(WaFld, HbFld);
		// Initialisation
		NoCutR = TRUE;
		is = -is;
		if (!W4FLAG)
			W4FLAG = TRUE;
		H3.COSTN = -32000;
		WbFld.COSTO = -WaFld.COSTN;
		HbFld.COSTO = -WaFld.COSTN;
		for (K = 1; K <= 9; K++)
		{
			if (NoCutR)
			{
				JumpR = FALSE;
				if (is == 1)
				{
					if (K != 9)
					{
						if (WbFld.FIGW[1][K] != 0)
						{
							HXR = WbFld.FIGW[2][K];
							HYR = WbFld.FIGW[3][K];
							IVALR = WbFld.FIELD[HXR][HYR] / 10;
						}
						else
							JumpR = TRUE;
					}
					else
					{
// Test Anfang
						if (WbFld.KINGW[1] != 0)
						{
						    HXR = WbFld.KINGW[2];
						    HYR = WbFld.KINGW[3];
						    IVALR = 1;
					    }
						else
							JumpR = TRUE;
					}
// Test Ende
				}
				else
				{
					if (K != 9)
					{
						if (WbFld.FIGR[1][K] != 0)
						{
							HXR = WbFld.FIGR[2][K];
							HYR = WbFld.FIGR[3][K];
							IVALR = - (WbFld.FIELD[HXR][HYR] / 10);
						}
						else
					       JumpR = TRUE;
					}
					else
					{
// Test Anfang
						if (WbFld.KINGR[1] != 0)
						{
						    HXR = WbFld.KINGR[2];
						    HYR = WbFld.KINGR[3];
						    IVALR = 1;
					    }
						else
							JumpR = TRUE;
					}
// Test Ende
				}
				if (!JumpR)
				{
					IVR = IVALR * 8 - 4;
					ICR = 0;
					// Check for VXR>0 AND VYR>0 for X-Y-lines
					XFIRST = TRUE; FXR = -1; FYR = 1;
					VXR = IVALR - 1; VYR = 1;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR - 1;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR>0 and VYR>0 for Y-X-lines
					XFIRST = FALSE; VXR = IVALR; VYR = 0;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR<0 and VYR>0 for X-Y-lines
					XFIRST = TRUE; FXR = -1; FYR = -1;
					VXR = 0; VYR = IVALR;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR<0 and VYR>0 for Y-X-lines
					XFIRST = FALSE; VXR = -1; VYR = IVALR - 1;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR - 1;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR<0 and VYR<0 for X-Y-lines
					XFIRST = TRUE; FXR = 1; FYR = -1;
					VXR = 1 - IVALR; VYR = -1;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR - 1;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR<0 and VYR<0 for Y-X-lines
					XFIRST = FALSE; VXR = -IVALR; VYR = 0;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR>0 and VYR<0 for X-Y-lines
					XFIRST = TRUE; FXR = 1; FYR = 1;
					VXR = 0; VYR = -IVALR;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					// Check for VXR>0 and VYR<0 for Y-X-lines
					XFIRST = FALSE; VXR = 1; VYR = 1 - IVALR;
					WXR = HXR + VXR; WYR = HYR + VYR;
					ILIMR = IVALR - 1;
					RetPossible(is, WaFld, WbFld, HaFld, HbFld);
					if (PFL > 1)
					{
						mein_showfile.ShowPossibleMoves(K, is, ICR, IVR, HbFld, "Erneut:");
					}
				}
			}
		}
		if (NoCutR)
		{
			if (IRAND == 'J')
				HRR = rand()%25 - 12;
			else
				HRR = 0;
			if (((IRAND == 'N') && (is != 1)) ||
				((IRAND == 'J') && (HRR < 0)) || (H3.COSTN != H2.COSTN))
			{
				if (H3.COSTN <= H2.COSTN)
				{
					H2.COSTN = H3.COSTN;
					Hold(H3, S2);
					Hold(W2, S3);
				}
			}
		}
		is = -is;
		NoCutR = TRUE;
	}
void duell::RetPossible(int is, FieldCommon& WaFld,
						FieldCommon& WbFld, FieldCommon& HaFld,
						FieldCommon& HbFld)
	{
		// Routine to help to find the best re-try-move for the computer
		int J;
		bool JUMPR;
		if ((ILIMR > 0) && (NoCutR))
		{
			for (J = 1; J <= ILIMR; J++)
			{
				if (NoCutR)
				{
					JUMPR = FALSE; 
					if ((XFIRST) &&  !(FXY(WbFld,HXR,HYR,VXR,VYR)))
						JUMPR = TRUE;
					else if ((!XFIRST) && !(FYX(WbFld,HXR,HYR,VXR,VYR)))
						JUMPR = TRUE;
					else if (WbFld.FIELD[WXR][WYR]*is > 0)
						JUMPR = TRUE; // own figure
					if (!JUMPR)
					{
						ICR = ICR + 1;
						Move(WbFld, HXR, HYR, WXR, WYR, VXR, VYR, is, IRET);
						Cost(WbFld, is);
						ITWR = I13W + I14W + I15W;
						ITRR = I13R + I14R + I15R;
						if (PFL >= 3)
						{
							strcpy(DATBUF, "Erneut:\0");
							mein_showfile.ShowInfoCosts(WbFld, DATBUF);
						}
						if (IRAND == 'J')
							HRR = rand()%25 - 12;
						else
							HRR = 0;
						if (((IRAND == 'N') && (is != 1)) ||
							((IRAND == 'J') && (HRR > 0)) ||
							(W3.COSTN != H2.COSTN))
						{
// Test Anfang
//?							if (W3.COSTN > H2.COSTN)
							if (W3.COSTN >= H2.COSTN)
// Test Ende
								NoCutR = FALSE; // Beta-Cutoff
						}
						if (((IRAND == 'N') && (is != 1)) ||
							((IRAND == 'J') && (HRR > 0)) ||
							(WbFld.COSTN != HbFld.COSTN))
						{
							if (WbFld.COSTN >= HbFld.COSTN)
								Hold(WbFld, HbFld);
						}
						Hold(WaFld, WbFld);
					}
					VXR = VXR + FXR;
					VYR = VYR + FYR;
					WXR = HXR + VXR;
					WYR = HYR + VYR;
				}
			}
		}		  
	}
void duell::Try(int& IRET)
	{
		// Routine to find the best move for the computer
		int K;
		bool JUMP, FLDOK, WFL;
		Hold(W0, W1);
		Hold(W0, H1);
		// Initialisation
		W3FLAG = FALSE;
		W4FLAG = FALSE;
		H1.COSTN = -32000;
		W1.COSTO = -W0.COSTN;
		H1.COSTO = -W0.COSTN;
		ICTOT = 0;
		ENDLP_T = FALSE;
		// change WTHR1 (=WTHR1-200) if IPKTOT == 4
		WFL = FALSE;
		if (IS == 1)
			WTHR1Change(1, W0, WFL);
		else
			WTHR1Change(-1, W0, WFL);
		// for main variant
		strcpy(GraphicText9, BLANK);
		if ((ILOOK == 'J') && (INN != 'S'))
		{
			FLDOK = FieldEqual();
			if (FLDOK)
			{
				Hold(S4, H1);
				W3FLAG = TRUE;
				strcpy(GraphicText9, "Haupt-Variante\0");
			}
		}
		for (K = 1; K <= 9; K++)
		{
			if (!ENDLP_T)
			{
				JUMP = FALSE;
				if (IS == 1)
					ValFig(1, W1, K, JUMP);
				else
					ValFig(-1, W1, K, JUMP);
				if (!JUMP)
				{
					IVT = IVALT * 8 - 4;
					ICT = 0;
					// Check for VXT>0 AND VYT>0 for X-Y-lines
					if (!ENDLP_T)
					{
						XFIRST = TRUE;
						FXT = -1;
						FYT = 1;
						VXT = IVALT - 1;
						VYT = 1;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT - 1;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT>0 and VYT>0 for Y-X-lines
					if (!ENDLP_T)
					{
						XFIRST = FALSE;
						VXT = IVALT;
						VYT = 0;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT<0 and VYT>0 for X-Y-lines
					if (!ENDLP_T)
					{
						XFIRST = TRUE;
						FXT = -1;
						FYT = -1;
						VXT = 0;
						VYT = IVALT;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT<0 and VYT>0 for Y-X-lines
					if (!ENDLP_T)
					{
						XFIRST = FALSE;
						VXT = -1;
						VYT = IVALT - 1;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT - 1;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT<0 and VYT<0 for X-Y-lines
					if (!ENDLP_T)
					{
						XFIRST = TRUE;
						FXT = 1;
						FYT = -1;
						VXT = 1 - IVALT;
						VYT = -1;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT - 1;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT<0 and VYT<0 for Y-X-lines
					if (!ENDLP_T)
					{
						XFIRST = FALSE;
						VXT = -IVALT;
						VYT = 0;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT>0 and VYT<0 for X-Y-lines
					if (!ENDLP_T)
					{
						XFIRST = TRUE;
						FXT = 1;
						FYT = 1;
						VXT = 0;
						VYT = -IVALT;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					// Check for VXT>0 and VYT<0 for Y-X-lines
					if (!ENDLP_T)
					{
						XFIRST = FALSE;
						VXT = 1;
						VYT = 1 - IVALT;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
						ILIMT = IVALT - 1;
						TryPossib(JUMP);
						if (abs(IRET) == 15)
							ENDLP_T = TRUE;
					}
					if (PFL >= 1)
					{
						mein_showfile.ShowPossibleMoves(K, IS, ICT, IVT, H1, "Suchen:");
					}
					ICTOT = ICTOT + ICT;
				}
			}
		}
		// correct WTHR1 if changed
		if (WFL)
			WTHR1 = WTHR1 + 200;
		// Was at least 1 move possible ?
		if (!ENDLP_T)
		{
			if (ICTOT == 0)
				IRET = IS * 15;
		}
		// Interpretation of best move
		ENDLP_T = FALSE;
		for (K = 1; K <= 9; K++)
		{
			if (!ENDLP_T)
			{
				if (IS == 1)
					NewPos(1, W0, H1, K);
				else
					NewPos(-1, W0, H1, K);
			}
		}
		// Interpretation of the computer move
		DXT = IXN - IXO;
		DYT = IYN - IYO;
		ILINE[1] = (char)((unsigned int)(IYO) + (unsigned int)('0'));
		ILINE[4] = (char)((unsigned int)(IYN) + (unsigned int)('0'));
		if (IXO == IXN)
		{
			ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('@'));
			ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('@'));
		}
		else if (IYO == IYN)
		{
			ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('`'));
			ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('`'));
		}
		else
		{
			XFIRST = TRUE;
			if ((H1.FIELD[IXN][IYN] == NEWV(DXT, DYT, W0.FIELD[IXO][IYO], IS)) &&
				(FXY(W0, IXO, IYO, DXT, DYT)))
			{
				ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('`'));
				ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('@'));
			}
			else
			{
				ILINE[0] = (char)((unsigned int)(IXO) + (unsigned int)('@'));
				ILINE[3] = (char)((unsigned int)(IXN) + (unsigned int)('`'));
				XFIRST = FALSE;
			}
		}
		if (W0.FIELD[IXN][IYN] == 0)
			ILINE[2] = '-';
		else
			ILINE[2] = 'x';
		ILINE[5] = ' ';
		ILINE[6] = ' ';
		if (IS == 1)
		{
			if (H1.KINGR[6] != 0)
				ILINE[5] = '+';
			if (H1.KINGR[1] == 0)
				ILINE[6] = '+';
		}
		else
		{
			if (H1.KINGW[6] != 0)
				ILINE[5] = '+';
			if (H1.KINGW[1] == 0)
				ILINE[6] = '+';
		}
		Hold(H1, W0);
		W3FLAG = FALSE;
		W4FLAG = FALSE;
		Hold(W0, W1);
		HIRET = IRET;
		HXFIRST = XFIRST;
		Contra(1, IS, W1, W2, H1, H2);
		XFIRST = HXFIRST;
		IRET = HIRET;
		if (IS == 1)
		{
			if ((S2.KINGR[6] != 0) && (S2.KINGW[1] != 0))
				ILINE[6] = '+';
		}
		else
		{
			if ((S2.KINGW[6] != 0) && (S2.KINGR[1] != 0))
				ILINE[6] = '+';
		}
	}
void duell::ValFig(int VORZ, FieldCommon& WaFld, int& K, bool& JUMP)
	{
		int H1_K;
		if (K != 9)
		{
			if (VORZ == 1)
				H1_K = WaFld.FIGW[1][K];
			else
				H1_K = WaFld.FIGR[1][K];

			if (H1_K == 0)
				JUMP = TRUE;
			else
			{
				if (VORZ == 1)
				{
					HXT = WaFld.FIGW[2][K];
					HYT = WaFld.FIGW[3][K];
				}
				else
				{
					HXT = WaFld.FIGR[2][K];
					HYT = WaFld.FIGR[3][K];
				}
					IVALT = VORZ * (WaFld.FIELD[HXT][HYT] / 10);
			}
		}
		else
		{
			if (VORZ == 1)
			{
				HXT = WaFld.KINGW[2];
				HYT = WaFld.KINGW[3];
			}
			else
			{
				HXT = WaFld.KINGR[2];
				HYT = WaFld.KINGR[3];
			}
			IVALT = 1;
		}
	}
void duell::NewPos(int VORZ, FieldCommon& WaFld,
					FieldCommon& HaFld, int& K)
	{
		int W1_K, W2_K, W3_K, H2_K, H3_K;
		int WK2, WK3, HK2, HK3;
		if (K != 9)
		{
			if (VORZ == 1)
			{
				W1_K = WaFld.FIGW[1][K];
				W2_K = WaFld.FIGW[2][K];
				W3_K = WaFld.FIGW[3][K];
				H2_K = HaFld.FIGW[2][K];
				H3_K = HaFld.FIGW[3][K];
			}
			else
			{
				W1_K = WaFld.FIGR[1][K];
				W2_K = WaFld.FIGR[2][K];
				W3_K = WaFld.FIGR[3][K];
				H2_K = HaFld.FIGR[2][K];
				H3_K = HaFld.FIGR[3][K];
			}
			if (W1_K != 0)
			{
				if ((W2_K != H2_K) || (W3_K != H3_K))
				{
					IXO = W2_K;
					IYO = W3_K;
					IXN = H2_K;
					IYN = H3_K;
					ENDLP_T = TRUE;
				}
			}
		}
		else
		{
			if (VORZ == 1)
			{
				WK2 = WaFld.KINGW[2];
				WK3 = WaFld.KINGW[3];
				HK2 = HaFld.KINGW[2];
				HK3 = HaFld.KINGW[3];
			}
			else
			{
				WK2 = WaFld.KINGR[2];
				WK3 = WaFld.KINGR[3];
				HK2 = HaFld.KINGR[2];
				HK3 = HaFld.KINGR[3];
			}
			if ((WK2 != HK2) || (WK3 != HK3))
			{
				IXO = WK2;
				IYO = WK3;
				IXN = HK2;
				IYN = HK3;
				ENDLP_T = TRUE;
			}
		}
	}
void duell::TryPossib(bool& JUMP)
	{
		// Routine to help to find the best move for the computer
		int J, HR;
		if (ILIMT > 0)
		{
			ENDLP_T = FALSE;
			for (J = 1; J <= ILIMT; J++)
			{
				if (!ENDLP_T)
				{
					JUMP = FALSE; 
					if ((XFIRST) && !(FXY(W1,HXT,HYT,VXT,VYT)))
						JUMP = TRUE;
					else if ((!XFIRST) && !(FYX(W1,HXT,HYT,VXT,VYT)))
						JUMP = TRUE;
					else if (W1.FIELD[WXT][WYT]*IS > 0)
						JUMP = TRUE; // own figure
					if (!JUMP)
					{
						ICT = ICT + 1;
						Move(W1, HXT, HYT, WXT, WYT, VXT, VYT, IS, IRET);
						Cost(W1, IS);
						ITWT = I13W + I14W + I15W;
						ITRT = I13R + I14R + I15R;
						if (PFL >= 3)
						{
							mein_showfile.ShowInfoCosts(W1, "Suchen:");
						}
						if (IRAND == 'J')
							HR = rand()%25 - 12;
						else
							HR = 0;
						if (((IRAND == 'N') && (IS != 1)) ||
							((IRAND == 'J') && (HR > 0)) ||
							(W1.COSTN != H1.COSTN))
						{
							if ((W1.COSTN >= H1.COSTN) && (!W3FLAG) && (!W4FLAG))
								Hold(W1, H1);
						}
						if (abs(IRET) == 15)
						{
							Hold(W1, H1);
							ENDLP_T = TRUE;
						}
						else
						{
							if ((ILOOK == 'J') && (W1.COSTN > W1.COSTO+WTHR1))
								W1FLAG = TRUE;
							else
								W1FLAG = FALSE;
							if (W1FLAG)
							{
								HIRET = IRET;
								Contra(2, IS, W1, W2, H1, H2);
								IRET = HIRET;
							}
							W1FLAG = FALSE;
							Hold(W0, W1);
						}
					}
					if (!ENDLP_T)
					{
						VXT = VXT + FXT;
						VYT = VYT + FYT;
						WXT = HXT + VXT;
						WYT = HYT + VYT;
					}
				}
			}
		}
	}
void duell::WTHR1Change(int VORZ, FieldCommon& GFld, bool& WFL)
	{
		int I, J, H1_J;
		bool Jump;
		if (VORZ == 1)
		{
			HXG = GFld.KINGW[2];
			HYG = GFld.KINGW[3];
		}
		else
		{
			HXG = GFld.KINGR[2];
			HYG = GFld.KINGR[3];
		}
		GX[1] = HXG + 1;
		GX[2] = HXG;
		GX[3] = HXG - 1;
		GX[4] = HXG;
		GY[1] = HYG;
		GY[3] = HYG;
		if (VORZ == 1)
		{
			GY[2] = HYG + 1;
			GY[4] = HYG - 1;
		}
		else
		{
			GY[2] = HYG - 1;
			GY[4] = HYG + 1;
		}
		HILFFG = GFld.FIELD[HXG][HYG];
		GFld.FIELD[HXG][HYG] = 0;
		PKTOTG = 0;
		PKOWNG = 0;
		for (I = 1; I <= 4; I++)
		{
			GPKNG[I] = 0;
			if ((GX[I] <= 0) || (GX[I] > 9) || (GY[I] <= 0) || (GY[I] > 8))
			{
				GPKNG[I] = 1;
				GPKNGO[I] = 1;
			}
			if (GPKNG[I] == 0)
			{
				if ((VORZ * GFld.FIELD[GX[I]][GY[I]]) > 0)
				{
					GPKNG[I] = 1;
					GPKNGO[I] = 1;
				}
			}
			if (GPKNG[I] == 0)
			{
				for (J = 1; J <= 9; J++)
				{
					Jump = FALSE;
					if (J == 9)
					{
						if (VORZ == -1)
						{
							XHG = GFld.KINGW[2];
							YHG = GFld.KINGW[3];
						}
						else
						{
							XHG = GFld.KINGR[2];
							YHG = GFld.KINGR[3];
						}
						IVALG = 1;
					}
					else
					{
						if (VORZ == -1)
							H1_J = GFld.FIGW[1][J];
						else
							H1_J = GFld.FIGR[1][J];
						if (H1_J != 0)
						{
							if (VORZ == -1)
							{
								XHG = GFld.FIGW[2][J];
								YHG = GFld.FIGW[3][J];
							}
							else
							{
								XHG = GFld.FIGR[2][J];
								YHG = GFld.FIGR[3][J];
							}
							IVALG = - VORZ * (GFld.FIELD[XHG][YHG] / 10);
						}
						else
							Jump = TRUE;
					}
					if (!Jump)
					{
						IDISTG = abs(GX[I]-XHG) + abs(GY[I]-YHG);
						if (IDISTG == IVALG)
						{
							if (FXY(GFld, XHG, YHG, GX[I]-XHG, GY[I]-YHG) ||
								FYX(GFld, XHG, YHG, GX[I]-XHG, GY[I]-YHG))
								GPKNG[I] = 1;
						}
					}
				}
			}
			PKTOTG = PKTOTG + GPKNG[I];
			PKOWNG = PKOWNG + GPKNGO[I];
		}
		GFld.FIELD[HXG][HYG] = HILFFG;
		ZWG = 0;
		ZRG = 0;
		for (I = 1; I <= 8; I++)
		{
			if (GFld.FIGW[1][I] == 0)
				ZWG = ZWG + 1;
			if (GFld.FIGR[1][I] == 0)
				ZRG = ZRG + 1;
		}
		if ((ZWG > 4) || (ZRG > 4) || ((PKTOTG == 4) && (PKOWNG != 4)))
		{
			WTHR1 = WTHR1 - 200;
			WFL = TRUE;
		}
	}
bool duell::FieldEqual()
	{
		int I, J;
		for (I = 1; I <= 9; I++)
		{
			for (J = 1; J <= 8; J++)
			{
				if (S5.FIELD[I][J] != W0.FIELD[I][J])
					return FALSE;
			}
		}
		return TRUE;
	}

duell mein_spiel;

BOOL CALLBACK hilfedialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if((wParam == IDOK)||(wParam == IDCANCEL))
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}
 
BOOL CALLBACK duelldialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_INITDIALOG:
			SetDlgItemText(hwndDlg, IDC_INFOTEXT1, infoText1);
			SetDlgItemText(hwndDlg, IDC_INFOTEXT2, infoText2);
			SetDlgItemText(hwndDlg, IDC_INFOTEXT3, infoText3);
			return TRUE;
		case WM_COMMAND:
			if( wParam == IDC_WEITERE_INFO)
			{
//				ShellExecute(NULL, "open", "http://www-et.bocholt.fh-gelsenkirchen.de", NULL, NULL, SW_SHOWNORMAL);
				ShellExecute(NULL, "open", "NOTEPAD.EXE", "Zusatz-Informationen.txt", Path_Buffer, SW_SHOWNORMAL);
				return TRUE;
			}
			if((wParam == IDOK)||(wParam == IDCANCEL))
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK thinknormaldialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				if ((FileOpen) && (MOVENO != 1))
					mein_protokoll.UpdateProtocol();
				ILOOK = 'N';
				CheckMenuItem( duell_menu, ID_THINORML, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_THIAHEAD, MF_UNCHECKED);
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK thinkaheaddialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				if ((FileOpen) && (MOVENO != 1))
					mein_protokoll.UpdateProtocol();
				ILOOK = 'J';
				CheckMenuItem( duell_menu, ID_THIAHEAD, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_THINORML, MF_UNCHECKED);
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}	
			else if (wParam == IDCANCEL)
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK oneplayerdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				INN = 'J';
				JumpCM = FALSE;
				JumpPM = FALSE;
				strcpy(GraphicText0, BLANK);
				strcpy(GraphicText1, BLANK);
				strcpy(GraphicText2, BLANK);
				strcpy(GraphicText8, BLANK);
				strcpy(GraphicText9, BLANK);
				CheckMenuItem( duell_menu, ID_ONE, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_TWO, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_NONE, MF_UNCHECKED);
				CHFLAG = FALSE;
				InpOK = FALSE;
				if (((INP == 'J') && (IS == -1)) || ((INP == 'N') && (IS == 1)))
					PMLabel = 5;
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				InpOK = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK twoplayerdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				INN = 'N';
				INP = 'J';
				JumpCM = TRUE;
				JumpPM = FALSE;
				strcpy(GraphicText0, BLANK);
				strcpy(GraphicText1, BLANK);
				strcpy(GraphicText2, WCM);
				strcpy(GraphicText8, BLANK);
				strcpy(GraphicText9, BLANK);
				CheckMenuItem( duell_menu, ID_TWO, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_ONE, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_NONE, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_BLACK, MF_UNCHECKED);
				CHFLAG = FALSE;
				InpOK = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				InpOK = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK noneplayerdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				INN = 'S';
				JumpCM = FALSE;
				strcpy(GraphicText0, BLANK);
				strcpy(GraphicText1, WPM);
				strcpy(GraphicText2, BLANK);
				CheckMenuItem( duell_menu, ID_NONE, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_ONE, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_TWO, MF_UNCHECKED);
				if (IS == 1)
				{
					MOVENO = MOVENO - 1;
					PMLabel = 1;
				}
				else
					PMLabel = 3;
				CHFLAG = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				InpOK = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK whiteplayerdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				char INPO;
				INPO = INP;
				INP = 'J';
				if (INPO == 'N')
				{
					CHFLAG = FALSE;
					PMLabel = 5;
				}
				else
				{
					if (IS == 1)
						PMLabel = 2;
					else
						PMLabel = 4;
				}
				mein_spiel.Hold(W0, S1);
				S1.COSTO = W0.COSTO;
				CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_BLACK, MF_UNCHECKED);
				strcpy(GraphicText0, BLANK);
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				InpOK = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK blackplayerdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				char INPO;
				INPO = INP;
				INP = 'N';
				if (INPO == 'J')
				{
					CHFLAG = FALSE;
					MOVENO = MOVENO - 1;
					PMLabel = 5;
				}
				else
				{
					if (IS == 1)
						PMLabel = 2;
					else
						PMLabel = 4;
				}
				mein_spiel.Hold(W0, S1);
				S1.COSTO = W0.COSTO;
				CheckMenuItem( duell_menu, ID_BLACK, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_WHITE, MF_UNCHECKED);
				strcpy(GraphicText0, BLANK);
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				InpOK = FALSE;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK backwarddialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				int I, J, K;
				int X[5], Y[5];
				K = 0 ;
				for (J = 1; J <= 8; J++)
				{
					for (I = 1; I <= 9; I++)
					{
						if (W0.FIELD[I][J] != S1.FIELD[I][J])
						{
							K = K + 1;
							X[K] = I;
							Y[K] = J;
						}
					}
				}
				mein_spiel.Hold(S1, W0);
				W0.COSTO = S1.COSTO;
				mein_spiel.UpdateBoard(X[1], Y[1], X[2], Y[2]);
				if (K == 3)
					mein_spiel.UpdateBoard(X[3], Y[3], X[3], Y[3]);
				else if (K == 4)
					mein_spiel.UpdateBoard(X[3], Y[3], X[4], Y[4]);
				if (!Exit)
				{
					if (FileOpen)
					{
						if ((INN == 'J') && (IS == 1) && (INP == 'J'))
						{
							mein_protokoll.WriteString(Zurk);
							mein_protokoll.WriteString(Line);
							mein_protokoll.WriteLn();
						}
						else if ((INN == 'J') && (IS == -1) && (INP == 'N'))
						{
							mein_protokoll.WriteString(Line);
							mein_protokoll.WriteLn();
							mein_protokoll.WriteString(Zurk);
						}
						else if ((INN == 'N') && (IS == 1))
						{
							mein_protokoll.WriteString(Zurk);
						}
						else if ((INN == 'N') && (IS == -1))
						{
							mein_protokoll.WriteString(Zurk);
							mein_protokoll.WriteLn();
						}
					}
					if ((INN == 'J') || (IS == 1))
						MOVENO = MOVENO - 1;
					if (INN == 'N')
						IS = -IS;
					strcpy(GraphicText0, BLANK);
					if (IS == 1)
						PMLabel = 2;
					else
						PMLabel = 4;
				}
				else
				{
					if (FileOpen)
					{
						if ((INN == 'J') && (IS == -1) && (INP == 'J'))
						{
							mein_protokoll.WriteString(Zurk);
							mein_protokoll.WriteString(Line);
							mein_protokoll.WriteLn();
						}
						else if ((INN == 'J') && (IS == 1) && (INP == 'J'))
						{
							mein_protokoll.WriteString(Zurk);
							mein_protokoll.WriteLn();
						}
						else if ((INN == 'J') && (IS == -1) && (INP == 'N'))
						{
							mein_protokoll.WriteString(Zurk);
						}
						else if ((INN == 'J') && (IS == 1) && (INP == 'N'))
						{
							mein_protokoll.WriteString(Zurk);
							mein_protokoll.WriteLn();
							mein_protokoll.WriteString(Line);
						}
						else if ((INN == 'N') && (IS == 1))
						{
							mein_protokoll.WriteString(Zurk);
							mein_protokoll.WriteLn();
						}
						else if ((INN == 'N') && (IS == -1))
						{
							mein_protokoll.WriteString(Zurk);
						}
					}
					if (INN == 'J')
					{
						JumpCM = FALSE;
						if (((IS == -1) && (INP == 'J')) ||
							((IS == 1) && (INP == 'N')))
							IS = -IS;
					}
				}
				strcpy(GraphicText1, BLANK);
				if (INN == 'J')
				{
					strcpy(GraphicText2, BLANK);
					strcpy(GraphicText3, BLANK);
					strcpy(GraphicText4, BLANK);
				}
				else if (INN == 'N')
				{
					strcpy(GraphicText3, BLANK);
					strcpy(GraphicText4, BLANK);
				}
				strcpy(GraphicText9, BLANK);
				mein_spiel.ShowCosts(W0.COSTO, W0.COSTN);
				CHFLAG = FALSE;
				if (Exit)
				{
					K_Flag = FALSE;
					Done = FALSE;
					DoneOK = FALSE;
					Exit = FALSE;
					InpOK = FALSE;
					JumpPM = FALSE;
					strcpy(GraphicText6, BLANK);
					strcpy(GraphicText8, BLANK);
				}
				EndDialog(hwndDlg, wParam);
				return TRUE;				
			}
			else if (wParam == IDCANCEL)
			{
				if (Exit)
					Done = TRUE;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK whatsduelldialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if ((wParam == IDOK) || (wParam == IDCANCEL))
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK moveexamplesdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if ((wParam == IDOK) || (wParam == IDCANCEL))
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK randomdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_COMMAND:
			if (wParam == IDC_YESYES)
			{
				if ((FileOpen) && (MOVENO != 1))
					mein_protokoll.UpdateProtocol();
				IRAND = 'J';
				CheckMenuItem( duell_menu, ID_RANDOM, MF_CHECKED);
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
			else if (wParam == IDC_NONO)
			{
				if ((FileOpen) && (MOVENO != 1))
					mein_protokoll.UpdateProtocol();
				IRAND = 'N';
				CheckMenuItem( duell_menu, ID_RANDOM, MF_UNCHECKED);
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
			else if (wParam == IDCANCEL)
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK thresholdsdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_INITDIALOG:
			SetDlgItemInt( hwndDlg, IDC_THRES1, WTHR1, TRUE);
			SetDlgItemInt( hwndDlg, IDC_THRES2, WTHR2, TRUE);
			return TRUE;
		case WM_COMMAND:
			if (wParam == IDOK)
			{
				if ((FileOpen) && (MOVENO != 1))
					mein_protokoll.UpdateProtocol();
				WTHR1 = GetDlgItemInt( hwndDlg, IDC_THRES1, NULL, TRUE);
				WTHR2 = GetDlgItemInt( hwndDlg, IDC_THRES2, NULL, TRUE);
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
			else if (wParam == IDCANCEL)
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK showeinstellungdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
	int i;
    switch (uMsg)
		{
		case WM_INITDIALOG:
			for (i = 0; i < 4; i++)
				CheckDlgButton(hwndDlg, 1028+i, (PFL == i) ? BST_CHECKED : BST_UNCHECKED);
			return TRUE;
		case WM_COMMAND:
			if ((wParam == IDC_STANDARD) || (wParam == IDC_STUFE1) ||
				(wParam == IDC_STUFE2) || (wParam == IDC_STUFE3))
			{
				for (i = 0; i < 4; i++)
				{
					if (IsDlgButtonChecked(hwndDlg, 1028+i) == BST_CHECKED)
						PFL = i;
				}
				for (i = 0; i < 4; i++)
					CheckDlgButton(hwndDlg, 1028+i, (PFL == i) ? BST_CHECKED : BST_UNCHECKED);
				return TRUE;
			}
			if ((wParam == IDOK) || (wParam == IDCANCEL))
			{
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

BOOL CALLBACK alertdialog( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
    switch (uMsg)
		{
		case WM_INITDIALOG:
			SetDlgItemText( hwndDlg, IDC_STR, str);
			duell_sounds.play(sound_persmove);
			return TRUE;
		case WM_COMMAND:
			if ((wParam == IDOK)||(wParam == IDCANCEL))
			{
				Flags = 31;
				EndDialog(hwndDlg, wParam);
				return TRUE;
			}
		}
	return FALSE;
	}

/*
** duell_windowhandler
*/

LRESULT CALLBACK duell_windowhandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
	switch(msg)
		{
	case WM_MOUSEMOVE:
		MoX = LOWORD(lParam);		// horizontal position of cursor 
		MoY = HIWORD(lParam);		// vertical position of cursor
		fwKeys = LOWORD(wParam);	// which key pressed
		if ((MoX <= 23) || (MoX >= 421) || (MoY <= 23) || (MoY >= 377))
			M1Flags = 0;
		else
			M1Flags = 1;
		if ((!InpOK) && (!K_Flag) && (M1Flags))
		{
			switch(fwKeys)
			{
			case MK_LBUTTON:
				if (M2Flags == 0)
				{
					xtmp = (MoX - 24) / 44 + 1;
					ytmp = 8 - ((MoY -24) / 44);
					if (W0.FIELD[xtmp][ytmp] != 0)
					{
						strcpy(GraphicText1, BLANK);
						Flags = 28;
						ILINE[5] = ' ';
						ILINE[6] = ' ';
						IQ = 5;
						allowed = TRUE;
						HilF = W0.FIELD[xtmp][ytmp];
						OldField = 0;
						NewField = 0;
						Hxtmp = xtmp;
						Hytmp = ytmp;
						back = FALSE;
						spec = FALSE;
						CH = 0;
						CV = 0;
						CT = 0;
						CM = IS * (HilF / 10);
						M2Flags = 1;
						M2X = (xtmp - 1) * 44 + 24;
						M2Y = (8 - ytmp) * 44 + 24;
						// GrafMouse(FlatHand, NIL);
						hold_cursor = LoadCursor(NULL, IDC_SIZEALL);
						SetCursor(hold_cursor);
					}
				}
				else
				{
					if ((MoX <= M2X) && (MoY >= M2Y) && (MoY <= M2Y+44))
					{
						mein_spiel.LeftTry();
						duell_sounds.play(sound_fold);
						mein_spiel.display();
						if ((back) && (allowed))
						{
							mein_spiel.retour();
							DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ALERT), duell_window, alertdialog);
							if (PFL < 4)
							{
								mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
							}
							// GrafMouse(PointHand, NIL) ;
							hold_cursor = LoadCursor(NULL, IDC_ARROW);
						}
						mein_spiel.InpOKWait();
						return 0;
						}
					else if ((MoX >= M2X+44) && (MoY >= M2Y) && (MoY <= M2Y+44))
					{
						mein_spiel.RightTry();
						duell_sounds.play(sound_fold);
						mein_spiel.display();
						if ((back) && (allowed))
						{
							mein_spiel.retour();
							DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ALERT), duell_window, alertdialog);
							if (PFL < 4)
							{
								mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
							}
							// GrafMouse(PointHand, NIL) ;
							hold_cursor = LoadCursor(NULL, IDC_ARROW);
						}
						mein_spiel.InpOKWait();
						return 0;
					}
					else if ((MoX > M2X) && (MoX < M2X+44) && (MoY <= M2Y))
					{
						mein_spiel.UpTry();
						duell_sounds.play(sound_fold);
						mein_spiel.display();
						if ((back) && (allowed))
						{
							mein_spiel.retour();
							DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ALERT), duell_window, alertdialog);
							if (PFL < 4)
							{
								mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
							}
							// GrafMouse(PointHand, NIL) ;
							hold_cursor = LoadCursor(NULL, IDC_ARROW);
						}
						mein_spiel.InpOKWait();
						return 0;
					}
					else if ((MoX > M2X) && (MoX < M2X+44) && (MoY >= M2Y+44))
					{
						mein_spiel.DownTry();
						duell_sounds.play(sound_fold);
						mein_spiel.display();
						if ((back) && (allowed))
						{
							mein_spiel.retour();
							DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ALERT), duell_window, alertdialog);
							if (PFL < 4)
							{
								mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
							}
							// GrafMouse(PointHand, NIL) ;
							hold_cursor = LoadCursor(NULL, IDC_ARROW);
						}
						mein_spiel.InpOKWait();
						return 0;
					}
					else if ((xtmp < 1) || (xtmp > 9) || (ytmp < 1) || (ytmp > 8))
					{
						W0.FIELD[xtmp][ytmp] = NewField;
						back = TRUE;
						if ((back) && (allowed))
						{
							mein_spiel.retour();
							DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ALERT), duell_window, alertdialog);
							if (PFL < 4)
							{
								mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
							}
							// GrafMouse(PointHand, NIL) ;
							hold_cursor = LoadCursor(NULL, IDC_ARROW);
						}
						mein_spiel.InpOKWait();
						return 0;
					}
					else
					{
						// sonst wird Cursor immer wieder zu 'arrow' gesetzt
						SetCursor(hold_cursor);
						return 0;
					}
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		if ((!InpOK) && (!K_Flag) && (M1Flags))
		{
			MoX = LOWORD(lParam);		// horizontal position of cursor 
			MoY = HIWORD(lParam);		// vertical position of cursor
			fwKeys = LOWORD(wParam);	// which key pressed
			if (M2Flags == 1)
			{
				Flags = 31;
				M2Flags = 0;
				M2X = 420;
				M2Y = 0;
		        // GrafMouse(PointHand, NIL) ;
				if (CT != 0)
				{
					if (CT != CM)
					{
						W0.FIELD[xtmp][ytmp] = NewField;
						back = TRUE;
						strcpy(str,"Unerlaubte Anzahl Würfel-Klappungen\0");
						spec = TRUE;
						if ((back) && (allowed))
						{
							mein_spiel.retour();
							DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ALERT), duell_window, alertdialog);
							if (PFL < 4)
							{
								mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
							}
							// GrafMouse(PointHand, NIL) ;
							hold_cursor = LoadCursor(NULL, IDC_ARROW);
						}
					}
					else
					{
						IXO = Hxtmp;
						IYO = Hytmp;
						IXN = xtmp;;
						IYN = ytmp;
						CT = 0;
						W0.FIELD[IXO][IYO] = HilF;
						W0.FIELD[IXN][IYN] = NewField;
						// GrafMouse(PointHand, NIL) ;
						hold_cursor = LoadCursor(NULL, IDC_ARROW);
						SetCursor(hold_cursor);
						strcpy(GraphicText0, H_GraphicText);
						strcat(GraphicText0,"<Maus> \0");
						mein_spiel.display();
						mein_spiel.ShowMove();
						mein_spiel.TestMove();
						if (PFL < 4)
							mein_spiel.UpdateBoard(xtmp, ytmp, Hxtmp, Hytmp);
					}
				}
			}
			mein_spiel.CheckState();
		}
		return 0;
	case WM_RBUTTONDOWN:
		if ((!InpOK) && (!K_Flag) && (M1Flags))
		{
			if (CT == CM)
			{
				ILINE[5] = '+';
				ILINE[6] = ' ';
				IQ = 6;
				strcpy(GraphicText0, H_GraphicText);
				strcat(GraphicText0,"<Duell>\0");
				mein_spiel.display();
			}
		}
		return 0;
	case WM_RBUTTONDBLCLK:
		if ((!InpOK) && (!K_Flag) && (M1Flags))
		{
			if (CT == CM)
			{
				ILINE[5] = '+';
				ILINE[6] = '+';
				IQ = 7;
				strcpy(GraphicText0, H_GraphicText);
				strcat(GraphicText0,"<DMatt>\0");
				mein_spiel.display();
			}
		}
		return 0;
	case WM_CHAR:
		char character;
		int j;
		character = (TCHAR) wParam;
		if ((mein_spiel.spiel_laeuft) && (Flags == 31))
		{
			if (!K_Flag)
			{
				K_Flag = TRUE;
				strcpy(H_GraphicText, GraphicText0);
				strcpy(GraphicText1, BLANK);
				strcpy(GraphicText3, BLANK);
				strcpy(GraphicText4, BLANK);
				strcpy(GraphicText5, BLANK);
				strcpy(GraphicText6, BLANK);
				EndInp = FALSE;
				ILINE[0] = character;
				if (ILINE[0] == '\015')
				{
					ILINE[0] = '\0';
					JCount = 0;
					K_Flag = FALSE;
				}
				else if (character == '\010')
				{
					ILINE[0] = '\0';
					JCount = 0;
					K_Flag = FALSE;
				}
				else
				{
					ILINE[1] = '\0';
					JCount = 1;
				}
				strcpy(GraphicText0, H_GraphicText);
				strcat(GraphicText0, ILINE);
				TextFlag = TRUE;
				mein_spiel.display();
				TextFlag = FALSE;
			}
			else
			{
				if (character == '\015')
					EndInp = TRUE;
				else if (character == '\010')
				{
					JCount = JCount - 2;
					ILINE[JCount + 1] = ' ';
					ILINE[JCount + 2] = '\0';
					strcpy(GraphicText0, H_GraphicText);
					strcat(GraphicText0, ILINE);
					mein_spiel.display();
					if (JCount == -1)
						K_Flag = FALSE;
				}
				else
				{
					ILINE[JCount] = character;
					ILINE[JCount + 1] = '\0';
					strcpy(GraphicText0, H_GraphicText);
					strcat(GraphicText0, ILINE);
					TextFlag = TRUE;
					mein_spiel.display();
					TextFlag = FALSE;
				}
				JCount = JCount + 1;
				if (JCount == 7)
				{
					EndInp = TRUE;
					if (character != '\015')
						JCount = JCount + 1;
					strcpy(GraphicText0, H_GraphicText);
					strcat(GraphicText0, ILINE);
					TextFlag = TRUE;
					mein_spiel.display();
					TextFlag = FALSE;
				}
				if (EndInp)
				{
					IQ = JCount - 1;
					if (IQ <= 6)
					{
						for (j = IQ; j <= 6; j++)
						{
							ILINE[j] = ' ';
						}
					}
					ILINE[7] = '\0';
					strcpy(GraphicText1, BLANK);
					strcpy(GraphicText1, "Ihr Zug ist :  \0");
					strcat(GraphicText1, ILINE);
					mein_spiel.display();
					K_Flag = FALSE;
					mein_spiel.TestMove();
					if (IERR == 0)
						duell_sounds.play(sound_persmove);
					mein_spiel.CheckState();
				}
			}
		}
		return 0;
	case WM_COMMAND:
		switch( LOWORD( wParam))
			{
		case IDM_EXIT:
			PostMessage( hWnd, WM_CLOSE, 0, 0);
			return 0;
		case ID_DUELL_SOUND:
			duell_sounds.on = !duell_sounds.on;
			CheckMenuItem( duell_menu, ID_DUELL_SOUND, duell_sounds.on ? MF_CHECKED:MF_UNCHECKED);
			return 0;
		case ID_DUELL_MARKERS:
			Mark_on = !Mark_on;
			CheckMenuItem( duell_menu, ID_DUELL_MARKERS, Mark_on ? MF_CHECKED:MF_UNCHECKED);
			return 0;
		case ID_INFO_HILFE:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_HILFE), duell_window, hilfedialog);
			mein_spiel.reset_timer();
			return 0;
		case ID_INFO_DUELL:
			duell_sounds.play(sound_persmove);
			mein_registeredfile.ReadRegisteredfile();
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_DUELL), duell_window, duelldialog);
			mein_spiel.reset_timer();
			return 0;
		case ID_DUELL_NEUESSPIEL:
			if (FileOpen)
			{
				CheckMenuItem( duell_menu, ID_WRITEPROT, MF_UNCHECKED);
				mein_protokoll.CloseProtocol();
			}
			if (FileOpenGameShowfile)
			{
				mein_showfile.CloseGameShowfile();
			}
			mein_spiel.start();
			CheckMenuItem( duell_menu, ID_THINORML, MF_CHECKED);
			CheckMenuItem( duell_menu, ID_THIAHEAD, MF_UNCHECKED);
			CheckMenuItem( duell_menu, ID_ONE, MF_CHECKED);
			CheckMenuItem( duell_menu, ID_TWO, MF_UNCHECKED);
			CheckMenuItem( duell_menu, ID_NONE, MF_UNCHECKED);
			CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
			CheckMenuItem( duell_menu, ID_BLACK, MF_UNCHECKED);
			CheckMenuItem( duell_menu, ID_RANDOM, MF_CHECKED);
			PostMessage( duell_window, WM_PAINT, 0, 0);
			break;
		case ID_THINORML:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_THINORML), duell_window, thinknormaldialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_THIAHEAD:
			mein_registeredfile.ReadRegisteredfile();
			if (registered)
			{
				duell_sounds.play(sound_persmove);
				DialogBox( duell_instance, MAKEINTRESOURCE( IDD_THIAHEAD), duell_window, thinkaheaddialog);
			}
			else
				MessageBox( duell_window, "Verstellung für Sharewareversion nicht möglich", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_ONE:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_ONE), duell_window, oneplayerdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			mein_spiel.CheckState();
			return 0;
		case ID_TWO:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_TWO), duell_window, twoplayerdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			mein_spiel.CheckState();
			return 0;
		case ID_NONE:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_NONE), duell_window, noneplayerdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			mein_spiel.CheckState();
			return 0;
		case ID_WHITE:
			if ((INN == 'N') || (INN == 'S'))
				MessageBox( duell_window, "Verstellung im Moment leider nicht möglich", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			else
			{
				duell_sounds.play(sound_persmove);
				DialogBox( duell_instance, MAKEINTRESOURCE( IDD_WHITE), duell_window, whiteplayerdialog);
			}
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			if (INN == 'J')
				mein_spiel.CheckState();
			return 0;
		case ID_BLACK:
			if ((INN == 'N') || (INN == 'S'))
				MessageBox( duell_window, "Verstellung im Moment leider nicht möglich", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			else
			{
				duell_sounds.play(sound_persmove);
				DialogBox( duell_instance, MAKEINTRESOURCE( IDD_BLACK), duell_window, blackplayerdialog);
			}
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			if (INN == 'J')
				mein_spiel.CheckState();
			return 0;
		case ID_BACKWARD:
			if (!((CHFLAG) && ((IS != 1) || (MOVENO != 1))))
			{
				if (INN == 'S')
					MessageBox( duell_window, "Rücknahme von Zügen beim 'Spiel ohne Personen' nicht möglich", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
				else
					MessageBox( duell_window, "Rücknahme des Zuges im Moment leider nicht möglich", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			}
			else
			{
				duell_sounds.play(sound_persmove);
				DialogBox( duell_instance, MAKEINTRESOURCE( IDD_BACKWARD), duell_window, backwarddialog);
			}
			mein_spiel.reset_timer();
			if (Done)
				mein_spiel.CheckState();
			else
				mein_spiel.InpOKWait();
			return 0;
		case ID_WHATSDUELL:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_WHATSDUELL), duell_window, whatsduelldialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_RULES:
			ShellExecute(NULL, "open", "NOTEPAD.EXE", "Duell-Spiel-Regeln.txt", Path_Buffer, SW_SHOWNORMAL);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_MOVEXAMP:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_MOVEXAMP), duell_window, moveexamplesdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_RANDOM:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_RANDOM), duell_window, randomdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_THRESHOLDS:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_THRESHOLDS), duell_window, thresholdsdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_SHOWEINSTELLUNG:
			duell_sounds.play(sound_persmove);
			DialogBox( duell_instance, MAKEINTRESOURCE( IDD_SHOWEINSTELLUNG), duell_window, showeinstellungdialog);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_SPIEL_SPEICHERN:
			if (!Exit)
				mein_spielfeld.WriteGameSituation();
			else
				MessageBox( duell_window, "Spiel-Seicherung im Moment leider nicht möglich", "Duell-Hinweis", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_SPIEL_LADEN:
			mein_spielfeld.ReadGameSituation();
			strcpy(GraphicText0, BLANK);
			strcpy(GraphicText1, BLANK);
			strcpy(GraphicText2, BLANK);
			strcpy(GraphicText3, BLANK);
			strcpy(GraphicText4, BLANK);
			strcpy(GraphicText5, BLANK);
			strcpy(GraphicText6, BLANK);
			strcpy(GraphicText7, BLANK);
			strcpy(GraphicText8, BLANK);
			strcpy(GraphicText9, BLANK);
			if (FileOpen)
			{
				CheckMenuItem( duell_menu, ID_WRITEPROT, MF_UNCHECKED);
				mein_protokoll.CloseProtocol();
			}
			if (INN == 'J')
			{
				JumpCM = FALSE;
				CheckMenuItem( duell_menu, ID_ONE, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_TWO, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_NONE, MF_UNCHECKED);
				if (INP == 'J')
				{
					CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
					CheckMenuItem( duell_menu, ID_BLACK, MF_UNCHECKED);
				}
				else
				{
					CheckMenuItem( duell_menu, ID_WHITE, MF_UNCHECKED);
					CheckMenuItem( duell_menu, ID_BLACK, MF_CHECKED);
				}
			}
			else if (INN == 'N')
			{
				JumpCM = TRUE;
				CheckMenuItem( duell_menu, ID_ONE, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_TWO, MF_CHECKED);
				strcpy(GraphicText2, WCM);
				CheckMenuItem( duell_menu, ID_NONE, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_BLACK, MF_UNCHECKED);
			}
			else
			{
				JumpCM = FALSE;
				CheckMenuItem( duell_menu, ID_ONE, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_TWO, MF_UNCHECKED);
				CheckMenuItem( duell_menu, ID_NONE, MF_CHECKED);
				strcpy(GraphicText1, WPM);
				strcpy(GraphicText9, Space);
				if (INP == 'J')
				{
					CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
					CheckMenuItem( duell_menu, ID_BLACK, MF_UNCHECKED);
				}
				else
				{
					CheckMenuItem( duell_menu, ID_WHITE, MF_UNCHECKED);
					CheckMenuItem( duell_menu, ID_BLACK, MF_CHECKED);
				}
			}
			if (ILOOK == 'N')
			{
				CheckMenuItem( duell_menu, ID_THINORML, MF_CHECKED);
				CheckMenuItem( duell_menu, ID_THIAHEAD, MF_UNCHECKED);
			}
			else
			{
				mein_registeredfile.ReadRegisteredfile();
				if (registered)
				{
					CheckMenuItem( duell_menu, ID_THINORML, MF_UNCHECKED);
					CheckMenuItem( duell_menu, ID_THIAHEAD, MF_CHECKED);
				}
				else
				{
					ILOOK = 'N';
					CheckMenuItem( duell_menu, ID_THINORML, MF_CHECKED);
					CheckMenuItem( duell_menu, ID_THIAHEAD, MF_UNCHECKED);
				}
			}
			if (IRAND == 'J')
				CheckMenuItem( duell_menu, ID_RANDOM, MF_CHECKED);
			else
				CheckMenuItem( duell_menu, ID_RANDOM, MF_UNCHECKED);
			// Code, um 'device context' wieder zu definieren
			duell_dc = GetDC(duell_window);
			SetBkMode(duell_dc, TRANSPARENT);
			mein_spiel.ShowCosts(W0.COSTO, W0.COSTN);		
// Test Anfang
			int z, s;
			for( z = 0; z <= 8; z++)
			{
				for( s = 0; s <= 9; s++)
					S5.FIELD[s][z] = 0;
			}
// Test Ende
			mein_spiel.reset_timer();
			K_Flag = FALSE;
			Done = FALSE;
			DoneOK = FALSE;
			Exit = FALSE;
			InpOK = FALSE;
			if ((INN == 'J') || (INN == 'N'))
			{
				JumpPM = FALSE;
				if (IS == 1)
					PMLabel = 2;
				else
					PMLabel = 4;
			}
			else
			{
				if (IS == 1)
				{
					MOVENO = MOVENO - 1;
					PMLabel = 1;
				}
				else
					PMLabel = 3;
			}
			CHFLAG = FALSE;
			mein_spiel.Hold(W0, S1);
			S1.COSTO = W0.COSTO;
			mein_spiel.InpOKWait();
			return 0;
		case ID_WRITEPROT:
			mein_protokoll.WriteGameProtocol();
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case ID_READPROT:
			mein_protokoll.ReadGameProtocol();
			mein_spiel.reset_timer();
			mein_spiel.InpOKWait();
			return 0;
		case IDM_DOWN:
			if ((mein_spiel.spiel_laeuft) && (!K_Flag))
			{
				if (Done)
				{
					if (FileOpen)
					{
						CheckMenuItem( duell_menu, ID_WRITEPROT, MF_UNCHECKED);
						mein_protokoll.CloseProtocol();
					}
					DoneOK = TRUE;
					InpOK = TRUE;
					JumpPM = TRUE;
					mein_spiel.CheckState();
				}
				else if (INN == 'S')
				{
					strcpy(GraphicText9, BLANK);
					strcpy(GraphicText1, WPM);
					InpOK = TRUE;
					JumpPM = TRUE;
					mein_spiel.CheckState();
				}
			}
			return 0;
			}
		break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = ((MINMAXINFO *)lParam)->ptMaxTrackSize.x = duell_bruttobreite;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = ((MINMAXINFO *)lParam)->ptMaxTrackSize.y = duell_bruttohoehe;
		return 0;
	case WM_DESTROY:
		PostQuitMessage( 0);
		return 0;
	case WM_MOVE:
		duell_display.update();
		return 0;
	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		mein_spiel.reset_timer();
		break;
	case WM_PAINT:
		mein_spiel.display();
		break;
	case WM_CLOSE:
		if (FileOpen)
		{
			CheckMenuItem( duell_menu, ID_WRITEPROT, MF_UNCHECKED);
			mein_protokoll.CloseProtocol();
		}
		if (FileOpenGameShowfile)
		{
			mein_showfile.CloseGameShowfile();
		}
		InpOK = TRUE;
		JumpPM = TRUE;
		Exit = TRUE;
		Done = TRUE;
		break;
		}
    return DefWindowProc(hWnd, msg, wParam, lParam);
	}

/*
** WinMain
*/
int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	HACCEL acc;
	WNDCLASSEX wcx;

	duell_instance = hInst;

	wcx.cbSize        = sizeof( wcx);
	wcx.lpszClassName = TEXT( "Duell");
	wcx.lpfnWndProc   = duell_windowhandler;
	wcx.style         = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wcx.hInstance     = hInst;
	wcx.hIcon         = LoadIcon( hInst, MAKEINTRESOURCE( IDI_MAIN));
	wcx.hIconSm       = LoadIcon( hInst, MAKEINTRESOURCE( IDI_MAIN));
	wcx.hCursor       = LoadCursor( NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcx.lpszMenuName  = MAKEINTRESOURCE( IDR_MENU);
	wcx.cbClsExtra    = 0;
	wcx.cbWndExtra    = 0;

	if( !RegisterClassEx( &wcx))
		return 0;

	acc = LoadAccelerators( hInst, MAKEINTRESOURCE(IDR_ACCEL));

	duell_bruttohoehe = duell_nettohoehe + 2*GetSystemMetrics( SM_CYSIZEFRAME) 
		                                   + GetSystemMetrics( SM_CYMENU)
							               + GetSystemMetrics( SM_CYCAPTION);
	duell_bruttobreite = duell_nettobreite + 2*GetSystemMetrics( SM_CXSIZEFRAME);

	duell_window = CreateWindowEx( 0, TEXT( "Duell"), TEXT( "Duell"), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 
		                                           CW_USEDEFAULT, CW_USEDEFAULT,
  	                                               duell_bruttobreite, duell_bruttohoehe, NULL, NULL, hInst, NULL);
	if( !duell_window)
		return 0;

	duell_menu = GetMenu( duell_window);

	duell_dc = GetDC(duell_window);

	if( duell_sounds.init( duell_window) < 0)
	{
		MessageBox( duell_window, "Fehler beim Initialisieren der Sounds", "Duell-Fehlermeldung", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		return 0;
	}
	CheckMenuItem( duell_menu, ID_DUELL_SOUND, duell_sounds.on ? MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem( duell_menu, ID_DUELL_MARKERS, Mark_on ? MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem( duell_menu, ID_THINORML, MF_CHECKED);
	CheckMenuItem( duell_menu, ID_ONE, MF_CHECKED);
	CheckMenuItem( duell_menu, ID_WHITE, MF_CHECKED);
	CheckMenuItem( duell_menu, ID_RANDOM, MF_CHECKED);

	if( duell_display.init( duell_window) < 0)
	{
		MessageBox( duell_window, "Fehler beim Initialisieren der Grafik", "Duell-Fehlermeldung", MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
		return 0;
	}

	MoveWindow( duell_window, (GetSystemMetrics(SM_CXSCREEN)-duell_bruttobreite)/16,
		(GetSystemMetrics(SM_CYSCREEN)-duell_bruttohoehe)/16, duell_bruttobreite, duell_bruttohoehe, TRUE);

	ShowWindow( duell_window, nCmdShow);
	SetBkMode(duell_dc, TRANSPARENT);
	GetCurrentDirectory(256, Path_Buffer);

	while( TRUE)
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if( GetMessage( &msg, NULL, 0, 0 ) == 0)
				return 0; // Message ist WM_QUIT

			if( TranslateAccelerator( duell_window, acc, &msg) == 0)
			{
				TranslateMessage( &msg); 
				DispatchMessage( &msg);
			}
		}
		else
		{
			HRESULT hr;
			hr = duell_display.cooperative();
			if( hr < 0)
			{
				switch( hr )
				{
				case DDERR_EXCLUSIVEMODEALREADYSET:
					Sleep(10);
					break;
				case DDERR_WRONGMODE:
					duell_display.free_all();
					duell_display.init( duell_window);
					PostMessage( duell_window, WM_PAINT, 0, 0);
					break;
				}
			}
			else
			{
				if( mein_spiel.spiel_laeuft)
				{
					if( mein_spiel.step())
					{
						TextFlag = TRUE;
						mein_spiel.display();
						TextFlag = FALSE;
					}
				}
				else
				{
					WaitMessage();
					mein_spiel.reset_timer(); // Spieluhr laeuft nicht
					if (!StartOK)
					{
						StartOK = TRUE;
						PostMessage( duell_window, WM_COMMAND, ID_DUELL_NEUESSPIEL, 0);
					}
				}
			}
		}
	}
}
