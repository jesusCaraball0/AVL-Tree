#pragma once
#include<iostream>

using namespace std;

class Validation {
public:
	// validates an inputter id
	bool validateId(int id);

	// validates and inputted name
	bool validateName(string name);
};