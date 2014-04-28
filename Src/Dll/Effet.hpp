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
| @methods : Effet.hpp                        |
+---------------------------------------------+

*/
#ifndef EFFET_HPP_
#define EFFET_HPP_

#include <string>
#include <iostream>

using namespace std;

class Effet {
private:
	string nomEffet;
	double nbOccurence;
	static int nbDefault;
    static int nbDestruc;
    static int nbParam;

public:
	Effet();
	Effet(Effet const&);
	Effet(string);
	virtual ~Effet();

	string getNomEffet();
	void setNomEffet(string);

	double getNbOccurence();
	void setnbOccurence(double);
};

#endif /* EFFET_HPP_ */
