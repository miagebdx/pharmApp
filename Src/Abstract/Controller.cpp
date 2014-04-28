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
| @class   : Controller.hpp                   |
+---------------------------------------------+
*/


#define RESET   "\033[0m"
#define BLACK   "\033[30m"      
#define RED     "\033[31m"     
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"      
#define BOLDBLACK   "\033[1m\033[30m"       
#define BOLDRED     "\033[1m\033[31m"      
#define BOLDGREEN   "\033[1m\033[32m"      
#define BOLDYELLOW  "\033[1m\033[33m"      
#define BOLDBLUE    "\033[1m\033[34m"      
#define BOLDMAGENTA "\033[1m\033[35m"      
#define BOLDCYAN    "\033[1m\033[36m"      
#define BOLDWHITE   "\033[1m\033[37m"     

#include "Controller.hpp"

int Controller::nbDefault=0;
int Controller::nbDestruc=0;

/**
* Default construct
* @return void
*/
Controller::Controller(bool asDisplay){
	this->tabTemp.clear();
	if (asDisplay){

		/*
		    ____  __                               ___              
		   / __ \/ /_  ____ __________ ___  ____ _/   |  ____  ____ 
		  / /_/ / __ \/ __ `/ ___/ __ `__ \/ __ `/ /| | / __ \/ __ \
		 / ____/ / / / /_/ / /  / / / / / / /_/ / ___ |/ /_/ / /_/ /
		/_/   /_/ /_/\__,_/_/  /_/ /_/ /_/\__,_/_/  |_/ .___/ .___/ 
		                                             /_/   /_/      

		*/
		cout << GREEN; 
		string a = "    ____  __                               ___               "; cout << a << endl;
		string b = "   / __ \\/ /_  ____ __________ ___  ____ _/   |  ____  ____  "; cout << b << endl;
		string c = "  / /_/ / __ \\/ __ `/ ___/ __ `__ \\/ __ `/ /| | / __ \\/ __ \\ "; cout << c << endl;
		string d = " / ____/ / / / /_/ / /  / / / / / / /_/ / ___ |/ /_/ / /_/ / "; cout << d << endl;
		string e = "/_/   /_/ /_/\\__,_/_/  /_/ /_/ /_/\\__,_/_/  |_/ .___/ .___/  "; cout << e << endl;
		string g = "                                             /_/   /_/       V 1.0"; cout << g << endl << endl;
		cout << RESET;	
	 	cout << "Miagax 2014. CLI version" << endl;
	 	cout << "Made with love & Freedom by Louis & Jérémy." << endl << endl;
	 	this->displayMenu();
	 	nbDefault+=1;
 	}
}

/**
* Default destruct
* @return void
*/
Controller::~Controller(){
	nbDestruc+=1;
	cout << "Bye ! " << endl;
}

void Controller::displayMenu(){
	cout << YELLOW << "+----------------------------------MENU----------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "1" << RESET "  => Afficher les médicaments."<< endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "2" << RESET " => Afficher les médicaments  avec leurs effets."<< endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "3" << RESET " => Afficher les médicaments en fct d'un effet."<< endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "4" << RESET " => Rechercher un médicament." << endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "5" << RESET " => Afficher l'histogramme des effets." << endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "6" << RESET " => Ajouter un médicament dans la base." << endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "7" << RESET " => Voir les médicaments ayant des effets en commun avec un autre médicament." << endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
 	cout << YELLOW << "| - " << RESET << RED << "0" << RESET " => Quitter l'application." << endl;
 	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
}

/**
* Display all \Medicament from the database
* @title : boolean, display the event of the function
* @return void
*/
template <typename T>
T Controller::dispMedoc(bool title, bool asReturn){
	try{
		this->tabTemp = this->database.getDataStorage();
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}

	if(title){
		cout << BOLDGREEN << "Les médicaments " << RESET << endl << endl;
	}

	if (asReturn) {
		return this->tabTemp;
	}
	/*
	Display LIKE :
	+-----------------------+
	   N° : 0 | Medicament
	+-----------------------+
	*/
	int nbMed = 0;
	cout << YELLOW << "+-------------------------------Medicament-------------------------------+" << RESET << endl;
	cout << YELLOW << "| "<< RESET << "Id | Name " << endl;
	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
	for(dataMapIterator it = this->tabTemp.begin(); it != this->tabTemp.end(); ++it)
	{
		cout << YELLOW << " | " << RESET << (it->first+1) << " | " << BOLDCYAN;
		cout <<it->second.getNomMedicament() << RESET << endl;
		cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
		nbMed++;
	}
	cout <<  BOLDRED << "Total " << nbMed << RESET << endl;
	this->tabTemp.clear();
	return T();
};

