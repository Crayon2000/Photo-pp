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
#define     IDS_FILENOTFOUND    5000
#define     IDS_NONE            5001
#define     IDS_CUSTOM          5002
#define     IDS_BLACK           5003
#define     IDS_MAROON          5004
#define     IDS_GREEN           5005
#define     IDS_OLIVE           5006
#define     IDS_NAVY            5007
#define     IDS_PURPLE          5008
#define     IDS_TEAL            5009
#define     IDS_GRAY            5010
#define     IDS_SILVER          5011
#define     IDS_RED             5012
#define     IDS_LIME            5013
#define     IDS_YELLOW          5014
#define     IDS_BLUE            5015
#define     IDS_FUCHSIA         5016
#define     IDS_AQUA            5017
#define     IDS_WHITE           5018

//---------------------------------------------------------------------------
#endif
