//---------------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include "Translation.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
static WORD gwLanguage = MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT);

String __fastcall LoadLocalizedString(HINSTANCE hInstance, UINT uID)
{
    HRSRC hrsrc = FindResourceEx(hInstance, RT_STRING,
                MAKEINTRESOURCE((uID >> 4) + 1), gwLanguage);
    if(hrsrc == NULL)
    {   // If not found in requested language, we use French
        hrsrc = FindResourceEx(hInstance, RT_STRING,
                    MAKEINTRESOURCE((uID >> 4) + 1),
                    MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT));
        if(hrsrc == NULL)
            return NULL;
    }
    HGLOBAL hGlobal = LoadResource(hInstance, hrsrc);
    if(hGlobal == NULL)
        return NULL;
    LPWSTR lpString = (LPWSTR)LockResource(hGlobal);
    if(lpString == NULL)
        return NULL;
    for(UINT i = 0; i < (uID & 0xf); i++)
    {
        lpString += *lpString + 1;
    }

    String strTemp = (String)lpString;
    return strTemp.SubString(2, ((WORD*)lpString)[0]);
}
//---------------------------------------------------------------------------

void __fastcall ScanComponent(TForm *tForm)
{
    UINT uID;
    String strBuffer;

    if(tForm->Tag)
    {
        tForm->Caption = LoadLocalizedString(HInstance, tForm->Tag);
    }
    for(int i = 0; i < tForm->ComponentCount; i++)
    {
        uID = ((TComponent*)tForm->Components[i])->Tag;
        if(tForm->Components[i]->ClassNameIs("TButton"))
        {
            strBuffer = LoadLocalizedString(HInstance, uID);
            dynamic_cast<TButton *>(tForm->Components[i])->Caption = strBuffer;
        }
        else if(tForm->Components[i]->ClassNameIs("TLabel"))
        {
            strBuffer = LoadLocalizedString(HInstance, uID);
            dynamic_cast<TLabel *>(tForm->Components[i])->Caption = strBuffer;
        }
        else if(tForm->Components[i]->ClassNameIs("TGroupBox"))
        {
            strBuffer = LoadLocalizedString(HInstance, uID);
            dynamic_cast<TGroupBox *>(tForm->Components[i])->Caption = strBuffer;
        }
        else if(tForm->Components[i]->ClassNameIs("TCheckBox"))
        {
            strBuffer = LoadLocalizedString(HInstance, uID);
            dynamic_cast<TCheckBox *>(tForm->Components[i])->Caption = strBuffer;
        }
        else if(tForm->Components[i]->ClassNameIs("TMenuItem"))
        {
            if(uID)
            {
                strBuffer = LoadLocalizedString(HInstance, uID);
                dynamic_cast<TMenuItem *>(tForm->Components[i])->Caption = strBuffer;
            }
        }
        else if(tForm->Components[i]->ClassNameIs("TOpenPictureDialog"))
        {
            strBuffer = LoadLocalizedString(HInstance, uID);
            dynamic_cast<TOpenDialog *>(tForm->Components[i])->Title = strBuffer;
        }
        else if(tForm->Components[i]->ClassNameIs("TTabSheet"))
        {
            strBuffer = LoadLocalizedString(HInstance, uID);
            dynamic_cast<TTabSheet *>(tForm->Components[i])->Caption = strBuffer;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall SetLanguage(WORD wLanguage, WORD wSubLanguage)
{
    gwLanguage = MAKELANGID(wLanguage, wSubLanguage);
}
//---------------------------------------------------------------------------