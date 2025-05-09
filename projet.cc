//projet.cc, Adam Coste et Max Ciriani, version 1
#define _USE_MATH_DEFINES

//#include <gtkmm/application.h>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

//#include "gui.h"
#include "jeu.h"
#include "gui.h"

using namespace std;

int main(int argc, char * argv[]) {
    if(argc != 2) {
        exit(EXIT_FAILURE);
    }
    string nom_fichier = argv[1];
   
    auto app = Gtk::Application::create();
    return app->make_window_and_run<My_window>(1, argv, nom_fichier);

    //Write the terminal log
    //just ./projet t23.txt > log.txt 2>&1
    // 2>&1 = Redirect standard error to the same place as standard output. 
    // (std error = 2)





    exit(EXIT_SUCCESS);
    return 0;
}
