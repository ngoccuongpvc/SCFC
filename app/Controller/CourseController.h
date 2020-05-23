#ifndef COURSECONTROLLER_H_INCLUDED
#define COURSECONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"

class CourseController : public ControllerInterface {
private:
public:

    void importAction() {
        cout << "Choose file: ";
        string path;
        cin >> path;
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        UserInfoModel* uim = new UserInfoModel();

        ModelInterface* model = new ModelInterface(path);
        vector<vector<string>> records = model->fetch();

        for (vector<string> record : records) {
            cim->setCourseId(record[1]);
            cim->setCourseName(record[2]);
            cim->setClassName(record[3]);
            cim->setLecturerAccount(record[4]);
            cim->setStartDay(record[5]);
            cim->setEndDay(record[6]);
            cim->setDayOfWeek(record[7]);
            cim->setStartHour(record[8]);
            cim->setEndHour(record[9]);
            cim->setRoom(record[10]);
            cim->AddCourse();

            am->setCourseId(record[1]);
            am->setDay("");
            vector<vector<string>> students = uim->FetchInfo();
            for (int i = 0; i < students.size(); ++i) {
                if (students[i][1] != "") {
                    am->setStudentId(students[i][1]);     
                    am->AddAttendance();
                }
            }

        }

        cout << "Imported Successfully" << endl;
    }

