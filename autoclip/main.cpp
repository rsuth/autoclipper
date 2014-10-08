#include<iostream>
#include<string>
#include"makeCCS.h"


using namespace std;


int main(int argc, char* argv[]){
	string inputPath;
	string outputPath;
	string firstName;
	string lastName;
	string date;

	if (argc > 2 ){
		cout << "USAGE: " << argv[0] << " " << "[designation filename] [output filename]";
	}
	else if(argc == 1){
		do{
			cout << "Path to Designation File: ";
			getline(cin, inputPath);
			if(!checkPath(inputPath, INPATH)){ 
				changeColor(12);
				cout << "File Not Found";
				changeColor(7);
				cout << endl;
			}
		} while (!checkPath(inputPath, INPATH));

		do{
			cout << "Path to Output CCS File: ";
			getline(cin, outputPath);
			if(!checkPath(outputPath, OUTPATH)){ 
				changeColor(12);
				cout << "Cannot Create CCS File with Specified Path";
				changeColor(7);
				cout << endl;
			}
		} while (!checkPath(outputPath, OUTPATH));

		cout << "First Name of Deponent: ";
		getline(cin, firstName);
		cout << "Last Name of Deponent: ";
		getline(cin, lastName);
		cout << "Date (MM/DD/YYYY): ";
		getline(cin, date);
		
		makeCCS(inputPath, outputPath, firstName, lastName, date);

	}

	cin.ignore();

}
