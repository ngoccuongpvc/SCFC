#ifndef ATTENDANCEMODEL_H_INCLUDED
#define ATTENDANCEMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;
/*
<Remember to lowercase before setting>
The csv file for this model has the following order:
0. Record ID (1,2,3,...)
1. Student ID (19125064)
2. Course ID (cs162)
3. Day (08-06-2020)
*/
class AttendanceModel : public ModelInterface
{
private:
	string id;
	string studentId;
	string courseId;
	string day;
	

public:
	AttendanceModel() : ModelInterface("database/CheckInList.csv") {
		this->id = "all";
		this->studentId = "all";
		this->courseId = "all";	
		this->day = "all";
	}

	void setId(string id) {
		this->id = toLowerCase(id);;
	}

	void setCourseId(string id) {
		this->courseId = toLowerCase(id);
	}

	void setStudentId(string id) {
		this->studentId = toLowerCase(id);
	}

	void setDay(string day) {
		this->day = toLowerCase(day);
	}

	// The incrementing id of this record
	string getId() {
		return this->id;
	}

	// The string id of the course, i.e CS162
	string getCourseId() {
		return this->courseId;
	}

	// The student id, i.e 19125064
	string getStudentId() {
		return this->studentId;
	}
	
	// The day of attendance
	string getDay() {
		return this->day;
	}

	/*Before fetching, please ensure that all parameters that are required as conditions are set in model using 'set' functions
	Example: if you want to fetch records with id 69, please set it using Model->setId(69) before fetching.*/
	myVector<myVector<string>> FetchAttendance() {
		myVector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = this->studentId;
		conditions[this->getIndex("day")] = this->day;
		conditions[this->getIndex("courseId")] = this->courseId;
		return this->fetch(&conditions);
	}


	/*Before adding, please provide all necessary information for the model using the 'set' functions.
	Except that the 'id' of the model (the incrementing id) is not needed.*/
	void AddAttendance() {
		myVector<string>* record = getAttendanceInfo();
		this->add(record);
	}
	
	/*Set the values in the model using a myVector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	void setAttendanceInfo(myVector<string>* info) {
		if (info->size() != this->columns.size()) return;
		this->studentId = (*info)[1];
		this->courseId = (*info)[2];
		this->day = (*info)[3];
	}

	/*Get the values in the model and return as a myVector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	myVector<string>* getAttendanceInfo() {
		myVector<string>* info = new myVector<string>();
		info->push_back(this->id);
		info->push_back(this->studentId);
		info->push_back(this->courseId);
		info->push_back(this->day);
		return info;
	}

	/*Please provide 2 myVectors for updating. The 'conditions' myVector is the conditions of the records you want to change.
	The 'toUpdate' myVector contains the fields (in the correct order) you want to update in those records. The remaining fields that you don't want to change may be left empty or same as the original record.
	In case you want to update the current record already set in the model, please provide 'nullptr' in 'conditions' field. Please do not leave the 'toUupdate' field blank.*/
	void UpdateAttendance(myVector<string>* conditions = nullptr, myVector<string>* toUpdate = nullptr) {
		if (toUpdate == nullptr || toUpdate->size() != this->columns.size()) return;
		if (conditions != nullptr && conditions->size() != this->columns.size()) return;
		if (conditions == nullptr) conditions = getAttendanceInfo();
		this->update(conditions, toUpdate);
	}

	/*The 'toDelete' myVector is the conditions of the records you want to delete.
	In case you want to delete the current record already set in the model, please provide 'nullptr' as the 'conditions' parameter.*/
	void RemoveAttendance(myVector<string>* conditions = nullptr) {
		if (conditions == nullptr || conditions->size() != this->columns.size()) conditions = getAttendanceInfo();
		this->erase(conditions);
	}
	
};

#endif // ATTENDANCEMODEL_H_INCLUDED
