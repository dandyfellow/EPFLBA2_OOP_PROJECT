#ifndef CHAINE_H
#define CHAINE_H

#include "message.h" //definitif
#include "tools.h" 
#include "constantes.h"


class Chaine {
    public:
        Chaine(S2d racine);
        unsigned int longeur_chaine() const;
        bool distance_points(unsigned int i) const;
        S2d get_point(unsigned int i) const;
        bool lecture_c(istringstream& data){
        bool lecture_c_mode(istringstream& data);
        void display() const;

    private:
        static vector<S2d> chaine;
        static Mode mode;
};

#endif