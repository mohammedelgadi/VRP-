#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include "solution.hpp"
#include "instance.hpp"
#include "client.hpp"
#include "fonctions.hpp"
#include <cstdio>
using namespace std;


/** 
 * \brief Heuristique de construction par insertion
 * 
 * @return  void
 * @param	Instance&	réf sur une instance du VRP
 * @param	Solution&	réf sur la solution à construire
 * 
 */
void heuristiqueConctruction(Instance& inInst , Solution& inSol)
{
	vector<Client>::iterator it = inInst.clients.begin();
	// parcours d'une séquence de clients
	// ++it en début pour ne pas prendre en compte le dépot
	for ( ++it ; it != inInst.clients.end() ; ++it)
		{
		if ( inSol.nbrTour == 0)
			{
			inSol.nbrTour ++ ;
			inSol.nbrTour_fictif ++;
			// modifications sur les torunées
			inSol.chargeTour[1]	= it->d_i;
			inSol.premClient[1]	= it->id;
			inSol.dernClient[1]	= it->id;
			inSol.distanceTou[1] = inInst.matDistance[0][it->id];

			// modifications sur les clients
			inSol.dateArrivee[it->id]	= it->a_i;
			inSol.dateDepart[it->id] 	= it->a_i + it->s_i;
			inSol.precTour[it->id]		= 0;
			inSol.suivTour[it->id]		= 0;
			inSol.numTour[it->id]		= 1;
			inSol.charge[it->id]		= it->d_i;
			inSol.distance[it->id]		= inInst.matDistance[0][it->id];
			}
		else
			{
			//d'abord chercher la possibilité de mettre le client 
			//dans une des tournées déjà existante
			bool done = false;
			for ( int i = 1 ; i <= inSol.nbrTour ; ++i)
				{
				if ( inSol.chargeTour[i] + it->d_i <= inInst.cap 
				  && it->date_ptard > inSol.dateDepart[ inSol.dernClient[i] ] )
					// on peut insérer dans la tournée i
					{	
					// modifications sur le client
					if ( inSol.dateDepart[ inSol.dernClient[i] ] <=  it->a_i ) 
						// si le véhicule arrive chez le client avant l'ouverture
						{inSol.dateArrivee[it->id]	= it->a_i;}
					else
						// sinon
					{inSol.dateArrivee[it->id] = inSol.dateDepart[ inSol.dernClient[i] ];}
						
					inSol.dateDepart[it->id] 	= inSol.dateArrivee[it->id] + it->s_i;
					
					inSol.precTour[it->id]		= inSol.dernClient[i];
					inSol.suivTour[it->id]		= 0;
						
					inSol.suivTour[inSol.dernClient[i]] = it->id;
						
					inSol.numTour[it->id]		= i;
						
					inSol.charge [it->id]		= inSol.chargeTour[i] + it->d_i;
					
					inSol.distance[it->id]		= inSol.distance[ inSol.precTour[it->id] ] + inInst.matDistance[ inSol.precTour[it->id] ][it->id];
						
						
					// modifications sur la tournée
					inSol.chargeTour[i]	+= it->d_i;
					inSol.dernClient[i]	= it->id;
					inSol.distanceTou[i] = inSol.distance[ inSol.dernClient[i] ];
						
					done = true;
					break;
					}
				}
			if ( done == false)
				// il faut créer une nouvelle tournée pour ce client
				{
				inSol.nbrTour ++ ;
				inSol.nbrTour_fictif ++;
				int j = inSol.nbrTour;
				// modifications sur les torunées
				inSol.chargeTour[j]	= it->d_i;
				inSol.premClient[j]	= it->id;
				inSol.dernClient[j]	= it->id;
				inSol.distanceTou[j] = inInst.matDistance[0][it->id];
				// modifications sur les clients
				inSol.dateArrivee[it->id]	= it->a_i;
				inSol.dateDepart[it->id] 	= it->a_i + it->s_i;
				inSol.precTour[it->id]		= 0;
				inSol.suivTour[it->id]		= 0;
				inSol.numTour[it->id]		= inSol.nbrTour;
				inSol.charge[it->id]		= it->d_i;
				inSol.distance[it->id]		= inInst.matDistance[0][it->id];
				}
				
				
			}
		}
		
		int u = 0;
		for( u = 1 ; u <= inSol.nbrTour ; u++){
		inSol.distanceTou[u] += inInst.matDistance[0][inSol.dernClient[u]];
		printf("-%d-",inSol.distanceTou[u]);
		inSol.tournees.push_back(u);
		}
		inSol.disTotal = 0;
		for ( int i = 1 ; i <= inSol.nbrTour ; ++i){
		inSol.disTotal = inSol.disTotal + inSol.distanceTou[i]; 
		}
}

