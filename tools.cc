#define _USE_MATH_DEFINES //pour cmath constantes

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "tools.h"

using namespace std;

constexpr double epsil_zero = 0.5;


Vecteur::Vecteur(const S2d& p1, const S2d& p2) : x(p2.x - p1.x), y(p2.y - p1.y)
{
    angle = atan2(y, x);
    norme = sqrt(x * x + y * y);
}

Vecteur::Vecteur(const S2d& p, const double& norme, const double& angle)
    : x(p.x), y(p.y), angle(angle), norme(norme)
{
    if (norme < 0)
    {
        cerr << "norme negative : tools.cc " << __LINE__ << endl;
        exit(EXIT_FAILURE);
    }
}

Vecteur Vecteur::reflechis(const S2d &point)
{
    S2d point_zero_zero; 
    Vecteur v_centre(point_zero_zero, point);
    double angle = M_PI + 2 * v_centre.get_angle() - this->get_angle();
    if (angle < -M_PI or angle > M_PI){ //normaliser la norme entre -pi et pi
        angle = fmod(angle, M_PI);
    }
    Vecteur reflechis(point, this->get_norme(), angle);
    return reflechis;
    //la fonction reflechis marche pour les cas logiques, CAD pour les cas qui se produiront.
    //Si le vecteur va dans le sens opposé du point de reflexion, alors les résultats sont bidons.
}

// Getters and setters
double Vecteur::get_x() const { return x; }
double Vecteur::get_y() const { return y; }
double Vecteur::get_angle() const { return angle; }
double Vecteur::get_norme() const { return norme; }
void Vecteur::set_x(double new_x) { this->x = new_x; }
void Vecteur::set_y(double new_y) { this->y = new_y; }
void Vecteur::set_angle(double new_angle) { this->angle = new_angle; }
void Vecteur::set_norme(double new_norme) { this->norme = new_norme; }

Cercle::Cercle(S2d centre, double rayon)
    : centre(centre), rayon(rayon)
{
    if (rayon < 0)
    {
        cerr << "rayon negatif, tools.cc, l" << __LINE__ << endl;
        exit(EXIT_FAILURE);
    }
}

// Getters and setters
S2d Cercle::get_centre() const { return centre; }
double Cercle::get_rayon() const { return rayon; }
void Cercle::set_centre(S2d centre) { this->centre = centre; }
void Cercle::set_rayon(double rayon) { 
    if (rayon < 0)
    {
        cerr << "rayon negatif, tools.cc, l" << __LINE__ << endl;
        exit(EXIT_FAILURE);
    }
    this->rayon = rayon; 
}
void Cercle::epsilTrue() { epsil = true; }
void Cercle::epsilFalse() { epsil = false; }// no static needed in .cc file
bool Cercle::get_epsil() { return epsil; } // techniquement inutile
//on peut juste acceder direct par Cercle::epsil

bool Cercle::inclusion(const Cercle &c1, const Cercle &c2)
{
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() - c2.get_rayon() - epsil_zero * epsil));
}

bool Cercle::intrusion(const Cercle &c1, const Cercle &c2)
{
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() + c2.get_rayon() + epsil_zero * epsil));
}
bool Cercle::epsil = false;  //Define the static variable


