#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

#include "ControllerInterface.h"
#include <iostream>
#include <string.h>
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"

using namespace std;

class TeacherController : public ControllerInterface
{
private:

	string toLowerCase(string s) {
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {return tolower(c); });
		return s;
	}

	string capitalize(string str) {
		int check = 0, i = 0;
		while (str[i]) {
			if (check == 0) {
				str[i] = toupper(str[i]);
				check = 1;
			}
			else if (isspace(str[i]))
				check = 0;
			i++;
		}
	}

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

		cout << "Plz enter the day of attendance for this student: ";
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
		cout << "Editting score of student!" << endl;
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


public:

	/**
	Constructor of Controller, which map a string to a function
	*/
	TeacherController() {
		
		this->mapMethods["editAttendance"] = [this]() { editAttendance(); };
		this->mapMethods["deleteAttendance"] = [this]() { deleteAttendance(); };
		this->mapMethods["editScore"] = [this]() { editScore(); };
	}


};

#endif // USERCONTROLLER_H_INCLUDED

