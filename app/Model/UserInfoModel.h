#ifndef USERINFOMODEL_H_INCLUDED
#define USERINFOMODEL_H_INCLUDED

#include "ModelInterface.h"
#include <algorithm>

using namespace std;

/*
<Remember to lowercase before setting>
The csv file for this model has the following order:
0. Record ID (1,2,3,...)
1. Student ID (19125001...)
2. First name (john)
3. Last name (cena)
4. Gender (male, female)
5. Date of Birth (01-01-2001)
6. Username (johncena)
*/
class UserInfoModel : public ModelInterface
{
private:

    string id; // the incrementing id
    string studentID; // if the user is a student
    string lastName;
    string firstName;
    string userGender;
    string dob;
    string username;

public:

    void setId(string id) {
        this->id = toLowerCase(id);
    }

    void setStudentId(string studentID) {
        this->studentID = toLowerCase(studentID);
    }

    void setLastName(string lastName) {
        this->lastName = toLowerCase(lastName);
    }

    void setFirstName(string firstName) {
        this->firstName = toLowerCase(firstName);
    }

    void setUserGender(string userGender) {
        this->userGender = toLowerCase(userGender);
    }

    void setDOB(string dob) {
        this->dob = toLowerCase(dob);
    }

    void setUsername(string username) {
        this->username = toLowerCase(username);
    }

    string getId() {
        return this->id;
    }

    string getStudentId() {
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

    UserInfoModel() : ModelInterface("database/UserInfo.csv") {
        this->id = "all";
        this->studentID = "all"; // if the user is a student
        this->lastName = "all";
        this->firstName = "all";
        this->userGender = "all";
        this->dob = "all";
        this->username = "all";
    }

    /*Before adding, please provide all necessary information for the model using the 'set' functions.
    Except that the 'id' of the model (the incrementing id) is not needed.*/
    void AddUser() {
        vector<string> *info = getUserInfo();
        this->add(info);
    }

    /*Before fetching, please ensure that all parameters that are required as conditions are set in model using 'set' functions
    Example: if you want to fetch records with id 69, please set it using Model->setId(69) before fetching.*/
    vector<vector<string>> FetchInfo() {
        vector<string> conditions(this->columns.size(), "all");
        conditions[this->getIndex("studentId")] = this->studentID;
        conditions[this->getIndex("firstName")] = this->firstName;
        conditions[this->getIndex("lastName")] = this->lastName;
        conditions[this->getIndex("dob")] = this->dob;
        conditions[this->getIndex("username")] = this->username;
        conditions[this->getIndex("userGender")] = this->userGender;
        return this->fetch(&conditions);
    }

    /*Set the values in the model using a vector. 
    Please provide all required fields for this model in order, including a blank at the start for an ID.*/
    void setUserInfo(vector<string>* info) {
        if (info->size() != this->columns.size()) return;
        this->studentID = (*info)[1];
        this->firstName = (*info)[2];
        this->lastName = (*info)[3];
        this->dob = (*info)[4];
        this->userGender = (*info)[5];
        this->username = (*info)[6];
    }

    /*Get the values in the model and return as a vector.
    Please provide all required fields for this model in order, including a blank at the start for an ID.*/
    vector<string>* getUserInfo() {
        vector<string>* info = new vector<string>();
        info->push_back(this->id);
        info->push_back(this->studentID);
        info->push_back(this->firstName);
        info->push_back(this->lastName);
        info->push_back(this->dob);
        info->push_back(this->userGender);
        info->push_back(this->username);
        return info;
    }

    /*Please provide 2 vectors for updating. The 'conditions' vector is the conditions of the records you want to change.
    The 'toUpdate' vector contains the fields (in the correct order) you want to update in those records. The remaining fields that you don't want to change may be left empty or same as the original record.
    In case you want to update the current record already set in the model, please provide 'nullptr' in 'conditions' field. Please do not leave the 'toUupdate' field blank.*/
    void UpdateInfo(vector<string>* conditions = nullptr, vector<string> *toUpdate = nullptr) {
        if (toUpdate == nullptr) return;
        if (conditions == nullptr) conditions = getUserInfo();
        this->update(conditions, toUpdate);
    }

    /*The 'toDelete' vector is the conditions of the records you want to delete.
    In case you want to delete the current record already set in the model, please provide 'nullptr' as the 'conditions' parameter.*/
    void RemoveUser(vector<string> *conditions = nullptr) {
        if (conditions == nullptr) conditions = getUserInfo();
        this->erase(conditions);
    }

    void findStudentInfo(string studentID) {
        vector<string>* conditions = new vector<string>((this->columns).size(), "all");
        (*conditions)[this->getIndex("studentid")] = studentID;
        vector<vector<string>> res = this->fetch(conditions);
        if (res.size() != 0) {
            this->setStudentId(res[0][this->getIndex("studentId")]);
            this->setFirstName(res[0][this->getIndex("firstName")]);
            this->setLastName(res[0][this->getIndex("lastName")]);
            this->setUserGender(res[0][this->getIndex("userGender")]);
            this->setDOB(res[0][this->getIndex("dob")]);
        }
    }
    
    void saveUser(vector<string>* user = nullptr) {
        if (user == nullptr) {
            user = this->getUserInfo();
        }
        this->add(user);
    }
};

#endif // USERINFOMODEL_H_INCLUDED
