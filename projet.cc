#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

#include "jeu.h" //definitif
#include "tools.h" //ENLEVER QUAND PLUS NECESSAIRE

using namespace std;


int main(int argc, char * argv[]) {
    if(argc != 2) {
        //cerr << "Usage correct: ./projet nom_du_ficher.txt" << endl;
        exit(EXIT_FAILURE);
    }

    string nom_fichier = argv[1];
    Jeu jeu;

    if(!jeu.lecture(nom_fichier)) {
        //les messaages d'erreurs sont gérées dans les fonctions lectures
        exit(EXIT_FAILURE);
    }

    jeu.success();

    // ----------------------------- SPACE FOR TESTING -----------------------------
    if(false){
        Chaine::display();
        Faiseur::display();
    }
    // ----------------------------- END OF TESTING -----------------------------
    exit(EXIT_SUCCESS);


//---------------------------------------------------------------------------------------------------------------------
//          SEPARATION ENTRE LES TESTS ET LE CODE FINAL	
//---------------------------------------------------------------------------------------------------------------------
    
  /*
    cout << "Hello, World!" << std::endl;
    //testing
    S2d p1;
    S2d p2;
    p2.x = 1;
    p2.y = 1;
    S2d p3 = {4, 4};
    S2d p4 = {1, 2};
    S2d p5 = {-1, 1};
    cout << "p1: " << p1.x << " " << p1.y << endl;
    cout << "p2: " << p2.x << " " << p2.y << endl;
    double norme = 2;
    double angle = M_PI/4;
    Vecteur v1(p1, p2);
    Vecteur v2(p1, norme, angle);
    Vecteur v3;
    Vecteur v4({-1, 0}, 1, M_PI/2.0);
    cout << "v1: " << v1.get_x() << " " << v1.get_y() << " " << v1.get_angle() << " " << v1.get_norme() << endl;
    cout << "v2: " << v2.get_x() << " " << v2.get_y() << " " << v2.get_angle() << " " << v2.get_norme() << endl;
    cout << "v3: " << v3.get_x() << " " << v3.get_y() << " " << v3.get_angle() << " " << v3.get_norme() << endl;
    //Vecteur v4(p3, -4, M_PI); //norme negative : CA MARCHE
    Vecteur v_reflechis = v1.reflechis(p3);
    cout << "v_reflechis " << v_reflechis.get_x() << " " << v_reflechis.get_y() << " " << v_reflechis.get_angle() << " " << v_reflechis.get_norme() << endl;
    cout << "v_reflechis2 " << v2.reflechis(p3).get_x() << " " << v2.reflechis(p3).get_y() << " " << v2.reflechis(p3).get_angle() << " " << v2.reflechis(p3).get_norme() << endl;
    cout << "v_reflechis3 " << v3.reflechis(p4).get_x() << " " << v3.reflechis(p4).get_y() << " " << v3.reflechis(p4).get_angle() << " " << v3.reflechis(p4).get_norme() << endl;
    cout << "v_reflechis4 " << v2.reflechis(p4).get_x() << " " << v2.reflechis(p4).get_y() << " " << v2.reflechis(p4).get_angle() << " " << v2.reflechis(p4).get_norme() << endl;
    cout << "v_reflechis5 " << v1.reflechis(p5).get_x() << " " << v1.reflechis(p5).get_y() << " " << v1.reflechis(p5).get_angle() << " " << v1.reflechis(p5).get_norme() << endl;
    cout << "v_reflechis6 " << v4.reflechis(p5).get_x() << " " << v4.reflechis(p5).get_y() << " " << v4.reflechis(p5).get_angle() << " " << v4.reflechis(p5).get_norme() << endl;
    
    cout << "Testing angle normalisation" << endl;
    cout << "-8./4.M_PI: " << fmod(-8./4*M_PI, M_PI) << endl;
    cout << "-7./4.M_PI: " << fmod(-7./4*M_PI, M_PI) << endl;
    cout << "-6./4.M_PI: " << fmod(-6./4*M_PI, M_PI) << endl;
    cout << "-5./4.M_PI: " << fmod(-5./4*M_PI, M_PI) << endl;
    cout << "-4./4.M_PI: " << fmod(-4./4*M_PI, M_PI) << endl;
    cout << "-3./4.M_PI: " << fmod(-3./4*M_PI, M_PI) << endl;
    cout << "-2./4.M_PI: " << fmod(-2./4*M_PI, M_PI) << endl;
    cout << "-1./4.M_PI: " << fmod(-1./4*M_PI, M_PI) << endl;
    cout << "0./4.M_PI: " << fmod(0./4*M_PI, M_PI) << endl;
    cout << "1./4.M_PI: " << fmod(1./4*M_PI, M_PI) << endl;
    cout << "2./4.M_PI: " << fmod(2./4*M_PI, M_PI) << endl;
    cout << "3./4.M_PI: " << fmod(3./4*M_PI, M_PI) << endl;
    cout << "4./4.M_PI: " << fmod(4./4*M_PI, M_PI) << endl;
    cout << "5./4.M_PI: " << fmod(5./4*M_PI, M_PI) << endl;
    cout << "6./4.M_PI: " << fmod(6./4*M_PI, M_PI) << endl;
    cout << "7./4.M_PI: " << fmod(7./4*M_PI, M_PI) << endl;
    cout << "8./4.M_PI: " << fmod(8./4*M_PI, M_PI) << endl;

    //testing getters and setters
    cout << "Testing getters and setters" << endl;
    v1.set_x(1);
    v1.set_y(2);
    v1.set_angle(M_PI/2);
    v1.set_norme(3);
    cout << "v1: " << v1.get_x() << " " << v1.get_y() << " " << v1.get_angle() << " " << v1.get_norme() << endl;
    
    //testing Cercle
    cout << "Testing Cercle" << endl;
    S2d centre = {1, 1};
    Cercle c1(centre, 1);
    cout << "c1: " << c1.get_centre().x << " " << c1.get_centre().y << " " << c1.get_rayon() << endl;
    //S2d centre2 = {2, 2};
    //c1.set_centre(centre2);
    //c1.set_rayon(-2); -> fonctionne
    //cout << "c2: " << c1.get_centre().x << " " << c1.get_centre().y << " " << c1.get_rayon() << endl;
    //Cercle c3({1, 1}, -1); works
    //cout << "c3: " << c3.get_centre().x << " " << c3.get_centre().y << " " << c3.get_rayon() << endl;
    //testing epsil
    //bool Cercle::epsil;
    cout << "epsil: " << Cercle::epsil << endl;
    
    cout << "Testing epsil" << endl;
    Cercle::epsilTrue();
    cout << "epsil: " << Cercle::get_epsil() << endl;
    Cercle::epsilFalse();
    cout << "epsil: " << Cercle::get_epsil() << endl;

    
    cout << "Testing inclusion" << endl;
    Cercle c2({0, 0}, 1);
    Cercle c3({0, 0.25}, 0.25);
    cout << Cercle::inclusion(c1, c2) << endl;
    cout << Cercle::inclusion(c2, c3) << endl;
    cout << Cercle::inclusion(c1, c1) << endl;

    
    cout << "Testing intrusion" << endl;
    cout << Cercle::intrusion(c1, c2) << endl;
    cout << Cercle::intrusion(c1, c3) << endl;
    cout << Cercle::intrusion(c1, c1) << endl;

*/
    return 0;
}
