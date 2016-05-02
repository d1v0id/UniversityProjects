#ifndef RSA_H_
#define RSA_H_

#include "PrimeNumbers.h"
#include "RandomNumbers.h"

using namespace std;

class Rsa {
public:
	Rsa() {
		int p = 0;
		int q = 0;
		int n = 0;
		int phi = 0;
		int e = 0;
		int d = 0;

		PrimeNumbers primeNumbers = PrimeNumbers(1, 90);
		p = primeNumbers.getRandomPrimeNumber();
		q = primeNumbers.getRandomPrimeNumber();
		n = p * q;
		phi = (p - 1) * (q - 1);

		e = RandomNumbers::getRandomNumber(2, (phi - 1));
		while (getGreatestCommonDenominator(e, phi) != 1) {
			e = RandomNumbers::getRandomNumber(2, (phi - 1));
		}

		d = solveModularLinearEquation(e, phi);

		this->privateKey = e;
		this->publicKey = d;
		this->modulus = n;
	}

	int getPublicKey() {
		return this->publicKey;
	}

	int getPrivateKey() {
		return this->privateKey;
	}

	int getModulus() {
		return this->modulus;
	}

	static void crypt(int key, int modulus, int *message) {
		long long codedMsg = 1;
		for (long i = 0; i < key; i++) {
			codedMsg = codedMsg * (*message) % modulus;
		}
		codedMsg = codedMsg % modulus;

		(*message) = codedMsg;
	}

private:
	int publicKey;
	int privateKey;
	int modulus;

	int getGreatestCommonDenominator(int a, int b) {
		return (a < b) ? getGreatestCommonDenominator(b, a) : ((a % b == 0) ? b : getGreatestCommonDenominator(b, a % b));
	}

	int gcd(int a, int b) {

	}

	int solveModularLinearEquation(int e, int phi) {
		int s;
		int d = 0;

		do {
			s = (d * e) % phi;
			d++;
		} while (s != 1);
		d = d - 1;

		return d;
	}
};

#endif /* RSA_H_ */