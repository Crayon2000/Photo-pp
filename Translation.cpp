//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Translation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

/**
 * The current language. The default value is French.
 */
static WORD gLanguage = MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT);

/**
 * Load localized String.
 */
String __fastcall LoadLocalizedString(UINT uID)
{
    HRSRC hrsrc = FindResourceEx(HInstance, RT_STRING,
                MAKEINTRESOURCE((uID >> 4) + 1), gLanguage);
    if(hrsrc == NULL)
    {   // If not found in requested language, we use French
        hrsrc = FindResourceEx(HInstance, RT_STRING,
                    MAKEINTRESOURCE((uID >> 4) + 1),
                    MAKELANGID(LANG_FRENCH, SUBLANG_DEFAULT));
        if(hrsrc == NULL)
        {
            return NULL;
        }
    }
    HGLOBAL hGlobal = LoadResource(HInstance, hrsrc);
    if(hGlobal == NULL)
    {
        return NULL;
    }
    LPWSTR lpString = (LPWSTR)LockResource(hGlobal);
    if(lpString == NULL)
    {
        return NULL;
    }
    for(UINT i = 0; i < (uID & 0xf); ++i)
    {
        lpString += *lpString + 1;
    }

    return String(lpString).SubString(2, ((WORD*)lpString)[0]);
}

/**
 * Scan components.
 */
void __fastcall ScanComponent(TForm *AForm)
{
    if(AForm->Tag != 0)
    {
        AForm->Caption = LoadLocalizedString(AForm->Tag);
    }
    for(int i = 0; i < AForm->ComponentCount; ++i)
    {
        const UINT uID = ((TComponent*)AForm->Components[i])->Tag;
        if(AForm->Components[i]->ClassNameIs("TButton") == true)
        {
            dynamic_cast<TButton *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TLabel") == true)
        {
            dynamic_cast<TLabel *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TGroupBox") == true)
        {
            dynamic_cast<TGroupBox *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TCheckBox") == true)
        {
            dynamic_cast<TCheckBox *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TMenuItem") == true && uID != 0)
        {
            dynamic_cast<TMenuItem *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TOpenPictureDialog") == true)
        {
            dynamic_cast<TOpenDialog *>(AForm->Components[i])->Title =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TTabSheet") == true)
        {
            dynamic_cast<TTabSheet *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
        else if(AForm->Components[i]->ClassNameIs("TRadioButton") == true)
        {
            dynamic_cast<TRadioButton *>(AForm->Components[i])->Caption =
                LoadLocalizedString(uID);
        }
    }
}

/**
 * Set language.
 */
void __fastcall SetLanguage(WORD ALanguage, WORD ASubLanguage)
{
    gLanguage = MAKELANGID(ALanguage, ASubLanguage);
}

