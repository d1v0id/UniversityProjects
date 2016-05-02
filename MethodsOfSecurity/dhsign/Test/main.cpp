// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DiffieHellman.h"

void PrintBuffer(const vector<char>& buffer)
{
    for (size_t i = 0; i < buffer.size(); ++i) {
        cout << "0x" << setbase(16) << setw(2) << setfill('0') << (int)(unsigned char)buffer[i] << " ";
        if ((i + 1) % 8 == 0) {
            cout << endl;
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
    cout << "�������� �����-��������:" << endl;
	const size_t PModuleLength = 32;

	// P (The bytes representation of number 0x24357685944363427687549776543601)
	unsigned char buffer[PModuleLength] = {
		0xEE, 0x38, 0x6B, 0xFB, 
        0x5A, 0x89, 0x9F, 0xA5, 
        0xAE, 0x9F, 0x24, 0x11, 
        0x7C, 0x4B, 0x1F, 0xE6,
        0x49, 0x28, 0x66, 0x51, 
        0xEC, 0xE6, 0x53, 0x81, 
        0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xFF, 0xFF, 0xFF
    };
    vector<char> cryptoPModule((char*)buffer, (char*)buffer + PModuleLength);
	
	// G
    unsigned long cryptoGModule = 0x02;

	DiffieHellmanLib::DiffieHellman<PModuleLength> aliceExchanger(cryptoPModule, cryptoGModule);
	DiffieHellmanLib::DiffieHellman<PModuleLength> bobExchanger(cryptoPModule, cryptoGModule);

    cout << endl << "��������� �������� ����� � �����..." << endl;
    vector<char> aliceExchangeKey;
	aliceExchanger.GenerateExchangeData(aliceExchangeKey);
    cout << "������� ���� � �����:\n";
    PrintBuffer(aliceExchangeKey);

    cout << endl << "��������� �������� ����� � ����..." << endl;
	vector<char> bobExchangeKey;
	bobExchanger.GenerateExchangeData(bobExchangeKey);
    cout << "������� ���� � ����:" << endl;
    PrintBuffer(bobExchangeKey);

    cout << endl << "���������� ���������� ����� � �����..." << endl;
	vector<char> aliceSharedKey;
	aliceExchanger.CompleteExchangeData(bobExchangeKey, aliceSharedKey);
    cout << "��������� ���� � �����:" << endl;
    PrintBuffer(aliceSharedKey);

    cout << endl << "���������� ���������� ����� � ����..." << endl;
	vector<char> bobSharedKey;
	bobExchanger.CompleteExchangeData(aliceExchangeKey, bobSharedKey);
    cout << "��������� ���� � ����:" << endl;
    PrintBuffer(bobSharedKey);

    if (aliceSharedKey == bobSharedKey) {
        cout << endl << "�������� ��������� �������: ����� �������." << endl;
    }
    else {
        cout << endl << "������: ����� �� �������." << endl;
    }

	return 0;
}
