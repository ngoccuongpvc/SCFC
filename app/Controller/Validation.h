#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <regex>
#include "MiscellanousFunctions.h"


using namespace std;

class Validation {
protected:

	map<string, regex> regList;

public:

	/*
	INSTRUCTION
	- To use validation, new it and use read(var, "kind-of-validation").
	- kind-of-validation was specified in the constructor below.
	- Don't new it too much as it's unneccessary, considering about allocating it 
	in the constructor of each Controller.
	*/

	void read(string &variable, string varName)
	{
		while (true)
		{
			getline(cin, variable);

			if (!regex_match(variable, regList["all"]))
			{
				cout << "Our program does not accept comma! Please try again." << endl;
				continue;
			}
			else if (!regex_match(variable, regList[varName]))
			{
				cout << "Invalid input or input does not match the required format! Please try again." << endl;
				continue;
			}
			variable = toLowerCase(variable);
			break;
		}
	}

	Validation()
	{
		//map variable's name to its regular expression
		regList["all"] = regex("[^\,]+");
		regList["nospc"] = regex("[^\\s]+"); //No space

		//TIME FORMAT
		regList["date"] = regex("[0-4]{4}\/[0-1][0-2]\/[0-3][0-9]"); // yyyy/mm/dd
		regList["hour"] = regex("[0-2][0-9]:[0-6][0-9]");
		regList["year"] = regex("20\\d\\d-20\\d\\d");

		regList["day"] = regex("^([1-9]?|10)$");
		regList["score"] = regex("\\d+");

		regList["gender"] = regex("male|female");
		regList["term"] = regex("midterm|final|bonus|lab");
		regList["sem"] = regex("spring|summer|fall|winter");
		regList["role"] = regex("student|staff|lecturer");
		regList["dow"] = regex("mon|tue|wed|thu|fri|sat|sun"); //day of week
	}

};

#endif // VALIDATION_H_INCLUDED
