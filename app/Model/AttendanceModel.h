#ifndef ATTENDANCEMODEL_H_INCLUDED
#define ATTENDANCEMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class CourseInformationModel : public ModelInterface
{
private:
	int id;
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

	vector<vector<string>> FetchAttendance(int studentId, int courseId) {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = studentId;
		conditions[this->getIndex("courseId")] = courseId;
		return this->fetch(&conditions);
	}

	bool FetchStudentAndCourse(int studentId, int courseId) {
		vector<vector<string>> fetchResults = FetchAttendance(studentId, courseId);
		if (fetchResults.size() == 0) return false;
		this->studentId = stoi(fetchResults[0][1]);
		this->courseId = stoi(fetchResults[0][2]);
		return true;
	}

	void AddAttendance(string day) {
		this->day = day;
		vector<string> record;
		record.push_back("0");
		record.push_back(to_string(this->studentId));
		record.push_back(to_string(this->courseId));
		record.push_back(this->day);
		this->add(&record);
	}
	
};

#endif // ATTENDANCEMODEL_H_INCLUDED
