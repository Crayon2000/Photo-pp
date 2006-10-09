//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <vcl\Registry.hpp>   // Pour le REGISTRE ou INI
#include "About.h"
#include "Options.h"
#include <jpeg.hpp>
#include <Menus.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <XPMan.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:  // IDE-managed Components
    TPopupMenu *PopupMenu;
    TMenuItem *mnuQuitter;
    TMenuItem *mnuBar1;
    TMenuItem *mnuAPropos;
    TMenuItem *mnuChoisir;
    TMenuItem *mnuGradeurOriginal;
    TMenuItem *mnuPremierPlan;
    TMenuItem *mnuBar2;
    TMenuItem *mnuBar3;
    TTimer *Timer;
    TImage *iRightBottomCorner;
    TImage *iLeftBottomCorner;
    TImage *iLeftTopCorner;
    TImage *iRightTopCorner;
    TImage *iBottom;
    TImage *iTop;
    TImage *iLeft;
    TImage *iRight;
    TImage *Image;
    TOpenPictureDialog *Dialog;
    TMenuItem *mnuStart;
    TMenuItem *mnuWallpaper;
    TMenuItem *mnuShowTime;
    TXPManifest *XPManifest;
    void __fastcall mnuQuitterClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Border(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall mnuGradeurOriginalClick(TObject *Sender);
    void __fastcall mnuAProposClick(TObject *Sender);
    void __fastcall mnuChoisirClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall mnuPremierPlanClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall mnuStartClick(TObject *Sender);
    void __fastcall mnuWallpaperClick(TObject *Sender);
    void __fastcall mnuShowTimeClick(TObject *Sender);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall FormResize(TObject *Sender);
private:  // User declarations
    bool dblClick;
    TRect befFullScr;
    bool mouseDown;
    bool isAlwayOnTop;
    String picFile;
    int oldX;
    int oldY;

    Graphics::TBitmap *tempBMP;

    void __fastcall LoadImage(String imgToLoad);
    void __fastcall StickBorder(int stickGap);
    void __fastcall DropFiles(TMessage &Message);
    void __fastcall FullScreen();
public:   // User declarations
    __fastcall TfrmMain(TComponent* Owner);

    bool gbShowTime;
    TColor gtTimeColor;
    int gnTimeSize;
    String gsTimeFont;
    String gsFormat;

    BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(WM_DROPFILES, TMessage, DropFiles)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
