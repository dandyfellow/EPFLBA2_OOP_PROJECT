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

class Chaine{
public:
    Chaine(S2d racine);
    Chaine(Mode mode);
    Chaine(Cercle cercle);
    static vector<pair<int, Cercle>> get_chaine();
    static pair<int, Cercle> get_chaine(unsigned int i);
    unsigned int longeur_chaine() const;
    static void display(); // for TESTING purpouses
    static Mode get_mode() { return mode; }
    static void clear_chaine(); //clears chain and sets guidage to CONSTRUCTION

private:
    static vector<pair<int, Cercle>> chaine;
    static Mode mode;
};

#endif