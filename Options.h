//---------------------------------------------------------------------------

#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:  // IDE-managed Components
    TGroupBox *GroupBox2;
    TCheckBox *chkShowTime;
    TButton *cmdOK;
    TButton *cmdCancel;
    TColorBox *ColorBox;
    TLabel *Label1;
    TLabel *Label2;
    TComboBox *cboSize;
    TLabel *Label3;
    TComboBox *cboFont;
    TComboBox *cboFormat;
    TLabel *Label10;
    TGroupBox *GroupBox1;
    TLabel *Label5;
    TGroupBox *GroupBox3;
    TEdit *txtExample;
    TTimer *Timer;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall TimerTimer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:  // User declarations
public:   // User declarations
    __fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
