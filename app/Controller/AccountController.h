#ifndef ACCOUNTCONTROLLER_H_INCLUDED
#define ACCOUNTCONTROLLER_H_INCLUDED

#include "AuthorizeController.h"
#include "MiscellanousFunctions.h"

#include <iostream>
#include <string.h>
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"
#include "Validation.h"

//using namespace std;

class AccountController : public ControllerInterface
{
private:
	Validation* valid = new Validation();

public:

    void seeProfile() {
        UserInfoModel* user = new UserInfoModel();
        user->setUsername(globalUsername);
        myVector<myVector<string>> records = user->FetchInfo();
        if (records.size() == 0) {
            cout << "Something wrong with your account, cannot fetch your profile.";
            delete user;
            return;
        }
        cout << "Student ID: " << records[0][1] << endl;
        cout << "First name: " << records[0][2] << endl;
        cout << "Last name: " << records[0][3] << endl;
        cout << "Date of Birth: " << records[0][4] << endl;
        cout << "Gender: " << records[0][5] << endl;
        delete user;
    }

    void createLecturer() {
        UserInfoModel* uim = new UserInfoModel();
        AccountModel* am = new AccountModel();
        string temp;
        uim->setStudentId("");
		cout << "Lecturer first name: "; valid->read(temp, "all");   uim->setFirstName(temp);
		cout << "Lecturer last name: ";  valid->read(temp, "all");   uim->setLastName(temp);
        cout << "Lecturer DOB: ";        valid->read(temp, "date");  uim->setDOB(temp);
		cout << "Lecturer gender: ";     valid->read(temp, "gender");uim->setUserGender(temp);
        cout << "Lecturer username: ";   valid->read(temp, "nospc"); uim->setUsername(temp);
        am->setUserName(temp);
        am->setPassword(uim->getDOB());
        am->setRole("lecturer");
        uim->AddUser();
        am->registerUser();
        cout << "Successfully created the lecturer." << endl;
        delete uim;
        delete am;
    }

    void viewAllLecturer() {
        UserInfoModel* uim = new UserInfoModel();
        AccountModel* am = new AccountModel();
        am->setRole("lecturer");
        myVector<myVector<string>> results = am->fetchAccount();
        if (results.size() == 0) {
            cout << "No lecturer was found!" << endl;
            delete uim;
            delete am;
            return;
        }
        myVector<myVector<string>> lecturers;
        for (int i = 0; i < results.size(); ++i) {
            uim->setUsername(results[i][1]);
            myVector<myVector<string>> getBack = uim->FetchInfo();
            if (getBack.size() != 0) {
                lecturers.push_back(getBack[0]);
            }
        }
        myVector<string> header = uim->columns;
        for (int i = 0; i < header.size(); ++i) {
            header[i] = capitalize(header[i]);
        }
        View* view = new View(lecturers, header);
        view->displayTable();

        delete uim;
        delete am;
        delete view;
    }

    void editLecturer() {
        UserInfoModel* uim = new UserInfoModel();
        cout << "Please enter the username of the lecturer that you want to edit: ";
		string username; valid->read(username, "nospc");;
        uim->setUsername(username);

        myVector<myVector<string>> results = uim->FetchInfo();
        if (results.size() == 0) {
            cout << "The lecturer account you entered does not exist. Please retry." << endl;
            delete uim;
            return;
        }
        myVector<string> record = results[0];
        cout << "Please enter the information that you want to change about this course. Press enter if you don't want to change that info.." << endl;
        string temp;
        myVector<string> toUpdate;
        toUpdate.push_back(record[0]);
        toUpdate.push_back("");
		cout << "First name: ";    valid->read(temp, "all");    toUpdate.push_back(temp);
		cout << "Last name: ";     valid->read(temp, "all");    toUpdate.push_back(temp);
		cout << "Date of birth: "; valid->read(temp, "date");   toUpdate.push_back(temp);
		cout << "User gender: ";   valid->read(temp, "gender"); toUpdate.push_back(temp);
		cout << "New username: ";  valid->read(temp, "nospc");  toUpdate.push_back(temp);
        uim->UpdateInfo(&record, &toUpdate);
        cout << "Successfully edited the lecturer." << endl;
        delete uim;
    }

    void deleteLecturer() {
        UserInfoModel* uim = new UserInfoModel();
        AccountModel* am = new AccountModel();
        string lecturer;
        cout << "Enter the account of the lecturer that you want to remove: ";
		valid->read(lecturer, "nospc");
        uim->setUsername(lecturer);
        am->setUserName(lecturer);
        am->setRole("lecturer");
        myVector<myVector<string>> accountResult = am->fetchAccount();
        myVector<myVector<string>> userResult = uim->FetchInfo();
        if (accountResult.size() == 0 || userResult.size() == 0) {
            cout << "The account you entered may not exist, please recheck." << endl;
            delete uim;
            delete am;
            return;
        }
        for (int i = 0; i < accountResult.size(); ++i) {
            am->removeAccount(&accountResult[i]);
        }
        for (int i = 0; i < userResult.size(); ++i) {
            uim->RemoveUser(&userResult[i]);
        }
        cout << "Successfully deleted the lecturer." << endl;
        delete uim;
        delete am;
    }

    AccountController() {
        this->mapMethods["createLecturer"] = [this]() { createLecturer(); };
        this->mapMethods["deleteLecturer"] = [this]() { deleteLecturer(); };
        this->mapMethods["editLecturer"] = [this]() { editLecturer(); };
        this->mapMethods["seeProfile"] = [this]() { seeProfile(); };
        this->mapMethods["viewAllLecturer"] = [this]() { viewAllLecturer(); };
    }

	~AccountController()
	{
		delete valid;
	}

    
};

#endif // USERCONTROLLER_H_INCLUDED
