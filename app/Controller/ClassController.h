#ifndef CLASSCONTROLLER_H_INCLUDED
#define CLASSCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../Model/ClassModel.h"
#include "../View/View.h"
#include "Validation.h"
 

class ClassController : public ControllerInterface {
private:
	Validation* valid = new Validation();
public:

	void importAction() {
		cout << "Choose file: ";
		string path;

		//fflush(0);
		getline(cin, path);
		//cin >> path;

		string className;
		cout << "Class Name: ";
		valid->read(className, "nospc");
		ClassModel* classModel = new ClassModel();
		AccountModel* accountModel = new AccountModel();
		UserInfoModel* userInfoModel = new UserInfoModel();

		ModelInterface* model = new ModelInterface(path);
		myVector<myVector<string>> records = model->fetch();
		if (model->columns.size() != 6) {
			cout << "Invalid input file format. Please recheck." << endl;
			delete classModel;
			delete accountModel;
			delete userInfoModel;
			delete model;
			return;
		}

		classModel->setClassName(className);
		for (myVector<string> record : records) {
			classModel->setStudentId(toLowerCase(record[1]));

			accountModel->setUserName(toLowerCase(record[1]));
			accountModel->setPassword(toLowerCase(record[5]));
			accountModel->setRole("student");

			userInfoModel->setStudentId(toLowerCase(record[1]));
			userInfoModel->setLastName(toLowerCase(record[2]));
			userInfoModel->setFirstName(toLowerCase(record[3]));
			userInfoModel->setUserGender(toLowerCase(record[4]));
			userInfoModel->setDOB(toLowerCase(record[5]));
			userInfoModel->setUsername(toLowerCase(record[1]));
			
			classModel->saveStudent();
			accountModel->registerUser();
			userInfoModel->AddUser();
		}

		delete classModel;
		delete accountModel;
		delete userInfoModel;
		delete model;

		cout << "Imported Successfully" << endl;
	}

	void showClassList() {
		ClassModel* classModel = new ClassModel();
		myVector<string> classes = classModel->getClassList();
		cout << "List of classes: " << endl;
		for (int i = 0; i < (int)classes.size(); ++i) {
			cout << i + 1 << " " << classes[i] << endl;
		}
		delete classModel;
	}

	void showStudentInClass() {
		ClassModel* classModel = new ClassModel();
		UserInfoModel* userInfoModel = new UserInfoModel();

		cout << "Input class name: ";
		string classname;
		valid->read(classname, "nospc");

		myVector<string> students = classModel->getStudentInClass(classname);
		myVector<myVector<string>> studentInfo;
		myVector<string> record;
		myVector<string> cols; // {" No. ", "Student ID", "Last Name", "First Name", "DoB", "  Gender  "};
		cols.push_back(" No. ");
		cols.push_back("Student ID");
		cols.push_back("Last Name");
		cols.push_back("First Name");
		cols.push_back("DoB");
		cols.push_back(" Gender ");
		int n = students.size();
		int id = userInfoModel->getIndex("studentId");
		int lastname = userInfoModel->getIndex("lastName");
		int firstname = userInfoModel->getIndex("firstName");
		int dob = userInfoModel->getIndex("dob");
		int gender = userInfoModel->getIndex("userGender");
		
		for (int i = 0; i < n; ++i) {
			userInfoModel->setStudentId(students[i]);
			record = userInfoModel->FetchInfo()[0];
			record.pop_back();
			studentInfo.push_back(record);
		}

		View* view = new View(studentInfo, cols);
		view->displayTable();
		delete view;
		delete classModel;
	}

	void deleteRecordsOfStudent(string studentId) {
		AttendanceModel* am = new AttendanceModel();
		ScoreboardModel* sm = new ScoreboardModel();
		am->setStudentId(studentId);
		sm->setStudentId(studentId);
		am->RemoveAttendance();
		sm->DeleteScore();
		delete am;
		delete sm;
	}

	void addRecordsOfStudent(string studentId, string className) {
		CourseInformationModel* cim = new CourseInformationModel();
		AttendanceModel* am = new AttendanceModel();
		ScoreboardModel* sm = new ScoreboardModel();
		am->setStudentId(studentId);
		sm->setStudentId(studentId);
		am->setDay("");
		sm->setScore("");
		sm->setTerm("");
		cim->setClassName(className);
		myVector<myVector<string>> courses = cim->FetchCourse();
		for (int i = 0; i < courses.size(); ++i) {
			am->setCourseId(courses[i][12]);
			sm->setCourseId(courses[i][12]);
			am->AddAttendance();
			sm->AddScore();
		}
		delete cim;
		delete am;
		delete sm;
	}

