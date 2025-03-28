#include "mobile.h"
#include <memory>

using namespace std;

int Particule::nbrs_particules = 0;
vector<Particule*> Particule::liste_particule;
vector<shared_ptr<Faiseur>> Faiseur::liste_faiseurs = {};
int Faiseur::compteur_faiseurs = 0;
//bool Particule::isInitialized = false;

Cercle Arene({0,0}, r_max);



Mobile::Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init)
    : position(position_init), vitesse(vitesse_init), alpha(alpha_init), rayon(rayon_init) {}

double Mobile::get_positionx() const {
    return position.x;
}

double Mobile::get_positiony() const {
    return position.y;
}

double Mobile::get_rayon() const{
    return rayon;
}

Particule::Particule(S2d position_init, Vecteur vitesse_init, double alpha_init)
    : Mobile(position_init, vitesse_init, alpha_init, 0.){
    ++nbrs_particules;
    liste_particule.push_back(this);
}


Particule::~Particule() {
    --nbrs_particules;
}

int Particule::get_compteur() const {
    return compteur;
}

void Particule::set_compteur(int c) {
    compteur = c;
}

int Particule::get_nbrs_particules() {
    return nbrs_particules;
}
/*void Particule::initializeCounter(double c) {
    if (!isInitialized){
        Particule:: compteur= c;
        isInitialized = true;
    }
}*/

Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements)
    : Mobile(position_init, vitesse_init, alpha_init, rayon_init), index(compteur_faiseurs++) {
    elements.reserve(nb_elements);
}

void Faiseur::ajouter_faiseur(shared_ptr<Faiseur> f) { //STATIC
    liste_faiseurs.push_back(f);
}

const vector<shared_ptr<Faiseur>>& Faiseur::get_liste_faiseurs(){
    return liste_faiseurs;
}

void Faiseur::ajouter_element(const S2d& position) {
    elements.emplace_back(compteur_elements++, position);
}

vector<pair<int, S2d>> Faiseur::get_elements() const {
    return elements;
}
    
/*bool Faiseur::collisions(const Faiseur* autre) {
    for (const auto& [index1, e1] : autre.get_elements()) {  // Utilisation de get_elements()
        Cercle c1(e1, autre.get_rayon());  // Utilisation de get_rayon()
        for (const auto& [index2, e2] : autre->get_elements()) {  // Accès via get_elements()
            Cercle c2(e2, autre->get_rayon());  // Accès via get_rayon()
            if (Cercle::intrusion(c1, c2)) {
                return true;
            }
        }
    }
    return false;
}*/

bool lecture_p(istringstream& data) {
    Cercle arene({0, 0}, r_max);
    double x, y, angle, deplacement, compteur;
    data >> x >> y >> angle >> deplacement >> compteur;
    //cout << "x: " << x << " y: " << y << " angle: " << angle << " deplacement: " << deplacement << " compteur: " << compteur << endl;

    Cercle c1({x, y}, 0.);
    Vecteur v({x, y}, deplacement, angle);
    //Particule::initializeCounter(compteur);

    if (compteur >= time_to_split || compteur < 0) {
        cout << message::particule_counter(compteur) << endl;
        return false;
    }
    if (!Cercle::inclusion(arene, c1)) {
        cout << message::particule_outside(x, y) << endl;
        return false;
    }
    if (v.get_norme() < 0 || v.get_norme() > d_max) {
        cout << message::mobile_displacement(deplacement) << endl;
        return false;
    }
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
    if(!Cercle::inclusion(arene, c2)){
        cout << message::faiseur_outside(x,y);
        return false;
    }

    S2d position = {x, y};
    auto f = make_shared<Faiseur>(position, v, angle, rayon, nbe); //using shared_ptr for Faiseur
    double cos_a= cos(angle);
    double sin_a= sin(angle);

    for (int i = 0; i < nbe; ++i) {
        double new_x = x - i * deplacement * cos_a;
        double new_y = y - i * deplacement * sin_a;
        Cercle c_test({new_x, new_y}, rayon);

        if (!Cercle::inclusion(arene, c_test)) {
            position.x -= v.get_norme() * cos(v.get_angle());
            position.y -= v.get_norme() * sin(v.get_angle());
            v = v.reflechis(position);
            v.set_angle(v.get_angle()); 
            position.x += v.get_norme() * cos(v.get_angle());
            position.y += v.get_norme() * sin(v.get_angle());
        }

        f->ajouter_element({position.x, position.y});
    }
    for (const auto& autre_faiseur : Faiseur::get_liste_faiseurs()) { 
        for (const auto& [index, centre] : f->get_elements()) {
            //cout << index << endl;
            Cercle current_cercle(centre, rayon);
            for (const auto& [autre_index, autre_centre] : autre_faiseur->get_elements()) { 
                //cout << autre_index << endl;
                Cercle autre_cercle(autre_centre, autre_faiseur->get_rayon());
                if (!Cercle::intrusion(current_cercle, autre_cercle)) {
                    cout << message::faiseur_element_collision(
                        f->get_index(), index, autre_faiseur->get_index(), autre_index
                    );
                    return false;
                }
            }
        }
    }
    Faiseur::ajouter_faiseur(f);
    return true;
}   

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