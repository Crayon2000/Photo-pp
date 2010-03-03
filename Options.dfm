object FormOptions: TFormOptions
  Tag = 2500
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Options'
  ClientHeight = 461
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
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object cmdOK: TButton
    Tag = 1000
    Left = 252
    Top = 431
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object cmdCancel: TButton
    Tag = 1001
    Left = 333
    Top = 431
    Width = 75
    Height = 25
    Caption = 'Annuler'
    ModalResult = 2
    TabOrder = 1
  end
  object pctrlOptions: TPageControl
    Left = 8
    Top = 6
    Width = 400
    Height = 419
    ActivePage = TabSheet2
    TabOrder = 2
    OnChange = pctrlOptionsChange
    object TabSheet2: TTabSheet
      Tag = 5000
      Caption = 'Affichage'
      object GroupBox2: TGroupBox
        Tag = 5001
        Left = 16
        Top = 36
        Width = 366
        Height = 102
        Caption = 'Opacit'#233
        TabOrder = 1
        object Label7: TLabel
          Tag = 5004
          Left = 14
          Top = 60
          Width = 339
          Height = 34
          AutoSize = False
          Caption = 
            'L'#39'opacit'#233' est seulement disponible pour Windows 2000 ou mieux.'#13#10 +
            'En plus, le syst'#232'me doit '#234'tre un P90 ou mieux.'
        end
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
        Left = 16
        Top = 319
        Width = 366
        Height = 57
        Caption = 'Couleur de l'#39'arri'#232're plan'
        TabOrder = 3
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
        Left = 16
        Top = 10
        Width = 369
        Height = 17
        Caption = 'Ouvrir le programme au d'#233'marrage'
        TabOrder = 0
      end
      object GroupBox5: TGroupBox
        Tag = 5006
        Left = 16
        Top = 144
        Width = 366
        Height = 97
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
        Left = 16
        Top = 247
        Width = 366
        Height = 66
        Caption = 'Rotation'
        TabOrder = 4
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
    end
    object TabSheet1: TTabSheet
      Tag = 3000
      Caption = 'Param'#232'tres de l'#39'horloge'
      object Label10: TLabel
        Tag = 3005
        Left = 16
        Top = 118
        Width = 159
        Height = 13
        AutoSize = False
        Caption = 'Format de l'#39'heure:'
      end
      object Label3: TLabel
        Tag = 3004
        Left = 16
        Top = 91
        Width = 159
        Height = 13
        AutoSize = False
        Caption = 'Police de caract'#232're:'
      end
      object Label2: TLabel
        Tag = 3003
        Left = 16
        Top = 64
        Width = 159
        Height = 13
        AutoSize = False
        Caption = 'Taille du texte:'
      end
      object Label1: TLabel
        Tag = 3002
        Left = 16
        Top = 36
        Width = 159
        Height = 13
        AutoSize = False
        Caption = 'Couleur du texte:'
      end
      object GroupBox3: TGroupBox
        Tag = 3008
        Left = 16
        Top = 263
        Width = 366
        Height = 118
        Caption = 'Aper'#231'u'
        TabOrder = 0
        object txtExample: TEdit
          Left = 14
          Top = 17
          Width = 339
          Height = 89
          TabStop = False
          AutoSize = False
          Color = clBtnFace
          ReadOnly = True
          TabOrder = 0
        end
      end
      object chkShowTime: TCheckBox
        Tag = 3001
        Left = 16
        Top = 10
        Width = 201
        Height = 17
        Caption = 'Afficher l'#39'horloge'
        TabOrder = 1
      end
      object GroupBox1: TGroupBox
        Tag = 3006
        Left = 16
        Top = 142
        Width = 366
        Height = 115
        Caption = 'Notation du format de l'#39'heure'
        TabOrder = 2
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
      object ColorBox: TColorBox
        Left = 181
        Top = 33
        Width = 201
        Height = 22
        Style = [cbStandardColors, cbCustomColor]
        TabOrder = 3
      end
      object cboSize: TComboBox
        Left = 181
        Top = 61
        Width = 201
        Height = 21
        Style = csDropDownList
        TabOrder = 4
      end
      object cboFont: TComboBox
        Left = 181
        Top = 88
        Width = 201
        Height = 21
        Style = csDropDownList
        TabOrder = 5
      end
      object cboFormat: TComboBox
        Left = 181
        Top = 115
        Width = 201
        Height = 21
        Style = csDropDownList
        TabOrder = 6
      end
    end
  end
  object Timer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = TimerTimer
    Left = 208
    Top = 428
  end
end
