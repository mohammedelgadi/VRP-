#include "solution.hpp"

Solution::Solution(Instance& inInst)
{
nbrTour = 0;
disTotal = 0;

/** Allocation des éléments pour les vecteurs */

dateArrivee.resize(inInst.nbrClient);   //indexation sur les clients
dateDepart.resize(inInst.nbrClient);	//indexation sur les clients
precTour.resize(inInst.nbrClient);		//indexation sur les clients
suivTour.resize(inInst.nbrClient);		//indexation sur les clients
numTour.resize(inInst.nbrClient);		//indexation sur les clients
charge.resize(inInst.nbrClient);		//indexation sur les clients
distance.resize(inInst.nbrClient);		//indexation sur les clients
	
//NB : Si on veut parcourir les tournées ne pas mettre comme critere 
//	   d'arret ...size() mais nbrTour car size() est plus grand que les 
//	   tournées réellement crées
chargeTour.resize(inInst.nbrClient);	//indexation sur les tournées
premClient.resize(inInst.nbrClient);	//indexation sur les tournées
dernClient.resize(inInst.nbrClient);	//indexation sur les tournées
distanceTou.resize(inInst.nbrClient);	//indexation sur les tournées

}


void Solution::afficher(Instance & inst)
{
	printf("***********Affichage*******\n");
for ( int i = 1 ; i <= nbrTour ; ++i)
 {
	if(tournees[i] != -1){
	cout << "Tournee " << i << endl;
	int j = premClient[i];
	while ( j != 0 && j != -1)
	{
	//cout << j << "[Ptard: "<< inst.clients[j].date_ptard <<"]"<< "[Arriv :"<< dateArrivee[j] <<", Depart:" <<dateDepart[j] << "] "<<" ["<< distance[j] << "] " <<"==>" ;
	cout << j <<"==>" ;
	j = suivTour[j];
	}
	printf("\n");
	cout << "\n distance parcourue par la tournée " << i << " : " << distanceTou[i];
	cout << endl;
	cout << "Charge Totale : "<< chargeTour[i] << endl;
	cout << endl;
		
 }
}
}
