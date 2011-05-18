/**
 * @file ResourceString.h
 * Contains the TResourceString class.
 */

//---------------------------------------------------------------------------
#ifndef ResourceStringH
#define ResourceStringH
//---------------------------------------------------------------------------
#include <system.hpp>
#include <map>
#include <Consts.hpp>
//---------------------------------------------------------------------------

/**
 * Class that modifies/adds strings to a specific string resource.
 */
class TResourceString : public TObject
{
    typedef TObject inherited;

private:

    __fastcall TResourceString();
    virtual __fastcall ~TResourceString();

    static TResourceString *FInstance;                /**< Pointer to a Singleton object. */
    std::map<TResStringRec*, wchar_t*> FResStringMap;   /**< Map that holds the string resource and its string text. */

public:

    static TResourceString& __fastcall Instance();
    static void __fastcall Destroy();
    void __fastcall Set(TResStringRec& AResStringRec, String AStrID);
};

//---------------------------------------------------------------------------
#endif
