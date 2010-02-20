//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "Options.h"
#include "main.h"
#include "Translation.h"
#include <StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
   : TForm(Owner)
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

    mouseDown = false;
    dblClick = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuQuitterClick(TObject */*Sender*/)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject */*Sender*/)
{
    // Set default screen size
    Config.Screen.Width = Image->Width;
    Config.Screen.Height = Image->Height;
    Config.Screen.Left = Screen->Width/2 - Image->Width/2;
    Config.Screen.Top = Screen->Height/2 - Image->Height/2;

    // Load configuration
    Config.Load();
    gwLanguage = Config.Language;
    Width = Config.Screen.Width;
    Height = Config.Screen.Height;
    Left = Config.Screen.Left;
    Top = Config.Screen.Top;

    //Lecture dans le registre
    TRegistry *reg = new TRegistry();
    try
    {
        reg->RootKey = HKEY_CURRENT_USER;
        reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
        Config.Startup = reg->ValueExists(Application->Title);
    }
    catch (...)
    {   // Valeur par défaut
    }
    delete reg;

    if (Config.AlwayOnTop)
    {
        FormStyle = fsStayOnTop;
    }
    else
    {
        FormStyle = fsNormal;
    }
    mnuPremierPlan->Checked = Config.AlwayOnTop;

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
    switch(Config.Language)
    {
        case LANG_ENGLISH:
            mnuEnglish->Checked = true;
            break;
        default:
            mnuFrench->Checked = true;
    }

    LoadImage(Config.FileName);
    DragAcceptFiles(Handle, true);

    tempBMP = new Graphics::TBitmap();

    ScanComponent(this);

    ApplySettings();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Border(TObject *Sender, TMouseButton Button,
      TShiftState /*Shift*/, int /*X*/, int /*Y*/)
{
    if (Button == mbLeft)
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

void __fastcall TfrmMain::TimerTimer(TObject */*Sender*/)
{
    tempBMP->Width = Width - iRightTopCorner->Width - iLeftTopCorner->Width;
    tempBMP->Height = Height - iRightTopCorner->Height - iLeftTopCorner->Height;

    tempBMP->Canvas->Brush->Style = bsSolid;
    tempBMP->Canvas->Brush->Color = Config.BkGroundColor;
    tempBMP->Canvas->FillRect(Rect(0, 0, ClientWidth, ClientHeight));
    //tempBMP->Canvas->CopyMode = cmPatCopy;

    // Dessine l'image dans le Bitmap temporaire
    tempBMP->Canvas->StretchDraw(Types::TRect(0, 0, tempBMP->Width, tempBMP->Height),
        Image->Picture->Graphic);

    if(Config.ShowTime)
    {
        TPoint position = Point(1, 0);
        String strTime = FormatDateTime(ReplaceStr(ReplaceStr(
                        Config.TimeFormat, "mm", "nn"), "tt", "am/pm"), Now());
        // Écris le texte dans le Bitmap temporaire
        SetBkMode(tempBMP->Canvas->Handle, TRANSPARENT);
        tempBMP->Canvas->Font->Name = Config.TimeFont;
        tempBMP->Canvas->Font->Size = Config.TimeSize;
//        tempBMP->Canvas->Font->Style = TFontStyles()<< fsBold;
        SetTextAlign (tempBMP->Canvas->Handle, TA_LEFT);
        tempBMP->Canvas->Font->Color = (TColor)(0xFFFFFF - Config.TimeColor);
        tempBMP->Canvas->TextOut(position.x + 1, position.y + 1, strTime);
        tempBMP->Canvas->Font->Color = Config.TimeColor;
        tempBMP->Canvas->TextOut(position.x, position.y, strTime);
    }

    // Assigne le Bitmap temporaire à l'application
    Canvas->Draw(iLeftTopCorner->Width, iLeftTopCorner->Height, tempBMP);

//SetZOrder(true);
//HWND tTopHwnd = GetTopWindow(Application->MainForm->Handle);
//if(tTopHwnd==Application->MainForm->Handle)
//    Beep();

    // Au cas ou Show Desktop est appellé
    if(Config.AlwayOnTop)
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

void __fastcall TfrmMain::FormMouseDown(TObject */*Sender*/,
      TMouseButton Button, TShiftState /*Shift*/, int X, int Y)
{
    if(Button==mbLeft)
    {
        Screen->Cursor = crSizeAll;
        mouseDown = true;
        oldX = X;
        oldY = Y;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseMove(TObject */*Sender*/, TShiftState /*Shift*/,
      int X, int Y)
{
    if(mouseDown && !dblClick)
    {
        this->Left += (X - oldX);
        this->Top += (Y - oldY);
    }

    dblClick = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseUp(TObject */*Sender*/, TMouseButton Button,
      TShiftState /*Shift*/, int /*X*/, int /*Y*/)
{
    if(Button==mbLeft)
    {
        mouseDown = false;
        Screen->Cursor = crDefault;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuGradeurOriginalClick(TObject */*Sender*/)
{
    Width = Image->Width;
    Height = Image->Height;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAProposClick(TObject */*Sender*/)
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
        Image->Picture->LoadFromFile(imgToLoad);
        Config.FileName = imgToLoad;
    }
    catch (...)
    {

    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuChoisirClick(TObject */*Sender*/)
{
    TOpenPictureDialog *Dialog = new TOpenPictureDialog(this);
    Dialog->OnShow = DialogShow;
    Dialog->OnFolderChange = DialogFolderChange;
    Dialog->OnSelectionChange = DialogSelectionChange;
    Dialog->Name = "Dialog";
    Dialog->Options << ofFileMustExist;
    Dialog->Title = LoadLocalizedString(HInstance, 4008);
    Dialog->Filter = LoadLocalizedString(HInstance, IDS_ALLIMGFILES) +
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

void __fastcall TfrmMain::FormClose(TObject */*Sender*/, TCloseAction &/*Action*/)
{
    if(this->GetClientRect() != Types::TRect(0, 0, Screen->Width, Screen->Height))
    {
        Config.Screen.Width = Width;
        Config.Screen.Height = Height;
        Config.Screen.Left = Left;
        Config.Screen.Top = Top;
    }
    else
    {
        Config.Screen.Width = befFullScr.Right;
        Config.Screen.Height = befFullScr.Bottom;
        Config.Screen.Left = befFullScr.Left;
        Config.Screen.Top = befFullScr.Top;
    }

    Config.Save();

    delete tempBMP;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPremierPlanClick(TObject */*Sender*/)
{
    mnuPremierPlan->Checked = !mnuPremierPlan->Checked;
    Config.AlwayOnTop = mnuPremierPlan->Checked;

    if(Config.AlwayOnTop)
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

void __fastcall TfrmMain::FormShow(TObject */*Sender*/)
{
    ShowWindow(Application->Handle, SW_HIDE);
    LoadLanguage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuWallpaperClick(TObject */*Sender*/)
{
    // Fonctionne avec les BMP seulement
    if(FileExists(Config.FileName))
    {
        SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, Config.FileName.c_str(), NULL );
    }
    else
    {
         MessageBeep(0);
         String strError = LoadLocalizedString(HInstance, IDS_FILENOTFOUND);
         MessageDlg(strError, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DropFiles(TMessage &Message)
{
    int nFiles;
    wchar_t buffer[MAX_PATH];

    nFiles = DragQueryFileW((HDROP)Message.WParam, 0xFFFFFFFF, NULL, 0);
    for(int i = 0; i < nFiles; i++)
    {
        DragQueryFileW((HDROP)Message.WParam, i, buffer, MAX_PATH);
        LoadImage(buffer);
    }
    DragFinish((HDROP)Message.WParam);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuShowOptionsClick(TObject */*Sender*/)
{
    FormOptions->chkShowTime->Checked = Config.ShowTime;
    FormOptions->ColorBox->Selected = Config.TimeColor;
    FormOptions->cboSize->ItemIndex =
                    FormOptions->cboSize->Items->IndexOf(IntToStr(Config.TimeSize));
    FormOptions->cboFont->ItemIndex =
                    FormOptions->cboFont->Items->IndexOf(Config.TimeFont);
    FormOptions->cboFormat->ItemIndex =
                    FormOptions->cboFormat->Items->IndexOf(Config.TimeFormat);
    FormOptions->tbarAlpha->Position = Config.Alpha;
    FormOptions->ColorBoxBk->Selected = Config.BkGroundColor;
    FormOptions->chkStartup->Checked = Config.Startup;

    if(FormOptions->ShowModal() == mrOk)  // Affiche les Options
    {
        Config.ShowTime = FormOptions->chkShowTime->Checked;
        Config.TimeColor = FormOptions->ColorBox->Selected;
        Config.TimeSize =  FormOptions->cboSize->Text.ToInt();
        Config.TimeFont = FormOptions->cboFont->Text;
        Config.TimeFormat = FormOptions->cboFormat->Text;
        Config.Alpha = FormOptions->tbarAlpha->Position;
        Config.BkGroundColor = FormOptions->ColorBoxBk->Selected;

        ApplySettings();

        if(Config.Startup != FormOptions->chkStartup->Checked)
        {
            Config.Startup = FormOptions->chkStartup->Checked;
            SetAtStarup();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyUp(TObject */*Sender*/, WORD &Key,
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

    for(int i = 0; i < Screen->MonitorCount; i++)
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
        befFullScr = Types::TRect(Left, Top, Width, Height);
        SetBounds(SelectedMonitor->Left, SelectedMonitor->Top,
            SelectedMonitor->Width, SelectedMonitor->Height);
    }
    else
    {   // Set back old value
        SetBounds(befFullScr.Left, befFullScr.Top,
            befFullScr.Right, befFullScr.Bottom);
    }

    dblClick = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject */*Sender*/)
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
    SetWindowTextW(tItemHWnd, LoadLocalizedString(HInstance, 1000).w_str());
    tItemHWnd = GetDlgItem(tParentHWnd, IDCANCEL);
    SetWindowTextW(tItemHWnd, LoadLocalizedString(HInstance, 1001).w_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DialogFolderChange(TObject *Sender)
{
    HWND tParentHWnd = GetParent(((TOpenDialog*)Sender)->Handle);
    HWND tItemHWnd = FindWindowEx(tParentHWnd, NULL, "SHELLDLL_DefView", NULL);
    SendMessage(tItemHWnd, WM_COMMAND, 0x702D, 0);   // Thumbs View
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DialogSelectionChange(TObject *Sender)
{
    HWND tParentHWnd = ((TOpenDialog*)Sender)->Handle;
    tParentHWnd = FindWindowEx(tParentHWnd, NULL, "TPanel", NULL);
    HWND tItemHWnd = FindWindowEx(tParentHWnd, NULL, "TSilentPaintPanel", NULL);
    SetWindowTextW(tItemHWnd, LoadLocalizedString(HInstance, IDS_NONE).w_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ChangeLanguage(TObject *Sender)
{
    TMenuItem *MenuItem = (TMenuItem*)Sender;
    MenuItem->Checked = true;

    if(mnuFrench->Checked)
    {
        Config.Language = LANG_FRENCH;
    }
    else if(mnuEnglish->Checked)
    {
        Config.Language = LANG_ENGLISH;
    }

    gwLanguage = Config.Language;

    ScanComponent(frmMain);
    ScanComponent(FormOptions);
    ScanComponent(AboutBox);

    LoadLanguage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadLanguage()
{
    // Met les noms de couleur dans la bonne langue
    FormOptions->ColorBox->Items->Strings[0] = LoadLocalizedString(HInstance, IDS_CUSTOM);
    FormOptions->ColorBox->Items->Strings[1] = LoadLocalizedString(HInstance, IDS_BLACK);
    FormOptions->ColorBox->Items->Strings[2] = LoadLocalizedString(HInstance, IDS_MAROON);
    FormOptions->ColorBox->Items->Strings[3] = LoadLocalizedString(HInstance, IDS_GREEN);
    FormOptions->ColorBox->Items->Strings[4] = LoadLocalizedString(HInstance, IDS_OLIVE);
    FormOptions->ColorBox->Items->Strings[5] = LoadLocalizedString(HInstance, IDS_NAVY);
    FormOptions->ColorBox->Items->Strings[6] = LoadLocalizedString(HInstance, IDS_PURPLE);
    FormOptions->ColorBox->Items->Strings[7] = LoadLocalizedString(HInstance, IDS_TEAL);
    FormOptions->ColorBox->Items->Strings[8] = LoadLocalizedString(HInstance, IDS_GRAY);;
    FormOptions->ColorBox->Items->Strings[9] = LoadLocalizedString(HInstance, IDS_SILVER);
    FormOptions->ColorBox->Items->Strings[10] = LoadLocalizedString(HInstance, IDS_RED);
    FormOptions->ColorBox->Items->Strings[11] = LoadLocalizedString(HInstance, IDS_LIME);
    FormOptions->ColorBox->Items->Strings[12] = LoadLocalizedString(HInstance, IDS_YELLOW);
    FormOptions->ColorBox->Items->Strings[13] = LoadLocalizedString(HInstance, IDS_BLUE);
    FormOptions->ColorBox->Items->Strings[14] = LoadLocalizedString(HInstance, IDS_FUCHSIA);
    FormOptions->ColorBox->Items->Strings[15] = LoadLocalizedString(HInstance, IDS_AQUA);
    FormOptions->ColorBox->Items->Strings[16] = LoadLocalizedString(HInstance, IDS_WHITE);
    // Pareillement pour la couleur de fond
    FormOptions->ColorBoxBk->Items = FormOptions->ColorBox->Items;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ApplySettings()
{
    this->AlphaBlend = (Config.Alpha == 255) ? false : true;
    this->AlphaBlendValue = Config.Alpha;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMain::SetAtStarup()
{
    bool bReturn = true;

    TRegistry *reg = new TRegistry();
    reg->RootKey = HKEY_CURRENT_USER;
    if(reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
    {
        if(Config.Startup == true)
        {
            try
            {
                reg->WriteString(Application->Title, Application->ExeName);
            }
            catch(...)
            {   // L'écriture dans le registre a échoué
                Config.Startup = false;
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
                Config.Startup = true;
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
    TResourceStream *Res = new TResourceStream((unsigned)HInstance, Identifier, (System::WideChar *)RT_RCDATA);
    TWICImage *WicImg = new TWICImage();
    WicImg->LoadFromStream(Res);
    Picture->Graphic = WicImg;
    delete WicImg;
    delete Res;
}
//---------------------------------------------------------------------------
