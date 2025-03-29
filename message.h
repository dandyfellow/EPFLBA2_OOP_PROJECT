// message.h, Adam Coste et Max Ciriani, version 1
#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
//
// message.h  : 13 fonctions pour l'affichage des messages d'erreur
//              et une fonction supplémentaire pour indiquer le succès de la lecture
//
// Version 1.0 du 24.02.2025
//

#include <string>

namespace message
{
	// score must be within ]0, max_score]
	std::string score_outside(unsigned score);

	// an entity is not fully inside the arena of radius r_max
	std::string particule_outside(double x, double y);
	std::string faiseur_outside(double x, double y);
	std::string articulation_outside(double x, double y);

	// Mobile : displacement must be within [0, d_max]
	std::string mobile_displacement(double d);

	// Particule : number must be within [0, nb_particule_max]
	std::string nb_particule_outside(unsigned nb);
	// Particule : counter must be within [0, time_to_split[
	std::string particule_counter(unsigned counter);

	// Faiseur : radius must be within [r_min_faiseur, r_max_faiseur]
	std::string faiseur_radius(double radius);
	// Faiseur : nbe > 0
	std::string faiseur_nbe(unsigned nbe);
	// Faiseur: collision detection ; both id and index values start at zero
	std::string faiseur_element_collision(unsigned id1, unsigned index1,
										  unsigned id2, unsigned index2);

	// Chaine : root articulation is not close enough to arena boundary
	std::string chaine_racine(double x, double y);
	// Chaine : inter-articulation distance must be within [0, r_capture];
	//          between smallest_index and smallest_index+1 ; index start at zero
	std::string chaine_max_distance(unsigned smallest_index);
	// Chaine : collision detection articulation<->faiseur element;
	//          both id and index start at zero
	std::string chaine_articulation_collision(unsigned articulation_index,
											  unsigned faiseur_id,
											  unsigned element_index);

	// Everything went well => file reading and all validation checks
	std::string success();
}

#endif // MESSAGE_H_INCLUDED