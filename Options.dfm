object FormOptions: TFormOptions
  Tag = 2500
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 466
  ClientWidth = 414
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pctrlOptions: TPageControl
    AlignWithMargins = True
    Left = 6
    Top = 6
    Width = 402
    Height = 422
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 1
    OnChange = pctrlOptionsChange
    object TabSheet2: TTabSheet
      Tag = 5000
      Caption = 'Affichage'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox2: TGroupBox
        Tag = 5001
        AlignWithMargins = True
        Left = 10
        Top = 31
        Width = 374
        Height = 53
        Margins.Left = 10
        Margins.Right = 10
        Align = alTop
        Caption = 'Opacit'#233
        TabOrder = 1
        object Label4: TLabel
          Tag = 5002
          Left = 14
          Top = 21
          Width = 67
          Height = 13
          AutoSize = False
          Caption = 'Transparent'
        end
        object Label8: TLabel
          Tag = 5003
          Left = 296
          Top = 21
          Width = 67
          Height = 13
          AutoSize = False
          Caption = 'Opaque'
        end
        object tbarAlpha: TTrackBar
          Left = 78
          Top = 16
          Width = 212
          Height = 25
          LineSize = 5
          Max = 255
          Min = 55
          PageSize = 25
          Frequency = 10
          Position = 255
          ShowSelRange = False
          TabOrder = 0
        end
      end
      object GroupBox4: TGroupBox
        Tag = 5005
        AlignWithMargins = True
        Left = 10
        Top = 328
        Width = 374
        Height = 57
        Margins.Left = 10
        Margins.Right = 10
        Align = alTop
        Caption = 'Couleur de l'#39'arri'#232're plan'
        TabOrder = 4
        object ColorBoxBk: TColorBox
          Left = 14
          Top = 19
          Width = 339
          Height = 22
          Style = [cbStandardColors, cbCustomColor]
          TabOrder = 0
        end
      end
      object chkStartup: TCheckBox
        Tag = 4004
        AlignWithMargins = True
        Left = 10
        Top = 8
        Width = 374
        Height = 17
        Margins.Left = 10
        Margins.Top = 8
        Margins.Right = 10
        Align = alTop
        Caption = 'Ouvrir le programme au d'#233'marrage'
        TabOrder = 0
      end
      object GroupBox5: TGroupBox
        Tag = 5006
        AlignWithMargins = True
        Left = 10
        Top = 90
        Width = 374
        Height = 97
        Margins.Left = 10
        Margins.Right = 10
        Align = alTop
        Caption = 'Position'
        TabOrder = 2
        object optKeepAR: TRadioButton
          Tag = 5008
          Left = 14
          Top = 38
          Width = 327
          Height = 25
          Caption = 'Conserver le rapport de l'#39'image et ajouter des bordures'
          TabOrder = 1
        end
        object optStretch: TRadioButton
          Tag = 5007
          Left = 14
          Top = 23
          Width = 327
          Height = 17
          Caption = #201'tirer l'#39'image'
          TabOrder = 0
        end
        object optTiled: TRadioButton
          Tag = 5009
          Left = 14
          Top = 61
          Width = 327
          Height = 25
          Caption = 'Mosa'#239'que'
          TabOrder = 2
        end
      end
      object GroupBox6: TGroupBox
        Tag = 5010
        AlignWithMargins = True
        Left = 10
        Top = 193
        Width = 374
        Height = 66
        Margins.Left = 10
        Margins.Right = 10
        Align = alTop
        Caption = 'Rotation'
        TabOrder = 3
        object chkFlipH: TCheckBox
          Tag = 5011
          Left = 14
          Top = 18
          Width = 330
          Height = 17
          Caption = 'Retourner horizontalement'
          TabOrder = 0
        end
        object chkFlipV: TCheckBox
          Tag = 5012
          Left = 14
          Top = 41
          Width = 330
          Height = 17
          Caption = 'Retourner verticalement'
          TabOrder = 1
        end
      end
      object GroupBox7: TGroupBox
        Tag = 5013
        AlignWithMargins = True
        Left = 10
        Top = 265
        Width = 374
        Height = 57
        Margins.Left = 10
        Margins.Right = 10
        Align = alTop
        Caption = 'Diaporama'
        TabOrder = 5
        object Label6: TLabel
          Tag = 5016
          Left = 14
          Top = 24
          Width = 132
          Height = 13
          AutoSize = False
          Caption = 'Afficher chaque image:'
        end
        object cboInterval: TComboBox
          Left = 152
          Top = 20
          Width = 201
          Height = 21
          Style = csDropDownList
          TabOrder = 0
        end
      end
    end
    object TabSheet1: TTabSheet
      Tag = 3000
      Caption = 'Param'#232'tres de l'#39'horloge'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox3: TGroupBox
        Tag = 3008
        AlignWithMargins = True
        Left = 10
        Top = 264
        Width = 374
        Height = 120
        Margins.Left = 10
        Margins.Right = 10
        Margins.Bottom = 10
        Align = alClient
        Caption = 'Aper'#231'u'
        TabOrder = 0
        ExplicitLeft = 16
        ExplicitTop = 263
        ExplicitWidth = 366
        ExplicitHeight = 118
        object txtExample: TEdit
          AlignWithMargins = True
          Left = 12
          Top = 25
          Width = 350
          Height = 83
          Margins.Left = 10
          Margins.Top = 10
          Margins.Right = 10
          Margins.Bottom = 10
          TabStop = False
          Align = alClient
          AutoSize = False
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 0
          ExplicitLeft = 14
          ExplicitTop = 17
          ExplicitWidth = 339
          ExplicitHeight = 89
        end
      end
      object GroupBox1: TGroupBox
        Tag = 3006
        AlignWithMargins = True
        Left = 10
        Top = 143
        Width = 374
        Height = 115
        Margins.Left = 10
        Margins.Right = 10
        Align = alTop
        Caption = 'Notation du format de l'#39'heure'
        TabOrder = 1
        ExplicitLeft = 16
        ExplicitTop = 142
        ExplicitWidth = 366
        object Label5: TLabel
          Tag = 3007
          Left = 14
          Top = 15
          Width = 339
          Height = 90
          AutoSize = False
          Caption = 
            'h = heure   m = minute   s = seconde   t = matin ou apr'#232's-midi'#13#10 +
            #13#10'h = 12 heures'#13#10'H = 24 heures'#13#10#13#10'hh, mm, ss = pr'#233'c'#233'd'#233' d'#39'un z'#233'ro' +
            #13#10'h, m, s = pas de z'#233'ro'
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 394
        Height = 140
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 2
        object Label3: TLabel
          Tag = 3004
          Left = 10
          Top = 89
          Width = 159
          Height = 13
          AutoSize = False
          Caption = 'Police de caract'#232're:'
        end
        object Label10: TLabel
          Tag = 3005
          Left = 10
          Top = 116
          Width = 159
          Height = 13
          AutoSize = False
          Caption = 'Format de l'#39'heure:'
        end
        object Label1: TLabel
          Tag = 3002
          Left = 10
          Top = 34
          Width = 159
          Height = 13
          AutoSize = False
          Caption = 'Couleur du texte:'
        end
        object Label2: TLabel
          Tag = 3003
          Left = 10
          Top = 62
          Width = 159
          Height = 13
          AutoSize = False
          Caption = 'Taille du texte:'
        end
        object ColorBox: TColorBox
          Left = 175
          Top = 31
          Width = 201
          Height = 22
          Style = [cbStandardColors, cbCustomColor]
          TabOrder = 0
        end
        object chkShowTime: TCheckBox
          Tag = 3001
          Left = 10
          Top = 8
          Width = 201
          Height = 17
          Caption = 'Afficher l'#39'horloge'
          TabOrder = 1
        end
        object cboFormat: TComboBox
          Left = 175
          Top = 113
          Width = 201
          Height = 21
          Style = csDropDownList
          TabOrder = 2
        end
        object cboFont: TComboBox
          Left = 175
          Top = 86
          Width = 201
          Height = 21
          Style = csDropDownList
          TabOrder = 3
        end
        object cboSize: TComboBox
          Left = 175
          Top = 59
          Width = 201
          Height = 21
          Style = csDropDownList
          TabOrder = 4
        end
      end
    end
  end
  object pnlBottom: TPanel
    Left = 0
    Top = 431
    Width = 414
    Height = 35
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object cmdOK: TButton
      Tag = 1000
      Left = 248
      Top = 5
      Width = 75
      Height = 25
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
    end
    object cmdCancel: TButton
      Tag = 1001
      Left = 329
      Top = 5
      Width = 75
      Height = 25
      Caption = 'Annuler'
      ModalResult = 2
      TabOrder = 1
    end
  end
  object Timer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = TimerTimer
    Left = 24
    Top = 428
  end
end
