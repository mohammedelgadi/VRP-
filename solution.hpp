#ifndef SOLUTION_HPP
#define	SOLUTION_HPP

#include <vector>
#include <iostream>
#include "instance.hpp"
/*
 * classe: solution
 * 
*/

using namespace std;

//class Instance;

class Solution{	
	public	:
	
	friend void heuristiqueConctruction(Instance& inInst , Solution& inSol);

	vector<int> dateArrivee,	//indexation sur les clients
				dateDepart,		//indexation sur les clients
				precTour,		//indexation sur les clients
				suivTour,		//indexation sur les clients
				numTour,		//indexation sur les clients
				charge,			//indexation sur les clients
/*pas encore*/	distance,       //indexation sur les clients
				
				chargeTour,		//indexation sur les tournées
				premClient,		//indexation sur les tournées
				dernClient,		//indexation sur les tournées
/*pas encore*/	distanceTou,    //indexation sur les tournées
				tournees;
				
	
	int			nbrTour,		//nombre de tournées
/*pas encore*/	disTotal,		//distance parcourue
				nbrTour_fictif;
				
	Solution(Instance& inIns);
	void afficher(Instance & inst);
	
	};
#endif
