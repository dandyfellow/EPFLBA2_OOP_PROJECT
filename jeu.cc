#include <iostream>
#include <fstream>
#include <sstream> //for istringstream
#include <vector>

#include "chaine.h"
#include "mobile.h"
#include "message.h"
#include "tools.h"
#include "jeu.h"  
#include "constantes.h"

using namespace std;

unsigned int score = 0;
unsigned int nb_particule_init = 0;
unsigned int nb_faiseur_init = 0;
unsigned int nb_chaine_init = 0;

Etat etat = SCORE;


void Jeu::reset(){
	score = 0;
	nb_particule_init = 0;
	nb_faiseur_init = 0;
	nb_chaine_init = 0;
	etat = SCORE;
}

bool imprimer_data(istringstream& data) //this function is for testing purpouses only
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
	reset(); //resets the values to the default ones
	ifstream fichier(nom_fichier); //opens the file (ifstream = input file stream)
    if(!fichier.fail()) {
		string line;
        // l’appel de getline filtre aussi les séparateurs
        while(getline(fichier >> ws,line)) {

		
			if(line[0]=='#')  continue;  
			istringstream data(line);
			if(decodage_ligne(data) == false) return false; //detection d'erreur simple
			//imprimer_data(data); //testing
		}
		fichier.close();
        cout << "fin de la lecture du fichier ligne par ligne " << endl;
        return true;
	}
	cout << "erreur lors de l'ouverture du fichier" << endl;
	return false;
}




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

	case FIN: 
		break;
		
	}
	return true;	
}


bool decodage_score(istringstream& data){
	if(data >> score){
		if(score <= 0 or score > score_max) {
			message::score_outside(score);
			return false;
		}
		cout << "score: " << score << endl; //remove later, just for testing
		return true;
	}
	return false;
}

bool decodage_nb_particule(istringstream& data) {
	if(data >> nb_particule_init){
		if(nb_particule_init < 0 or nb_particule_init > nb_particule_max) {
			message::nb_particule_outside(nb_particule_init);
			return false;
		}
		if(nb_particule_init == 0) {etat = NB_FAISEUR;}
		else {etat = PARTICULE;}
		cout << "nb particules: " << nb_particule_init << endl; //remove later, just for testing
		return true;
	}
	return false;
}
bool decodage_particule(istringstream& data) {
	for(unsigned int i(0); i < nb_particule_init; i++){
		if(lecture_c(data) == false){return false;}
	}
	etat = NB_FAISEUR;
	return true;
}
bool decodage_nb_faiseur(istringstream& data) {
	if(data >> nb_faiseur_init){
		if(nb_faiseur_init == 0) {etat = NB_CHAINE;}
		else {etat = FAISEUR;}
		cout << "nb faiseur: " << nb_faiseur_init << endl; //remove later, just for testing
		return true;
	}
	return false;
}

bool decodage_faiseur(istringstream& data) {
	for(unsigned int i(0); i < nb_faiseur_init; i++){
		if(lecture_f(data) == false) {return false;}
	}
	etat = NB_CHAINE;
	return true;
}
bool decodage_nb_chaine(istringstream& data) {
	if(data >> nb_chaine_init){
		if(nb_chaine_init == 0) {etat = CHAINE_MODE;}
		else {etat = CHAINE;}
		cout << "nb chaine: " << nb_chaine_init << endl; //remove later, just for testing
		return true;
	}
	return false;
}
bool decodage_chaine(istringstream& data) {
	for(unsigned int i(0); i < nb_chaine_init; i++){
		if(lecture_c(data) == false) {return false;}
	}
	etat = CHAINE_MODE;
	return true;
}
bool decodage_chaine_mode(istringstream& data) {
	if(lecture_c_mode(data) == false) {return false;}
	etat = FIN;
	return true;
}
