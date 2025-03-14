void lecture() {
  // Lecture du fichier
  ifstream fichier("jeu/jeu.txt");
  if (fichier) {
    string ligne;
    while (getline(fichier, ligne)) {
      cout << ligne << endl;
    }
  } else {
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  }
}