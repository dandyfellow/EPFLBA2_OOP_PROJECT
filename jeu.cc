#include <iostream>
#include <fstream>

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"
#include "jeu.h"  

using namespace std;

void lecture()
{

  // Lecture du fichier
  ifstream fichier("jeu/jeu.txt");
  if (fichier)
  {
    string ligne;
    while (getline(fichier, ligne))
    {
      cout << ligne << endl;
    }
  }
  else
  {
    cout << "Impossible d'ouvrir le fichier !" << endl;
  }
}