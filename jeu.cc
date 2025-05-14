//jeu.cc, Adam Coste et Max Ciriani, version 1
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
//needed because all of these are statics 
// -> cannot initialize statics with default values in the header file

#define WIDTH_DRAWING 2
unsigned int Jeu::score = 0;
bool Jeu::lecture_success = false;
Status Jeu::status = ONGOING;
Cercle Jeu::start_cercle = {{0,0},0};


namespace{
	bool decodage_score(istringstream &data);
	bool decodage_ligne(istringstream &data);
	bool decodage_nb_particule(istringstream &data);
	bool decodage_particule(istringstream &data);
	bool decodage_nb_faiseur(istringstream &data);
	bool decodage_faiseur(istringstream &data);
	bool decodage_nb_chaine(istringstream &data);
	bool decodage_chaine(istringstream &data);
	bool decodage_chaine_mode(istringstream &data);
	bool collision_chaine_faiseur();

	string single_particule_sauvegarde_ecriture(Particule* p_ptr);
	string particule_sauvegarde_ecriture();

	string single_faiseur_sauvegarde_ecriture(Faiseur* f_ptr);
	string faiseur_sauvegarde_ecriture();

	string single_chaine_sauvegarde_ecriture(pair<int, Cercle> c_pair);
	string chaine_sauvegarde_ecriture();

	int unsigned counts = 0;
	static int unsigned nb_particule_init = 0;
	static int unsigned nb_faiseur_init = 0;
	static int unsigned nb_chaine_init = 0;

	Etat etat = SCORE;
}

bool victoire(){
	if (Chaine::get_longueur_chaine() == 0) return false; //évite une bus error 
	Cercle c1(Chaine::get_but_final().get_centre(), 0);
	Cercle c2(Chaine::get_chaine(Chaine::get_longueur_chaine()-1).second.get_centre(),
		r_capture);
	if(Cercle::inclusion(c2,c1)){
		return true;
	}
	return false;
}

void ajouter_chaine(const vector<Particule*>& liste_particules){
	cout << __func__ << endl;
	int n(0);
	Particule* particule = nullptr;
	
	for(auto& p : liste_particules) {
		Cercle c1(p->get_position(), 0);
		Cercle c2 = {{0,0},0};
		if(Chaine::get_longueur_chaine() == 0) {
			c2 = Cercle(Jeu::get_start_cercle().get_centre(), r_capture);
		} else {
			c2 = Cercle(Chaine::get_chaine(
				Chaine::get_longueur_chaine()-1).second.get_centre(), r_capture);
		}
		if (Cercle::inclusion(c2, c1)) {
			n++;
			particule = p;
		}
		if(n>= 2){return;}
	}
	if(n == 1){
		Chaine c(particule->get_position());
		Particule::supprimer_particule(particule);
		delete particule;
		return;
	}

	if(collision_chaine_faiseur()){
		Chaine::reset();
	}
}


void Jeu::draw_but_final(){
	Cercle but_final = Chaine::get_but_final();
	but_final.draw_cercle(WIDTH_DRAWING, NO_COLOR, BLACK);
}

void Jeu::draw_start(){
	Vecteur v_souris({0,0}, Chaine::get_mouse_pos());
	Vecteur v_start({0,0}, r_max, v_souris.get_angle());
	S2d start_pos = v_start.get_p2();
	Cercle start_cercle(start_pos, r_capture);
	creation_but_final(start_pos);
	start_cercle.draw_cercle(2, NO_COLOR, RED);
	set_start_cercle(start_cercle);
}
//====================================================================================
void Jeu::reset(){
	Particule::reset();
	Faiseur::reset();
	Chaine::reset();
	Jeu::score = 0;
	lecture_success = false;
	nb_particule_init = 0;
	nb_faiseur_init = 0;
	nb_chaine_init = 0;
	etat = SCORE;
	counts = 0;
}
void Jeu::set_status(Status s){
	status = s;
	cout << "Status set to: " << s << endl;
}

void Jeu::update() {
	//displaying info
	Chaine::display();
	Faiseur::display();
	Particule::display();
	
	if(score == 0) {
		Jeu::set_status(LOST);
	} else {
		Jeu::score--;
		update_particules();
		update_faiseurs();

		if(collision_chaine_faiseur()){
			Chaine::reset();
		}
		if(Chaine::get_longueur_chaine() == 0) {}//logique dans gui.cc
		
		if (Chaine::get_mode() == GUIDAGE) {
			Chaine::algo_move_chaine();
			
			if (victoire()){
				Jeu::set_status(WON);
			}
		}

	}
}

