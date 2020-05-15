#include <iostream>
#include <stack>
#include <string>

#include "app/Controller/ControllerInterface.h"
#include "app/Controller/UserController.h"
#include "app/View/Routes.h"

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
    return nullptr;
}

int main()
{
    /**
    set the default history
    */
    history.push("login");
    Routes *route = new Routes();
    /**
    this is just an example, we need to go forward or backward depend of what we put or pop to history
    */

    
    string path;

    while (true) {
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
                history.pop();
            }
            else {
                string nextPath = route->getOption(path, opt);
                history.push(nextPath);
            }
        }
    }

    return 0;
}
