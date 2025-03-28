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

std::vector<Cercle> Chaine::chaine;
Mode Chaine::mode;


Chaine::Chaine(S2d p) {
    Cercle c(p, 0);
    chaine.push_back(c);
}
Chaine::Chaine(Cercle c) {
    chaine.push_back(c);
}

Chaine::Chaine(Mode m) {mode = m;}

std::vector<Cercle> Chaine::get_chaine() const {return chaine;}

Cercle Chaine::get_chaine(unsigned int i) const {return chaine[i];};

unsigned int Chaine::longeur_chaine() const {return chaine.size();}

void Chaine::display() const {
    
}
//---------------------------------------------------------------------------------------------------
bool lecture_c(istringstream& data){
    double x, y;
    data >> x >> y;

    //TESTING cout << "x:" << x << " y: " << y << endl;
    Cercle arene({0,0}, r_max);
    Cercle cercle({x,y}, 0);
    if(!Cercle::intrusion(arene, cercle)){ //condition verified if no intrusion
        //error, chaine outside arena
        cout << message::articulation_outside(x, y);
        return false;
    }
    Chaine c({x,y});

    //TESTING cout << "c.longeur_chaine(): " << c.longeur_chaine() << endl;

    if (c.longeur_chaine() == 1) { //first chain
        //TESTING cout << "test chaine = 0" << endl;
        Vecteur v({x, y}, {0, 0});
        if(!(r_max - v.get_norme() <= r_capture)){
            //TESTING cout << "Vector norm for comparing: "<< v.get_norme() << endl;
            //TESTING cout << "r_max - v.get_norme(): " << r_max - v.get_norme() << endl;
            cout << message::chaine_racine(x, y);
            return false;
        }
        return true;
    } 
    Vecteur v(c.get_chaine(c.longeur_chaine()-2).get_centre(), c.get_chaine(c.longeur_chaine()-1).get_centre());
    //cout << "Vector chaine i-1, i: norme " << v.get_norme() << " angle: " << v.get_angle() << endl;
    //TESTING cout << "v.get_norme() <= r_capture: " << (v.get_norme() <= r_capture) << endl;
    if(!(v.get_norme() <= r_capture)){ 
        cout << message::chaine_max_distance(c.longeur_chaine()-2);
        return false;}

        //TESTING cout << "---- test concluded ----\n";
    return true;
}

bool lecture_c_mode(istringstream& data){
    string mot = "";
    
    if(data >> mot){
        //cout << "mot:  " << mot << endl;
        if(mot == "CONSTRUCTION") {Chaine c(CONSTRUCTION);}
        else if(mot == "GUIDAGE") {Chaine c(GUIDAGE);}
        else {return false;}
        //TESTING cout << "mode: " << mot << endl; //remove later, just for testing
        return true;
    }
    return false;   
}