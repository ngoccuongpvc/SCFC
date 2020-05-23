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
            history.push("teacher-dashboard");
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
    
    void teacherDashboard() {
        cout << "Hello Teacher!" << endl;
    }
    
    void staffDashboard() {
        cout << "Hello Staff!" << endl;
    }

    void classDashboardStaff() {
        cout << "This is the class operation dashboard for staff." << endl;
    }

    void courseDashboardStaff() {
        cout << "This is the course operation dashboard for staff." << endl;
    //--------------------------------xx Staff-Scoreboard xx--------------------------------//

    //-------------------------------- Staff-Attendance --------------------------------//
  

    void exportAttendance() {

    }
    //--------------------------------xx Staff-Attendance xx--------------------------------//

    // Student

    //LECTURER/TEACHER

  /*
	void editAttendance()
	{
		cout << "Plz aware that you can edit the attendant's day of each student only" << endl;
		AttendanceModel* am = new AttendanceModel();
		string courseID, studentID;
		cout << "Plz enter the course ID: "; cin >> courseID; am->setCourseId(courseID);
		cout << "Plz enter the student ID: "; cin >> studentID; am->setStudentId(studentID);
		vector<vector<string>> conditions = am->FetchAttendance();

		if (conditions.size() == 0)
		{
			cout << "Unable to find this course/student!" << endl;
			delete am;
			return;
		}

		cout << "Plz enter the day of Attendance for this student: ";
		string day; cin >> day;
		vector<string> record = conditions[0];
		record.back() = day;
		am->UpdateAttendance(&conditions[0], &record);
		delete am;
		return;
	}

	void deleteAttendance()
	{
		cout << "Plz aware that you can't recovery the deleted data. Do you want continue(Y/N)" << endl;
		string opt; cin >> opt;

		while (true)
		{
			if (opt == "Y") break;
			else if (opt == "N") return;
			else
			{
				cout << "Invalid input. Plz try again" << endl;
				cin >> opt;
			}
		}
		AttendanceModel* am = new AttendanceModel();
		string courseID, studentID;
		cout << "Plz enter the course ID: "; cin >> courseID; am->setCourseId(courseID);
		cout << "Plz enter the student ID: "; cin >> studentID; am->setStudentId(studentID);
		vector<vector<string>> conditions = am->FetchAttendance();

		if (conditions.size() == 0)
		{
			cout << "Unable to find this course/student!" << endl;
			delete am;
			return;
		}

		am->RemoveAttendance(&conditions[0]);
		delete am;
		return;
	}

	void editScore()
	{
		ScoreboardModel* sm = new ScoreboardModel();
		string courseId, studentId, term;
		cout << "Plz enter course id: "; cin >> courseId; sm->setCourseId(courseId);
		cout << "Plz enter student id "; cin >> studentId; sm->setStudentId(studentId);
		cout << "Plz enter the term(mid/final)"; cin >> term; sm->setTerm(term);

		vector<vector<string>> conditions = sm->FetchScoreboard();
		if (conditions.size() == 0)
		{
			delete sm;
			cout << "Can't find this student/course/term" << endl;
			return;
		}

		string score;
		cout << "Plz enter the score: "; cin >> score;
		vector<string> record = conditions[0];
		record[sm->getIndex["score"]] = score;
		sm->UpdateScore(&conditions[0], &record);
		delete sm;
		return;
	}
  */

	//END OF LECTURER/TEACHER
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
        this->mapMethods["teacherDashboard"] = [this]() { teacherDashboard(); };
        this->mapMethods["staffDashboard"] = [this]() { staffDashboard(); };

        this->mapMethods["classDashboardStaff"] = [this]() { classDashboardStaff(); };
        this->mapMethods["courseDashboardStaff"] = [this]() { courseDashboardStaff(); };
        this->mapMethods["scoreDashboardStaff"] = [this]() { scoreDashboardStaff(); };
        this->mapMethods["attendanceDashboardStaff"] = [this]() { attendanceDashboardStaff(); };
        this->mapMethods["courseDashboardLecturer"] = [this]() { courseDashboardLecturer(); };
        this->mapMethods["scoreDashboardLecturer"] = [this]() { scoreDashboardLecturer(); };
        this->mapMethods["attendanceDashboardLecturer"] = [this]() { attendanceDashboardLecturer(); };


		//LECTURE/TEACHER SECTION
		this->mapMethods["editAttendance"] = [this]() { editAttendance(); };
		this->mapMethods["deleteAttendance"] = [this]() { deleteAttendance(); };
		this->mapMethods["editScore"] = [this]() { editScore(); };
    }


};

#endif // USERCONTROLLER_H_INCLUDED
