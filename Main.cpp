//---------------------------------------------------------------------------
#include <vcl.h>
#include <Vcl.FileCtrl.hpp>
#include <System.StrUtils.hpp>
#include <System.Win.Registry.hpp>
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
     FDblClick(false),
     FImageIndex(0)
{
    LoadResImage(iRightBottomCorner->Picture->Bitmap, "RIGHTBOTTOMCORNER");
    LoadResImage(iLeftBottomCorner->Picture->Bitmap, "LEFTBOTTOMCORNER");
    LoadResImage(iLeftTopCorner->Picture->Bitmap, "LEFTTOPCORNER");
    LoadResImage(iRightTopCorner->Picture->Bitmap, "RIGHTTOPCORNER");
    LoadResImage(iBottom->Picture->Bitmap, "BOTTOM");
    iBottom->AutoSize = false;
    LoadResImage(iTop->Picture->Bitmap, "TOP");
    iTop->AutoSize = false;
    LoadResImage(iLeft->Picture->Bitmap, "LEFT");
    iLeft->AutoSize = false;
    LoadResImage(iRight->Picture->Bitmap, "RIGHT");
    iRight->AutoSize = false;

    FImage = new Graphics::TPicture();
    TResourceStream *Res = new TResourceStream((NativeUInt)HInstance, "DEFAULTIMAGE", (System::WideChar *)RT_RCDATA);
    TJPEGImage *JpegImage = new TJPEGImage;
    JpegImage->LoadFromStream(Res);
    FImage->Assign(JpegImage);
    delete JpegImage;
    delete Res;

    FTempBMP = new Graphics::TBitmap();
    FConfig = new TConfiguration();

    FExtList = new TStringList();
    FExtList->Delimiter = L',';
    // The extension list comes from TFileFormatsList.Create in Graphics.pas
    // Some extensions are prohibited: wmf, emf, ico
    FExtList->DelimitedText = "tiff, tif, png, gif, jpeg, jpg, bmp";

    FFilesInDir = new TStringList();

#ifdef DISABLESLIDESHOW
    mnuChoisirDossier->Visible = false;
#endif
}
//---------------------------------------------------------------------------

