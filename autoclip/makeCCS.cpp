#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<fstream>
#include<Windows.h>
#include<boost/algorithm/string.hpp>
#include"makeCCS.h"


using namespace std;

bool checkPath(string path, inout n){
	
	bool isGood;

	if(n == INPATH){
		ifstream checker;
		checker.open(path.c_str());
	
		if(!checker){
			isGood = false;
			checker.close();
		}
		else{
			isGood = true;
			checker.close();
		}
	}
	else{
		
		ofstream checker;
		checker.open(path.c_str());
	
		if(!checker){
			isGood = false;
			checker.close();
		}
		else{
			isGood = true;
			checker.close();
		}
	}

	return isGood;
}

void makeCCS(string inputPath, string outputPath, const string &firstName, const string &lastName, const string &date){
	
	ifstream input;
	string line;
	vector<string> content;
	vector<clip> clips;

	input.open(inputPath.c_str());
	while(getline(input, line)){
		content.push_back(line);
	}
	input.close();

	stripDes(content);
	cout << "Input designations:\n\n";
	printVector(content);
	clips = getClips(content);
	cout << "\n\n";
	writeCCSFile(clips, outputPath, firstName, lastName, date);

	
}

void printVector(vector<string> &v){
	for(unsigned int i = 0; i < v.size(); i++){
		cout << v[i] << endl;
	}
}

void stripDes(vector<string> &v){
	for(unsigned int i = 0; i < v.size(); i++){
		boost::erase_all(v[i], " ");
	}
}

vector<clip> getClips(vector<string> &content){
	vector<clip> allClips;
	vector<string> seperated;
	clip tempClip;

	for(unsigned int i = 0; i < content.size(); i++){
		boost::split(seperated, content[i], boost::is_any_of(":-."));
		
		tempClip.startPage = stoi(seperated[0]);
		tempClip.startLine = stoi(seperated[1]);
		
		if(seperated.size() == 3){
			tempClip.endPage = stoi(seperated[0]);
			tempClip.endLine = stoi(seperated[2]);
		}

		else if(seperated.size() == 4){
			tempClip.endPage = stoi(seperated[2]);
			tempClip.endLine = stoi(seperated[3]);
		}

		allClips.push_back(tempClip);
	}

	return allClips;
}

void writeCCSFile(vector<clip> &v, string outpath, const string &firstName, const string &lastName, const string &date){
	ofstream output;
	output.open(outpath.c_str());
	if(output){
			output << "!(" << lastName << ", " << firstName << " - " << date << ")" << endl;
		for(unsigned int i = 0; i < v.size(); i++){
			output << "\nC()\nD()\n";
			output << setfill('0') << setw(5) << v[i].startPage 
				 << setw(1) << ":" << setw(2) << v[i].startLine
				 << " - " 
				 << setw(5) << v[i].endPage 
				 << setw(1) << ":" << setw(2) << v[i].endLine << endl;
		}
		
		output.close();
		changeColor(10);
		cout << "CCS File Created: " << outpath;
		changeColor(7);
	}
	else{
		changeColor(12);
		cout << "\nError writing File.\nCheck path spelling or Specify a different path for ouput file";
		changeColor(7);
	}

	
}

void changeColor(int colorValue){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorValue);
}

void moveCursor(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}