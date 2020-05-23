#ifndef ATTENDANCEMODEL_H_INCLUDED
#define ATTENDANCEMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class AttendanceModel : public ModelInterface
{
private:
	string id;
	string studentId; // The incrementing id of UserInformationModel records
	string courseId; // The incrementing id of CourseInformationModel records
	string day;
	

public:
	AttendanceModel() : ModelInterface("database/CheckInList.csv") {
		this->id = "all";
		this->studentId = "all";
		this->courseId = "all";	
		this->day = "all";
	}

	void setId(string id) {
		this->id = id;;
	}

	void setCourseId(string id) {
		this->courseId = id;
	}

	void setStudentId(string id) {
		this->studentId = id;
	}

	void setDay(string day) {
		this->day = day;
	}

	string getId() {
		return this->id;
	}

	string getCourseId() {
		return this->courseId;
	}

	string getStudentId() {
		return this->studentId;
	}
	
	string getDay() {
		return this->day;
	}

	vector<vector<string>> FetchAttendance() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = this->studentId;
		conditions[this->getIndex("id")] = this->id;
		conditions[this->getIndex("day")] = this->day;
		conditions[this->getIndex("courseId")] = this->courseId;
		return this->fetch(&conditions);
	}

	void UpdateAttendance(vector<string> *conditions, vector<string> *toUpdate) {
		this->update(conditions, toUpdate);
	}

	void AddAttendance() {
		vector<string> record;
		record.push_back(this->id);
		record.push_back(this->studentId);
		record.push_back(this->courseId);
		record.push_back(this->day);
		this->add(&record);
	}
	
	void RemoveAttendance(vector<string> *toDelete) {
		this->erase(toDelete);
	}
	
};

#endif // ATTENDANCEMODEL_H_INCLUDED
