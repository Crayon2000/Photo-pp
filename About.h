//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
    TPanel *Panel1;
    TImage *ProgramIcon;
    TLabel *ProductName;
    TLabel *Version;
    TLabel *Copyright;
    TLabel *Comments;
    TButton *OKButton;
    TLabel *Label1;
    void __fastcall CommentsClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:
public:
    virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
