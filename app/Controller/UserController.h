#ifndef USERCONTROLLER_H_INCLUDED
#define USERCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include <string.h>

#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"

#include "MiscellanousFunctions.h"

#include "AuthorizeController.h"
#include "AcademicController.h"
#include "AttendanceController.h"
#include "ScoreboardController.h"
#include "AuthorizeController.h"
#include "CourseController.h"

using namespace std;

class UserController : public ControllerInterface
{
private:

public:

    void mainAction() {
        extern stack<string> history;
        string nextMethod;
        if (role == "student") {
            history.push("student-dashboard");
        }
        else if (role == "lecturer") {
            history.push("lecturer-dashboard");
        }
        else if (role == "staff") {
            history.push("staff-dashboard");
        }
        else {
            history.push("login");
        }
    }

    void accessDashboard() {
        cout << "Hello User!" << endl;
        extern stack<string> history;
        //history = stack<string>();
    }

    void studentDashboard() {
        cout << "Hello Student!" << endl;
    }
    
    void lecturerDashboard() {
        cout << "Hello lecturer!" << endl;
    }
    
    void staffDashboard() {
        cout << "Hello Staff!" << endl;
    }

    void classDashboardStaff() {
        cout << "This is the class operation dashboard for staff." << endl;
    }

    void courseDashboardStaff() {
        cout << "This is the course operation dashboard for staff." << endl;
    }

    void scoreDashboardStaff() {
        cout << "This is the score operation dashboard for staff." << endl;
    }

    void attendanceDashboardStaff() {
        cout << "This is the attendance operation dashboard for staff." << endl;
    }

    void lecturerDashboardStaff() {
        cout << "This is the lecturer operation dashboard for staff." << endl;
    }

    void courseDashboardLecturer() {
        cout << "This is the course operation dashboard for lecturer." << endl;
    }

    void scoreDashboardLecturer() {
        cout << "This is the score operation dashboard for lecturer." << endl;
    }

    void attendanceDashboardLecturer() {
        cout << "This is the attendance operation dashboard for lecturer." << endl;
    }

//public:

    /**
    Constructor of Controller, which map a string to a function
    */
    UserController() {

        this->mapMethods["mainAction"] = [this]() { mainAction(); };
        this->mapMethods["studentDashboard"] = [this]() { studentDashboard(); };
        this->mapMethods["lecturerDashboard"] = [this]() { lecturerDashboard(); };
        this->mapMethods["staffDashboard"] = [this]() { staffDashboard(); };

        this->mapMethods["classDashboardStaff"] = [this]() { classDashboardStaff(); };
        this->mapMethods["courseDashboardStaff"] = [this]() { courseDashboardStaff(); };
        this->mapMethods["scoreDashboardStaff"] = [this]() { scoreDashboardStaff(); };
        this->mapMethods["attendanceDashboardStaff"] = [this]() { attendanceDashboardStaff(); };
        this->mapMethods["courseDashboardLecturer"] = [this]() { courseDashboardLecturer(); };
        this->mapMethods["scoreDashboardLecturer"] = [this]() { scoreDashboardLecturer(); };
        this->mapMethods["attendanceDashboardLecturer"] = [this]() { attendanceDashboardLecturer(); };

    }


};

#endif // USERCONTROLLER_H_INCLUDED
