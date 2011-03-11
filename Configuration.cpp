//---------------------------------------------------------------------------
#include <Registry.hpp>
#pragma hdrstop

#include "Configuration.h"

#define COMPANY_KEY "SOFTWARE\\Crayon Application\\"
#define PRODUCT_KEY "Photo ++\\"
#define KEY         COMPANY_KEY PRODUCT_KEY
#define ROOT_KEY    HKEY_CURRENT_USER

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

/**
 * Constructor.
 */
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
    Position = 0;
    FlipH = false;
    FlipV = false;
}

/**
 * Destructor.
 */
TConfiguration::~TConfiguration()
{
}

/**
 * Load configuration from registry.
 */
void __fastcall TConfiguration::Load()
{
    TRegistry *reg = new TRegistry();
    reg->RootKey = ROOT_KEY;
    // On cr�e la cl� si elle n'existe pas
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
    Position = ReadRegistry(reg, "Position", Position);
    FlipH = ReadRegistry(reg, "FlipH", FlipH);
    FlipV = ReadRegistry(reg, "FlipV", FlipV);

    delete reg;
}

/**
 * Save configuration to registry.
 */
void __fastcall TConfiguration::Save()
{
    // �criture dans le registre
    TRegistry *reg = new TRegistry();
    reg->RootKey = ROOT_KEY;
    // On cr�e la cl� si elle n'existe pas
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
    reg->WriteInteger("Position", Position);
    reg->WriteBool("FlipH", FlipH);
    reg->WriteBool("FlipV", FlipV);

    delete reg;
}

/**
 * Read a value from the registry.
 * @param Registry Pointer to a TRegistry object.
 * @param Name The name of the data value to read.
 * @param Default Value to return in case of error.
 * @return An integer value from a specified data value associated with the current key.
 */
int __fastcall TConfiguration::ReadRegistry(TRegistry *Registry, String Name, int Default)
{
    try
    {
        return Registry->ReadInteger(Name);
    }
    catch (...)
    {
        return Default;
    }
}

/**
 * Read a value from the registry.
 * @param Registry Pointer to a TRegistry object.
 * @param Name The name of the data value to read.
 * @param Default Value to return in case of error.
 * @return A boolean value from a specified data value associated with the current key.
 */
bool __fastcall TConfiguration::ReadRegistry(TRegistry *Registry, String Name, bool Default)
{
    try
    {
        return Registry->ReadBool(Name);
    }
    catch (...)
    {
        return Default;
    }
}

/**
 * Read a value from the registry.
 * @param Registry Pointer to a TRegistry object.
 * @param Name The name of the data value to read.
 * @param Default Value to return in case of error.
 * @return A double value from a specified data value associated with the current key.
 */
double __fastcall TConfiguration::ReadRegistry(TRegistry *Registry, String Name, double Default)
{
    try
    {
        return Registry->ReadFloat(Name);
    }
    catch (...)
    {
        return Default;
    }
}

/**
 * Read a value from the registry.
 * @param Registry Pointer to a TRegistry object.
 * @param Name The name of the data value to read.
 * @param Default Value to return in case of error.
 * @return A String value from a specified data value associated with the current key.
 */
String __fastcall TConfiguration::ReadRegistry(TRegistry *Registry, String Name, String Default)
{
    return Registry->ValueExists(Name) ? Registry->ReadString(Name) : Default;
}
