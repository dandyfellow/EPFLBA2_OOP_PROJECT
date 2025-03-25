#include <fstream>
#include <sstream> 
#include <vector>
#include <iostream>
#include <string>

#include "message.h" //definitif
#include "tools.h" 
#include "chaine.h"

using namespace std;



class Chaine {
    public:
        enum Chaine_mode {CONSTRUCTION, GUIDAGE};

        Chaine(S2d racine) {chaine.push_back(racine);}
        unsigned int longeur_chaine() const {return chaine.size();}

        bool distance_points(unsigned int i){
            Vecteur v(chaine[i], chaine[i+1]);
            if(v.get_norme() <  ){
                cout << message::chaine_distance(v.get_norme()) << endl;
                return false;
            }
        }
        
        bool lecture_c(istringstream& data){
            double x, y;
            data >> x >> y;
            chaine.push_back({x, y});
            return true;
            // MISING VALUE CHECKING !!!!!!!!!!!!!!!!!!!!!!
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
        Chaine_mode mode;
};