#include <cmath>
#include <iostream>
#include <cstdlib>
#include "tools.h"

using namespace std;

constexpr double epsil_zero = 0.5;
static bool epsil = false;

Vecteur::Vecteur(const S2d &p1, const S2d &p2)
    : x(p2.x - p1.x), y(p2.y - p1.y)
{
    angle = atan2(y, x);
    norme = sqrt(x * x + y * y);
}

Vecteur::Vecteur(const S2d &p, const double &angle, const double &norme)
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
    Vecteur reflechis(point, (M_PI + 2 * v_centre.get_angle() - this->get_angle()), this->get_norme());
    return reflechis;
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
        cerr << "rayon negatif, tools.cc " << __LINE__ << endl;
        exit(EXIT_FAILURE);
    }
}

// Getters and setters
S2d Cercle::get_centre() const { return centre; }
double Cercle::get_rayon() const { return rayon; }
void Cercle::set_centre(S2d new_centre) { this->centre = new_centre; }
void Cercle::set_rayon(double new_rayon) { this->rayon = new_rayon; }

bool inclusion(const Cercle &c1, const Cercle &c2)
{
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() - c2.get_rayon() - epsil_zero * epsil));
}

bool intrusion(const Cercle &c1, const Cercle &c2)
{
    Vecteur v1(c2.get_centre(), c1.get_centre());
    double distance = v1.get_norme();
    return (distance < (c1.get_rayon() + c2.get_rayon() + epsil_zero * epsil));
}

void epsilTrue()
{
    epsil = true;
}

void epsilFalse()
{
    epsil = false;
}

int main() {
    // Test Vecteur class
    S2d p1 = {0, 0};
    S2d p2 = {3, 4};
    Vecteur v1(p1, p2);

    assert(fabs(v1.get_x() - 3.0) < 1e-9);
    assert(fabs(v1.get_y() - 4.0) < 1e-9);
    assert(fabs(v1.get_norme() - 5.0) < 1e-9);

    // Test Cercle class
    Cercle c1(p1, 5);
    Cercle c2(p2, 2);

    assert(fabs(c1.get_rayon() - 5.0) < 1e-9);
    assert(fabs(c2.get_rayon() - 2.0) < 1e-9);

    // Test inclusion and intrusion
    epsilTrue();
    assert(inclusion(c1, c2) == false);
    assert(intrusion(c1, c2) == true);

    epsilFalse();
    assert(inclusion(c1, c2) == false);
    assert(intrusion(c1, c2) == true);

    cout << "All tests passed!" << endl;
    return 0;
}
