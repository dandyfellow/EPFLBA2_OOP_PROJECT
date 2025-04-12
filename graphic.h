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
    CYAN
};
class Graphic{
public:
    static void draw_vecteur(const double& p1x, const double& p1y,const double& p2x, 
        const double& p2y, const double& width, Color color);
    static void draw_cercle(const double& px, const double& py, const double& r,
        const double& width, const bool& full, Color color);
};



#endif
