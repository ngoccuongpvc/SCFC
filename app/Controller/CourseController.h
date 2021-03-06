#ifndef COURSECONTROLLER_H_INCLUDED
#define COURSECONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/ClassModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"
#include "Validation.h"

class CourseController : public ControllerInterface {
private:
	Validation* valid = new Validation();
public:

    void importCourse() {
        cout << "Choose file: ";
        string path;
        getline(cin, path);

        ifstream of(path);
        if (!of.is_open()) {
            cout << "File not found, please recheck." << endl;
            return;
        }
        of.close();

        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ClassModel* cm = new ClassModel();
        ScoreboardModel* sm = new ScoreboardModel();

        ModelInterface* model = new ModelInterface(path);
        myVector<myVector<string>> records = model->fetch();
        if (model->columns.size() != 11) {
            cout << "Invalid input file format. Please recheck." << endl;
            delete cim;
            delete am;
            delete cm;
            delete sm;
            delete model;
            return;
        }

        for (myVector<string> record : records) {
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
            myVector<string> students = cm->getStudentInClass(toLowerCase(record[3]));
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
        if (month >= 1 && month <= 3) return "spring";
        if (month >= 4 && month <= 6) return "summer";
        if (month >= 7 && month <= 9) return "fall";
        if (month >= 10 && month <= 12) return "winter";
    }

    string getYear() {
        time_t t = time(0);
        tm* now = localtime(&t);
        int year = now->tm_year + 1900;
        string sem = getSemester();
        if (sem == "fall" || sem == "winter")
        return to_string(year) + "-" + to_string(year+1);
        else return to_string(year-1) + "-" + to_string(year);
    }

    void viewAllCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        myVector<myVector<string>> results = cim->FetchCourse();
        myVector<string> header = cim->columns;
        for (int i = 0; i < header.size(); ++i) header[i] = capitalize(header[i]);
        View* view = new View(results, header);
        view->displayTable();
        delete view;
        delete cim;
    }

