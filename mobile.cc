// mobile.cc, Adam Coste et Max Ciriani, version 1
#include <memory>
#include "mobile.h"
#include <cmath>  // Pour cos, sin

using namespace std;

namespace {
    bool verifier_collision_faiseur(const unique_ptr<Faiseur>& f);
    Cercle Arene({0, 0}, r_max);
}

vector<Particule*> Particule::liste_particule;
vector<unique_ptr<Faiseur>> Faiseur::liste_faiseurs = {};
int Particule::nbrs_particules = 0;

Mobile::Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init)
    : position(position_init), vitesse(vitesse_init), alpha(alpha_init), rayon(rayon_init) { }

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

    Vecteur v({x, y}, deplacement, angle + 3.14159265358979323846);  // angle + pi pour adapter à l'angle réfléchi
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

    for (int i = 0; i < nbe; ++i) {
        double new_x = position.x - deplacement * cos(angle);
        double new_y = position.y - deplacement * sin(angle);
        Cercle c_test({new_x, new_y}, rayon);

        if (!Cercle::inclusion(arene, c_test)) {
            v = v.reflechis(position);
            angle = v.get_angle();
            new_x = position.x - deplacement * cos(angle);
            new_y = position.y - deplacement * sin(angle);
        }

        f->ajouter_element(make_unique<Mobile>(S2d{new_x, new_y}, v, angle, rayon));
        position.x = new_x;
        position.y = new_y;
    }
    if (!verifier_collision_faiseur(f)) {
        return false;
    }
    Faiseur::ajouter_faiseur(std::move(f));
    return true;
}

void Mobile::move(const Cercle arene) {
    cout << "Mise à jour position" << endl;
    S2d new_position = {position.x + vitesse.get_x(), position.y + vitesse.get_y()};
    Cercle c_test(new_position, rayon);
    if (!Cercle::inclusion(arene, c_test)) {
        Vecteur v_reflechis = vitesse.reflechis(position);
        alpha = v_reflechis.get_angle();
        new_position.x = position.x + v_reflechis.get_x();
        new_position.y = position.y + v_reflechis.get_y();
    }
    position.x = new_position.x;
    position.y = new_position.y;
}

Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements)
    : Mobile(position_init, vitesse_init, alpha_init, rayon_init) {
    
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
    

/*void mise_a_jour_p(const Cercle arene){
    vector<Particule*> liste_particule_temporaire;

    for (Particule* p : Particule::liste_particule) {
        liste_particule_temporaire.push_back(new Particule(*p));
    }
    cout << "nombres particules initiale(taille tableau): " << Particule::liste_particule.size() << endl;
    cout << "nombres particules initiale(nbrs_particules): " << Particule::get_nbrs_particules() << endl;

    for (const auto &p : liste_particule_temporaire){
        p->increase_compteur();
        if (p->get_compteur() == time_to_split){
            cout << "Time to split" << endl;
            if (Particule::get_nbrs_particules() == nb_particule_max){
                cout << "Trop de particules, suppression" << endl;
                delete p;
                Particule::liste_particule.erase(remove(Particule::liste_particule.begin(), Particule::liste_particule.end(), p), Particule::liste_particule.end());
                continue;
            }else{
                cout << "Split de particules" << endl;
                Vecteur nouvelle_vitesse1(p->get_position(), (p->get_vitesse().get_norme() * coef_split), p->get_alpha() + delta_split);
                Vecteur nouvelle_vitesse2(p->get_position(), (p->get_vitesse().get_norme() * coef_split), p->get_alpha() - delta_split);
                Particule* nouvelle_particule1 = new Particule(p->get_position(), nouvelle_vitesse1, p->get_alpha() + delta_split);
                Particule* nouvelle_particule2 = new Particule(p->get_position(), nouvelle_vitesse2, p->get_alpha() - delta_split);
                Particule::liste_particule.push_back(nouvelle_particule1);
                Particule::liste_particule.push_back(nouvelle_particule2);
                delete p;
                Particule::liste_particule.erase(remove(Particule::liste_particule.begin(), Particule::liste_particule.end(), p), Particule::liste_particule.end());//verifier si marche
                nouvelle_particule1->move(arene);
                nouvelle_particule2->move(arene);
                continue;
            }
        }else{
            cout << "Pas time to split" << endl;
            p->move(arene);
        }
        cout << "nombres particules finale(taille tableau): " << Particule::liste_particule.size() << endl;
        cout << "nombres particules finale(nbrs_particules): " << Particule::get_nbrs_particules() << endl;
    }
};

void mise_a_jour_faiseur(const Cercle arene){
    for (auto &faiseur : Faiseur::get_liste_faiseurs()){
        faiseur->move(arene);
        for(auto &element : faiseur->get_elements()){
            
        }
        faiseur->move(arene);
           
    }
}*/
