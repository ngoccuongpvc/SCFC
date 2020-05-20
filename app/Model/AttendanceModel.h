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
	string courseId;
	string studentId;
	string day;
	

public:
	AttendanceModel() : ModelInterface("database/CheckInList.csv") {
		this->id = "all";
		this->courseId = "all";
		this->studentId = "all";
		this->day = "all";
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

	void UpdateAttendance(vector<string> toUpdate) {
		vector<vector<string>> records = this->FetchAttendance();
		if (records.size() == 0) return;
		vector<string> conditions = records[0];
		this->update(&conditions, &toUpdate);
	}

	void AddAttendance() {
		vector<string> record;
		record.push_back(this->id);
		record.push_back(this->studentId);
		record.push_back(this->courseId);
		record.push_back(this->day);
		this->add(&record);
	}
	
};

#endif // ATTENDANCEMODEL_H_INCLUDED