	void addStudent() {
		string studentID, firstName, lastName, gender, DOB, className;
		cout << "Add new student to class: ";
		valid->read(className, "nospc");
		cout << "Student ID: ";
		valid->read(studentID, "nospc");
		cout << "First Name: ";
		valid->read(firstName, "nospc");
		cout << "Last Name: ";
		valid->read(lastName, "nospc");
		cout << "Gender: ";
		valid->read(gender, "gender");
		cout << "DOB: ";
		valid->read(DOB, "date");

		ClassModel* classModel = new ClassModel();
		AccountModel* accountModel = new AccountModel();
		UserInfoModel* userInfoModel = new UserInfoModel();
		
		userInfoModel->setStudentId(studentID);
		userInfoModel->setFirstName(firstName);
		userInfoModel->setLastName(lastName);
		userInfoModel->setUserGender(gender);
		userInfoModel->setDOB(DOB);
		userInfoModel->setUserGender(gender);
		userInfoModel->setUsername(studentID);

		accountModel->setUserName(studentID);
		accountModel->setPassword(DOB);
		accountModel->setRole("student");

		classModel->setClassName(className);
		classModel->setStudentId(studentID);

		addRecordsOfStudent(studentID, className);
		userInfoModel->AddUser();
		accountModel->registerUser();
		classModel->saveStudent();

		delete classModel;
		delete userInfoModel;
		delete accountModel;

		cout << "Successfully added the student." << endl;
	}

	void studentManipulate() {
		///Nothing here
	}

	void removeStudent() {
		string studentID;
		cout << "Input the ID of student that you want to remove: ";
		valid->read(studentID, "nospc");

		ClassModel* classModel = new ClassModel();
		UserInfoModel* userInfoModel = new UserInfoModel();
		AccountModel* accountModel = new AccountModel();

		classModel->removeStudentById(studentID);
		userInfoModel->setStudentId(studentID);
		userInfoModel->RemoveUser();
		accountModel->setUserName(studentID);
		accountModel->removeAccount();
		deleteRecordsOfStudent(studentID);
		delete classModel;
		delete userInfoModel;
		delete accountModel;
		cout << "Successfully removed the student." << endl;
	}

	void editStudent() {
		string studentID, firstName, lastName, gender, DOB, className;
		cout << "Input the ID of student that you want to edit: ";
		valid->read(studentID, "nospc");

		ClassModel* classModel = new ClassModel();
		UserInfoModel* userInfoModel = new UserInfoModel();

		userInfoModel->findStudentInfo(studentID);
		userInfoModel->RemoveUser();

		cout << "Please input the following fields (press enter to skip): " << endl;
		cout << "First Name: [current: " << userInfoModel->getFirstName() << "]: ";
		valid->read(firstName, "all");
		cout << "Last Name: [current: " << userInfoModel->getLastName() << "]: ";
		valid->read(lastName, "all");
		cout << "Gender: [current: " << userInfoModel->getUserGender() << "]: ";
		valid->read(gender, "gender");
		cout << "DOB: [current: " << userInfoModel->getDOB() << "]: ";
		valid->read(DOB, "date");
		
		if (firstName.size()) userInfoModel->setFirstName(firstName);
		if (lastName.size()) userInfoModel->setLastName(lastName);
		if (gender.size()) userInfoModel->setUserGender(gender);
		if (DOB.size()) userInfoModel->setDOB(DOB);
		
		userInfoModel->AddUser();

		delete classModel;
		delete userInfoModel;

		cout << "Modified the student succesfully" << endl;
	}

	void changeStudentClass() {
		string studentID, currentClass, newClass;

		cout << "Please input the ID of student: ";
		valid->read(studentID, "nospc");

		ClassModel* classModel = new ClassModel();
		currentClass = classModel->getClassOfStudent(studentID);
		classModel->removeStudentById(studentID);

		cout << "The current class is: " << currentClass << endl;
		cout << "Please enter the new class: ";
		valid->read(newClass, "nospc");

		classModel->setStudentId(studentID);
		classModel->setClassName(newClass);
		classModel->saveStudent();
		if (currentClass != newClass) {
			deleteRecordsOfStudent(studentID);
			addRecordsOfStudent(studentID, newClass);
		}
		

		cout << "The student has been assign to " << newClass << endl;
	}

	

	ClassController() {
		this->mapMethods["importAction"] = [this]() { importAction(); };
		this->mapMethods["showClassList"] = [this]() { showClassList(); };
		this->mapMethods["showStudentInClass"] = [this]() { showStudentInClass(); };
		this->mapMethods["addStudent"] = [this]() { addStudent(); };
		this->mapMethods["studentManipulate"] = [this]() { studentManipulate(); };
		this->mapMethods["removeStudent"] = [this]() { removeStudent(); };
		this->mapMethods["editStudent"] = [this]() { editStudent(); };
		this->mapMethods["changeStudentClass"] = [this]() { changeStudentClass(); };
	}

	~ClassController()
	{
		delete valid;
	}

};
#endif // CLASSCONTROLLER_H_INCLUDED
