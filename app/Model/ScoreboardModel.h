#ifndef SCOREBOARDMODEL_H_INCLUDED
#define SCOREBOARDMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"

using namespace std;

/*
<Remember to lowercase before setting>
The csv file for this model has the following order:
0. Record ID (1,2,3,...)
1. Student ID (19125001)
2. Course ID (cs162, mth252)
3. Term (midterm/final/lab/bonus/...)
4. Score (1.0-10.0)
*/
class ScoreboardModel : public ModelInterface
{
private:

	string id;
	string studentId; // The incrementing id of UserInformationModel records
	string courseId; // The incrementing id of CourseInformationModel records
	string term;
	string score;

public:
	ScoreboardModel() : ModelInterface("database/ScoreList.csv") {
		this->id = "all";
		this->studentId = "all";
		this->courseId = "all";
		this->term = "all";
		this->score = "all";
	}

	void setStudentId(string id) {
		this->studentId = toLowerCase(id);
	}

	void setCourseId(string id) {
		this->courseId = toLowerCase(id);
	}

	void setTerm(string term) {
		this->term = toLowerCase(term);
	}

	void setScore(string score) {
		this->score = toLowerCase(score);
	}

	string getStudentId() {
		return this->studentId;
	}

	string getCourseId() {
		return this->courseId;
	}

	string getTerm() {
		return this->term;
	}

	string getScore() {
		return this->score;
	}

	/*Before fetching, please ensure that all parameters that are required as conditions are set in model using 'set' functions
	Example: if you want to fetch records with id 69, please set it using Model->setId(69) before fetching.*/
	myVector<myVector<string>> FetchScoreboard() {
		myVector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = this->studentId;
		conditions[this->getIndex("courseId")] = this->courseId;
		conditions[this->getIndex("term")] = this->term;
		conditions[this->getIndex("score")] = this->score;
		return this->fetch(&conditions);
	}


	/*Before adding, please provide all necessary information for the model using the 'set' functions.
	Except that the 'id' of the model (the incrementing id) is not needed.*/
	void AddScore() {
		myVector<string>* record = getScoreboardInfo();
		this->add(record);
	}

	/*Set the values in the model using a myVector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	void setScoreboardInfo(myVector<string>* info) {
		if (info->size() != this->columns.size()) return;
		this->studentId = (*info)[1];
		this->courseId = (*info)[2];
		this->term = (*info)[3];
		this->score = (*info)[4];
	}

	/*Get the values in the model and return as a myVector.
	Please provide all required fields for this model in order, including a blank at the start for an ID.*/
	myVector<string>* getScoreboardInfo() {
		myVector<string>* info = new myVector<string>();
		info->push_back(this->id);
		info->push_back(this->studentId);
		info->push_back(this->courseId);
		info->push_back(this->term);
		info->push_back(this->score);
		return info;
	}

	/*Please provide 2 myVectors for updating. The 'conditions' myVector is the conditions of the records you want to change.
	The 'toUpdate' myVector contains the fields (in the correct order) you want to update in those records. The remaining fields that you don't want to change may be left empty or same as the original record.
	In case you want to update the current record already set in the model, please provide 'nullptr' in 'conditions' field. Please do not leave the 'toUupdate' field blank.*/
	void UpdateScore(myVector<string>* conditions = nullptr, myVector<string>* toUpdate = nullptr) {
		if (toUpdate == nullptr || toUpdate->size() != this->columns.size()) return;
		if (conditions != nullptr && conditions->size() != this->columns.size()) return;
		if (conditions == nullptr) conditions = getScoreboardInfo();
		this->update(conditions, toUpdate);
	}

	/*The 'toDelete' myVector is the conditions of the records you want to delete.
	In case you want to delete the current record already set in the model, please provide 'nullptr' as the 'conditions' parameter.*/
	void DeleteScore(myVector<string>* conditions = nullptr) {
		if (conditions == nullptr || conditions->size() != this->columns.size()) conditions = getScoreboardInfo();
		this->erase(conditions);
	}
	

};

#endif // COURSEINFORMATIONMODEL_H_INCLUDED
