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
| @class : ObjectFactory.hpp                  |
+---------------------------------------------+

*/

#include "ObjectFactory.hpp"

int ObjectFactory::nbDefault=0;
int ObjectFactory::nbDestruc=0;

/**
* Constructor
* @return void
*/
ObjectFactory::ObjectFactory(){
	//cout << "ObjectFactory" << endl;
	this->theParser = new ParserFichier();
	this->nbEffets = 0;
	nbDefault+=1;
};

ObjectFactory::ObjectFactory(ObjectFactory const& _objFct) : theParser(_objFct.theParser), nbEffets(_objFct.nbEffets) {


};

/**
* Destructor
* @return void
*/
ObjectFactory::~ObjectFactory(){
	delete this->theParser;
	nbDestruc+=1;
};

/**
* Get \theParser
* @return \ParserFichier
*/
ParserFichier* ObjectFactory::getTheParser(){
	return this->theParser;
}

/**
* Make all the object from the the \Parser string, vector<string>
* @return dataMap
*/
dataMap ObjectFactory::transformToObjet(){
	dataMap theObjectMap;
	parserMap theStringMap;

	//string theFichier = "./liste.txt";

	this->theParser->countNbLineInFile();
	int nbLignesFichiers = this->theParser->getNbLigne();

	//Get file
	vector<string> lesLines;
	try{
		lesLines = this->theParser->copyFile();
	}catch(ParserFichier::ParserException e){
		e.what();
	}

	if (nbLignesFichiers < 1)
	{
		throw FactoryException("countNbLineInFile return a < 1 integer", "ObjectFactory.cpp::transformToObjet::43", "> 1 INTEGER") ;
	}


	for (int i = 0; i < nbLignesFichiers; ++i) {
		Medicament theMedoc;
		 // Access to the i line
		theStringMap = this->theParser->splitLine(this->theParser->oneLine(i, lesLines));

		//Check if not empty avoid output_range exception
		if (!theStringMap.begin()->first.empty())
		{
			//new Medicament from the i->first element of the map
			theMedoc.setNomMedicament(theStringMap.begin()->first);

			for (int j = 0; j < theStringMap.begin()->second.size(); ++j)
			{
				//new Effet corresponding to the i->second[j]
				Effet theEffet(theStringMap.begin()->second[j]);
				theMedoc.appendToEffets(theEffet);
				++this->nbEffets; //iterate for nbEffet created during the generation
			}

		}
		// Insert into the dataMap <int, Medicament>
		theObjectMap.insert(std::make_pair(i, theMedoc));
	}


	return theObjectMap;
};


/*
void ObjectFactory::test(){
	this->theParser->test();
	this->theParser->getNombreLigneFichier();

	int nbLignesFichiers = this->theParser->getNbLigne();

	cout << nbLignesFichiers << endl;
}
*/
