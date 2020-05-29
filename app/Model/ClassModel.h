#ifndef CLASSMODEL_H_INCLUDED
#define CLASSMODEL_H_INCLUDED

#include "ModelInterface.h"
#include "../Utils/vector.h"

class ClassModel : public ModelInterface {

private:
	string id;
	string className;
	string studentId;

public:
	ClassModel() : ModelInterface("database/Class.csv") {
		this->id = "all";
		this->className = "all";
		this->studentId = "all";
	}

	void setId(string id) {
		this->id = toLowerCase(id);
	}

	void setClassName(string className) {
		this->className = toLowerCase(className);
	}

	void setStudentId(string studentId) {
		this->studentId = toLowerCase(studentId);
	}
	
	void saveStudent() {
		myVector<string> record((this->columns).size());
		record[this->getIndex("classname")] = this->className;
		record[this->getIndex("studentid")] = this->studentId;
		this->add(&record);
	}

	myVector<string> getClassList() {
		myVector<myVector<string>> records = this->fetch();
		myVector<string> res;

		int n = records.size();
		int col = this->getIndex("classname");

		for (int i = 0; i < n; ++i) {
			bool isExisted = false;
			for (int j = 0; j < i; ++j) {
				if (records[i][col] == records[j][col]) {
					isExisted = true;
					break;
				}
			}

			if (!isExisted) res.push_back(records[i][col]);
		}

		return res;
	}

	myVector<string> getStudentInClass(string classname) {
		myVector<string>* conditions = new myVector<string>((this->columns).size(), "all");
		(*conditions)[this->getIndex("classname")] = classname;

		myVector<myVector<string>> records = this->fetch(conditions);
		myVector<string> res;
		int n = records.size();
		int col = this->getIndex("studentid");
		for (int i = 0; i < n; ++i) {
			res.push_back(records[i][col]);
		}
		return res;
	}

	/*Set the values in the model using a myVector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	void setClassInfo(myVector<string>* info) {
		if (info->size() != this->columns.size()) return;
		this->studentId = (*info)[this->getIndex("studentid")];
		this->className = (*info)[this->getIndex("classname")];
	}

	/*Get the values in the model and return as a myVector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	myVector<string>* getClassInfo() {
		myVector<string>* info = new myVector<string>();
		info->push_back(this->id);
		info->push_back(this->className);
		info->push_back(this->studentId);
		return info;
	}

	void RemoveClass(myVector<string>* conditions = nullptr) {
		if (conditions == nullptr || conditions->size() != this->columns.size()) conditions = getClassInfo();
		this->erase(conditions);
	}

	void removeStudentById(string studentID) {
		myVector<string>* conditions = new myVector<string>((this->columns).size(), "all");
		(*conditions)[this->getIndex("studentid")] = studentID;
		this->erase(conditions);
	}

	string getClassOfStudent(string studentID) {
		myVector<string>* conditions = new myVector<string>((this->columns).size(), "all");
		(*conditions)[this->getIndex("studentid")] = studentID;
		myVector<myVector<string>> res = this->fetch(conditions);
		if (res.size() == 0) return "";
		return res[0][this->getIndex("classname")];
	}
};
#endif // CLASSMODEL_H_INCLUDED
