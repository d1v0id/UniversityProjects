#ifndef PRIMENUMBERS_H_
#define PRIMENUMBERS_H_

#include <vector>
#include <algorithm>

using namespace std;

class PrimeNumbers {
public:
	PrimeNumbers(int min, int max) {
		this->generatePrimeNumbers(min, max);

		this->min = min;
		this->max = max;
	}

	int getRandomPrimeNumber() {
		int number = 0;
		while (true) {
			number = rand() % (this->max - this->min) + this->min;
			if (find(primes.begin(), primes.end(), number) != primes.end()) {
				break;
			}
		}
		return number;
	}

private:
	int min;
	int max;
	vector<int> primes;

	void generatePrimeNumbers(int min, int max) {
		primes.push_back(2);

		for (int i = 3; i < max; i++) {
			bool prime = true;
			for (unsigned int j = 0; j < primes.size() && primes[j] * primes[j] <= i; j++) {
				if (i % primes[j] == 0) {
					prime = false;
					break;
				}
			}

			if (prime && i >= min) {
				primes.push_back(i);
			}
		}

		if (primes.front() < min) {
			primes.erase(primes.begin());
		}
	}
};

#endif /* PRIMENUMBERS_H_ */
