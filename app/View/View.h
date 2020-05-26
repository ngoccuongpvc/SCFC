#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <iostream>
#include <string>
#include "../Utils/vector.h"
#include <iomanip>
#include <fstream>

using namespace std;

class View
{
private:
	string path = "database/exported.csv";
	vector<vector<string>> data;
	vector<string> colHeader;
	vector<int> maxWidth;
	int rowWidth = 0;

	//CALCULATE MAX WIDTH OF EACH COL
	string calculateMaxWidth()
	{
		if (this->data.size() == 0 || this->colHeader.size() == 0) return "null data";
		else if (this->data[0].size() != this->colHeader.size()) return "unmatched data and collumn header";
		else if (this->maxWidth.size() != 0) return "maxWidth initialized before used"; //maxWidth should not be initialized before this
		
		cout << this->data[0].size() << endl;
		this->data.push_back(this->colHeader);
		this->maxWidth = vector<int>(this->data[0].size(), 0);

		for (int i = 0; i < this->data.size(); i++)
		{
			int j = 0;
			for (j; j < this->data[0].size(); j++)
			{
				int temp = this->data[i][j].size();
				if (this->maxWidth[j] < temp) this->maxWidth[j] = temp + 4; //extra 4 space
				if (i == this->data.size() - 1) this->rowWidth += this->maxWidth[j];
			}
		}
		this->data.pop_back();
		return "successfully init maxWidth";
	}

	//ALIGN CENTER FOR EACH CELL
	string center(string input, int width)
	{
		return input + string((width - input.size())/ 2, ' ');
	}

	//HEADER SECTION
	void headerPrint()
	{
		cout << setfill('-') << setw(this->rowWidth + 2*this->colHeader.size()) << '-' << endl;
		for (int i = 0; i < this->colHeader.size(); i++)
		{
			cout << setfill(' ') <<  "|" << setw(this->maxWidth[i]) << center(this->colHeader[i], this->maxWidth[i]) << "|";
		}
		cout << endl << setfill('-') << setw(this->rowWidth + 2 * this->colHeader.size()) << '-' << endl;
		cout << setfill(' ') << setw(0);
		return;
	}

	void headerExport()
	{
		ofstream* f = this->writeConnection();
		for (int i = 0; i < this->colHeader.size(); i++)
		{
			(*f) << this->colHeader[i];
			if (i < this->data.size() - 1) (*f) << ',';
		}
		(*f) << endl;
		f->close();
		this->closeConnection(f);
		return;
	}

	//DATA SECTION
	void dataPrint()
	{
		for (int i = 0; i < this->data.size(); i++)
		{
			for (int j = 0; j < this->data[i].size(); j++)
			{
				cout << setfill(' ') << "|" << setw(this->maxWidth[j]) << center(this->data[i][j], this->maxWidth[j]) << "|";
			}
			cout << endl << setfill('-') << setw(this->rowWidth + 2 * this->colHeader.size()) << '-' << endl;
		}
		cout << setfill(' ') << setw(0);
		return;
	}

	void dataExport()
	{
		ofstream* f = writeConnection();
		for (int i = 0; i < this->data.size(); i++)
		{
			for (int j = 0; j < this->data[i].size(); j++)
			{
				(*f) << this->data[i][j];
				if (j < this->data[i].size() - 1) (*f) << ',';
			}
			(*f) << endl;
		}
		f->close();
		this->closeConnection(f);
		return;
	}
	
	//FILE CONNECTION SECTION

	ofstream* writeConnection()
	{
		if (path == "null") return nullptr;
		ofstream* f;
		f = new ofstream(path, ios::out);
		return f;
	}

	void closeConnection(ofstream* f)
	{
		delete f;
	}
	

public:
	void displayTable()
	{
		//collumn format
		this->headerPrint();
		//data format
		this->dataPrint();
		return;
	}

	void exportTable()
	{
		this->headerExport();
		this->dataExport();
	}

	//init function
	View(vector<vector<string>> data, vector<string> colHeader) {
		this->data = data;
		this->colHeader = colHeader;
		this->calculateMaxWidth();
	}
};

#endif // VIEW_H_INCLUDED
