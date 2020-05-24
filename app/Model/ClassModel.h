#ifndef CLASSMODEL_H_INCLUDED
#define CLASSMODEL_H_INCLUDED

#include "ModelInterface.h"

class ClassModel : public ModelInterface {
private:
	string id;
	string className;
	string studentId;

public:
	ClassModel() : ModelInterface("database/Class.csv") {

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
		vector<string> record((this->columns).size());
		record[this->getIndex("classname")] = this->className;
		record[this->getIndex("studentid")] = this->studentId;
		this->add(&record);
	}

	vector<string> getClassList() {
		vector<vector<string>> records = this->fetch();
		vector<string> res;

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

	vector<string> getStudentInClass(string classname) {
		vector<string>* conditions = new vector<string>((this->columns).size(), "all");
		(*conditions)[this->getIndex("classname")] = classname;

		vector<vector<string>> records = this->fetch(conditions);
		vector<string> res;
		int n = records.size();
		int col = this->getIndex("studentid");
		for (int i = 0; i < n; ++i) {
			res.push_back(records[i][col]);
		}
		return res;
	}
};
#endif // CLASSMODEL_H_INCLUDED
