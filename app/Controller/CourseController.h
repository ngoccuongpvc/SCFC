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
        getline(cin, path);
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ClassModel* cm = new ClassModel();
        ScoreboardModel* sm = new ScoreboardModel();

        ModelInterface* model = new ModelInterface(path);
        vector<vector<string>> records = model->fetch();
        if (model->columns.size() != 11) {
            cout << "Invalid input file format. Please recheck." << endl;
            delete cim;
            delete am;
            delete cm;
            delete sm;
            delete model;
            return;
        }

        for (vector<string> record : records) {
            cim->setCourseId(toLowerCase(record[1]));
            cim->setCourseName(toLowerCase(record[2]));
            cim->setClassName(toLowerCase(record[3]));
            cim->setLecturerAccount(toLowerCase(record[4]));
            cim->setStartDay(toLowerCase(record[5]));
            cim->setEndDay(toLowerCase(record[6]));
            cim->setDayOfWeek(toLowerCase(record[7]));
            cim->setStartHour(toLowerCase(record[8]));
            cim->setEndHour(toLowerCase(record[9]));
            cim->setRoom(toLowerCase(record[10]));
            cim->setSemester(getSemester());
            cim->setYear(getYear());
            cim->AddCourse();

            am->setCourseId(toLowerCase(record[1]));
            am->setDay("");
            sm->setCourseId(toLowerCase(record[1]));
            sm->setScore("");
            sm->setTerm("");
            vector<string> students = cm->getStudentInClass(toLowerCase(record[3]));
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

        cout << "The default semester of all courses will be the current semester of the current year. Courses imported successfully" << endl;
    }

    string getSemester() {
        time_t t = time(0);
        tm* now = localtime(&t);
        int month = now->tm_mon + 1;
        if (month >= 1 && month <= 3) return "Spring";
        if (month >= 4 && month <= 6) return "Summer";
        if (month >= 7 && month <= 9) return "Fall";
        if (month >= 10 && month <= 12) return "Winter";
    }

    string getYear() {
        time_t t = time(0);
        tm* now = localtime(&t);
        int year = now->tm_year + 1900;
        string sem = getSemester();
        if (sem == "Fall" || sem == "Winter")
        return to_string(year) + "-" + to_string(year+1);
        else return to_string(year-1) + "-" + to_string(year);
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
        cout << "Please enter the academic year that you want to remove: "; getline(cin, year);
        cim->setYear(toLowerCase(year));
        vector<vector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            removeAllRecordsOfCourse(results[i][12]);
        }
        cout << "Successfully remove all course in the year " << year;
        delete cim;
    }

    void removeCourseBySemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        string semester, year;
        cout << "Please enter the academic year that you want to remove: "; getline(cin, year);
        cim->setYear(toLowerCase(year));
        cout << "Please enter the semester that you want to remove: "; getline(cin, semester);
        cim->setSemester(toLowerCase(semester));
        vector<vector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            removeAllRecordsOfCourse(results[i][12]);
        }
        cout << "Successfully remove all course in the semester " << semester;
        delete cim;
    }

    void addCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        ClassModel* cm = new ClassModel();
        string temp, temp2;
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
        cout << "Please enter the ID of the course that you want to edit: "; string courseId; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        vector<vector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered does not exist. Please retry." << endl;
            delete cim; //check if crash
            return;
        }
        vector<string> record = results[0];
        cout << "Please enter the information that you want to change about this course. Press enter (leave blank) if you don't want to change that info.." << endl;
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
        if (record[2] != toUpdate[2] && toUpdate[2] != "") {
            // Remove all students from the old class and all of their records
            // Add all students of the new class and add their records
            emptyCourse(courseId);
            enrollStudentsOfClass(toUpdate[2], courseId);
        }
        if (record[12] != toUpdate[12] && toUpdate[12] != "") {
            updateCourseId(record[12], toUpdate[12]);
        }
        cim->UpdateCourse(&record, &toUpdate);
        cout << "Successfully updated the course." << endl;
        delete cim;
    }

    void updateCourseId(string oldCourseId, string newCourseId) {
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        am->setCourseId(oldCourseId);
        sm->setCourseId(oldCourseId);
        vector<string> updateAttendance(4, "all");
        vector<string> updateScore(5, "all");
        am->UpdateAttendance(nullptr, &updateAttendance);
        sm->UpdateScore(nullptr, &updateScore);

    }

    void emptyCourse(string courseId) {
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();

        am->setCourseId(courseId);
        sm->setCourseId(courseId);
        am->RemoveAttendance();
        sm->DeleteScore();

        delete am;
        delete sm;
    }

    void enrollStudentsOfClass(string className, string courseId) {
        ClassModel* cm = new ClassModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        
        am->setCourseId(courseId);
        am->setDay("");
        sm->setCourseId(courseId);
        sm->setTerm("");
        sm->setScore("");
        vector<string> students = cm->getStudentInClass(className);
        for (int i = 0; i < students.size(); ++i) {
            am->setStudentId(students[i]);
            sm->setStudentId(students[i]);
            am->AddAttendance();
            sm->AddScore();
        }

        delete cm;
        delete am;
        delete sm;
    }

    void removeAllRecordsOfCourse(string courseId) {
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();

        cim->setCourseId(toLowerCase(courseId));
        am->setCourseId(toLowerCase(courseId));
        sm->setCourseId(toLowerCase(courseId));

        cim->RemoveCourse();
        am->RemoveAttendance();
        sm->DeleteScore();

    }

    void removeCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        cout << "Please enter the ID of the course that you want to remove: "; string courseId; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered doesn't exist, please recheck." << endl;
            delete cim;
            return;
        }
        removeAllRecordsOfCourse(courseId);
        cout << "Successfully removed the course " << courseId << endl;
        delete cim;
    }

    void listOfCourseCurrentSemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        string semester, year;
        cout << "Please enter the year of the semester: "; getline(cin, year);
        cout << "Please enter the semester that you want to view the list of courses of: "; getline(cin, semester);
        cim->setSemester(toLowerCase(semester));
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

    void listOfCourseCurrentYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the year that you want to view the list of courses of: "; getline(cin, year);
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
        cout << "Please enter the ID of the course that you want to remove a student from: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        cout << "Please enter the student ID of the student you want to remove from this course: "; getline(cin, studentId);
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
        cout << "Please enter the ID of the course that you want to add: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        cout << "Please enter the student ID of the student you want to add into this course: "; getline(cin, studentId);
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
        cout << "Please enter the ID of the course that you want to list of students: "; getline(cin, courseId);
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
