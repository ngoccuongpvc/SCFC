#ifndef USERCONTROLLER_H_INCLUDED
#define USERCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include "../Model/AccountModel.h"

using namespace std;

class UserController : public ControllerInterface
{
private:

    void mainAction() {
        cout << "Menu: " << endl;
        cout << "1 - Login" << endl;
        cout << "Please choose a number: ";
        string type;
        cin >> type;
        if (type == "1") {
            this->callMethod("loginAction");
        }

        return;
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
        } else {
            cout << "Wrong username or password" << endl;
        }
    }
public:

    /**
    Constructor of Controller, which map a string to a function
    */
    UserController() {
        this->mapMethods["mainAction"] = [this]() { mainAction(); };
        this->mapMethods["loginAction"] = [this]() { loginAction(); };
    }


};

#endif // USERCONTROLLER_H_INCLUDED
