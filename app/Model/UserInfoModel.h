#ifndef USERINFOMODEL_H_INCLUDED
#define USERINFOMODEL_H_INCLUDED

#include "ModelInterface.h"
#include <algorithm>

using namespace std;

class UserInfoModel : public ModelInterface
{
private:

    string id;
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
        this->id = "all";
        this->studentID = "all"; // if the user is a student
        this->lastName = "all";
        this->firstName = "all";
        this->userGender = "all";
        this->dob = "all";
        this->username = "all";
    }

    /**
    check if both username and password are both existed in database
    */
    void AddUser() {
        vector<string> info;
        info.push_back(this->id);
        info.push_back(this->studentID);
        info.push_back(this->firstName);
        info.push_back(this->lastName);
        info.push_back(this->dob);
        info.push_back(this->userGender);     
        info.push_back(this->username);
        this->add(&info);
    }

    vector<vector<string>> FetchInfo() {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("id")] = this->id;
        conditions[this->getIndex("studentId")] = this->studentID;
        conditions[this->getIndex("firstName")] = this->firstName;
        conditions[this->getIndex("lastName")] = this->lastName;
        conditions[this->getIndex("dob")] = this->dob;
        conditions[this->getIndex("username")] = this->username;
        conditions[this->getIndex("userGender")] = this->userGender;
        return this->fetch(&conditions);
    }

    vector<string> UpdateInfo(vector<string> toUpdate) {
        vector<vector<string>> records = this->FetchInfo();
        if (records.size() == 0) return;
        vector<string> conditions = records[0];
        this->update(&conditions, &toUpdate);
    }
    
};

#endif // USERINFOMODEL_H_INCLUDED