/**
* Display all \Medicament with \Effet from the database.
* This function can return the same thing like dispMedoc. It's only for graphic usage.
* @title : boolean, display the event of the function
* @return void
*/
template <typename T>
T Controller::dispMedocWithEffet(bool title, bool asReturn){
	try{
		this->tabTemp = this->database.getDataStorage();
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}
	if(title){
		cout << BOLDGREEN << "Les médicaments avec leurs effets : " << RESET << endl << endl;
	}

	if (asReturn) {
		return this->tabTemp;
	}

	/*
	Display like
	+--------------------------------------------------------------------+
	| Nom médicament (nbEffets)
	| % Effet1, Effet2, ..
	+--------------------------------------------------------------------+
	*/
	int nbMed, nbEffets;
	cout << YELLOW << "+------------------------------------------------------------------------+" << RESET << endl;
	for(dataMapIterator it = this->tabTemp.begin(); it != this->tabTemp.end(); ++it)
	{
		cout << "\033[0;33m|\033[0m\033[1;36m ";
		cout << it->second.getNomMedicament();
		cout << "\033[0m ";
		nbEffets = it->second.getLesEffetsIndesirables().size();
		cout << "\033[1;31m(" << nbEffets << ")\033[0m"  << endl;
		cout << "\033[0;33m|\033[0m % ";
		cout << "\033[1;34m";
		for (int i = 0; i < nbEffets ; ++i)
		{
			cout << it->second.getLesEffetsIndesirables()[i].getNomEffet() << " ";
		}
		cout << "\033[0m";
		cout << endl;
		cout << "\033[0;33m+--------------------------------------------------------------------+\033[0m" << endl;

	}


	this->tabTemp.clear();

	return T();
};

/**
* Display all \Effet.nom from the database
* @string : the nom effet
* @title : boolean, display the event of the function
*/
template <typename T>
T Controller::dispEffetFromMedoc(string theNomEffet, bool title, bool asReturn){
	try{
		this->tabTemp = this->database.getMapMedocFromEffet(theNomEffet);
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}

	if (title) {
		cout << theNomEffet << " are in the following medicament " << endl;
	}

	if (asReturn){
		return this->tabTemp;
	}
	//cout << this->tabTemp.size() << endl;
	cout << "+------------------------+" << endl;
	for(dataMapIterator it = this->tabTemp.begin(); it != this->tabTemp.end(); ++it)
	{
		cout << "| " << it->first << " | ";
		cout << it->second.getNomMedicament() << " |" << endl;
		cout << "+------------------------+" << endl;

	}
	this->tabTemp.clear();
	return T();
};


/**
* Display all \Effect with the nbOccurence of the effect  
* @asTitle=false  : display the "title" of the function
* @asReturn=false : return the typename T if true
* @return : mixed
*/
template <typename T>
T Controller::dispHistogrammeEffet(bool asTitle, bool asReturn){
	try{
		this->tabTempEffets = this->database.getLesEffets();
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}

	if(asTitle){
		cout <<  "\033[4;32mL'histogramme des effets : \033[0m" << endl << endl;
	}

	if (asReturn){
		return this->tabTempEffets;
	}
	
	for(dataEffetIterator it = this->tabTempEffets.begin() ; it != this->tabTempEffets.end(); ++it){
		//cout << it->getNomEffet() << "---" << it->getNbOccurence() << endl;
		cout << "\033[1;36m" << it->first <<  "\033[0m" << " --> " << it->second << " % " <<  endl;
	}

	return T();

};


template <typename T> 
T Controller::dispSearchMedicament(string _nomMedoc, bool asTitle, bool asReturn){
	Medicament tempMed;
	try{
		tempMed = this->database.getTheMedicament(_nomMedoc);
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}

	if(asTitle){
		cout <<  "\033[4;32mRésultat de la recherche :  \033[0m" << endl;
	}
	
	if (asReturn){
		return tempMed;
	}
	
	cout << tempMed.getNomMedicament() << endl;
	for (int i = 0; i < tempMed.getLesEffetsIndesirables().size(); ++i)
	{
		cout << tempMed.getLesEffetsIndesirables()[i].getNomEffet() << " ";
	}
	return T();
};

template <typename T> 
T Controller::dispMedEnCommunWithEffet(string _nomMedic, int choixAlgo, bool asTitle, bool asReturn){
	//Récupération du médicament
	Medicament tempMed;

	try{
		tempMed = this->database.getTheMedicament(_nomMedic);
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}

	//Récupération des Médicaments
	try{
		this->tabTemp = this->database.getMedicamentEffetsMaxCommun(tempMed, choixAlgo);
	}catch(DataProvider::DBException e){
		e.getMessage();
		return T();
	}

	if(asReturn){
		return this->tabTemp;
	}

	if (asTitle){
		cout << "Les médicaments ayant le plus d'effet en commun avec : " << tempMed.getNomMedicament() << endl;
	}

	cout << "+------------------------+" << endl;
	for(dataMapIterator it = this->tabTemp.begin(); it != this->tabTemp.end(); ++it)
	{
		cout << "| " << it->first << " | ";
		cout << it->second.getNomMedicament() << " |" << endl;
		cout << "+------------------------+" << endl;

	}
	this->tabTemp.clear();
	return T();
};

/**
* Add Medicament to the dataStorage instance
* @param _nomMedoc : string
* @param _lesEffetsString : vector<string>
* @return void
*/
void Controller::dispAddMedicament(string _nomMedoc, vector<string> _lesEffetsString){
	Medicament newMed;
	vector<Effet> newEffets;
	newMed.setNomMedicament(_nomMedoc);
	for (int i = 0; i < _lesEffetsString.size(); ++i)
	{
		newEffets.push_back(_lesEffetsString[i]);
	}
	newMed.setLesEffetsIndesirables(newEffets);
	this->database.insertIntoMedicament(newMed);
	cout << newMed.getNomMedicament() << "bien ajouté à la base." << endl;
};
