#ifndef COURSEINFORMATIONMODEL_H_INCLUDED
#define COURSEINFORMATIONMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

/*
<Remember to lowercase before setting>
The csv file for this model has the following order:
0. Record ID (1,2,3,...)
1. Course name (introduction to mandarin i)
2. Class name (19ctt2)
3. Lecturer account (dinhbatien)
4. Start hour (8:00)
5. End hour (12:00)
6. Start day (01-01-2020)
7. End day (01-01-2020)
8. Room (i52)
9. Semester (fall)
10. Year (2020)
11. Day of Week (wed, thur, fri)
12. Course ID (cs162, mth252)
*/
class CourseInformationModel : public ModelInterface
{
private:

	string id; // the incrementing id
	string courseId; //ex: cs162, mth251
	string courseName;
	string className;
	string lecturerAccount;
	string startDay;
	string endDay;
	string startHour;
	string endHour;
	string room;
	string semester;
	string year;
	string dayOfWeek;

public:
	CourseInformationModel() : ModelInterface("database/CourseInfo.csv") {
		this->id = "all";
		this->courseName = "all";
		this->className = "all";
		this->lecturerAccount = "all";
		this->startDay = "all";
		this->startHour = "all";
		this->endDay = "all";
		this->endHour = "all";
		this->room = "all";
		this->semester = "all";
		this->year = "all";
		this->dayOfWeek = "all";
		this->courseId = "all";
	}

	void setId(string id) {
		this->id = toLowerCase(id);
	}

	void setCourseId(string id)
	{
		this->courseId = toLowerCase(id);
	}

	void setCourseName(string courseName) {
		this->courseName = toLowerCase(courseName);
	}

	void setClassName(string className) {
		this->className = toLowerCase(className);
	}

	void setLecturerAccount(string lecturerAccount) {
		this->lecturerAccount = toLowerCase(lecturerAccount);
	}

	void setStartDay(string startDay) {
		this->startDay = toLowerCase(startDay);
	}

	void setEndDay(string endDay) {
		this->endDay = toLowerCase(endDay);
	}

	void setStartHour(string startHour) {
		this->startHour = toLowerCase(startHour);
	}

	void setEndHour(string endHour) {
		this->endHour = toLowerCase(endHour);
	}

	void setRoom(string room) {
		this->room = toLowerCase(room);
	}

	void setSemester(string semester) {
		this->semester = toLowerCase(semester);
	}

	void setYear(string year) {
		this->year = toLowerCase(year);
	}


	void setDayOfWeek(string day) {
		this->dayOfWeek = toLowerCase(day);
	}

	string getId() {
		return this->id;
	}

	string getCourseId() {
		return this->courseId;
	}

	string getCourseName() {
		return this->courseName;
	}

	string getClassName() {
		return this->className;
	}

	string getLecturerAccount() {
		return this->lecturerAccount;
	}

	string getStartDay() {
		return this->startDay;
	}

	string getEndDay() {
		return this->endDay;
	}

	string getStartHour() {
		return this->startHour;
	}

	string getEndHour() {
		return this->endHour;
	}

	string getRoom() {
		return this->room;
	}

	string getSemester() {
		return this->semester;
	}
	
	string getYear() {
		return this->year;
	}

	string getDayofWeek() {
		return this->dayOfWeek;
	}

	void ImportCourse() {

	}

	/*Before fetching, please ensure that all parameters that are required as conditions are set in model using 'set' functions
	Example: if you want to fetch records with id 69, please set it using Model->setId(69) before fetching.*/
	vector<vector<string>> FetchCourse() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("courseId")] = this->courseId;
		conditions[this->getIndex("courseName")] = this->courseName;
		conditions[this->getIndex("className")] = this->className;
		conditions[this->getIndex("lecturerAccount")] = this->lecturerAccount;
		conditions[this->getIndex("startHour")] = this->startHour;
		conditions[this->getIndex("endHour")] = this->endHour;
		conditions[this->getIndex("startDay")] = this->startDay;
		conditions[this->getIndex("endDay")] = this->endDay;
		conditions[this->getIndex("semester")] = this->semester;
		conditions[this->getIndex("room")] = this->room;
		conditions[this->getIndex("year")] = this->year;
		conditions[this->getIndex("dayOfWeek")] = this->dayOfWeek;		
		return this->fetch(&conditions);
	}


	/*Before adding, please provide all necessary information for the model using the 'set' functions.
	Except that the 'id' of the model (the incrementing id) is not needed.*/
	void AddCourse() {
		vector<string> *record = getCourseInfo();
		this->add(record);
	}

	/*Set the values in the model using a vector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	void setCourseInfo(vector<string>* info) {
		if (info->size() != this->columns.size()) return;
		this->courseName = (*info)[1];
		this->className = (*info)[2];
		this->lecturerAccount = (*info)[3];
		this->startHour = (*info)[4];
		this->endHour = (*info)[5];
		this->startDay = (*info)[6];
		this->endDay = (*info)[7];
		this->room = (*info)[8];
		this->semester = (*info)[9];
		this->year = (*info)[10];
		this->dayOfWeek = (*info)[11];
		this->courseId = (*info)[12];
	}

	/*Get the values in the model and return as a vector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	vector<string>* getCourseInfo() {
		vector<string>* info = new vector<string>();
		info->push_back(this->id);
		info->push_back(this->courseName);
		info->push_back(this->className);
		info->push_back(this->lecturerAccount);
		info->push_back(this->startHour);
		info->push_back(this->endHour);
		info->push_back(this->startDay);
		info->push_back(this->endDay);
		info->push_back(this->room);
		info->push_back(this->semester);
		info->push_back(this->year);
		info->push_back(this->dayOfWeek);
		info->push_back(this->courseId);
		return info;
	}

	/*Please provide 2 vectors for updating. The 'conditions' vector is the conditions of the records you want to change.
	The 'toUpdate' vector contains the fields (in the correct order) you want to update in those records. The remaining fields that you don't want to change may be left empty or same as the original record.
	In case you want to update the current record already set in the model, please provide 'nullptr' in 'conditions' field. Please do not leave the 'toUupdate' field blank.*/
	void UpdateCourse(vector<string>* conditions = nullptr, vector<string>* toUpdate = nullptr) {
		if (toUpdate == nullptr) return;
		if (conditions == nullptr) conditions = getCourseInfo();
		this->update(conditions, toUpdate);
	}

	/*The 'toDelete' vector is the conditions of the records you want to delete.
	In case you want to delete the current record already set in the model, please provide 'nullptr' as the 'conditions' parameter.*/
	void RemoveCourse(vector<string>* conditions = nullptr) {
		if (conditions == nullptr) conditions = getCourseInfo();
		this->erase(conditions);
	}
};

#endif // COURSEINFORMATIONMODEL_H_INCLUDED
