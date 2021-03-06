#ifndef SCOREBOARDCONTROLLER_H_INCLUDED
#define SCOREBOARDCONTROLLER_H_INCLUDED

#include "ControllerInterface.h"
#include "MiscellanousFunctions.h"
#include "AuthorizeController.h"
#include "../Model/AccountModel.h"
#include "../Model/UserInfoModel.h"
#include "../Model/CourseInformationModel.h"
#include "../Model/ScoreboardModel.h"
#include "../Model/AttendanceModel.h"
#include "../View/View.h"
#include "Validation.h"

class ScoreboardController : public ControllerInterface {
private:
	Validation* valid = new Validation();
public:

    void importScoreboard() {
        cout << "Choose file: ";
        string path;
        getline(cin, path);
        ifstream of(path);
        if (!of.is_open()) {
            cout << "File not found, please recheck." << endl;
            return;
        }
        of.close();
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        UserInfoModel* uim = new UserInfoModel();
        ScoreboardModel* sm = new ScoreboardModel();

        ModelInterface* model = new ModelInterface(path);
        myVector<myVector<string>> records = model->fetch();
        if (model->columns.size() != 6) {
            cout << "Invalid input file format. Please recheck." << endl;
            delete cim;
            delete sm;
            delete am;
            delete uim;
            delete model;
            return;
        }

        cout << "Please enter the Course ID: "; string courseId;  valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        if (cim->FetchCourse().size() == 0) {
            cout << "There is no such course." << endl;
            delete cim;
            delete sm;
            delete am;
            delete uim;
            delete model;
            return;
        }
        sm->setCourseId(courseId);

        for (myVector<string> record : records) {
            sm->setStudentId(record[1]);
            sm->setTerm("midterm");
            sm->setScore(record[2]);
            sm->AddScore();
            sm->setTerm("lab");
            sm->setScore(record[3]);
            sm->AddScore();
            sm->setTerm("final");
            sm->setScore(record[4]);
            sm->AddScore();
            sm->setTerm("bonus");
            sm->setScore(record[5]);
            sm->AddScore();
        }

        cout << "Imported Successfully" << endl;
        delete cim;
        delete sm;
        delete am;
        delete uim;
        delete model;
    }

