object AboutBox: TAboutBox
  Tag = 2005
  Left = 523
  Top = 594
  BorderStyle = bsDialog
  Caption = #192' propos de Photo++'
  ClientHeight = 213
  ClientWidth = 282
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 265
    Height = 161
    BevelInner = bvRaised
    BevelOuter = bvLowered
    ParentColor = True
    TabOrder = 0
    object ProgramIcon: TImage
      Left = 16
      Top = 16
      Width = 48
      Height = 48
      Stretch = True
      Transparent = True
      IsControl = True
    end
    object ProductName: TLabel
      Tag = 2000
      Left = 88
      Top = 16
      Width = 47
      Height = 13
      Caption = 'Photo ++'
      IsControl = True
    end
    object Version: TLabel
      Tag = 2001
      Left = 88
      Top = 46
      Width = 35
      Height = 13
      Caption = 'Version'
      IsControl = True
    end
    object Copyright: TLabel
      Tag = 2002
      Left = 8
      Top = 80
      Width = 47
      Height = 13
      Caption = 'Copyright'
      IsControl = True
    end
    object Comments: TLabel
      Tag = 2004
      Left = 8
      Top = 120
      Width = 120
      Height = 13
      Caption = 'crayon1@rocketmail.com'
      OnClick = CommentsClick
      IsControl = True
    end
    object Label1: TLabel
      Tag = 2003
      Left = 8
      Top = 104
      Width = 113
      Height = 13
      Caption = 'Pour plus d'#39'information:'
    end
  end
  object OKButton: TButton
    Tag = 1000
    Left = 104
    Top = 180
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
end
