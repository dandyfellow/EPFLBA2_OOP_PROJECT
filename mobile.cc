#include "mobile.h"

Cercle Arene({0,0}, r_max);
int Particule::nbrs_particules = 0;
vector<Particule*> Particule::liste_particule;
vector<Faiseur*> Faiseur::liste_faiseurs;


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

Particule::Particule(S2d position_init, Vecteur vitesse_init, double alpha_init, int compteur)
    : Mobile(position_init, vitesse_init, alpha_init, 0.), compteur(compteur) {
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

void Particule::set_nbrs_particules(int n) {
    nbrs_particules = n;
}


vector<Faiseur> Faiseur::liste_faiseurs;
int Faiseur::compteur_faiseurs = 0;

Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements)
    : Mobile(position_init, vitesse_init, alpha_init, rayon_init), index(compteur_faiseurs++) {
    elements.reserve(nb_elements);
}

void Faiseur::ajouter_faiseur(const Faiseur& f) {
    liste_faiseurs.push_back(f);
}

vector<Faiseur>& Faiseur::get_liste_faiseurs() {
    return liste_faiseurs;
}

// Ajout d'un élément avec un index unique
void Faiseur::ajouter_element(const S2d& position) {
    elements.emplace_back(compteur_elements++, position);
}

// Récupérer les éléments avec leurs indices
vector<std::pair<int, S2d> > Faiseur::get_elements() const {
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

    Cercle c1({x, y}, 0.);
    Vecteur v({x, y}, deplacement, angle);

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
        cout << message::faiseur_nbe(nbe) << endl;
        return false;
    }

    if (rayon < r_min_faiseur || rayon > r_max_faiseur) {
        cout << message::faiseur_radius(rayon) << endl;
        return false;
    }

    if (v.get_norme() < 0 || v.get_norme() > d_max) {
        cout << message::mobile_displacement(deplacement);
        return false;
    }

    S2d position = {x, y};
    Faiseur f(position, v.get_norme(), angle, rayon, nbe);

    for (int i = 0; i < nbe; ++i) {
        double new_x = x - i * deplacement * cos(angle);
        double new_y = y - i * deplacement * sin(angle);
        Cercle c_test({new_x, new_y}, rayon);

        if (!Cercle::inclusion(arene, c_test)) {
            position.x -= v.get_norme() * cos(v.get_angle());
            position.y -= v.get_norme() * sin(v.get_angle());
            v = v.reflechis(position);
            v.set_angle(v.get_angle()); // Corrected this line
            position.x += v.get_norme() * cos(v.get_angle());
            position.y += v.get_norme() * sin(v.get_angle());
        }

        f.ajouter_element({position.x, position.y});
    }
    for (const auto& autre_faiseur : Faiseur::get_liste_faiseurs()) {  
        for (const auto& [index, centre] : f.get_elements()) {
            Cercle current_cercle(centre, rayon);
            for (const auto& [autre_index, autre_centre] : autre_faiseur.get_elements()) { 
                Cercle autre_cercle(autre_centre, autre_faiseur.get_rayon()); 
                if (Cercle::intrusion(current_cercle, autre_cercle)) {
                    cout << message::faiseur_element_collision(f.get_index(), index, autre_faiseur.get_index(), autre_index);
                    return false;
                }
            }
        }
    }
    Faiseur::ajouter_faiseur(f);
    return true;
}
#include <iostream>
#include <sstream>
#include <vector>
#include "mobile.h"

using namespace std;

int main() {
    cout << "=== Début du programme - Création des particules et faiseurs ===\n";
    
    string input;
    istringstream data;
    
    // Lecture et création des particules
    while (true) {
        cout << "\nEntrez les données de la particule (x y angle déplacement compteur) ou 'stop' pour terminer : ";
        getline(cin, input);
        if (input == "stop") break;

        data.clear();
        data.str(input);

        if (!lecture_p(data)) {
            cout << "❌ Erreur dans les données de particule. Arrêt du programme.\n";
            return 1;
        } else {
            cout << "✅ Particule ajoutée avec succès.\n";
        }
    }

    // Lecture et création des faiseurs
    while (true) {
        cout << "\nEntrez les données du faiseur (x y angle déplacement rayon nb_elements) ou 'stop' pour terminer : ";
        getline(cin, input);
        if (input == "stop") break;

        data.clear();
        data.str(input);

        if (!lecture_f(data)) {
            cout << "❌ Erreur dans les données de faiseur. Arrêt du programme.\n";
            return 1;
        } else {
            cout << "✅ Faiseur ajouté avec succès.\n";
        }
    }

    // Affichage des particules créées
    cout << "\n=== Liste des particules créées ===\n";
    for (const auto& particule : Particule::liste_particule) {  
        cout << "Particule - Position: (" << particule->get_positionx() << ", " << particule->get_positiony() 
             << ") | Compteur: " << particule->get_compteur() << endl;
    }

    // Affichage des faiseurs créés
    cout << "\n=== Liste des faiseurs créés ===\n";
    for (const auto& faiseur : Faiseur::get_liste_faiseurs()) {  
        cout << "Faiseur - Position: (" << faiseur.get_positionx() << ", " << faiseur.get_positiony() 
             << ") | Rayon: " << faiseur.get_rayon() << " | Nb éléments: " << faiseur.get_elements().size() << endl;
    }

    cout << "\n=== Programme terminé avec succès. ===\n";
    return 0;
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