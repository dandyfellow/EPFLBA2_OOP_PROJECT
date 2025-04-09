//mobile.h, Adam Coste et Max Ciriani, version 1
#ifndef MOBILE_H
#define MOBILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> 
#include <vector>
#include <memory>

#include "tools.h"
#include "constantes.h"
#include "message.h"

using namespace std;

extern Cercle Arene;

bool lecture_p(istringstream& data);
bool lecture_f(istringstream& data);
void mise_a_jour_p(const Cercle& arene);

class Mobile {
public:
    Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init);
    double get_positionx() const{ return position.x; };
    double get_positiony() const{ return position.y; };
    double get_rayon() const{ return rayon; };
    
protected:
    S2d position;
    Vecteur vitesse;
    double alpha;
    double rayon;
};

class Particule : public Mobile {
public:
    Particule(S2d position_init, Vecteur vitesse_init, double alpha_init);
    int get_compteur() const { return compteur; };
    void increase_compteur();
    static int get_nbrs_particules(){ return nbrs_particules; };
    static const vector<Particule*>& get_liste_particules(){ return liste_particule; };
    void mise_a_jour(const Cercle arene);
    void move_particule(Particule* p, const Cercle arene);
    ~Particule(){--nbrs_particules;};
private:
    static int nbrs_particules;
    int compteur=0;
    static vector<Particule*> liste_particule;
};

class Faiseur : public Mobile {
public:
    Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements);
    static void ajouter_faiseur(unique_ptr<Faiseur>&& f);
    static const vector<unique_ptr<Faiseur>>& get_liste_faiseurs();
    void ajouter_element(const S2d& position);
    vector<pair<int, S2d>> get_elements() const{ return elements; };
    int get_index() const { return index; }
    static void display();
    
private:
    static vector<unique_ptr<Faiseur>> liste_faiseurs;  
    static int compteur_faiseurs;  
    int index;  
    vector<pair<int, S2d>> elements; 
    int compteur_elements = 0;
};

#endif // MOBILE_H
