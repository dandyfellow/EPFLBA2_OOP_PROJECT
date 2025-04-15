//tools.cc, Adam Coste et Max Ciriani, version 1
#define _USE_MATH_DEFINES //pour cmath constantes -> NEEDS TO COME BEFORE CMATH

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "tools.h"
#include "graphic.h"

using namespace std;

//=====================================Vecteur=========================================

Vecteur::Vecteur(const S2d& p1, const S2d& p2) : p1(p1), p2(p2), x(p2.x - p1.x), 
                                                 y(p2.y - p1.y) {
    angle = atan2(y, x);
    norme = sqrt(x * x + y * y);
}

Vecteur::Vecteur(const S2d& p, const double& norme, const double& angle)
    : p1(p), p2({p.x + norme * cos(angle), p.y + norme * sin(angle)}),
      x(norme * cos(angle)), y(norme * sin(angle)),
      angle(0), norme(norme) {

    if (norme < 0){
        cerr << "norme negative : tools.cc " << __LINE__ << endl;
        exit(EXIT_FAILURE);
    }
    double a = angle;
    if (a < -M_PI or a > M_PI){ 
        this->angle = fmod(a, M_PI);
    } else {
        this->angle = a;
    }
}

Vecteur Vecteur::reflechis(const S2d& point) {
    Vecteur normale({0, 0}, point);
    double nx = normale.get_x();
    double ny = normale.get_y();

    double dot = get_x() * nx + get_y() * ny;

    double norme2 = nx * nx + ny * ny;

    double rx = get_x() - 2 * dot / norme2 * nx;
    double ry = get_y() - 2 * dot / norme2 * ny;

    S2d arrivee;
    arrivee.x = point.x + rx;
    arrivee.y = point.y + ry;

    return Vecteur(point, arrivee);
}


void Vecteur::set_x(double new_x) { this->x = new_x; }
void Vecteur::set_y(double new_y) { this->y = new_y; }
void Vecteur::set_angle(double new_angle) { this->angle = new_angle; }
void Vecteur::set_norme(double new_norme) { this->norme = new_norme; }

void Vecteur::draw_vecteur(const double& width, Color color) {
    Graphic::draw_vecteur(p1.x, p1.y, p2.x, p2.y, width, color);
}

//=====================================Cercle==========================================
bool Cercle::epsil = false;  
Cercle::Cercle(S2d centre, double rayon)
    : centre(centre), rayon(rayon){}

void Cercle::set_centre(S2d centre) { this->centre = centre; }
void Cercle::set_rayon(double rayon) { this->rayon = rayon; }
void Cercle::epsilTrue() { epsil = true; }
void Cercle::epsilFalse() { epsil = false; }// no static needed in .cc file

bool Cercle::inclusion(const Cercle &c1, const Cercle &c2){ //return true if c2 in c1
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() - c2.get_rayon() - epsil_zero * epsil));
}

bool Cercle::intrusion(const Cercle &c1, const Cercle &c2){
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() + c2.get_rayon() + epsil_zero * epsil));
}

void Cercle::draw_cercle(const double& width, const Color& c1, const Color& c2){
    Graphic::draw_cercle(centre.x, centre.y , rayon, width, c1, c2);
}



