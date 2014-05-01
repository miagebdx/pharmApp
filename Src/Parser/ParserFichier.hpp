/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
|+--------------------------------------------+
| @authors : Jérémy Morin & Louis Lainé       |
+---------------------------------------------+      
| @usage   : Parse document storage (.txt)    |
| @methods : ParseFichier.cpp                 |
+---------------------------------------------+

*/


#ifndef PARSERFICHIER_HPP_
#define PARSERFICHIER_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdarg.h>

using namespace std;


typedef std::map<string, std::vector<string> > mapParse;
typedef std::map<string, std::vector<string> >::iterator mapParseIterator;
typedef std::vector<string> leFichier;

class ParserFichier
{

private: 
	int cmpLine;
	mapParse map;
	bool openFile;
   int nbDefault;
    int nbDestruc;


public:
	ParserFichier(){this->nbDefault++;};
	~ParserFichier(){
		this->cmpLine = -1;
		this->openFile=false;
		this->nbDestruc++;
	};
	std::vector<string> copyFile();
	
	void countNbLineInFile();

	string oneLine(int, std::vector<string>);
	mapParse splitLine(string);

	string createLine( leFichier );

	mapParse getMap();
	int getNbLigne();

	class ParserException {
	
	private:
		string msg;
		string trace;
		string expected;

	public:
		ParserException(string _msg="NULL", string _trace="NULL", string _expected="NULL"){
			this->msg = _msg;
			this->trace = _trace;
			this->expected = _expected;
		};
		~ParserException(){

		};
		void what(){
			cout << "EXCEPTION FOUND  ==> " << this->trace << endl;
			cout << "MSG  		 ==> " << this->msg << endl;
			cout << "EXCEPTED	 ==> " << this->expected << endl;
		}

	};


};

#endif