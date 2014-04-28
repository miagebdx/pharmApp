/*

+---------------------------------------------+
|    ___ _  _  __  ___ __ __  __  ___ ___     |
|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
|+--------------------------------------------+
| @authors : Jérémy Morin & Louis Lainé       |
+---------------------------------------------+
| @usage : Parse document storage (.txt)      |
| @class : ParseFichier.hpp                   |
+---------------------------------------------+

*/

#include "ParserFichier.hpp"
/**
* CopyFile
* @return a vector of string with all lines on initial documents
*/

leFichier ParserFichier::copyFile()
{

   leFichier theLine;
   std::ifstream fichier("./liste.txt", ios::in);
   std::string line;
    while(getline(fichier, line))  //while you put the line
    {
        theLine.push_back(line);
    }
    if (theLine.empty())
    {
        throw ParserException("No line copy", "ParserFichier.cpp::copyFile::25", "No file opened");
    }
    return theLine;
}

void ParserFichier::countNbLineInFile()
{
   ifstream fichier("./liste.txt", ios::in);
   std::string line;
   while(getline(fichier, line)) this->cmpLine++;
}


/**
* showVector
* Print a vector
* @param vector
*/

void showVector(leFichier _vect){

    for(int i=0; i!=_vect.size(); i++)
    {
     cout<<_vect[i]<<endl;
 }

}

/**
* showVector
* Print a vector
* @param vector
* @return string : a line of vector
*/

string ParserFichier::oneLine(int _numero, leFichier _vect)

{
    return _vect[_numero];

}


/**
* splitline
* Print a vector
* @param a line of file's medicaments
* @return Obect parser Medicament = some effects
*/

mapParse ParserFichier::splitLine(string _string)
{
    string _nameMedicament;
    string _effet;
    leFichier _lesEffets;
    int i=0;

    int longueurMot = 0;

    while(_string.at(i)!=' '){
        _nameMedicament=_nameMedicament+_string.at(i);
        i++;
        }
        //extract medicaments name

    while(i!=_string.size())
    {
        if (_string.at(i)!=' '&&_string.at(i)!=':') _effet=_effet+_string.at(i);
        if (_string.at(i)==',')
        {
            _effet.erase(_effet.size()-1,1 );
            _lesEffets.push_back(_effet);
            _effet.erase();

        }
        if(_string.at(i)=='.')
        {
            _effet.erase(_effet.size()-1,1 );
            _lesEffets.push_back(_effet);
            _effet.erase();
        }
        i++;
    }
    mapParse theMap;
    theMap.insert( std::make_pair(_nameMedicament,_lesEffets));
    return theMap;
}

mapParse ParserFichier::getMap(){
    return this->map;
};

int ParserFichier::getNbLigne(){
    return this->cmpLine;
};



// string ParserFichier::createLine(leFichier _vect)
// {
//     string laLigneResultat;
//     string deuxPoint = " : ";
//     string virgule = ", ";
//     string point =".";

//     for (int i = 0; i < _vect.size(); ++i)
//     {
//         if (i=0)
//         {
//             laLigneResultat+=_vect[i]+deuxPoint;
//         }

//         if (i!=0&&i+1!=_vect.size())
//         {
//             laLigneResultat+=_vect[i]+virgule;
//         }

//         if (i+1==_vect.size())
//         {
//             laLigneResultat+=_vect[i]+point;
//         }
//     }

//     return laLigneResultat;
// }


// int main(int argc, char const *argv[])
// {
// ParserFichier newest;
// string test= "test";
// string test1= test;
// string test2 = test;

// leFichier test3;
// test3.push_back(test);
// test3.push_back(test2);
// test3.push_back(test1);

// string x;
// newest.createLine(test3);
// cout<<x<<endl;




//     return 0;
// }
