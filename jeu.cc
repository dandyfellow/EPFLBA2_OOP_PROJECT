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
int unsigned counts = 0;
int unsigned score = 0;
int unsigned nb_particule_init = 0;
int unsigned nb_faiseur_init = 0;
int unsigned nb_chaine_init = 0;

Etat etat = SCORE;

//---------------------------------------------------------------------------------------------------
// 										PROTOTYPES
//---------------------------------------------------------------------------------------------------
void reset();
bool imprimer_data(istringstream &data);
bool decodage_score(istringstream &data);
bool decodage_ligne(istringstream &data);
bool decodage_nb_particule(istringstream &data);
bool decodage_particule(istringstream &data);
bool decodage_nb_faiseur(istringstream &data);
bool decodage_faiseur(istringstream &data);
bool decodage_nb_chaine(istringstream &data);
bool decodage_chaine(istringstream &data);
bool decodage_chaine_mode(istringstream &data);
bool collisions_intertides();
//---------------------------------------------------------------------------------------------------
// 									END OF PROTOTYPES
//---------------------------------------------------------------------------------------------------
void reset(){
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
			//imprimer_data(data); // TESTING
		}
		fichier.close();
        return true;
	}
	cout << "erreur lors de l'ouverture du fichier" << endl;
	return false;
}




bool decodage_ligne(istringstream& data) {
	switch(etat) 
	{
	case SCORE: // lecture du nombre de livreurs
		if(decodage_score(data) == false) return false;
	    break;

	case NB_PARTICULE: // ajout dans le vector en cas de succès
		if(decodage_nb_particule(data) == false) return false;
	    break;

	case PARTICULE: // lecture du nombre de véhicules
		if(decodage_particule(data) == false) return false;
	    break;

	case NB_FAISEUR: 
		if(decodage_nb_faiseur(data) == false) return false;
	    break;

	case FAISEUR: 
		if(decodage_faiseur(data) == false) return false;
	    break;

	case NB_CHAINE: 
		if(decodage_nb_chaine(data) == false) return false;
	    break;

	case CHAINE: 
		if(decodage_chaine(data) == false) return false;
	    break;

	case CHAINE_MODE:
		if(decodage_chaine_mode(data) == false) return false;
	    break;		

	case FIN: 
		break;
		
	}
	return true;	
}


bool decodage_score(istringstream& data){
	data >> score;	
	//cout << "score: " << score << endl; //remove later, just for testing
	if((score == 0) or (score > score_max)) {
		cout << message::score_outside(score);
		return false;
	}
	etat = NB_PARTICULE;
	return true;
	
}

bool decodage_nb_particule(istringstream& data) {
	if(data >> nb_particule_init){
		//cout << "nb particules: " << nb_particule_init << endl; //remove later, just for testing
		//cout << "count: " << count << endl; //remove later, just for testing

		if(nb_particule_init > nb_particule_max) {//  !!!!!!!!!!!!!!!!!!!!!!!!!!! nbr particule negatif ? removed : nb_particule_init < 0 ||
			cout << message::nb_particule_outside(nb_particule_init);
			return false;
		}
		if(nb_particule_init == 0) {etat = NB_FAISEUR;}
		else {
			etat = PARTICULE;
			counts = 0;
		}
		return true;
	}
	return false;
}
bool decodage_particule(istringstream& data) {
	counts++;
	if(counts == nb_particule_init) etat = NB_FAISEUR;
	if(lecture_p(data) == false){return false;}
	return true;
}
bool decodage_nb_faiseur(istringstream& data) {
	if(data >> nb_faiseur_init){
		if(nb_faiseur_init == 0) {etat = NB_CHAINE;}
		else {etat = FAISEUR;}
		//cout << "nb faiseur: " << nb_faiseur_init << endl; //remove later, just for testing
		//cout << "count: " << count << endl; //remove later, just for testing

		counts = 0;
		return true;
	}
	return false;
}

bool decodage_faiseur(istringstream& data) {
	counts++;
	if(counts == nb_faiseur_init) etat = NB_CHAINE;

	//cout << "count: " << count << endl; //remove later, just for testing

	if(lecture_f(data) == false) {return false;}
	return true;
}
bool decodage_nb_chaine(istringstream& data) {
	if(data >> nb_chaine_init){
		if(nb_chaine_init == 0) {etat = CHAINE_MODE;}
		else {etat = CHAINE;}
		//cout << "nb chaine: " << nb_chaine_init << endl; //remove later, just for testing
		//cout << "count: " << count << endl; //remove later, just for testing

		counts = 0;
		return true;
	}
	return false;
}
bool decodage_chaine(istringstream& data) {
	counts++;
	if(counts == nb_chaine_init) etat = CHAINE_MODE;
	if(lecture_c(data) == false) {return false;}
	return true;
}
bool decodage_chaine_mode(istringstream& data) {
	if(lecture_c_mode(data) == false) {return false;}

	counts = 0;
	etat = FIN;

	if(collisions_intertides() == false) return false;

	return true;
}


bool collisions_intertides(){
	std::vector<pair<int, Cercle>> chaine = Chaine::get_chaine();
	const vector<shared_ptr<Faiseur>>& faiseur = Faiseur::get_liste_faiseurs();
	for(const auto& [index_articulation, articulation] : chaine){

		//std::cout << "Articulation: " << articulation.get_centre().x << " ; " << articulation.get_centre().y << "\n"; //testing remove latter

		for(const auto& f : faiseur){

			//std::cout << "Faiseur Rayon: " << f->get_rayon() << "\n"; //testing remove latter
			//std::cout << "Faiseur Position: " << f->get_positionx() << " " << f->get_positiony() << "\n"; //testing remove latter	
			//std::cout << "Faiseur Index: " << f->get_index() << "\n"; //testing remove latter

			for(const auto& [index_elements, point] : f->get_elements()){

				//std::cout << "Element number: " << index_elements << " , point: " << point.x << " : " << point.y <<"\n"; //testing remove latter

				Cercle c_faiseur(point , f->get_rayon());
				if(Cercle::inclusion(c_faiseur, articulation)) {
					cout << message::chaine_articulation_collision(index_articulation, f->get_index(), index_elements);
					return false;
				}
				
			}
			
		}
	}
	return true;
}