#ifndef JEU_H
#define JEU_H

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"

#include <string> 


class Jeu {
public:
    bool lecture(std::string nom_fichier);
    void success();
};




#endif