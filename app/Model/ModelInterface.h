#ifndef MODELINTERFACE_H_INCLUDED
#define MODELINTERFACE_H_INCLUDED

#include <cstring>
#include <fstream>
#include <iostream>
#include "../Utils/myVector.h"
#include <map>
#include <functional>
#include <cmath>

using namespace std;

#define getName(var)  #var

class ModelInterface
{
public:
    string source;
    map<string, function<void()>> mapMethods;
    myVector<string> columns;
    myVector<string> values;

    ifstream *readConnection() {
        ifstream *f = new ifstream(this->source, std::ifstream::in);
        if (f->is_open()) {
            return f;
        } else {
            return nullptr;
        }
    }

    ofstream *writeConnection() {
        ofstream *f = new ofstream(this->source);
        if (f->is_open()) {
            return f;
        } else {
            return nullptr;
        }
    }

	void closeConnection(ifstream *f) {
		delete f;
	}

	void closeConnection(ofstream* f) {
		delete f;
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
    myVector<string> split(string str) {
        myVector<string> v;
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
        getline((*f), str); //exception
        f->close();
		closeConnection(f);
        columns = split(str);
    }

    /**
    Just responsible for assert 2 array
    */
    bool isMeetConditions(myVector<string> *expected, myVector<string> *actual) {
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
    myVector<myVector<string>> fetch (myVector<string> *conditions = nullptr) {
        string str;
        myVector<myVector<string>> result;
        myVector<string> temp;
        ifstream *f = this->readConnection();
        bool getAll = (conditions == nullptr);
        getline((*f), str);
        while (!(*f).eof()) {
            getline((*f), str);
            if (str == "") continue;
            temp = this->split(str);
            if (getAll || isMeetConditions(conditions, &temp)) {
                result.push_back(temp);
            }
        }
        f->close();
		//closeConnection(f);
        return result;
    }

    void save(myVector<myVector<string>>* records) {
        ofstream* f = this->writeConnection();
        for (int i = 0; i < (int)this->columns.size(); ++i) {
            (*f) << this->columns[i];
            if (i != this->columns.size() - 1) {
                (*f) << ",";
            }
        }
        (*f) << endl;

        for (int i = 0; i < (int)records->size(); ++i) {
            for (int j = 0; j < (int)(*records)[i].size(); ++j) {
                (*f) << (*records)[i][j];
                if (j != (*records)[i].size() - 1) {
                    (*f) << ",";
                }
            }
            (*f) << endl;
        }
        f->close();
		//closeConnection(f);
    }

    /*
        add a new record to the end of file
        the first element will be automatically increasing
    */
    void add(myVector<string> *record) {
        myVector<myVector<string>> records = this->fetch();
        int maxId = 0, temp;
        for (int i = 0; i < (int)records.size(); ++i) {
            if (records[i][0] == "") {
                maxId = 0; break;
            }
            temp = stoi(records[i][0]);
            if (temp > maxId) maxId = temp;
        }
        (*record)[0] = to_string(maxId + 1);
        records.push_back(*record);
        this->save(&records);
    }

    /*
        conditions should be initialized by myVector<string> conditions(size, "all"), then specify columns that you want to restrict
        record should be initialized by myVector<string> record(size), then fill to columns that you want to update for ALL records
        that meet the conditions above
    */
    void update(myVector<string>* conditions, myVector<string>* record) {
        myVector<myVector<string>> records = this->fetch();
        for (int i = 0; i < (int)records.size(); ++i) {
            if (this->isMeetConditions(conditions, &records[i])) {
                for (int j = 0; j < (int)records[i].size(); ++j) {
                    if ((*record)[j] != "")
                        records[i][j] = (*record)[j];
                }
            }
        }

        this->save(&records);
    }

    void erase(myVector<string>* conditions) {
        myVector<myVector<string>> records = this->fetch();
        myVector<myVector<string>> newRecords;
        for (int i = 0; i < (int)records.size(); ++i) {
            if (!this->isMeetConditions(conditions, &records[i])) {
                newRecords.push_back(records[i]);
            }
        }

        this->save(&newRecords);
    }

    ModelInterface(string source) {
        this->source = source;
        this->getColumns();

    }

    ~ModelInterface() {
        //this->c/*olumns.clear();
        //this->values.clear();

        //delete this*/;
    }
};

#endif // MODELINTERFACE_H_INCLUDED
