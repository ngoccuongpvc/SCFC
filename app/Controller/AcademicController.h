#ifndef ACADEMICCONTROLLER_H_INCLUDED
#define ACADEMICCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "ClassController.h"
#include "CourseController.h"
#include "ScoreboardController.h"


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
        myVector<myVector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "No courses was entered in the year you entered." << endl;
            delete cim;
            return;
        }
        myVector<string> years;
        for (int i = 0; i < results.size(); ++i) {
            for (int k = 0; k < years.size(); ++k) {
                if (years[k] != results[i][10]) {
                    years.push_back(results[i][10]);
                    break;
                }
            }
        }
        myVector<myVector<string>> info;
        info.push_back(years);
        myVector<string> header; header.push_back("Year");
        View* view = new View(info, header);
        view->displayTable();
        delete view;
    }


    void showSemester() {
        if (role != "staff") return;
        CourseInformationModel* cim = new CourseInformationModel();
        myVector<myVector<string>> listCourses = cim->FetchCourse();
        if (listCourses.size() == 0) {
            cout << "No courses found in the semester you entered." << endl;
            delete cim;
            return;
        }
        myVector<string> semesters;
        for (int i = 0; i < listCourses.size(); ++i) {
            for (int k = 0; k < semesters.size(); ++k) {
                if (listCourses[i][9] != semesters[k])
                    semesters.push_back(listCourses[i][9]);
            }
        }
        myVector<myVector<string>> info;
        info.push_back(semesters);
        myVector<string> header; header.push_back("Semester");
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
        //cout << "Please enter your student Id: "; getline(cin, studentId);
        am->setStudentId(globalUsername);
        am->setDay("");
        uim->setStudentId(globalUsername);
        myVector<myVector<string>> results = uim->FetchInfo();
        if (results.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete cim;
            delete uim;
            delete am;
            return;
        }
        myVector<myVector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in any course." << endl;
            delete cim;
            delete uim;
            delete am;
            return;
        }
        myVector<myVector<string>> schedules;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setStudentId(studentId);
        for (int i = 0; i < enrollment.size(); ++i) {
            cim->setCourseId(enrollment[i][2]);
            myVector<string> course = cim->FetchCourse()[0];
            myVector<string> schedule;
            schedule.push_back(course[1]);
            schedule.push_back(course[11]);
            string dailyHour = course[4] + "-" + course[5];
            string studyPeriod = course[6] + "-" + course[7];
            schedule.push_back(dailyHour);
            schedule.push_back(studyPeriod);
            schedules.push_back(schedule);
        }
        int max_column = 0;
        for (int i = 0; i < schedules.size(); ++i) {
            if (schedules[i].size() > max_column) max_column = schedules[i].size();
        }
        myVector<string> header; header.push_back("Course Name");
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

    void importDatabase() {
        ClassController* classC = new ClassController();
        CourseController* courseC = new CourseController();
        ScoreboardController* scoreC = new ScoreboardController();
        string opt = "";
        cout << "Import the list of students(Y/N): "; getline(cin, opt);
        if (opt == "Y" || opt == "y")
        classC->importAction();
        cout << "Import the list of courses(Y/N): "; getline(cin, opt);
        if (opt == "Y" || opt == "y")
        courseC->importCourse();
        cout << "Import the list of scores(Y/N): "; getline(cin, opt);
        if (opt == "Y" || opt == "y")
        scoreC->importScoreboard();

        delete classC;
        delete courseC;
        delete scoreC;

    }

    void dropDatabase() {
        //AccountModel* acm = new AccountModel();
        AttendanceModel* atm = new AttendanceModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        ScoreboardModel* sm = new ScoreboardModel();
        ClassModel* cm = new ClassModel();

        //acm->removeAccount();
        atm->RemoveAttendance();
        cim->RemoveCourse();
        uim->RemoveUser();
        sm->DeleteScore();
        cm->RemoveClass();

        delete atm;
        delete cim;
        delete uim;
        delete sm;
        delete cm;

        cout << "Successfully dropped all databases. You can now import safely." << endl;
    }

    AcademicController() {
        this->mapMethods["showSemester"] = [this]() { showSemester(); };
        this->mapMethods["showYear"] = [this]() { showYear(); };
        this->mapMethods["viewSchedule"] = [this]() { viewSchedule(); };
        this->mapMethods["importDatabase"] = [this]() {importDatabase(); };
        this->mapMethods["dropDatabase"] = [this]() {dropDatabase(); };
    }
};

#endif