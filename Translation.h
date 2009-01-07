//---------------------------------------------------------------------------

#ifndef TranslationH
#define TranslationH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------
AnsiString __fastcall LoadLocalizedString(HINSTANCE, UINT);
void __fastcall ScanComponent(TForm *);

//---------------------------------------------------------------------------
// Externals
//---------------------------------------------------------------------------
extern WORD gwLanguage;

//---------------------------------------------------------------------------
// Definitions
//---------------------------------------------------------------------------
#define     IDS_FILENOTFOUND    6000
#define     IDS_NONE            6001
#define     IDS_CUSTOM          6002
#define     IDS_BLACK           6003
#define     IDS_MAROON          6004
#define     IDS_GREEN           6005
#define     IDS_OLIVE           6006
#define     IDS_NAVY            6007
#define     IDS_PURPLE          6008
#define     IDS_TEAL            6009
#define     IDS_GRAY            6010
#define     IDS_SILVER          6011
#define     IDS_RED             6012
#define     IDS_LIME            6013
#define     IDS_YELLOW          6014
#define     IDS_BLUE            6015
#define     IDS_FUCHSIA         6016
#define     IDS_AQUA            6017
#define     IDS_WHITE           6018
#define     IDS_ALLIMGFILES     6020

//---------------------------------------------------------------------------
#endif
