//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "Options.h"
#include "main.h"
#include "Translation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RxGIF"
#pragma link "SXPNGUtils"
#pragma resource "*.dfm"
#pragma resource "Images/IMAGES.res"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
   : TForm(Owner)
{
    iRightBottomCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "RIGHTBOTTOMCORNER");
    iLeftBottomCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "LEFTBOTTOMCORNER");
    iLeftTopCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "LEFTTOPCORNER");
    iRightTopCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "RIGHTTOPCORNER");
    iBottom->Picture->Bitmap->LoadFromResourceName((int)HInstance, "BOTTOM");
    iBottom->AutoSize = false;
    iTop->Picture->Bitmap->LoadFromResourceName((int)HInstance, "TOP");
    iTop->AutoSize = false;
    iLeft->Picture->Bitmap->LoadFromResourceName((int)HInstance, "LEFT");
    iLeft->AutoSize = false;
    iRight->Picture->Bitmap->LoadFromResourceName((int)HInstance, "RIGHT");
    iRight->AutoSize = false;

    mouseDown = false;
    dblClick = false;

    Dialog->Filter = "All (*.jpg;*.jpeg;*.bmp;*.png;*.gif)|*.jpg;*.jpeg;*.bmp;*.png;*.gif|"
            "JPEG Image File (*.jpg;*.jpeg)|*.jpg;*.jpeg|"
            "Bitmaps (*.bmp)|*.bmp|"
            "Portable Network Graphics (*.png)|*.png|"
            "Image CompuServe GIF (*.gif)|*.gif";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StickBorder(int nStickGap)
{
    HWND tTrayHwnd = FindWindow("Shell_TrayWnd", NULL);
    RECT tTrayRect;
    int nTrayHeight;

    if(tTrayHwnd != NULL)
    {
        GetWindowRect(tTrayHwnd, &tTrayRect);
        nTrayHeight = Screen->Height - tTrayRect.top;
        if ( abs(Top + Height - Screen->Height + nTrayHeight) <= nStickGap )
        {   // Colle à la barre des tâches
            this->Top = Screen->Height - Height - nTrayHeight;
        }
    }
    if( abs(Left) <= nStickGap )
    {   // Colle à gauche
        this->Left = 0;
    }
    if( abs(Left + Width - Screen->Width ) <= nStickGap )
    {   // Colle à droite
        this->Left = Screen->Width - Width;
    }
    if( abs(Top) <= nStickGap )
    {   // Cole en haut
        this->Top = 0;
    }
    if( abs(Top + Height - Screen->Height) <= nStickGap )
    {   // Colle en bas
        this->Top = Screen->Height - Height;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuQuitterClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    //Lecture dans le registre
    TRegistry *reg = new TRegistry();
    try
    {
        reg->RootKey = HKEY_CURRENT_USER;
        // On crée la clé si elle n'existe pas
        reg->OpenKey("SOFTWARE\\Crayon Application\\Photo ++\\", TRUE);

        Width = reg->ReadInteger("Width");
        Height = reg->ReadInteger("Height");
        Left = reg->ReadInteger("Left");
        Top = reg->ReadInteger("Top");
        isAlwayOnTop = reg->ReadBool("AlwayOnTop");
        picFile = reg->ReadString("picFile");
        gbShowTime = reg->ReadBool("ShowTime");
        gtTimeColor = (TColor)reg->ReadInteger("TimeColor");
        gnTimeSize = reg->ReadInteger("TimeSize");
        gsTimeFont = reg->ReadString("TimeFont");
        gsFormat = reg->ReadString("TimeFormat");
        gwLanguage = reg->ReadInteger("Language");

        reg->CloseKey();

        reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
        if (reg->ValueExists(Application->Title))
        {
            mnuStart->Checked = true;
        }
        else
        {
            mnuStart->Checked = false;
        }
    }
    catch (...)
    {   // Valeur par défaut
        Width = Image->Width;
        Height = Image->Height;
        Left = Screen->Width/2 - Image->Width/2;
        Top = Screen->Height/2 - Image->Height/2;
        isAlwayOnTop = true;
        gbShowTime = false;
        gtTimeColor = (TColor)0;
        gnTimeSize = 12;
        gsTimeFont = "Arial";
        gsFormat = "HH:mm:ss";
        gwLanguage = LANG_FRENCH;
    }
    delete reg;

    if (isAlwayOnTop)
    {
        FormStyle = fsStayOnTop;
    }
    else
    {
        FormStyle = fsNormal;
    }
    mnuPremierPlan->Checked = isAlwayOnTop;

    // On s'assure que l'image n'est pas en dehors de l'écran
    if (this->Left > Screen->Width)
    {
        this->Left = Screen->Width / 2 - this->Width / 2;
    }
    if (this->Top > Screen->Height)
    {
        this->Top = Screen->Height / 2 - this->Height / 2;
    }

    switch(gwLanguage)
    {
        case LANG_FRENCH:
            mnuFrench->Checked = true;
            break;
        case LANG_ENGLISH:
            mnuEnglish->Checked = true;
            break;
    }

    LoadImage(picFile);
    DragAcceptFiles(Handle, true);

    tempBMP = new Graphics::TBitmap();

    ScanComponent(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Border(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
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

void __fastcall TfrmMain::TimerTimer(TObject *Sender)
{
    HWND tTopHwnd;
    int nLeft = 1,
        nTop = 0;
    String strTime = FormatDateTime(StringReplace(StringReplace(gsFormat, "mm",
                        "nn", TReplaceFlags()), "tt", "am/pm",
                        TReplaceFlags()), Now());

    tempBMP->Width = Width - iRightTopCorner->Width - iLeftTopCorner->Width;
    tempBMP->Height = Height - iRightTopCorner->Height - iLeftTopCorner->Height;

    tempBMP->Canvas->Brush->Color = clNavy;
    tempBMP->Canvas->FillRect(Rect(0,0,ClientWidth,ClientHeight));

    // Dessine l'image dans le Bitmap temporaire
    tempBMP->Canvas->StretchDraw( Types::TRect(0,0,tempBMP->Width,tempBMP->Height), Image->Picture->Graphic);

    if(gbShowTime)
    {
        // Écris le texte dans le Bitmap temporaire
        SetBkMode(tempBMP->Canvas->Handle, TRANSPARENT);
        tempBMP->Canvas->Font->Name = gsTimeFont;
        tempBMP->Canvas->Font->Size = gnTimeSize;
//        tempBMP->Canvas->Font->Style = TFontStyles()<< fsBold;
        SetTextAlign (tempBMP->Canvas->Handle, TA_LEFT);
        tempBMP->Canvas->Font->Color = (TColor)(0xFFFFFF - gtTimeColor);
        tempBMP->Canvas->TextOut(nLeft+1, nTop+1, strTime);
        tempBMP->Canvas->Font->Color = gtTimeColor;
        tempBMP->Canvas->TextOut(nLeft, nTop, strTime);
    }

    // Assigne le Bitmap temporaire à l'application
    Canvas->Draw(iLeftTopCorner->Width, iLeftTopCorner->Height, tempBMP);

//SetZOrder(true);
//tTopHwnd = GetTopWindow(Application->MainForm->Handle);
//if(tTopHwnd==Application->MainForm->Handle)
//    Beep();

    // Au cas ou Show Desktop est appellé
    if(isAlwayOnTop)
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
        mouseDown = true;
        oldX = X;
        oldY = Y;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormMouseMove(TObject *Sender, TShiftState Shift,
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

void __fastcall TfrmMain::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft)
    {
        mouseDown = false;
        Screen->Cursor = crDefault;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuGradeurOriginalClick(TObject *Sender)
{
    Width = Image->Width;
    Height = Image->Height;
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
    if ( ExtractFileExt(imgToLoad)==".ico" || ExtractFileExt(imgToLoad)==".emf" || ExtractFileExt(imgToLoad)==".wmf")
    {
        return;
    }

    try
    {
        Image->Picture->LoadFromFile(imgToLoad);
        picFile = imgToLoad;
    }
    catch (...)
    {

    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuChoisirClick(TObject *Sender)
{
    if ( Dialog->Execute() )
    {
        /* Load l'image */
        if (FileExists (Dialog->FileName))
        {
            LoadImage(Dialog->FileName);
        }
        else
        {
            AnsiString strError = LoadLocalizedString(HInstance, IDS_FILENOTFOUND);
            MessageBeep(0);
            MessageDlg(strError, mtWarning, TMsgDlgButtons() << mbOK, 0);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    //Écriture dans le registre
    TRegistry *reg = new TRegistry();
    reg->RootKey = HKEY_CURRENT_USER;
    // On crée la clé si elle n'existe pas
    reg->OpenKey("SOFTWARE\\Crayon Application\\Photo ++\\", TRUE);

    if (this->GetClientRect() != Types::TRect(0, 0, Screen->Width, Screen->Height))
    {
        reg->WriteInteger("Left", Left);
        reg->WriteInteger("Top", Top);
        reg->WriteInteger("Height", Height);
        reg->WriteInteger("Width", Width);
    }
    else
    {
        reg->WriteInteger("Left", befFullScr.Left);
        reg->WriteInteger("Top", befFullScr.Top);
        reg->WriteInteger("Height", befFullScr.Bottom);
        reg->WriteInteger("Width", befFullScr.Right);
    }

    reg->WriteBool("AlwayOnTop", isAlwayOnTop);
    reg->WriteString("picFile", picFile);
    reg->WriteBool("ShowTime", gbShowTime);
    reg->WriteInteger("TimeColor", gtTimeColor);
    reg->WriteInteger("TimeSize", gnTimeSize);
    reg->WriteString("TimeFont", gsTimeFont);
    reg->WriteString("TimeFormat", gsFormat);
    reg->WriteInteger("Language", gwLanguage);

    delete reg;

    delete tempBMP;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPremierPlanClick(TObject *Sender)
{
    mnuPremierPlan->Checked = !mnuPremierPlan->Checked;
    isAlwayOnTop = mnuPremierPlan->Checked;

    if (isAlwayOnTop)
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

void __fastcall TfrmMain::mnuStartClick(TObject *Sender)
{
    mnuStart->Checked = !mnuStart->Checked;

    TRegistry *reg = new TRegistry();
    reg->RootKey = HKEY_CURRENT_USER;
    if(reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
    {
        try
        {
            if(mnuStart->Checked)
            {
                reg->WriteString(Application->Title, Application->ExeName);
            }
            else
            {
                reg->DeleteValue(Application->Title);
            }
        }
        catch(...)
        {   // L'écriture dans le registre a échoué
            mnuStart->Checked = !mnuStart->Checked;
        }
    }
    reg->CloseKey();
    delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuWallpaperClick(TObject *Sender)
{
    // Fonctionne avec les BMP seulement
    if(FileExists(picFile))
    {
        SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, picFile.c_str(), NULL );
    }
    else
    {
         MessageBeep(0);
         AnsiString strError = LoadLocalizedString(HInstance, IDS_FILENOTFOUND);
         MessageDlg(strError, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DropFiles(TMessage &Message)
{
    int nFiles;
    char buffer[256];

    nFiles = DragQueryFile((HDROP)Message.WParam, 0xFFFFFFFF, NULL, 0);
    for (int i = 0; i < nFiles; i++)
    {
        DragQueryFile((HDROP)Message.WParam, i, buffer, 256);
        LoadImage((AnsiString)buffer);
    }
    DragFinish((HDROP)Message.WParam);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuShowTimeClick(TObject *Sender)
{
    FormOptions->chkShowTime->Checked = gbShowTime;
    FormOptions->ColorBox->Selected = gtTimeColor;
    FormOptions->cboSize->ItemIndex =
                    FormOptions->cboSize->Items->IndexOf(IntToStr(gnTimeSize));
    FormOptions->cboFont->ItemIndex =
                    FormOptions->cboFont->Items->IndexOf(gsTimeFont);
    FormOptions->cboFormat->ItemIndex =
                    FormOptions->cboFormat->Items->IndexOf(gsFormat);

    if (FormOptions->ShowModal() == mrOk)  // Affiche les Options
    {
        gbShowTime = FormOptions->chkShowTime->Checked;
        gtTimeColor = FormOptions->ColorBox->Selected;
        gnTimeSize =  FormOptions->cboSize->Text.ToInt();
        gsTimeFont = FormOptions->cboFont->Text;
        gsFormat = FormOptions->cboFormat->Text;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key==VK_RETURN && Shift.Contains(ssAlt))
    {
        FullScreen();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FullScreen()
{
    dblClick = true;

    if (this->GetClientRect() != Types::TRect(0, 0, Screen->Width, Screen->Height))
    {
        befFullScr = Types::TRect(Left, Top, Width, Height);
        this->SetBounds(0, 0, Screen->Width, Screen->Height);
    }
    else
    {
        this->SetBounds(befFullScr.Left, befFullScr.Top, befFullScr.Right, befFullScr.Bottom);
    }
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
    SetWindowText(tItemHWnd, LoadLocalizedString(HInstance, 1000).c_str());
    tItemHWnd = GetDlgItem(tParentHWnd, IDCANCEL);
    SetWindowText(tItemHWnd, LoadLocalizedString(HInstance, 1001).c_str());
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
    SetWindowText(tItemHWnd, LoadLocalizedString(HInstance, IDS_NONE).c_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ChangeLanguage(TObject *Sender)
{
    mnuFrench->Checked = !mnuFrench->Checked;
    mnuEnglish->Checked = !mnuEnglish->Checked;

    if(mnuFrench->Checked)
    {
        gwLanguage = LANG_FRENCH;
    }
    else if(mnuEnglish->Checked)
    {
        gwLanguage = LANG_ENGLISH;
    }

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
}

