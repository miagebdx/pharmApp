#define pathFichierListe "liste.txt"

#include "Abstract/Controller.cpp"
/*
	+--+ |  | +--+ +--+  +\  /+ +--+   +--+ +---+ +---+
	|  | |__| |  | |  |  | \/ | |  |   |  | |   | |   |
	+--+ |  | |--| +--\  |    | |--|   |--| +---+ +---+
    |    |  | |  | |   \ |    | |  |   |  | |     |

    Brought to you by Louis & Jérémy
	*/

// Occurence statique
// Pour avoir l'histogramme : Nb fois qu'on rentre l'occurence / la nombre de quantité
int main(int argc, char const *argv[])
{
	// DataProvider db;
	// string nomMedoc = "Voltaren";
	// Medicament m = db.getTheMedicament(nomMedoc);

	// dataMap tabTemp = db.getMedicamentEffetsMaxCommun(m, 2);
	
	// for(dataMapIterator it = tabTemp.begin(); it != tabTemp.end(); ++it)
	// {
	// 	cout << it->second.getNomMedicament() << endl;
	// }
	


	
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
				break;
			}
			case 2 : {
				cmd.dispMedocWithEffet<dataMap>(true);
				break;
			}
			case 3 : {
				cout << "Entrez le nom d'un effet, par exemple : anaphylacticReaction" << endl;
				cin >> nomMedocRecherche;
				cmd.dispEffetFromMedoc<dataMap>(nomMedocRecherche, true);
				break;
			}
			case 4 : {
				cout << "Entrez le nom d'un médicament, par ex : Voltaren" << endl;
				cin >> nomMedocRecherche;
				cmd.dispSearchMedicament<Medicament>(nomMedocRecherche, true);
				break;
			}
			case 5 : {
				cmd.dispHistogrammeEffet<dataEffet>(true);
				break;
			}
			case 6 : {
				cout << "Entrez le nom d'un médicament à ajouter" << endl;
				cin >> nomMed;
				cout << "Entrez les effets correspondant " << endl;

				while(true){
					cin >> nomEffet;
					if(nomEffet=="0"){ 
						break;
					}else{
						lesEffets.push_back(nomEffet);
						cout << nomEffet << " added" << endl;
					}
				}	
				cmd.dispAddMedicament(nomMed, lesEffets);
				break;
			}
			case 7 : {
				cout << "Entrez le nom d'un médicament pour rechercher les Medicaments ayant des effets en commun avec." << endl;
				cin >> nomMedocRecherche;
				cout << "Entrez le choix d'un algo : 1 / 2" << endl;
				cout << "1 -> Parcoure tout et récupère ceux en commun" << endl;
				cout << "2 -> Récupère les deux premiers " << endl;
				cin >> choixAlgo;
				cmd.dispMedEnCommunWithEffet<dataMap>(nomMedocRecherche, choixAlgo);
				break;
			}
			case 0 : {
				return 0;
			}
		}
	}
	
	return 0;
}
