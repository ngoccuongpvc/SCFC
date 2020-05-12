#ifndef CONTROLLERINTERFACE_H_INCLUDED
#define CONTROLLERINTERFACE_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "../History.h"

using namespace std;

class ControllerInterface {
protected:
    /**
    this map is used to map method's name to function
    */
    map<string, function<void()>> mapMethods;
public:
    ControllerInterface() {
    }

    /**
    call the method of controller by their name
    but we need to method's name to its function in mapMethods map
    */
    void callMethod(string methodName) {
        if (mapMethods.count(methodName)) {
            mapMethods[methodName]();
        }
    }

};

#endif // CONTROLLERINTERFACE_H_INCLUDED
