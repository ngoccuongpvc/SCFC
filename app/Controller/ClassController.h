#ifndef CLASSCONTROLLER_H_INCLUDED
#define CLASSCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "../Model/ClassModel.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../View/View.h"

class ClassController : public ControllerInterface {
private:
public:

	void importAction() {
		cout << "Choose file: ";
		string path;
		//fflush(0);
		getline(cin, path);
		//cin >> path;
		string className;
		cout << "Class Name: ";
		getline(cin, className);
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
		getline(cin, classname);

		vector<string> students = classModel->getStudentInClass(classname);
		vector<vector<string>> studentInfo;
		vector<string> record;
		vector<string> cols = {" No. ", "Student ID", "Last Name", "First Name", "DoB", "  Gender  "};
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

	void showStudent() {
		ClassModel* classModel = new ClassModel();

		cout << "Input class name: ";
		string classname;
		getline(cin, classname);

		vector<vector<string>> students = classModel->FetchAll(classname);
		vector<string> cols = classModel->columns;

		View* view = new View(students, cols);
		view->displayTable();
		delete view;
		delete classModel;
	}

	ClassController() {
		this->mapMethods["importAction"] = [this]() { importAction(); };
		this->mapMethods["showClassList"] = [this]() { showClassList(); };
		this->mapMethods["showStudentInClass"] = [this]() { showStudentInClass(); };

	}

};
#endif // CLASSCONTROLLER_H_INCLUDED
