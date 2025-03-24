#ifndef JEU_H
#define JEU_H

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"

#include <string> 


class Jeu {
public:
    bool lecture(std::string nom_fichier);
    void success();
    bool imprimer_data(istringstream& data);
    void reset();
    bool decodage_ligne(istringstream& data);
    bool decodage_score(istringstream& data);
    bool decodage_nb_particule(istringstream& data);
    bool decodage_particule(istringstream& data);
    bool decodage_nb_faiseur(istringstream& data);
    bool decodage_faiseur(istringstream& data);
    bool decodage_nb_chaine(istringstream& data);
    bool decodage_chaine(istringstream& data);
    bool decodage_chaine_mode(istringstream& data);


    static unsigned int score = 0;
    static unsigned int nb_particule_init = 0;
    static unsigned int nb_faiseur_init = 0;
    static unsigned int nb_chaine_init = 0;

    static Etat etat = SCORE;
    static Chaine_mode mode;
};




#endif