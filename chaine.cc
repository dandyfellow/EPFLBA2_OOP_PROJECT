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
Cercle Chaine::but_final= {{0,0}, 0};
S2d Chaine::mouse_pos = {0,0};

bool lecture_c(istringstream& data){
    double x, y;
    data >> x >> y;
    Cercle arene({0,0}, r_max);
    Cercle cercle({x,y}, 0);

    static bool first = true;
    if(first){
        creation_but_final({x,y});
        first = false;
    }

    if(!Cercle::intrusion(arene, cercle)){ //condition verified if no intrusion
        cout << message::articulation_outside(x, y);
        return false;
    }
    Chaine c({x,y});
    if (Chaine::get_longueur_chaine() == 1) { //first chain
        Vecteur v({x, y}, {0, 0});
        if(!(r_max - v.get_norme() <= r_capture)){
            cout << message::chaine_racine(x, y);
            return false;
        }
        return true;
    } 
   
    Vecteur v(c.get_chaine(Chaine::get_longueur_chaine()-2).second.get_centre(),
              c.get_chaine(Chaine::get_longueur_chaine()-1).second.get_centre());

    if(!(v.get_norme() <= r_capture)){ 
        cout << message::chaine_max_distance(Chaine::get_longueur_chaine()-2);
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
    int index = Chaine::get_longueur_chaine();
    Cercle c(p, 0);
    pair<int, Cercle> pair = {index, c};

    chaine.push_back(pair);
}
Chaine::Chaine(Cercle c) {
    int index = Chaine::get_longueur_chaine();
    pair<int, Cercle> p = {index, c};
    chaine.push_back(p);
}

Chaine::Chaine(Mode m) {mode = m;}

vector<pair<int, Cercle>> Chaine::get_chaine() {return chaine;} //static

pair<int, Cercle> Chaine::get_chaine(unsigned int i) {return chaine[i];}; //static

void Chaine::set_mode(Mode m){
    mode = m;
};

void Chaine::display() { //for TESTING purpouses
    cout <<  "INFO CHAINE:";
    for(const auto& a : chaine){
        cout << "(" << a.first << ", {" << a.second.get_centre().x << "," 
             << a.second.get_centre().y << "}) ";
    }
    cout << " MODE: ";
    if(mode == CONSTRUCTION) cout << "CONSTRUCTION";
    if(mode == GUIDAGE) cout << "GUIDAGE";
    cout << endl;
}

void Chaine::reset(){
    chaine.clear();
    mode = CONSTRUCTION;
}


unsigned int Chaine::get_longueur_chaine() {
    if(chaine.size() == 0) {
        //cout << "Chaine length is 0, beware of doing get_longueur_chaine() -1 !!!\n";
    }
    return chaine.size();
}

void creation_but_final(S2d position){
    Vecteur centre({position.x,position.y}, {0,0});
    Vecteur final({0,0}, r_max, centre.get_angle());
    Cercle but_final = {final.get_p2(), r_viz};
    Chaine::set_but_final(but_final);
}

void Chaine::algo_move_chaine(){
    vector<pair<int, Cercle>> chaine_copy = chaine;
    int chaine_size = get_longueur_chaine()-1;
    if(chaine_size == -1 or chaine_size == 0) return; 
    Vecteur v_mouse_pos(chaine[chaine_size].second.get_centre(), mouse_pos);
    S2d but_inter = mouse_pos; //but intermediaire
    if(v_mouse_pos.get_norme() > r_capture){
        Vecteur v_but_inter(chaine[chaine_size].second.get_centre(),r_capture, 
        v_mouse_pos.get_angle());
        but_inter = v_but_inter.get_p2();
    } 
    S2d racine_pos = get_chaine(0).second.get_centre();
    std::vector<double> t_lk(chaine_size+1); //dans l'ordre de la racine -> effecteur
    for(unsigned int i = 0; i < chaine_size; i++){
        Vecteur v_lk(chaine_copy[i].second.get_centre(), 
        chaine_copy[i+1].second.get_centre());
        t_lk[i] = v_lk.get_norme();
    }
    for(unsigned int i = chaine_size; i > 0; i--){
        Vecteur v_pour_angle(but_inter, chaine_copy[i-1].second.get_centre());
        Vecteur v_pkprime_pk(but_inter, t_lk[i-1], v_pour_angle.get_angle());
        chaine_copy[i].second = {but_inter, 0};
        but_inter = v_pkprime_pk.get_p2();
        if(i == 1) chaine_copy[0].second = {but_inter, 0};
    }
    but_inter = racine_pos;  //racine vers effecteur
    for(unsigned int i(0); i < chaine_size; i++){        
        Vecteur v_pour_angle(but_inter, chaine_copy[i+1].second.get_centre());
        Vecteur v_pkprime_pk(but_inter, t_lk[i], v_pour_angle.get_angle());
        chaine_copy[i].second = {but_inter, 0};
        but_inter = v_pkprime_pk.get_p2();
        if(i == chaine_size-1) chaine_copy[chaine_size].second = {but_inter, 0};
    }
    for(auto& art : chaine_copy){
        if(!Cercle::inclusion(Cercle({0,0}, r_max), art.second)) { 
            cout << "ARTICULATION NOT IN ARENE" << endl;
            return;
        }  
    }
    chaine = chaine_copy;
}

void Chaine::set_chaine(unsigned int i, Cercle c){
    chaine[i] = {i, c};
}