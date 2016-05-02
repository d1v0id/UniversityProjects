#ifndef RANDOMNUMBER_H_
#define RANDOMNUMBER_H_

#include <cstdlib>

using namespace std;

class RandomNumbers {
public:
	static int RandomNumbers::getRandomNumber(int start, int end) {
		return rand() % (end - start) + start;
	}
};

#endif /* RANDOMNUMBER_H_ */