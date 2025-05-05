//mobile.cc, Adam Coste et Max Ciriani, version 1
#ifndef JEU_H
#define JEU_H

#include <string> 

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"
#include "constantes.h"

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
    static bool get_lecture_success() { return lecture_success; }
    void set_lecture_success(bool success) { lecture_success = success; }
    void reset();

    static void set_score(unsigned int s) { score = s; }
    static unsigned int get_score() { return score; }

    void draw_arene();
    void draw_faiseurs();
    void draw_particules();
    void draw_chaine();

    //save_file() writes the current state of the game to a file
    void save_file(string file_name);

    Status get_status() const;
    static void set_status(Status s);


    static void draw_but_final();
    static void draw_start();

private:
    static unsigned int score;
    static bool lecture_success;
    static Status status;
};

#endif