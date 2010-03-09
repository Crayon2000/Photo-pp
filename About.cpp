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
    ProductName->Font->Size += 7;
    ProductName->Font->Style = TFontStyles() << fsBold;
    Comments->Font->Color = clBlue;
    Comments->Font->Style = TFontStyles() << fsUnderline;
    Comments->Cursor = crHandPoint;
}
//---------------------------------------------------------------------

void __fastcall TAboutBox::CommentsClick(TObject */*Sender*/)
{
    String strEmail = "mailto:" +
            Comments->Caption +
            "?subject=" +
            LoadLocalizedString(HInstance, 2000);
    ShellExecuteW(Handle,
            L"open",
            strEmail.w_str(),
            NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormShow(TObject */*Sender*/)
{
    this->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormCreate(TObject */*Sender*/)
{
    ScanComponent(this);

    ProgramIcon->Picture->Icon->Handle = (HICON)LoadImage(HInstance,
                                            "MAINICON",
                                            IMAGE_ICON,
                                            32, 32,
                                            LR_DEFAULTSIZE);
}
//---------------------------------------------------------------------------

