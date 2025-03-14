#include <iostream>
#include <cmath>
/*

#include 'chaine.h'
#include 'mobile.h' 
#include 'jeu.h'

*/

using namespace std;
constexpr double epsil_zero(0.5);


struct S2d {double x=0.; double y=0.;};

struct Vecteur { //public ou privé?? class ou struct
    double x=0.;
    double y=0.;
    double angle=0.; //en radians
    double norme=0.;
    //Vecteur operator+(const Vecteur& v) const {return {x+v.x, y+v.y};} //surcharge de l'opérateur + on garde l'idée
    //Constructor
    Vecteur(const S2d& p1, const S2d& p2) : x(p2.x-p1.x), y(p2.y-p1.y) {
        angle = atan2(y,x);
        norme = sqrt(x*x + y*y);
    }
    Vecteur(const S2d& p, const double& angle, double norme) : angle(angle), norme(norme), x(p.x), y(p.y) {}
    //pour former le vecteur AB, il faut faire vecteur(A,B) et pas vecteur(B,A)
    //pour former le vecteur de norme et d'angle, il faut faire vecteur(A,angle,norme)
    //surcharge de constructeur
};

class Cercle {
    public:
    Cercle(S2d centre, double rayon) : centre(centre), rayon(rayon) {}
    bool inclusion(const  Cercle& c1){
        Vecteur v1(c1.centre, this->centre);
        double distance = v1.norme; 
        if (distance < (this->rayon - c1.rayon - epsil_zero)){
            return true;
        }else{ 
            return false;
        }
    }
    bool intersection(const Cercle& c1){
        Vecteur v1(c1.centre, this -> centre);
        double distance = v1.norme;
        if(distance < (this->rayon - c1.rayon + epsil_zero)){
            return true;
         }else{
            return false;
         }
    }
    
    private:

    S2d centre;
    double rayon;
    
};

 Vecteur reflechis(Vecteur incident, S2d point){
    S2d point_zero_zero; //Creer le vectueur centre du cercle -> Point(0,0)
    Vecteur v_centre(point_zero_zero, point); //Creer le vecteur entre le centre du cercle et 
    Vecteur reflechis(point, (M_PI + 2 * v_centre.angle - incident.angle), incident.norme);
    return reflechis;
 }

