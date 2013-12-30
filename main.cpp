#include <iostream>
#include "instance.hpp"
#include "solution.hpp"
#include "fonctions.hpp"
#include <stdlib.h>

int main()
{
	
Instance instance("c101.txt");
instance.afficher();
Solution solution(instance);
heuristiqueConctruction( instance , solution );
solution.afficher(instance);
//_2Opt(instance , solution,1,1,0,3);
//solution.afficher(instance);
while(_2opt_( instance , solution )){
solution.afficher(instance);
}


solution.afficher(instance);
cout << "Nbre tournees : " << solution.nbrTour_fictif -1 << endl ;
cout << "Distance Totale : " << solution.disTotal << endl ;
return 0;
}
