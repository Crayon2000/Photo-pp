//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RxGIF"
#pragma resource "*.dfm"
#pragma resource "Images/IMAGES.res"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
   : TForm(Owner)
{
   RightBottomCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "RightBottomCorner");
   LeftBottomCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "LeftBottomCorner");
   LeftTopCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "LeftTopCorner");
   RightTopCorner->Picture->Bitmap->LoadFromResourceName((int)HInstance, "RightTopCorner");
   iBottom->Picture->Bitmap->LoadFromResourceName((int)HInstance, "Bottom");
   iBottom->AutoSize = false;
   iTop->Picture->Bitmap->LoadFromResourceName((int)HInstance, "Top");
   iTop->AutoSize = false;
   iLeft->Picture->Bitmap->LoadFromResourceName((int)HInstance, "Left");
   iLeft->AutoSize = false;
   iRight->Picture->Bitmap->LoadFromResourceName((int)HInstance, "Right");
   iRight->AutoSize = false;

   mouseDown = false;
   dblClick = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StickBorder(int stickGap)
{
   if ( abs(Left) <= stickGap ) {
      Left = 0;
   }
   if ( abs(Left + Width - Screen->Width ) <= stickGap ) {
      Left = Screen->Width - Width;
   }
   if ( abs(Top) <= stickGap ) {
      Top = 0;
   }
   if ( abs(Top + Width - Screen->Height) <= stickGap ) {
      Top = Screen->Height - Height;
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
      showTime = reg->ReadBool("ShowTime");

      reg->CloseKey();

      reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
      if (reg->ValueExists(Application->Title))
      {
         mnuStart->Checked = true;
      }
      else {
         mnuStart->Checked = false;
      }
   }
   catch (...)
   {
      Width = Image->Width;
      Height = Image->Height;
      Left = Screen->Width/2 - Image->Width/2;
      Top = Screen->Height/2 - Image->Height/2;
      isAlwayOnTop = true;
      showTime = false;
   }
   delete reg;

   if (isAlwayOnTop) {
      FormStyle = fsStayOnTop;
   }
   else {
      FormStyle = fsNormal;
   }
   mnuPremierPlan->Checked = isAlwayOnTop;

   mnuShowTime->Checked = showTime;

   // On s'assure que l'image n'est pas en dehors de l'écran
   if (this->Left > Screen->Width) {
      this->Left = Screen->Width / 2 - this->Width / 2;
   }
   if (this->Top > Screen->Height) {
      this->Top = Screen->Height / 2 - this->Height / 2;
   }

   LoadImage(picFile);
   DragAcceptFiles(Handle, true);

   tempBMP = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Border(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   if (Button == mbLeft) {
      TImage *myimage = (TImage*) Sender;
      ReleaseCapture();

      switch (myimage->Tag){
      case 1:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, 0);
         break;
      case 2:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTBOTTOMLEFT, 0);
         break;
      case 3:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTTOPLEFT, 0);
         break;
      case 4:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTTOPRIGHT, 0);
         break;
      case 5:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTBOTTOM, 0);
         break;
      case 6:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTTOP, 0);
         break;
      case 7:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTLEFT, 0);
         break;
      case 8:
         SNDMSG(Handle, WM_NCLBUTTONDOWN, HTRIGHT, 0);
         break;
      default:
         break;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TimerTimer(TObject *Sender)
{
   String strTime = TimeToStr( Now() );

   tempBMP->Width = Width - RightTopCorner->Width - LeftTopCorner->Width;
   tempBMP->Height = Height - RightTopCorner->Height - LeftTopCorner->Height;

   tempBMP->Canvas->Brush->Color = clNavy;
   tempBMP->Canvas->FillRect(Rect(0,0,ClientWidth,ClientHeight));

   // Dessine l'image dans le Bitmap temporaire
   tempBMP->Canvas->StretchDraw( TRect(0,0,tempBMP->Width,tempBMP->Height), Image->Picture->Graphic);

   if (showTime)
   {
       // Écris le texte dans le Bitmap temporaire
       int iLeft, iTop;
       iLeft = 1;
       iTop = 0;
       SetBkMode(tempBMP->Canvas->Handle, TRANSPARENT);
       tempBMP->Canvas->Font->Name = "Arial";
       tempBMP->Canvas->Font->Size = 12;
       tempBMP->Canvas->Font->Style = TFontStyles()<< fsBold;
       SetTextAlign (tempBMP->Canvas->Handle, TA_LEFT);
       tempBMP->Canvas->Font->Color = (TColor)RGB(255,254,255);
       tempBMP->Canvas->TextOut(iLeft+1, iTop+1, strTime);
       tempBMP->Canvas->Font->Color = clBlack;
       tempBMP->Canvas->TextOut(iLeft, iTop, strTime);
   }

   // Assigne le Bitmap temporaire à l'application
   Canvas->Draw(LeftTopCorner->Width, LeftTopCorner->Height, tempBMP);

   // Au cas ou Show Desktop es appellé
   if (isAlwayOnTop) {
      FormStyle = fsStayOnTop;
   }
   else {
      FormStyle = fsNormal;
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
      StickBorder(20);
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
   if ( ExtractFileExt(imgToLoad)==".ico" || ExtractFileExt(imgToLoad)==".emf" || ExtractFileExt(imgToLoad)==".wmf"){
      return;
   }

   try {
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
         MessageBeep(0);
         MessageDlg("Fichier introuvable." \
                    "\r\n" \
                    "Vérifiez que le nom de fichier a été correctement entré.",
                    mtWarning, TMsgDlgButtons() << mbOK, 0);
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

   if (this->GetClientRect() != TRect(0, 0, Screen->Width, Screen->Height)){
     reg->WriteInteger("Left", Left);
     reg->WriteInteger("Top", Top);
     reg->WriteInteger("Height", Height);
     reg->WriteInteger("Width", Width);
   }
   else {
     reg->WriteInteger("Left", befFullScr.Left);
     reg->WriteInteger("Top", befFullScr.Top);
     reg->WriteInteger("Height", befFullScr.Bottom);
     reg->WriteInteger("Width", befFullScr.Right);
   }

   reg->WriteBool("AlwayOnTop", isAlwayOnTop);
   reg->WriteString("picFile", picFile);
   reg->WriteBool("ShowTime", showTime);
   delete reg;

   delete tempBMP;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPremierPlanClick(TObject *Sender)
{
   mnuPremierPlan->Checked = !mnuPremierPlan->Checked;
   isAlwayOnTop = mnuPremierPlan->Checked;

   if (isAlwayOnTop) {
      FormStyle = fsStayOnTop;
   }
   else {
      FormStyle = fsNormal;
   }

   DragAcceptFiles(Handle, true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
   ShowWindow(Application->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuStartClick(TObject *Sender)
{
    mnuStart->Checked = !mnuStart->Checked;

    TRegistry *reg = new TRegistry();
    reg->RootKey = HKEY_CURRENT_USER;
    reg->OpenKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run", false);
    if (mnuStart->Checked){
       reg->WriteString(Application->Title, Application->ExeName);
    }
    else {
       reg->DeleteValue(Application->Title);
    }
    delete reg;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuWallpaperClick(TObject *Sender)
{
  // Fonctionne avec les BMP seulement
  if (FileExists(picFile)){
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, picFile.c_str(), NULL );
  }
  else
  {
     MessageBeep(0);
     MessageDlg("Action impossible à exécuter car le fichier introuvable.",
                mtWarning, TMsgDlgButtons() << mbOK, 0);
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
  showTime = !showTime;
  mnuShowTime->Checked = showTime;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==13 && Shift.Contains(ssAlt)){
      FullScreen();
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FullScreen()
{
     dblClick = true;

     if (this->GetClientRect() != TRect(0, 0, Screen->Width, Screen->Height)){
       befFullScr = TRect(Left, Top, Width, Height);
       this->SetBounds(0, 0, Screen->Width, Screen->Height);
     }
     else{
       this->SetBounds(befFullScr.Left, befFullScr.Top, befFullScr.Right, befFullScr.Bottom);
     }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject *Sender)
{
   // Place les Bordures
   RightBottomCorner->Left = Width - RightBottomCorner->Width;
   RightBottomCorner->Top = Height - RightBottomCorner->Height;
   LeftBottomCorner->Left = 0;
   LeftBottomCorner->Top = Height - LeftBottomCorner->Height;
   LeftTopCorner->Left = 0;
   LeftTopCorner->Top = 0;
   RightTopCorner->Left = Width - RightTopCorner->Width;
   RightTopCorner->Top = 0;
   iBottom->Left = LeftBottomCorner->Width;
   iBottom->Top = Height - iBottom->Height;
   iBottom->Width = Width - LeftBottomCorner->Width - RightBottomCorner->Width;
   iTop->Left = LeftTopCorner->Height;
   iTop->Top = 0;
   iTop->Width = Width - LeftTopCorner->Width - RightTopCorner->Width;
   iLeft->Left = 0;
   iLeft->Top = LeftTopCorner->Height;
   iLeft->Height = Height - LeftTopCorner->Width - LeftBottomCorner->Width;
   iRight->Left = Width - iRight->Width;
   iRight->Top = RightTopCorner->Height;
   iRight->Height = Height - RightTopCorner->Width - RightBottomCorner->Width;
}
//---------------------------------------------------------------------------

