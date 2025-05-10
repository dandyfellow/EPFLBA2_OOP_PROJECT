//mobile.cc, Adam Coste et Max Ciriani, version 1
#ifndef CHAINE_H
#define CHAINE_H

#include <fstream>
#include <sstream> 
#include <vector>
#include <iostream>
#include <string>
#include <istream>

#include "message.h" //definitif
#include "tools.h" 
#include "constantes.h"

using namespace std;

bool lecture_c(istringstream& data);
bool lecture_c_mode(istringstream& data);

void creation_but_final(S2d but_final);

class Chaine{
public:
    Chaine(S2d racine);
    Chaine(Mode mode);
    Chaine(Cercle cercle);
    static vector<pair<int, Cercle>> get_chaine();
    static pair<int, Cercle> get_chaine(unsigned int i);
    static unsigned int get_longueur_chaine();
    static void display(); // for TESTING purpouses
    static Mode get_mode() { return mode; }
    static void reset(); //clears chain and sets guidage to CONSTRUCTION
    static void set_mode(Mode m);

    static Cercle get_but_final() { return but_final; }
    static void set_but_final(Cercle but) { but_final = but; }
    static S2d get_mouse_pos() { return mouse_pos; }
    static void set_mouse_pos(double x, double y) {Chaine::mouse_pos = {x,y};}

    static void algo_move_chaine();
    static void set_chaine(unsigned int i, Cercle c);

private:
    static vector<pair<int, Cercle>> chaine;
    static Mode mode;
    static Cercle but_final;
    static S2d mouse_pos;
};

#endif