#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "jeu.h" //definitif
#include "tools.h" //ENLEVER QUAND PLUS NECESSAIRE

using namespace std;


int main() {
  
    cout << "Hello, World!" << std::endl;
    //testing
    S2d p1;
    S2d p2;
    p2.x = 1;
    p2.y = 1;
    S2d p3 = {4, 4};
    cout << "p1: " << p1.x << " " << p1.y << endl;
    cout << "p2: " << p2.x << " " << p2.y << endl;
    double norme = 2;
    double angle = M_PI/4;
    Vecteur v1(p1, p2);
    Vecteur v2(p1, norme, angle);
    Vecteur v3;
    cout << "v1: " << v1.get_x() << " " << v1.get_y() << " " << v1.get_angle() << " " << v1.get_norme() << endl;
    cout << "v2: " << v2.get_x() << " " << v2.get_y() << " " << v2.get_angle() << " " << v2.get_norme() << endl;
    cout << "v3: " << v3.get_x() << " " << v3.get_y() << " " << v3.get_angle() << " " << v3.get_norme() << endl;
    //Vecteur v4(p3, -4, M_PI); //norme negative : CA MARCHE
    Vecteur v_reflechis = v1.reflechis(p3);
    cout << "v_reflechis " << v_reflechis.get_x() << " " << v_reflechis.get_y() << " " << v_reflechis.get_angle() << " " << v_reflechis.get_norme() << endl;
    
   

    
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

    
    




    return 0;
}
