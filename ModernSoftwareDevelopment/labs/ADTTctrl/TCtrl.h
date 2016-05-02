#include "TEditor.h"
#include "TProc.cpp"
#include "TMemory.cpp"
#include "TFrac.cpp"

#pragma once

enum TCtrlState { cStart, cEditing, cFunDone, cValDone, cExpDone, cOpChange, cError };

class TCtrl
{
public:
	TCtrl();
	~TCtrl();
	string executeCalcCmd(int, string *, string *);
	string executeEditorCmd(int);
	string executeOperation(int);
	string executeFunction(int);
	string calculateExpression(int);
	string setInitialCalcState(int);
	string executeMemoryCmd(int, string *);
	string executeClipboardCmd(int, string *);
	TCtrlState getCtrlState();
	void setCtrlState(TCtrlState);

private:
	TEditor editor;
	TProc<> proc;
	TMemory<> memory;
	TCtrlState ctrlState;
	TFrac<> frac;
};

