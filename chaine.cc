#include <fstream>
#include <sstream> 
#include <vector>
#include <iostream>
#include <string>

#include "message.h" //definitif
#include "tools.h" 
#include "chaine.h"
#include "constantes.h"

using namespace std;



class Chaine {
    public:
        //enum Chaine_mode {CONSTRUCTION, GUIDAGE};

        Chaine(S2d racine) {chaine.push_back(racine);}

        unsigned int longeur_chaine() const {return chaine.size();}

        bool distance_points(unsigned int i){ //input the index of the point, compares with the one before it
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
        S2d get_point(unsigned int i) const {return chaine[i];}
        bool lecture_c(istringstream& data){
            double x, y;
            data >> x >> y;
            chaine.push_back({x, y});
            if(distance_points(distance_points.size()-1) == false) {return false;}
            return true;
        }
        bool lecture_c_mode(istringstream& data){
            string mot = "";
            if(data >> mot){
                if(mot == "CONSTRUCTION") {mode = CONSTRUCTION;}
                else if(mot == "GUIDAGE") {mode = GUIDAGE;}
                else {return false;}
                cout << "mode: " << mode << endl; //remove later, just for testing
                return true;
            }
            return false;   
        }
        
        void display(){
            for (const auto& s : chaine){
                cout << s.x << " " << s.y << endl;
            }
        }

    private:
        static vector<S2d> chaine;
        Mode mode;
};