//---------------------------------------------------------------------------
#pragma hdrstop

#include "UCtrl.h"
//---------------------------------------------------------------------------
TCtrl::TCtrl()
{
}
//---------------------------------------------------------------------------
TCtrl::~TCtrl()
{
}
//---------------------------------------------------------------------------
String TCtrl::executeCalcCmd(int cmdNumber, String memoryState)
{
	/* управляет вызовом операций по работе с объектами: редактор (поле TEditor), процессор (поле TProc), память (поле TMemory),
	буфер обмена (глобальный объект ClipBoard), операция получает целое число (номер команды пользователя), строку для буфера обмена,
	строку со значением состояния памяти и возвращает строку для буфера обмена, строку состояния памяти и строку результата */

        TFrac value = editor->getValue();
        TCtrlState state = getCtrlState();
        
        switch (cmdNumber) {
        case 2:
                proc->setOperation(Dvd);
                setCtrlState(cOpChange);
                break;

        case 3:
                proc->setOperation(Add);
                setCtrlState(cOpChange);
                break;

        case 4:
                proc->setOperation(Sub);
                setCtrlState(cOpChange);
                break;

        case 5:
                proc->setOperation(Mul);
                setCtrlState(cOpChange);
                break;

        case 7:
                if (editor->getValue().IsEmpty()) {
                        value = proc->getLop_Res();
                }
                
                if (state != cValDone) {
                        proc->setRop(value);
                }

                proc->OprtnRun();
                value = proc->getLop_Res();
                editor->setValue(value.getFracAsString());
                setCtrlState(cValDone);
                return editor->getValue();

        case 8:
                proc->setRop(value);
                proc->FuncRun(Rev);
                value = proc->getRop();
                editor->setValue(value.getFracAsString());
                setCtrlState(cFunDone);
                return editor->getValue();

        case 9:
                proc->setRop(value);
                proc->FuncRun(Sqr);
                value = proc->getRop();
                editor->setValue(value.getFracAsString());
                setCtrlState(cFunDone);
                return editor->getValue();

        default:
                return editor->getValue();
        }

        proc->setLop_Res(value);
        editor->setValue("");

        return editor->getValue();
}
//---------------------------------------------------------------------------
String TCtrl::executeEditorCmd(int cmdNumber)
{
	/* управляет вызовом методов объекта редактор (тип TEditor),
	операция получает целое число (номер команды пользователя и возвращает строку результата */

        TCtrlState state = getCtrlState();

        switch (cmdNumber) {
        case 1:
                return editor->changeNegativeSign();

        case 6:
                if (editor->getValue().Length() == 0) {
                        editor->setValue("0/");
                }
                if (editor->getValue().Pos("/") == 0) {
                        editor->setValue(editor->getValue() + "/");
                }
                break;

        case 12:
                editor->setValue("");
                break;

        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
                if ((state == cFunDone) || (state == cValDone)) {
                        editor->clear();
                }
                editor->addNumber(cmdNumber - 100);
                break;

        default:
                break;
        }

	return editor->getValue();
}
//---------------------------------------------------------------------------
String TCtrl::setInitialCalcState(int cmdNumber)
{
	/* управляет вызовом методов для перевода объекта типа TCalc в состояние Start,
	операция получает целое число (номер команды пользователя и возвращает строку результата) */

        editor = new TEditor;
        proc = new TProc<TFrac>;
        memory = new TMemory<TFrac>;

        ctrlState = cStart;
        editor->setValue("");

	return "";
}
//---------------------------------------------------------------------------
String TCtrl::executeMemoryCmd(int cmdNumber, String memoryState)
{
	/* управляет вызовом методов объекта типа TCtrl, обеспечивающих выполнение команд памяти,
	операция получает целое число (номер команды пользователя), строку со значением состояния
	памяти и возвращает строку состояния памяти и строку результата */

        TFrac value = editor->getValue();

        switch (cmdNumber) {
        case 13:
                memory->add(value);
                break;

        case 14:
                memory->store(value);
                break;

        case 15:
                editor->setValue(memory->restore().getFracAsString());
                break;

        case 16:
                memory->clear();
                memoryState = memory->getState();
                return "";

        default:
                break;
        }

        memoryState = memory->getState();
	return memory->getNumber().getFracAsString();
}
//---------------------------------------------------------------------------
TCtrlState TCtrl::getCtrlState()
{
	return this->ctrlState;
}
//---------------------------------------------------------------------------
void TCtrl::setCtrlState(TCtrlState state)
{
	this->ctrlState = state;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
