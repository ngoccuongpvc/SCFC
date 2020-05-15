#ifndef ACCOUNTMODEL_H_INCLUDED
#define ACCOUNTMODEL_H_INCLUDED

#include "ModelInterface.h"
#include <sstream>
#include <algorithm>

using namespace std;

class AccountModel : public ModelInterface
{
private:

	string SHF(string input) //SHF = simple hash function
	{
		unsigned int magic = 5674356;
		unsigned int hash = 1234564352;
		for (int i = 0; i < input.length(); i++)
		{
			hash = hash ^ (input[i]);
			hash = hash * magic;
		}
		return toHex(hash);
	}

	string toHex(unsigned int input)
	{
		string hexHash;
		stringstream hexstream;
		hexstream << hex << input;
		hexHash = hexstream.str();
		std::transform(hexHash.begin(), hexHash.end(), hexHash.begin(), ::toupper);
		return hexHash;
	}

public:

    /**
    constructor, call to parent's constructor, the string inside is the path to its database
    */
    AccountModel() : ModelInterface("database/Account.csv") {

    }

    /**
    check if both username and password are both existed in database
    */
    bool checkCredential(string username, string password) {
        vector<string> conditions (this->columns.size(), "all");
        conditions[this->getIndex(getName(username))] = username;
        conditions[this->getIndex(getName(password))] = SHF(password); //hashing password

        if ((this->fetch(&conditions)).size() != 0) {
            return true;
        } else {
            return false;
        }
    }

    string getUserRole(string username) {
        try {
            vector<string> conditions (this->columns.size(), "all");
            conditions[this->getIndex("username")] = username;
            vector<string> record = fetch(&conditions)[0];
            return record[this->getIndex("role")];
        } catch (exception e) {
            cout << "An exception has occurred" << endl;
            return "";
        }
    }
};

#endif // ACCOUNTMODEL_H_INCLUDED
