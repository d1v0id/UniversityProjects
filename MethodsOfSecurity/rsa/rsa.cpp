// rsa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rsa.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	Rsa rsa;

	string message = "Hello RSA!";
	cout << "Исходное сообщение: " << endl << message << endl << endl;

	cout << "Зашифрованное сообщение: " << endl;
	vector<int> cryptMsg;
	for (int letter : message) {
		Rsa::crypt(rsa.getPrivateKey(), rsa.getModulus(), &letter);
		cryptMsg.push_back(letter);
		cout << letter << endl;
	}
	cout << endl;

	message = "";
	cout << "Расшифрованное сообщение: " << endl;
	for (int letter : cryptMsg) {
		Rsa::crypt(rsa.getPublicKey(), rsa.getModulus(), &letter);
		message.push_back(letter);
	}
	cout << message << endl;

	return 0;
}

