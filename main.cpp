#include <iostream>
#include <stack>
#include <string>
#include <windows.system.h>

#include "app/Controller/ControllerInterface.h"
#include "app/Controller/UserController.h"
#include "app/Controller/TeacherController.h"
#include "app/Controller/ClassController.h"
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
	else if (name == "TeacherController") {
		return new TeacherController();
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

	vector<string> col = { "col1", "col2", "col3" };
	vector<vector<string>> data = { {"19", "hung","18"}, {"579844", "welll this must be the shortest","18"}, {"1", "hu","hu"} };

	View viewModel = View(data, col);
	viewModel.displayTable();
	viewModel.exportTable();

	/*END TEST SITE*/
    while (true) {
        if (history.empty()) {
            history.push("access");
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
            int opt;
            cout << "Choose your option: ";
            cin >> opt;
            if (!opt) {
                history.pop(); //opt == 0
            }
            else {
                string nextPath = route->getOption(path, opt);
                history.push(nextPath);
            }
        }
    }

    return 0;
}
