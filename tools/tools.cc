#include <iostream>
#include <cmaths>
#include 'chaine.h'
#include 'mobile.h' 
#include 'jeu.h'

using namespace std;

constexpr double epsil_zero(0.5);

struct S2d {double x=0.; double y=0.;};

struct Vecteur { //public ou privé?? class ou struct
    double x=0.;
    double y=0.;
    double angle = atan2(y,x); //en radians
    double norme = sqrt(x*x+y*y);
    //Vecteur operator+(const Vecteur& v) const {return {x+v.x, y+v.y};} //surcharge de l'opérateur + on garde l'idée
    //Constructor
    Vector(double x, double y) : x(x), y(y) {}
}

struct Cercle {

}

 Vecteur reflechis(Vecteur incident, S2d point){
    
 }
