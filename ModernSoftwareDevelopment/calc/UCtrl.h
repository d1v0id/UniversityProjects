//---------------------------------------------------------------------------
#ifndef UCtrlH
#define UCtrlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "UEditor.h"
#include "UProc.cpp"
#include "UMemory.cpp"
#include "UFrac.h"

enum TCtrlState { cStart, cEditing, cFunDone, cValDone, cExpDone, cOpChange, cError };
//---------------------------------------------------------------------------
class TCtrl
{
public:
	TCtrl();
	~TCtrl();
	String executeCalcCmd(int, String);
	String executeEditorCmd(int);
	String setInitialCalcState(int);
	String executeMemoryCmd(int, String);
	TCtrlState getCtrlState();
	void setCtrlState(TCtrlState);

private:
        TEditor *editor;
        TProc<TFrac> *proc;
        TMemory<TFrac> *memory;
	TCtrlState ctrlState;
};
//---------------------------------------------------------------------------
#endif
 