int max(int a,int b){
	return (a>b)?a:b;
}
void changerTourSequence(Instance & inst, Solution & sol ,int Elmt , int new_Tr)
{
	printf("-----\n");
	//~ //On change l'indice des successeur de l'Element.
	//~ 
	//sol.afficher(inst);
	while( sol.suivTour[ Elmt ] != 0 )
	{
		printf("-----\n");
		
		//printf("%d---",sol.suivTour[ Elmt ]);
		sol.distance [ sol.suivTour[ Elmt ] ] = sol.distance[ Elmt ] + inst.matDistance[ Elmt ][ sol.suivTour[ Elmt ]];
		//printf("%d--------------------------------%d\n",sol.suivTour[ Elmt ],sol.distance [ sol.suivTour[ Elmt ] ]);
		sol.charge[ sol.suivTour[ Elmt ] ]    = sol.charge [ Elmt ] + inst.clients [ sol.suivTour[ Elmt ] ].d_i;
		sol.numTour [ sol.suivTour[ Elmt ] ]  = new_Tr;
		sol.dateArrivee[sol.suivTour[ Elmt ]] = max(sol.dateDepart[Elmt],inst.clients [ sol.suivTour[ Elmt ] ].a_i);
		sol.dateDepart[sol.suivTour[ Elmt ]]  = sol.dateArrivee[sol.suivTour[ Elmt ]] + inst.clients[sol.suivTour[ Elmt ]].s_i;
		Elmt = sol.suivTour[ Elmt ];
	}
	
}

