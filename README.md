```
______ _                                 ___              
| ___ \ |                               / _ \             
| |_/ / |__   __ _ _ __ _ __ ___   __ _/ /_\ \_ __  _ __  
|  __/| '_ \ / _` | '__| '_ ` _ \ / _` |  _  | '_ \| '_ \ 
| |   | | | | (_| | |  | | | | | | (_| | | | | |_) | |_) |
\_|   |_| |_|\__,_|_|  |_| |_| |_|\__,_\_| |_/ .__/| .__/ 
                                             | |   | |    
                                             |_|   |_|    

```
# Projet POO L3 MIAGe

##Description du projet
Application permettant de charger une base de donnée minimaliste et de chercher des informations dans celle-ci.

La base de donnée contiendra des médicaments ainsi que leurs effets indésirables. Elle sera
présentée sous la forme :
```
nom du médicament 1 : effets indésirables notoires : effet 1 , effet 2 , effet 3 et effet 4 .
nom du médicament 2 : effets indésirables notoires : effet 1 , et effet 2 .
```

On note que tous les médicaments n’ont pas le même nombre d’effets secondaires.

##Cahier des charges

1. Parsing du fichier
2. Création de l’histogramme : un histogramme des effets secondaires existant devra être
créé.
3. Visualisation des données : la visualisation de l’histogramme ainsi que la liste des médi-
caments présents devront pouvoir être visualisés.
4. Recherche : Pour un effet secondaire donnée	
5. Ajouter des médicaments
6. Interface graphique


Compilation gui : 

```
g++ main.cpp -o Fenetre `pkg-config gtkmm-3.0 --cflags --libs`
```

Make :

    `make all`
    `make mainTerm`
    `make mainGui`
    `make mrpropre` : avant de commit par exemple hein louis ! :)

// Le bruit : le nmbre de réponses correcte divisé par le nb de réponse correcte existante dans la db
// Si = 1 alors bon

// La précision : si le sys répond des réponses correctes mais aussi du bruit, 
// LE nombre des vrai positif que le système renvoie / le nombre de réponses