#ifndef USERCONTROLLER_H_INCLUDED
#define USERCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"

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
		while (true)
		{
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
				extern stack<string> history;
				history.push("dashboard");
				createSession(username);
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
        history.push("login");
    }
    

    void seeProfile() {
        if (!checkLoginStatus()) return;
        UserInfoModel* user = new UserInfoModel();
        user->setUsername(globalUsername);
        vector<vector<string>> records = user->FetchInfo();
        if (records.size() == 0) {
            cout << "Something wrong with your account, cannot fetch your profile.";
            return;
        }
        cout << "Student ID: " << records[0][1] << endl;
        cout << "First name: " << records[0][2] << endl;
        cout << "Last name: " << records[0][3] << endl;
        cout << "Date of Birth: " << records[0][4] << endl;
        cout << "Gender: " << records[0][6] << endl;
        delete user;
    }

    // Staff
    
    //----13. CRUD Academic years + semester
    void showSemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> listCourses = cim->FetchAllCourse();
        
    }

    void addCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        AccountModel* am = new AccountModel();
        string temp;
        cout << "Course name: "; cin >> temp; cim->setCourseName(temp);
        cout << "Class name: "; cin >> temp; cim->setClassName(temp);
        
        cout << "Lecturer Account: "; cin >> temp;
        // Check if the lecturer account is available
        am->setUserName(temp);
        vector<vector<string>> results = am->fetchAccount();
        if (results.size() == 0) {
            cout << "The lecturer account is not found, returning..." << endl;
            return;
        }

        cout << "Start day: "; cin >> temp; cim->setStartDay(temp);
        cout << "End day: "; cin >> temp; cim->setEndDay(temp);
        cout << "Start hour: "; cin >> temp; cim->setStartHour(temp);
        cout << "End hour: "; cin >> temp; cim->setEndHour(temp);
        cout << "Room: "; cin >> temp; cim->setRoom(temp);
        cout << "Semester: "; cin >> temp; cim->setSemester(temp);
        cout << "Year: "; cin >> temp; cim->setYear(temp);
        cim->AddCourse();
        delete cim;
    }


    // Student

    // Lecturer

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
