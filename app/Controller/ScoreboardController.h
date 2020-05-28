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

class ScoreboardController : public ControllerInterface {
private:
public:

    void importScoreboard() {
        cout << "Choose file: ";
        string path;
        getline(cin, path);
        CourseInformationModel* cim = new CourseInformationModel();
        AttendanceModel* am = new AttendanceModel();
        UserInfoModel* uim = new UserInfoModel();
        ScoreboardModel* sm = new ScoreboardModel();

        ModelInterface* model = new ModelInterface(path);
        vector<vector<string>> records = model->fetch();
        if (model->columns.size() != 6) {
            cout << "Invalid input file format. Please recheck." << endl;
            delete cim;
            delete sm;
            delete am;
            delete uim;
            delete model;
            return;
        }

        cout << "Please enter the Course ID: "; string courseId;  getline(cin, courseId);
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

        for (vector<string> record : records) {
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
        cout << "Please enter the ID of the course that you want to view score of: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        vector<vector<string>> courseResult = cim->FetchCourse();
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
        vector<vector<string>> studentResults = sm->FetchScoreboard();
        if (studentResults.size() == 0) {
            cout << "No students was given any score in the given course." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        ScoreboardModel* sm_temp = new ScoreboardModel();
        vector<vector<string>> scores;
        sm_temp->setCourseId(courseId);
        for (int i = 0; i < studentResults.size(); ++i) {
            vector<string> score;
            sm_temp->setStudentId(studentResults[i][1]);
            uim->setStudentId(studentResults[i][1]);
            score.push_back(uim->FetchInfo()[0][1]);
            vector<vector<string>> scoreResult = sm_temp->FetchScoreboard();
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
        vector<string> header; header.push_back("Student ID");
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
        cin >> path;
        ScoreboardModel* sm = new ScoreboardModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string courseId, studentId;
        cout << "Please enter the ID of the course whose scoreboard you want to export: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        sm->setTerm("");
        sm->setScore("");
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        sm->setCourseId(courseId);
        vector<vector<string>> studentResults = sm->FetchScoreboard();
        if (studentResults.size() == 0) {
            cout << "No students was given any score in the given course." << endl;
            delete sm;
            delete cim;
            delete uim;
            return;
        }
        ScoreboardModel* sm_temp = new ScoreboardModel();
        vector<vector<string>> scores;
        sm_temp->setCourseId(courseId);
        for (int i = 0; i < studentResults.size(); ++i) {
            vector<string> score;
            sm_temp->setStudentId(studentResults[i][1]);
            uim->setStudentId(studentResults[i][1]);
            score.push_back(uim->FetchInfo()[0][1]);
            vector<vector<string>> scoreResult = sm_temp->FetchScoreboard();
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
        vector<string> header; header.push_back("Student ID");
        header.push_back("Midterm");
        header.push_back("Lab");
        header.push_back("Final");
        header.push_back("Bonus");
        View* view = new View(scores, header);
        view->setPath(path);
        view->exportTable();
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
        cout << "Please enter course id: "; getline(cin, courseId);; sm->setCourseId(courseId);
        cout << "Please enter student id "; getline(cin, studentId);; sm->setStudentId(studentId);
        cout << "Pleasee enter the term (midterm/final/bonus/lab)"; cin >> term; sm->setTerm(term);

        vector<vector<string>> conditions = sm->FetchScoreboard();
        if (conditions.size() == 0)
        {
            delete sm;
            cout << "Cannot find this student/course/term" << endl;
            return;
        }

        string score;
        cout << "Please enter the score: "; cin >> score;
        vector<string> record = conditions[0];
        record[4] = score;
        sm->UpdateScore(&conditions[0], &record);
        delete sm;
        return;
    }

    void viewScoreOfCourse() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        ScoreboardModel* sm = new ScoreboardModel();
        string courseId, studentId = globalUsername, day;
        cout << "Please enter the ID of the course that you want to view score of: "; getline(cin, courseId);
        cim->setCourseId(toLowerCase(courseId));
        if (cim->FetchCourse().size() == 0) {
            cout << "The course you entered does not exist." << endl;
            delete cim;
            delete uim;
            delete sm;
            return;
        }
        //cout << "Please enter your student Id: "; cin >> studentId;
        uim->setStudentId(toLowerCase(studentId));
        if (uim->FetchInfo().size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            delete cim;
            delete uim;
            delete sm;
            return;
        }
        sm->setStudentId(toLowerCase(studentId));
        sm->setCourseId(toLowerCase(courseId));
        vector<vector<string>> scoreboard = sm->FetchScoreboard();
        if (scoreboard.size() == 0) {
            cout << "You are not enrolled in this course." << endl;
            delete cim;
            delete uim;
            delete sm;
            return;
        }
        vector<vector<string>> scores;
        for (int i = 0; i < scoreboard.size(); ++i) {
            vector<string> score(2, "unmarked");
            if (scoreboard[i][3] != "" && scoreboard[i][4] != "") {
                score[0] = scoreboard[i][3];
                score[1] = scoreboard[i][4];
            }
            
            scores.push_back(score);
        }
        vector<string> header; header.push_back("Term"); header.push_back("Score");
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
};

#endif