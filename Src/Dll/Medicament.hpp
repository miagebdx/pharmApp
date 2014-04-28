/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
+---------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage   : class Medicament                 |
| @methods : Medicament.cpp                   |
+---------------------------------------------+

*/

#ifndef MEDICAMENT_HPP_
#define MEDICAMENT_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "Effet.cpp"


using namespace std;

class Medicament {
private:
	string nomMedicament;
	vector<Effet> lesEffetsIndesirables;
	static int nbDefault;
  	static int nbDestruc;

public:
	Medicament(string);
	Medicament(Medicament const&);
	Medicament(){};
	virtual ~Medicament();

	void setNomMedicament(string);
	string getNomMedicament();
	void appendToEffets(Effet&);
	vector<Effet> getLesEffetsIndesirables();
	Effet getEffetIndesirable(string);
	void setLesEffetsIndesirables(vector<Effet>);

};

#endif