    void removeCourseByYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the academic year that you want to remove: "; valid->read(year, "year");
        cim->setYear(year);
        myVector<myVector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            removeAllRecordsOfCourse(results[i][12]);
        }
        cout << "Successfully remove all course in the year " << year << endl;
        delete cim;
    }

    void removeCourseBySemester() {
        CourseInformationModel* cim = new CourseInformationModel();
        string semester, year;
        cout << "Please enter the academic year that you want to remove: "; valid->read(year, "year");
        cim->setYear(year);
        cout << "Please enter the semester that you want to remove: "; valid->read(semester, "sem");
        cim->setSemester(semester);
        myVector<myVector<string>> results = cim->FetchCourse();
        for (int i = 0; i < results.size(); ++i) {
            removeAllRecordsOfCourse(results[i][12]);
        }
        cout << "Successfully remove all course in the semester " << semester << endl;
        delete cim;
    }

    void addCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        ScoreboardModel* sm = new ScoreboardModel();
        ClassModel* cm = new ClassModel();
        string temp, temp2;
        cout << "Course ID: ";        valid->read(temp, "nospc"); cim->setCourseName(temp);
        cout << "Course name: ";      valid->read(temp, "nospc"); cim->setCourseName(temp);
        cout << "Class name: ";       valid->read(temp, "all");   cim->setClassName(temp);
        cout << "Lecturer Account: "; valid->read(temp, "nospc"); cim->setLecturerAccount(temp);
        cout << "Start day: ";        valid->read(temp, "date");  cim->setStartDay(temp);
        cout << "End day: ";          valid->read(temp, "date");  cim->setEndDay(temp);
        cout << "Start hour: ";       valid->read(temp, "hour");  cim->setStartHour(temp);
        cout << "End hour: ";		  valid->read(temp, "hour");  cim->setEndHour(temp);
        cout << "Day of week: ";      valid->read(temp, "dow");   cim->setEndHour(temp);
        cout << "Room: ";             valid->read(temp, "nospc"); cim->setRoom(temp);
        cout << "Semester: ";         valid->read(temp, "sem");   cim->setSemester(temp);
        cout << "Year: ";             valid->read(temp, "year");  cim->setYear(temp);

        am->setCourseId(cim->getCourseId());
        am->setDay("");
        sm->setCourseId(cim->getCourseId());
        sm->setScore("");
        sm->setTerm("");
        myVector<string> students = cm->getStudentInClass(cim->getClassName());
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

    void viewInfoOfCourse(string courseId) {
        CourseInformationModel* cim = new CourseInformationModel();
        cim->setCourseId(courseId);
        myVector<myVector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            delete cim;
            return;
        }

        cout << "Course ID: " << results[0][12] << endl;
        cout << "Course name: " << results[0][1] << endl;
        cout << "Class name: " << results[0][2] << endl;
        cout << "Lecturer account: " << results[0][3] << endl;
        cout << "Start hour: " << results[0][4] << endl;
        cout << "End hour: " << results[0][5] << endl;
        cout << "Start day: " << results[0][6] << endl;
        cout << "End day: " << results[0][7] << endl;
        cout << "Day of week: " << results[0][8] << endl;
        cout << "Room: " << results[0][9] << endl;
        cout << "Semester: " << results[0][10] << endl;
        cout << "Year: " << results[0][11] << endl;
        
        delete cim;
    }

    void editCourse() {
        CourseInformationModel* cim = new CourseInformationModel();
        cout << "Please enter the ID of the course that you want to edit: "; 
		string courseId; valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        myVector<myVector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The course you entered does not exist. Please retry." << endl;
            delete cim; //check if crash
            return;
        }

        cout << "Below is the current information about the course: " << endl;
        viewInfoOfCourse(courseId);

        myVector<string> record = results[0];
        cout << "Please enter the information that you want to change about this course." << endl;
        string temp, temp2;
        myVector<string> toUpdate;
        toUpdate.push_back(record[0]);

        cout << "Course ID: ";       valid->read(temp2, "nospc");
		cout << "Course name: ";     valid->read(temp, "nospc"); toUpdate.push_back(temp);
		cout << "Class name: ";      valid->read(temp, "all");   toUpdate.push_back(temp);
		cout << "Lecturer account: ";valid->read(temp, "nospc"); toUpdate.push_back(temp);
		cout << "Start hour: ";      valid->read(temp, "date");  toUpdate.push_back(temp);
		cout << "End hour: ";        valid->read(temp, "date");  toUpdate.push_back(temp);
		cout << "Start day: ";       valid->read(temp, "hour");  toUpdate.push_back(temp);
		cout << "End day: ";         valid->read(temp, "hour");  toUpdate.push_back(temp);
		cout << "Day of week: ";     valid->read(temp, "dow");   toUpdate.push_back(temp);
		cout << "Room: ";            valid->read(temp, "nospc"); toUpdate.push_back(temp);
		cout << "Semester: ";        valid->read(temp, "sem");   toUpdate.push_back(temp);
		cout << "Year: ";            valid->read(temp, "year");  toUpdate.push_back(temp);
        toUpdate.push_back(temp2);
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
        myVector<string> updateAttendance(4, "all");
        myVector<string> updateScore(5, "all");
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
        myVector<string> students = cm->getStudentInClass(className);
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
        cout << "Please enter the ID of the course that you want to remove: "; 
		string courseId; valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        myVector<myVector<string>> courseResult = cim->FetchCourse();
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
        cout << "Please enter the year of the semester: "; valid->read(year, "year");
        cout << "Please enter the semester that you want to view the list of courses of: "; valid->read(semester, "sem");
        cim->setSemester(semester);
        cim->setYear(year);
        myVector<myVector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The semester doesn't exist or you haven't added any course to this semester yet!" << endl;
            delete cim;
            return;
        }
        myVector<myVector<string>> courses;
        for (int i = 0; i < results.size(); ++i) {
            myVector<string> info;
            info.push_back(results[i][1]);
            info.push_back(results[i][12]);
            courses.push_back(info);
        }
        myVector<string> header; header.push_back("Course Name");
        header.push_back("Course ID");
        View* view = new View(courses, header);
        view->displayTable();
        delete cim;
        delete view;
    }

    void listOfCourseCurrentYear() {
        CourseInformationModel* cim = new CourseInformationModel();
        string year;
        cout << "Please enter the year that you want to view the list of courses of: "; valid->read(year, "nospc");
        cim->setYear(year);
        myVector<myVector<string>> results = cim->FetchCourse();
        if (results.size() == 0) {
            cout << "The semester doesn't exist or you haven't added any course to this semester yet!" << endl;
            delete cim;
            return;
        }
        myVector<myVector<string>> courses;
        for (int i = 0; i < results.size(); ++i) {
            myVector<string> info;
            info.push_back(results[i][1]);
            info.push_back(results[i][12]);
            courses.push_back(info);
        }
        myVector<string> header; header.push_back("Course Name");
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
        cout << "Please enter the ID of the course that you want to remove a student from: "; valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        cout << "Please enter the student ID of the student you want to remove from this course: "; valid->read(studentId, "nospc");
        uim->setStudentId(studentId);
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
        myVector<myVector<string>> attendance = am->FetchAttendance();
        for (int i = 0; i < attendance.size(); ++i) {
            am->RemoveAttendance(&attendance[i]);
        }
        sm->setCourseId(courseId);
        sm->setStudentId(studentId);
        myVector<myVector<string>> scoreboard = sm->FetchScoreboard();
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
        cout << "Please enter the ID of the course that you want to add: "; valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete am;
            delete uim;
            delete sm;
            return;
        }
        cout << "Please enter the student ID of the student you want to add into this course: "; 
		valid->read(studentId, "nospc");
        uim->setStudentId(studentId);
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
        cout << "Please enter the ID of the course that you want to list of students: "; 
		valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered could not be found." << endl;
            delete cim;
            delete uim;
            delete am;
            return;
        }
        myVector<myVector<string>> students;
        am->setCourseId(courseId);
        am->setDay("");
        myVector<myVector<string>> results = am->FetchAttendance();
        for (int i = 0; i < results.size(); ++i) {
            uim->setStudentId(results[i][1]);
            myVector<myVector<string>> getBack = uim->FetchInfo();
            if (getBack.size() != 0) {
                students.push_back(getBack[0]);
            }
        }

        myVector<string> header = uim->columns;
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
    
	~CourseController() {
		delete valid;
	}

};

#endif // 
