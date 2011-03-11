//---------------------------------------------------------------------------
#ifndef ConfigurationH
#define ConfigurationH
//---------------------------------------------------------------------------
#include <Controls.hpp>
//---------------------------------------------------------------------------
namespace Registry
{
    class TRegistry;
}
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
    int __fastcall ReadRegistry(TRegistry *Registry, String Name, int Default);
    bool __fastcall ReadRegistry(TRegistry *Registry, String Name, bool Default);
    double __fastcall ReadRegistry(TRegistry *Registry, String Name, double Default);
    String __fastcall ReadRegistry(TRegistry *Registry, String Name, String Default);
public:
    TConfiguration();
    ~TConfiguration();
    void __fastcall Load();
    void __fastcall Save();

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
    unsigned char Position;
    bool FlipH;
    bool FlipV;
};
//---------------------------------------------------------------------------
#endif
