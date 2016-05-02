//---------------------------------------------------------------------------

#ifndef UPanel_pTopH
#define UPanel_pTopH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "UCtrl.h"
#include "ULHistory.h"
#include "UAbout.h"
#include <Menus.hpp>
#include <list>
#include <iterator>

using namespace std;
//---------------------------------------------------------------------------
class TConvPanel : public TForm
{
__published:	// IDE-managed Components
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;
        TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;
        TSpeedButton *SpeedButton9;
        TSpeedButton *SpeedButton10;
        TSpeedButton *SpeedButton11;
        TSpeedButton *SpeedButton12;
        TSpeedButton *SpeedButton13;
        TSpeedButton *SpeedButton14;
        TSpeedButton *SpeedButton15;
        TSpeedButton *SpeedButton16;
        TSpeedButton *SpeedButton17;
        TSpeedButton *SpeedButton18;
        TSpeedButton *SpeedButton19;
        TSpeedButton *SpeedButton20;
        TSpeedButton *SpeedButton21;
        TTrackBar *TrackBar1;
        TLabel *Label1;
        TLabel *P_In_Label;
        TStaticText *StaticText1;
        TLabel *Label3;
        TStaticText *StaticText2;
        TLabel *Label4;
        TTrackBar *TrackBar2;
        TLabel *P_Out_Label;
        TLabel *Label6;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Exit1;
        TMenuItem *History1;
        TMenuItem *Clear1;
        TMenuItem *Clear2;
        TMenuItem *About1;
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SpeedButtonClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall Clear2Click(TObject *Sender);
        void __fastcall Clear1Click(TObject *Sender);
private:	// User declarations
        TCtrl* Control;
        TLHistory* History;

        void UpdateSB();
        void DoCommand(int);
public:		// User declarations
        __fastcall TConvPanel(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConvPanel *ConvPanel;
//---------------------------------------------------------------------------
#endif
