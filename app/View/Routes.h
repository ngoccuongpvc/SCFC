#ifndef ROUTES_H_INCLUDED
#define ROUTES_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Routes {
private:
	map<string, pair<string, string>> routes;
	map<string, vector<string>> links;
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
		usage["change-password"] = "Change password";
		usage["check-in"] = "Check in";
		usage["check-in-result"] = "View your check in result";
		usage["view-schedule"] = "View schedule";
		usage["view-scoreboard"] = "Scoreboard";

		usage["log-out"] = "Log out";
		usage["login"] = "Log in";
		usage["register"] = "Register a new account";
		usage["import-class"] = "Import student list of class";
		usage["view-class"] = "View list of classes";
		usage["view-student-in-class"] = "View list of students in a classe";

		//TEACHER SECTION

		usage["edit-attendence"] = "Editting one student's attendence day";
		usage["delete-attendence"] = "Deleting one student from attendence list";
		usage["edit-score"] = "Editting one student score";

		/**************************************************************************/
		addRoute("login", "UserController", "loginAction");
		addRoute("dashboard", "UserController", "mainAction");
		addRoute("student-dashboard", "UserController", "studentDashboard");
		addRoute("teacher-dashboard", "TeacherController", "teacherDashboard");
		addRoute("staff-dashboard", "UserController", "staffDashboard");
		addRoute("change-password", "UserController", "changePassword");

    
		addRoute("log-out", "UserController", "logoutAction");
		addRoute("register", "UserController", "registerAction");
		addRoute("access", "UserController", "accessDashboard");

		//CLASS SECTION
		addRoute("import-class", "ClassController", "importAction");
		addRoute("view-class", "ClassController", "showClassList");
		addRoute("view-student-in-class", "ClassController", "showStudentInClass");

		//TEACHER SECTION
		addRoute("edit-attendence", "UserController", "editAttendence");
		addRoute("delete-attendence", "UserController", "deleteAttendence");
		addRoute("edit-score", "UserController", "editScore");

		/**************************************************************************/
		linkTo("student-dashboard", "change-password");
		linkTo("student-dashboard", "check-in");
		linkTo("student-dashboard", "check-in-result");
		linkTo("student-dashboard", "view-schedule");
		linkTo("student-dashboard", "view-scoreboard");
		linkTo("student-dashboard", "log-out");

		linkTo("access", "login");
		linkTo("access", "register");

		//TEACHER SECTION
		linkTo("teacher-dashboard", "edit-attendence");
		linkTo("teacher-dashboard", "delete-attendence");
		linkTo("teacher-dashboard", "edit-score");
		
		linkTo("staff-dashboard", "import-class");
		linkTo("staff-dashboard", "view-class");
		linkTo("staff-dashboard", "view-student-in-class");
	}
};
#endif // ROUTES_H_INCLUDED