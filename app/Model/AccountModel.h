#ifndef ACCOUNTMODEL_H_INCLUDED
#define ACCOUNTMODEL_H_INCLUDED

#include "ModelInterface.h"
#include <sstream>
#include <algorithm>

using namespace std;

class AccountModel : public ModelInterface
{
private:

    int id;
    string username;
    string password;
    string role;

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

    void setUserName(string username) {
        this->username = username;
    }

    void setPassword(string password) {
        this->password = password;
    }

    void setRole(string role) {
        this->role = role;
    }

    string getUserName() {
        return this->username;
    }

    string getPassword() {
        return this->password;
    }

    string getRole() {
        return this->role;
    }

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

    bool registerUser() {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("username")] = this->username;
        if ((this->fetch(&conditions)).size() != 0) return false;
        vector<string> account;
        account.push_back("0");
        account.push_back(this->username);
        account.push_back(SHF(this->password));
        account.push_back(this->role);
        this->add(&account);
        return true;
    }

    bool checkMatchPassword(string password) {
        if (SHF(password) == this->password) return true;
        return false;
    }

    bool fetchAccount(string username) {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("username")] = username;
        vector<string> record = fetch(&conditions)[0];
        this->id = stoi(record[0]);
        this->username = record[1];
        this->password = record[2];
        this->role = record[3];
        return true;
    }

	bool changePassword(string username, string newPass)
	{
		try {
			vector<string> conditions(this->columns.size(), "all");
			conditions[this->getIndex("username")] = username;
			vector<string> record = fetch(&conditions)[0];
			record[this->getIndex("password")] = SHF(newPass);
			this->update(&conditions, &record);
			return true;
		}
		catch (exception e) {
			cout << "An exception has occured" << endl;
			return false;
		}
		
	}
};

#endif // ACCOUNTMODEL_H_INCLUDED
