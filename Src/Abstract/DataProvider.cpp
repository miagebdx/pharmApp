/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
+---------------------------------------------+
| @authors : Louis Lainé & Jérémy Morin       |
+---------------------------------------------+
| @usage : Abstract layer for data gesture    |
| @class : DataProvider.hpp                   |
+---------------------------------------------+

*/
#include "DataProvider.hpp"

int DataProvider::nbDefault=0;
int DataProvider::nbDestruc=0;

/**
* default constructor.
* From the ObjectFactory, this function create all the object in the dataStorage
*/
DataProvider::DataProvider() {
	//Making the couple
	try{
		this->dataStorage = this->transformToObjet();
	}catch(ObjectFactory::FactoryException e){
		e.what();
	}
	nbDefault+=1;
}

/**
* copy constructor
*/
DataProvider::DataProvider(DataProvider const& _dataP) : dataStorage(_dataP.dataStorage) {

};

/**
* default destructor, virtual
*/
DataProvider::~DataProvider() {
	// TODO !CodeTemplates.destructorstub.tododesc!
	this->dataStorage.clear();
	nbDestruc+=1;
}

/**
* Set dataStorage.
* @param _datas : the map of the dataStorage
* @return void
*/
void DataProvider::setDataStorage(dataMap _datas){
	this->dataStorage = _datas;
}

/**
* Add \Medicament to the dataStorage instance
* @param : the Medicament
* @return void
*/
void DataProvider::insertIntoMedicament(Medicament& _newMedoc){
	this->dataStorage[this->dataStorage.size()] = _newMedoc;
};

/**
* Get dataStorage
* @return dataMap
*/
dataMap DataProvider::getDataStorage(){
	if (this->dataStorage.empty())
	{
		throw DBException("Undefined database");
	}
	return this->dataStorage;
}


/**
* Retrieve all medicament which are in the
* dataStorage which has the effect in param.
* @param _effet : The effet
* @return dataMap
* @throw \DbException
*/
dataMap DataProvider::getMapMedocFromEffet(string _nomEffet){
	dataMap lesMedoc;
	int cmp = 0;
	for (dataMapIterator it = this->dataStorage.begin(); it != this->dataStorage.end(); ++it)
	{
		for (int i = 0; i < it->second.getLesEffetsIndesirables().size(); ++i)
		{

			// Access to vector<Effet> of each \Medicament
			if(it->second.getLesEffetsIndesirables()[i].getNomEffet() == _nomEffet){
				// Make the array of medicament which contains the effect
				lesMedoc.insert(std::make_pair(cmp, it->second));
			}
			cmp++;
		}
	}

	// Verify if the dataMap empty
	if (lesMedoc.empty())
	{
		throw DBException("Aucun effet correspondant à " + _nomEffet);
	}

	return lesMedoc;
}

/**
* get nbTotalEffet created from ObjectFactory
* @return int
*/
int DataProvider::getNbTotalEffet(){
	return this->nbEffets;
};


/**
* get nb occurence of an \Effet
* @return int
*/
int DataProvider::getNbOccurenceEffet(Effet& _effet){
	int nbOccurences = 0;
	for (dataMapIterator it = this->dataStorage.begin(); it != this->dataStorage.end(); ++it)
	{
		for (int i = 0; i < it->second.getLesEffetsIndesirables().size(); ++i)
		{
			// If \Effet in \Medoc is the same as this _effet then count
			if(it->second.getLesEffetsIndesirables()[i].getNomEffet() == _effet.getNomEffet()){
				++nbOccurences;
			}
		}
	}
	return nbOccurences;

};

/**
* get the average percentage of effet in the db
* @return double
*/
double DataProvider::getHistogramme(Effet& _effet){
	double nbOccu = 0;
	nbOccu = this->getNbOccurenceEffet(_effet);
	if(!nbOccu) throw DBException("Aucun effet correspondant");
  	//cout << nbOccu << "/" << this->nbEffets << endl;
	return (double)(nbOccu / this->getNbTotalEffet()) * 100;
};

