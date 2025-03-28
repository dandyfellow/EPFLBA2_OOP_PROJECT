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

std::vector<S2d> Chaine::get_chaine() const {return chaine;}

unsigned int Chaine::longeur_chaine() const {return chaine.size();}

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
    if (c.longeur_chaine() == 1) { //first chain
        Vecteur v({x, y}, {0, 0});
        if(!(r_max - v.get_norme() <= r_capture)){
            //cout << "Vector norm for comparing: "<< v.get_norme() << endl;
            cout << message::chaine_racine(x, y);
            return false;
        }
        return true;
    } 
    Vecteur v(c.get_chaine()[c.longeur_chaine()-2], c.get_chaine()[c.longeur_chaine()-1]);
    //cout << "Vector chaine i-1, i: norme " << v.get_norme() << " angle: " << v.get_angle() << endl;
    if(!(v.get_norme() <= r_capture)){ 
        cout << message::chaine_max_distance(c.longeur_chaine()-2);
        return false;}
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