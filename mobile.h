// mobile.h, Adam Coste et Max Ciriani, version 1
#ifndef MOBILE_H
#define MOBILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

#include "tools.h"
#include "constantes.h"
#include "message.h"

using namespace std;

extern Cercle Arene;

bool lecture_p(istringstream& data);
bool lecture_f(istringstream& data);
void mise_a_jour_particules(const Cercle arene); // mise à jour (déplacement, split)
void mise_a_jour_faiseurs(const Cercle arene); // mise à jour (déplacement, collisons entre faisuers)

class Mobile {
public:
    Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init);
    void move(const Cercle arene);
    double get_positionx() const { return position.x; }
    double get_positiony() const { return position.y; }
    S2d get_position() const { return position; }
    double get_rayon() const { return rayon; }
    double get_alpha() const { return alpha; }
    Vecteur get_vitesse() const { return vitesse; }

protected:
    S2d position;
    Vecteur vitesse;
    double alpha;
    double rayon;
};

class Particule : public Mobile {
public:
    Particule(S2d position_init, Vecteur vitesse_init, double alpha_init);
    int get_compteur() const { return compteur; }
    void increase_compteur();
    static int get_nbrs_particules() { return nbrs_particules; }
    static const vector<Particule*>& get_liste_particules() { return liste_particule; }
    static void ajouter_particule(Particule* p);
    static void supprimer_particule(Particule* p);
    ~Particule() { --nbrs_particules; }

private:
    static int nbrs_particules;
    int compteur = 0;
    static vector<Particule*> liste_particule;
};

class Faiseur : public Mobile {
public:
    Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements);
    static void ajouter_faiseur(unique_ptr<Faiseur>&& f);
    static const vector<unique_ptr<Faiseur>>& get_liste_faiseurs();
    void ajouter_element(unique_ptr<Mobile> element);
    const vector<unique_ptr<Mobile>>& get_elements() const { return elements; }
    void move_faiseur(const Cercle arene);

private:
    static vector<unique_ptr<Faiseur>> liste_faiseurs;
    static int compteur_faiseurs;
    vector<unique_ptr<Mobile>> elements;
};

#endif
