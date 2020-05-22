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
    void searchAndViewScore() {
        ScoreboardModel* sm = new ScoreboardModel();
        CourseInformationModel* cim = new CourseInformationModel();
        UserInfoModel* uim = new UserInfoModel();
        string studentIdentifier, courseId, studentId;
        cout << "Please enter the ID of the course that you want to edit: "; string courseIdentifier; cin >> courseIdentifier;
        cim->setCourseId(toLowerCase(courseIdentifier));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        sm->setCourseId(courseId);
        sm->setScore("");
        sm->setTerm("");
        vector<vector<string>> studentResults = sm->FetchScoreboard();
        if (studentResults.size() == 0) {
            cout << "No students was given any score in the given course." << endl;
            return;
        }
        ScoreboardModel* sm_temp = new ScoreboardModel();
        vector<vector<string>> scores;
        sm_temp->setCourseId(courseId);
        for (int i = 0; i < studentResults.size(); ++i) {
            vector<string> score;
            sm_temp->setStudentId(studentResults[i][1]);
            uim->setId(studentResults[i][1]);
            vector<vector<string>> users = uim->FetchInfo();
            score.push_back(users[0][1]);
            vector<vector<string>> scoreResult = sm_temp->FetchScoreboard();
            for (int k = 0; k < scoreResult.size(); k++) {
                string scoreLine = scoreResult[k][3] + ":" + scoreResult[k][4];
                score.push_back(scoreLine);
            }
        }
        int max_column = 0;
        for (int i = 0; i < scores.size(); ++i) {
            if (scores[i].size() > max_column) max_column = scores[i].size();
        }
        vector<string> header; header.push_back("Course Name");
        for (int i = 0; i < max_column; ++i) header.push_back(" ");
        View* view = new View(scores, header);
        view->displayTable();
        delete view;
        delete sm;
        delete sm_temp;
        delete cim;
        delete uim;

    }

    void exportScoreboard() {

    }

    void editScore()
    {
        cout << "Editting score of student!" << endl;
        ScoreboardModel* sm = new ScoreboardModel();
        string courseId, studentId, term;
        cout << "Plz enter course id: "; cin >> courseId; sm->setCourseId(courseId);
        cout << "Plz enter student id "; cin >> studentId; sm->setStudentId(studentId);
        cout << "Plz enter the term(mid/final)"; cin >> term; sm->setTerm(term);

        vector<vector<string>> conditions = sm->FetchScoreboard();
        if (conditions.size() == 0)
        {
            delete sm;
            cout << "Can't find this student/course/term" << endl;
            return;
        }

        string score;
        cout << "Plz enter the score: "; cin >> score;
        vector<string> record = conditions[0];
        record[sm->getIndex["score"]] = score;
        sm->UpdateScore(&conditions[0], &record);
        delete sm;
        return;
    }

    void viewScoreOfCourse() {
        UserInfoModel* uim = new UserInfoModel();
        CourseInformationModel* cim = new CourseInformationModel();
        ScoreboardModel* sm = new ScoreboardModel();
        if (role != "student") return;
        string studentIdentifier, courseId, studentId, day;
        cout << "Please enter the ID of the course that you want to edit: "; string courseIdentifier; cin >> courseIdentifier;
        cim->setCourseId(toLowerCase(courseIdentifier));
        vector<vector<string>> courseResult = cim->FetchCourse();
        if (courseResult.size() == 0) {
            cout << "The course you entered does not exist." << endl;
            return;
        }
        courseId = courseResult[0][0];
        cout << "Please enter your student Id: "; cin >> studentIdentifier;
        uim->setStudentID(toLowerCase(studentIdentifier));
        vector<vector<string>> studentResult = uim->FetchInfo();
        if (studentResult.size() == 0) {
            cout << "The student ID you entered does not exist." << endl;
            return;
        }
        studentId = studentResult[0][0];
        sm->setStudentId(studentId);
        sm->setCourseId(courseId);
        vector<vector<string>> scoreboard = sm->FetchScoreboard();
        if (scoreboard.size() == 0) {
            cout << "You are not enrolled in this course." << endl;
            return;
        }
        vector<vector<string>> scores;
        for (int i = 0; i < scoreboard.size(); ++i) {
            vector<string> score;
            score.push_back(scoreboard[i][3]);
            score.push_back(scoreboard[i][4]);
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
        this->mapMethods["editScore"] = [this]() { editScore(); };
        this->mapMethods["exportScoreboard"] = [this]() { exportScoreboard(); };
        this->mapMethods["searchAndViewScore"] = [this]() { searchAndViewScore(); };
        this->mapMethods["viewScoreOfCourse"] = [this]() { viewScoreOfCourse(); };
    }
};

#endif