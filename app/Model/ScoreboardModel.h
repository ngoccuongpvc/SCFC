#ifndef SCOREBOARDMODEL_H_INCLUDED
#define SCOREBOARDMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class ScoreboardModel : public ModelInterface
{
private:

	string id;
	string studentId;
	string courseId;
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
		this->studentId = id;
	}

	void setCourseId(string id) {
		this->courseId = id;
	}

	void setTerm(string term) {
		this->term = term;
	}

	void setScore(string score) {
		this->score = score;
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

	vector<vector<string>> FetchScoreboard() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("id")] = this->id;
		conditions[this->getIndex("studentId")] = this->studentId;
		conditions[this->getIndex("courseId")] = this->studentId;
		conditions[this->getIndex("term")] = this->term;
		conditions[this->getIndex("score")] = this->score;
		return this->fetch(&conditions);
	}

	void UpdateScore(vector<string> *condition, vector<string> *toUpdate) {
		this->update(conditions, toUpdate);
	}

	void AddScore() {
		vector<string> record;
		record.push_back(this->id);
		record.push_back(this->studentId);
		record.push_back(this->courseId);
		record.push_back(this->term);
		record.push_back(this->score);
		this->add(&record);
	}

	void DeleteScore(vector<string> *toDelete) {
		this->erase(toDelete);
	}

	

};

#endif // COURSEINFORMATIONMODEL_H_INCLUDED
