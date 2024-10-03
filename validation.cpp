#include"validation.h"
#include<iostream>
#include<cmath>

using namespace std;


// returns true if id entered is valid
bool Validation::validateId(int id) {
	int numberDigits = floor(log10(id) + 1);
	if (id < 1 || numberDigits != 8) {
		return false;
	}
	else {
		return true;
	}
}

// returns true if entered name is valid
bool Validation::validateName(string name) {
	for (int i = 0; i < name.length(); i++) {
		char c = char(name[i]);
		if (!(64 < int(c) < 91) || !(96 < int(c) < 123)) {
			return false;
		}
	}
	return true;
}