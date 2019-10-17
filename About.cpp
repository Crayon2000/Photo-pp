//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "Translation.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
  : TForm(AOwner)
{
    ScanComponent(this);

    ProductName->Font->Size += 7;
    ProductName->Font->Style = TFontStyles() << TFontStyle::fsBold;
    Comments->Font->Color = clBlue;
    Comments->Font->Style = TFontStyles() << TFontStyle::fsUnderline;
    Comments->Cursor = crHandPoint;

    ProgramIcon->Picture->Icon->Handle = (HICON)LoadImageW(HInstance,
                                            L"MAINICON",
                                            IMAGE_ICON,
                                            32, 32,
                                            LR_DEFAULTSIZE);
}
//---------------------------------------------------------------------

void __fastcall TAboutBox::CommentsClick(TObject *Sender)
{
    const String LEmail =
            "mailto:" + Comments->Caption +
            "?subject=" + LoadLocalizedString(2000);
    ShellExecuteW(Handle, L"open", LEmail.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormShow(TObject *Sender)
{
    this->FormStyle = TFormStyle::fsStayOnTop;
}
//---------------------------------------------------------------------------

