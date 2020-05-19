#ifndef USERINFOMODEL_H_INCLUDED
#define USERINFOMODEL_H_INCLUDED

#include "ModelInterface.h"
#include <algorithm>

using namespace std;

class UserInfoModel : public ModelInterface
{
private:

    string studentID; // if the user is a student
    string lastName;
    string firstName;
    string userGender;
    string dob;
    string username;

public:

    void setStudentID(string studentID) {
        this->studentID = studentID;
    }

    void setLastName(string lastName) {
        this->lastName = lastName;
    }

    void setFirstName(string firstName) {
        this->firstName = firstName;
    }

    void setUserGender(string userGender) {
        this->userGender = userGender;
    }

    void setDOB(string dob) {
        this->dob = dob;
    }

    void setUsername(string username) {
        this->username = username;
    }

    string getStudentID() {
        return this->studentID;
    }

    string getLastName() {
        return this->lastName;
    }

    string getFirstName() {
        return this->firstName;
    }

    string getDOB() {
        return this->dob;
    }

    string getUsername() {
        return this->username;
    }

    string getUserGender() {
        return this->userGender;
    }

    /**
    constructor, call to parent's constructor, the string inside is the path to its database
    */
    UserInfoModel() : ModelInterface("database/UserInfo.csv") {

    }

    /**
    check if both username and password are both existed in database
    */
    string AddUser() {
        vector<string> info;
        info.push_back("2");
        info.push_back(this->studentID);
        info.push_back(this->firstName);
        info.push_back(this->lastName);
        info.push_back(this->dob);
        info.push_back(this->userGender);     
        if (this->studentID != "") this->username = this->studentID + this->dob;
        else this->username = this->firstName + this->lastName;
        info.push_back(this->username);
        this->add(&info);
        return this->username;
    }

    bool CheckProfile(string username) {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("username")] = username;
        vector<vector<string>> result = this->fetch(&conditions);
        if (result.size() != 0) {
            this->studentID = result[0][1];
            this->firstName = result[0][2];
            this->lastName = result[0][3];
            this->dob = result[0][4];
            this->userGender = result[0][5];
            this->username = result[0][6];
            return true;
        }
        else {
            return false;
        }
    }
    
};

#endif // USERINFOMODEL_H_INCLUDED
