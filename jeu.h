//mobile.cc, Adam Coste et Max Ciriani, version 1
#ifndef JEU_H
#define JEU_H

#include <string> 

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"
#include "constantes.h"
#include "gui.h"

enum Status{
    ONGOING,
    WON,
    LOST
};

enum Etat { SCORE, NB_PARTICULE, PARTICULE, NB_FAISEUR, FAISEUR, NB_CHAINE, CHAINE, 
            CHAINE_MODE, FIN};

class Jeu {
public:
    /*Jeu(string nom_fichier){
        lecture(nom_fichier);
    };*/
    bool lecture(std::string nom_fichier);
    void success(); //only these ones needed for project.cc
    void update();

    //save_file() writes the current state of the game to a file
    void save_file();


    
private:
};

#endif