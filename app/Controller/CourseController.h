#ifndef COURSECONTROLLER_H_INCLUDED
#define COURSECONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"

class CourseController : public ControllerInterface {
private:
public:
    void viewAllCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> results = cim->FetchCourse();
        vector<string> header = cim->columns;
        for (int i = 0; i < header.size(); ++i) header[i] = capitalize(header[i]);
        View* view = new View(results, header);
        view->displayTable();
        delete view;
    }

};

#endif // 
