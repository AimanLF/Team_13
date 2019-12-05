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
		migrate();
	} 
	printAlleles();
}

void Migration::migrate()   // fait migrer toutes les populations de la simulation
{
	//Transforme les tableaux de fréquence en tableaux d'individus
	std::vector<std::vector<double>> populationsInd;
	for (size_t i(0); i < populations.size(); ++i){
		std::vector<double> populationI;
		
		for (size_t j(0); j < populations[i].frequence.size(); ++j)
			populationI.push_back(populations[i].frequence[j] * populations[i].getIndividuals());
		
		populationsInd.push_back(populationI);
	}
	
	for (size_t i(0); i < populationsInd.size(); ++i){
		for (size_t j(0); j < populationsInd.size(); ++j){
			
			if(i==j) //pas d'auto transfert
				break;
			
			//Determine nb à faire migrer
			std::cout << matrix[i][j] << std::endl;
			double NumberToMove(round(matrix[i][j] * populations[i].getIndividuals()));
			
			//Choisi le nb d'individus à faire migrer pour une allèle spécifique + bouge individus
			while(NumberToMove > 0){
					int whichAllele = randomUniform(0,(populationsInd[i].size() - 1));
					int toMove = randomUniform(0, std::min(NumberToMove,populationsInd[i][whichAllele])); 
					
					populationsInd[i][whichAllele] -= toMove;
					populationsInd[j][whichAllele] += toMove;
					NumberToMove -= toMove;
			}
		}
	}
	
	//Recalcule les fréquences
	std::vector<double> sommes;
	for (size_t i(0); i < populationsInd.size(); ++i){
		double nbIndividus(0);
		for (size_t j(0); j < populationsInd[i].size(); ++j)
			nbIndividus+=populationsInd[i][j];
		sommes.push_back(nbIndividus);
		
		if(nbIndividus == populations[i].getIndividuals())
			std::cout << "Yeah !" << std::endl;
			
	}
	
	for (size_t i(0); i < populationsInd.size(); ++i){
		for (size_t j(0); j < populationsInd[i].size(); ++j)
			populationsInd[i][j] = populationsInd[i][j]/sommes[i];
	}
	
	for(size_t i(0); i < populations.size(); ++i){
		populations[i].frequence = populationsInd[i];
		std::cout<< populations[i].individuals << '|' << sommes[i] << std::endl;
		//populations[i].individuals = sommes[i];
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
