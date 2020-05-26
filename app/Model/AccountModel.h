#ifndef ACCOUNTMODEL_H_INCLUDED
#define ACCOUNTMODEL_H_INCLUDED

#include "ModelInterface.h"
#include <sstream>
#include <algorithm>

using namespace std;

/*
<Remember to lowercase before setting>
The csv file for this model has the following order:
0. Record ID (1,2,3,...)
1. Username (19125064, htthanh)
2. Password (****** - hashed)
3. Role (student/lecturer/staff)
*/
class AccountModel : public ModelInterface
{
private:

    string id;
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
        this->username = toLowerCase(username);
    }

    void setPassword(string password) {
        this->password = toLowerCase(password);
    }

    void setRole(string role) {
        this->role = toLowerCase(role);
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
        this->id = "all";
        this->username = "all";
        this->password = "all";
        this->role = "all";
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

    /*Before adding, please provide all necessary information for the model using the 'set' functions.
    Except that the 'id' of the model (the incrementing id) is not needed.*/
    void registerUser() {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("username")] = this->username;
        if ((this->fetch(&conditions)).size() != 0) return;
        vector<string> account;
        account.push_back(this->id);
        account.push_back(this->username);
        account.push_back(SHF(this->password));
        account.push_back(this->role);
        this->add(&account);
    }

    bool checkMatchPassword(string password) {
        if (SHF(password) == this->password) return true;
        return false;
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

    /*Before fetching, please ensure that all parameters that are required as conditions are set in model using 'set' functions
    Example: if you want to fetch records with id 69, please set it using Model->setId(69) before fetching.*/
    vector<vector<string>> fetchAccount() {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("username")] = this->username;
        conditions[this->getIndex("password")] = this->password;
        conditions[this->getIndex("role")] = this->role;
        return fetch(&conditions);
    }

    /*The 'toDelete' vector is the conditions of the records you want to delete.
    In case you want to delete the current record already set in the model, please provide 'nullptr' as the 'toDelete' parameter.*/
    void removeAccount(vector<string>* toDelete = nullptr) {
        if (toDelete == nullptr) {
            toDelete = new vector<string>((this->columns).size(), "all");
            (*toDelete)[this->getIndex("username")] = this->username;
        }
        this->erase(toDelete);
    }
};

#endif // ACCOUNTMODEL_H_INCLUDED
