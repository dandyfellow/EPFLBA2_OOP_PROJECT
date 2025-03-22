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
  
/* J'ai tout mis en commentaire pasque sinons ca marche pas avec mobile.h et jeu.cc
class Mobile{
    public:
     void mise_a_jour(Arene arene){
        position.x += vitesse.get_norme() * cos(alpha);
        position.y += vitesse.get_norme() * sin(alpha);
        if (arene.in_cercle(position, rayon)){
            return;
        }else{
            position.x -= vitesse.get_norme() * cos(alpha);
            position.y -= vitesse.get_norme() * sin(alpha);
            vitesse = vitesse.reflechis(position);
             //alpha = nouvel angle de deplacement du vecteur reflechis = - alpha 
        }       
     };


    protected:
    S2d position;
    Vecteur vitesse;
    double alpha; // orientation alpha du deplacement 
    double rayon;


};
*/
//class Faiseur : public Mobile {}; j'ai mis dans mobile.h sinons ca marche pas pour jeu.cc
//class Particule : public Mobile{};

