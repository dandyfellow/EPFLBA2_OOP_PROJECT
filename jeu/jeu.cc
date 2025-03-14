#include <iostream>
#include <fstream>

using namespace std;


void lecture() {
  // Lecture du fichier
  ifstream fichier("jeu/jeu.txt");
  if (fichier) {
    string ligne;
    while (getline(fichier, ligne)) {
      cout << ligne << endl;
    }
  } else {
    cout << "Impossible d'ouvrir le fichier !" << endl;
  }
}