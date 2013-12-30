#ifndef INSTANCE_HPP
#define	INSTANCE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "client.hpp"

class Instance;
class Solution;

class Instance{
	public:
	
	friend void heuristiqueConctruction(Instance& inInst , Solution& inSol);

	int 	nbrClient,		//nombre des clients
			cap;			//capacite des vehicules
	float	** matDistance;	//matrice des distances
		  
	std::vector<Client> clients;	//vecteur des clients

	std::string nomInstance;		//nom instance
	
	
	Instance(std::string inNomInstance);
	void afficher();
	void afficher_tournees();

};


#endif
