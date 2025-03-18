// message.cc  : 13 fonctions pour l'affichage des messages d'erreur
//              et une fonction supplémentaire pour indiquer le succès de la lecture
// 
//
// Version 1.0 du 24.02.2025
//

#include "message.h"

using namespace std;

// l'espace de nom non-nommé sert ici à restreindre l'usage de la fonction
// reorder_for_consistency à ce module ; c'est une fonction utilitaire locale
namespace  // non-nommé
{
    void reorder_for_consistency(unsigned &index1, unsigned &id1,
                                 unsigned &index2, unsigned &id2)
    {
        if (index1 > index2 || (index1 == index2 && id1 > id2))
        {
            swap(index1, index2);
            swap(id1, id2);
        }
    }
}

// définition des autres fonctions appartenant à l'espace de nom message
// noter la syntaxe " message:: " qui précède le nom de la fonction.
// Il indique que la fonction appartient à cet espace de nom "message" 

std::string message::score_outside(unsigned score)
{
    return string("score (") + to_string(score) 
         + string(") must be within ]0, score_max]\n");
}

std::string message::particule_outside(double x, double y)
{
    return string("particule at (") + to_string(x) + string(";") 
         + to_string(y) + string(") is outside the arena\n");
}
std::string message::faiseur_outside(double x, double y)
{
    return string("faiseur at (") + to_string(x) + string(";") 
         + to_string(y) + string(") is outside the arena\n");
}
std::string message::articulation_outside(double x, double y)
{
    return string("articulation at (") + to_string(x) + string(";") 
         + to_string(y) + string(") is outside the arena\n");
}

std::string message::mobile_displacement(double d)
{
    return string("mobile entity displacement (") + to_string(d) 
         + string(") must be within [0, d_max]\n");
}

std::string message::nb_particule_outside(unsigned nb)
{
    return string("particule number (") + to_string(nb) 
         + string(") must be within [0, nb_particule_max]\n");
}
std::string message::particule_counter(unsigned counter)
{
    return string("particule counter (") + to_string(counter) 
         + string(") must be within [0, time_to_spli[ \n");
}

std::string message::faiseur_radius(double radius)
{
    return string("faiseur radius (") + to_string(radius) 
         + string(") is not within [r_min_faiseur, r_max_faiseur]\n");
}
std::string message::faiseur_nbe(unsigned nbe)
{
    return string("faiseur nbe (") + to_string(nbe) 
         + string(") is not strictly positive\n");
}
std::string message::faiseur_element_collision(unsigned id1, unsigned index1,
								               unsigned id2, unsigned index2)
{
    reorder_for_consistency(index1, id1, index2, id2);

    return string("faiseur (") + to_string(id1) + string(") element (") 
         + to_string(index1) + string(") collides with faiseur (") + to_string(id2) 
         + string(") element (") + to_string(index2) + string(")\n");
}

std::string message::chaine_racine(double x, double y)
{
    return string("root at (") + to_string(x) + string(";") 
         + to_string(y) + string(") is not close enough to the arena boundary\n");
}
std::string message::chaine_max_distance(unsigned smallest_index)
{
    return string("too long distance between articulation (") 
         + to_string(smallest_index)  
         + string(") and the following one\n");
}
std::string message::chaine_articulation_collision(unsigned articulation_index,
	                                          unsigned faiseur_id, 
	                                          unsigned element_index)
{
    return string("articulation (") + to_string(articulation_index) 
         + string(") collides with faiseur (") + to_string(faiseur_id) 
         + string(") element (") + to_string(element_index) + string(")\n");
}

std::string message::success()
{
    return string("Correct file\n");
}
