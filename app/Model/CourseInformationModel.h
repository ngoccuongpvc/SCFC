#ifndef COURSEINFORMATIONMODEL_H_INCLUDED
#define COURSEINFORMATIONMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class CourseInformationModel : public ModelInterface
{
private:

	string id;
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
	}

	void setId(string id) {
		this->id = id;
	}

	void setCourseName(string courseName) {
		this->courseName = courseName;
	}

	void setClassName(string className) {
		this->className = className;
	}

	void setLecturerAccount(string lecturerAccount) {
		this->lecturerAccount = lecturerAccount;
	}

	void setStartDay(string startDay) {
		this->startDay = startDay;
	}

	void setEndDay(string endDay) {
		this->endDay = endDay;
	}

	void setStartHour(string startHour) {
		this->startHour = startHour;
	}

	void setEndHour(string endHour) {
		this->endHour = endHour;
	}

	void setRoom(string room) {
		this->room = room;
	}

	void setSemester(string semester) {
		this->semester = semester;
	}

	void setYear(string year) {
		this->year = year;
	}

	void setDayOfWeek(string day) {
		this->dayOfWeek = day;
	}

	string getId() {
		return this->id;
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

	vector<vector<string>> FetchCourse() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("id")] = this->id;
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
		conditions[this->getIndex("dayOfWeek")] = this->year;
		return this->fetch(&conditions);
	}

	void UpdateCourse(vector<string> *conditions, vector<string> *toUpdate) {
		this->update(conditions, toUpdate);
	}

	void AddCourse() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("courseName")] = courseName;
		if (this->fetch(&conditions).size() != 0) return;
		vector<string> record;
		record.push_back(this->id);
		record.push_back(this->courseName);
		record.push_back(this->className);
		record.push_back(this->lecturerAccount);
		record.push_back(this->startHour);
		record.push_back(this->endHour);
		record.push_back(this->startDay);
		record.push_back(this->endDay);	
		record.push_back(this->room);
		record.push_back(this->semester);
		record.push_back(this->year);
		record.push_back(this->dayOfWeek);
		this->add(&record);
	}

	void RemoveCourse(vector<string> *toDelete) {
		this->erase(toDelete);
	}
};

#endif // COURSEINFORMATIONMODEL_H_INCLUDED