__fastcall TfrmMain::~TfrmMain()
{
    delete FTempBMP;
    delete FImage;
    delete FConfig;
    delete FExtList;
    delete FFilesInDir;
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

    // Reading from registry
    TRegistry *LRegistry = new TRegistry();
    try
    {
        LRegistry->RootKey = HKEY_CURRENT_USER;
        LRegistry->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
        FConfig->Startup = LRegistry->ValueExists(Application->Title);
    }
    catch (...)
    {   // Default value
    }
    delete LRegistry;

    if(FConfig->AlwayOnTop == true)
    {
        FormStyle = TFormStyle::fsStayOnTop;
    }
    else
    {
        FormStyle = TFormStyle::fsNormal;
    }
    mnuPremierPlan->Checked = FConfig->AlwayOnTop;

    // Make sure that the image is not outside the screen
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

    LoadPath(FConfig->FileName);
    DragAcceptFiles(Handle, true);

    ScanComponent(this);

    ApplySettings();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Border(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    if(Button == TMouseButton::mbLeft)
    {
        TImage *Myimage = static_cast<TImage*>(Sender);
        ReleaseCapture();

        switch(Myimage->Tag)
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

    // Draw image in temporary Bitmap
    if(FConfig->Position == 0)
    {
        FTempBMP->Canvas->StretchDraw(Types::TRect(0, 0, FTempBMP->Width, FTempBMP->Height),
            FImage->Graphic);
    }
    else if(FConfig->Position == 1 && FImage->Width && FImage->Height)
    {
        Types::TRect ImgRect;
        const float RatioX = (float)FTempBMP->Width / (float)FImage->Width;
        const float RatioY = (float)FTempBMP->Height / (float)FImage->Height;
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

    if(FConfig->FlipH == true)
    {
        FTempBMP->Canvas->CopyRect(
            Rect(FTempBMP->Width-1, 0, -1, FTempBMP->Height),
            FTempBMP->Canvas,
            Rect(0, 0, FTempBMP->Width, FTempBMP->Height));
    }
    if(FConfig->FlipV == true)
    {
        FTempBMP->Canvas->CopyRect(
            Rect(0, FTempBMP->Height-1, FTempBMP->Width, -1),
            FTempBMP->Canvas,
            Rect(0, 0, FTempBMP->Width, FTempBMP->Height));
    }

    if(FConfig->ShowTime == true)
    {
        TPoint position = Point(1, 0);
        String strTime = FormatDateTime(ReplaceStr(ReplaceStr(
                        FConfig->TimeFormat, "mm", "nn"), "tt", "am/pm"), Now());
        // Write text in temporary Bitmap
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

    // Assign temporary Bitmap to application
    Canvas->Draw(iLeftTopCorner->Width, iLeftTopCorner->Height, FTempBMP);

//SetZOrder(true);
//HWND LTopHwnd = GetTopWindow(Application->MainForm->Handle);
//if(LTopHwnd==Application->MainForm->Handle)
//    Beep();

    // In case Show Desktop is called
    if(FConfig->AlwayOnTop == true)
    {
        this->FormStyle = TFormStyle::fsStayOnTop;
        //SetWindowPos(this->Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        this->FormStyle = TFormStyle::fsNormal;
        //SetWindowPos(this->Handle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button == TMouseButton::mbLeft)
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
    if(FMouseDown == true && FDblClick == false)
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
    if(Button == TMouseButton::mbLeft)
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
    AboutBox->ShowModal(); // Show About window
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadPath(const String Path)
{
    const int Attributes = FileGetAttr(Path);
    if(Attributes & Sysutils::faDirectory)
    {
#ifndef DISABLESLIDESHOW
        LoadDirectory(Path);
#endif
    }
    else
    {
        LoadImage(Path);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadImage(String ImgToLoad)
{
    FImageIndex = 0;
    FFilesInDir->Clear();
    if(IsValidExtension(ImgToLoad) == false)
    {
        return;
    }
    FFilesInDir->Add(ImgToLoad);

    FConfig->FileName = ImgToLoad;
    ChangeImage();
    TimerSlideShow->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadDirectory(String DirToLoad)
{
    DirToLoad = IncludeTrailingPathDelimiter(DirToLoad);
    TSearchRec SearchRec;
    if(FindFirst(DirToLoad + "*.*", 0, SearchRec) == 0)
    {
        FImageIndex = 0;
        FFilesInDir->Clear();
        do
        {
            if(IsValidExtension(SearchRec.Name) == true)
            {
                FFilesInDir->Add(DirToLoad + SearchRec.Name);
            }
        } while(FindNext(SearchRec) == 0);
        FindClose(SearchRec);

        FConfig->FileName = DirToLoad;
        ChangeImage();
        TimerSlideShow->Enabled = true;
    }
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMain::ChangeImage()
{
    if(FFilesInDir->Count <= 0)
    {
        return false;
    }
    if(FImageIndex >= FFilesInDir->Count)
    {
        FImageIndex = 0;
    }

    String Image = FFilesInDir->Strings[FImageIndex];
    try
    {
        FImage->LoadFromFile(Image);
    }
    catch (...)
    {
        FFilesInDir->Delete(FImageIndex);
        ChangeImage();
    }
    ++FImageIndex;

    return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuChoisirDossierClick(TObject *Sender)
{
    String Caption = LoadLocalizedString(4011);
    String Directory = ExtractFilePath(FConfig->FileName);
    if(Win32MajorVersion() >= 6)
    {
        TFileOpenDialog *FileOpenDialog = new TFileOpenDialog(this);
        FileOpenDialog->Title = Caption;
        FileOpenDialog->DefaultFolder = Directory;
        FileOpenDialog->Options << TFileDialogOption::fdoPickFolders;
        if(FileOpenDialog->Execute() == true)
        {
            LoadDirectory(FileOpenDialog->FileName);
        }
        delete FileOpenDialog;
    }
    else
    {
        Caption += ":";
        const System::WideString Root = "";
        TSelectDirExtOpts Options = TSelectDirExtOpts() << TSelectDirExtOpt::sdNewUI;
        if(SelectDirectory(Caption, Root, Directory, Options) == true)
        {
            LoadDirectory(Directory);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuChoisirClick(TObject *Sender)
{
    TOpenPictureDialog *Dialog = new TOpenPictureDialog(this);
    if(!((Win32MajorVersion() >= 6) && UseLatestCommonDialogs))
    {
        Dialog->OnShow = DialogShow;
    }
    Dialog->OnFolderChange = DialogFolderChange;
    Dialog->Name = "Dialog";
    Dialog->Options << TOpenOption::ofFileMustExist;
    Dialog->Title = LoadLocalizedString(4008);
    Dialog->Filter = LoadLocalizedString(IDS_ALLIMGFILES) +
            " (*.jpg;*.jpeg;*.bmp;*.png;*.gif;*.tif;*.tiff)|"
            "*.jpg;*.jpeg;*.bmp;*.png;*.gif;*.tif;*.tiff|"
            "JPEG Image File (*.jpg;*.jpeg)|*.jpg;*.jpeg|"
            "Bitmaps (*.bmp)|*.bmp|"
            "Portable Network Graphics (*.png)|*.png|"
            "Image CompuServe GIF (*.gif)|*.gif|"
            "Tagged Image File Format (*.tif;*.tiff)|*.tif;*.tiff";

    if(Dialog->Execute() == true)
    {
        // Load image
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

    if(FConfig->AlwayOnTop == true)
    {
        FormStyle = TFormStyle::fsStayOnTop;
    }
    else
    {
        FormStyle = TFormStyle::fsNormal;
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
    // Only works with BMP
    if(FileExists(FConfig->FileName) == true)
    {
        SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, FConfig->FileName.c_str(), NULL);
    }
    else
    {
        MessageBeep(0);
        const String LError = LoadLocalizedString(IDS_FILENOTFOUND);
        MessageDlg(LError, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DropFiles(TMessage &Message)
{
    wchar_t Buffer[MAX_PATH];

    const int FileCount = DragQueryFileW((HDROP)Message.WParam, 0xFFFFFFFF, NULL, 0);
    for(int i = 0; i < FileCount; ++i)
    {
        DragQueryFileW((HDROP)Message.WParam, i, Buffer, MAX_PATH);
        LoadPath(Buffer);
        break;
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
    FormOptions->cboInterval->ItemIndex =
        FormOptions->cboInterval->Items->IndexOfObject((TObject *)FConfig->Interval);
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
        default:
            break;
    }
    FormOptions->chkFlipH->Checked = FConfig->FlipH;
    FormOptions->chkFlipV->Checked = FConfig->FlipV;

    if(FormOptions->ShowModal() == mrOk) // Show Options
    {
        FConfig->ShowTime = FormOptions->chkShowTime->Checked;
        FConfig->TimeColor = FormOptions->ColorBox->Selected;
        FConfig->TimeSize =  FormOptions->cboSize->Text.ToInt();
        FConfig->TimeFont = FormOptions->cboFont->Text;
        FConfig->TimeFormat = FormOptions->cboFormat->Text;
        FConfig->Interval = (int)FormOptions->cboInterval->Items->Objects[FormOptions->cboInterval->ItemIndex];
        FConfig->Alpha = FormOptions->tbarAlpha->Position;
        FConfig->BkGroundColor = FormOptions->ColorBoxBk->Selected;
        if(FormOptions->optStretch->Checked == true)
        {
            FConfig->Position = 0;
        }
        else if(FormOptions->optKeepAR->Checked == true)
        {
            FConfig->Position = 1;
        }
        else if(FormOptions->optTiled->Checked == true)
        {
            FConfig->Position = 2;
        }
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
    if(Key == VK_RETURN && Shift.Contains(ssAlt) == true)
    {
        FullScreen();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FullScreen()
{
    Forms::TMonitor *SelectedMonitor = NULL;
    int PixelCount = 0;
    Types::TRect ResultRect;

    for(int i = 0; i < Screen->MonitorCount; ++i)
    {
        if(IntersectRect(ResultRect, Screen->Monitors[i]->BoundsRect, BoundsRect) == true)
        {
            const int TempCount = ResultRect.Width() * ResultRect.Height();
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
    // Set Borders
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
    TOpenDialog* LOpenDialog = dynamic_cast<TOpenDialog*>(Sender);
    if(LOpenDialog == NULL)
    {
        return;
    }
    HWND LParentHWnd = GetParent(LOpenDialog->Handle);

    HWND LItemHWnd = GetDlgItem(LParentHWnd, IDOK);
    SetWindowTextW(LItemHWnd, LoadLocalizedString(1002).c_str());
    LItemHWnd = GetDlgItem(LParentHWnd, IDCANCEL);
    SetWindowTextW(LItemHWnd, LoadLocalizedString(1001).c_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DialogFolderChange(TObject *Sender)
{
    TOpenDialog* LOpenDialog = dynamic_cast<TOpenDialog*>(Sender);
    if(LOpenDialog == NULL)
    {
        return;
    }
    HWND LParentHWnd = GetParent(LOpenDialog->Handle);
    HWND LItemHWnd = FindWindowExW(LParentHWnd, NULL, L"SHELLDLL_DefView", NULL);
    SendMessage(LItemHWnd, WM_COMMAND, 0x702D, 0); // Thumbs View
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ChangeLanguage(TObject *Sender)
{
    TMenuItem *MenuItem = static_cast<TMenuItem*>(Sender);
    MenuItem->Checked = true;

    if(mnuFrench->Checked == true)
    {
        FConfig->Language = LANG_FRENCH;
    }
    else if(mnuEnglish->Checked == true)
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
    // Put the color names in the correct language
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
    // Same for background color
    FormOptions->ColorBoxBk->Items = FormOptions->ColorBox->Items;

    String StrInterval;
    String FormatSec = LoadLocalizedString(5014);
    String FormatMin = LoadLocalizedString(5015);
    FormOptions->cboInterval->Items->Strings[0] = StrInterval.sprintf(FormatSec.c_str(), 5);
    FormOptions->cboInterval->Items->Strings[1] = StrInterval.sprintf(FormatSec.c_str(), 10);
    FormOptions->cboInterval->Items->Strings[2] = StrInterval.sprintf(FormatSec.c_str(), 15);
    FormOptions->cboInterval->Items->Strings[3] = StrInterval.sprintf(FormatSec.c_str(), 30);
    FormOptions->cboInterval->Items->Strings[4] = StrInterval.sprintf(FormatMin.c_str(), 1);
    FormOptions->cboInterval->Items->Strings[5] = StrInterval.sprintf(FormatMin.c_str(), 2);
    FormOptions->cboInterval->Items->Strings[6] = StrInterval.sprintf(FormatMin.c_str(), 5);

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
    TimerSlideShow->Interval = FConfig->Interval;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMain::SetAtStarup()
{
    bool Result = true;

    TRegistry *LRegistry = new TRegistry();
    LRegistry->RootKey = HKEY_CURRENT_USER;
    if(LRegistry->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
    {
        if(FConfig->Startup == true)
        {
            try
            {
                LRegistry->WriteString(Application->Title, Application->ExeName);
            }
            catch(...)
            {   // Writing to the registry failed
                FConfig->Startup = false;
                Result = false;
            }
        }
        else
        {
            try
            {
                LRegistry->DeleteValue(Application->Title);
            }
            catch(...)
            {   // Writing to the registry failed
                FConfig->Startup = true;
                Result = false;
            }
        }
    }
    LRegistry->CloseKey();
    delete LRegistry;

    return Result;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EndSession(TMessage &Message)
{
    if(Message.WParam == true)
    {   // Session is being ended
        Close();
    }
    // If an application processes this message, it should return zero
    Message.Result = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadResImage(Graphics::TBitmap *ABitmapImage, const String AIdentifier)
{
    if(ABitmapImage == NULL)
    {
        throw EArgumentException(Sysutils::Format(System_Rtlconsts_SParamIsNil, ARRAYOFCONST(("ABitmapImage"))));
    }

    Pngimage::TPngImage *PngImage = new Pngimage::TPngImage();
    PngImage->LoadFromResourceName((NativeUInt)HInstance, AIdentifier);
    ABitmapImage->Assign(PngImage);
    delete PngImage;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMain::IsValidExtension(const String FileName)
{
    String Ext = ExtractFileExt(FileName);
    Ext.Delete(1, 1); // Remove period character
    return (FExtList->IndexOf(Ext) >= 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TimerSlideShowTimer(TObject *Sender)
{
    ChangeImage();
}
//---------------------------------------------------------------------------