bool _2Opt(Instance & inst, Solution  & sol , int I , int TrI , int J , int TrJ)
{
	bool ameliore_distance;
	bool ok_charge,
		 ok_fenetres;
		 
	int  	new_dist_I,
			new_dist_J,
			new_char_I,
			new_char_J,
			new_distanceTotal,
			new_TrI,
			new_TrJ;
		  
	if( I != 0 && J != 0 )
	{
	    if(sol.precTour [ I ] != 0  && sol.precTour [ J ] != 0)
	    {
			
			printf("------------sol.precTour [ I ] != 0 && sol.precTour [ J ] != 0----------------------------------\n");
			new_char_I = sol.charge[sol.precTour [ J ]] + sol.chargeTour[ TrI ] - sol.charge[sol.precTour [ I ]]; 
			new_char_J = sol.charge[sol.precTour [ I ]] + sol.chargeTour[ TrJ ] - sol.charge[sol.precTour [ J ]];
			ok_charge = (new_char_I <= inst.cap && new_char_J <= inst.cap) ;
			
			ok_fenetres = (sol.dateDepart[sol.precTour [ I ]] <=  inst.clients[J].date_ptard) && (sol.dateDepart[sol.precTour [ J ]] <=  inst.clients[ I ].date_ptard);
			new_dist_I =  sol.distance [ sol.precTour [ J ] ] + inst.matDistance[sol.precTour [ J ]][I] + sol.distanceTou[TrI] - sol.distance[ I ];
			new_dist_J =  sol.distance [ sol.precTour [ I ] ] + inst.matDistance[sol.precTour [ I ]][J] + sol.distanceTou[TrJ] - sol.distance[ J ];
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrJ] - sol.distanceTou[TrI] + new_dist_I + new_dist_J;
			ameliore_distance = (new_distanceTotal < sol.disTotal );
			
			if( ok_charge  && ok_fenetres && ameliore_distance )
			{
				//printf("ancienne distance : %d \n",sol.disTotal);
				//printf("Nouvelle distance : %d \n",new_distanceTotal);
				sol.suivTour [ sol.precTour [ I ] ] = J ;
				sol.suivTour [ sol.precTour [ J ] ] = I ;
				int predI = sol.precTour [ I ];
				sol.precTour [ I ] = sol.precTour [ J ] ;
				sol.precTour [ J ] = predI ;
				int dernier = sol.dernClient[ TrI ];
				sol.dernClient[ TrI ] = sol.dernClient [ TrJ ];
				sol.dernClient[ TrJ ] = dernier;
				new_TrI = TrJ;
				new_TrJ = TrI;
				sol.disTotal = new_distanceTotal;
				sol.distanceTou [ new_TrI ] = new_dist_I ;
				sol.distanceTou [ new_TrJ ] = new_dist_J ;
				sol.chargeTour  [ new_TrI ] = new_char_I ;
				sol.chargeTour  [ new_TrJ ] = new_char_J ;
				changerTourSequence(inst, sol , sol.precTour [ I ] , new_TrI);
				changerTourSequence(inst, sol , sol.precTour [ J ] , new_TrJ);
				return true;
		   }
		}
		else if (sol.precTour [ I ] != 0 && sol.precTour [ J ] == 0 )
		{
			printf("-----------sol.precTour [ I ] != 0 && sol.precTour [ J ] == 0---------------------------------\n");
			new_char_I  = sol.chargeTour [ TrI ] - sol.charge [ sol.precTour [ I ] ];
			new_char_J  = sol.charge [ sol.precTour [ I ] ] + sol.chargeTour [ TrJ ] ;
			
			ok_charge   = ( (new_char_I <= inst.cap)  && (new_char_J <= inst.cap ) );
			ok_fenetres = ( sol.dateDepart [ sol.precTour[ I ] ] <= inst.clients[J].date_ptard );
			new_dist_I = sol.distanceTou[TrI] - sol.distance [I] + inst.matDistance [0][I];
			new_dist_J = sol.distance[ sol.precTour [ I ] ] + inst.matDistance [sol.precTour [ I ] ][J]+ sol.distanceTou[TrJ] - - sol.distance[ J ];
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrJ] - sol.distanceTou[TrI] + new_dist_I + new_dist_J;
			ameliore_distance = (new_distanceTotal < sol.disTotal );
			if( ok_charge && ok_fenetres && ameliore_distance)
			{
				//printf("--------");
				//printf("ancienne distance : %d \n",sol.disTotal);
				//printf("Nouvelle distance : %d \n",new_distanceTotal);
				sol.suivTour [ sol.precTour [ I ] ] = J ; 
				int prec_I = sol.precTour [ I ];
				sol.precTour [ I ] = 0 ;
				sol.precTour [ J ] = prec_I ;
				
				sol.premClient[ TrJ ] = I ;
				int dernier_client_TrJ = sol.dernClient[ TrJ ];
				sol.dernClient[TrJ] = sol.dernClient[ TrI ];
				sol.dernClient[TrI] = dernier_client_TrJ;
				
			
				new_TrI = TrJ;
				new_TrJ = TrI;
				sol.disTotal = new_distanceTotal;
				sol.distanceTou [ new_TrI ] = new_dist_I ;
				sol.distanceTou [ new_TrJ ] = new_dist_J ;
				sol.chargeTour  [ new_TrI ] = new_char_I ;
				sol.chargeTour  [ new_TrJ ] = new_char_J ;
				changerTourSequence(inst, sol , sol.precTour [ J ] , new_TrJ);
				sol.distance[I] = inst.matDistance [0][I];
				sol.charge [I]  = inst.clients[I].d_i; //regard ici
				sol.numTour [ I ] = new_TrI;
				changerTourSequence( inst, sol ,I, new_TrI);
				return true;
				
			}
			
		}
		else if(sol.precTour  [ J ] != 0 && sol.precTour [ I ] == 0)
		{
			printf("-----------sol.precTour  [ J ] != 0 && sol.precTour [ I ] == 0---------------------------------\n");
			new_char_J  = sol.chargeTour [ TrJ ] - sol.charge [ sol.precTour [ J ] ];
			new_char_I  = sol.charge [ sol.precTour [ J ] ] + sol.chargeTour [ TrI ] ;
			
			ok_charge   = ( ( new_char_I <= inst.cap )  && ( new_char_J <= inst.cap ) );
			ok_fenetres = ( sol.dateDepart [ sol.precTour[ J ] ] <= inst.clients[I].date_ptard );
			new_dist_J = sol.distanceTou [ TrJ ] - sol.distance [ J ] + inst.matDistance [ 0 ][ J ];
			new_dist_I = sol.distance[ sol.precTour [ J ] ] + inst.matDistance [sol.precTour [ J ] ][I]+sol.distanceTou[TrI] - sol.distance[ I ];
			//~ printf("new distance I %d", new_dist_I);
			//~ printf("new distance I %d", new_dist_J);
			//sleep(4);
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrJ] - sol.distanceTou[TrI] + new_dist_I + new_dist_J;
			ameliore_distance = (new_distanceTotal < sol.disTotal );
			//~ printf("new distance totale %d", new_distanceTotal);
			//~ printf("ancienne distance totale %d", sol.disTotal);
			if( ok_charge && ok_fenetres && ameliore_distance)
			{
				//printf("ancienne distance : %d \n",sol.disTotal);
				//printf("Nouvelle distance : %d \n",new_distanceTotal);
				sol.suivTour [ sol.precTour [ J ] ] = I ; 
				int prec_J = sol.precTour [ J ];
				sol.precTour [ J ] = 0 ;
				sol.precTour [ I ] = prec_J ;
				
				sol.premClient[ TrI ] = J ;
				int dernier_client_TrI = sol.dernClient[ TrI ];
				sol.dernClient[ TrI ] = sol.dernClient[ TrJ ] ;
				
				sol.dernClient[TrJ] = dernier_client_TrI;
				
				new_TrI = TrJ;
				new_TrJ = TrI;
				sol.disTotal = new_distanceTotal;
				sol.distanceTou [ new_TrI ] = new_dist_I ;
				sol.distanceTou [ new_TrJ ] = new_dist_J ;
				sol.chargeTour  [ new_TrI ] = new_char_I ;
				sol.chargeTour  [ new_TrJ ] = new_char_J ;
				changerTourSequence ( inst, sol , sol.precTour [ I ] , new_TrI);
				
				sol.distance[J] = inst.matDistance [0][J];
				sol.charge [J]  = inst.clients[J].d_i; //regard ici
				sol.numTour [ J ] = new_TrJ;
				changerTourSequence ( inst, sol , J , new_TrJ);
				
				return true;
			}
			
		}		
	}
	else if ( I == 0 && J != 0 )
	{///////////////////////
		if( sol.precTour[ J ] != 0 )
		{
			printf("-----------A---------------------------------\n");
			//new_char_I contient les elements de la charge de I
			ok_fenetres = ( sol.dateDepart[ sol.dernClient[ TrI ] ] <= inst.clients[ J ].date_ptard );
			new_char_J = sol.charge[ sol.dernClient[ TrI ] ] + sol.chargeTour[ TrJ ] - sol.charge [ sol.precTour[ J ] ] ;
			int new_char_ = sol.charge [ sol.precTour[ J ] ];
			ok_charge = ( new_char_J <= inst.cap );
			
			
			new_dist_J = sol.distance [ sol.precTour[ J ] ]  + inst.matDistance [ sol.precTour[ J ] ][ 0 ]; 
			new_dist_I = sol.distance [ sol.dernClient[ TrI ] ] + inst.matDistance[sol.dernClient[ TrI ]][ J ] + sol.distanceTou[TrJ] - sol.distance[J];
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrJ] - sol.distanceTou[ sol.dernClient[ TrI ] ] + new_dist_I + new_dist_J;
			ameliore_distance = (new_distanceTotal < sol.disTotal );
			if( ok_charge  && ok_fenetres && ameliore_distance )
			{
			//~ printf("ancienne distance : %d \n",sol.disTotal);
			//~ printf("Nouvelle distance : %d \n",new_distanceTotal);
			sol.suivTour [ sol.precTour [ J ] ] = I;
			sol.suivTour [ sol.dernClient [ TrI ] ]  = J;
			int dernier_J = sol.precTour [ J ];
			sol.precTour [J] = sol.dernClient [ TrI ];
			
			sol.disTotal = new_distanceTotal;
			
				//new_TrJ = TrI;
			
				sol.distanceTou [ TrJ ] = new_dist_J ; //new_dist_I contient la nouvelle distance de l'ancienne tournne de J
				sol.distanceTou [ TrI ] = new_dist_I ;
				sol.chargeTour  [ TrI ] = new_char_J ;
				sol.chargeTour  [ TrJ ] = new_char_ ;
				changerTourSequence(inst, sol , sol.dernClient[ TrI ] , TrI);
				
				sol.dernClient[ TrI ] = sol.dernClient [ TrJ ];
				sol.dernClient[ TrJ ] = dernier_J;
				
				return true;
		    }
			
		}
		else
		{
			printf("-----------B--------------------------------\n");
			//printf("\n ********************** \n");
			ok_fenetres = ( sol.dateDepart[ sol.dernClient[ TrI ] ] <= inst.clients[ J ].date_ptard );
			ok_charge = ( sol.charge[ sol.dernClient[ TrI ] ] + sol.chargeTour[ TrJ ] <= inst.cap );
			new_char_I = sol.charge[ sol.dernClient[ TrI ] ] + sol.chargeTour[ TrJ ];
			new_dist_I = sol.distance [ sol.dernClient[ TrI ] ] + inst.matDistance[sol.dernClient[ TrI ] ] [ J ]  + sol.distanceTou[TrJ] - sol.distance[J];
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrJ] - sol.distanceTou[ TrI  ] +  new_dist_I;
			//ameliore_distance = (new_distanceTotal <= sol.disTotal );
			
			//new_dist_J = sol.distance [ sol.dernClient[ TrJ ] ] + inst.matDistance[sol.dernClient[ TrJ ] ] [ I ]  + sol.distanceTou[TrI] - sol.distance[I];
			
			//new_distanceTotal =  sol.disTotal - sol.distanceTou[TrI] - sol.distanceTou[ TrJ ] +  new_dist_J;
			if ( ok_charge  && ok_fenetres  )
			{
			//~ printf("ancienne distance : %d \n",sol.disTotal);
			//~ printf("Nouvelle distance : %d \n",new_distanceTotal);
			sol.suivTour [ sol.dernClient [ TrI ] ]  = J;
			sol.precTour [ J ] = sol.dernClient [ TrI ];
			
			
			sol.disTotal = new_distanceTotal;
			sol.chargeTour  [ TrI ] = new_char_I ;
			sol.distanceTou	[ TrI ] = new_dist_I;
			changerTourSequence(inst, sol , sol.dernClient[ TrI ] , TrI);
			sol.dernClient  [ TrI ] = sol.dernClient [ TrJ ];
			sol.chargeTour  [ TrJ ] = -1;
			sol.dernClient  [ TrJ ] = -1;
			sol.dernClient  [ TrJ ] = -1;
			sol.tournees	[ TrJ ] = -1;
			sol.nbrTour_fictif --;
			
			return true;
			//suppression d'une tournée TrJ
			
			}
			
		}
	}
	else if ( J == 0 && I != 0 )
	{
		printf("-----------c---------------------------------\n");
		//printf("\n ***************** J == 0 && I != 0 ************* ************** \n");
		//new copie.
		//printf("%d\n", sol.precTour[ I ]);
		if( sol.precTour[ I ] != 0 )
		{
			//printf("\n ************\n");
			
			//new_char_I contient les elements de la charge de I
			ok_fenetres = ( sol.dateDepart[ sol.dernClient[ TrJ ] ] <= inst.clients[ I ].date_ptard );//
			new_char_I = sol.charge[ sol.dernClient[ TrJ ] ] + sol.chargeTour[ TrI ] - sol.charge [ sol.precTour[ I ] ] ;
			int new_char_ = sol.charge [ sol.precTour[ I ] ];
			ok_charge = ( new_char_I <= inst.cap );
			
			
			new_dist_I = sol.distance [ sol.precTour[ I ] ]  + inst.matDistance [ sol.precTour[ I ] ][ 0 ]; 
			new_dist_J = sol.distance [ sol.dernClient[ TrJ ] ] + inst.matDistance[sol.dernClient[ TrJ ]][ J ] + sol.distanceTou[TrI] - sol.distance[I];
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrI] - sol.distanceTou[ sol.dernClient[ TrJ ] ] + new_dist_I + new_dist_J;
			ameliore_distance = (new_distanceTotal < sol.disTotal );

			if( ok_charge  && ok_fenetres && ameliore_distance )
			{
			//~ printf("ancienne distance : %d \n",sol.disTotal);
			//~ printf("Nouvelle distance : %d \n",new_distanceTotal);
			sol.suivTour [ sol.precTour [ I ] ] 		= J;
			sol.suivTour [ sol.dernClient [ TrJ ] ] 	 = I;
			int dernier_I = sol.precTour [ I ];//
			sol.precTour [ I ] = sol.dernClient [ TrJ ];
			
			sol.disTotal = new_distanceTotal;
			
				//new_TrJ = TrI;
			
				sol.distanceTou [ TrI ] = new_dist_I ; //new_dist_I contient la nouvelle distance de l'ancienne tournne de J
				sol.distanceTou [ TrJ ] = new_dist_J ;
				sol.chargeTour  [ TrJ ] = new_char_I ;
				sol.chargeTour  [ TrI ] = new_char_ ;//
				changerTourSequence(inst, sol , sol.dernClient[ TrJ ] , TrJ);
				
				sol.dernClient[ TrJ ] = sol.dernClient [ TrI ];
				sol.dernClient[ TrI ] = dernier_I;
				return true;
		    }
			
		}
		else
		{
			printf("-----------D---------------------------------\n");
			ok_fenetres = ( sol.dateDepart[ sol.dernClient[ TrJ ] ] <= inst.clients[ I ].date_ptard );
			
			ok_charge = ( sol.charge[ sol.dernClient[ TrJ ] ] + sol.chargeTour[ TrI ] <= inst.cap );
			
			new_char_J = sol.charge[ sol.dernClient[ TrJ ] ] + sol.chargeTour[ TrI ];
			//printf("\n ****dernier trJ %d********** \n",sol.dernClient[ TrJ ]);
			new_dist_J = sol.distance [ sol.dernClient[ TrJ ] ] + inst.matDistance[sol.dernClient[ TrJ ] ] [ I ]  + sol.distanceTou[TrI] - sol.distance[I];
			
			new_distanceTotal =  sol.disTotal - sol.distanceTou[TrI] - sol.distanceTou[ TrJ ] +  new_dist_J;
			//ameliore_distance = (new_distanceTotal <= sol.disTotal );
			printf("ancienne distance : %d \n",sol.disTotal);
			printf("sol.distance[I] = %d \n",sol.distance[I]);
			printf("Nouvelle distance : %d \n",new_distanceTotal);
			if ( ok_charge  && ok_fenetres )
			{
				
				//printf("%d \n",sol.dernClient [ TrJ ]);
			sol.suivTour [ sol.dernClient [ TrJ ] ]  = I;
			sol.precTour [ I ] = sol.dernClient [ TrJ ];
			
			
			sol.disTotal = new_distanceTotal;
			sol.chargeTour  [ TrJ ] = new_char_J ;
			sol.distanceTou	[ TrJ ] = new_dist_J;
			changerTourSequence(inst, sol , sol.dernClient[ TrJ ] , TrJ);
			sol.dernClient [ TrJ ] = sol.dernClient [ TrI ];
			sol.chargeTour  [ TrI ] = -1;
			sol.dernClient  [ TrI ] = -1;
			sol.dernClient  [ TrI ] = -1;
			sol.premClient  [ TrI ] = -1;
			sol.tournees	[ TrI ] = -1;
			sol.nbrTour_fictif --;
			return true;
			}
			
		}
	}
	return false;
	
}


int _2opt_(Instance& Inst , Solution& Sol)
{
	
	int i , j;
	bool f1 = false , f2 = false;
	int I	, J;

	
	for ( i = 1; i <= Sol.nbrTour ; i++ )
	{
		f1 = false;
		if( Sol.tournees[i] != -1 )
		{
			I = Sol.premClient[i];
			while (!f1)
			{
				for ( j = 1; j <= Sol.nbrTour ; j++ )
				{
					f2 = false;
					if( Sol.tournees[j] != -1 && i != j )
					{
						J = Sol.premClient[j];
						while(!f2)
						{
							if ( I != 0 || J != 0 ){
							printf("(I = %d TrI = %d , J = %d TrJ = %d ) \n",I,i,J,j);
							//Sol.afficher(Inst);
							
							//printf("..\n");
							//sleep(1);
							if(_2Opt(Inst,Sol , I , i , J , j )){return 1;}
							}
						
							if( J == 0){f2 =true;break;}
							
							J = Sol.suivTour[J];
							
						}
					}
				}
				
				if( I == 0){f1 =true;break;}
				I = Sol.suivTour[I];
				//printf("\n");
			}
		}
	}
	return 0;
}





#endif
