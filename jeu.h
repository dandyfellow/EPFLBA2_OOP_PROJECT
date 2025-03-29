#ifndef JEU_H
#define JEU_H

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"

#include <string> 

enum Etat {SCORE, NB_PARTICULE, PARTICULE, NB_FAISEUR, FAISEUR, NB_CHAINE, CHAINE, CHAINE_MODE, FIN};

class Jeu {
public:

    bool lecture(std::string nom_fichier);
    void success(); //only these ones needed for project.cc
    

private:
    static unsigned int score;
    static unsigned int nb_particule_init;
    static unsigned int nb_faiseur_init;
    static unsigned int nb_chaine_init;

    static Etat etat;
};

#endif