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


/*
    auto app = Gtk::Application::create();
    return app->make_window_and_run<My_window>(1, argv, file_name);
*/

int main(int argc, char * argv[]) {
    if(argc != 2) {
        exit(EXIT_FAILURE);
    }
    string nom_fichier = argv[1];
    Jeu jeu;

    Cercle::epsilFalse(); //desactive l'epsil pour les tests
    if(!jeu.lecture(nom_fichier)) {
        //les messages d'erreurs sont gérées dans les fonctions lectures
        //exit(EXIT_FAILURE); RENDU 1
        //effacer les donnees est gereer dans la fonction Jeu::lecture();
    }
    jeu.success();
    jeu.set_lecture_success(true);
    Cercle::epsilTrue(); //active epsil pour le reste de jeu

    // ----------------------------- SPACE FOR TESTING -----------------------------
    if(false) { 
        Chaine::display();
        Faiseur::display();
        Particule::display();
    }
    // ----------------------------- END OF TESTING -----------------------------
    
    auto app = Gtk::Application::create();
    return app->make_window_and_run<My_window>(1, argv, nom_fichier);

    exit(EXIT_SUCCESS);


//---------------------------------------------------------------------------------------------------------------------
//          SEPARATION ENTRE LES TESTS ET LE CODE FINAL	
//---------------------------------------------------------------------------------------------------------------------

    return 0;
}