    void searchAndViewScore() {
        ScoreboardModel* sm = new ScoreboardModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string courseId, studentId;
        cout << "Please enter the ID of the course that you want to view score of: "; 
		valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        myVector<myVector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        sm->setCourseId(courseId);
        sm->setScore("");
        sm->setTerm("");
        myVector<myVector<string>> studentResults = sm->FetchScoreboard();
        if (studentResults.size() == 0) {
            cout << "No students was given any score in the given course." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        ScoreboardModel* sm_temp = new ScoreboardModel();
        myVector<myVector<string>> scores;
        sm_temp->setCourseId(courseId);
        for (int i = 0; i < studentResults.size(); ++i) {
            myVector<string> score;
            sm_temp->setStudentId(studentResults[i][1]);
            uim->setStudentId(studentResults[i][1]);
            score.push_back(uim->FetchInfo()[0][1]);
            myVector<myVector<string>> scoreResult = sm_temp->FetchScoreboard();
            string midterm, lab, final, bonus;
            midterm = lab = final = bonus = "";
            for (int k = 0; k < scoreResult.size(); k++) {
                if (scoreResult[k][3] == "midterm") midterm = scoreResult[k][4];
                else if (scoreResult[k][3] == "lab") lab = scoreResult[k][4];
                else if (scoreResult[k][3] == "final") final = scoreResult[k][4];
                else if (scoreResult[k][3] == "bonus") bonus = scoreResult[k][4];
            }
            score.push_back(midterm);
            score.push_back(lab);
            score.push_back(final);
            score.push_back(bonus);
            scores.push_back(score);
        }
        int max_column = 0;
        for (int i = 0; i < scores.size(); ++i) {
            if (scores[i].size() > max_column) max_column = scores[i].size();
        }
        myVector<string> header; header.push_back("Student ID");
        header.push_back("Midterm");
        header.push_back("Lab");
        header.push_back("Final");
        header.push_back("Bonus");
        View* view = new View(scores, header);
        view->displayTable();
        delete view;
        delete sm;
        delete sm_temp;
        delete cim;
        delete uim;

    }

    void exportScoreboard() {
        cout << "Choose file to export to: ";
        string path;
        getline(cin, path);
        ScoreboardModel* sm = new ScoreboardModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string courseId, studentId;
        cout << "Please enter the ID of the course whose scoreboard you want to export: "; 
		valid->read(courseId, "nospc");
        cim->setCourseId(courseId);
        sm->setTerm("");
        sm->setScore("");
        myVector<myVector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        sm->setCourseId(courseId);
        myVector<myVector<string>> studentResults = sm->FetchScoreboard();
        if (studentResults.size() == 0) {
            cout << "No students was given any score in the given course." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        ScoreboardModel* sm_temp = new ScoreboardModel();
        myVector<myVector<string>> scores;
        sm_temp->setCourseId(courseId);
        for (int i = 0; i < studentResults.size(); ++i) {
            myVector<string> score;
            sm_temp->setStudentId(studentResults[i][1]);
            uim->setStudentId(studentResults[i][1]);
            score.push_back(uim->FetchInfo()[0][1]);
            myVector<myVector<string>> scoreResult = sm_temp->FetchScoreboard();
            string midterm, lab, final, bonus;
            midterm = lab = final = bonus = "";
            for (int k = 0; k < scoreResult.size(); k++) {
                if (scoreResult[k][3] == "midterm") midterm = scoreResult[k][4];
                else if (scoreResult[k][3] == "lab") lab = scoreResult[k][4];
                else if (scoreResult[k][3] == "final") final = scoreResult[k][4];
                else if (scoreResult[k][3] == "bonus") bonus = scoreResult[k][4];
            }
            score.push_back(midterm);
            score.push_back(lab);
            score.push_back(final);
            score.push_back(bonus);
            scores.push_back(score);
        }
        myVector<string> header; header.push_back("Student ID");
        header.push_back("Midterm");
        header.push_back("Lab");
        header.push_back("Final");
        header.push_back("Bonus");
        View* view = new View(scores, header);
        view->setPath(path);
        view->exportTable();
        cout << "Successfully exported scoreboard to " << path << endl;
        delete view;
        delete sm;
        delete sm_temp;
        delete cim;
        delete uim;
    }

    void editScore()
    {
        cout << "Please be aware that you can only edit only one score at a time." << endl;
        ScoreboardModel* sm = new ScoreboardModel();
        string courseId, studentId, term;
        cout << "Please enter course id: "; valid->read(courseId, "nospc");; sm->setCourseId(courseId);
        cout << "Please enter student id: "; valid->read(studentId, "nospc"); sm->setStudentId(studentId);

        cout << "Below is the current score of that student in the course: " << endl;
        myVector<string> score;
        myVector<myVector<string>> scoreResult = sm->FetchScoreboard();
        string midterm, lab, final, bonus;
        midterm = lab = final = bonus = "";
        for (int k = 0; k < scoreResult.size(); k++) {
            if (scoreResult[k][3] == "midterm") midterm = scoreResult[k][4];
            else if (scoreResult[k][3] == "lab") lab = scoreResult[k][4];
            else if (scoreResult[k][3] == "final") final = scoreResult[k][4];
            else if (scoreResult[k][3] == "bonus") bonus = scoreResult[k][4];
        }
        score.push_back(midterm);
        score.push_back(lab);
        score.push_back(final);
        score.push_back(bonus);
        myVector<myVector<string>> scores; scores.push_back(score);
        myVector<string> header;
        header.push_back("Midterm");
        header.push_back("Lab");
        header.push_back("Final");
        header.push_back("Bonus");
        View* view = new View(scores, header);
        view->displayTable();

        cout << "Please enter the term (midterm/final/bonus/lab)"; valid->read(term, "term"); sm->setTerm(term);

        myVector<myVector<string>> conditions = sm->FetchScoreboard();
        if (conditions.size() == 0)
        {
            delete sm;
            cout << "Cannot find this student/course/term" << endl;
            return;
        }

        string scoreT;
        cout << "Please enter the score (0.00 - 10.00): "; valid->read(scoreT, "score");
        cout << "Successfully updated the score." << endl;
        sm->setScoreboardInfo(&conditions[0]);
        myVector<string> record = conditions[0];
        cout << conditions[0][4] << endl;
        record[4] = scoreT;
        cout << conditions[0][4] << endl;
        sm->UpdateScore(nullptr, &record);
        delete sm;
        delete view;
        return;
    }

    void viewScoreOfCourse() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        ScoreboardModel* sm = new ScoreboardModel();
        string courseId, studentId = globalUsername;
        cout << "Please enter the ID of the course that you want to view score of: "; 
		valid->read(courseId, "nospc");
        cim->setCourseId(courseId);

        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete uim;
            delete sm;
            return;
        }
        //cout << "Please enter your student Id: "; cin >> studentId;
        uim->setStudentId(studentId);
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete cim;
            delete uim;
            delete sm;
            return;
        }
        sm->setStudentId(studentId);
        sm->setCourseId(courseId);
        myVector<myVector<string>> scoreboard = sm->FetchScoreboard();
        if (scoreboard.size() == 0) {
            cout << "You are not enrolled in this course or there hasn't been any score added." << endl;
            delete cim;
            delete uim;
            delete sm;
            return;
        }
        myVector<myVector<string>> scores;
        for (int i = 0; i < scoreboard.size(); ++i) {
            myVector<string> score(2, "unmarked");
            if (scoreboard[i][3] != "" && scoreboard[i][4] != "") {
                score[0] = scoreboard[i][3];
                score[1] = scoreboard[i][4];
            }
            
            scores.push_back(score);
        }
        myVector<string> header; header.push_back("Term"); header.push_back("Score");
        View* view = new View(scores, header);
        view->displayTable();

        delete cim;
        delete uim;
        delete sm;
        delete view;
    }

    ScoreboardController() {
        this->mapMethods["importScoreboard"] = [this]() {importScoreboard(); };
        this->mapMethods["editScore"] = [this]() { editScore(); };
        this->mapMethods["exportScoreboard"] = [this]() { exportScoreboard(); };
        this->mapMethods["searchAndViewScore"] = [this]() { searchAndViewScore(); };
        this->mapMethods["viewScoreOfCourse"] = [this]() { viewScoreOfCourse(); };
    }

	~ScoreboardController() {
		delete valid;
	}
};

#endif