/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
+---------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage   : class Effet                      |
| @class : Effet.hpp                          |
+---------------------------------------------+

*/

#include "Effet.hpp"


int Effet::nbDefault=0;
int Effet::nbParam=0;
int Effet::nbDestruc=0;

/**
* Default constructor
*/
Effet::Effet(){
	nbDefault+=1;

}

/**
* Cpoy constructor
*/
Effet::Effet(Effet const& _effet) : nomEffet(_effet.nomEffet), nbOccurence(_effet.nbOccurence) {

};
/**
* Param contrusctor
* @param _nomEffet : name of the effect
* @return void
*/
Effet::Effet(string _nomEffet){
	this->nomEffet = _nomEffet;
	nbParam+=1;

}

/**
* Default destructor
* @return void
*/
Effet::~Effet(){
	nbDestruc+=1;

}

/**
* Get nomEffet
* @return string
*/
string Effet::getNomEffet(){
	return this->nomEffet;
};

/**
* Set nomEffet
* @param _nomEffet : name of the effect
* @return string
*/
void Effet::setNomEffet(string _nomEffet){
	this->nomEffet = _nomEffet;
};

/**
* get nbOccurence
* @return double
*/
double Effet::getNbOccurence(){
	return this->nbOccurence;
};

/**
* set nbOccurence
* @return void
*/
void Effet::setnbOccurence(double _nbOccurence){
	this->nbOccurence = _nbOccurence;
};
