#include "population.h"
#include <iostream>
//#include multibinomial

Population::Population(size_t n_, size_t a_, const std::vector<double> &frequence_, const std::vector<std::string> &codons_) 
: n(n_),a(a_),frequence(frequence_), codons(codons_){}

void Population::print() const{
	for (auto f : frequence){
		std::cout << f << '|';}
}

void Population:: step(){
	frequence = multibinomial (n, frequence);
}
