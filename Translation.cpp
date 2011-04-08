//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Translation.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
static WORD gwLanguage = MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT);

String __fastcall LoadLocalizedString(UINT uID)
{
    HRSRC hrsrc = FindResourceEx(HInstance, RT_STRING,
                MAKEINTRESOURCE((uID >> 4) + 1), gwLanguage);
    if(hrsrc == NULL)
    {   // If not found in requested language, we use French
        hrsrc = FindResourceEx(HInstance, RT_STRING,
                    MAKEINTRESOURCE((uID >> 4) + 1),
                    MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT));
        if(hrsrc == NULL)
            return NULL;
    }
    HGLOBAL hGlobal = LoadResource(HInstance, hrsrc);
    if(hGlobal == NULL)
        return NULL;
    LPWSTR lpString = (LPWSTR)LockResource(hGlobal);
    if(lpString == NULL)
        return NULL;
    for(UINT i = 0; i < (uID & 0xf); ++i)
    {
        lpString += *lpString + 1;
    }

    return String(lpString).SubString(2, ((WORD*)lpString)[0]);
}
//---------------------------------------------------------------------------

void __fastcall ScanComponent(TForm *AForm)
{
    UINT uID;

    if(AForm->Tag)
    {
        AForm->Caption = LoadLocalizedString(AForm->Tag);
    }
    for(int i = 0; i < AForm->ComponentCount; ++i)
    {
        uID = ((TComponent*)AForm->Components[i])->Tag;
        if(AForm->Components[i]->ClassNameIs("TButton"))
        {
            dynamic_cast<TButton *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TLabel"))
        {
            dynamic_cast<TLabel *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TGroupBox"))
        {
            dynamic_cast<TGroupBox *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TCheckBox"))
        {
            dynamic_cast<TCheckBox *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TMenuItem") && uID)
        {
            dynamic_cast<TMenuItem *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TOpenPictureDialog"))
        {
            dynamic_cast<TOpenDialog *>(AForm->Components[i])->Title =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TTabSheet"))
        {
            dynamic_cast<TTabSheet *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TRadioButton"))
        {
            dynamic_cast<TRadioButton *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall SetLanguage(WORD ALanguage, WORD ASubLanguage)
{
    gwLanguage = MAKELANGID(ALanguage, ASubLanguage);
}
//---------------------------------------------------------------------------