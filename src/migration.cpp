#include <cmath>
#include "migration.h"
#include "multibinomial.h"
#include <algorithm>

Migration::Migration(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
					const std::vector<double>& _f, const std::vector<std::string>& _c,
					std::string _matrix)
:Simulation(_t, _r, _n, _a, terminal, file, _f, _c)
{
	matrix = create_matrix(_matrix, _n, _r);
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

void Migration::migrate()  
{
	std::vector<std::vector<double>> populationsInd;
	for (size_t i(0); i < populations.size(); ++i){
		std::vector<double> populationI;
		
		for (size_t j(0); j < populations[i].frequence.size(); ++j)
			populationI.push_back(populations[i].frequence[j] * populations[i].getIndividuals());
		
		populationsInd.push_back(populationI);
	}
	
	for (size_t i(0); i < populationsInd.size(); ++i){
		for (size_t j(0); j < populationsInd.size(); ++j){
			
			if(i!=j){ 
				
				double NumberToMove(round(matrix[i][j] * populations[i].getIndividuals()));
				
				while(NumberToMove > 0){
						int whichAllele = randomUniform(0,(populationsInd[i].size() - 1));
						int toMove = randomUniform(0, std::min(NumberToMove,populationsInd[i][whichAllele])); 
						
						populationsInd[i][whichAllele] -= toMove;
						populationsInd[j][whichAllele] += toMove;
						NumberToMove -= toMove;
				}
			}
		}
	}

	std::vector<double> sommes;
	for (size_t i(0); i < populationsInd.size(); ++i){
		double nbIndividus(0);
		for (size_t j(0); j < populationsInd[i].size(); ++j)
			nbIndividus+=populationsInd[i][j];
		sommes.push_back(nbIndividus);
			
	}
	
	for (size_t i(0); i < populationsInd.size(); ++i){
		for (size_t j(0); j < populationsInd[i].size(); ++j)
			populationsInd[i][j] = populationsInd[i][j]/sommes[i];
	}
	
	for(size_t i(0); i < populations.size(); ++i){
		populations[i].frequence = populationsInd[i];
		populations[i].individuals = sommes[i];
	}
	
}

Matrix Migration::create_matrix(std::string matrix_type, size_t n, size_t r) 
{
	Matrix matrice;
	const double SEUIL(0.7);
		
	if (matrix_type == "star") {

		Ligne ligne1({0});
		for (size_t i(1) ; i < r ; ++i) ligne1.push_back(pick_ratio(n));
		matrice.push_back(ligne1);
		for (size_t k(1) ; k < r ; ++k){
			Ligne ligne({ligne1[k]});
			for (size_t i(1) ; i < r ; ++i) ligne.push_back(0);
			matrice.push_back(ligne);
			}
		}	
	else if (matrix_type == "ring"){
		
		Ligne ligne;
		for (size_t i(0) ; i < r ; ++i) ligne.push_back(0);
		for (size_t i(0) ; i < r ; ++i) matrice.push_back(ligne);
		double ratio1 = pick_ratio(n);
		matrice[1][0] = ratio1, matrice[0][1] = ratio1;
		
		for (size_t p(2) ; p < r ; ++p){
			matrice[p][p-1] = pick_ratio(n);
			matrice[p-1][p] = matrice[p][p-1];
			}
			double ratio = pick_ratio(n);
			matrice[r-1][0] = ratio, matrice[0][r-1] = ratio;
		}	
	else if (matrix_type == "complete"){
		double x(pick_ratio(n));
		for (size_t i(0) ; i < r ; ++i){
			Ligne ligne;
			for (size_t k(0) ; k < r ; ++k){
				if (i == k) ligne.push_back(0);
				else ligne.push_back(x);
				}
				matrice.push_back(ligne);
			}
		}
	
	for (size_t i(0) ; i < r ; ++i){	//normalisation
		double somme(0);
		for (size_t k(0) ; k < r ; ++k) somme += matrice[i][k];
		if (somme >= 1) for (size_t m(0) ; m < r ; ++m) matrice[m][i] /= somme, matrice[i][m] /= somme;
}
	for (auto& ligne : matrice) for (auto& val : ligne) val *= SEUIL; 

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
