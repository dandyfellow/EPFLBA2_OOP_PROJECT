#include <cmath>
#include <iostream>
#include "graphic_gui.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context> *ptcr(nullptr);

// local prototypes
static void set_color(Color color);
// graphic_gui.h
void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr)
{
    ptcr = &cr;
}
// à compléter pour effectuer des dessins élémentaires: trait, cercle, ...


// local function
static void set_color(Color color)
{
    double r(0.), g(0.), b(0.);
    switch (color)
    {
    case WHITE:
        r = g = b = 1;
        break;
    case GREY:
        r = g = b = 0.5;
        break;
    case BLACK:
        r = g = b = 0.;
        break;
    case RED:
        r = 1;
        break;
    case GREEN:
        g = 0.65;
        break;
    case BLUE:
        r = g = 0.65;
        b = 1;
        break;
    case ORANGE:
        r = 1;
        g = 0.65;
        break;
    case PURPLE:
        r = b = 0.65;
        break;
    case CYAN:
        g = b = 1;
        break;
    }
    (*ptcr)->set_source_rgb(r, g, b);
}
