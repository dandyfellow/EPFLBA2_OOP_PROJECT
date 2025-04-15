// mobile.cc, Adam Coste et Max Ciriani, version 1
#include <iostream>
#include <memory>
#include <cmath>  // Pour cos, sin
#include <algorithm> // Pour std::remove
#include "mobile.h"

using namespace std;

namespace {
    bool verifier_collision_faiseur(const unique_ptr<Faiseur>& f);
    Cercle arene({0, 0}, r_max);
}

vector<Particule*> Particule::liste_particule;
vector<unique_ptr<Faiseur>> Faiseur::liste_faiseurs = {};
unsigned int Particule::nbrs_particules = 0;
int Faiseur::compteur_faiseurs = 0;



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

    Particule* p = new Particule({x, y}, v, angle);
    Particule::ajouter_particule(p);
    return true;
}

bool lecture_f(istringstream& data) { 
    double x, y, angle, deplacement, rayon, nbe;
    data >> x >> y >> angle >> deplacement >> rayon >> nbe;
    Vecteur v({x, y}, deplacement, angle); 

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
    if (!Cercle::inclusion(arene, c2)) {
        cout << message::faiseur_outside(x, y);
        return false;
    }

    S2d position = {x, y};
    auto f = make_unique<Faiseur>(position, v, angle, rayon, nbe);
    f->ajouter_element(make_unique<Mobile>(position, v, angle, rayon)); 

    Vecteur v_tmp = v;
    double angle_tmp = angle;

    for (int i = 0; i < nbe; ++i) {
        double new_x = position.x - deplacement * cos(angle);
        double new_y = position.y - deplacement * sin(angle);
        Cercle c_test({new_x, new_y}, rayon);

        if (!Cercle::inclusion(arene, c_test)) {
            v_tmp = v_tmp.reflechis(position);
            angle_tmp = v_tmp.get_angle();
            new_x = position.x - deplacement * cos(angle_tmp);
            new_y = position.y - deplacement * sin(angle_tmp);
        }

        f->ajouter_element(make_unique<Mobile>(S2d{new_x, new_y}, v_tmp, angle_tmp, rayon));
        position.x = new_x;
        position.y = new_y;
    }
    if (!verifier_collision_faiseur(f)) {
        return false;
    }
    
    Faiseur::ajouter_faiseur(std::move(f));
    return true;
}

void update_particules() {
    const auto& particules = Particule::get_liste_particules();
    Cercle arene({0, 0}, r_max);
    vector<Particule*> copie_particules = particules;

    for (Particule* p : copie_particules) {
        p->increase_compteur();

        if (p->get_compteur() == time_to_split) {

            if (Particule::get_nbrs_particules() >= nb_particule_max) {
                Particule::supprimer_particule(p);
                delete p;
                continue;
            }
            Vecteur nouvelle_v1(p->get_position(), 
                                p->get_vitesse().get_norme() * coef_split, 
                                p->get_alpha() + delta_split);
            Vecteur nouvelle_v2(p->get_position(), 
                                p->get_vitesse().get_norme() * coef_split, 
                                p->get_alpha() - delta_split);

            Particule* p1 = new Particule(p->get_position(), nouvelle_v1, 
                                          p->get_alpha() + delta_split);
            Particule* p2 = new Particule(p->get_position(), 
                                          nouvelle_v2, p->get_alpha() - delta_split);

            Particule::ajouter_particule(p1);
            Particule::ajouter_particule(p2);

            p1->move(arene);
            p2->move(arene);

            Particule::supprimer_particule(p);
            delete p;
        } else {
            p->move(arene);
        }
    }
}


void update_faiseurs(){
    auto& faiseurs = Faiseur::get_liste_faiseurs();

    for(size_t i=0; i<faiseurs.size(); i++){
        bool collision = false;
        const auto& f = faiseurs[i];
        auto& elements = f->get_elements();
        auto& tete= elements[0]; //Creation tete faiseur
        S2d new_position = {tete->get_positionx() + f->get_vitesse().get_x(), tete->get_positiony() + f->get_vitesse().get_y()};
        Cercle c_test(new_position, f->get_rayon());

        for(size_t j=0; j<faiseurs.size(); ++j){
            if(i==j) continue;
            const auto& f_autre= faiseurs[j]->get_elements();

            for(const auto& k : f_autre){
                Cercle autre(k->get_position(), faiseurs[j]->get_rayon());
                if(Cercle::intrusion(c_test, autre)){
                    collision = true;
                    break;
                }
            }
            if(collision){break;}
        }
        if(!collision){
            f->move_faiseur(arene);
        }
    }
}


