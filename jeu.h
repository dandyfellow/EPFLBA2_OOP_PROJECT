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
   

    /*void reset();
    bool imprimer_data(istringstream& data);
    bool decodage_score(istringstream& data);
    bool decodage_ligne(istringstream& data);
    bool decodage_nb_particule(istringstream& data);
    bool decodage_particule(istringstream& data);
    bool decodage_nb_faiseur(istringstream& data);
    bool decodage_faiseur(istringstream& data);
    bool decodage_nb_chaine(istringstream& data);
    bool decodage_chaine(istringstream& data);
    bool decodage_chaine_mode(istringstream& data);*/


    static unsigned int score;
    static unsigned int nb_particule_init;
    static unsigned int nb_faiseur_init;
    static unsigned int nb_chaine_init;

    static Etat etat;

private:

};




#endif