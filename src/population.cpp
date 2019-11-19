#include "population.h"
#include "multibinomial.h"
#include <string>

std::random_device rd;
std::mt19937 Population::rng = std::mt19937(rd());
	
void Population:: step(){
	frequence = multibinomial(individuals, frequence, rng);
}

std::string Population::getAllelesFreq() const{
	std::string alleles ("|");
	for (auto f : frequence){
		alleles = alleles + std::to_string(f) + '|';	
	}
	return alleles;
}

std::vector<double> Population::getFreq() const {
	return frequence;
}


std::vector<std::string> Population::getgenetic_code() const {
	return genetic_code;
}
