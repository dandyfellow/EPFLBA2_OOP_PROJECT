//graphic.cc, Adam Coste et Max Ciriani, version 1, 95% Max/5% Adam
#define _USE_MATH_DEFINES //pour cmath constantes -> NEEDS TO COME BEFORE CMATH

#include <cmath>
#include <iostream>
#include "graphic_gui.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

// local prototypes
static void set_color(Color color);
// graphic_gui.h

//grabs the cr pointer in gui.cc and stores it in a static variable to be used
//in the drawing functions
void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
    ptcr = &cr;
}
// à compléter pour effectuer des dessins élémentaires: trait, cercle, ...
//=====================================================================================
void Graphic::draw_vecteur(const double& p1x, const double& p1y,const double& p2x, 
                           const double& p2y, const double& width, const Color& color){
    if(color == NO_COLOR) {
        cout << "Graphic::draw_vecteur: color is NO_COLOR -> incorrect" << endl;
    }
    set_color(color);
    
    (*ptcr)->set_line_width(width);

    (*ptcr)->move_to(p1x, p1y);
    (*ptcr)->line_to(p2x, p2y);
    (*ptcr)->stroke();
}

void Graphic::draw_cercle(const double& px, const double& py, const double& r,
                          const double& width, const Color& c1, const Color& c2){
    if(c1 != NO_COLOR and c2 != NO_COLOR) {
        set_color(c2);
        (*ptcr)->set_line_width(width); 
    
        (*ptcr)->save();
        (*ptcr)->arc(px, py, r, 0, 2 * M_PI); // draw circle
        set_color(c1);
        (*ptcr)->fill_preserve();
        (*ptcr)->restore();
    
        (*ptcr)->stroke();
    }
    if(c1 == NO_COLOR and c2 != NO_COLOR) { // outside circle only
        set_color(c2);
        (*ptcr)->set_line_width(width); 
        (*ptcr)->arc(px, py, r, 0, 2 * M_PI); // draw circle     
        (*ptcr)->stroke();
    }
    if(c1 != NO_COLOR and c2 == NO_COLOR) { // inside circle -> fill
        set_color(c1);
        (*ptcr)->set_line_width(width); 
        (*ptcr)->arc(px, py, r, 0, 2 * M_PI); // draw circle
    }
}

//=====================================================================================

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
    case NO_COLOR:
        r = g = b = 1; //white so that it doesn't crash
        cout << "Function set_color(Color c) used badly! Do not set color"; 
        cout << "to NO_COLOR! (Set the color to white by default)" << endl;
        break;
    }
    (*ptcr)->set_source_rgb(r, g, b);
}