void Faiseur::display() {
    std::cout << "-------- Displaying faiseurs --------\n";
    const auto& faiseurs = Faiseur::get_liste_faiseurs();

    for (size_t i = 0; i < faiseurs.size(); ++i) {
        const auto& f = faiseurs[i];
        std::cout << "Faiseur " << i << " :\n";
        const auto& elements = f->get_elements();
        for (size_t j = 0; j < elements.size(); ++j) {
            const auto& e = elements[j];
            std::cout << "  Élément " << j << " → "
                      << "x = " << e->get_positionx()
                      << ", y = " << e->get_positiony() << "\n";
        }
    }
}


//==========================MOBILE=====================================================
Mobile::Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, 
               double rayon_init)
    : position(position_init), vitesse(vitesse_init), alpha(alpha_init), 
      rayon(rayon_init) {}

    void Mobile::move(const Cercle arene) {
    
        S2d new_position = {position.x + vitesse.get_x(),position.y + vitesse.get_y()};
        Cercle c_test(new_position, rayon);
    
        if (!Cercle::inclusion(arene, c_test)) {
            Vecteur v_reflechis = vitesse.reflechis(position);
            vitesse = v_reflechis; 
            alpha = v_reflechis.get_angle();
    
            new_position.x = position.x + v_reflechis.get_x();
            new_position.y = position.y + v_reflechis.get_y();
        }
        position = new_position;
    }
    
//==========================PARTICULE==================================================

Particule::Particule(S2d position_init, Vecteur vitesse_init, double alpha_init)
    : Mobile(position_init, vitesse_init, alpha_init, 0.){
    ++nbrs_particules;
}

void Particule::display() {
    cout << "-------- Displaying particule --------\n";
    for(size_t i=0; i < liste_particule.size(); ++i) {
        Particule* p = liste_particule[i];
        cout << "Particule number: " << i << " , point: ";
        cout << p->get_positionx() << " : " << p->get_positiony() << "\n";
    }
}

void Particule::ajouter_particule(Particule* p) {
    liste_particule.push_back(p);
}

void Particule::supprimer_particule(Particule* p) {
    auto& lp = liste_particule;
    lp.erase(std::remove(lp.begin(), lp.end(), p), lp.end());
}


void Particule::increase_compteur() {
    ++compteur;
}

void Particule::reset() {
    liste_particule.clear();
    nbrs_particules = 0; 
}

//==========================FAISEUR====================================================

Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, 
                 double rayon_init, int nb_elements)
    : Mobile(position_init, vitesse_init, alpha_init, rayon_init) {
        elements.reserve(nb_elements);
}

void Faiseur::ajouter_faiseur(unique_ptr<Faiseur>&& f) {
    liste_faiseurs.push_back(std::move(f));
}

const vector<unique_ptr<Faiseur>>& Faiseur::get_liste_faiseurs() {
    return liste_faiseurs;
}

void Faiseur::ajouter_element(unique_ptr<Mobile> element) {
    elements.push_back(std::move(element));
}

void Faiseur::move_faiseur(const Cercle arene) {
    for(const auto& element : elements) {
        element->move(arene);
    }
}

void Faiseur::reset() {
    liste_faiseurs.clear();
}

Faiseur::~Faiseur() { 
    --compteur_faiseurs; 
    elements.clear(); 
}

namespace {
    bool verifier_collision_faiseur(const unique_ptr<Faiseur>& f) {
        const auto& nouveaux_elements = f->get_elements();
        const auto& faiseurs = Faiseur::get_liste_faiseurs();

        // index futur, car pas encore ajouté
        int index_faiseur = static_cast<int>(faiseurs.size()); 

        for (size_t k = 0; k < nouveaux_elements.size(); ++k) {
            Cercle c1(nouveaux_elements[k]->get_position(), f->get_rayon());

            for (size_t i = 0; i < faiseurs.size(); ++i) {
                const auto& faiseur_i = faiseurs[i];
                const auto& elements_i = faiseur_i->get_elements();

                for (size_t j = 0; j < elements_i.size(); ++j) {
                    Cercle c2(elements_i[j]->get_position(), faiseur_i->get_rayon());

                    if (Cercle::intrusion(c1, c2)) {
                        cout << message::faiseur_element_collision(index_faiseur, 
                                                                   k, i, j);
                        return false;
                    }
                }
            }
        }
        return true;
    }
}
    

