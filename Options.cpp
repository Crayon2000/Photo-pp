//---------------------------------------------------------------------------
#include <vcl.h>
#include <StrUtils.hpp>
#pragma hdrstop

#include "Options.h"
#include "Translation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
    : TForm(Owner)
{
    // Taille disponible pour la police
    cboSize->Items->Add("8");
    cboSize->Items->Add("10");
    cboSize->Items->Add("12");
    cboSize->Items->Add("14");
    cboSize->Items->Add("18");
    cboSize->Items->Add("20");
    cboSize->Items->Add("22");
    cboSize->Items->Add("24");
    cboSize->Items->Add("26");
    cboSize->Items->Add("28");
    cboSize->Items->Add("36");
    cboSize->Items->Add("48");

    // Format de l'heure
    cboFormat->Items->Add("HH:mm:ss");
    cboFormat->Items->Add("hh:mm:ss tt");
    cboFormat->Items->Add("H:mm:ss");
    cboFormat->Items->Add("h:mm:ss tt");
    cboFormat->Items->Add("H:mm");
    cboFormat->Items->Add("h:mm tt");

    // Police de caractère
    cboFont->Items = Screen->Fonts;

    // Select first tab
    pctrlOptions->TabIndex = 0;

    ScanComponent(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormShow(TObject *Sender)
{
    this->FormStyle = fsStayOnTop;
    pctrlOptionsChange(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::TimerTimer(TObject *Sender)
{
    String strFormat = ReplaceStr(ReplaceStr(cboFormat->Text, "mm", "nn"),
                "tt", "am/pm");

    txtExample->Text = FormatDateTime(strFormat, Now());
    txtExample->Font->Size = cboSize->Text.ToInt();
    txtExample->Font->Name = cboFont->Text;
    txtExample->Font->Color = ColorBox->Selected;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormClose(TObject *Sender, TCloseAction &Action)
{
    Timer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::pctrlOptionsChange(TObject *Sender)
{
    Timer->Enabled = (pctrlOptions->TabIndex == 1) ? true : false;
}
//---------------------------------------------------------------------------

