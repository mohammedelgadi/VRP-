
#include "instance.hpp"


Instance::Instance(std::string fileName)
{
	//  CUST NO.   XCOORD.   YCOORD.    DEMAND   READY TIME   DUE DATE   SERVICE TIME
	
	std::string	ligne;
	
	std::stringstream ss;
	
	int		word,
			nbrClient	= 0; //pour ne pas compter le dépot
	
	std::ifstream file(fileName.c_str());
	
	if ( !file )
	{
		std::cerr << "erreur ouverture" << std::endl;
	}
	
	getline ( file , ligne );
	ss << ligne;
	
	ss >> nomInstance; 
	getline ( file , ligne );
	getline ( file , ligne );
	
	getline ( file , ligne );

	
	file >> word;
	
	file >> cap;
	
	
	getline ( file , ligne );
	getline ( file , ligne );
	getline ( file , ligne );
	getline ( file , ligne );
	
	getline ( file , ligne );

	

	while ( !file.eof())
	{
		Client client;
		nbrClient ++;
			
		file >> client.id;
		
		file >> client.x;
		
		file >> client.y;
		
		file >> client.d_i;
		
		file >> client.a_i;
		
		file >> client.b_i;
		
		file >> client.s_i;
		
		client.date_ptard = client.b_i - client.s_i;
		
		clients.push_back ( client );

	}
	
	clients.pop_back();
	nbrClient --;
	
	std::cout  << "NBR CLIENT " << nbrClient << std::endl;
	this->nbrClient = nbrClient;
	
	matDistance = new float * [ nbrClient ];
	* matDistance = new float [ nbrClient * nbrClient];
	
    for(int i = 0 ; i < nbrClient; i++)
    {
      matDistance[i] = *matDistance + i*nbrClient;
    }

	for(int i = 0 ; i < nbrClient ; i++)
	{
		for(int j = 0 ; j < nbrClient ; j++)
		{
			matDistance[i][j] = std::sqrt( (clients.at(i).x - clients.at(j).x)*(clients.at(i).x - clients.at(j).x) + (clients.at(i).y - clients.at(j).y)*(clients.at(i).y - clients.at(j).y) );
			
		}
	}
	
}


void Instance::afficher()
{
	for(int i = 0 ; i < nbrClient ; i++)
	{
		for(int j = 0 ; j < nbrClient ; j++)
		{
			std::cout << matDistance[i][j] << "\t" ;
		}
		std::cout << "\n";
	}
}


