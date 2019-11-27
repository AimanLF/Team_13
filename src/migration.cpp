#include <migration.h>
#include <iostream>
#include <vector>
#include <string>

Migration::Migration(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
					const std::vector<double>& _f, const std::vector<std::string>& _c,
					std::string _matrix, double _migration_ratio)
:Simulation(_t, _r, _n, _a, terminal, file, _f, _c)
{
	matrix = create_matrix(_matrix, _n, _migration_ratio);
}

void Migration::run()
{
	size_t end = getEndtime();
	for (size_t t(0); t< end; ++t){
		print(t+1);
		step();
		// use migrate(...) dans une boucle;
	} 
	printAlleles();
}

void Migration::migrate(Population& pop1, Population& pop2, Matrix matrix)
{
// in progress ...
}

Matrix Migration::create_matrix(std::string matrix, size_t n, double migration_ratio){
Matrix matrice;
		
	if (matrix == "star"){
			
		Ligne ligne1({0});
		for (size_t i(1) ; i < n ; ++i) ligne1.push_back(migration_ratio);
		matrice.push_back(ligne1);				// 1ère ligne ok
		Ligne ligne({migration_ratio});
		for (size_t i(1) ; i < n ; ++i) ligne.push_back(0);		//création des autres lignes
		
		for (size_t k(1) ; k < n ; ++k) matrice.push_back(ligne);	//ajout des autres lignes
		return matrice;
		}
			
	else if (matrix == "ring"){

		for (size_t i(0) ; i < n ; ++i){
			Ligne ligne;
			for (size_t k(0) ; k < n ; ++k){
				if (k == i+1 or k == i-1) ligne.push_back(migration_ratio);
				else ligne.push_back(0);
				}
			matrice.push_back(ligne);
			}
			matrice[0][n-1] = migration_ratio;
			matrice[n-1][0] = migration_ratio;
			return matrice;
		}
			
	else if (matrix == "complete"){
		for (size_t i(0) ; i < n ; ++i){
			Ligne ligne;
			for (size_t k(0) ; k < n ; ++k){
				if (i == k) ligne.push_back(0);
				else ligne.push_back(migration_ratio);
				}
				matrice.push_back(ligne);
			}
			return matrice;
		}
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
