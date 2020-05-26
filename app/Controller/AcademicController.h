#ifndef ACADEMICCONTROLLER_H_INCLUDED
#define ACADEMICCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"

class AcademicController : public ControllerInterface {
private:
public:
    void showYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "No courses was entered in the year you entered." << endl;
            delete cim;
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
            delete cim;
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

    void viewSchedule() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        string courseName, studentIdentifier, courseId, studentId, day;
		//fllusing
		//string temp;
		//getline(cin, temp);
        cout << "Please enter your student Id: "; getline(cin, studentId);
        am->setStudentId(studentId);
        am->setDay("");
        uim->setStudentId(toLowerCase(studentId));
        vector<vector<string>> results = uim->FetchInfo();
        if (results.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete cim;
            delete uim;
            delete am;
            return;
        }
        vector<vector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in any course." << endl;
            delete cim;
            delete uim;
            delete am;
            return;
        }
        vector<vector<string>> schedules;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setStudentId(studentId);
        for (int i = 0; i < enrollment.size(); ++i) {
            cim->setCourseId(enrollment[i][2]);
            vector<string> course = cim->FetchCourse()[0];
            vector<string> schedule;
            schedule.push_back(course[1]);
            schedule.push_back(course[11]);
            string dailyHour = course[6] + "-" + course[7];
            string studyPeriod = course[4] + "-" + course[5];
            schedule.push_back(dailyHour);
            schedule.push_back(studyPeriod);
            schedules.push_back(schedule);
        }
        int max_column = 0;
        for (int i = 0; i < schedules.size(); ++i) {
            if (schedules[i].size() > max_column) max_column = schedules[i].size();
        }
        vector<string> header; header.push_back("Course Name");
        header.push_back("Day Of Week"); header.push_back("Daily Hour");
        header.push_back("Study Period");
        View* view = new View(schedules, header);
        view->displayTable();
        delete uim;
        delete cim;
        delete am;
        delete am_temp;
        delete view;
    }

    AcademicController() {
        this->mapMethods["showSemester"] = [this]() { showSemester(); };
        this->mapMethods["showYear"] = [this]() { showYear(); };
        this->mapMethods["viewSchedule"] = [this]() { viewSchedule(); };
    }
};

#endif