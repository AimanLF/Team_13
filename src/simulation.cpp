#include "simulation.h"


Simulation::Simulation(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
						const std::vector<double>& _f, const std::vector<std::string>& _c)
:endtime(_t), repetition(_r), term(terminal), fichier(file), output("test.txt")
{
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
		print(t+1);
		step();
	} 
	printAlleles();
}

void Simulation::print_term(int t){
	std::cout << t << "\t" ;
	for (size_t i(0); i<populations.size();++i){
			std::cout << populations[i].getAllelesFreq() << "\t";
		}
	std::cout << std::endl;
}


void Simulation::print_fichier(int t){
	std::ostream *_output = &std::cout; 
	if (output.is_open()) _output = &output;
	if(output.fail()) std::cerr << "ERROR output failed" << std::endl;
	(*_output) << t << "\t" ;
	for (size_t i(0); i<populations.size();++i){
		(*_output) << populations[i].getAllelesFreq() << "\t";
	}
	(*_output) << std::endl;
	//if (output.is_open()) output.close();
}


void Simulation::print(int t) {
	if (term) print_term(t);
	if (fichier) print_fichier(t);
}

void Simulation::printAlleles(){
	if (term) print_term_alleles();
	if (fichier) print_fichier_alleles();
		}


void Simulation:: print_term_alleles(){
	for (size_t i(0); i<populations.size();++i){
		std::vector<std::string> popcode;
		popcode = populations[i].getgenetic_code();
		std::cout << "\t";
		for (auto codon : popcode){
			std::cout << codon << "|";	
		}
		std::cout << "\t";
	}
	std::cout << std::endl;
}

void Simulation::print_fichier_alleles(){
	std::ostream *_output = &std::cout; 
	if (output.is_open()) _output = &output;
	if(output.fail()) std::cerr << "ERROR output failed" << std::endl;
	for (size_t i(0); i<populations.size();++i){
		std::vector<std::string> popcode;
		popcode = populations[i].getgenetic_code();
		(*_output)  << "\t";
		for (auto codon : popcode){
			(*_output)  << codon << "|";	
		}
		(*_output)  << "\t";
	}
	(*_output)  << std::endl;
	if (output.is_open()) output.close();
}
