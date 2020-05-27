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
        cout << "Please enter the ID of the course that you want to view attendance list: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            delete am;
            delete cim;
            return;
        }
        vector<vector<string>> attendance;
        am->setCourseId(courseId);
        am->setDay("");
        vector<vector<string>> results = am->FetchAttendance();
        if (results.size() == 0) {
            cout << "No students attended the given course, please recheck." << endl;
            delete am;
            delete cim;
            return;
        }
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setCourseId(courseId);
        for (int i = 0; i < results.size(); ++i) {
            am_temp->setStudentId(results[i][1]);
            uim->setStudentId(results[i][1]);
            vector<vector<string>> users = uim->FetchInfo();
            vector<string> attendanceOfOne(11, "0");
            if (users.size() != 0) {
                attendanceOfOne[0] = users[0][1];
            }
            else attendanceOfOne.push_back("");
            vector<vector<string>> getBack = am_temp->FetchAttendance();

            for (int k = 0; k < getBack.size(); ++k) {
                if (getBack[k][3] != "")
                    attendanceOfOne[stoi(getBack[k][3])] = "1";
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 10;
        vector<string> header; header.push_back("Student ID");
        for (int i = 0; i < max_column; ++i) header.push_back("Day " + to_string(i + 1));
        View* view = new View(attendance, header);
        view->displayTable();
        delete view;
        delete am;
        delete cim;
        delete uim;
    }


    void exportAttendance() {
        cout << "Choose file to export to: ";
        string path;
        cin >> path;
        AttendanceModel* am = new AttendanceModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string temp, courseId;
        cout << "Please enter the ID of the course that you want to edit: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            delete am;
            delete cim;
            delete uim;
            return;
        }
        vector<vector<string>> attendance;
        am->setCourseId(courseId);
        am->setDay("");
        vector<vector<string>> results = am->FetchAttendance();
        if (results.size() == 0) {
            cout << "No students attended the given course, please recheck." << endl;
            delete am;
            delete cim;
            delete uim;
            return;
        }
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setCourseId(courseId);
        for (int i = 0; i < results.size(); ++i) {
            am_temp->setStudentId(results[i][1]);
            uim->setStudentId(results[i][1]);
            vector<vector<string>> users = uim->FetchInfo();
            vector<string> attendanceOfOne(11, "0");
            if (users.size() != 0) {
                attendanceOfOne[0] = users[0][1];
            }
            else attendanceOfOne.push_back("");
            vector<vector<string>> getBack = am_temp->FetchAttendance();

            for (int k = 0; k < getBack.size(); ++k) {
                if (getBack[k][3] != "")
                    attendanceOfOne[stoi(getBack[k][3])] = "1";
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 10;
        vector<string> header; header.push_back("Student ID");
        for (int i = 0; i < max_column; ++i) header.push_back("Day " + to_string(i + 1));
        View* view = new View(attendance, header);
        view->setPath(path);
        view->exportTable();
        delete view;
        delete am;
        delete uim;
        delete cim;
    }


    void editAttendance()
    {
        cout << "Please be aware that you can add one attendance of a student at a time" << endl;
        AttendanceModel* am = new AttendanceModel();
        string courseID, studentID;
        cout << "Please enter the course ID: "; getline(cin, courseID); am->setCourseId(toLowerCase(courseID));
        cout << "Please enter the student ID: "; getline(cin, studentID); am->setStudentId(toLowerCase(studentID));
        vector<vector<string>> conditions = am->FetchAttendance();

        if (conditions.size() == 0)
        {
            cout << "Unable to find this course/student!" << endl;
            delete am;
            return;
        }

        cout << "Please enter the day of attendance for this student(1-10): ";
        string day; cin >> day;
        am->setDay(day);
        am->AddAttendance();
        delete am;
        return;
    }

    void deleteAttendance()
    {
        
        cout << "Provide information to delete attendance of a student" << endl;
        /*
        string opt; cin >> opt;

        while (true)
        {
            if (opt == "Y") break;
            else if (opt == "N") return;
            else
            {
                cout << "Invalid input. Please try again" << endl;
                cin >> opt;
            }
        }
        */
        AttendanceModel* am = new AttendanceModel();
        string courseID, studentID, day;
        cout << "Please enter the course ID: "; getline(cin, courseID); am->setCourseId(toLowerCase(courseID));
        cout << "Please enter the student ID: "; getline(cin, studentID); am->setStudentId(toLowerCase(studentID));
        cout << "Please enter the day to delete attendance of this student(1-10): "; cin >> day; am->setDay(toLowerCase(day));
        vector<vector<string>> conditions = am->FetchAttendance();

        if (conditions.size() == 0)
        {
            cout << "Unable to find this course/student/day!" << endl;
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
        string courseId, studentId = globalUsername, day;
        cout << "Please enter the ID of the course that you want to check in: ";  getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        vector<vector<string>> temp = cim->FetchCourse();
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete uim;
            delete am;
            delete cim;
            return;
        }
        //cout << "Please enter your student Id: "; cin >> studentId;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete uim;
            delete am;
            delete cim;
            return;
        }
        am->setStudentId(studentId);
        am->setCourseId(courseId);
        am->setDay("");
        vector<vector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in this course." << endl;
            delete uim;
            delete am;
            delete cim;
            return;
        }
        cout << "Please enter the day you are checking in (1-10): ";  getline(cin, day);
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
        string courseName, courseId, studentId = globalUsername, day;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete uim;
            delete cim;
            delete am;
            return;
        }
        am->setStudentId(studentId);
        am->setDay("");
        vector<vector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in any course." << endl;
            delete uim;
            delete cim;
            delete am;
            return;
        }
        vector<vector<string>> attendance;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setStudentId(studentId);
        for (int i = 0; i < enrollment.size(); ++i) {
            cim->setCourseId(enrollment[i][2]);
            vector<vector<string>> courses = cim->FetchCourse();
            vector<string> attendanceOfOne(11, "0");
            attendanceOfOne[0] = courses[0][1];
            am_temp->setCourseId(enrollment[i][2]);
            vector<vector<string>> days = am_temp->FetchAttendance();
            for (int k = 0; k < days.size(); ++k) {
                if (days[k][3] != "")
                attendanceOfOne[stoi(days[k][3])] = "1";
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 10;
        /*
        for (int i = 0; i < attendance.size(); ++i) {
            if (attendance[i].size() > max_column) max_column = attendance[i].size();
        }
        */
        vector<string> header; header.push_back("Course Name");
        for (int i = 0; i < max_column; ++i) header.push_back("Day" + to_string(i+1));
        View* view = new View(attendance, header);
        view->displayTable();
        delete view;
        delete uim;
        delete cim;
        delete am;
    }

    AttendanceController() {
        this->mapMethods["checkIn"] = [this]() { checkIn(); };
        this->mapMethods["exportAttendance"] = [this]() {exportAttendance();  };
        this->mapMethods["deleteAttendance"] = [this]() { deleteAttendance(); };
        this->mapMethods["editAttendance"] = [this]() { editAttendance(); };
        this->mapMethods["exportAttendance"] = [this]() { exportAttendance(); };
        this->mapMethods["viewAttendanceList"] = [this]() { viewAttendanceList(); };
        this->mapMethods["viewCheckInResult"] = [this]() { viewCheckInResult(); };
    }

};

#endif