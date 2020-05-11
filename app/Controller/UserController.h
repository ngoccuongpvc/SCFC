#ifndef USERCONTROLLER_H_INCLUDED
#define USERCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include "../Model/AccountModel.h"

using namespace std;

string role;

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

        } else {
            cout << "Wrong username or password" << endl;
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
    }
public:

    /**
    Constructor of Controller, which map a string to a function
    */
    UserController() {
        this->mapMethods["mainAction"] = [this]() { mainAction(); };
        this->mapMethods["loginAction"] = [this]() { loginAction(); };
        this->mapMethods["studentDashboard"] = [this]() { studentDashboard(); };
        this->mapMethods["teacherDashboard"] = [this]() { studentDashboard(); };
        this->mapMethods["staffDashboard"] = [this]() { studentDashboard(); };

    }


};

#endif // USERCONTROLLER_H_INCLUDED
