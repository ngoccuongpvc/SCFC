#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class View
{
private:
	vector<vector<string>> data;
	vector<string> colHeader;
	vector<int> maxWidth;
	int rowWidth = 0;

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
				if (this->maxWidth[j] < temp) this->maxWidth[j] = temp + 4; //extra 2 space
				if (i == this->data.size() - 1) this->rowWidth += this->maxWidth[j];
			}
		}
		this->data.pop_back();
		return "successfully init maxWidth";
	}

	string center(string input, int width)
	{
		return input + string((width - input.size())/ 2, ' ');
	}

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
		system("pause");
		cout << setfill(' ') << setw(0);
		return;
	}

public:
	void displayTable()
	{
		//print out
		if (this->maxWidth.size() == 0 || this->rowWidth == 0) return;
		//collumn format
		this->headerPrint();
		//data format
		this->dataPrint();
		
		return;
	}

	//init function
	View(vector<vector<string>> data, vector<string> colHeader) {
		this->data = data;
		this->colHeader = colHeader;
		this->calculateMaxWidth();
	}
};

#endif // VIEW_H_INCLUDED
