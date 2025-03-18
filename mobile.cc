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
        Vecteur get_vecteur() const { return arene; }
        
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
     void mise_a_jour(Arene arene){
       // position.x+= vitesseX;
       // position.y+= vitesseY;
        if (arene.in_cercle(position, rayon)){return;}
        else{
       //     position.x-=vitesseX;
       //     position.y-=vitesseY;
            Vecteur mobile(position);
       //     vecteur actuel =mobile.reflechis(); 
        }       
     };


    protected:
    S2d position;
    // orientation alpha du deplacement 
    double rayon;


};

class Faiseur : public Mobile {};
class Particule : public Mobile{};
