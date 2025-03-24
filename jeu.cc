#include <iostream>
#include <fstream>
#include <sstream> //for istringstream
#include <vector>

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"
#include "jeu.h"  

using namespace std;

enum Etat {SCORE, NB_PARTICULE, PARTICULE, NB_FAISEUR, FAISEUR, NB_CHAINE, CHAINE, CHAINE_MODE, FIN};
enum Chaine_mode {CONSTRUCTION, GUIDAGE};
static vector<Faiseur>   tFaiseur;
static vector<Particule> tParticule;
static vector<Chaine>    tChaine;

static unsigned int score = 0;
static unsigned int nb_particule = 0;
static unsigned int nb_faiseur = 0;
static unsigned int nb_chaine = 0;

static Etat etat = SCORE;
static Chaine_mode mode;

//PROTOTYPES -----------------------------------------------------------------
bool imprimer_data(istringstream& data);
void reset();
bool decodage_ligne(istringstream& data);
bool decodage_score(istringstream& data);
bool decodage_nb_particule(istringstream& data);
bool decodage_particule(istringstream& data);
bool decodage_nb_faiseur(istringstream& data);
bool decodage_faiseur(istringstream& data);
bool decodage_nb_chaine(istringstream& data);
bool decodage_chaine(istringstream& data);
bool decodage_chaine_mode(istringstream& data);

//END OF PROTOTYPES -----------------------------------------------------------

void reset(){
	score = 0;
	tFaiseur = {};
	tParticule = {};
	tChaine = {};
}

bool imprimer_data(istringstream& data)
{
	string txt = "";
	string mot;
	while(data >> mot) {
		cout << mot << txt;
	}
	cout << endl;
	return true;
}

void Jeu::success(){
	cout << message::success();
}

bool Jeu::lecture(string nom_fichier){
	//return true;
	reset();
	ifstream fichier(nom_fichier); //opens the file (ifstream = input file stream)
    if(!fichier.fail()) {
		string line;
        // l’appel de getline filtre aussi les séparateurs
        while(getline(fichier >> ws,line)) {
	//getline(): It reads an entire line of text from an input stream (is) and stores
	// it into the string (str), up to the newline character (\n), without including it.
	//ws: whitespace
		
			if(line[0]=='#')  continue;  
			istringstream data(line);
			if(decodage_ligne(data) == false) return false; //detection d'erreur simple
			//imprimer_data(data);
		}
		fichier.close();
        cout << "fin de la lecture du fichier ligne par ligne " << endl;
        return true;
	}
	cout << "erreur lors de l'ouverture du fichier" << endl;
	return false;
}



//			/*
bool decodage_ligne(istringstream& data) {
	switch(etat) 
	{
	case SCORE: // lecture du nombre de livreurs
		if(decodage_score(data)== false) return false;
	    break;

	case NB_PARTICULE: // ajout dans le vector en cas de succès
		if(decodage_nb_particule(data)== false) return false;
	    break;

	case PARTICULE: // lecture du nombre de véhicules
		if(decodage_particule(data)== false) return false;
	    break;

	case NB_FAISEUR: 
		if(decodage_nb_faiseur(data)== false) return false;
	    break;

	case FAISEUR: 
		if(decodage_faiseur(data)== false) return false;
	    break;

	case NB_CHAINE: 
		if(decodage_nb_chaine(data)== false) return false;
	    break;

	case CHAINE: 
		if(decodage_chaine(data)== false) return false;
	    break;

	case CHAINE_MODE:
		if(decodage_chaine_mode(data)== false) return false;
	    break;
/*
	case FIN: erreur(LECTURE_FIN) ; //techniquement inutile car on ne va jamais traiter FIN vu que la fonction lecture s'arrete avant
		return false;
		*/
	}
	return true;	
}
//			*/

bool decodage_score(istringstream& data){
	if(data >> score){
		cout << "score: " << score << endl; //remove later, just for testing
		return true;
	}
	return false;
}

bool decodage_nb_particule(istringstream& data) {
	if(data >> nb_particule){
		if(nb_particule == 0) {etat = NB_FAISEUR;}
		else {etat = PARTICULE;}
		cout << "nb particules: " << nb_particule << endl; //remove later, just for testing
		return true;
	}
	return false;
}
bool decodage_particule(istringstream& data) {
	for(unsigned int i(0); i < nb_particule; i++){
		Particule p;
		if(p.lecture(data) == false) {return false;}
		else {
			tParticule.push_back(p);
		}
		/*
		double x;
		double y;
		double angle;
		double deplacement;
		double compteur;
		data >> x;
		data >> y;
		data >> angle;
		data >> deplacement;
		data >> compteur;
		//creer une fonction lecture pour chaque type de mobile?
		//p(x, y, angle, deplacement, compteur);
		tParticule.push_back(p);
		*/
	}
	etat = NB_FAISEUR;
	return true;
}
bool decodage_nb_faiseur(istringstream& data) {
	if(data >> nb_faiseur){
		if(nb_faiseur == 0) {etat = NB_CHAINE;}
		else {etat = FAISEUR;}
		cout << "nb faiseur: " << nb_faiseur << endl; //remove later, just for testing
		return true;
	}
	return false;
}

bool decodage_faiseur(istringstream& data) {
	for(unsigned int i(0); i < nb_faiseur; i++){
		Faiseur f;
		if(f.lecture(data) == false) {return false;}
		else {
			tFaiseur.push_back(f);
		}
	}
	etat = NB_CHAINE;
	return true;
}
bool decodage_nb_chaine(istringstream& data) {
	if(data >> nb_chaine){
		if(nb_chaine == 0) {etat = CHAINE_MODE;}
		else {etat = CHAINE;}
		cout << "nb chaine: " << nb_chaine << endl; //remove later, just for testing
		return true;
	}
	return false;
}
bool decodage_chaine(istringstream& data) {
	for(unsigned int i(0); i < nb_chaine; i++){
		Chaine c;
		if(c.lecture(data) == false) {return false;}
		else {
			tChaine.push_back(c);
		}
	}
	etat = CHAINE_MODE;
	return true;
}
bool decodage_chaine_mode(istringstream& data) {
	etat = FIN;
	string mot;
	if(data >> mot){
		if(mot == "CONSTRUCTION") {mode = CONSTRUCTION;}
		else if(mot == "GUIDAGE") {mode = GUIDAGE;}
		else {return false;}
		cout << "mode: " << mot << endl; //remove later, just for testing
		return true;
	}
	return false;
}
/*
if(une détection d’erreur est vraie)
{
cout << message::appel_de_la_fonction(paramètres éventuels);
 std ::exit(EXIT_FAILURE) ; // Rendu1
} 

*/








