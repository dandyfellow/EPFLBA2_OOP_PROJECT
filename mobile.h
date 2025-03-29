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

extern Cercle Arene;

class Mobile {
public:
    Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init);
    double get_positionx() const;
    double get_positiony() const;
    double get_rayon() const;
    
protected:
    S2d position;
    Vecteur vitesse;
    double alpha;
    double rayon;
};

class Particule : public Mobile {
public:
    Particule(S2d position_init, Vecteur vitesse_init, double alpha_init);
    ~Particule();

    int get_compteur() const;
    void set_compteur(int c);
    static int get_nbrs_particules();
    //static void initializeCounter(double compteur);

private:
    static int nbrs_particules;
    int compteur;
    static vector<Particule*> liste_particule;
    //static bool isInitialized;
};

class Faiseur : public Mobile {
public:
    Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements);
    static void ajouter_faiseur(shared_ptr<Faiseur> f);
    static const vector<shared_ptr<Faiseur>>& get_liste_faiseurs();
    void ajouter_element(const S2d& position);
    vector<pair<int, S2d>> get_elements() const;
    int get_index() const { return index; }
    static void display();
    

private:
    static vector<shared_ptr<Faiseur>> liste_faiseurs;  
    static int compteur_faiseurs;  
    int index;  
    vector<pair<int, S2d>> elements; 
    int compteur_elements = 0;
};

bool lecture_p(istringstream& data);
bool lecture_f(istringstream& data);

#endif // MOBILE_H
