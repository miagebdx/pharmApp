#define pathFichierListe "liste.txt"

#include "Abstract/Controller.cpp"
#define clear system("clear")
#include <string.h>

int main(int argc, char const *argv[])
{
	if(argc!=2){
	  printf("Usage: %s start\n",argv[0]);
	  return EXIT_FAILURE;	
	}
	
	if (strcmp(argv[1],(const char*)"start")==0)
  	{
		clear;
		Controller cmd(true);
		int userChoice, choixAlgo = 0;
		string nomMedocRecherche, nomMed, nomEffet;
		std::vector<string> lesEffets;
		for (;;)
		{
			cin >> userChoice;
			switch(userChoice){
				case 1 : {
					cmd.dispMedoc<dataMap>(true);
					cmd.displayMiniMenu();
					break;
				}
				case 2 : {
					cmd.dispMedocWithEffet<dataMap>(true);
					cmd.displayMiniMenu();
					break;
				}
				case 3 : {
					cout << RED "-> "<< RESET << " Entrez le nom d'un effet "<< CYAN << " (anaphylacticReaction)" << RESET << endl;
					cin >> nomMedocRecherche;
					cmd.dispEffetFromMedoc<dataMap>(nomMedocRecherche, true);
					cmd.displayMiniMenu();
					break;
				}
				case 4 : {
					cout << RED "-> "<< RESET << " Entrez le nom d'un médicament" << BLUE " (Voltaren)" << RESET << endl;
					cin >> nomMedocRecherche;
					nomMedocRecherche[0] = toupper(nomMedocRecherche[0]);
					cmd.dispSearchMedicament<Medicament>(nomMedocRecherche, true);
					cmd.displayMiniMenu();
					break;
				}
				case 5 : {
					cmd.dispHistogrammeEffet<dataEffet>(true);
					cmd.displayMiniMenu();
					break;
				}
				case 6 : {
					cout << RED << "-> Entrez le nom d'un médicament à ajouter" << RESET << endl;
					cin >> nomMed;
					cout << "-> Entrez les effets correspondant (0 pour quitter) " << endl;
	
					while(true){
						cin >> nomEffet;
						if(nomEffet=="0"){ 
							break;
						}else{
							lesEffets.push_back(nomEffet);
							cout << nomEffet << " : OK" << endl;
						}
					}	
					cmd.dispAddMedicament(nomMed, lesEffets);
					cmd.displayMiniMenu();
					break;
				}
				case 7 : {
					cout << GREEN << "Entrez le nom d'un médicament pour rechercher les Medicaments ayant des effets en commun avec." << RESET << BLUE << "(Voltaren)" << RESET << endl;
					cin >> nomMedocRecherche;
					nomMedocRecherche[0] = toupper(nomMedocRecherche[0]);
					cout << "Entrez le choix d'un algo :"<< RED <<" 1 / 2" << RESET << endl;
					cout << RED <<"1 -> "<< RESET << " Parcoure tout et récupère ceux en commun" << endl;
					cout << RED <<"2 -> "<< RESET << " Récupère les deux premiers " << endl;
					cin >> choixAlgo;
					cmd.dispMedEnCommunWithEffet<dataMap>(nomMedocRecherche, choixAlgo);
					cmd.displayMiniMenu();
					break;
				}
				case 0 : {
					return 0;
				}
				default : {
					
					break;
				}
			}
		}
  	}
  	else
  	{
  	  printf("Usage: %s start\n",argv[0]);
          return EXIT_FAILURE;
  	}
  	
	
	return 0;
}
