#ifndef SCOREBOARDMODEL_H_INCLUDED
#define SCOREBOARDMODEL_H_INCLUDED

#include <iostream>
#include <string>
#include "../Model/ModelInterface.h"
using namespace std;

class ScoreboardModel : public ModelInterface
{
private:

	int id;
	int studentId;
	int courseId;
	string term;
	string score;

public:
	ScoreboardModel() : ModelInterface("database/ScoreList.csv") {

	}

	void setStudentId(int id) {
		this->studentId = id;
	}

	void setCourseId(int id) {
		this->courseId = id;
	}

	void setTerm(string term) {
		this->term = term;
	}

	void setScore(string score) {
		this->score = score;
	}

	int getStudentId() {
		return this->studentId;
	}

	int getCourseId() {
		return this->courseId;
	}

	string getTerm() {
		return this->term;
	}

	string getScore() {
		return this->score;
	}

	vector<vector<string>> FetchScoreStudent() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = this->studentId;
		return this->fetch(&conditions);
	}

	vector<vector<string>> FetchScoreCourse() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("courseId")] = this->courseId;
		return this->fetch(&conditions);
	}
	
	vector<vector<string>> FetchScoreStudentAndCourse() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = this->studentId;
		conditions[this->getIndex("courseId")] = this->courseId;
		return this->fetch(&conditions);
	}

	vector<vector<string>> FetchTermScore() {
		vector<string> conditions(this->columns.size(), "all");
		conditions[this->getIndex("studentId")] = this->studentId;
		conditions[this->getIndex("courseId")] = this->courseId;
		conditions[this->getIndex("term")] = this->term;
		return this->fetch(&conditions);
	}

	void UpdateScore() {
		vector<vector<string>> records = FetchTermScore();
		if (records.size() == 0) return;
		vector<string> conditions = records[0];
		vector<string> toUpdate = records[0];
		toUpdate[4] = this->score;
		this->update(&conditions, &toUpdate);
	}

	void AddScore() {
		vector<string> record;
		record.push_back("0");
		record.push_back(to_string(this->studentId));
		record.push_back(to_string(this->courseId));
		record.push_back(this->term);
		record.push_back(this->score);
		this->add(&record);
	}

	

};

#endif // COURSEINFORMATIONMODEL_H_INCLUDED
