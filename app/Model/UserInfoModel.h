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
        info.push_back(this->studentID);
        info.push_back(this->firstName);
        info.push_back(this->lastName);
        info.push_back(this->dob);
        info.push_back(this->userGender);
        this->add(&info);
        if (this->studentID != "") return this->studentID + this->dob;
        else return this->firstName + this->lastName;
    }

    bool CheckProfile(string username) {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex(getName(username))] = username;
        vector<vector<string>> result = this->fetch(&conditions);
        if (result.size() != 0) {
            this->studentID = result[0][1];
            this->firstName = result[0][2];
            this->lastName = result[0][3];
            this->dob = result[0][4];
            this->userGender = result[0][5];
            return true;
        }
        else {
            return false;
        }
    }
    
};

#endif // USERINFOMODEL_H_INCLUDED
