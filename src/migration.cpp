#include <cmath>
#include "migration.h"
#include "multibinomial.h"
#include <algorithm>

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
		//migrate();
	} 
	printAlleles();
}

void Migration::migrate()   // fait migrer toutes les populations de la simulation
{
   for(size_t i(0); i < populations.size(); ++i) {
	   std::vector<double> populationI;
	   double sommeI(populations[i].getIndividuals());
	   
	   for(size_t k(0); k < populations[i].frequence.size(); ++k)
				populationI.push_back(populations[i].frequence[k] * sommeI);
	   
	   for(size_t j(0); j < populations.size(); ++j) {
			
			if(i == j) { // exclure auto transfert
				break;
			}
			
			std::vector<double> populationJ;
			double sommeJ(populations[j].getIndividuals());
			for(size_t k(0); k < populations[j].frequence.size(); ++k)
				populationJ.push_back(populations[j].frequence[k] *sommeJ);
			
			//Determine nb à faire migrer
			double NumberToMove(round(matrix[i][j] * sommeI));
			
			//Choisi le nb d'individus à faire migrer pour une allèle spécifique + bouge individus
			while(NumberToMove > 0){
					int whichAllele = randomUniform(0,(populationI.size() - 1));
					int toMoveAlleleI = randomUniform(0, std::min(NumberToMove,populationI[whichAllele])); 
					
					populationI[whichAllele] -= toMoveAlleleI;
					sommeI -= toMoveAlleleI;
					populationJ[whichAllele] += toMoveAlleleI;
					sommeJ += toMoveAlleleI;
					NumberToMove -= toMoveAlleleI;
			}
			
			//Recalculer les fréquences 
			for(auto& ind : populationJ)
				ind = ind/sommeJ;
				
			populations[j].frequence = populationJ;
			populations[j].individuals = sommeJ;
		
	   }
	   std::cout << sommeI << std::endl;
	   if(sommeI > 0){
		   for(auto& ind : populationI)
				ind = ind/sommeI;
		}
		for(auto& ind : populationI)
			std::cout << ' ' << ind << std::endl;
		std::cout << std::endl;
			
		populations[i].frequence = populationI;
		populations[i].individuals = sommeI;
   }
}

Matrix Migration::create_matrix(std::string matrix_type, size_t n) 
{
	Matrix matrice;
		
	if (matrix_type == "star") {

		Ligne ligne1({0});
		for (size_t i(1) ; i < n ; ++i) ligne1.push_back(pick_ratio(n));
		matrice.push_back(ligne1);
		for (size_t k(1) ; k < n ; ++k){
			Ligne ligne({ligne1[k]});
			for (size_t i(1) ; i < n ; ++i) ligne.push_back(0);
			matrice.push_back(ligne);
			}
		}	
	else if (matrix_type == "ring"){
		
		Ligne ligne;
		for (size_t i(0) ; i < n ; ++i) ligne.push_back(0);
		for (size_t i(0) ; i < n ; ++i) matrice.push_back(ligne);
		double ratio1 = pick_ratio(n);
		matrice[1][0] = ratio1, matrice[0][1] = ratio1;
		
		for (size_t p(2) ; p < n ; ++p){
			matrice[p][p-1] = pick_ratio(n);
			matrice[p-1][p] = matrice[p][p-1];
			}
			double ratio = pick_ratio(n);
			matrice[n-1][0] = ratio, matrice[0][n-1] = ratio;
		}	
	else if (matrix_type == "complete"){
		double x(pick_ratio(n));
		for (size_t i(0) ; i < n ; ++i){
			Ligne ligne;
			for (size_t k(0) ; k < n ; ++k){
				if (i == k) ligne.push_back(0);
				else ligne.push_back(x);
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

double Migration::pick_ratio(int n)
{
	double val = randomUniform(1,n-1);
	return val/n;
}
