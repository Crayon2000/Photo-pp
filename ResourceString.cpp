//---------------------------------------------------------------------------
#pragma hdrstop
#include "ResourceString.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Must be defined only once.
TResourceString* TResourceString::FInstance = NULL;

 /**
 * Singleton instanciator.
 * Always use this method to instanciate TResourceString.
 * @return A reference to the Singleton TResourceString.
 * @note It creates the Static Instance on the first call, and then returns
 * the same Static Instance for other calls.
 */
TResourceString& __fastcall TResourceString::Instance()
{
    if(FInstance == NULL)
    {
        FInstance = new TResourceString();
    }

    return *FInstance;
}

/**
 * Destroys the singleton instance of TResourceString.
 * If Instance() is called after this call, the Singleton Instance
 * will be re-created.
 */
void __fastcall TResourceString::Destroy()
{
    delete FInstance;
    FInstance = NULL;
}

/**
 * Assign a string to a specified String Resource.
 * @param AResStringRec String Resource we wish to modify/add.
 * @param[in] AStrID String we wish to add to a specified string resource.
 */
void __fastcall TResourceString::Set(TResStringRec& AResStringRec, String AStrID)
{
    std::map<TResStringRec*, wchar_t*>::iterator It = FResStringMap.find(&AResStringRec);

    if(It != FResStringMap.end())
    {
        // We found an existing item in the map, delete it, and store the new value.
        delete[] It->second;
    }

    wchar_t* NewString = new wchar_t[AStrID.Length() + 1];

    wcscpy(NewString, AStrID.c_str());

    FResStringMap[&AResStringRec] = NewString;

    DWORD OldProtect;

    VirtualProtect(&AResStringRec, sizeof(AResStringRec), PAGE_EXECUTE_READWRITE, &OldProtect);
#if __BORLANDC__ >= 0x630
    // For C++Builder XE and over
    AResStringRec.Identifier = Integer(NewString);
#else
    AResStringRec.ident = Integer(NewString);
#endif
    VirtualProtect(&AResStringRec, sizeof(AResStringRec), OldProtect, &OldProtect);
}

/**
 * Private Constructor.
 */
__fastcall TResourceString::TResourceString()
{

}

/**
 * Private Destructor.
 */
__fastcall TResourceString::~TResourceString()
{
    std::map<TResStringRec*, wchar_t*>::iterator It = FResStringMap.begin();
    std::map<TResStringRec*, wchar_t*>::iterator End = FResStringMap.end();

    for(; It != End; ++It)
    {
        delete[] It->second;
    }
}

