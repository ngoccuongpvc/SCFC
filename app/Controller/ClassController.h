#ifndef CLASSCONTROLLER_H_INCLUDED
#define CLASSCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "../Model/ClassModel.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"

class ClassController : public ControllerInterface {
private:
public:

	void importAction() {
		cout << "Choose file: ";
		string path;
		cin >> path;
		string className;
		cout << "Class Name: ";
		cin >> className;
		ClassModel* classModel = new ClassModel();
		AccountModel* accountModel = new AccountModel();
		UserInfoModel* userInfoModel = new UserInfoModel();

		ModelInterface* model = new ModelInterface(path);
		vector<vector<string>> records = model->fetch();

		classModel->setClassName(className);
		for (vector<string> record : records) {
			classModel->setStudentId(record[1]);

			accountModel->setUserName(record[1]);
			accountModel->setPassword(record[5]);
			accountModel->setRole("student");

			userInfoModel->setStudentId(record[1]);
			userInfoModel->setLastName(record[2]);
			userInfoModel->setFirstName(record[3]);
			userInfoModel->setUserGender(record[4]);
			userInfoModel->setDOB(record[5]);
			userInfoModel->setUsername(record[1]);

			classModel->saveStudent();
			accountModel->registerUser();
			userInfoModel->AddUser();
		}

		cout << "Imported Successfully" << endl;
	}

	void showClassList() {
		ClassModel* classModel = new ClassModel();
		vector<string> classes = classModel->getClassList();
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
		cin >> classname;

		vector<string> students = classModel->getStudentInClass(classname);
		vector<vector<string>> studentInfo;
		vector<string> record;

		int n = students.size();
		int id = userInfoModel->getIndex("studentId");
		int lastname = userInfoModel->getIndex("lastName");
		int firstname = userInfoModel->getIndex("firstName");
		int dob = userInfoModel->getIndex("dob");
		int gender = userInfoModel->getIndex("userGender");
		
		for (int i = 0; i < n; ++i) {
			userInfoModel->setStudentId(students[i]);
			record = userInfoModel->FetchInfo()[0];
			studentInfo.push_back(record);
			cout << record[id] << " " << record[firstname] << " " << record[lastname] << " " << record[gender] << " " << record[dob] << endl;
		}
		delete classModel;
	}

	void addStudent() {
		string studentID, firstName, lastName, gender, DOB, className;
		cout << "Add new student to class: ";
		cin >> className;
		cout << "Student ID: ";
		cin >> studentID;
		cout << "First Name: ";
		cin >> firstName;
		cout << "Last Name: ";
		cin >> lastName;
		cout << "Gender: ";
		cin >> gender;
		cout << "DOB: ";
		cin >> DOB;

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

		userInfoModel->AddUser();
		accountModel->registerUser();
		classModel->saveStudent();
	}

	void studentManipulate() {
		///Nothing here
	}

	void removeStudent() {
		string studentID;
		cout << "Input the ID of student that you want to remove: ";
		cin >> studentID;

		ClassModel* classModel = new ClassModel();
		UserInfoModel* userInfoModel = new UserInfoModel();
		AccountModel* accountModel = new AccountModel();

		classModel->removeStudentById(studentID);
		userInfoModel->setStudentId(studentID);
		userInfoModel->RemoveUser();
		accountModel->setUserName(studentID);
		accountModel->removeAccount();
	}

	void editStudent() {
		string studentID, firstName, lastName, gender, DOB, className;
		cout << "Input the ID of student that you want to edit: ";
		cin >> studentID;

		ClassModel* classModel = new ClassModel();
		UserInfoModel* userInfoModel = new UserInfoModel();

		userInfoModel->findStudentInfo(studentID);
		userInfoModel->RemoveUser();

		cout << "Please input the following fields (press enter to skip): " << endl;
		cout << "First Name: [current: " << userInfoModel->getFirstName() << "]: ";
		getline(cin, firstName);
		cout << "Last Name: [current: " << userInfoModel->getLastName() << "]: ";
		getline(cin, lastName);
		cout << "Gender: [current: " << userInfoModel->getUserGender() << "]: ";
		getline(cin, gender);
		cout << "DOB: [current: " << userInfoModel->getDOB() << "]: ";
		getline(cin, DOB);

		if (firstName.size()) userInfoModel->setFirstName(firstName);
		if (lastName.size()) userInfoModel->setLastName(lastName);
		if (gender.size()) userInfoModel->setUserGender(gender);
		if (DOB.size()) userInfoModel->setDOB(DOB);
		
		userInfoModel->AddUser();

		cout << "Modify Succesfully" << endl;
	}

	void changeStudentClass() {
		string studentID, currentClass, newClass;

		cout << "Please input the ID of student: ";
		cin >> studentID;

		ClassModel* classModel = new ClassModel();
		currentClass = classModel->getClassOfStudent(studentID);
		classModel->removeStudentById(studentID);

		cout << "The current class is: " << currentClass << endl;
		cout << "Please enter the new class: ";
		cin >> newClass;

		classModel->setStudentId(studentID);
		classModel->setClassName(newClass);
		classModel->saveStudent();

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

};
#endif // CLASSCONTROLLER_H_INCLUDED
