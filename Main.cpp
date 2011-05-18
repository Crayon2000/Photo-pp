//---------------------------------------------------------------------------
#include <vcl.h>
#include <StrUtils.hpp>
#include <Registry.hpp>
#pragma hdrstop

#include "About.h"
#include "Options.h"
#include "Main.h"
#include "Translation.h"
#include "ResourceString.h"
#include "Configuration.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
   : TForm(Owner),
     FMouseDown(false),
     FDblClick(false)
{
    LoadResImage(iRightBottomCorner->Picture, "RIGHTBOTTOMCORNER");
    LoadResImage(iLeftBottomCorner->Picture, "LEFTBOTTOMCORNER");
    LoadResImage(iLeftTopCorner->Picture, "LEFTTOPCORNER");
    LoadResImage(iRightTopCorner->Picture, "RIGHTTOPCORNER");
    LoadResImage(iBottom->Picture, "BOTTOM");
    iBottom->AutoSize = false;
    LoadResImage(iTop->Picture, "TOP");
    iTop->AutoSize = false;
    LoadResImage(iLeft->Picture, "LEFT");
    iLeft->AutoSize = false;
    LoadResImage(iRight->Picture, "RIGHT");
    iRight->AutoSize = false;

    FImage = new Graphics::TPicture();
    TResourceStream *Res = new TResourceStream((unsigned)HInstance, "DEFAULTIMAGE", (System::WideChar *)RT_RCDATA);
    TJPEGImage *JpegImage = new TJPEGImage;
    JpegImage->LoadFromStream(Res);
    FImage->Assign(JpegImage);
    delete JpegImage;
    delete Res;

    FTempBMP = new Graphics::TBitmap();
    FConfig = new TConfiguration();
}
//---------------------------------------------------------------------------

