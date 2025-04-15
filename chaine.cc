//chaine.cc, Adam Coste et Max Ciriani, version 1
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

std::vector<pair<int, Cercle>> Chaine::chaine;
Mode Chaine::mode;

bool lecture_c(istringstream& data){
    double x, y;
    data >> x >> y;
    Cercle arene({0,0}, r_max);
    Cercle cercle({x,y}, 0);
    if(!Cercle::intrusion(arene, cercle)){ //condition verified if no intrusion
        cout << message::articulation_outside(x, y);
        return false;
    }
    Chaine c({x,y});
    if (c.longeur_chaine() == 1) { //first chain
        Vecteur v({x, y}, {0, 0});
        if(!(r_max - v.get_norme() <= r_capture)){
            cout << message::chaine_racine(x, y);
            return false;
        }
        return true;
    } 
   
    Vecteur v(c.get_chaine(c.longeur_chaine()-2).second.get_centre(),
              c.get_chaine(c.longeur_chaine()-1).second.get_centre());

    if(!(v.get_norme() <= r_capture)){ 
        cout << message::chaine_max_distance(c.longeur_chaine()-2);
        return false;
    }
    return true;
}

bool lecture_c_mode(istringstream& data){
    string mot = "";
    if(data >> mot){
       
        if(mot == "CONSTRUCTION") {Chaine c(CONSTRUCTION);}
        else if(mot == "GUIDAGE") {Chaine c(GUIDAGE);}
        else {
            return false;
        }
        return true;
    }
    return false;   
}

//Chaine
Chaine::Chaine(S2d p) {
    int index = longeur_chaine();
    Cercle c(p, 0);
    pair<int, Cercle> pair = {index, c};

    chaine.push_back(pair);
}
Chaine::Chaine(Cercle c) {
    int index = longeur_chaine();
    pair<int, Cercle> p = {index, c};
    chaine.push_back(p);
}

Chaine::Chaine(Mode m) {mode = m;}

vector<pair<int, Cercle>> Chaine::get_chaine() {return chaine;} //static

pair<int, Cercle> Chaine::get_chaine(unsigned int i) {return chaine[i];}; //static

unsigned int Chaine::longeur_chaine() const {return chaine.size();}

void Chaine::set_mode(Mode m){
    mode = m;
};

void Chaine::display() { //for TESTING purpouses
    cout << "-------- Displaying chaine --------\n";
    for(const auto& a : chaine){
        cout << "index: " << a.first << " x: " << a.second.get_centre().x << " y: " 
             << a.second.get_centre().y << endl;
    }
}

void Chaine::reset(){
    chaine.clear();
    mode = CONSTRUCTION;
}