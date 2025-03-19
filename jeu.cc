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


/*ic unsigned count(0), total(0);	

// structures de données construites avec la lecture du fichier
static vector<Livreur>   tlivreur;
static vector<Vehicule>  tvehicule;
static vector<Livraison> tlivraison;
					 								
// prototypes
bool lecture(string nom_fichier);
void reset();
bool decodage_ligne(istringstream& line);
bool decodage_nb_livreur(istringstream& data);
bool decodage_livreur(istringstream& data);
bool decodage_nb_vehicule(istringstream& data);
bool decodage_vehicule(istringstream& data);
bool decodage_nb_livraison(istringstream& data);
bool decodage_livraison(istringstream& data);
void erreur(Erreur_lecture code);

// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	if(argc != 2) erreur(LECTURE_ARG);
	
	if(lecture(argv[1]))
		cout << "Première lecture OK !" << endl;
	else
		cout << "==> Problème à la première lecture !" << endl;
	
	// seconde tentative 

	if(lecture(argv[1]))
		cout << "Seconde lecture OK !" << endl;
	else
		cout << "==> Problème à la seconde lecture !" << endl;
	

	return EXIT_SUCCESS;
}

// traite le fichier ligne par ligne.
// une détection d'erreur simple ou complexe renvoie un booléen false
bool lecture( string nom_fichier)
{
	reset();

    ifstream fichier(nom_fichier); 
    if(!fichier.fail()) 
    {
		string line;

        // l’appel de getline filtre aussi les séparateurs
        while(getline(fichier >> ws,line)) 
        {
			// ligne de commentaire à ignorer, on passe à la suivante
			if(line[0]=='#')  continue;  
 
			istringstream data(line);
      
			if(decodage_ligne(data)== false) // détection d'erreur simple
				return false;
        }
        cout << "fin de la lecture du fichier ligne par ligne " << endl;
        cout << "il est possible de faire d'autres détections d'erreurs " 
                " plus complexes inter-types avant de quitter cette fonction" << endl;
        
        return true;
	}
	else erreur(LECTURE_OUVERTURE);
	return false;
}

// ré-initialise les variable de l'automate et vide les vectors
void reset()
{
	etat = NB0;
	count= 0;
	total= 0;
	tlivreur.clear();
	tvehicule.clear();
	tlivraison.clear();
}

// décodage selon l'etat courant d'une ligne lue dans le fichier 
// une détection d'erreur simple au niveau d'une ligne isolée renvoie un booléen false  
bool decodage_ligne(istringstream& data)
{
	switch(etat) 
	{
	case NB0: // lecture du nombre de livreurs
		if(decodage_nb_livreur(data)== false) 	return false;
	    break;

	case LIVREUR: // ajout dans le vector en cas de succès
		if(decodage_livreur(data)== false) 		return false;
	    break;

	case NB1: // lecture du nombre de véhicules
		if(decodage_nb_vehicule(data)== false) 	return false;
	    break;

	case VEHICULE: // ajout dans le vector en cas de succès
		if(decodage_vehicule(data)== false) 	return false;
	    break;

	case NB2: // lecture du nombre de livraisons
		if(decodage_nb_livraison(data)== false) return false;
	     break;

	case LIVRAISON: // ajout dans le vector en cas de succès
		if(decodage_livraison(data)== false) 	return false;
	    break;

	case FIN: erreur(LECTURE_FIN) ; 
		return false;

	default: erreur(LECTURE_ETAT);
		return false;
	}
	return true;	
}

bool decodage_nb_livreur(istringstream& data)
{
	if(!(data >> total)) 
	{
		erreur(LECTURE_NB0);
		return false;
	} 
	count = 0;
	if(total==0) 
		etat=NB1; 
	else         
		etat=LIVREUR ; 
	return true;
}

bool decodage_livreur(istringstream& data)
{
	Livreur x;
	if(x.lecture(data)==false) 				
		return false;
	else 
	{
		tlivreur.push_back(x);
		++count;
	}
	if(count == total) 
		etat=NB1 ;
	return true;
}

bool decodage_nb_vehicule(istringstream& data)
{
	if(!(data >> total)) 
	{
		erreur(LECTURE_NB1);
		return false;
	} 
	count = 0;
	if(total==0) 
		etat=NB2; 
	else         
		etat=VEHICULE ; 
	return true;
}

bool decodage_vehicule(istringstream& data)
{
	Vehicule y;
	if(y.lecture(data)==false) 				
		return false;
	else
	{
		++count;
		tvehicule.push_back(y);
	}		
	if(count == total) 
		etat=NB2 ;
	return true;
}

bool decodage_nb_livraison(istringstream& data)
{
	if(!(data >> total)) 
	{
		erreur(LECTURE_NB2);
		return false;
	} 
	count = 0;
	if(total==0) 
		etat=FIN; 
	else         
		etat=LIVRAISON ; 
	return true;
}

bool decodage_livraison(istringstream& data)
{
	Livraison z;
	if(z.lecture(data)==false) 				
		return false;
	else 
	{
		++count;
		tlivraison.push_back(z);
	}	
	if(count == total) 
		etat=FIN ;
	return true;
}

// affiche un message d'erreur puis quitte le programme
void erreur(Erreur_lecture code)
{
	switch(code)
	{
	case LECTURE_ARG : cout << " nom de fichier manquant\n";  
		break;
	case LECTURE_OUVERTURE: cout << " ouverture fichier impossible\n";
		break;
	case LECTURE_NB0 : cout << " lecture nb livreurs impossible \n";
		break;
	case LECTURE_NB1 : cout << " lecture nb vehicules impossible \n";
		break;
	case LECTURE_NB2 : cout << " lecture nb livraisons impossible \n";
		break;
	case LECTURE_FIN : cout << " format non respecté \n";     
		break;
	case LECTURE_ETAT : cout << " etat inexistant\n";         
		break;
	default: cout << " erreur inconnue\n";
	}
	// arret d'exécution à commenter si on préfère poursuivre en renvoyant un booléen
	exit(EXIT_FAILURE); 
}*/