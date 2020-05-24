#ifndef MISCELLANOUSFUNCTIONS_H_INCLUDED
#define MISCELLANOUSFUNCTIONS_H_INCLUDED

#include <iostream>
#include <string.h>

using namespace std;

string comaFilter(string& str)
{
	while (true)
	{
		int t = str.find(",");
		if (t == -1) return str;
		str.erase(t, 1);
		continue;
	}
}

string toLowerCase(string s) {
	while (true)
	{
		int t = s.find(",");
		if (t == -1) return s;
		s.erase(t, 1);
		continue;
	}

    for (int i = 0; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}

string capitalize(string str) {
    int check = 0, i = 0;
    while (str[i]) {
        if (check == 0) {
            str[i] = toupper(str[i]);
            check = 1;
        }
        else if (isspace(str[i]))
            check = 0;
        i++;
    }
    return str;
}


#endif