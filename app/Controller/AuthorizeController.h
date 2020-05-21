#ifndef AUTHORIZECONTROLLER_H_INCLUDED
#define AUTHORIZECONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "UserController.h"

class AuthorizeController : public ControllerInterface {

private:

public:
    string role;
    bool logged_in = false;
    string currentSession = "";

    string globalUsername = "null";

    bool checkLoginStatus() {
        if (!logged_in || currentSession == "") {
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
        AccountModel* model = new AccountModel();

        while (true) {
            cout << "User name: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (model->checkCredential(username, password)) {
                cout << "Login successful" << endl;
                cout << "You are login as: " << model->getUserRole(username) << endl;
                role = model->getUserRole(username);
                extern stack<string> history;
                history.push("dashboard");
                createSession(username);
                break;
            }
            else {
                cout << "Wrong username or password" << endl;
                cout << "Wrong username or password!! Wanna try again (0:false, 1: true): ";
                bool tryAgain = false;
                cin >> tryAgain;
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
                user->setUsername(studentID);
                am->setUserName(studentID);
                am->setPassword(dob);
            }
            else {
                user->setStudentID("");
                cout << "Username: "; cin >> username; user->setUsername(username);
                am->setUserName(username);
                cout << "Password: "; cin >> password; am->setPassword(password);
                am->setPassword(password);
            }
            user->AddUser();
            am->registerUser();
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
        history = stack<string>();
        history.push("access");
    }
};

#endif // !