/**
* getLesEffets from the dataStorage
* @return dataEffet
*/
dataEffet DataProvider::getLesEffets(){
	int cmp = 0;
	dataEffet tabTemp;
	if(this->dataStorage.empty()) throw DBException("Empty data@DataProvider::getLesEffets");
	for (dataMapIterator it = this->dataStorage.begin(); it != this->dataStorage.end(); ++it)
	{

		for (int i = 0; i < it->second.getLesEffetsIndesirables().size(); ++i)
		{
			//Effet effetTemp;
			//effetTemp = it->second.getLesEffetsIndesirables()[i];
			//effetTemp.setnbOccurence(this->getHistogramme(effetTemp));
			//tabTemp.push_back(effetTemp);

			// Make the Map of string double. 
			tabTemp.insert(std::make_pair(it->second.getLesEffetsIndesirables()[i].getNomEffet(), this->getHistogramme(it->second.getLesEffetsIndesirables()[i])));
		}
		++cmp;
	}
	return tabTemp;
};


/**
* Retrieve the \Medicament which had the maximum \Effet in common with one in param
* Two algorithm provided for this search
* @param : &Medicament 
* @param : int choixAlgo
* @return : dataMap
*/
dataMap DataProvider::getMedicamentEffetsMaxCommun(Medicament& _medicament, int choixAlgo){
	dataMap effetsCommun;
	switch(choixAlgo){
		case 1 : { 
				//Run over all the \Medicament and put in effetCommun those who have a least 
				//one effet in common with the _medicament
				int counter = 0;
				for (dataMapIterator it = this->dataStorage.begin(); it != this->dataStorage.end(); ++it){
					if (it->second.getNomMedicament() != _medicament.getNomMedicament()){		
						for (int i = 0; i < it->second.getLesEffetsIndesirables().size(); ++i){
							for (int j = 0; j < _medicament.getLesEffetsIndesirables().size(); ++j){
								if(it->second.getLesEffetsIndesirables()[i].getNomEffet() == _medicament.getLesEffetsIndesirables()[j].getNomEffet()){	
									effetsCommun.insert(std::make_pair(counter, it->second));
									++counter;	
								}
							} // for j 
						} // for i 
					} // nomMed != nomMed
				} // dataMapIterator 
			break;
		} // case 1
		case 2 : {
			int counter = 0;
			//Put in effetCommun the first two \MEdicament with at least 1 \Effect in common
			for (dataMapIterator it = this->dataStorage.begin(); it != this->dataStorage.end(); ++it){
				if(counter==2) break; 
				if (it->second.getNomMedicament() != _medicament.getNomMedicament()){		
					for (int i = 0; i < it->second.getLesEffetsIndesirables().size(); ++i){
						for (int j = 0; j < _medicament.getLesEffetsIndesirables().size(); ++j){
							if(counter==2) break; 
							if(it->second.getLesEffetsIndesirables()[i].getNomEffet() == _medicament.getLesEffetsIndesirables()[j].getNomEffet()){	
								effetsCommun.insert(std::make_pair(counter, it->second));
								++counter;	
							}
						} // for j
					} // for i 
				} // nomMed != nomMed
			} //dataMapIterator
			break;
		} // case 2
	}
	return effetsCommun;
};


/**
* Get the \Medicament from the string in param
* @param : string
* @return : Medicament
*/
Medicament DataProvider::getTheMedicament(string _nomMedoc){
	Medicament medTemp;
	bool found = false;
	for (dataMapIterator it = this->dataStorage.begin(); it != this->dataStorage.end(); ++it){
		if (it->second.getNomMedicament() == _nomMedoc){
			medTemp = it->second;
			found = true;
		}
	}
	if(!found) throw DBException("Aucun médicament correspondant à " + _nomMedoc);
	return medTemp;
};
