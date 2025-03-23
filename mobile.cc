#include <iostream> 

#include "tools.h"
#include "constantes.h"
#include "message.h"
#include "mobile.h"

using namespace std;

class Arene {
    public:
        Arene(double r) : r_max(r), centre(), arene({0,0},0 , r) {}  //constexpr en parametre 
                                            //j'ai changé l'argument en metant 0,0 pour le centre et 0 pour l'angle
        Vecteur get_vecteur() const {return arene;}
        
        bool in_cercle(S2d position, double rayon) const {
            Vecteur mobile(position);
            return((mobile.get_norme() + rayon) < r_max); // plus petit ou egal ?
        }
    
    private:
        S2d centre;  
        Vecteur arene;  
        double r_max;  
    };
  

class Mobile{
    public:
    Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init)
    : position(position_init), vitesse(vitesse_init), alpha(alpha_init), rayon(rayon_init) {}

     virtual void mise_a_jour(const Arene& arene){
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
     };
     // methode de lecture fichier 
     double get_positionx(){return position.x;};
     double get_positiony(){return position.y;};

    protected:
    S2d position;
    Vecteur vitesse;
    double alpha; 
    double rayon;
};


class Particule : public Mobile{
    public:
    Particule(S2d position_init, Vecteur vitesse_init, double alpha_init)
        : Mobile(position_init, vitesse_init, alpha_init, 0.), compteur(0){
        ++nbrs_particules;  
    }
    void mise_a_jour(const Arene& arene) override{
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
    };
    ~Particule(){--nbrs_particules;}

    private:
    static int nbrs_particules;
    int compteur;
};

int Particule::nbrs_particules = 0;

class Faiseur : public Mobile{
public:
Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements)
        : Mobile(position_init, vitesse_init, alpha_init, rayon_init), nbs_elements(nb_elements){
        elements.resize(nbs_elements, position_init);  
        liste_faiseurs.push_back(this);
    };
    void mise_a_jour(const Arene &arene){
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
    }
    bool collisions(const Faiseur *autre){
        for (const auto &e1 : elements){
            Cercle c1(e1, rayon);
            for (const auto &e2 : autre->elements){
                Cercle c2(e2, autre->rayon);
                if (Cercle::intrusion(c1, c2)){
                    return true;
                }
            }
        }
        return false;
    }
private:
    int nbs_elements;
    vector<S2d> elements;
    static vector<Faiseur*> liste_faiseurs;

};
vector<Faiseur*> Faiseur::liste_faiseurs;


int main() {
    // Créer une arène avec un rayon de 10 unités
    Arene arene(10.0);

    // Créer deux Faiseurs qui se touchent après deux mises à jour
    S2d positionFaiseur1 = {0.0, 0.0};
    Vecteur vitesseFaiseur1(positionFaiseur1, 1.0, 0.0); // Vitesse dirigée vers la droite
    Faiseur faiseur1(positionFaiseur1, vitesseFaiseur1, 0.0, 1.0, 5);

    S2d positionFaiseur2 = {2.0, 0.0};
    Vecteur vitesseFaiseur2(positionFaiseur2, 1.0, M_PI); // Vitesse dirigée vers la gauche
    Faiseur faiseur2(positionFaiseur2, vitesseFaiseur2, M_PI, 1.0, 5);

    // Mettre à jour les positions des Faiseurs
    faiseur1.mise_a_jour(arene);
    faiseur2.mise_a_jour(arene);
    faiseur1.mise_a_jour(arene);
    faiseur2.mise_a_jour(arene);

    // Vérifier s'ils se touchent
    if (faiseur1.collisions(&faiseur2)) {
        std::cout << "Les Faiseurs se touchent après deux mises à jour." << std::endl;
    } else {
        std::cout << "Les Faiseurs ne se touchent pas." << std::endl;
    }

    // Créer une Particule qui rebondit
    S2d positionParticule = {5.0, 0.0};
    Vecteur vitesseParticule(positionParticule, 2.0, M_PI / 4); // Vitesse dirigée en diagonale
    Particule particule(positionParticule, vitesseParticule, M_PI / 4);

    // Mettre à jour la position de la Particule
    particule.mise_a_jour(arene);
    particule.mise_a_jour(arene);

    // Afficher la position finale de la Particule
    std::cout << "Position finale de la Particule : ("
              << particule.get_positionx() << ", "
              << particule.get_positiony() << ")" << std::endl;

    return 0;
}
