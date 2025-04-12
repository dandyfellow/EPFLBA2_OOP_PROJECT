#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color
{
    WHITE,
    GREY,
    BLACK,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    PURPLE,
    CYAN,
    NO_COLOR //for no color / empty
};
class Graphic{
public:
    static void draw_vecteur(const double& p1x, const double& p1y,const double& p2x, 
        const double& p2y, const double& width, const Color& color);
    static void draw_cercle(const double& px, const double& py, const double& r,
        const double& width, const Color& c1, const Color& c2);
    //c1 is the inside color, c2 is the outside color
};



#endif
