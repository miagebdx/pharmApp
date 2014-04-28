/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
+---------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage   : Abstract layer for event gesture |
| @methods : Controller.cpp                   |
+---------------------------------------------+
*/

#ifndef DEF_CONTROLLER
#define DEF_CONTROLLER

#include "DataProvider.cpp"

typedef std::map<int, Medicament> dataMap;
typedef std::map<int, Medicament>::iterator dataMapIterator;

typedef std::map<string, double> dataEffet;
typedef std::map<string, double>::iterator dataEffetIterator;



class Controller
{
	private:
		dataMap tabTemp;
		dataEffet tabTempEffets;
		DataProvider database;
		static int nbDefault;
		static int nbDestruc;

	public:
		Controller(bool=false);
		~Controller();

		void displayMenu();

		template <typename T> T dispMedoc(bool=false, bool=false);
		template <typename T> T dispMedocWithEffet(bool=false, bool=false);
		template <typename T> T dispEffetFromMedoc(string, bool=false, bool=false);
		template <typename T> T dispHistogrammeEffet(bool=false, bool=false);
		template <typename T> T dispSearchMedicament(string, bool=false, bool=false);
		template <typename T> T dispMedEnCommunWithEffet(string, int=1, bool=false, bool=false);

		void dispAddMedicament(string, vector<string>);
};

#endif
