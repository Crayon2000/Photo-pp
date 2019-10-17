//---------------------------------------------------------------------------
#include <System.Win.Registry.hpp>
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
    Interval = 5000;
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
    TRegistry *LRegistry = new TRegistry();
    LRegistry->RootKey = ROOT_KEY;
    // The key is created if it does not exist
    LRegistry->OpenKey(KEY, true);

    Alpha = ReadRegistry(LRegistry, "Alpha", Alpha);
    ShowTime = ReadRegistry(LRegistry, "ShowTime", ShowTime);
    TimeColor = (TColor)ReadRegistry(LRegistry, "TimeColor", TimeColor);
    TimeSize = ReadRegistry(LRegistry, "TimeSize", TimeSize);
    TimeFont = ReadRegistry(LRegistry, "TimeFont", TimeFont);
    TimeFormat = ReadRegistry(LRegistry, "TimeFormat", TimeFormat);
    FileName = ReadRegistry(LRegistry, "picFile", FileName);
    AlwayOnTop = ReadRegistry(LRegistry, "AlwayOnTop", AlwayOnTop);
    Language = ReadRegistry(LRegistry, "Language", Language);
    Screen.Width = ReadRegistry(LRegistry, "Width", Screen.Width);
    Screen.Height = ReadRegistry(LRegistry, "Height", Screen.Height);
    Screen.Left = ReadRegistry(LRegistry, "Left", Screen.Left);
    Screen.Top = ReadRegistry(LRegistry, "Top", Screen.Top);
    BkGroundColor = (TColor)ReadRegistry(LRegistry, "BkGroundColor", BkGroundColor);
    Position = ReadRegistry(LRegistry, "Position", Position);
    FlipH = ReadRegistry(LRegistry, "FlipH", FlipH);
    FlipV = ReadRegistry(LRegistry, "FlipV", FlipV);
    Interval = ReadRegistry(LRegistry, "Interval", Interval);

    delete LRegistry;
}

/**
 * Save configuration to registry.
 */
void __fastcall TConfiguration::Save()
{
    // Write into the registry
    TRegistry *LRegistry = new TRegistry();
    LRegistry->RootKey = ROOT_KEY;
    // The key is created if it does not exist
    LRegistry->OpenKey(KEY, true);

    LRegistry->WriteBool("ShowTime", ShowTime);
    LRegistry->WriteInteger("TimeColor", TimeColor);
    LRegistry->WriteInteger("TimeSize", TimeSize);
    LRegistry->WriteString("TimeFont", TimeFont);
    LRegistry->WriteString("TimeFormat", TimeFormat);
    LRegistry->WriteInteger("Alpha", Alpha);
    LRegistry->WriteString("picFile", FileName);
    LRegistry->WriteBool("AlwayOnTop", AlwayOnTop);
    LRegistry->WriteInteger("Language", Language);
    LRegistry->WriteInteger("Left", Screen.Left);
    LRegistry->WriteInteger("Top", Screen.Top);
    LRegistry->WriteInteger("Height", Screen.Height);
    LRegistry->WriteInteger("Width", Screen.Width);
    LRegistry->WriteInteger("BkGroundColor", BkGroundColor);
    LRegistry->WriteInteger("Position", Position);
    LRegistry->WriteBool("FlipH", FlipH);
    LRegistry->WriteBool("FlipV", FlipV);
    LRegistry->WriteInteger("Interval", Interval);

    delete LRegistry;
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

