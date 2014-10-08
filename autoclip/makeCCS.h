#include<string>
#include<vector>


using namespace std;

struct clip{
	int startPage;
	int startLine;
	int endPage;
	int endLine;
};

enum inout{INPATH,OUTPATH};

/****
* TITLE: moveCursor
* Desc:	Moves the cursor to parameters x, y coordinates.
*/
void moveCursor(int x, int y);

/****
* TITLE: changeColor
* Desc:	Changes the color to a Windows.h console color 
*		designated by an integer RGB value.
*/
void changeColor(int colorCode);

bool checkPath(string path, inout n);

void makeCCS(string inputPath, string outputPath, const string &firstName, const string &lastName, const string &date);

void printVector(vector<string> &v);

void stripDes(vector<string> &v);

vector<clip> getClips(vector<string> &content);

void writeCCSFile(vector<clip> &v, string outpath, const string &firstName, const string &lastName, const string &date);
