#include <iostream>
#include <cmath>
#include "tools.h"
/*
#include 'chaine.h'
#include 'mobile.h' 
#include 'jeu.h'
*/
/*
CHOSES A FAIRE :

TOUTES LES STRUCT N'ONT QUE DES xATTRUBUTS, SI ON VEUT DES METHODES ON FAIT DES CLASSES
Mettre des testeurs, genre r > 0, etc.

*/

using namespace std;
constexpr double epsil_zero(0.5);
static bool epsil;

struct S2d {double x=0.; double y=0.;};

class Vecteur { //Vecteur, x, y, angle, norme, avec deux constructeurs 
public:
    Vecteur(const S2d& p1={0,0}, const S2d& p2={0,0}) : x(p2.x-p1.x), y(p2.y-p1.y) {
        angle = atan2(y,x);
        norme = sqrt(x*x + y*y);
    }
    Vecteur(const S2d& p, const double& angle, const double& norme) : angle(angle), norme(norme), x(p.x), y(p.y) {
        if(norme < 0){
            cerr << "norme negative : tools.cc" << __LINE__ << endl;
            exit(EXIT_FAILURE);
        }
    }
    //pour former le vecteur AB, il faut faire vecteur(A,B) et pas vecteur(B,A)
    //pour former le vecteur de norme et d'angle, il faut faire vecteur(A,angle,norme)

    Vecteur reflechis(const S2d& point){
        S2d point_zero_zero; //Creer le vectueur centre du cercle -> Point(0,0)
        Vecteur v_centre(point_zero_zero, point); //Creer le vecteur entre le centre du cercle et 
        Vecteur reflechis(point, (M_PI + 2 * v_centre.get_angle() - this->get_angle()), this->get_norme());
        return reflechis;
     }


    //getters and setters
    double get_x() const {return x;}
    double get_y() const {return y;}
    double get_angle() const {return angle;}
    double get_norme() const {return norme;}
    void set_x(double x) {this->x = x;}
    void set_y(double y) {this->y = y;}
    void set_angle(double angle) {this->angle = angle;}
    void set_norme(double norme) {this->norme = norme;}

private:
    double x=0.;
    double y=0.;
    double angle=0.; //en radians
    double norme=0.;
    //Vecteur operator+(const Vecteur& v) const {return {x+v.x, y+v.y};} //surcharge de l'opérateur + on garde l'idée
    //surcharge de constructeur
    
};

class Cercle {
public:
    Cercle(S2d centre, double rayon) : centre(centre), rayon(rayon) { 
        if (rayon < 0){
            cerr << "rayon negatif, tools.cc" << __LINE__ << endl;
            exit(EXIT_FAILURE);
        }

    }
    //getters and setters
    S2d get_centre() const {return centre;}
    double get_rayon() const {return rayon;}
    void set_centre(S2d centre) {this->centre = centre;}
    void set_rayon(double rayon) {this->rayon = rayon;}

private:
    S2d centre;
    double rayon;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                          INDEPENDENT FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 bool inclusion(const Cercle &c1, const Cercle &c2){
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() - c2.get_rayon() - epsil_zero * epsil)); // <<<<< A REVOIRe{
 }

 bool intrusion (const Cercle &c1, const Cercle &c2){
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() + c2.get_rayon() + epsil_zero*epsil));
 }