__fastcall TfrmMain::~TfrmMain()
{
    delete FTempBMP;
    delete FImage;
    delete FConfig;
    TResourceString::Destroy();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuQuitterClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    // Set default screen size
    FConfig->Screen.Width = FImage->Width;
    FConfig->Screen.Height = FImage->Height;
    FConfig->Screen.Left = Screen->Width/2 - FImage->Width/2;
    FConfig->Screen.Top = Screen->Height/2 - FImage->Height/2;

    // Load configuration
    FConfig->Load();
    SetLanguage(FConfig->Language);
    SetBounds(FConfig->Screen.Left, FConfig->Screen.Top,
        FConfig->Screen.Width, FConfig->Screen.Height);

    //Lecture dans le registre
    TRegistry *reg = new TRegistry();
    try
    {
        reg->RootKey = HKEY_CURRENT_USER;
        reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
        FConfig->Startup = reg->ValueExists(Application->Title);
    }
    catch (...)
    {   // Valeur par défaut
    }
    delete reg;

    if (FConfig->AlwayOnTop)
    {
        FormStyle = fsStayOnTop;
    }
    else
    {
        FormStyle = fsNormal;
    }
    mnuPremierPlan->Checked = FConfig->AlwayOnTop;

    // On s'assure que l'image n'est pas en dehors de l'écran
    if(this->Left > Screen->Width)
    {
        this->Left = Screen->Width / 2 - this->Width / 2;
    }
    if(this->Top > Screen->Height)
    {
        this->Top = Screen->Height / 2 - this->Height / 2;
    }

    mnuFrench->RadioItem = true;
    mnuEnglish->RadioItem = true;
    switch(FConfig->Language)
    {
        case LANG_ENGLISH:
            mnuEnglish->Checked = true;
            break;
        default:
            mnuFrench->Checked = true;
    }

    LoadImage(FConfig->FileName);
    DragAcceptFiles(Handle, true);

    ScanComponent(this);

    ApplySettings();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Border(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    if(Button == mbLeft)
    {
        TImage *myimage = (TImage*) Sender;
        ReleaseCapture();

        switch(myimage->Tag)
        {
        case 1:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, 0);
            break;
        case 2:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTBOTTOMLEFT, 0);
            break;
        case 3:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTTOPLEFT, 0);
            break;
        case 4:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTTOPRIGHT, 0);
            break;
        case 5:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTBOTTOM, 0);
            break;
        case 6:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTTOP, 0);
            break;
        case 7:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTLEFT, 0);
            break;
        case 8:
            SendMessage(Handle, WM_NCLBUTTONDOWN, HTRIGHT, 0);
            break;
        default:
            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TimerTimer(TObject *Sender)
{
    FTempBMP->SetSize(Width - iRightTopCorner->Width - iLeftTopCorner->Width,
        Height - iRightTopCorner->Height - iLeftTopCorner->Height);

    FTempBMP->Canvas->Brush->Style = bsSolid;
    FTempBMP->Canvas->Brush->Color = FConfig->BkGroundColor;
    FTempBMP->Canvas->FillRect(Rect(0, 0, ClientWidth, ClientHeight));
    //tempBMP->Canvas->CopyMode = cmPatCopy;

    // Dessine l'image dans le Bitmap temporaire
    if(FConfig->Position == 0)
    {
        FTempBMP->Canvas->StretchDraw(Types::TRect(0, 0, FTempBMP->Width, FTempBMP->Height),
            FImage->Graphic);
    }
    else if(FConfig->Position == 1 && FImage->Width && FImage->Height)
    {
        Types::TRect ImgRect;
        float RatioX = (float)FTempBMP->Width / (float)FImage->Width;
        float RatioY = (float)FTempBMP->Height / (float)FImage->Height;
        if(RatioX > RatioY)
        {
            float NewWidth = FImage->Width * RatioY;
            ImgRect.Left = FTempBMP->Width/2.0 - NewWidth/2.0;
            ImgRect.Top = 0;
            ImgRect.Right = ImgRect.Left + NewWidth;
            ImgRect.Bottom = FTempBMP->Height;
        }
        else
        {
            float NewHeight = FImage->Height * RatioX;
            ImgRect.Left = 0;
            ImgRect.Top = FTempBMP->Height/2.0 - NewHeight/2.0;
            ImgRect.Right = FTempBMP->Width;
            ImgRect.Bottom = ImgRect.Top + NewHeight;
        }
        FTempBMP->Canvas->StretchDraw(ImgRect, FImage->Graphic);
    }
    else if(FConfig->Position == 2)
    {
        Graphics::TBitmap* bm = new Graphics::TBitmap();
        bm->Canvas->Brush->Style = bsSolid;
        bm->Canvas->Brush->Color = FConfig->BkGroundColor;
        bm->SetSize(FImage->Width, FImage->Height);
        bm->Canvas->Draw(0, 0, FImage->Graphic);
        FTempBMP->Canvas->Brush->Bitmap = bm;
        FTempBMP->Canvas->FillRect(Rect(0, 0, ClientWidth, ClientHeight));
        delete bm;
    }

    if(FConfig->FlipH)
    {
        FTempBMP->Canvas->CopyRect(
            Rect(FTempBMP->Width-1, 0, -1, FTempBMP->Height),
            FTempBMP->Canvas,
            Rect(0, 0, FTempBMP->Width, FTempBMP->Height));
    }
    if(FConfig->FlipV)
    {
        FTempBMP->Canvas->CopyRect(
            Rect(0, FTempBMP->Height-1, FTempBMP->Width, -1),
            FTempBMP->Canvas,
            Rect(0, 0, FTempBMP->Width, FTempBMP->Height));
    }

    if(FConfig->ShowTime)
    {
        TPoint position = Point(1, 0);
        String strTime = FormatDateTime(ReplaceStr(ReplaceStr(
                        FConfig->TimeFormat, "mm", "nn"), "tt", "am/pm"), Now());
        // Écris le texte dans le Bitmap temporaire
        SetBkMode(FTempBMP->Canvas->Handle, TRANSPARENT);
        FTempBMP->Canvas->Font->Name = FConfig->TimeFont;
        FTempBMP->Canvas->Font->Size = FConfig->TimeSize;
//        tempBMP->Canvas->Font->Style = TFontStyles()<< fsBold;
        SetTextAlign(FTempBMP->Canvas->Handle, TA_LEFT);
        FTempBMP->Canvas->Font->Color = (TColor)(0xFFFFFF - FConfig->TimeColor);
        FTempBMP->Canvas->TextOut(position.x + 1, position.y + 1, strTime);
        FTempBMP->Canvas->Font->Color = FConfig->TimeColor;
        FTempBMP->Canvas->TextOut(position.x, position.y, strTime);
    }

    // Assigne le Bitmap temporaire à l'application
    Canvas->Draw(iLeftTopCorner->Width, iLeftTopCorner->Height, FTempBMP);

//SetZOrder(true);
//HWND tTopHwnd = GetTopWindow(Application->MainForm->Handle);
//if(tTopHwnd==Application->MainForm->Handle)
//    Beep();

    // Au cas ou Show Desktop est appellé
    if(FConfig->AlwayOnTop)
    {
        this->FormStyle = fsStayOnTop;
        //SetWindowPos(this->Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        this->FormStyle = fsNormal;
        //SetWindowPos(this->Handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft)
    {
        Screen->Cursor = crSizeAll;
        FMouseDown = true;
        FOldX = X;
        FOldY = Y;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    if(FMouseDown && !FDblClick)
    {
        this->Left += (X - FOldX);
        this->Top += (Y - FOldY);
    }

    FDblClick = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft)
    {
        FMouseDown = false;
        Screen->Cursor = crDefault;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuGradeurOriginalClick(TObject *Sender)
{
    Width = FImage->Width + iRightTopCorner->Width + iLeftTopCorner->Width;
    Height = FImage->Height + iRightTopCorner->Height + iLeftTopCorner->Height;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAProposClick(TObject *Sender)
{
    AboutBox->ShowModal();  //Affiche le About
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadImage(String imgToLoad)
{
    // Certaine extension son prohibée
    String Ext = ExtractFileExt(imgToLoad).LowerCase();
    if(Ext == ".ico" || Ext == ".emf" || Ext == ".wmf")
    {
        return;
    }

    try
    {
        FImage->LoadFromFile(imgToLoad);
        FConfig->FileName = imgToLoad;
    }
    catch (...)
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuChoisirClick(TObject *Sender)
{
    TOpenPictureDialog *Dialog = new TOpenPictureDialog(this);
    if(!((Win32MajorVersion >= 6) && UseLatestCommonDialogs))
    {
        Dialog->OnShow = DialogShow;
    }
    Dialog->OnFolderChange = DialogFolderChange;
    Dialog->Name = "Dialog";
    Dialog->Options << ofFileMustExist;
    Dialog->Title = LoadLocalizedString(4008);
    Dialog->Filter = LoadLocalizedString(IDS_ALLIMGFILES) +
            " (*.jpg;*.jpeg;*.bmp;*.png;*.gif;*.tif;*.tiff)|"
            "*.jpg;*.jpeg;*.bmp;*.png;*.gif;*.tif;*.tiff|"
            "JPEG Image File (*.jpg;*.jpeg)|*.jpg;*.jpeg|"
            "Bitmaps (*.bmp)|*.bmp|"
            "Portable Network Graphics (*.png)|*.png|"
            "Image CompuServe GIF (*.gif)|*.gif|"
            "Tagged Image File Format (*.tif;*.tiff)|*.tif;*.tiff";

    if(Dialog->Execute())
    {
        // Load l'image
        LoadImage(Dialog->FileName);
    }
    delete Dialog;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(this->GetClientRect() != Types::TRect(0, 0, Screen->Width, Screen->Height))
    {
        FConfig->Screen.Width = Width;
        FConfig->Screen.Height = Height;
        FConfig->Screen.Left = Left;
        FConfig->Screen.Top = Top;
    }
    else
    {
        FConfig->Screen.Width = FBefFullScreen.Right;
        FConfig->Screen.Height = FBefFullScreen.Bottom;
        FConfig->Screen.Left = FBefFullScreen.Left;
        FConfig->Screen.Top = FBefFullScreen.Top;
    }

    FConfig->Save();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPremierPlanClick(TObject *Sender)
{
    mnuPremierPlan->Checked = !mnuPremierPlan->Checked;
    FConfig->AlwayOnTop = mnuPremierPlan->Checked;

    if(FConfig->AlwayOnTop)
    {
        FormStyle = fsStayOnTop;
    }
    else
    {
        FormStyle = fsNormal;
    }
    
    DragAcceptFiles(Handle, true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
    ShowWindow(Application->Handle, SW_HIDE);
    LoadLanguage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuWallpaperClick(TObject *Sender)
{
    // Fonctionne avec les BMP seulement
    if(FileExists(FConfig->FileName))
    {
        SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, FConfig->FileName.c_str(), NULL );
    }
    else
    {
         MessageBeep(0);
         String strError = LoadLocalizedString(IDS_FILENOTFOUND);
         MessageDlg(strError, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DropFiles(TMessage &Message)
{
    wchar_t buffer[MAX_PATH];

    int nFiles = DragQueryFileW((HDROP)Message.WParam, 0xFFFFFFFF, NULL, 0);
    for(int i = 0; i < nFiles; ++i)
    {
        DragQueryFileW((HDROP)Message.WParam, i, buffer, MAX_PATH);
        LoadImage(buffer);
    }
    DragFinish((HDROP)Message.WParam);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuShowOptionsClick(TObject *Sender)
{
    FormOptions->chkShowTime->Checked = FConfig->ShowTime;
    FormOptions->ColorBox->Selected = FConfig->TimeColor;
    FormOptions->cboSize->ItemIndex =
                    FormOptions->cboSize->Items->IndexOf(IntToStr(FConfig->TimeSize));
    FormOptions->cboFont->ItemIndex =
                    FormOptions->cboFont->Items->IndexOf(FConfig->TimeFont);
    FormOptions->cboFormat->ItemIndex =
                    FormOptions->cboFormat->Items->IndexOf(FConfig->TimeFormat);
    FormOptions->tbarAlpha->Position = FConfig->Alpha;
    FormOptions->ColorBoxBk->Selected = FConfig->BkGroundColor;
    FormOptions->chkStartup->Checked = FConfig->Startup;
    switch(FConfig->Position)
    {
        case 0:
            FormOptions->optStretch->Checked = true;
            break;
        case 1:
            FormOptions->optKeepAR->Checked = true;
            break;
        case 2:
            FormOptions->optTiled->Checked = true;
            break;
    }
    FormOptions->chkFlipH->Checked = FConfig->FlipH;
    FormOptions->chkFlipV->Checked = FConfig->FlipV;

    if(FormOptions->ShowModal() == mrOk)  // Affiche les Options
    {
        FConfig->ShowTime = FormOptions->chkShowTime->Checked;
        FConfig->TimeColor = FormOptions->ColorBox->Selected;
        FConfig->TimeSize =  FormOptions->cboSize->Text.ToInt();
        FConfig->TimeFont = FormOptions->cboFont->Text;
        FConfig->TimeFormat = FormOptions->cboFormat->Text;
        FConfig->Alpha = FormOptions->tbarAlpha->Position;
        FConfig->BkGroundColor = FormOptions->ColorBoxBk->Selected;
        if(FormOptions->optStretch->Checked)
            FConfig->Position = 0;
        else if(FormOptions->optKeepAR->Checked)
            FConfig->Position = 1;
        else if(FormOptions->optTiled->Checked)
            FConfig->Position = 2;
        FConfig->FlipH = FormOptions->chkFlipH->Checked;
        FConfig->FlipV = FormOptions->chkFlipV->Checked;

        ApplySettings();

        if(FConfig->Startup != FormOptions->chkStartup->Checked)
        {
            FConfig->Startup = FormOptions->chkStartup->Checked;
            SetAtStarup();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==VK_RETURN && Shift.Contains(ssAlt))
    {
        FullScreen();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FullScreen()
{
    Forms::TMonitor *SelectedMonitor;
    int PixelCount = 0;
    TRect ResultRect;

    for(int i = 0; i < Screen->MonitorCount; ++i)
    {
        if(IntersectRect(ResultRect, Screen->Monitors[i]->BoundsRect, BoundsRect))
        {
            int TempCount = ResultRect.Width() * ResultRect.Height();
            if(TempCount > PixelCount)
            {
                PixelCount = TempCount;
                SelectedMonitor = Screen->Monitors[i];
            }
        }
    }

    if(SelectedMonitor->BoundsRect != BoundsRect)
    {   // Store old value and put in full screen
        FBefFullScreen = Types::TRect(Left, Top, Width, Height);
        SetBounds(SelectedMonitor->Left, SelectedMonitor->Top,
            SelectedMonitor->Width, SelectedMonitor->Height);
    }
    else
    {   // Set back old value
        SetBounds(FBefFullScreen.Left, FBefFullScreen.Top,
            FBefFullScreen.Right, FBefFullScreen.Bottom);
    }

    FDblClick = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject *Sender)
{
    // Place les Bordures
    iRightBottomCorner->Left = Width - iRightBottomCorner->Width;
    iRightBottomCorner->Top = Height - iRightBottomCorner->Height;
    iLeftBottomCorner->Left = 0;
    iLeftBottomCorner->Top = Height - iLeftBottomCorner->Height;
    iLeftTopCorner->Left = 0;
    iLeftTopCorner->Top = 0;
    iRightTopCorner->Left = Width - iRightTopCorner->Width;
    iRightTopCorner->Top = 0;
    iBottom->Left = iLeftBottomCorner->Width;
    iBottom->Top = Height - iBottom->Height;
    iBottom->Width = Width - iLeftBottomCorner->Width - iRightBottomCorner->Width;
    iTop->Left = iLeftTopCorner->Height;
    iTop->Top = 0;
    iTop->Width = Width - iLeftTopCorner->Width - iRightTopCorner->Width;
    iLeft->Left = 0;
    iLeft->Top = iLeftTopCorner->Height;
    iLeft->Height = Height - iLeftTopCorner->Width - iLeftBottomCorner->Width;
    iRight->Left = Width - iRight->Width;
    iRight->Top = iRightTopCorner->Height;
    iRight->Height = Height - iRightTopCorner->Width - iRightBottomCorner->Width;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DialogShow(TObject *Sender)
{
    HWND tParentHWnd = GetParent(((TOpenDialog*)Sender)->Handle);

    HWND tItemHWnd = GetDlgItem(tParentHWnd, IDOK);
    SetWindowTextW(tItemHWnd, LoadLocalizedString(1002).c_str());
    tItemHWnd = GetDlgItem(tParentHWnd, IDCANCEL);
    SetWindowTextW(tItemHWnd, LoadLocalizedString(1001).c_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DialogFolderChange(TObject *Sender)
{
    HWND tParentHWnd = GetParent(((TOpenDialog*)Sender)->Handle);
    HWND tItemHWnd = FindWindowExW(tParentHWnd, NULL, L"SHELLDLL_DefView", NULL);
    SendMessage(tItemHWnd, WM_COMMAND, 0x702D, 0);   // Thumbs View
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ChangeLanguage(TObject *Sender)
{
    TMenuItem *MenuItem = (TMenuItem*)Sender;
    MenuItem->Checked = true;

    if(mnuFrench->Checked)
    {
        FConfig->Language = LANG_FRENCH;
    }
    else if(mnuEnglish->Checked)
    {
        FConfig->Language = LANG_ENGLISH;
    }

    SetLanguage(FConfig->Language);

    ScanComponent(frmMain);
    ScanComponent(FormOptions);
    ScanComponent(AboutBox);

    LoadLanguage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadLanguage()
{
    // Met les noms de couleur dans la bonne langue
    FormOptions->ColorBox->Items->Strings[0] = LoadLocalizedString(IDS_CUSTOM);
    FormOptions->ColorBox->Items->Strings[1] = LoadLocalizedString(IDS_BLACK);
    FormOptions->ColorBox->Items->Strings[2] = LoadLocalizedString(IDS_MAROON);
    FormOptions->ColorBox->Items->Strings[3] = LoadLocalizedString(IDS_GREEN);
    FormOptions->ColorBox->Items->Strings[4] = LoadLocalizedString(IDS_OLIVE);
    FormOptions->ColorBox->Items->Strings[5] = LoadLocalizedString(IDS_NAVY);
    FormOptions->ColorBox->Items->Strings[6] = LoadLocalizedString(IDS_PURPLE);
    FormOptions->ColorBox->Items->Strings[7] = LoadLocalizedString(IDS_TEAL);
    FormOptions->ColorBox->Items->Strings[8] = LoadLocalizedString(IDS_GRAY);;
    FormOptions->ColorBox->Items->Strings[9] = LoadLocalizedString(IDS_SILVER);
    FormOptions->ColorBox->Items->Strings[10] = LoadLocalizedString(IDS_RED);
    FormOptions->ColorBox->Items->Strings[11] = LoadLocalizedString(IDS_LIME);
    FormOptions->ColorBox->Items->Strings[12] = LoadLocalizedString(IDS_YELLOW);
    FormOptions->ColorBox->Items->Strings[13] = LoadLocalizedString(IDS_BLUE);
    FormOptions->ColorBox->Items->Strings[14] = LoadLocalizedString(IDS_FUCHSIA);
    FormOptions->ColorBox->Items->Strings[15] = LoadLocalizedString(IDS_AQUA);
    FormOptions->ColorBox->Items->Strings[16] = LoadLocalizedString(IDS_WHITE);
    // Pareillement pour la couleur de fond
    FormOptions->ColorBoxBk->Items = FormOptions->ColorBox->Items;

    TResourceString &ResourceString = TResourceString::Instance();
    ResourceString.Set(_SPreviewLabel, LoadLocalizedString(3008));
    ResourceString.Set(_srNone, LoadLocalizedString(IDS_NONE));
    ResourceString.Set(_SPictureLabel, LoadLocalizedString(IDS_PICTURE));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ApplySettings()
{
    this->AlphaBlend = (FConfig->Alpha == 255) ? false : true;
    this->AlphaBlendValue = FConfig->Alpha;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMain::SetAtStarup()
{
    bool bReturn = true;

    TRegistry *reg = new TRegistry();
    reg->RootKey = HKEY_CURRENT_USER;
    if(reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
    {
        if(FConfig->Startup == true)
        {
            try
            {
                reg->WriteString(Application->Title, Application->ExeName);
            }
            catch(...)
            {   // L'écriture dans le registre a échoué
                FConfig->Startup = false;
                bReturn = false;
            }
        }
        else
        {
            try
            {
                reg->DeleteValue(Application->Title);
            }
            catch(...)
            {   // L'écriture dans le registre a échoué
                FConfig->Startup = true;
                bReturn = false;
            }
        }
    }
    reg->CloseKey();
    delete reg;

    return bReturn;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EndSession(TMessage &Message)
{
    if(Message.WParam == true)
    {   // Session is being ended
        Close();
    }
    //If an application processes this message, it should return zero
    Message.Result = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadResImage(Graphics::TPicture *Picture, const String Identifier)
{
    TPngImage *PngImage = new TPngImage;
    PngImage->LoadFromResourceName((unsigned)HInstance, Identifier);
    Picture->Assign(PngImage);
    delete PngImage;
}
//---------------------------------------------------------------------------
