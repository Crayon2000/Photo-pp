//---------------------------------------------------------------------------
#pragma hdrstop

#include "Configuration.h"

#define COMPANY_KEY "SOFTWARE\\Crayon Application\\"
#define PRODUCT_KEY "Photo ++\\"
#define KEY         COMPANY_KEY PRODUCT_KEY
#define ROOT_KEY    HKEY_CURRENT_USER

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Input:   Nothing
// Output:  Nothing
// Return:  Nothing
// Purpose: Constructor
//------------------------------------------------------------------------------
TConfiguration::TConfiguration()
{
    ShowTime = false;
    TimeColor = clBlack;
    TimeSize = 12;
    TimeFont = "Arial";
    TimeFormat = "HH:mm:ss";
    Alpha = 255;
    FileName = "";
    AlwayOnTop = true;
    Language = PRIMARYLANGID(GetUserDefaultUILanguage());
    Screen.Left = 0;
    Screen.Top = 0;
    BkGroundColor = clNavy;
    Startup = false;
}

//------------------------------------------------------------------------------
// Input:   Nothing
// Output:  Nothing
// Return:  Nothing
// Purpose: Destructor
//------------------------------------------------------------------------------
TConfiguration::~TConfiguration()
{
}

//------------------------------------------------------------------------------
// Input:   Nothing
// Output:  Nothing
// Return:  Nothing
// Purpose: Load configuration from registry
//------------------------------------------------------------------------------
void TConfiguration::Load()
{
    TRegistry *reg = new TRegistry();
    reg->RootKey = ROOT_KEY;
    // On crée la clé si elle n'existe pas
    reg->OpenKey(KEY, TRUE);

    Alpha = ReadRegistry(reg, "Alpha", Alpha);
    ShowTime = ReadRegistry(reg, "ShowTime", ShowTime);
    TimeColor = (TColor)ReadRegistry(reg, "TimeColor", TimeColor);
    TimeSize = ReadRegistry(reg, "TimeSize", TimeSize);
    TimeFont = ReadRegistry(reg, "TimeFont", TimeFont);
    TimeFormat = ReadRegistry(reg, "TimeFormat", TimeFormat);
    FileName = ReadRegistry(reg, "picFile", FileName);
    AlwayOnTop = ReadRegistry(reg, "AlwayOnTop", AlwayOnTop);
    Language = ReadRegistry(reg, "Language", Language);
    Screen.Width = ReadRegistry(reg, "Width", Screen.Width);
    Screen.Height = ReadRegistry(reg, "Height", Screen.Height);
    Screen.Left = ReadRegistry(reg, "Left", Screen.Left);
    Screen.Top = ReadRegistry(reg, "Top", Screen.Top);
    BkGroundColor = (TColor)ReadRegistry(reg, "BkGroundColor", BkGroundColor);

    delete reg;
}

//------------------------------------------------------------------------------
// Input:   Nothing
// Output:  Nothing
// Return:  Nothing
// Purpose: Save configuration to registry
//------------------------------------------------------------------------------
void TConfiguration::Save()
{
    //Écriture dans le registre
    TRegistry *reg = new TRegistry();
    reg->RootKey = ROOT_KEY;
    // On crée la clé si elle n'existe pas
    reg->OpenKey(KEY, TRUE);

    reg->WriteBool("ShowTime", ShowTime);
    reg->WriteInteger("TimeColor", TimeColor);
    reg->WriteInteger("TimeSize", TimeSize);
    reg->WriteString("TimeFont", TimeFont);
    reg->WriteString("TimeFormat", TimeFormat);
    reg->WriteInteger("Alpha", Alpha);
    reg->WriteString("picFile", FileName);
    reg->WriteBool("AlwayOnTop", AlwayOnTop);
    reg->WriteInteger("Language", Language);
    reg->WriteInteger("Left", Screen.Left);
    reg->WriteInteger("Top", Screen.Top);
    reg->WriteInteger("Height", Screen.Height);
    reg->WriteInteger("Width", Screen.Width);
    reg->WriteInteger("BkGroundColor", BkGroundColor);

    delete reg;
}

//------------------------------------------------------------------------------
int TConfiguration::ReadRegistry(TRegistry *reg, String Name, int Default)
{
    try
    {
        return reg->ReadInteger(Name);
    }
    catch (...)
    {
        return Default;
    }
}

//------------------------------------------------------------------------------
bool TConfiguration::ReadRegistry(TRegistry *reg, String Name, bool Default)
{
    try
    {
        return reg->ReadBool(Name);
    }
    catch (...)
    {
        return Default;
    }
}

//------------------------------------------------------------------------------
double TConfiguration::ReadRegistry(TRegistry *reg, String Name, double Default)
{
    try
    {
        return reg->ReadFloat(Name);
    }
    catch (...)
    {
        return Default;
    }
}

//------------------------------------------------------------------------------
String TConfiguration::ReadRegistry(TRegistry *reg, String Name, String Default)
{
    return reg->ValueExists(Name) ? reg->ReadString(Name) : Default;
}
