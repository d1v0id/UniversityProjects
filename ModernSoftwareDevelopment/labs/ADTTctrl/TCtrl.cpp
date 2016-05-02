#include "stdafx.h"
#include "TCtrl.h"

TCtrl::TCtrl()
{
}

TCtrl::~TCtrl()
{
}

string TCtrl::executeCalcCmd(int cmdNumber, string *clipboardBuffer, string *memoryState)
{
	/* управляет вызовом операций по работе с объектами: редактор (поле TEditor), процессор (поле TProc), память (поле TMemory),
	буфер обмена (глобальный объект ClipBoard), операция получает целое число (номер команды пользователя), строку для буфера обмена,
	строку со значением состояния памяти и возвращает строку для буфера обмена, строку состояния памяти и строку результата */

	return "";
}

string TCtrl::executeEditorCmd(int cmdNumber)
{
	/* управляет вызовом методов объекта редактор (тип TEditor),
	операция получает целое число (номер команды пользователя и возвращает строку результата */
	
	return "";
}

string TCtrl::executeOperation(int cmdNumber)
{
	/* управляет вызовом методов объекта процессор (поле TProc),
	операция получает целое число (номер команды пользователя и возвращает строку результата */

	return "";
}

string TCtrl::executeFunction(int cmdNumber)
{
	/* управляет вызовом методов объекта процессор (поле TProc),
	операция получает целое число (номер команды пользователя и возвращает строку результата */

	return "";
}

string TCtrl::calculateExpression(int cmdNumber)
{
	/* управляет вызовом методов объекта процессор (поле TProc),
	операция получает целое число (номер команды пользователя и возвращает строку результата */

	return "";
}

string TCtrl::setInitialCalcState(int cmdNumber)
{
	/* управляет вызовом методов для перевода объекта типа TCalc в состояние Start,
	операция получает целое число (номер команды пользователя и возвращает строку результата */

	return "";
}

string TCtrl::executeMemoryCmd(int cmdNumber, string *memoryState)
{
	/* управляет вызовом методов объекта типа TCtrl, обеспечивающих выполнение команд памяти,
	операция получает целое число (номер команды пользователя), строку со значением состояния
	памяти и возвращает строку состояния памяти и строку результата */

	return "";
}

string TCtrl::executeClipboardCmd(int cmdNumber, string *clipboadBuffer)
{
	/* управляет вызовом методов объекта типа TClipBoard, обеспечивающих выполнение команд буфера обмена,
	операция получает целое число (номер команды пользователя), строку со значением буфера обмена и возвращает
	строку со значением буфера обмена и строку результата */

	return "";
}

TCtrlState TCtrl::getCtrlState()
{
	return this->ctrlState;
}

void TCtrl::setCtrlState(TCtrlState state)
{
	this->ctrlState = state;
}