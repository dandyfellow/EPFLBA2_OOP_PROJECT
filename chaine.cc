#include <fstream>
#include <sstream> 
#include <vector>
#include <iostream>
#include <string>

#include "message.h" //definitif
#include "tools.h" 
#include "chaine.h"


class Chaine {
    public:
        enum Chaine_mode {CONSTRUCTION, GUIDAGE};

        Chaine(S2d racine) {chaine.push_back(racine);}
        unsigned int longeur_chaine() const {return chaine.size();}


        bool lecture_c(istringstream& data){
            double x, y;
            data >> x >> y;
            chaine.push_back({x, y});
            return true;
            // MISING VALUE CHECKING !!!!!!!!!!!!!!!!!!!!!!
        }
        bool lecture_c_mode(istringstream& data){
            string mot;
            data >> mot;
            if(data >> mot){
                if(mot == "CONSTRUCTION") {mode = CONSTRUCTION;}
                else if(mot == "GUIDAGE") {mode = GUIDAGE;}
                else {return false;}
                cout << "mode: " << mot << endl; //remove later, just for testing
                return true;
            }
            return false;   
        }

    private:
        vector<S2d> chaine;
        Chaine_mode mode;
        



};