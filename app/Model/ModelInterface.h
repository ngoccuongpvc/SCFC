#ifndef MODELINTERFACE_H_INCLUDED
#define MODELINTERFACE_H_INCLUDED

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>

using namespace std;

#define getName(var)  #var

class ModelInterface
{
public:
    string source;
    map<string, function<void()>> mapMethods;
    vector<string> columns;
    vector<string> values;

    ifstream *readConnection() {
        ifstream *f = new ifstream(this->source, std::ifstream::in);
        if (f->is_open()) {
            return f;
        } else {
            return nullptr;
        }
    }

    ofstream *writeConnection() {
        ofstream *f = new ofstream(this->source, std::ofstream::app);
        if (f->is_open()) {
            return f;
        } else {
            return nullptr;
        }
    }

    /**
    get the corresponding index of column order
    */
    int getIndex(string variableName) {
        for (int i=0; i<(int)columns.size(); ++i) {
            if (columns[i] == variableName) {
                return i;
            }
        }
        return -1;
    }

    /**
    split the string into many strings separated by ","
    */
    vector<string> split(string str) {
        vector<string> v;
        string temp = "";
        for (int i=0; i<(int)str.size(); ++i) {
            if (str[i] == ',') {
                v.push_back(temp);
                temp = "";
            } else {
                temp = temp + str[i];
            }
        }
        v.push_back(temp);
        return v;
    }

    /**
    Get the first line of csv file, which contains columns names
    */
    void getColumns() {
        ifstream *f = this->readConnection();
        string str;
        getline((*f), str);
        f->close();
        columns = split(str);
    }

    /**
    Just responsible for assert 2 array
    */
    bool isMeetConditions(vector<string> *expected, vector<string> *actual) {
        if (expected->size() != actual->size()) {
            return false;
        }
        for (int i=0; i<(int)expected->size(); ++i) {
            if ((*expected)[i] != "all" && (*expected)[i] != (*actual)[i]) {
                return false;
            }
        }
        return true;
    }

    /**
    Get all records that meet the conditions.
    For fields that is set = "all", it will be skipped
    if no arguments is passed into fetch, it will return all records
    */
    vector<vector<string>> fetch (vector<string> *conditions = nullptr) {
        string str;
        vector<vector<string>> result;
        vector<string> temp;
        ifstream *f = this->readConnection();
        bool getAll = (conditions == nullptr);
        getline((*f), str);
        while (!(*f).eof()) {
            getline((*f), str);
            temp = this->split(str);
            if (getAll || isMeetConditions(conditions, &temp)) {
                result.push_back(temp);
            }
        }
        return result;
    }

    ModelInterface(string source) {
        this->source = source;
        this->getColumns();

    }

    ~ModelInterface() {
        this->columns.clear();
        this->values.clear();

        delete this;
    }
};

#endif // MODELINTERFACE_H_INCLUDED
