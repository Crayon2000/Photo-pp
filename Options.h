//---------------------------------------------------------------------------
#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:  // IDE-managed Components
    TTimer *Timer;
    TPageControl *pctrlOptions;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox3;
    TEdit *txtExample;
    TCheckBox *chkShowTime;
    TGroupBox *GroupBox1;
    TLabel *Label5;
    TLabel *Label10;
    TLabel *Label3;
    TLabel *Label2;
    TLabel *Label1;
    TColorBox *ColorBox;
    TComboBox *cboSize;
    TComboBox *cboFont;
    TComboBox *cboFormat;
    TGroupBox *GroupBox2;
    TTrackBar *tbarAlpha;
    TLabel *Label4;
    TLabel *Label8;
    TGroupBox *GroupBox4;
    TColorBox *ColorBoxBk;
    TCheckBox *chkStartup;
    TGroupBox *GroupBox5;
    TRadioButton *optKeepAR;
    TRadioButton *optStretch;
    TRadioButton *optTiled;
    TGroupBox *GroupBox6;
    TCheckBox *chkFlipH;
    TCheckBox *chkFlipV;
    TGroupBox *GroupBox7;
    TButton *cmdOK;
    TButton *cmdCancel;
    TPanel *pnlBottom;
    TPanel *Panel1;
    TComboBox *cboInterval;
    TLabel *Label6;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall pctrlOptionsChange(TObject *Sender);
private:  // User declarations
public:   // User declarations
    __fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
