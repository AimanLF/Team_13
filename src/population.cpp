#include "population.h"
#include "multibinomial.cpp"
#include <string>
	
void Population:: step(){
	frequence = multibinomial(individuals, frequence);
}

std::string Population::getAllelesFreq const{
	std::string alleles ('|');
	for (auto f : frequence){
		alleles = alleles + f + '|';	
	}
	return alleles;
}

std::vector<double> getAllelesFreq() const {
	return frequence;
}
