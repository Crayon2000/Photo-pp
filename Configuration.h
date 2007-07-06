//---------------------------------------------------------------------------

#ifndef ConfigurationH
#define ConfigurationH
//---------------------------------------------------------------------------
#include <Controls.hpp>
#include <vcl\Registry.hpp>
//---------------------------------------------------------------------------

class TWindows
{
    public:
        int Width;
        int Height;
        int Left;
        int Top;
};

class TConfiguration
{
private:
    int ReadRegistry(TRegistry *, String, int);
    bool ReadRegistry(TRegistry *, String, bool);
    String ReadRegistry(TRegistry *, String, String);
public:
    TConfiguration();
    ~TConfiguration();
    void Load();
    void Save();

    bool ShowTime;
    TColor TimeColor;
    int TimeSize;
    String TimeFont;
    String TimeFormat;
    int Alpha;
    String FileName;
    bool AlwayOnTop;
    unsigned short Language;
    TWindows Screen;
    TColor BkGroundColor;
    bool Startup;
};
//---------------------------------------------------------------------------
#endif
