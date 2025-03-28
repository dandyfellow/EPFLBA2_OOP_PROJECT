#include <fstream>
#include <sstream> 
#include <vector>
#include <iostream>
#include <string>
#include <istream>

#include "message.h" //definitif
#include "tools.h" 
#include "chaine.h"
#include "constantes.h"

using namespace std;

std::vector<S2d> Chaine::chaine;
Mode Chaine::mode;


Chaine::Chaine(S2d racine) {chaine.push_back(racine);}

Chaine::Chaine(Mode mode) : mode(mode) {}

unsigned int Chaine::longeur_chaine() const {return chaine.size();}

bool Chaine::distance_points(unsigned int i) { //input the index of the point, compares with the one before it
    if(i == 0) { //check distance between point and edge of arena
        Vecteur v(chaine[i], {0, 0});
        if(r_max - v.get_norme() <= r_capture){
            cout << message::chaine_racine(get_point(i).x, get_point(i).y) << endl;
            return false;
        }
        return true;
    }

    Vecteur v(chaine[i], chaine[i-1]);
    if(v.get_norme() <= r_capture){
        cout << message::chaine_max_distance(i-1) << endl;
        return false;
    }
    return true;
}

S2d Chaine::get_point(unsigned int i) {return chaine[i];}



void Chaine::display() const {
    for (const auto& s : chaine){
        cout << s.x << " " << s.y << endl;
    }
}
//---------------------------------------------------------------------------------------------------
bool lecture_c(istringstream& data){
    double x, y;
    data >> x >> y;
    Chaine c({x,y});
    if(c.distance_points(c.longeur_chaine()-1) == false) {
        //message d'erreur gérer dans distance points

        //Actually, I can change distance_point to check only with the
    // the distance between the newly created point and the previous one
    // not check everyone.
        return false;
    }
    return true;
}

bool lecture_c_mode(istringstream& data){
    string mot = "";
    if(data >> mot){
        if(mot == "CONSTRUCTION") {Chaine c(CONSTRUCTION);}
        else if(mot == "GUIDAGE") {Chaine c(GUIDAGE);}
        else {return false;}
        cout << "mode: " << mot << endl; //remove later, just for testing
        return true;
    }
    return false;   
}