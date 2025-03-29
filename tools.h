#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <iostream>
#include <cstdlib>


struct S2d {
    double x = 0.;
    double y = 0.;
};

class Vecteur {
public:
    Vecteur(const S2d& p1 = {0, 0}, const S2d& p2 = {0, 0});
    Vecteur(const S2d& p, const double& norme, const double& angle);
     // ne pas mettre de valeur par défaut, sinon confusion pour valeur par défaut lorsqu'on fait Vecteur v;
    Vecteur reflechis(const S2d& point);

    // Getters and setters
    double get_x() const;
    double get_y() const;
    double get_angle() const;
    double get_norme() const;
    void set_x(double x);
    void set_y(double y);
    void set_angle(double angle);
    void set_norme(double norme);
    
private:
    double x = 0.;
    double y = 0.;
    double angle = 0.; // en radians
    double norme = 0.;
};

class Cercle {
public:
    Cercle(S2d centre, double rayon);

    // Getters and setters
    S2d get_centre() const;
    double get_rayon() const;
    void set_centre(S2d centre);
    void set_rayon(double rayon);

    static bool epsil;
    static void epsilTrue();
    static void epsilFalse();
    static bool get_epsil();

    static bool inclusion(const Cercle &c1, const Cercle &c2);
    static bool intrusion(const Cercle &c1, const Cercle &c2);
private:
    S2d centre = {0, 0};
    double rayon = 0.;
};

#endif // TOOLS_H
