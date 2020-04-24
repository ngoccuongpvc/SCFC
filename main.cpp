#include <bits/stdc++.h>
#include "app/Controller/ControllerInterface.h"
#include "app/Controller/UserController.h"
using namespace std;

/**
History, which contains both controller name and action name
*/
stack<pair<string,string>> History;

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
    History.push(make_pair<string,string>("UserController", "mainAction"));

    /**
    this is just an example, we need to go forward or backward depend of what we put or pop to history
    */
    while (true) {
        string controllerName = History.top().first;
        string actionName = History.top().second;

        /**
        create the controller by controller interface
        */
        ControllerInterface *controller = createInstance(controllerName);
        controller->callMethod(actionName);

        delete controller;
        break;
    }
    return 0;
}
