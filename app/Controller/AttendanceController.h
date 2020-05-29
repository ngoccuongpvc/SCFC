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
#include "Validation.h"

class AttendanceController : public ControllerInterface {
private:
	Validation* valid = new Validation();
public:
    void viewAttendanceList() {
        AttendanceModel* am = new AttendanceModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string temp, courseId;
        cout << "Please enter the ID of the course that you want to view attendance list: "; 
		valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            delete am;
            delete cim;
            return;
        }
        myVector<myVector<string>> attendance;
        am->setCourseId(courseId);
        am->setDay("");
        myVector<myVector<string>> results = am->FetchAttendance();
        if (results.size() == 0) {
            cout << "No students attended the given course, please recheck." << endl;
            delete am;
            delete cim;
            return;
        }
        cout << "The attendance list will be given below, in which '0' indicates absence, '1' for having checked in." << endl;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setCourseId(courseId);
        for (int i = 0; i < results.size(); ++i) {
            am_temp->setStudentId(results[i][1]);
            uim->setStudentId(results[i][1]);
            myVector<myVector<string>> users = uim->FetchInfo();
            myVector<string> attendanceOfOne(11, "0");
            if (users.size() != 0) {
                attendanceOfOne[0] = users[0][1];
            }
            else attendanceOfOne.push_back("");
            myVector<myVector<string>> getBack = am_temp->FetchAttendance();

            for (int k = 0; k < getBack.size(); ++k) {
                if (getBack[k][3] != "") {
                    int dayT = stoi(getBack[k][3]);
                    if (dayT >= 1 && dayT <= 10) attendanceOfOne[dayT] = "1";
                }
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 10;
        myVector<string> header; header.push_back("Student ID");
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
        cout << "Please enter the ID of the course that you want to edit: "; valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            delete am;
            delete cim;
            delete uim;
            return;
        }
        myVector<myVector<string>> attendance;
        am->setCourseId(courseId);
        am->setDay("");
        myVector<myVector<string>> results = am->FetchAttendance();
        if (results.size() == 0) {
            cout << "No students attended the given course, please recheck." << endl;
            delete am;
            delete cim;
            delete uim;
            return;
        }
        cout << "The attendance list will be given below, in which '0' indicates absence, '1' for having checked in." << endl;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setCourseId(courseId);
        for (int i = 0; i < results.size(); ++i) {
            am_temp->setStudentId(results[i][1]);
            uim->setStudentId(results[i][1]);
            myVector<myVector<string>> users = uim->FetchInfo();
            myVector<string> attendanceOfOne(11, "0");
            if (users.size() != 0) {
                attendanceOfOne[0] = users[0][1];
            }
            else attendanceOfOne.push_back("");
            myVector<myVector<string>> getBack = am_temp->FetchAttendance();

            for (int k = 0; k < getBack.size(); ++k) {
                if (getBack[k][3] != "") {
                    int dayT = stoi(getBack[k][3]);
                    if (dayT >= 1 && dayT <= 10) attendanceOfOne[dayT] = "1";
                }
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 10;
        myVector<string> header; header.push_back("Student ID");
        for (int i = 0; i < max_column; ++i) header.push_back("Day " + to_string(i + 1));
        View* view = new View(attendance, header);
        view->setPath(path);
        view->exportTable();
        delete view;
        delete am;
        delete uim;
        delete cim;
    }

    void showAttendance(string courseId, string studentId) {
        myVector<myVector<string>> attendance;
        AttendanceModel* am = new AttendanceModel();
        am->setCourseId(courseId);
        am->setStudentId(studentId);
   
        myVector<string> attendanceOfOne(10, "0");
        myVector<myVector<string>> days = am->FetchAttendance();
        for (int k = 0; k < days.size(); ++k) {
            if (days[k][3] != "") {
                int dayT = stoi(days[k][3]);
                if (dayT >= 1 && dayT <= 10) attendanceOfOne[dayT-1] = "1";
            }
        }
        attendance.push_back(attendanceOfOne);
        
        int max_column = 10;
        myVector<string> header;
        for (int i = 0; i < max_column; ++i) header.push_back("Day" + to_string(i + 1));
        View* view = new View(attendance, header);
        view->displayTable();
        delete view;
        delete am;
    }


    void editAttendance()
    {
        cout << "Please be aware that you can add one attendance of a student at a time" << endl;
        AttendanceModel* am = new AttendanceModel();
        string courseID, studentID;
        cout << "Please enter the course ID: ";  valid->read(courseID, "nospc");  am->setCourseId(courseID);
        cout << "Please enter the student ID: "; valid->read(studentID, "nospc"); am->setStudentId(studentID);
        myVector<myVector<string>> conditions = am->FetchAttendance();

        if (conditions.size() == 0)
        {
            cout << "Unable to find this course/student!" << endl;
            delete am;
            return;
        }
        cout << "Below is the list of attendance for this student in the entered course:" << endl;

        showAttendance(courseID, studentID);

        cout << "Please enter the day of attendance for this student(1-10): ";
		string day; valid->read(day, "day");
        am->setDay(day);
        am->AddAttendance();
        cout << "Successfully updated the attendance." << endl;
        delete am;
        return;
    }

    void deleteAttendance()
    {
        
        cout << "Provide information to delete attendance of a student" << endl;
        AttendanceModel* am = new AttendanceModel();
        string courseID, studentID, day;
        cout << "Please enter the course ID: ";   valid->read(courseID, "nospc");  am->setCourseId(courseID);
		cout << "Please enter the student ID: ";  valid->read(studentID, "nospc"); am->setStudentId(studentID);
        cout << "Below is the list of attendance for this student in the entered course:" << endl;

        showAttendance(courseID, studentID);
		cout << "Please enter the day to delete attendance of this student(1-10): "; valid->read(day, "day"); am->setDay(day);
        myVector<myVector<string>> conditions = am->FetchAttendance();

        if (conditions.size() == 0)
        {
            cout << "Unable to find this course/student/day!" << endl;
            delete am;
            return;
        }    

        am->RemoveAttendance(&conditions[0]);
        delete am;
        cout << "Successfully deleted the attendance." << endl;
        return;
    }

    void checkIn() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        string courseId, studentId = globalUsername, day;
        cout << "Please enter the ID of the course that you want to check in: ";   valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        myVector<myVector<string>> temp = cim->FetchCourse();
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete uim;
            delete am;
            delete cim;
            return;
        }
        //cout << "Please enter your student Id: "; cin >> studentId;
        uim->setStudentId(studentId);
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
        myVector<myVector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in this course." << endl;
            delete uim;
            delete am;
            delete cim;
            return;
        }
        cout << "Please enter the day you are checking in (1-10): ";  valid->read(day, "day");
        am->setDay(day);
        enrollment = am->FetchAttendance();
        if (enrollment.size() != 0) {
            cout << "You have already checked in for this day in the course, please try again." << endl;
        }
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
        uim->setStudentId(studentId);
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete uim;
            delete cim;
            delete am;
            return;
        }
        am->setStudentId(studentId);
        am->setDay("");
        myVector<myVector<string>> enrollment = am->FetchAttendance();
        if (enrollment.size() == 0) {
            cout << "You are not enrolled in any course." << endl;
            delete uim;
            delete cim;
            delete am;
            return;
        }
        cout << "The attendance list will be given below, in which '0' indicates absence, '1' for having checked in." << endl;
        myVector<myVector<string>> attendance;
        AttendanceModel* am_temp = new AttendanceModel();
        am_temp->setStudentId(studentId);
        for (int i = 0; i < enrollment.size(); ++i) {
            cim->setCourseId(enrollment[i][2]);
            myVector<myVector<string>> courses = cim->FetchCourse();
            myVector<string> attendanceOfOne(11, "0");
            attendanceOfOne[0] = courses[0][1];
            am_temp->setCourseId(enrollment[i][2]);
            myVector<myVector<string>> days = am_temp->FetchAttendance();
            for (int k = 0; k < days.size(); ++k) {
                if (days[k][3] != "") {
                    int dayT = stoi(days[k][3]);
                    if (dayT >= 1 && dayT <= 10) attendanceOfOne[dayT] = "1";
                }
            }
            attendance.push_back(attendanceOfOne);
        }
        int max_column = 10;
        /*
        for (int i = 0; i < attendance.size(); ++i) {
            if (attendance[i].size() > max_column) max_column = attendance[i].size();
        }
        */
        myVector<string> header; header.push_back("Course Name");
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

	~AttendanceController()
	{
		delete valid;
	}

};

#endif