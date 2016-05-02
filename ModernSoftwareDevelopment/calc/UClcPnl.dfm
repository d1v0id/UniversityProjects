object ClcPnl: TClcPnl
  Left = 194
  Top = 126
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Calc'
  ClientHeight = 247
  ClientWidth = 258
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object STResult: TStaticText
    Left = 11
    Top = 2
    Width = 238
    Height = 31
    Alignment = taRightJustify
    AutoSize = False
    BiDiMode = bdLeftToRight
    BorderStyle = sbsSunken
    Caption = '1/2'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentBiDiMode = False
    ParentColor = False
    ParentFont = False
    TabOrder = 0
  end
  object STMemory: TStaticText
    Left = 8
    Top = 42
    Width = 113
    Height = 31
    Alignment = taCenter
    AutoSize = False
    BevelInner = bvNone
    BorderStyle = sbsSingle
    Caption = '0/1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object BBce: TBitBtn
    Left = 168
    Top = 40
    Width = 41
    Height = 41
    Caption = 'CE'
    TabOrder = 2
    TabStop = False
    OnClick = BBceClick
  end
  object BBc: TBitBtn
    Left = 208
    Top = 40
    Width = 41
    Height = 41
    Caption = 'C'
    TabOrder = 3
    TabStop = False
    OnClick = BBcClick
  end
  object BBmc: TBitBtn
    Left = 8
    Top = 80
    Width = 41
    Height = 41
    Caption = 'MC'
    TabOrder = 4
    TabStop = False
    OnClick = BBmcClick
  end
  object BBmr: TBitBtn
    Left = 8
    Top = 120
    Width = 41
    Height = 41
    Caption = 'MR'
    TabOrder = 5
    TabStop = False
    OnClick = BBmrClick
  end
  object BBms: TBitBtn
    Left = 8
    Top = 160
    Width = 41
    Height = 41
    Caption = 'MS'
    TabOrder = 6
    TabStop = False
    OnClick = BBmsClick
  end
  object BBmplus: TBitBtn
    Left = 8
    Top = 200
    Width = 41
    Height = 41
    Caption = 'M+'
    TabOrder = 7
    TabStop = False
    OnClick = BBmplusClick
  end
  object BB7: TBitBtn
    Left = 48
    Top = 80
    Width = 41
    Height = 41
    Caption = '7'
    TabOrder = 8
    TabStop = False
    OnClick = BB7Click
  end
  object BB4: TBitBtn
    Left = 48
    Top = 120
    Width = 41
    Height = 41
    Caption = '4'
    TabOrder = 9
    TabStop = False
    OnClick = BB4Click
  end
  object BB1: TBitBtn
    Left = 48
    Top = 160
    Width = 41
    Height = 41
    Caption = '1'
    TabOrder = 10
    TabStop = False
    OnClick = BB1Click
  end
  object BB0: TBitBtn
    Left = 48
    Top = 200
    Width = 41
    Height = 41
    HelpType = htKeyword
    Caption = '0'
    TabOrder = 11
    TabStop = False
    OnClick = BB0Click
  end
  object BB8: TBitBtn
    Left = 88
    Top = 80
    Width = 41
    Height = 41
    Caption = '8'
    TabOrder = 12
    TabStop = False
    OnClick = BB8Click
  end
  object BB5: TBitBtn
    Left = 88
    Top = 120
    Width = 41
    Height = 41
    Caption = '5'
    TabOrder = 13
    TabStop = False
    OnClick = BB5Click
  end
  object BB2: TBitBtn
    Left = 88
    Top = 160
    Width = 41
    Height = 41
    Caption = '2'
    TabOrder = 14
    TabStop = False
    OnClick = BB2Click
  end
  object BBplusminus: TBitBtn
    Left = 88
    Top = 200
    Width = 41
    Height = 41
    Caption = '+\-'
    TabOrder = 15
    TabStop = False
    OnClick = BBplusminusClick
  end
  object BB9: TBitBtn
    Left = 128
    Top = 80
    Width = 41
    Height = 41
    Caption = '9'
    TabOrder = 16
    TabStop = False
    OnClick = BB9Click
  end
  object BB6: TBitBtn
    Left = 128
    Top = 120
    Width = 41
    Height = 41
    Caption = '6'
    TabOrder = 17
    TabStop = False
    OnClick = BB6Click
  end
  object BB3: TBitBtn
    Left = 128
    Top = 160
    Width = 41
    Height = 41
    Caption = '3'
    TabOrder = 18
    TabStop = False
    OnClick = BB3Click
  end
  object BBslash: TBitBtn
    Left = 128
    Top = 200
    Width = 41
    Height = 41
    Caption = '\'
    TabOrder = 19
    TabStop = False
    OnClick = BBslashClick
  end
  object BBdiv: TBitBtn
    Left = 168
    Top = 80
    Width = 41
    Height = 41
    Caption = '/'
    TabOrder = 20
    TabStop = False
    OnClick = BBdivClick
  end
  object BBmul: TBitBtn
    Left = 168
    Top = 120
    Width = 41
    Height = 41
    Caption = '*'
    TabOrder = 21
    TabStop = False
    OnClick = BBmulClick
  end
  object BBminus: TBitBtn
    Left = 168
    Top = 160
    Width = 41
    Height = 41
    Caption = '-'
    TabOrder = 22
    TabStop = False
    OnClick = BBminusClick
  end
  object BBplus: TBitBtn
    Left = 168
    Top = 200
    Width = 41
    Height = 41
    Caption = '+'
    TabOrder = 23
    TabStop = False
    OnClick = BBplusClick
  end
  object BBsqr: TBitBtn
    Left = 208
    Top = 80
    Width = 41
    Height = 41
    Caption = 'sqr'
    TabOrder = 25
    TabStop = False
    OnClick = BBsqrClick
  end
  object BB1x: TBitBtn
    Left = 208
    Top = 120
    Width = 41
    Height = 41
    Caption = '1/x'
    TabOrder = 26
    TabStop = False
    OnClick = BB1xClick
  end
  object BBcalc: TBitBtn
    Left = 208
    Top = 160
    Width = 41
    Height = 81
    Caption = '='
    TabOrder = 24
    TabStop = False
    OnClick = BBcalcClick
  end
  object MainMenu1: TMainMenu
    Left = 8
    object MFile: TMenuItem
      Caption = #1060#1072#1081#1083
      object MClose: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = MCloseClick
      end
    end
    object N1: TMenuItem
      Caption = #1042#1080#1076
      object N2: TMenuItem
        Caption = #1062#1077#1083#1086#1077
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1062#1077#1083#1086#1077' '#1080' '#1076#1088#1086#1073#1100
        OnClick = N3Click
      end
    end
    object MHelp: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object MAbout: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = MAboutClick
      end
    end
  end
end
