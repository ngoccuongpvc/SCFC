#ifndef USERCONTROLLER_H_INCLUDED
#define USERCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"

using namespace std;

string role;
bool logged_in = false;
string currentSession = "";

string globalUsername = "null";

class UserController : public ControllerInterface
{
private:

    void mainAction() {
        extern stack<string> history;
        string nextMethod;
        if (role == "student") {
            history.push("student-dashboard");
        }
        else if (role == "teacher") {
            history.push("teacher-dashboard");
        }
        else if (role == "staff") {
            history.push("staff-dashboard");
        }
        else {
            history.push("login");
        }
    }


    bool checkLoginStatus() {
        if (!logged_in || currentSession == "") {
            cout << "You are not logged in." << endl;
            return false;
        }
        else return true;
    }

    void createSession(string username) {
        if (checkLoginStatus()) return;
        currentSession = username;
        logged_in = true;
    }

    void resetSession() {
        currentSession = "";
        logged_in = false;
    }

    void loginAction() {
        string username, password;
        cout << "User name: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        AccountModel *model = new AccountModel();

        if (model->checkCredential(username, password)) {
            cout << "Login successful" << endl;
            cout << "You are login as: " << model->getUserRole(username) << endl;
            role = model->getUserRole(username);
            extern stack<string> history;
            history.push("dashboard");
            createSession(username);
        } else {
            cout << "Wrong username or password" << endl;
            cout << "Wrong username or password!! Wanna try again (0:false, 1: true): ";
				  bool tryAgain = false;
				  cin >> tryAgain;
				  if (!tryAgain) break;
        }

    }

    string toLowerCase(string s) {
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {return tolower(c); });
        return s;
    }

    void registerAction() {
        //if (checkLoginStatus()) return;
        
        bool validAccount = false;
        UserInfoModel* user = new UserInfoModel();
        AccountModel* am = new AccountModel();
        extern stack<string> history;
        while (!validAccount) {
            string firstName, lastName, dob, gender, role, username, password, studentID;
            cout << "Welcome to the register screen" << endl;
            cout << "First name: "; cin >> firstName; user->setFirstName(firstName);
            cout << "Last name: "; cin >> lastName; user->setLastName(lastName);
            cout << "Date of Birth: "; cin >> dob; user->setDOB(dob);
            cout << "Gender: "; cin >> gender; user->setUserGender(gender);
            cout << "Role (student/ staff/ lecturer): "; cin >> role;
            if (toLowerCase(role) == "student") {
                cout << "Student ID: "; cin >> studentID; user->setStudentID(studentID);
            }
            else user->setStudentID("");
            cout << "Password: "; cin >> password;
            username = user->AddUser();
            am->setPassword(password);
            am->setUserName(username);
            validAccount = am->registerUser();
        }
        createSession(am->getUserName());
        history.push("dashboard");
        delete user;
        delete am;
    }

    void logoutAction() {
        if (!checkLoginStatus()) return;
        extern stack<string> history;
        resetSession();
        history.push("login");
    }
    

    void seeProfile() {
        if (!checkLoginStatus()) return;
        UserInfoModel* user = new UserInfoModel();
        if (user->CheckProfile(currentSession)) {
            cout << "Student ID: " << user->getStudentID();
            cout << "First name: " << user->getFirstName();
            cout << "Full name: " << user->getLastName();
            cout << "Date of Birth: " << user->getDOB();
            cout << "Gender: " << user->getUserGender();
        }
        else {
            cout << "Something wrong with your account, cannot fetch your profile.";
            return;
        }
        delete user;
    }
  /*
    void changePasswordAction() {
        if (!checkLoginStatus()) return;
        AccountModel* am = new AccountModel();
        am->fetchAccount(currentSession);
        string oldPassword, newPassword;
        cout << "Please enter your old password: "; cin >> oldPassword;
        if (!am->checkMatchPassword(oldPassword)) {
            cout << "Wrong password." << endl;
            return;
        }

        cout << "Enter your new password: "; cin >> newPassword;
        am->changePassword(newPassword);
    }
    
   */

    void accessDashboard() {
        cout << "Hello User!" << endl;
        extern stack<string> history;
        history.push("access");
    }

    void studentDashboard() {
        cout << "Hello Student!" << endl;
    }
    
    void teacherDashboard() {
        cout << "Hello Teacher!" << endl;
    }
    
    void staffDashboard() {
        cout << "Hello Staff!" << endl;
    }

    void changePasswordAction() {
        cout << "Change password here!";
		if (globalUsername == "null")
		{
			cout << "Login 1st!!" << endl;
		}
		else
		{
			string newPass;
			cout << "Pls enter new password: ";
			cin >> newPass;

			AccountModel* model = new AccountModel();

			if(model->changePassword(globalUsername, newPass))
			{ 
				cout << "Successfully change password!" << endl;
				extern stack<string> history;
				history.push("dashboard");
			}
			else 
			{
				cout << "Can't change password" << endl;
			}

			//delete model;
		}
    }

public:

    /**
    Constructor of Controller, which map a string to a function
    */
    UserController() {
        this->mapMethods["mainAction"] = [this]() { mainAction(); };
        this->mapMethods["loginAction"] = [this]() { loginAction(); };
        this->mapMethods["studentDashboard"] = [this]() { studentDashboard(); };
        this->mapMethods["teacherDashboard"] = [this]() { teacherDashboard(); };
        this->mapMethods["staffDashboard"] = [this]() { staffDashboard(); };
		this->mapMethods["changePassword"] = [this](){ changePasswordAction(); };

        this->mapMethods["registerAction"] = [this]() { registerAction(); };
        this->mapMethods["logoutAction"] = [this]() { logoutAction(); };
        this->mapMethods["changePassword"] = [this]() { changePasswordAction(); };
    }


};

#endif // USERCONTROLLER_H_INCLUDED
