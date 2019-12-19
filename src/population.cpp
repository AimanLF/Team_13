#include <algorithm>
#include "population.h"
#include "multibinomial.h"
	
void Population:: step()
{
	frequence = multibinomial(individuals, frequence);
}

std::string Population::getAllelesFreq() const
{
	std::string alleles;
	for (auto f : frequence)
		alleles += std::to_string(f) + '|';	
	alleles = alleles.substr(0, alleles.length() -1);
	return alleles;
}
std::string Population::getCodons() const
{
	std::string code;
	for (auto codon : genetic_code)
		code += codon + '|';	
	code = code.substr(0, code.length() -1);
	return code;
}

std::vector<double> Population::getFreq() const 
{
	return frequence;
}

std::size_t Population::getIndividuals() const 
{
	return individuals;
}
