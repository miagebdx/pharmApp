/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
+---------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage   : Abstract layer for               |
|            object creator                   |
| @methods : ObjectFactory.cpp                |
+---------------------------------------------+

*/
#ifndef DEF_OBJETFACTORY
#define DEF_OBJETFACTORY

// C+ Library
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// \Object from the DLL
#include "../Parser/ParserFichier.cpp" // Type of Parser to include. Could be XML ...
#include "../Dll/Medicament.cpp"


// Alias for usage
typedef std::map<int, Medicament> dataMap;
typedef std::map<string, std::vector<string> > parserMap;


class ObjectFactory
{
protected:
	ParserFichier *theParser;
	int nbEffets;

private:
	static int nbDefault;
  	static int nbDestruc;

public:
	ObjectFactory();
	ObjectFactory(ObjectFactory const&);
	virtual ~ObjectFactory();

	ParserFichier* getTheParser();
	dataMap transformToObjet();
	
	class FactoryException {
		private:
			string msg;
			string trace;
			string expected;


		public:
			FactoryException(string _msg="NULL", string _trace="NULL", string _expected="NULL"){
				this->msg = _msg;
				this->trace = _trace;
				this->expected = _expected;
			};
			~FactoryException(){

			};
			void what(){
				cout << "EXCEPTION FOUND  ==> " << this->trace << endl;
				cout << "MSG  		 ==> " << this->msg << endl;
				cout << "EXCEPTED	 ==> " << this->expected << endl;
			}

	};
};


#endif
