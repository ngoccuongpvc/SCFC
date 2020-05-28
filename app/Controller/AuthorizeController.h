#ifndef AUTHORIZECONTROLLER_H_INCLUDED
#define AUTHORIZECONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include <string.h>
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"
#include "Validation.h"

string role;
bool logged_in = false;
string currentSession = "";

string globalUsername = "null";

class AuthorizeController : public ControllerInterface {

private:
	Validation* valid = new Validation();
	 
public:
    bool checkLoginStatus() {
        if (!logged_in || currentSession == "") {
            return false;
        }
        else return true;
    }

    void createSession(string username) {
        if (checkLoginStatus()) return;
        globalUsername = username;
        currentSession = username;
        logged_in = true;
    }

    void resetSession() {
        currentSession = "";
        globalUsername = "";
        logged_in = false;
    }

    void loginAction() {
        string username, password;
        AccountModel* model = new AccountModel();

        while (true) {
			//fflush
            cout << "User name: ";
			valid->read(username, "nospc");
            cout << "Password: ";
			valid->read(password, "nospc");
			if (model->checkCredential(username, password)) {
                cout << "Login successful" << endl;
                cout << "You are login as: " << model->getUserRole(username) << endl;
                role = model->getUserRole(username);
                extern stack<string> history;
                history.push("dashboard");
                createSession(username);
                role = model->getUserRole(username);
                break;
            }
            else {
                cout << "Wrong username or password" << endl;
                cout << "Wrong username or password!! Wanna try again (0:false, 1: true): ";
                bool tryAgain = false;
				//fflush
                string temp;
                getline(cin, temp);

                if (!tryAgain) break;
            }
        }

    }

    void registerAction() {
        //if (checkLoginStatus()) return;

        bool validAccount = false;
        UserInfoModel* user = new UserInfoModel();
        AccountModel* am = new AccountModel();
        extern stack<string> history;
        string firstName, lastName, dob, gender, role_l, username, password, studentID;

		//fflush
		//string temp;
		//getline(cin, temp);

        cout << "Welcome to the register screen" << endl;
        cout << "First name: ";    valid->read(firstName, "all"); user->setFirstName(firstName);
		cout << "Last name: ";     valid->read(lastName, "all");  user->setLastName(lastName);
		cout << "Date of Birth: "; valid->read(dob, "date");      user->setDOB(dob);
		cout << "Gender: ";        valid->read(gender, "gender"); user->setUserGender(gender);
		role = "";																		  
        while (role_l != "student" && role_l != "lecturer" && role_l != "staff") {
            cout << "Role (student/ staff/ lecturer): "; valid->read(role_l, "role");
        }
        if (role_l == "student") {
            cout << "Student ID: "; valid->read(studentID, "nospc"); user->setStudentId(studentID);
            user->setUsername(studentID);
            am->setUserName(studentID);
            am->setPassword(dob); //defualt password of student == thier dob
        }
        else {
            user->setStudentId("");
            cout << "Username: "; valid->read(username, "nospc"); user->setUsername(username);
            am->setUserName(username);
            cout << "Password: "; valid->read(password, "nospc"); 
			am->setPassword(password);
        }
		am->setRole(role_l);
        user->AddUser();
        am->registerUser();
        createSession(am->getUserName());
        role = role_l;
        history.push("dashboard");
        delete user;
        delete am;
    }

    void logoutAction() {
        if (!checkLoginStatus()) return;
        extern stack<string> history;
        resetSession();
        history = stack<string>();
        history.push("access");
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
            valid->read(newPass, "nospc");

            AccountModel* model = new AccountModel();

            if (model->changePassword(globalUsername, newPass))
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

    AuthorizeController() {
        this->mapMethods["changePasswordAction"] = [this]() { changePasswordAction(); };
        this->mapMethods["logoutAction"] = [this]() { logoutAction(); };
        this->mapMethods["loginAction"] = [this]() { loginAction(); };
        this->mapMethods["registerAction"] = [this]() { registerAction(); };
    }

	~AuthorizeController()
	{
		delete valid;
	}
};

#endif // !
