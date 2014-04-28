/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
+---------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage   : Abstract layer for data gesture  |
+---------------------------------------------+
*/
#ifndef DEF_DATAPROVIDER
#define DEF_DATAPROVIDER

#include "ObjectFactory.cpp"

using namespace std;

typedef std::map<int, Medicament> dataMap;
typedef std::map<int, Medicament>::iterator dataMapIterator;

typedef std::map<string, std::vector<string> > parserMap;
typedef std::map<string, std::vector<string> >::iterator parserMapIterator;


typedef std::map<string, double> dataEffet;
typedef std::map<string, double>::iterator dataEffetIterator;


class DataProvider : public ObjectFactory {
private:
	dataMap dataStorage;
	static int nbDefault;
    static int nbDestruc;


public:
	DataProvider();
	DataProvider(DataProvider const&);
	virtual ~DataProvider();

	void setDataStorage(dataMap _datas);
	void insertIntoMedicament(Medicament&);
	dataMap getDataStorage();
	dataMap getMapMedocFromEffet(string);
	dataMap getMedicamentEffetsMaxCommun(Medicament&, int);

	int getNbTotalEffet();
	int getNbOccurenceEffet(Effet&);
	double getHistogramme(Effet&);

	dataEffet getLesEffets();
	Medicament getTheMedicament(string);

	/**
	* DBException class for DataProvider
	*/
	class DBException {
		private:
			string message;
		public:
			DBException(string _mess="NULL"){
				this->message = _mess;
			};
			~DBException(){};
			void getMessage(){
				cout << this->message << endl;
			}
	};
};

#endif
