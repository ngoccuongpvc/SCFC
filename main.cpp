#include <iostream>
#include <stack>
#include <string>
#include <windows.system.h>

#include "app/Controller/ControllerInterface.h"
#include "app/Controller/AcademicController.h"
#include "app/Controller/AccountController.h"
#include "app/Controller/AttendanceController.h"
#include "app/Controller/AuthorizeController.h"
#include "app/Controller/ClassController.h"
#include "app/Controller/CourseController.h"
#include "app/Controller/ScoreboardController.h"
#include "app/Controller/UserController.h"
#include "app/Controller/Validation.h"

#include "app/View/Routes.h"
#include "app/View/View.h"

using namespace std;

/**
History, which contains both controller name and action name
*/
extern stack<string> history;

/**
create to corresponding instance by its name
*/
ControllerInterface *createInstance(string name)
{
    if (name == "UserController") {
        return new UserController();
    }
    else if (name == "ClassController") {
        return new ClassController();
    }
    else if (name == "AccountController") {
        return new AccountController();
    }
    else if (name == "AuthorizeController") {
        return new AuthorizeController();
    }
    else if (name == "CourseController") {
        return new CourseController();
    }
    else if (name == "ScoreboardController") {
        return new ScoreboardController();
    }
    else if (name == "AcademicController") {
        return new AcademicController();
    }
    else if (name == "AttendanceController") {
        return new AttendanceController();
    }
    return nullptr;
}

int main()
{
    /**
    set the default history
    */
    history.push("access");
    Routes *route = new Routes();
    /**
    this is just an example, we need to go forward or backward depend of what we put or pop to history
    */

    
    string path;

	/*TEST SITE FOR VIEW

	Validation *valid = new Validation();
	string day;
	valid->read(day, "term");
	cout << day;
	delete valid;

	/*END TEST SITE*/
    while (true) {
        if (history.empty()) {
            //history.push("access");
            break;
        }
        path = history.top();
        string controllerName = route->getController(path);
        string actionName = route->getAction(path);

        /**
        create the controller by controller interface
        */
        ControllerInterface* controller = createInstance(controllerName);
        controller->callMethod(actionName);
        delete controller;
        
        if (path == history.top()) {
            route->showOptions(path);
            int opt, nopt = route->getNumberOfOption(path);
            cout << "Choose your option: ";
            do {
                cin >> opt;

				string temp;
				getline(cin, temp);
				system("cls");

                if (!opt) {
                    history.pop(); //opt == 0
                    break;
                }
                else if (0 < opt && opt <= nopt) {
                    string nextPath = route->getOption(path, opt);
                    history.push(nextPath);
                    break;
                }
				cout << "Invalid option! Please try again: " << endl;
				route->showOptions(path);
				nopt = route->getNumberOfOption(path);
				cout << "Choose your option: ";
            } while (true);
        }
    }

    return 0;
}
