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

    void importCourse() {
        cout << "Choose file: ";
        string path;
        cin >> path;
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ClassModel* cm = new ClassModel();
        ScoreboardModel* sm = new ScoreboardModel();

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
            sm->setCourseId(record[1]);
            sm->setScore("");
            sm->setTerm("");
            vector<string> students = cm->getStudentInClass(record[3]);
            for (int i = 0; i < students.size(); ++i) {
                am->setStudentId(students[i]);  
                am->AddAttendance();
                sm->setStudentId(students[i]);
                sm->AddScore();
            }

        }

        delete cim;
        delete am;
        delete cm;
        delete sm;
        delete model;

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
        delete cim;
    }

    void removeCourseByYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the academic year that you want to remove: "; cin >> year;
        cim->setYear(toLowerCase(year));
        vector<vector<string>> results = cim->FetchCourse();
        cim->RemoveCourse();
        cout << "Successfully remove all course in the year " << year;
        delete cim;
    }

    void removeCourseBySemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        string semester, year;
        cout << "Please enter the academic year that you want to remove: "; cin >> year;
        cim->setYear(toLowerCase(year));
        cout << "Please enter the semester that you want to remove: "; cin >> semester;
        cim->setSemester(toLowerCase(semester));
        cim->RemoveCourse();
        cout << "Successfully remove all course in the semester " << semester;
        delete cim;
    }

    void addCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        ClassModel* cm = new ClassModel();
        string temp, temp2;
        getline(cin, temp2);
        cout << "Course ID: "; getline(cin, temp); cim->setCourseName(toLowerCase(temp));
        cout << "Course name: "; getline(cin, temp); cim->setCourseName(toLowerCase(temp));
        cout << "Class name: "; getline(cin, temp); cim->setClassName(toLowerCase(temp));
        cout << "Lecturer Account: "; getline(cin, temp); cim->setLecturerAccount(toLowerCase(temp));
        cout << "Start day: "; getline(cin, temp); cim->setStartDay(toLowerCase(temp));
        cout << "End day: "; getline(cin, temp); cim->setEndDay(toLowerCase(temp));
        cout << "Start hour: "; getline(cin, temp); cim->setStartHour(toLowerCase(temp));
        cout << "End hour: "; getline(cin, temp); cim->setEndHour(toLowerCase(temp));
        cout << "Day of week: "; getline(cin, temp); cim->setEndHour(toLowerCase(temp));
        cout << "Room: "; getline(cin, temp); cim->setRoom(toLowerCase(temp));
        cout << "Semester: "; getline(cin, temp); cim->setSemester(toLowerCase(temp));
        cout << "Year: "; getline(cin, temp); cim->setYear(toLowerCase(temp));

        am->setCourseId(cim->getCourseId());
        am->setDay("");
        sm->setCourseId(cim->getCourseId());
        sm->setScore("");
        sm->setTerm("");
        vector<string> students = cm->getStudentInClass(cim->getClassName());
        for (int i = 0; i < students.size(); ++i) {
            am->setStudentId(students[i]);
            am->AddAttendance();
            sm->setStudentId(students[i]);
            sm->AddScore();
        }
        
        cim->AddCourse();
        cout << "Successfully added the course." << endl;
        delete cim;
        delete am;
        delete sm;
        delete cm;
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
        getline(cin, temp2);
        cout << "Course ID: ";  getline(cin, temp2);
        cout << "Course name: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Class name: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Lecturer account: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Start hour: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "End hour: ";  getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Start day: ";  getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "End day: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Day of week: ";  getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Room: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Semester: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
        cout << "Year: "; getline(cin, temp); toUpdate.push_back(toLowerCase(temp));
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
            delete cim;
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
            delete cim;
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
            delete cim;
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
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        cout << "Please enter the student ID of the student you want to remove from this course: "; cin >> studentId;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
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
        cout << "Please enter the ID of the course that you want to edit: "; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        cout << "Please enter the student ID of the student you want to add into this course: "; cin >> studentId;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        am->setCourseId(courseId);
        am->setStudentId(studentId);
        if (am->FetchAttendance().size() != 0) {
            cout << "The student is already enrolled into this course." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        am->setDay("");
        am->AddAttendance();

        sm->setCourseId(courseId);
        sm->setStudentId(studentId);
        if (sm->FetchScoreboard().size() != 0) {
            cout << "The student is already enrolled into this course." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        sm->setTerm("");
        sm->setScore("");
        sm->AddScore();

        cout << "Successfully added the student to the course." << endl;

        delete cim;
        delete am;
        delete uim;
        delete sm;

    }

    void viewListOfStudentsOfCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        AttendanceModel* am = new AttendanceModel();
        string temp, courseId;
        cout << "Please enter the ID of the course that you want to edit: "; cin >> courseId;
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            delete cim;
            delete uim;
            delete am;
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
        this->mapMethods["importCourse"] = [this]() { importCourse(); };
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
