//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <jpeg.hpp>
#include <Menus.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include "Configuration.h"
#include <GIFImg.hpp>
#include <pngimage.hpp>
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
    TMenuItem *mnuWallpaper;
    TMenuItem *mnuShowOptions;
    TMenuItem *mnuLanguage;
    TMenuItem *mnuFrench;
    TMenuItem *mnuEnglish;
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
    void __fastcall mnuWallpaperClick(TObject *Sender);
    void __fastcall mnuShowOptionsClick(TObject *Sender);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall ChangeLanguage(TObject *Sender);
private:  // User declarations
    bool dblClick;
    Types::TRect befFullScr;
    bool mouseDown;
    int oldX;
    int oldY;

    TConfiguration Config;

    Graphics::TBitmap *tempBMP;

    void __fastcall DialogShow(TObject *Sender);
    void __fastcall DialogFolderChange(TObject *Sender);
    void __fastcall DialogSelectionChange(TObject *Sender);

    void __fastcall LoadImage(String imgToLoad);
    void __fastcall DropFiles(TMessage &Message);
    void __fastcall EndSession(TMessage &Message);
    void __fastcall LoadResImage(Graphics::TPicture *Picture, const String Identifier);
    void __fastcall FullScreen();
    void __fastcall LoadLanguage();
    void __fastcall ApplySettings();
    bool __fastcall SetAtStarup();
public:   // User declarations
    __fastcall TfrmMain(TComponent* Owner);

    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_DROPFILES, TMessage, DropFiles)
        MESSAGE_HANDLER(WM_ENDSESSION, TMessage, EndSession)
    END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
