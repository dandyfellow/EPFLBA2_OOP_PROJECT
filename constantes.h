#ifndef CONSTANTES_H
#define CONSTANTES_H

// nécessaire pour utiliser epsil_zero et disposer des symboles de graphic.h
#include "tools.h" 
enum Mode
{
    CONSTRUCTION,
    GUIDAGE
};
constexpr double r_max(100.);
constexpr double r_min_faiseur(1.5);
constexpr double r_max_faiseur(5.);
constexpr double r_capture(18.);
constexpr double r_viz(0.9); // seulement pour le dessin

// déplacement max par mise à jour du jeu
constexpr double d_max(r_max / 40.);
constexpr unsigned time_to_split(500);
constexpr unsigned nb_particule_max(50);
constexpr double delta_split(0.5); // radian
constexpr double coef_split(0.8);
constexpr unsigned score_max(8000);

#endif