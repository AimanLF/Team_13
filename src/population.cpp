#include "population.h"
#include "multibinomial.cpp"
	
void Population:: step(){
	frequence = multibinomial(individuals, frequence);
}

void Population::print() const{
	for (auto f : frequence){
		std::cout << f << '|';}
}
