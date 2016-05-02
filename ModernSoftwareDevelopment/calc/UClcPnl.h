//---------------------------------------------------------------------------
#ifndef UClcPnlH
#define UClcPnlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>

#include "UCtrl.cpp"
//---------------------------------------------------------------------------
/* Remove border from focused buttons */
#ifndef TBB_HPP
#define TBB_HPP
namespace CalcBitBtn
{
    class TBitBtn : public Buttons::TBitBtn
    {
    public:
        inline __fastcall virtual TBitBtn(Classes::TComponent* AOwner) :
            Buttons::TBitBtn(AOwner) {}
    protected:
        virtual void __fastcall SetButtonStyle(bool)
        {
            Buttons::TBitBtn::SetButtonStyle(false);
        }
    };
};
#define TBitBtn CalcBitBtn::TBitBtn
#endif
//---------------------------------------------------------------------------
class TClcPnl : public TForm
{
__published:	// IDE-managed Components
        TStaticText *STResult;
        TStaticText *STMemory;
        TMainMenu *MainMenu1;
        TMenuItem *MFile;
        TMenuItem *MClose;
        TMenuItem *MHelp;
        TMenuItem *MAbout;
        TBitBtn *BBce;
        TBitBtn *BBc;
        TBitBtn *BBmc;
        TBitBtn *BBmr;
        TBitBtn *BBms;
        TBitBtn *BBmplus;
        TBitBtn *BB7;
        TBitBtn *BB4;
        TBitBtn *BB1;
        TBitBtn *BB0;
        TBitBtn *BB8;
        TBitBtn *BB5;
        TBitBtn *BB2;
        TBitBtn *BBplusminus;
        TBitBtn *BB9;
        TBitBtn *BB6;
        TBitBtn *BB3;
        TBitBtn *BBslash;
        TBitBtn *BBdiv;
        TBitBtn *BBmul;
        TBitBtn *BBminus;
        TBitBtn *BBplus;
        TBitBtn *BBcalc;
        TBitBtn *BBsqr;
        TBitBtn *BB1x;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BBbsClick(TObject *Sender);
        void __fastcall MCloseClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BBceClick(TObject *Sender);
        void __fastcall BBcClick(TObject *Sender);
        void __fastcall BBmcClick(TObject *Sender);
        void __fastcall BBmrClick(TObject *Sender);
        void __fastcall BBmsClick(TObject *Sender);
        void __fastcall BBmplusClick(TObject *Sender);
        void __fastcall BB7Click(TObject *Sender);
        void __fastcall BB4Click(TObject *Sender);
        void __fastcall BB1Click(TObject *Sender);
        void __fastcall BB0Click(TObject *Sender);
        void __fastcall BB8Click(TObject *Sender);
        void __fastcall BB5Click(TObject *Sender);
        void __fastcall BB2Click(TObject *Sender);
        void __fastcall BBplusminusClick(TObject *Sender);
        void __fastcall BB9Click(TObject *Sender);
        void __fastcall BB6Click(TObject *Sender);
        void __fastcall BB3Click(TObject *Sender);
        void __fastcall BBslashClick(TObject *Sender);
        void __fastcall BBdivClick(TObject *Sender);
        void __fastcall BBmulClick(TObject *Sender);
        void __fastcall BBminusClick(TObject *Sender);
        void __fastcall BBplusClick(TObject *Sender);
        void __fastcall BBsqrClick(TObject *Sender);
        void __fastcall BB1xClick(TObject *Sender);
        void __fastcall BBcalcClick(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall MAboutClick(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
private:	// User declarations
        void BBClick(int cmdNumber, String rawValue);
        bool shortFormat;
        TCtrl ctrl;
public:		// User declarations
        __fastcall TClcPnl(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClcPnl *ClcPnl;
//---------------------------------------------------------------------------
#endif
