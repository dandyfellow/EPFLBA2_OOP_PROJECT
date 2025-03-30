//mobile.cc, Adam Coste et Max Ciriani, version 1
#include <memory>
#include "mobile.h"

using namespace std;

namespace{
    bool verifier_collision_faiseur(const shared_ptr<Faiseur>& f);
    Cercle Arene({0,0}, r_max);
}

vector<Particule*> Particule::liste_particule;
vector<shared_ptr<Faiseur>> Faiseur::liste_faiseurs = {};
int Faiseur::compteur_faiseurs = 0;
int Particule::nbrs_particules = 0;

bool lecture_p(istringstream& data) {
    Cercle arene({0, 0}, r_max);
    double x, y, angle, deplacement, compteur;
    data >> x >> y >> angle >> deplacement >> compteur;

    Cercle c1({x, y}, 0.);
    Vecteur v({x, y}, deplacement, angle);

    if (compteur >= time_to_split || compteur < 0) {
        cout << message::particule_counter(compteur);
        return false;
    }
    if (!Cercle::inclusion(arene, c1)) {
        cout << message::particule_outside(x, y);
        return false;
    }
    if (v.get_norme() < 0 || v.get_norme() > d_max) {
        cout << message::mobile_displacement(deplacement);
        return false;
    }
    return true;
}

bool lecture_f(istringstream& data) {
    double x, y, angle, deplacement, rayon, nbe;
    data >> x >> y >> angle >> deplacement >> rayon >> nbe;

    Vecteur v({x, y}, deplacement, angle + 3.14159265358979323846); 
    //angle + pi pour adapter à l'angle reflechi
    Cercle arene({0, 0}, r_max);
    Cercle c2({x, y}, rayon);

    if (nbe <= 0) {
        cout << message::faiseur_nbe(nbe);
        return false;
    }
    if (rayon < r_min_faiseur || rayon > r_max_faiseur) {
        cout << message::faiseur_radius(rayon);
        return false;
    }
    if (v.get_norme() < 0 || v.get_norme() > d_max) {
        cout << message::mobile_displacement(deplacement);
        return false;
    }
    if(!Cercle::inclusion(arene, c2)){
        cout << message::faiseur_outside(x,y);
        return false;
    }

    S2d position = {x, y};
    auto f = make_shared<Faiseur>(position, v, angle, rayon, nbe); //using shared_ptr 
    f->ajouter_element(position); //ajout de la tete du faiseur 

    for (int i = 0; i < nbe; ++i) {
        double new_x = position.x - deplacement * cos(angle);
        double new_y = position.y - deplacement * sin(angle);
        Cercle c_test({new_x, new_y}, rayon);

        if (!Cercle::inclusion(arene, c_test)) {
            v = v.reflechis({position.x, position.y});
            angle = v.get_angle();
            new_x = position.x - deplacement * cos(angle);
            new_y = position.y - deplacement * sin(angle);
        }
        f->ajouter_element({new_x, new_y});
        position.x = new_x;
        position.y = new_y;
    }
    if (!verifier_collision_faiseur(f)){
        return false;
    }
    Faiseur::ajouter_faiseur(f);
    return true;
}   

void Faiseur::display(){
    cout << "-------- Displaying faiseur --------\n";
    for (const auto& f : Faiseur::get_liste_faiseurs()) {
        cout << "Faiseur index: " << f->get_index() << "\n";
        cout << "Elements: \n";
        for (const auto& [index, point] : f->get_elements()) {
            cout << "Element number: " << index << " , point: " << point.x << " : " 
                 << point.y << "\n";
        }
    }
}

//Mobile
Mobile::Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, 
               double rayon_init)
    :position(position_init), vitesse(vitesse_init), alpha(alpha_init), 
     rayon(rayon_init) {}

//Particule
Particule::Particule(S2d position_init, Vecteur vitesse_init, double alpha_init)
    : Mobile(position_init, vitesse_init, alpha_init, 0.){
    ++nbrs_particules;
    liste_particule.push_back(this);
}

Particule::~Particule() {
    --nbrs_particules;
}

void Particule::set_compteur(int c) {
    compteur = c;
}

//Faiseur 
Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, 
                 double rayon_init, int nb_elements)
    :Mobile(position_init, vitesse_init, alpha_init, rayon_init),
             index(compteur_faiseurs++) {
                elements.reserve(nb_elements);
}

void Faiseur::ajouter_faiseur(shared_ptr<Faiseur> f) { 
    liste_faiseurs.push_back(f);
}

const vector<shared_ptr<Faiseur>>& Faiseur::get_liste_faiseurs(){
    return liste_faiseurs;
}

void Faiseur::ajouter_element(const S2d& position) {
    elements.emplace_back(compteur_elements++, position);
}    

namespace {
    bool verifier_collision_faiseur(const shared_ptr<Faiseur>& f) {
        for (const auto& autre_faiseur : Faiseur::get_liste_faiseurs()) {  
            auto elements_f = f->get_elements();
            for (const auto& [index, centre] : elements_f) {  
                Cercle current_cercle(centre, f->get_rayon());
                auto elements_autre_f = autre_faiseur->get_elements();
                for (const auto& [autre_index, autre_centre] : elements_autre_f) {  
                    Cercle autre_cercle(autre_centre, autre_faiseur->get_rayon());
                    if (Cercle::intrusion(current_cercle, autre_cercle)) {  
                        cout << message::faiseur_element_collision(
                                f->get_index(), index, autre_faiseur->get_index(),
                                autre_index);
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

//FONCTIONS RENDU 2 - EBAUCHES
   /*void mise_a_jour(const Arene &arene){
        Mobile::mise_a_jour(arene);
        for (const auto& autre : liste_faiseurs){
            if (autre != this && collisions(autre)){
                return; 
            }
        } 
        for(int i = nbs_elements - 1; i > 0; --i){
            elements[i]=elements[i-1];
        } 
        elements[0]={(position.x),(position.y)};
    }*/

     /*void mise_a_jour(const Arene& arene) override{
        Mobile::mise_a_jour(arene);
        ++compteur;
        if(compteur==time_to_split){
            if(nbrs_particules >= nb_particule_max){
                delete this;
            }else{
                Vecteur nouvelle_vitesse1(position, (vitesse.get_norme()*coef_split), alpha+delta_split);
                Particule* particule1 = new Particule(position, nouvelle_vitesse1, alpha+delta_split);
                Vecteur nouvelle_vitesse2(position, (vitesse.get_norme()*coef_split), alpha-delta_split);
                Particule* particule2 = new Particule(position, nouvelle_vitesse2, alpha-delta_split);
                delete this;
            }
        }
    };*/

    /*virtual void mise_a_jour(const Arene& arene){
        position.x += vitesse.get_norme() * cos(alpha);
        position.y += vitesse.get_norme() * sin(alpha);
        if (arene.in_cercle(position, rayon)){
            return;
        }else{
            position.x -= vitesse.get_norme() * cos(alpha);
            position.y -= vitesse.get_norme() * sin(alpha);
            vitesse = vitesse.reflechis(position);
            alpha = vitesse.get_angle(); 
            position.x += vitesse.get_norme() * cos(alpha);
            position.y += vitesse.get_norme() * sin(alpha);
        }       
     };*/