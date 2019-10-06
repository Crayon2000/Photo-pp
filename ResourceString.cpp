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
 * @return A reference to the singleton TResourceString.
 * @note It creates the static instance on the first call, and then returns
 * the same static instance for other calls.
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
 * If Instance() is called after this call, the singleton instance
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
void __fastcall TResourceString::Set(TResStringRec& AResStringRec, const String AStrID)
{
    std::map<TResStringRec*, wchar_t*>::iterator It = FResStringMap.find(&AResStringRec);
    if(It != FResStringMap.end())
    {
        // We found an existing item in the map, delete it, and store the new value.
        delete[] It->second;
    }

    const int StrLength = AStrID.Length() + 1;
    wchar_t* NewString = new wchar_t[StrLength];
    wcsncpy(NewString, AStrID.c_str(), StrLength);

    FResStringMap[&AResStringRec] = NewString;

    DWORD OldProtect;
    bool Result = VirtualProtect(&AResStringRec, sizeof(AResStringRec), PAGE_EXECUTE_READWRITE, &OldProtect);
    if(Result == true)
    {
        AResStringRec.Identifier = NativeUInt(NewString);
        VirtualProtect(&AResStringRec, sizeof(AResStringRec), OldProtect, &OldProtect);
    }
}

/**
 * Private constructor.
 */
__fastcall TResourceString::TResourceString()
{
}

/**
 * Private destructor.
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

