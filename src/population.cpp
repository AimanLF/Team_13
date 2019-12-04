#include <algorithm>
#include "population.h"
#include "multibinomial.h"
	
void Population:: step(){
	frequence = multibinomial(individuals, frequence);
}

void Population::sort(){
	std::vector<std::string> new_genetic_code(genetic_code);
	std::sort(new_genetic_code.begin(),new_genetic_code.end());
	std::vector<int>index;
	
	for (size_t i(0); i<genetic_code.size(); ++i){
		std::string codon = genetic_code[i];
		std::vector<std::string>::iterator it = std::find(new_genetic_code.begin(), new_genetic_code.end(), codon);
		if (it != genetic_code.end())
			  index.push_back(std::distance(new_genetic_code.begin(), it));
	}
	
	std::vector<double> new_frequence(frequence.size());
	for (size_t i(0); i<index.size(); ++i){
		 int nb=index[i];
		 new_frequence[nb]=frequence[i];
	 }
	 
	 genetic_code=new_genetic_code;
	 frequence=new_frequence;
}

std::string Population::getAllelesFreq() const{
	std::string alleles;
	for (auto f : frequence)
		alleles += std::to_string(f) + '|';	
	alleles = alleles.substr(0, alleles.length() -1);
	return alleles;
}
std::string Population::getCodons() const{
	std::string code;
	for (auto codon : genetic_code)
		code += codon + '|';	
	code = code.substr(0, code.length() -1);
	return code;
}

std::vector<double> Population::getFreq() const {
	return frequence;
}

std::size_t Population::getIndividuals() const {
	return individuals;
}
