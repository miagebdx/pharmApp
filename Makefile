#+---------------------------------------------+
#|    ___ _  _  __  ___ __ __  __  ___ ___     |
#|   | _,\ || |/  \| _ \  V  |/  \| _,\ _,\    |
#|   | v_/ >< | /\ | v / \_/ | /\ | v_/ v_/    |
#|   |_| |_||_|_||_|_|_\_| |_|_||_|_| |_|      |
#|+--------------------------------------------+
#| @authors : Jérémy Morin & Louis Lainé       |
#+---------------------------------------------+
#| @usage   : make all                         |
#+---------------------------------------------+

tmp=Tmp/
lib=Src/Dll/
abstract=Src/Abstract/
parser=Src/Parser/
build=Build/
src=Src/
flag=`pkg-config gtkmm-3.0 --cflags --libs` -std=c++11

all: mainGui mainTerm clean

mainGui: lesLibs abstractLibs
	g++ $(src)mainGui.cpp -o $(build)mainGui $(flag)

guiOnly:
	g++ $(src)mainGui.cpp -o $(build)mainGui $(flag)

mainTerm: lesLibs abstractLibs
	g++ -c $(src)mainTerm.cpp -o $(tmp)mainTerm.o  -std=c++11
	g++ $(tmp)mainTerm.o -o $(build)mainTerm -std=c++11


lesLibs:
	g++ -c $(lib)Medicament.cpp -o $(tmp)Medicament.o
	g++ -c $(lib)Effet.cpp -o $(tmp)Effet.o
	g++ -c $(parser)ParserFichier.cpp -o $(tmp)ParserFichier.o

abstractLibs:
	g++ -c $(abstract)DataProvider.cpp -o $(tmp)DataProvider.o
	g++ -c $(abstract)ObjectFactory.cpp -o $(tmp)ObjectFactory.o
	g++ -c $(abstract)Controller.cpp -o $(tmp)Controller.o

clean:
	rm -f *.o
	rm -f $(tmp)*.o

mrpropre: clean
	rm -f $(build)/mainTerm
	rm -f $(build)/mainGui
