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
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::CommentsClick(TObject *Sender)
{
    AnsiString strEmail = "mailto:" +
                Comments->Caption +
                "?subject=" +
                LoadLocalizedString(HInstance, 2000);
    ShellExecute(Handle,
            "open",
            strEmail.c_str(),
            NULL,NULL,SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormShow(TObject *Sender)
{
    this->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
    ScanComponent(this);
}
//---------------------------------------------------------------------------

