#ifndef ATTENDANCECONTROLLER_H_INCLUDED
#define ATTENDANCECONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"

class AttendanceController : public ControllerInterface {
private:
public:
    void viewAttendanceList() {
        AttendanceModel* am = new AttendanceModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string temp, courseId;
        cout << "Please enter the ID of the course that you want to edit: "; string courseIdentifier; cin >> courseIdentifier;
        cim->setCourseId(toLowerCase(courseIdentifier));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered could not be found." << endl;
            return;
        }
        courseId = results[0][0];
        vector<vector<string>> attendance;
        am->setCourseId(courseId);
        am->setDay("");
        results = am->FetchAttendance();
        if (results.size() == 0) {
            cout << "No students attended the given course, please recheck." << endl;
            return;
        }
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setCourseId(courseId);
        for (int i = 0; i < results.size(); ++i) {
            am_temp->setStudentId(results[i][1]);
            uim->setId(results[i][1]);
            vector<vector<string>> users = uim->FetchInfo();
            vector<string> attendanceOfOne;
            if (users.size() != 0) {
                attendanceOfOne.push_back(users[0][1]);
            }
            else attendanceOfOne.push_back("");
            vector<vector<string>> getBack = am->FetchAttendance();

            for (int k = 0; k < getBack.size(); ++k) {
                attendanceOfOne.push_back(getBack[k][3]);
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 0;
        for (int i = 0; i < attendance.size(); ++i) {
            if (attendance[i].size() > max_column) max_column = attendance[i].size();
        }
        vector<string> header; header.push_back("Course Name");
        for (int i = 0; i < max_column; ++i) header.push_back(" ");
        View* view = new View(attendance, header);
        view->displayTable();
        delete view;
        delete am;
        delete cim;
        delete view;
    }


    void exportAttendance() {

    }
    //--------------------------------xx Staff-Attendance xx--------------------------------//

    // Student

    //LECTURER/TEACHER

    void editAttendance()
    {
        cout << "Plz aware that you can edit the attendent's day of each student only" << endl;
        AttendanceModel* am = new AttendanceModel();
        string courseID, studentID;
        cout << "Plz enter the course ID: "; cin >> courseID; am->setCourseId(courseID);
        cout << "Plz enter the student ID: "; cin >> studentID; am->setStudentId(studentID);
        vector<vector<string>> conditions = am->FetchAttendance();

        if (conditions.size() == 0)
        {
            cout << "Unable to find this course/student!" << endl;
            delete am;
            return;
        }

        cout << "Plz enter the day of attendence for this student: ";
        string day; cin >> day;
        vector<string> record = conditions[0];
        record.back() = day;
        am->UpdateAttendance(&conditions[0], &record);
        delete am;
        return;
    }

    void deleteAttendance()
    {
        cout << "Plz aware that you can't recovery the deleted data. Do you want continue(Y/N)" << endl;
        string opt; cin >> opt;

        while (true)
        {
            if (opt == "Y") break;
            else if (opt == "N") return;
            else
            {
                cout << "Invalid input. Plz try again" << endl;
                cin >> opt;
            }
        }
        AttendanceModel* am = new AttendanceModel();
        string courseID, studentID;
        cout << "Plz enter the course ID: "; cin >> courseID; am->setCourseId(courseID);
        cout << "Plz enter the student ID: "; cin >> studentID; am->setStudentId(studentID);
        vector<vector<string>> conditions = am->FetchAttendance();

        if (conditions.size() == 0)
        {
            cout << "Unable to find this course/student!" << endl;
            delete am;
            return;
        }

        am->RemoveAttendance(&conditions[0]);
        delete am;
        return;
    }
    void checkIn() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        string studentIdentifier, courseId, studentId, day;
        cout << "Please enter the ID of the course that you want to edit: "; string courseIdentifier; cin >> courseIdentifier;
        cim->setCourseId(toLowerCase(courseIdentifier));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        cout << "Please enter your student Id: "; cin >> studentIdentifier;
        uim->setStudentID(toLowerCase(studentIdentifier));
        vector<vector<string>> studentResult = uim->FetchInfo();
        if (studentResult.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        studentId = studentResult[0][0];
        am->setStudentId(studentId);
        am->setCourseId(courseId);
        am->setDay("");
        vector<vector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in this course." << endl;
            return;
        }
        cout << "Please enter the day you are checking in: "; cin >> day;
        am->setDay(day);
        am->AddAttendance();
        cout << "Successfully added your checkin." << endl;
        delete uim;
        delete am;
        delete cim;
    }

    void viewCheckInResult() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        string courseName, studentIdentifier, courseId, studentId, day;
        cout << "Please enter your student Id: "; cin >> studentIdentifier;
        uim->setStudentID(toLowerCase(studentIdentifier));
        vector<vector<string>> studentResult = uim->FetchInfo();
        if (studentResult.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        studentId = studentResult[0][0];
        am->setStudentId(studentId);
        am->setDay("");
        vector<vector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in any course." << endl;
            return;
        }
        vector<vector<string>> attendance;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setStudentId(studentId);
        for (int i = 0; i < enrollment.size(); ++i) {
            cim->setId(enrollment[i][2]);
            vector<vector<string>> courses = cim->FetchCourse();
            vector<string> attendanceOfOne;
            attendanceOfOne.push_back(courses[0][1]);
            am_temp->setCourseId(enrollment[i][2]);
            vector<vector<string>> days = am_temp->FetchAttendance();
            for (int k = 0; k < days.size(); ++k) {
                attendanceOfOne.push_back(days[k][3]);
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 0;
        for (int i = 0; i < attendance.size(); ++i) {
            if (attendance[i].size() > max_column) max_column = attendance[i].size();
        }
        vector<string> header; header.push_back("Course Name");
        for (int i = 0; i < max_column; ++i) header.push_back(" ");
        View* view = new View(attendance, header);
        view->displayTable();
        delete view;
        delete uim;
        delete cim;
        delete am;
    }

    AttendanceController() {
        this->mapMethods["checkIn"] = [this]() { checkIn(); };
        this->mapMethods["deleteAttendance"] = [this]() { deleteAttendance(); };
        this->mapMethods["editAttendance"] = [this]() { editAttendance(); };
        this->mapMethods["exportAttendance"] = [this]() { exportAttendance(); };
        this->mapMethods["viewAttendanceList"] = [this]() { viewAttendanceList(); };
        this->mapMethods["viewCheckInResult"] = [this]() { viewCheckInResult(); };
    }

};

#endif