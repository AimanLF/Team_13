#include "simulation.h"
#include <assert.h>
// uncomment to disable assert()
#define NDEBUG 


Simulation::Simulation(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
						const std::vector<double>& _f, const std::vector<std::string>& _c)
:endtime(_t), repetition(_r), term(terminal), fichier(file)
{
	/*double sommefreq(0);
	for (auto freq : _f)
		sommefreq += freq;
	assert(sommefreq == 1);*/
	
	for (size_t i(0); i<_r;++i){
		Population pop (_n,_a,_f,_c);
		populations.push_back(pop);
	}
}

std::vector<double> Simulation:: getFreqPop(size_t numPopu) const{
	return populations[numPopu].getFreq();
}

void Simulation::step() {
	for (size_t i(0); i<populations.size();++i){
		populations[i].step();
	}
}

void Simulation::run() {
	for (size_t t(0); t<endtime; ++t){
		step();
	}
	print();
}

void Simulation::print_term(){
	for (size_t t(0); t<endtime; ++t){
		std::cout << t << "\t" ;
		for (size_t i(0); i<populations.size();++i){
			std::cout << populations[i].getAllelesFreq() << "\t";
		}
	std::cout << std::endl;
	}
	
	for (size_t i(0); i<populations.size();++i){
		std::vector<std::string> popcode;
		popcode = populations[i].getgenetic_code();
		for (auto codon : popcode){
			std::cout << codon << "|";	
		}
		std::cout << "\t";
	}
	std::cout << std::endl;
}

void Simulation::print_fichier(){
	if (output.is_open()){
		if(output.fail()) std::cerr << "ERROR output failed" << std::endl;
		std::ostream *output = &std::cout; // des que je pointe qc ca le cout sur le fichier
		for (size_t t(0); t<endtime; ++t){
			(*output) << t << "\t" ;
			for (size_t i(0); i<populations.size();++i){
				(*output) << populations[i].getAllelesFreq() << "\t";
			}
		(*output) << std::endl;
		}
		
	for (size_t i(0); i<populations.size();++i){
		std::vector<std::string> popcode;
		popcode = populations[i].getgenetic_code();
		for (auto codon : popcode){
			(*output) << codon << "|";	
		}
		std::cout << "\t";
	}
	std::cout << std::endl;
	}
	if (output.is_open()) output.close();
}


void Simulation::print() {
	if (term) {
		print_term();
		if (fichier){
			print_fichier();
		}
	} else if (fichier) {
		print_fichier();
	}
}