void Jeu::success(){
	cout << message::success();
}

bool Jeu::lecture(string nom_fichier){

	reset();

	ifstream fichier(nom_fichier); //opens the file (ifstream = input file stream)
    if(!fichier.fail()) {
		string line;
        // l’appel de getline filtre aussi les séparateurs
        while(getline(fichier >> ws,line)) {

			if(line[0]=='#')  continue;  
			istringstream data(line);

			if(decodage_ligne(data) == false) {
				reset(); // reset if problem during lecture
				return false; 
			}
		}
		fichier.close();
        return true;
	}
	cout << "erreur lors de l'ouverture du fichier" << endl;
	return false;
}

void Jeu::save_file(string file_name){
	ofstream save(file_name);
	if (!save.is_open()) { // Check if the file opened successfully
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
	save << "# fichier de sauvegarde" << endl;
	save << "# score: " << endl;
	save << Jeu::score << endl;
	save << endl;

	save << "# nombre d’entité particule puis les données d’une entité par ligne\n";
	save << Particule::get_nbrs_particules() << endl;
	save << particule_sauvegarde_ecriture() << endl;

	save << "# nombre d’entité faiseur puis les données d’une entité par ligne\n";
	save << Faiseur::get_liste_faiseurs().size() << endl;
	save << faiseur_sauvegarde_ecriture() << endl;

	save << "# nombre d’articulations (nul veut dire « pas de chaîne »)" << endl;
	save << "#        puis une ligne par articulation" << endl;
	save << Chaine::get_chaine().size() << endl;
	save << chaine_sauvegarde_ecriture() << endl;
	if(Chaine::get_mode() == CONSTRUCTION) save << "CONSTRUCTION";
	else save << "GUIDAGE";

	save.close();
}
void Jeu::draw_arene(){
	Cercle arene({0, 0}, r_max);
	arene.draw_cercle(WIDTH_DRAWING, NO_COLOR, GREEN);
}

void Jeu::draw_faiseurs(){
	for(const auto& f : Faiseur::get_liste_faiseurs()) {
		for(const auto& e : f->get_elements()) {
			Cercle c(e->get_position(), e->get_rayon());
			c.draw_cercle(1, NO_COLOR, BLUE);
			//cout << __func__ << endl;
		}
	}
}


void Jeu::draw_particules(){
	for(const auto& p : Particule::get_liste_particules()) {
		Cercle c(p->get_position(), r_viz);
		c.draw_cercle(WIDTH_DRAWING, CYAN, GREEN);
		//cout << __func__ << endl;
	}
}

void Jeu::draw_chaine(){
	vector<pair<int, Cercle>> chaine = Chaine::get_chaine();
	int chaine_size = chaine.size();
 
	for(int i = 0; i < chaine_size; ++i) {

		Cercle c(chaine[i].second.get_centre(), r_viz);
		c.draw_cercle(WIDTH_DRAWING, NO_COLOR, RED);

		if(i < (chaine_size - 1)) {
			Vecteur v(chaine[i].second.get_centre(),chaine[i + 1].second.get_centre());
			v.draw_vecteur(WIDTH_DRAWING, RED);
		}
	}
	if(chaine_size >=1){ //to not access t[-1] -> segmentation fault
	Cercle capture(chaine[chaine_size-1].second.get_centre(), r_capture);
	capture.draw_cercle(WIDTH_DRAWING, NO_COLOR, RED);
	}
}

Status Jeu::get_status() const{
	return status;
}

namespace {
	string single_chaine_sauvegarde_ecriture(pair<int, Cercle> c_pair){
		string txt = "\t";
		txt += to_string(c_pair.second.get_centre().x) + "\t";
		txt += to_string(c_pair.second.get_centre().y) + "\t";
		return txt;
	}
	
	string chaine_sauvegarde_ecriture(){
		string txt = "";
		const vector<pair<int, Cercle>> chaines = Chaine::get_chaine();
		for(const auto& c : chaines) {
			txt += single_chaine_sauvegarde_ecriture(c);
			txt += "\n";
		}
		return txt;
	}

	string single_faiseur_sauvegarde_ecriture(Faiseur* f_ptr){
		string txt = "\t";

		txt += to_string(f_ptr->get_positionx()) + "\t";
		txt += to_string(f_ptr->get_positiony()) + "\t";
	
		txt += to_string(f_ptr->get_alpha()) + "\t";
		txt += to_string(f_ptr->get_vitesse().get_norme()) + "\t";
		txt += to_string(f_ptr->get_rayon()) + "\t";
		txt += to_string(f_ptr->get_elements().size()) + "\t";
	
		return txt;
	}
	
	
	string faiseur_sauvegarde_ecriture(){
		string txt = "";
		const vector<unique_ptr<Faiseur>>& faiseurs = Faiseur::get_liste_faiseurs();
		for(const auto& f : faiseurs) {
			txt += single_faiseur_sauvegarde_ecriture(f.get());
			txt += "\n";
		}
		return txt;
	}

	string single_particule_sauvegarde_ecriture(Particule* p_ptr){
		string txt = "\t";
		txt += to_string(p_ptr->get_positionx()) + "\t";
		txt += to_string(p_ptr->get_positiony()) + "\t";
		txt += to_string(p_ptr->get_alpha()) + "\t";
		txt += to_string(p_ptr->get_vitesse().get_norme()) + "\t";
		txt += to_string(p_ptr->get_compteur()) + "\t";
		return txt;
	}

	string particule_sauvegarde_ecriture(){
		string txt = "";
		for(const auto& p : Particule::get_liste_particules()) {
			cout << "particule_sauvegarde_ecriture()" << endl;
			txt += single_particule_sauvegarde_ecriture(p);
			txt += "\n";
		}
		return txt;
	}


	bool decodage_score(istringstream& data){
		unsigned int s;
		data >> s;	
		Jeu::set_score(s);
		if((s == 0) or (s > score_max)) {
			cout << message::score_outside(s);
			return false;
		}
		etat = NB_PARTICULE;
		return true;
		
	}
	
	bool decodage_ligne(istringstream& data) {
		switch(etat) 
		{
		case SCORE: 
			if(decodage_score(data) == false) return false;
			break;
	
		case NB_PARTICULE:
			if(decodage_nb_particule(data) == false) return false;
			break;
	
		case PARTICULE: 
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
	
	bool decodage_nb_particule(istringstream& data) {
		if(data >> nb_particule_init){
			if(nb_particule_init > nb_particule_max) { 
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
			counts = 0;
			return true;
		}
		return false;
	}
	
	bool decodage_faiseur(istringstream& data) {
		counts++;
		if(counts == nb_faiseur_init) etat = NB_CHAINE;
		if(lecture_f(data) == false) {return false;}
		return true;
	}
	bool decodage_nb_chaine(istringstream& data) {
		if(data >> nb_chaine_init){
			if(nb_chaine_init == 0) {etat = CHAINE_MODE;}
			else {etat = CHAINE;}
			counts = 0;
			return true;
		}
		return false;
	}

	bool decodage_chaine(istringstream& data) {
		counts++;
		if(counts == nb_chaine_init){
			etat = CHAINE_MODE;

		}
		if(lecture_c(data) == false) {return false;}
		return true;
	}

	bool decodage_chaine_mode(istringstream& data) {
		if(lecture_c_mode(data) == false) {return false;}
		if(victoire()){
			Jeu::set_status(WON);
		}
		counts = 0;
		etat = FIN;
	
		if(collision_chaine_faiseur()) return false;
	
		return true;
	}
	
	bool collision_chaine_faiseur() { // returns true if collisions
		const vector<pair<int, Cercle>>& chaine = Chaine::get_chaine();
		const vector<unique_ptr<Faiseur>>& faiseurs = Faiseur::get_liste_faiseurs();
		
		for (const auto& [index_articulation, articulation] : chaine) {
			for (size_t i = 0; i < faiseurs.size(); ++i) {
				const auto& faiseur = faiseurs[i];
				const auto& elements = faiseur->get_elements();
				for (size_t j = 0; j < elements.size(); ++j) {
					Cercle c_faiseur(elements[j]->get_position(),faiseur->get_rayon());
					if (Cercle::intrusion(c_faiseur, articulation)) {
						cout << message::chaine_articulation_collision(
							index_articulation, static_cast<int>(i),static_cast<int>(j)
						);
						return true;
					}
				}
			}
		}
		return false;
	}
}

