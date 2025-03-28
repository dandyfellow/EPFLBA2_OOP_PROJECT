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

class Chaine {
    public:
        Chaine(S2d racine);
        Chaine(Mode mode);
        unsigned int longeur_chaine() const;
        void display() const;
        
        static S2d get_point(unsigned int i);
        static bool distance_points(unsigned int i);
        

    private:
        static std::vector<S2d> chaine;
        static Mode mode;
};

bool lecture_c(istringstream& data);
bool lecture_c_mode(istringstream& data);

#endif