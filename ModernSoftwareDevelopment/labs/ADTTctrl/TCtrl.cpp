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
	/* ��������� ������� �������� �� ������ � ���������: �������� (���� TEditor), ��������� (���� TProc), ������ (���� TMemory),
	����� ������ (���������� ������ ClipBoard), �������� �������� ����� ����� (����� ������� ������������), ������ ��� ������ ������,
	������ �� ��������� ��������� ������ � ���������� ������ ��� ������ ������, ������ ��������� ������ � ������ ���������� */

	return "";
}

string TCtrl::executeEditorCmd(int cmdNumber)
{
	/* ��������� ������� ������� ������� �������� (��� TEditor),
	�������� �������� ����� ����� (����� ������� ������������ � ���������� ������ ���������� */
	
	return "";
}

string TCtrl::executeOperation(int cmdNumber)
{
	/* ��������� ������� ������� ������� ��������� (���� TProc),
	�������� �������� ����� ����� (����� ������� ������������ � ���������� ������ ���������� */

	return "";
}

string TCtrl::executeFunction(int cmdNumber)
{
	/* ��������� ������� ������� ������� ��������� (���� TProc),
	�������� �������� ����� ����� (����� ������� ������������ � ���������� ������ ���������� */

	return "";
}

string TCtrl::calculateExpression(int cmdNumber)
{
	/* ��������� ������� ������� ������� ��������� (���� TProc),
	�������� �������� ����� ����� (����� ������� ������������ � ���������� ������ ���������� */

	return "";
}

string TCtrl::setInitialCalcState(int cmdNumber)
{
	/* ��������� ������� ������� ��� �������� ������� ���� TCalc � ��������� Start,
	�������� �������� ����� ����� (����� ������� ������������ � ���������� ������ ���������� */

	return "";
}

string TCtrl::executeMemoryCmd(int cmdNumber, string *memoryState)
{
	/* ��������� ������� ������� ������� ���� TCtrl, �������������� ���������� ������ ������,
	�������� �������� ����� ����� (����� ������� ������������), ������ �� ��������� ���������
	������ � ���������� ������ ��������� ������ � ������ ���������� */

	return "";
}

string TCtrl::executeClipboardCmd(int cmdNumber, string *clipboadBuffer)
{
	/* ��������� ������� ������� ������� ���� TClipBoard, �������������� ���������� ������ ������ ������,
	�������� �������� ����� ����� (����� ������� ������������), ������ �� ��������� ������ ������ � ����������
	������ �� ��������� ������ ������ � ������ ���������� */

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