/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
|+--------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage : class Medicament                   |
| @class : Medicament.hpp                     |
+---------------------------------------------+

*/
#include "Medicament.hpp"

int Medicament::nbDefault=0;
int Medicament::nbDestruc=0;

/**
* Constructor with param
* _nomMedoc : name of the medicament
*/
Medicament::Medicament(string _nomMedoc) {
	this->nomMedicament = _nomMedoc;
	nbDefault+=1;
}


Medicament::Medicament(Medicament const& _medic) 
	: nomMedicament(_medic.nomMedicament), lesEffetsIndesirables(_medic.lesEffetsIndesirables) {

};

/**
* Destructor
*/
Medicament::~Medicament() {
	nbDestruc=+1;
}

/**
* set idMedicament
* @param _nomMedoc : name of the medicament
* @return void
*/
void Medicament::setNomMedicament(string _nomMedoc){
	this->nomMedicament = _nomMedoc;
}

/**
* Get nomMedicament
* @return string
*/
string Medicament::getNomMedicament(){
	return this->nomMedicament;
}

/**
* Get lesEffetsIndesirables
* @return vector<Effet>
*/
vector<Effet> Medicament::getLesEffetsIndesirables(){
	return this->lesEffetsIndesirables;
}

/**
* Set lesEfetsIndesirables
* @param  vector \Effet 
* @return void 
*/
void Medicament::setLesEffetsIndesirables(vector<Effet> _lesEffets){
	this->lesEffetsIndesirables = _lesEffets;
};

/**
* Set lesEffetsIndesirables
* @param \Effet
* @return void
*/
void Medicament::appendToEffets(Effet& _effet){
	this->lesEffetsIndesirables.push_back(_effet);
}

/**
* Fetch the researched effect in the vector<Effet> array.
* Get EffetIndesirable
* @param _nomEffet : the name of the effect
* @return Effet
*/
Effet Medicament::getEffetIndesirable(string _nomEffet){
	Effet theEffet;
	for(int i = 0 ; i < this->lesEffetsIndesirables.size() ; ++i){
		if(this->lesEffetsIndesirables[i].getNomEffet() == _nomEffet){
			theEffet = this->lesEffetsIndesirables[i];
			break;
		}
	}
	return theEffet;
}
