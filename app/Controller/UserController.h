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
    
    //----13. CRUD Academic years + semester

    void viewAllCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> results = cim->FetchCourse();
        vector<string> header = cim->columns;
        for (int i = 0; i < header.size(); ++i) header[i] = capitalize(header[i]);
        View* view = new View(results, header);
        view->displayTable();
        delete view;
    }

    void showYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "No courses was entered in the year you entered." << endl;
            return;
        }
        vector<string> years;
        for (int i = 0; i < results.size(); ++i) {
            for (int k = 0; k < years.size(); ++k) {
                if (years[k] != results[i][10]) {
                    years.push_back(results[i][10]);
                    break;
                }
            }
        }
        vector<vector<string>> info;
        info.push_back(years);
        vector<string> header; header.push_back("Year");
        View* view = new View(info, header);
        view->displayTable();
        delete view;
    }


    void showSemester() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> listCourses = cim->FetchCourse();
        if (listCourses.size() == 0) {
            cout << "No courses found in the semester you entered." << endl;
            return;
        }
        vector<string> semesters;
        for (int i = 0; i < listCourses.size(); ++i) {
            for (int k = 0; k < semesters.size(); ++k) {
                if (listCourses[i][9] != semesters[k])
                    semesters.push_back(listCourses[i][9]);
            }
        }
        vector<vector<string>> info;
        info.push_back(semesters);
        vector<string> header; header.push_back("Semester");
        View* view = new View(info, header);
        view->displayTable();
        delete view;

        delete cim;
    }

    void removeCourseByYear() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the academic year that you want to remove: "; cin >> year;
        cim->setYear(toLowerCase(year));
        vector<vector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            cim->RemoveCourse(&results[i]);
        }
        cout << "Successfully remove all course in the year " << year;
        delete cim;
    }

    void removeCourseBySemester() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        string semester;
        cout << "Please enter the semester that you want to remove: "; cin >> semester;
        cim->setSemester(toLowerCase(semester));
        vector<vector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            cim->RemoveCourse(&results[i]);
        }
        cout << "Successfully remove all course in the semester " << semester;
        delete cim;
    }

    void addCourse() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        AccountModel* am = new AccountModel();
        string temp;
        cout << "Course name: "; cin >> temp; cim->setCourseName(toLowerCase(temp));
        cout << "Class name: "; cin >> temp; cim->setClassName(toLowerCase(temp));
        
        cout << "Lecturer Account: "; cin >> temp;
        // Check if the lecturer account is available
        am->setUserName(toLowerCase(temp));
        vector<vector<string>> results = am->fetchAccount();
        if (results.size() == 0) {
            cout << "The lecturer account is not found, returning..." << endl;
            return;
        }

        cout << "Start day: "; cin >> temp; cim->setStartDay(toLowerCase(temp));
        cout << "End day: "; cin >> temp; cim->setEndDay(toLowerCase(temp));
        cout << "Start hour: "; cin >> temp; cim->setStartHour(toLowerCase(temp));
        cout << "End hour: "; cin >> temp; cim->setEndHour(toLowerCase(temp));
        cout << "Day of week: "; cin >> temp; cim->setEndHour(toLowerCase(temp));
        cout << "Room: "; cin >> temp; cim->setRoom(toLowerCase(temp));
        cout << "Semester: "; cin >> temp; cim->setSemester(toLowerCase(temp));
        cout << "Year: "; cin >> temp; cim->setYear(toLowerCase(temp));
        cim->AddCourse();
        cout << "Successfully added the course." << endl;
        delete cim;
        delete am;
    }

    void editCourse() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        cout << "Please enter the course name that you want to edit: "; string courseName; cin >> courseName;
        cim->setCourseName(toLowerCase(courseName));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered does not exist. Please retry." << endl;
			delete cim; //check if crash
            return;
        }
        vector<string> record = results[0];
        cout << "Please enter the information that you want to change about this course. Press enter if you don't want to change that info.." << endl;
        string temp;
        vector<string> toUpdate;
        toUpdate.push_back(record[0]);
        cout << "Course name: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Class name: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Lecturer account: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Start hour: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "End hour: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Start day: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "End day: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Day of week: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Room: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Semester: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Year: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cim->UpdateCourse(&record, &toUpdate);
        cout << "Successfully updated the course." << endl;
        delete cim;
    }

    void removeCourse() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        string courseName;
        cout << "Please enter the name of the course that you want to remove: "; cin >> courseName;
        cim->setCourseName(toLowerCase(courseName));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered doesn't exist, please recheck." << endl;
            return;
        }
        cim->RemoveCourse(&courseResult[0]);
        cout << "Successfully removed the course " << courseName << endl;
        delete cim;
    }

    void listOfCourseCurrentSemester() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        string semester;
        cout << "Please enter the semester that you want to view the list of courses of: "; cin >> semester;
        cim->setSemester(toLowerCase(semester));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The semester doesn't exist or you haven't added any course to this semester yet!" << endl;
            return;
        }
        vector<string> courses;
        for (int i = 0; i < results.size(); ++i) {
            courses.push_back(results[i][1]);
        }
        vector<vector<string>> info;
        info.push_back(courses);
        vector<string> header; header.push_back("Course Name");
        View* view = new View(info, header);
        view->displayTable();
        delete cim;
        delete view;
    }

    void removeStudentFromCourse() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        string courseName, studentIdentifier, courseId, studentId;
        cout << "Please enter the name of the course you want to remove a student from: "; cin >> courseName;
        cim->setCourseName(toLowerCase(courseName));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        cout << "Please enter the student ID of the student you want to remove from this course: "; cin >> studentIdentifier;
        uim->setStudentID(toLowerCase(studentIdentifier));
        vector<vector<string>> studentResult = uim->FetchInfo();
        if (studentResult.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        studentId = studentResult[0][0];
        am->setCourseId(courseId);
        am->setStudentId(studentId);
        vector<vector<string>> attendance = am->FetchAttendance();
        for (int i = 0; i < attendance.size(); ++i) {
            am->RemoveAttendance(&attendance[i]);
        }
        sm->setCourseId(courseId);
        sm->setStudentId(studentId);
        vector<vector<string>> scoreboard = sm->FetchScoreboard();
        for (int i = 0; i < scoreboard.size(); ++i) {
            sm->DeleteScore(&scoreboard[i]);
        }
        cout << "Successfully removed the student." << endl;
        delete cim;
        delete am;
        delete uim;
        delete sm;
    }

    void addStudentToCourse() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        string courseName, studentIdentifier, courseId, studentId;
        cout << "Please enter the name of the course you want to add a student into: "; cin >> courseName;
        cim->setCourseName(toLowerCase(courseName));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        cout << "Please enter the student ID of the student you want to add into this course: "; cin >> studentIdentifier;
        uim->setStudentID(toLowerCase(studentIdentifier));
        vector<vector<string>> studentResult = uim->FetchInfo();
        if (studentResult.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        studentId = studentResult[0][0];
        am->setCourseId(courseId);
        am->setStudentId(studentId);
        am->setDay("");
        am->AddAttendance();

        sm->setCourseId(courseId);
        sm->setStudentId(studentId);
        sm->setTerm("");
        sm->setScore("");
        sm->AddScore();
        
        cout << "Successfully added the student to the course." << endl;

        delete cim;
        delete am;
        delete uim;
        
    }

    void viewListOfStudentsOfCourse() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        string temp, courseId;
        cout << "Enter the name of the course you want to search: "; cin >> temp;
        cim->setCourseName(toLowerCase(temp));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered could not be found." << endl;
            return;
        }
        courseId = results[0][0];
        vector<vector<string>> students;
        
        am->setCourseId(courseId);
        am->setDay("");
        results = am->FetchAttendance();
        for (int i = 0; i < results.size(); ++i) {
            uim->setId(results[i][1]);
            vector<vector<string>> getBack = uim->FetchInfo();
            if (getBack.size() != 0) {
                students.push_back(getBack[0]);
            }
        }

        vector<string> header = uim->columns;
        for (int i = 0; i < header.size(); ++i) {
            header[i] = capitalize(header[i]);
        }
        View* view = new View(students, header);
        view->displayTable();
        delete cim;
        delete uim;
        delete am;
        delete view;
    }

    void viewAttendanceList() {
        if (role != "staff") return;
        AttendanceModel* am = new AttendanceModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string temp, courseId;
        cout << "Enter the name of the course you want to search: "; cin >> temp;
        cim->setCourseName(toLowerCase(temp));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered could not be found." << endl;
            return;
        }
        courseId = results[0][0];
        vector<vector<string>> attendance;
        am->setCourseId(courseId);
        am->setDay("");
        results = am->FetchAttendance();
        if (results.size() == 0) {
            cout << "No students attended the given course, please recheck." << endl;
            return;
        }
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setCourseId(courseId);
        for (int i = 0; i < results.size(); ++i) {
            am_temp->setStudentId(results[i][1]);
            uim->setId(results[i][1]);
            vector<vector<string>> users = uim->FetchInfo();
            vector<string> attendanceOfOne;
            if (users.size() != 0) {
                attendanceOfOne.push_back(users[0][1]);
            }
            else attendanceOfOne.push_back("");
            vector<vector<string>> getBack = am->FetchAttendance();
            
            for (int k = 0; k < getBack.size(); ++k) {
                attendanceOfOne.push_back(getBack[k][3]);
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 0;
        for (int i = 0; i < attendance.size(); ++i) {
            if (attendance[i].size() > max_column) max_column = attendance[i].size();
        }
        vector<string> header; header.push_back("Course Name");
        for (int i = 0; i < max_column; ++i) header.push_back(" ");
        View* view = new View(attendance, header);
        view->displayTable();
        delete view;
        delete am;
        delete cim;
    }

    void createLecturer() {
        if (role != "staff") return;
        UserInfoModel* uim = new UserInfoModel();
        AccountModel* am = new AccountModel();
        string temp;
        uim->setStudentID("");
        cout << "Lecturer first name: "; cin >> temp; uim->setFirstName(toLowerCase(temp));
        cout << "Lecturer last name: "; cin >> temp; uim->setLastName(toLowerCase(temp));
        cout << "Lecturer DOB: "; cin >> temp; uim->setDOB(toLowerCase(temp));
        cout << "Lecturer gender: "; cin >> temp; uim->setUserGender(toLowerCase(temp));
        cout << "Lecturer username: "; cin >> temp; uim->setFirstName(toLowerCase(toLowerCase(temp)));
        am->setUserName(temp);
        am->setPassword(uim->getDOB());
        am->setRole("lecturer");
        uim->AddUser();
        am->registerUser();
        cout << "Successfully created the lecturer." << endl;
        delete uim;
        delete am;
    }

    void viewAllLecturer() {
        if (role != "staff") return;
        UserInfoModel* uim = new UserInfoModel();
        AccountModel* am = new AccountModel();
        am->setRole("lecturer");
        vector<vector<string>> results = am->fetchAccount();
        if (results.size() == 0) {
            cout << "No lecturer was found!" << endl;
            return;
        }
        vector<vector<string>> lecturers;
        for (int i = 0; i < results.size(); ++i) {
            uim->setUsername(results[i][7]);
            vector<vector<string>> getBack = uim->FetchInfo();
            if (getBack.size() != 0) {
                lecturers.push_back(getBack[0]);
            }
        }
        vector<string> header = uim->columns;
        for (int i = 0; i < header.size(); ++i) {
            header[i] = capitalize(header[i]);
        }
        View* view = new View(lecturers, header);
        view->displayTable();

        delete uim;
        delete am;
        delete view;
    }

    void editLecturer() {
        if (role != "staff") return;
        UserInfoModel* uim = new UserInfoModel();
        cout << "Please enter the username of the lecturer that you want to edit: "; string username; cin >> username;
        uim->setUsername(toLowerCase(username));
        vector<vector<string>> results = uim->FetchInfo();
        if (results.size() == 0) {
            cout << "The lecturer account you entered does not exist. Please retry." << endl;
            return;
        }
        vector<string> record = results[0];
        cout << "Please enter the information that you want to change about this course. Press enter if you don't want to change that info.." << endl;
        string temp;
        vector<string> toUpdate;
        toUpdate.push_back(record[0]);
        toUpdate.push_back("");
        cout << "First name: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Last name: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Date of birth: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "User gender: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "New username: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        uim->UpdateInfo(&record, &toUpdate);
        cout << "Successfully edited the lecturer." << endl;
        delete uim;
    }

    void deleteLecturer() {
        if (role != "staff") return;
        UserInfoModel* uim = new UserInfoModel();
        AccountModel* am = new AccountModel();
        string lecturer;
        cout << "Enter the account of the lecturer that you want to remove: "; cin >> lecturer;
        uim->setUsername(lecturer);
        am->setUserName(lecturer);
        am->setRole("lecturer");
        vector<vector<string>> accountResult = am->fetchAccount();
        vector<vector<string>> userResult = uim->FetchInfo();
        if (accountResult.size() == 0 || userResult.size() == 0)  {
            cout << "The account you entered may not exist, please recheck." << endl;
            return;
        }
        for (int i = 0; i < accountResult.size(); ++i) {
            am->removeAccount(&accountResult[i]);
        }
        for (int i = 0; i < userResult.size(); ++i) {
            uim->RemoveUser(&userResult[i]);
        }
        cout << "Successfully deleted the lecturer." << endl;
        delete uim;
        delete am;
    }

    //--------------------------------xx Staff-Course xx--------------------------------//

    //-------------------------------- Staff-Scoreboard --------------------------------//

    void searchAndViewScore() {
        ScoreboardModel* sm = new ScoreboardModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string courseName, studentIdentifier, courseId, studentId;
        cout << "Please enter the name of the course you want to view score of: "; cin >> courseName;
        cim->setCourseName(toLowerCase(courseName));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        sm->setCourseId(courseId);
        sm->setScore("");
        sm->setTerm("");
        vector<vector<string>> studentResults = sm->FetchScoreboard();
        if (studentResults.size() == 0) {
            cout << "No students was given any score in the given course." << endl;
            return;
        }
        ScoreboardModel* sm_temp = new ScoreboardModel();
        vector<vector<string>> scores;
        sm_temp->setCourseId(courseId);
        for (int i = 0; i < studentResults.size(); ++i) {
            vector<string> score;
            sm_temp->setStudentId(studentResults[i][1]);
            uim->setId(studentResults[i][1]);
            vector<vector<string>> users = uim->FetchInfo();
            score.push_back(users[0][1]);
            vector<vector<string>> scoreResult = sm_temp->FetchScoreboard();
            for (int k = 0; k < scoreResult.size(); k++) {
                string scoreLine = scoreResult[k][3] + ":" + scoreResult[k][4];
                score.push_back(scoreLine);
            }
        }
        int max_column = 0;
        for (int i = 0; i < scores.size(); ++i) {
            if (scores[i].size() > max_column) max_column = scores[i].size();
        }
        vector<string> header; header.push_back("Course Name");
        for (int i = 0; i < max_column; ++i) header.push_back(" ");
        View* view = new View(scores, header);
        view->displayTable();
        delete view;
        delete sm;
        delete sm_temp;
        delete cim;
        delete uim;

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

    void checkIn() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        if (role != "student") return;
        string courseName, studentIdentifier, courseId, studentId, day;
        cout << "Please enter the name of the course you want to checkin: "; cin >> courseName;
        cim->setCourseName(toLowerCase(courseName));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        cout << "Please enter your student Id: "; cin >> studentIdentifier;
        uim->setStudentID(toLowerCase(studentIdentifier));
        vector<vector<string>> studentResult = uim->FetchInfo();
        if (studentResult.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        studentId = studentResult[0][0];
        am->setStudentId(studentId);
        am->setCourseId(courseId);
        am->setDay("");
        vector<vector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in this course." << endl;
            return;
        }
        cout << "Please enter the day you are checking in: "; cin >> day;
        am->setDay(day);
        am->AddAttendance();
        cout << "Successfully added your checkin." << endl;
        delete uim;
        delete am;
        delete cim;
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

    void accessDashboard() {
        cout << "Hello User!" << endl;
        extern stack<string> history;
        //history = stack<string>();

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


    }


};

#endif // USERCONTROLLER_H_INCLUDED
