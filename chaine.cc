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

Chaine::Chaine(Mode m) {mode = m;}

unsigned int Chaine::longeur_chaine() const {return chaine.size();}

bool Chaine::distance_points(unsigned int i) { //input the index of the point, compares with the one before it
    if(i == 0) { //check distance between point and edge of arena
        Vecteur v(chaine[i], {0, 0});
        if(r_max - v.get_norme() <= r_capture){
            cout << message::articulation_outside(get_point(i).x, get_point(i).y);
            return false;
        }
        return true;
    }

    Vecteur v(chaine[i], chaine[i-1]);
    if(v.get_norme() <= r_capture){
        cout << message::chaine_max_distance(i-1);
        return false;
    }
    return true;
}

S2d Chaine::get_point(unsigned int i) {return chaine[i];}



void Chaine::display() const {
    cout << "mode: " << mode << endl;
    for (const auto& s : chaine){
        cout << s.x << " " << s.y << endl;
    }
}
//---------------------------------------------------------------------------------------------------
bool lecture_c(istringstream& data){
    double x, y;
    data >> x >> y;
    Chaine c({x,y});
    if(c.distance_points(c.longeur_chaine()-1) == false) {return false;}
    return true;
}

bool lecture_c_mode(istringstream& data){
    string mot = "";
    if(data >> mot){
        if(mot == "CONSTRUCTION") {Chaine c(CONSTRUCTION);}
        else if(mot == "GUIDAGE") {Chaine c(GUIDAGE);}
        else {return false;}
        //cout << "mode: " << mot << endl; //remove later, just for testing
        return true;
    }
    return false;   
}