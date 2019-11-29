#include "population.h"
#include "multibinomial.h"
#include <string>

	
void Population:: step(){
	frequence = multibinomial(individuals, frequence);
}

std::string Population::getAllelesFreq() const{
	std::string alleles;
	for (auto f : frequence){
		alleles += std::to_string(f) + '|';	
	}
	alleles = alleles.substr(0, alleles.length() -1);
	return alleles;
}

std::vector<double> Population::getFreq() const {
	return frequence;
}

std::vector<std::string> Population::getgenetic_code() const {
	return genetic_code;
}

std::size_t Population::getIndividuals() const {
	return individuals;
}
