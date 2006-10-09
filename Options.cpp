//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::FormCreate(TObject *Sender)
{
    // Met les noms de couleur en français
    ColorBox->Items->Strings[0] = "Personnalisé...";
    ColorBox->Items->Strings[1] = "Noir";
    ColorBox->Items->Strings[2] = "Marron";
    ColorBox->Items->Strings[3] = "Vert";
    ColorBox->Items->Strings[4] = "Olive";
    ColorBox->Items->Strings[5] = "Bleu marine";
    ColorBox->Items->Strings[6] = "Violet";
    ColorBox->Items->Strings[7] = "Bleu-vert";
    ColorBox->Items->Strings[8] = "Gris";
    ColorBox->Items->Strings[9] = "Argenté";
    ColorBox->Items->Strings[10] = "Rouge";
    ColorBox->Items->Strings[11] = "Lime";
    ColorBox->Items->Strings[12] = "Jaune";
    ColorBox->Items->Strings[13] = "Bleu";
    ColorBox->Items->Strings[14] = "Magenta";
    ColorBox->Items->Strings[15] = "Cyan";
    ColorBox->Items->Strings[16] = "Blanc";

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
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormShow(TObject *Sender)
{
    this->FormStyle = fsStayOnTop;
    Timer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::TimerTimer(TObject *Sender)
{
    String strFormat = cboFormat->Text;
    String strTime;

    strFormat = StringReplace(StringReplace(strFormat, "mm", "nn",
                TReplaceFlags()), "tt", "am/pm", TReplaceFlags());
    strTime = FormatDateTime(strFormat, Now());

    txtExample->Text = strTime;
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

