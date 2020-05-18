#ifndef USERCONTROLLER_H_INCLUDED
#define USERCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include "../Model/AccountModel.h"

using namespace std;

string role;

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

	void loginAction() {
		while (true) {
			string username, password;
			cout << "User name: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			AccountModel* model = new AccountModel();

			if (model->checkCredential(username, password)) {
				cout << "Login successful" << endl;
				cout << "You are login as: " << model->getUserRole(username) << endl;
				role = model->getUserRole(username);
				globalUsername = username;
				extern stack<string> history;
				history.push("dashboard");
				break;

			}
			else {
				cout << "Wrong username or password!! Wanna try again (0:false, 1: true): ";
				bool tryAgain = false;
				cin >> tryAgain;
				if (!tryAgain) break;
				//change to loop
			}

			//delete model; //check here if crashed :))
		}
        
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

    }


};

#endif // USERCONTROLLER_H_INCLUDED
