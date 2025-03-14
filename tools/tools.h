#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
constexpr double epsil_zero = 0.5;

struct S2d {
    double x = 0.;
    double y = 0.;
};

struct Vecteur {
    double x = 0.;
    double y = 0.;
    double angle = 0.;  // Angle in radians
    double norme = 0.;  // Magnitude (length)

    // Constructor to create a vector from two points
    Vecteur(const S2d& p1, const S2d& p2) 
        : x(p2.x - p1.x), y(p2.y - p1.y) {
        angle = atan2(y, x);
        norme = sqrt(x * x + y * y);
    }

    // Constructor to create a vector from an origin, angle, and magnitude
    Vecteur(const S2d& p, double angle, double norme) 
        : angle(angle), norme(norme) {
        x = norme * cos(angle);
        y = norme * sin(angle);
    }
};
struct Cercle {
    Cercle(S2d centre, double rayon) : centre(centre), rayon(rayon) {}
    S2d centre;
    double rayon;
};
bool intersection(const Cercle& c1, const Cercle& c2, bool epsil);
bool inclusion(const Cercle& c1, const Cercle& c2, bool epsil);
Vecteur reflechis(Vecteur incident, S2d point);

#endif 
