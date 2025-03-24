#ifndef MOBILE_H
#define MOBILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> 
#include <vector>
#include "tools.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Cercle Arene({0,0}, r_max);

class Mobile {
public:
    Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init);

    double get_positionx() const;
    double get_positiony() const;

protected:
    S2d position;
    Vecteur vitesse;
    double alpha;
    double rayon;
};

class Particule : public Mobile {
public:
    Particule(S2d position_init, Vecteur vitesse_init, double alpha_init, int compteur);
    ~Particule();

    int get_compteur() const;
    void set_compteur(int c);
    static int get_nbrs_particules();
    static void set_nbrs_particules(int n);

private:
    static int nbrs_particules;
    int compteur;
    static vector<Particule*> liste_particule;
};

class Faiseur : public Mobile {
public:
    Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements);
    bool collisions(const Faiseur* autre);

private:
    int nbs_elements;
    vector<S2d> elements;
    static vector<Faiseur*> liste_faiseurs;
};

bool lecture_p(istringstream& data);
bool lecture_f(istringstream& data);

#endif // MOBILE_H
