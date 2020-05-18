#ifndef COURSEINFORMATIONMODEL_H_INCLUDED
#define COURSEINFORMATIONMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class CourseInformationModel : public ModelInterface
{
private:

	int id;
	string courseName;
	string className;
	string lecturerAccount;
	string startDay;
	string endDay;
	string startHour;
	string endHour;
	string room;
	string semester;

public:
	CourseInformationModel() : ModelInterface("database/CourseInfo.csv") {

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
		return this->getStartHour;
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

	void FetchCourse(string courseName) {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("CourseName")] = courseName;
		vector<string> record = this->fetch(&conditions)[0];
		this->id = stoi(record[0]);
		this->courseName = record[1];
		this->className = record[2];
		this->lecturerAccount = record[3];
		this->startDay = record[4];
		this->endDay = record[5];
		this->startHour = record[6];
		this->endHour = record[7];
		this->room = record[8];
		this->semester = record[9];
	}

	void UpdateCourse(string courseName) {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("CourseName")] = courseName;
		if (this->fetch(&conditions).size() == 0) return;
		vector<string> record = this->fetch(&conditions)[0];
		record[1] = this->courseName;
		record[2] = this->className;
		record[3] = this->lecturerAccount;
		record[4] = this->startDay;
		record[5] = this->endDay;
		record[6] = this->startHour;
		record[7] = this->endHour;
		record[8] = this->room;
		record[9] = this->semester;
		this->update(&conditions, &record);
	}

	void AddCourse() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("CourseName")] = courseName;
		if (this->fetch(&conditions).size() != 0) return;
		vector<string> record;
		record.push_back("0");
		record.push_back(this->courseName);
		record.push_back(this->className);
		record.push_back(this->lecturerAccount);
		record.push_back(this->startDay);
		record.push_back(this->endDay);
		record.push_back(this->startHour);
		record.push_back(this->endHour);
		record.push_back(this->room);
		record.push_back(this->semester);
		this->add(&record);
	}
};

#endif // COURSEINFORMATIONMODEL_H_INCLUDED
