#include <cmath>
#include "migration.h"

Migration::Migration(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
					const std::vector<double>& _f, const std::vector<std::string>& _c,
					std::string _matrix)
:Simulation(_t, _r, _n, _a, terminal, file, _f, _c)
{
	matrix = create_matrix(_matrix, _n);
}

void Migration::run()
{
	size_t end = getEndtime() +1;
	for (size_t t(0); t< end; ++t){
		print(t);
		step();
		// use migrate(...) dans une boucle;
	} 
	printAlleles();
}

void Migration::migrate(const Matrix& matrix)   // fait migrer toutes les populations de la simulation
{
   for(size_t i(0); i < populations.size(); ++i) {
	   
	   /*vector<double> populationI;
	   for(size_t k(0); k < populations[i].frequence.size(); ++k)
				populationI.push_back(populations[i].frequence * populations[i].getIndividuals());*/
	   
	   for(size_t j(0); j < populations.size(); ++j) {
			
			if(i == j) { // exclure auto transfert
				break;
			}
			
			/*vector<double> populationJ;
			for(size_t k(0); k < populations[k].frequence.size(); ++k)
				populationI.push_back(populations[j].frequence * populations[j].getIndividuals());*/
			
			//Determine nb à faire migrer
			size_t NumberToMove( ceil(matrix[i][j] * populations[i].getIndividuals()));
			
			/*//Choisi le nb d'individus à faire migrer pour une allèle spécifique + bouge individus
			while(NumberToMove > 0){
				for (size_t y(0); y < populationI.size(); ++y){
					size_t toMoveAlleleI  //Nb aléatoire entre 0 et min(populationI[y],NumberToMove)
					populationI[y] -= toMoveAlleleI;
					populationJ[y] += toMOveAlleleI;
				}
			}
			
			//Recalculer les fréquences 
			size_t sommeI(0);
			size_t sommeJ(0);
			for (auto ind : populationI)
				sommeI += ind;
			for (auto ind : populationJ)
				sommeJ += ind;
			
			for(auto ind : populationI)
				ind = ind/sommeI;
			for(auto ind : populationJ)
				ind = ind/sommeJ;
			
			populations[i].frequence = populationI;
			populations[i].individuals = sommeI;
			populations[j].frequence = populationJ;
			populations[j].individuals = sommeJ;*/
				
				
			
			// ajoute à la pop d'arrivée j les fréquences de la pop de départ i comprises entre 0 et ration * taille de la pop i
			populations[j].frequence.insert(populations[j].frequence.end(), populations[i].frequence.begin(), populations[i].frequence.begin() + NumberToMove);
			// Effacer frequences correspondantes dans population i 
			populations[i].frequence.erase(populations[i].frequence.begin(), populations[i].frequence.begin() + NumberToMove);
			
			// Same avec genetic code
			populations[j].genetic_code.insert(populations[j].genetic_code.end(), populations[i].genetic_code.begin(), populations[i].genetic_code.begin() + NumberToMove);
			populations[i].genetic_code.erase(populations[i].genetic_code.begin(), populations[i].genetic_code.begin() + NumberToMove);
	   }
   }
}

Matrix Migration::create_matrix(std::string matrix_type, size_t n) 
{
	Matrix matrice;
		
	if (matrix_type == "star") {

		Ligne ligne1({0});
		for (size_t i(1) ; i < n ; ++i) ligne1.push_back(pick_ratio());
		matrice.push_back(ligne1);				// 1ère ligne ok
		Ligne ligne({pick_ratio()});
		for (size_t i(1) ; i < n ; ++i) ligne.push_back(0);		//création des autres lignes
		
		for (size_t k(1) ; k < n ; ++k) matrice.push_back(ligne);	//ajout des autres lignes
		}
			
	else if (matrix_type == "ring"){

		for (size_t i(0) ; i < n ; ++i){
			Ligne ligne;
			for (size_t k(0) ; k < n ; ++k){
				if (k == i+1 or k == i-1) ligne.push_back(pick_ratio());
				else ligne.push_back(0);
				}
			matrice.push_back(ligne);
			}
			matrice[0][n-1] = pick_ratio();
			matrice[n-1][0] = pick_ratio();
		}
			
	else if (matrix_type == "complete"){
		for (size_t i(0) ; i < n ; ++i){
			Ligne ligne;
			for (size_t k(0) ; k < n ; ++k){
				if (i == k) ligne.push_back(0);
				else ligne.push_back(pick_ratio());
			}
				matrice.push_back(ligne);
			}
		}
	
	return matrice;
}

void Migration::print_matrix() const
{
	for (auto ligne : matrix){
		std::cout << " (";
		for (auto num : ligne) std::cout << " " << num;
		std::cout << " )" << std::endl;
	}
	std::cout << std::endl;
}

double Migration::pick_ratio()
{
	return 0.0;
	}
