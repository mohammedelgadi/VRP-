#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <vector> 
//#include "instance.hpp" 
//#include "solution.hpp"
/*
 * Class client{}
 * contient l'ensemble des informations clients
 * 
 *  */
class Instance;
class Solution;

class Client{
	public :

	friend void heuristiqueConctruction(Instance& inInst , Solution& inSol);

	int		id,			//identifiant
			x,			//abs x
			y,			//ord y
			a_i,		//ouverture
			b_i,		//fermeture
			s_i,		//durée service
			d_i,		//demande
			date_ptard;	//date au plus tard
   
   std::vector<int> voisins; //liste des arcs et voisins
    
   Client();			//constructeur			
};



#endif
