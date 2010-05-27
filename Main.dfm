object frmMain: TfrmMain
  Left = 511
  Top = 452
  BorderIcons = []
  BorderStyle = bsNone
  ClientHeight = 411
  ClientWidth = 340
  Color = clNavy
  TransparentColorValue = clNavy
  Constraints.MinHeight = 75
  Constraints.MinWidth = 75
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu
  ScreenSnap = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyUp = FormKeyUp
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object iRightBottomCorner: TImage
    Tag = 1
    Left = 105
    Top = 201
    Width = 43
    Height = 40
    Cursor = crSizeNWSE
    AutoSize = True
    OnMouseDown = Border
  end
  object iLeftBottomCorner: TImage
    Tag = 2
    Left = 48
    Top = 200
    Width = 40
    Height = 44
    Cursor = crSizeNESW
    AutoSize = True
    OnMouseDown = Border
  end
  object iLeftTopCorner: TImage
    Tag = 3
    Left = 49
    Top = 152
    Width = 32
    Height = 41
    Cursor = crSizeNWSE
    AutoSize = True
    OnMouseDown = Border
  end
  object iRightTopCorner: TImage
    Tag = 4
    Left = 96
    Top = 152
    Width = 48
    Height = 36
    Cursor = crSizeNESW
    AutoSize = True
    OnMouseDown = Border
  end
  object iBottom: TImage
    Tag = 5
    Left = 72
    Top = 250
    Width = 72
    Height = 33
    Cursor = crSizeNS
    AutoSize = True
    Stretch = True
    OnMouseDown = Border
  end
  object iTop: TImage
    Tag = 6
    Left = 60
    Top = 112
    Width = 69
    Height = 20
    Cursor = crSizeNS
    AutoSize = True
    Stretch = True
    OnMouseDown = Border
  end
  object iLeft: TImage
    Tag = 7
    Left = 8
    Top = 176
    Width = 24
    Height = 50
    Cursor = crSizeWE
    AutoSize = True
    Stretch = True
    OnMouseDown = Border
  end
  object iRight: TImage
    Tag = 8
    Left = 172
    Top = 165
    Width = 21
    Height = 61
    Cursor = crSizeWE
    AutoSize = True
    Stretch = True
    OnMouseDown = Border
  end
  object PopupMenu: TPopupMenu
    Left = 48
    Top = 8
    object mnuChoisir: TMenuItem
      Tag = 4000
      Caption = 'Choisir l'#39'image...'
      OnClick = mnuChoisirClick
    end
    object mnuBar1: TMenuItem
      Caption = '-'
    end
    object mnuShowOptions: TMenuItem
      Tag = 4001
      Caption = 'Options...'
      OnClick = mnuShowOptionsClick
    end
    object mnuGradeurOriginal: TMenuItem
      Tag = 4002
      Caption = 'Mettre la grandeur originale'
      OnClick = mnuGradeurOriginalClick
    end
    object mnuPremierPlan: TMenuItem
      Tag = 4003
      Caption = 'Mettre en premier plan'
      OnClick = mnuPremierPlanClick
    end
    object mnuWallpaper: TMenuItem
      Tag = 4005
      Caption = 'Mettre l'#39'image comme papier peint'
      Visible = False
      OnClick = mnuWallpaperClick
    end
    object mnuLanguage: TMenuItem
      Tag = 4009
      Caption = 'Langue'
      object mnuFrench: TMenuItem
        Caption = 'Fran'#231'ais'
        OnClick = ChangeLanguage
      end
      object mnuEnglish: TMenuItem
        Caption = 'English'
        OnClick = ChangeLanguage
      end
    end
    object mnuBar2: TMenuItem
      Caption = '-'
    end
    object mnuAPropos: TMenuItem
      Tag = 4006
      Caption = #192' &propos...'
      OnClick = mnuAProposClick
    end
    object mnuBar3: TMenuItem
      Caption = '-'
    end
    object mnuQuitter: TMenuItem
      Tag = 4007
      Caption = '&Quitter'
      OnClick = mnuQuitterClick
    end
  end
  object Timer: TTimer
    Interval = 50
    OnTimer = TimerTimer
    Left = 96
    Top = 8
  end
end
