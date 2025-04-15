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
int Particule::nbrs_particules = 0;
int Faiseur::compteur_faiseurs = 0;



bool lecture_p(istringstream& data) {
    Cercle arene({0, 0}, r_max);
    double x, y, angle, deplacement, compteur;
    data >> x >> y >> angle >> deplacement >> compteur;

    cout << "lecture_p" << endl;
    cout << "Position initiale: (" << x << ", " << y << ")" << endl;
    cout << "Angle: " << angle << ", Déplacement: " << deplacement << ", Compteur: " << compteur << endl;

    Cercle c1({x, y}, 0.);
    Vecteur v({x, y}, deplacement, angle);

    cout << "Vecteur construit: " << v.get_x() << " , " << v.get_y() << endl;
    cout << "Norme: " << v.get_norme() << ", Angle réel: " << v.get_angle() << endl;

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
    cout << "→ Particule créée et ajoutée" << endl;
    Particule::ajouter_particule(p);
    return true;
}

bool lecture_f(istringstream& data) {//nombres lignes a changer 
    double x, y, angle, deplacement, rayon, nbe;
    data >> x >> y >> angle >> deplacement >> rayon >> nbe;
    cout << "lecture_f" << endl;
    Vecteur v({x, y}, deplacement, angle);  // angle + pi pour adapter à l'angle réfléchi

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
    cout << "Vitesse finale faiseur (avant ajout): "
          << f->get_vitesse().get_x() << " , "
          << f->get_vitesse().get_y() << std::endl;

    cout << "ajouter faiseur" << endl;
    Faiseur::ajouter_faiseur(std::move(f));
    return true;
}

void update_particules() {
    cout << "Début update_particules" << endl;
    const auto& particules = Particule::get_liste_particules();
    Cercle arene({0, 0}, r_max);
    vector<Particule*> copie_particules = particules;

    for (Particule* p : copie_particules) {
        cout << "Particule compteur = " << p->get_compteur() << endl;
        p->increase_compteur();

        if (p->get_compteur() == time_to_split) {
            cout << "→ Time to split" << endl;

            if (Particule::get_nbrs_particules() >= nb_particule_max) {
                cout << "→ Trop de particules, suppression" << endl;
                Particule::supprimer_particule(p);
                delete p;
                continue;
            }
            cout << "→ Split en deux nouvelles particules" << endl;
            Vecteur nouvelle_v1(p->get_position(), p->get_vitesse().get_norme() * coef_split, p->get_alpha() + delta_split);
            Vecteur nouvelle_v2(p->get_position(), p->get_vitesse().get_norme() * coef_split, p->get_alpha() - delta_split);

            Particule* p1 = new Particule(p->get_position(), nouvelle_v1, p->get_alpha() + delta_split);
            Particule* p2 = new Particule(p->get_position(), nouvelle_v2, p->get_alpha() - delta_split);

            Particule::ajouter_particule(p1);
            Particule::ajouter_particule(p2);

            p1->move(arene);
            p2->move(arene);

            Particule::supprimer_particule(p);
            delete p;
        } else {
            cout << "→ Pas time to split" << endl;
            cout << "Avant move : " << p->get_positionx() << ", " << p->get_positiony() << endl;
            p->move(arene);
            cout << "Après move : " << p->get_positionx() << ", " << p->get_positiony() << endl;
        }
    }
    cout << "Fin update_particules" << endl;
}


void update_faiseurs(){
    auto& faiseurs = Faiseur::get_liste_faiseurs();
    cout << "Mise à jour faiseur" << endl;

    for(size_t i=0; i<faiseurs.size(); i++){
        bool collision = false;
        const auto& f = faiseurs[i];
        auto& elements = f->get_elements();
        auto& tete= elements[0];//Creation tete faiseur
        S2d new_position = {tete->get_positionx() + f->get_vitesse().get_x(), tete->get_positiony() + f->get_vitesse().get_y()};
        Cercle c_test(new_position, f->get_rayon());
        for(size_t j=0; j<faiseurs.size(); ++j){
            if(i==j) continue;
            const auto& f_autre= faiseurs[j]->get_elements();
            for(const auto& k : f_autre){
                Cercle autre(k->get_position(), faiseurs[j]->get_rayon());
                if(Cercle::intrusion(c_test, autre)){
                    cout << "Faiseur: " << i << " collision avec faiseur: " << j << endl;
                    collision = true;
                    break;
                }
            }
            if(collision){break;}
        }
      if(!collision){
        cout << "Pas de collision" << endl;
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
Mobile::Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init)
    : position(position_init), vitesse(vitesse_init), alpha(alpha_init), rayon(rayon_init) { }

    void Mobile::move(const Cercle arene) {
        cout << "Mise à jour position" << endl;
        cout << "Vitesse: " << vitesse.get_x() << " , " << vitesse.get_y() << endl;
    
        S2d new_position = {position.x + vitesse.get_x(), position.y + vitesse.get_y()};
        Cercle c_test(new_position, rayon);
    
        if (!Cercle::inclusion(arene, c_test)) {
            cout << "Particule/faiseur hors arène → déclenchement du rebond" << endl;
            Vecteur v_reflechis = vitesse.reflechis(position);
            vitesse = v_reflechis; 
            alpha = v_reflechis.get_angle();
    
            new_position.x = position.x + v_reflechis.get_x();
            new_position.y = position.y + v_reflechis.get_y();
        }
        position = new_position;
        cout << "Nouvelle position: " << position.x << " , " << position.y << endl;
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
        cout << "Particule number: " << i << " , point: " << p->get_positionx() << " : " << p->get_positiony() << "\n";
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
    ++compteur;  // ou autre logique selon ton besoin
}

void Particule::reset() {
    liste_particule.clear();
    nbrs_particules = 0; 
}


//==========================FAISEUR====================================================

Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements)
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
    for(size_t i=0; i < elements.size(); ++i) {
        cout << "Deplacement de l'element: " << i << endl;
        cout << "Position initiale de l'element: " << elements[i]->get_positionx() << " : " << elements[i]->get_positiony() << endl;
    }
    cout << "Deplacement du faiseur" << endl;
    for(const auto& element : elements) {
    element->move(arene);
    }
    for(size_t i=0; i < elements.size(); ++i) {
        cout << "Deplacement de l'element: " << i << endl;
        cout << "Position finale de l'element: " << elements[i]->get_positionx() << " : " << elements[i]->get_positiony() << endl;
    }
  cout << "Fin du deplacement des elements du faiseur" << endl;
}

void Faiseur::reset() {
    liste_faiseurs.clear();
}

namespace {
        bool verifier_collision_faiseur(const unique_ptr<Faiseur>& f) {
            const auto& nouveaux_elements = f->get_elements();
            const auto& faiseurs = Faiseur::get_liste_faiseurs();

            int index_faiseur = static_cast<int>(faiseurs.size()); // index futur, car pas encore ajouté
            for (size_t k = 0; k < nouveaux_elements.size(); ++k) {
                Cercle c1(nouveaux_elements[k]->get_position(), f->get_rayon());
                for (size_t i = 0; i < faiseurs.size(); ++i) {
                    const auto& faiseur_i = faiseurs[i];
                    const auto& elements_i = faiseur_i->get_elements();
                    for (size_t j = 0; j < elements_i.size(); ++j) {
                        Cercle c2(elements_i[j]->get_position(), faiseur_i->get_rayon());
                        if (Cercle::intrusion(c1, c2)) {
                            cout << message::faiseur_element_collision(index_faiseur, k, i, j);
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    }
    

