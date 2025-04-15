//tools.h, Adam Coste et Max Ciriani, version 1
#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "graphic.h"

constexpr double epsil_zero(0.5);

struct S2d {
    double x = 0.;
    double y = 0.;
};

class Vecteur {
public:
    Vecteur(const S2d& p1 = {0, 0}, const S2d& p2 = {0, 0}); //acts as default constr
    Vecteur(const S2d& p, const double& norme, const double& angle);

    Vecteur reflechis(const S2d& point);
    void draw_vecteur(const double& width, Color color);

    // getters and setters
    S2d get_p1() const{ return p1; };
    S2d get_p2() const{ return p2; };
    double get_x() const{ return x; };
    double get_y() const{ return y; };
    double get_angle() const{ return angle; };
    double get_norme() const{ return norme; };
    void set_x(double x);
    void set_y(double y);
    void set_angle(double angle);
    void set_norme(double norme);
    
private:
    S2d p1;
    S2d p2;
    // x, y are p1.x and p1.y respectively -> useless but used in many functions
    double x; //p1.x
    double y; //p1.y
    double angle; // en radians
    double norme;
};

class Cercle {
public:
    Cercle(S2d centre, double rayon);

    static bool inclusion(const Cercle &c1, const Cercle &c2);
    static bool intrusion(const Cercle &c1, const Cercle &c2);
    void draw_cercle(const double& width, const Color& c1, const Color& c2);

    static void epsilTrue();
    static void epsilFalse();


    //getters and setters
    S2d get_centre() const{ return centre; };
    double get_rayon() const{ return rayon; };
    static bool get_epsil(){ return epsil; };

    void set_centre(S2d centre);
    void set_rayon(double rayon);
    
   
private:
    static bool epsil;
    S2d centre = {0, 0};
    double rayon = 0.;
};

#endif // TOOLS_H
