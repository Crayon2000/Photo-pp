//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Menus.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TConfiguration;

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
    TMenuItem *mnuWallpaper;
    TMenuItem *mnuShowOptions;
    TMenuItem *mnuLanguage;
    TMenuItem *mnuFrench;
    TMenuItem *mnuEnglish;
    TTimer *TimerSlideShow;
    TMenuItem *mnuChoisirDossier;
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
    void __fastcall TimerSlideShowTimer(TObject *Sender);
    void __fastcall mnuChoisirDossierClick(TObject *Sender);
private:  // User declarations
    bool FDblClick;
    Types::TRect FBefFullScreen;
    bool FMouseDown;
    int FOldX;
    int FOldY;
    int FImageIndex;

    TConfiguration *FConfig;
    TStringList *FExtList;
    TStringList *FFilesInDir;

    Graphics::TPicture *FImage;
    Graphics::TBitmap *FTempBMP;

    void __fastcall DialogShow(TObject *Sender);
    void __fastcall DialogFolderChange(TObject *Sender);

    void __fastcall LoadPath(const String Path);
    void __fastcall LoadImage(String ImgToLoad);
    void __fastcall LoadDirectory(String DirToLoad);
    void __fastcall DropFiles(TMessage &Message);
    void __fastcall EndSession(TMessage &Message);
    void __fastcall LoadResImage(Graphics::TPicture *Picture, const String Identifier);
    void __fastcall FullScreen();
    void __fastcall LoadLanguage();
    void __fastcall ApplySettings();
    bool __fastcall SetAtStarup();
    bool __fastcall IsValidExtension(const String FileName);
    bool __fastcall ChangeImage();
public:   // User declarations
    __fastcall TfrmMain(TComponent* Owner);
    __fastcall ~TfrmMain();

    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_DROPFILES, TMessage, DropFiles)
        MESSAGE_HANDLER(WM_ENDSESSION, TMessage, EndSession)
    END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
