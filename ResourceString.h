/**
 * @file ResourceString.h
 * Contains the TResourceString class.
 */

//---------------------------------------------------------------------------
#ifndef ResourceStringH
#define ResourceStringH
//---------------------------------------------------------------------------
#include <System.hpp>
#include <map>
#include <Vcl.Consts.hpp>
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

    static TResourceString *FInstance; /**< Pointer to a singleton object. */
    std::map<TResStringRec*, wchar_t*> FResStringMap; /**< Map that holds the string resource and its string text. */

public:

    static TResourceString& __fastcall Instance();
    static void __fastcall Destroy();
    void __fastcall Set(TResStringRec& AResStringRec, const String AStrID);
};

//---------------------------------------------------------------------------
#endif
