#ifndef ROUTES_H_INCLUDED
#define ROUTES_H_INCLUDED

#include <map>
#include <string>
#include <iostream>
#include "../Utils/myVector.h"

using namespace std;


class Routes {
private:
	map<string, pair<string, string>> routes;
	map<string, myVector<string>> links;
	map<string, string> usage;

public:
	void addRoute(string path, string controller, string action)
	{
		this->routes[path] = make_pair(controller, action);
	}

	void linkTo(string current, string next)
	{
		links[current].push_back(next);
	}

	string getController(string path)
	{
		return routes[path].first;
	}

	string getAction(string path)
	{
		return routes[path].second;
	}

	int getNumberOfOption(string path)
	{
		return this->links[path].size();
	}

	void showOptions(string path)
	{
		cout << "0 - Back" << endl;
		int i = 1;
		for (string nextPath : links[path]) {
			cout << i++ << " - " << usage[nextPath] << endl;;
		}
	}

	string getOption(string path, int option)
	{
		return links[path][option-1];
	}

	Routes()
	{
		/****** AUTHORIZATION ******/
		usage["log-out"] = "Log out";
		usage["login"] = "Log in";
		usage["register"] = "Register a new account";
		usage["change-password"] = "Change password";
		usage["import-database"] = "Add a database";
		usage["drop-database"] = "Drop all databases";

		/****** COURSE OPERATIONS ******/
		usage["add-course"] = "Manually add a new course";
		usage["add-student-to-course"] = "Add a student to an available course";
		usage["edit-course"] = "Edit the information of a course";
		usage["import-course"] = "Import courses from a csv file";
		usage["list-of-course-current-semester"] = "View list of courses in a semester";
		usage["list-of-course-current-year"] = "View list of courses in an academic year";
		usage["remove-course"] = "Manually remove a course";
		usage["remove-course-by-semester"] = "Remove a semester";
		usage["remove-course-by-year"] = "Remove an academic year";
		usage["remove-student-from-course"] = "Remove a student from a course";
		usage["view-all-course"] = "View all courses";
		usage["view-list-of-students-of-course"] = "View list of students in a course";

		/****** SCOREBOARD OPERATIONS ******/
		usage["edit-score"] = "Edit scores of a student";
		usage["import-scoreboard"] = "Import scoreboard for a course";
		usage["export-scoreboard"] = "Export scoreboard to a CSV file";
		usage["search-and-view-score"] = "Search and view scoreboard of a course";
		usage["view-score-of-course"] = "View scores of an enrolled course";

		/****** ATTENDANCE OPERATIONS ******/
		usage["check-in"] = "Check in a course study day";
		usage["delete-attendance"] = "Delete attendance of a student";
		usage["edit-attendance"] = "Add attendance of a student";
		usage["export-attendance"] = "Export attendance board to a CSV file";
		usage["view-attendance-list"] = "View attendance list of a course";
		usage["view-check-in-result"] = "View your check-in result of a course";

		/****** ACCOUNT OPERATIONS ******/
		usage["create-lecturer"] = "Create a new lecturer";
		usage["delete-lecturer"] = "Delete a lecturer";
		usage["edit-lecturer"] = "Edit a lecturer";
		usage["see-profile"] = "See profile of your account";
		usage["view-all-lecturer"] = "View list of lecturers";

		/****** ACADEMIC OPERATIONS ******/
		usage["show-semester"] = "Show the list of semesters";
		usage["show-year"] = "Show the list of academic years";
		usage["view-schedule"] = "View the schedule";

		/****** USER OPERATIONS ******/
		usage["class-dashboard-staff"] = "View class operations";
		usage["course-dashboard-staff"] = "View course operations";
		usage["score-dashboard-staff"] = "View scoreboard operations";
		usage["attendance-dashboard-staff"] = "View attendance operations";
		usage["lecturer-dashboard-staff"] = "View lecturer operations";

		usage["course-dashboard-lecturer"] = "View course operations for lecturers";
		usage["score-dashboard-lecturer"] = "View scoreboard operations for lecturers";
		usage["attendance-dashboard-lecturer"] = "View attendance operations for lecturers";

		/****** CLASS OPERATIONS ******/
		usage["import-class"] = "Import student list of class";
		usage["view-class"] = "View list of classes";
		usage["view-student-in-class"] = "View list of students in a class";
		usage["add-student-to-class"] = "Add a new student to class";
		usage["student-manipulate"] = "Student operations";
		usage["remove-student"] = "Remove a student";
		usage["edit-student"] = "Edit student information";
		usage["change-student-class"] = "Move student to new class";
		/**************************************************************************/

		/****** AUTHORIZATION ******/
		addRoute("login", "AuthorizeController", "loginAction");
		addRoute("change-password", "AuthorizeController", "changePasswordAction");
		addRoute("log-out", "AuthorizeController", "logoutAction");
		addRoute("register", "AuthorizeController", "registerAction");

		/****** COURSE OPERATIONS ******/
		addRoute("add-course", "CourseController", "addCourse");
		addRoute("add-student-to-course", "CourseController", "addStudentToCourse");
		addRoute("edit-course", "CourseController", "editCourse");
		addRoute("import-course", "CourseController", "importCourse");
		addRoute("list-of-course-current-semester", "CourseController", "listOfCourseCurrentSemester");
		addRoute("list-of-course-current-year", "CourseController", "listOfCourseCurrentYear");
		addRoute("remove-course", "CourseController", "removeCourse");
		addRoute("remove-course-by-semester", "CourseController", "removeCourseBySemester");
		addRoute("remove-course-by-year", "CourseController", "removeCourseByYear");
		addRoute("remove-student-from-course", "CourseController", "removeStudentFromCourse");
		addRoute("view-all-course", "CourseController", "viewAllCourse");
		addRoute("view-list-of-students-of-course", "CourseController", "viewListOFStudentsOfCourse");
		
		/****** SCOREBOARD OPERATIONS ******/
		addRoute("import-scoreboard", "ScoreboardController", "importScoreboard");
		addRoute("edit-score", "ScoreboardController", "editScore");
		addRoute("export-scoreboard", "ScoreboardController", "exportScoreboard");
		addRoute("search-and-view-score", "ScoreboardController", "searchAndViewScore");
		addRoute("view-score-of-course", "ScoreboardController", "viewScoreOfCourse");

		/****** ATTENDANCE OPERATIONS ******/
		addRoute("check-in", "AttendanceController", "checkIn");
		addRoute("delete-attendance", "AttendanceController", "deleteAttendance");
		addRoute("edit-attendance", "AttendanceController", "editAttendance");
		addRoute("export-attendance", "AttendanceController", "exportAttendance");
		addRoute("view-attendance-list", "AttendanceController", "viewAttendanceList");
		addRoute("view-check-in-result", "AttendanceController", "viewCheckInResult");

		/****** ACCOUNT OPERATIONS ******/
		addRoute("create-lecturer", "AccountController", "createLecturer");
		addRoute("delete-lecturer", "AccountController", "deleteLecturer");
		addRoute("edit-lecturer", "AccountController", "editLecturer");
		addRoute("see-profile", "AccountController", "seeProfile");
		addRoute("view-all-lecturer", "AccountController", "viewAllLecturer");

		/****** ACADEMIC OPERATIONS ******/
		addRoute("show-semester", "AcademicController", "showSemester");
		addRoute("show-year", "AcademicController", "showYear");
		addRoute("view-schedule", "AcademicController", "viewSchedule");
		addRoute("import-database", "AcademicController", "importDatabase");
		addRoute("drop-database", "AcademicController", "dropDatabase");

		/****** USER OPERATIONS ******/
		addRoute("dashboard", "UserController", "mainAction");
		addRoute("student-dashboard", "UserController", "studentDashboard");
		addRoute("lecturer-dashboard", "UserController", "lecturerDashboard");
		addRoute("staff-dashboard", "UserController", "staffDashboard");
		addRoute("access", "UserController", "accessDashboard");

		/****** CLASS OPERATORS ********************/
		addRoute("import-class", "ClassController", "importAction");
		addRoute("view-class", "ClassController", "showClassList");
		addRoute("view-student-in-class", "ClassController", "showStudentInClass");
		addRoute("add-student-to-class", "ClassController", "addStudent");
		addRoute("student-manipulate", "ClassController", "studentManipulate");
		addRoute("remove-student", "ClassController", "removeStudent");
		addRoute("edit-student", "ClassController", "editStudent");
		addRoute("change-student-class", "ClassController", "changeStudentClass");

		/*********************************************/
		addRoute("class-dashboard-staff", "UserController", "classDashboardStaff");
		addRoute("course-dashboard-staff", "UserController", "courseDashboardStaff");
		addRoute("score-dashboard-staff", "UserController", "scoreDashboardStaff");
		addRoute("attendance-dashboard-staff", "UserController", "attendanceDashboardStaff");
		addRoute("lecturer-dashboard-staff", "UserController", "lecturerDashboardStaff");

		addRoute("course-dashboard-lecturer", "UserController", "courseDashboardLecturer");
		addRoute("score-dashboard-lecturer", "UserController", "scoreDashboardLecturer");
		addRoute("attendance-dashboard-lecturer", "UserController", "attendanceDashboardLecturer");

		/**************************************************************************/

		/****** STUDENT DASHBOARD ******/
		linkTo("student-dashboard", "change-password");
		linkTo("student-dashboard", "check-in");
		linkTo("student-dashboard", "view-check-in-result");
		linkTo("student-dashboard", "view-schedule");
		linkTo("student-dashboard", "view-score-of-course");
		linkTo("student-dashboard", "see-profile");
		linkTo("student-dashboard", "log-out");
		/****** STAFF DASHBOARD ******/
		linkTo("staff-dashboard", "change-password");
		linkTo("staff-dashboard", "class-dashboard-staff");
		linkTo("staff-dashboard", "course-dashboard-staff");
		linkTo("staff-dashboard", "score-dashboard-staff");
		linkTo("staff-dashboard", "attendance-dashboard-staff");
		linkTo("staff-dashboard", "lecturer-dashboard-staff");
		linkTo("staff-dashboard", "see-profile");
		linkTo("staff-dashboard", "log-out");
		/****** LECTURE DASHBOARD******/
		linkTo("lecturer-dashboard", "change-password");
		linkTo("lecturer-dashboard", "course-dashboard-lecturer");
		linkTo("lecturer-dashboard", "score-dashboard-lecturer");
		linkTo("lecturer-dashboard", "attendance-dashboard-lecturer");
		linkTo("lecturer-dashboard", "see-profile");
		linkTo("lecturer-dashboard", "log-out");

		/****** STAFF - CLASS OPERATIONS ******/
		linkTo("class-dashboard-staff", "import-class");
		linkTo("class-dashboard-staff", "view-class");
		linkTo("class-dashboard-staff", "view-student-in-class");
		linkTo("class-dashboard-staff", "student-manipulate");
		linkTo("student-manipulate", "add-student-to-class");
		linkTo("student-manipulate", "remove-student");
		linkTo("student-manipulate", "edit-student");
		linkTo("student-manipulate", "change-student-class");

		/****** STAFF - COURSE OPERATIONS ******/
		linkTo("course-dashboard-staff", "add-course");
		linkTo("course-dashboard-staff", "add-student-to-course");
		linkTo("course-dashboard-staff", "edit-course");
		linkTo("course-dashboard-staff", "import-course");
		linkTo("course-dashboard-staff", "list-of-course-current-semester");
		linkTo("course-dashboard-staff", "list-of-course-current-year");
		linkTo("course-dashboard-staff", "remove-course");
		linkTo("course-dashboard-staff", "remove-course-by-semester");
		linkTo("course-dashboard-staff", "remove-course-by-year");
		linkTo("course-dashboard-staff", "remove-student-from-course");
		linkTo("course-dashboard-staff", "view-all-course");
		linkTo("course-dashboard-staff", "view-list-of-students-of-course");
		/****** STAFF - SCORE OPERATIONS ******/
		linkTo("score-dashboard-staff", "export-scoreboard");
		linkTo("score-dashboard-staff", "search-and-view-score");
		/****** STAFF - ATTENDANCE OPERATIONS ******/
		linkTo("attendance-dashboard-staff", "export-attendance");
		linkTo("attendance-dashboard-staff", "view-attendance-list");
		/****** STAFF - LECTURER OPERATIONS ******/
		linkTo("lecturer-dashboard-staff", "create-lecturer");
		linkTo("lecturer-dashboard-staff", "delete-lecturer");
		linkTo("lecturer-dashboard-staff", "edit-lecturer");
		linkTo("lecturer-dashboard-staff", "view-all-lecturer");

		/****** LECTURER - COURSE OPERATIONS ******/
		linkTo("course-dashboard-lecturer", "list-of-course-current-semester");
		linkTo("course-dashboard-lecturer", "view-list-of-students-of-course");
		/****** LECTURER - ATTENDANCE OPERATIONS ******/
		linkTo("attendance-dashboard-lecturer", "view-attendance-list");
		linkTo("attendance-dashboard-lecturer", "edit-attendance");
		linkTo("attendance-dashboard-lecturer", "delete-attendance");
		/****** LECTURER - SCORE OPERATIONS ******/
		linkTo("score-dashboard-lecturer", "import-scoreboard");
		linkTo("score-dashboard-lecturer", "edit-score");
		linkTo("score-dashboard-lecturer", "search-and-view-score");

		linkTo("access", "login");
		linkTo("access", "register");			
		linkTo("access", "import-database");			
		linkTo("access", "drop-database");			
	}
};
#endif // ROUTES_H_INCLUDED