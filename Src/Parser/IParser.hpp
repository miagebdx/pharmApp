/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
|+--------------------------------------------+
| @authors : Jérémy Morin & Louis Lainé       |
+---------------------------------------------+      
| @usage   : Interface for parsing issue      |
| @methods : ParseFichier.cpp                 |
+---------------------------------------------+

*/

#ifndef DEF_IParser
#define DEF_IParser

#include <string>
#include <map>
#include <vector>

using namespace std;

class IParser
{
private:
	int cmpLine;
	std::map<string, std::vector<string> >  map;
	bool openFile;

public:
	IParser();
	~IParser();

	virtual std::vector<string> copyFile() = 0;
	
	virtual void countNbLineInFile() = 0;

	virtual	string oneLine(int, std::vector<string>) = 0;
	virtual std::map<string, std::vector<string> >  splitLine(string) = 0;

	virtual string createLine(std::vector<string>) = 0;

	virtual std::map<string, std::vector<string> >  getMap() = 0;
	virtual int getNbLigne() = 0; 

	
};
#endif