    void viewAllCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        vector<vector<string>> results = cim->FetchCourse();
        vector<string> header = cim->columns;
        for (int i = 0; i < header.size(); ++i) header[i] = capitalize(header[i]);
        View* view = new View(results, header);
        view->displayTable();
        delete view;
    }

    void removeCourseByYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the academic year that you want to remove: "; cin >> year;
        cim->setYear(toLowerCase(year));
        vector<vector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            cim->RemoveCourse(&results[i]);
        }
        cout << "Successfully remove all course in the year " << year;
        delete cim;
    }

    void removeCourseBySemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        string semester;
        cout << "Please enter the semester that you want to remove: "; cin >> semester;
        cim->setSemester(toLowerCase(semester));
        vector<vector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            cim->RemoveCourse(&results[i]);
        }
        cout << "Successfully remove all course in the semester " << semester;
        delete cim;
    }

    void addCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        AccountModel* am = new AccountModel();
        string temp, temp2;
        cout << "Course ID: "; cin >> temp2;
        cout << "Course name: "; cin >> temp; cim->setCourseName(toLowerCase(temp));
        cout << "Course id: "; cin >> temp; cim->setCourseId(toLowerCase(temp));
        cout << "Class name: "; cin >> temp; cim->setClassName(toLowerCase(temp));

        cout << "Lecturer Account: "; cin >> temp;
        // Check if the lecturer account is available
        am->setUserName(toLowerCase(temp));
        vector<vector<string>> results = am->fetchAccount();
        if (results.size() == 0) {
            cout << "The lecturer account is not found, returning..." << endl;
            return;
        }
        cout << "Start day: "; cin >> temp; cim->setStartDay(toLowerCase(temp));
        cout << "End day: "; cin >> temp; cim->setEndDay(toLowerCase(temp));
        cout << "Start hour: "; cin >> temp; cim->setStartHour(toLowerCase(temp));
        cout << "End hour: "; cin >> temp; cim->setEndHour(toLowerCase(temp));
        cout << "Day of week: "; cin >> temp; cim->setEndHour(toLowerCase(temp));
        cout << "Room: "; cin >> temp; cim->setRoom(toLowerCase(temp));
        cout << "Semester: "; cin >> temp; cim->setSemester(toLowerCase(temp));
        cout << "Year: "; cin >> temp; cim->setYear(toLowerCase(temp));
        cim->setCourseName(toLowerCase(temp2));
        cim->AddCourse();
        cout << "Successfully added the course." << endl;
        delete cim;
        delete am;
    }

    void editCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        cout << "Please enter the ID of the course that you want to edit: "; string courseId; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered does not exist. Please retry." << endl;
            delete cim; //check if crash
            return;
        }
        vector<string> record = results[0];
        cout << "Please enter the information that you want to change about this course. Press enter if you don't want to change that info.." << endl;
        string temp, temp2;
        vector<string> toUpdate;
        toUpdate.push_back(record[0]);
        cout << "Course ID: ";  cin >> temp2; 
        cout << "Course name: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));   
        cout << "Class name: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Lecturer account: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Start hour: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "End hour: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Start day: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "End day: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Day of week: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Room: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Semester: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        cout << "Year: ";  cin >> temp; toUpdate.push_back(toLowerCase(temp));
        toUpdate.push_back(toLowerCase(temp2));
        cim->UpdateCourse(&record, &toUpdate);
        cout << "Successfully updated the course." << endl;
        delete cim;
    }

    void removeCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        cout << "Please enter the ID of the course that you want to edit: "; string courseId; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered doesn't exist, please recheck." << endl;
            return;
        }
        cim->RemoveCourse(&courseResult[0]);
        cout << "Successfully removed the course " << courseId << endl;
        delete cim;
    }

    void listOfCourseCurrentSemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        string semester;
        cout << "Please enter the semester that you want to view the list of courses of: "; cin >> semester;
        cim->setSemester(toLowerCase(semester));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The semester doesn't exist or you haven't added any course to this semester yet!" << endl;
            return;
        }
        vector<vector<string>> courses;
        for (int i = 0; i < results.size(); ++i) {
            vector<string> info;
            info.push_back(results[i][1]);
            info.push_back(results[i][12]);
            courses.push_back(info);
        }
        vector<string> header; header.push_back("Course Name");
        header.push_back("Course ID");
        View* view = new View(courses, header);
        view->displayTable();
        delete cim;
        delete view;
    }

    void listOfCourseCurrentYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the year that you want to view the list of courses of: "; cin >> year;
        cim->setYear(toLowerCase(year));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The semester doesn't exist or you haven't added any course to this semester yet!" << endl;
            return;
        }
        vector<vector<string>> courses;
        for (int i = 0; i < results.size(); ++i) {
            vector<string> info;
            info.push_back(results[i][1]);
            info.push_back(results[i][12]);
            courses.push_back(info);
        }
        vector<string> header; header.push_back("Course Name");
        header.push_back("Course ID");
        View* view = new View(courses, header);
        view->displayTable();
        delete cim;
        delete view;
    }

    void removeStudentFromCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        string courseId, studentId;
        cout << "Please enter the ID of the course that you want to edit: "; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        cout << "Please enter the student ID of the student you want to remove from this course: "; cin >> studentId;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        am->setCourseId(courseId);
        am->setStudentId(studentId);
        vector<vector<string>> attendance = am->FetchAttendance();
        for (int i = 0; i < attendance.size(); ++i) {
            am->RemoveAttendance(&attendance[i]);
        }
        sm->setCourseId(courseId);
        sm->setStudentId(studentId);
        vector<vector<string>> scoreboard = sm->FetchScoreboard();
        for (int i = 0; i < scoreboard.size(); ++i) {
            sm->DeleteScore(&scoreboard[i]);
        }
        cout << "Successfully removed the student." << endl;
        delete cim;
        delete am;
        delete uim;
        delete sm;
    }

    void addStudentToCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        string courseId, studentId;
        cout << "Please enter the ID of the course that you want to edit: "; string courseId; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        cout << "Please enter the student ID of the student you want to add into this course: "; cin >> studentId;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        am->setCourseId(courseId);
        am->setStudentId(studentId);
        if (am->FetchAttendance().size() != 0) {
            cout << "The student is already enrolled into this course." << endl;
            return;
        }
        am->setDay("");
        am->AddAttendance();

        sm->setCourseId(courseId);
        sm->setStudentId(studentId);
        if (sm->FetchScoreboard().size() != 0) {
            cout << "The student is already enrolled into this course." << endl;
            return;
        }
        sm->setTerm("");
        sm->setScore("");
        sm->AddScore();

        cout << "Successfully added the student to the course." << endl;

        delete cim;
        delete am;
        delete uim;

    }

    void viewListOfStudentsOfCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        string temp, courseId;
        cout << "Please enter the ID of the course that you want to edit: "; string courseId; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            return;
        }
        vector<vector<string>> students;
        am->setCourseId(courseId);
        am->setDay("");
        vector<vector<string>> results = am->FetchAttendance();
        for (int i = 0; i < results.size(); ++i) {
            uim->setStudentId(results[i][1]);
            vector<vector<string>> getBack = uim->FetchInfo();
            if (getBack.size() != 0) {
                students.push_back(getBack[0]);
            }
        }

        vector<string> header = uim->columns;
        for (int i = 0; i < header.size(); ++i) {
            header[i] = capitalize(header[i]);
        }
        View* view = new View(students, header);
        view->displayTable();
        delete cim;
        delete uim;
        delete am;
        delete view;
    }

    CourseController() {
        this->mapMethods["addCourse"] = [this]() { addCourse(); };
        this->mapMethods["addStudentToCourse"] = [this]() { addStudentToCourse(); };
        this->mapMethods["editCourse"] = [this]() { editCourse(); };
        this->mapMethods["listOfCourseCurrentSemester"] = [this]() { listOfCourseCurrentSemester(); };
        this->mapMethods["listOfCourseCurrentYear"] = [this]() {listOfCourseCurrentYear(); };
        this->mapMethods["removeCourse"] = [this]() { removeCourse(); };
        this->mapMethods["removeCourseBySemester"] = [this]() { removeCourseBySemester(); };
        this->mapMethods["removeCourseByYear"] = [this]() { removeCourseByYear(); };
        this->mapMethods["removeStudentFromCourse"] = [this]() { removeStudentFromCourse(); };
        this->mapMethods["viewAllCourse"] = [this]() { viewAllCourse(); };
        this->mapMethods["viewListOFStudentsOfCourse"] = [this]() { viewListOfStudentsOfCourse(); };
    }
    

};

#endif // 
