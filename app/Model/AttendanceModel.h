#ifndef ATTENDANCEMODEL_H_INCLUDED
#define ATTENDANCEMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class CourseInformationModel : public ModelInterface
{
private:
	int courseId;
	int studentId;
	string day;
	

public:
	CourseInformationModel() : ModelInterface("database/CheckInList.csv") {

	}

	void setCourseId(int id) {
		this->courseId = id;
	}

	void setStudentId(int id) {
		this->studentId = id;
	}

	void setDay(string day) {
		this->day = day;
	}

	int getCourseId() {
		return this->courseId;
	}

	int getStudentId() {
		return this->studentId;
	}
	
	string getDay() {
		return this->day;
	}

	bool FetchAttendance(int studentId, int courseId) {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = studentId;
		conditions[this->getIndex("courseId")] = courseId;
		if (this->fetch(&conditions).size() == 0) return false;
		vector<string> record = this->fetch(&conditions)[0];
		this->studentId = stoi(record[1]);
		this->courseId = stoi(record[2]);
		this->day = record[3];
		return true;
	}

	void AddAttendance(int studentId, int courseId, string day) {
		
	}

	
};

#endif // ATTENDANCEMODEL_H_INCLUDED
