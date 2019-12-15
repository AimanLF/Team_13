#include <assert.h>
#include "simulation.h"

Simulation::Simulation(size_t _t, size_t _r, size_t _n, size_t _a, bool _terminal,bool _file,
						const std::vector<double>& _f, const std::vector<std::string>& _c)
:endtime(_t), repetition(_r), terminal(_terminal), file(_file), output("test.txt")
{
	for (size_t i(0); i<_r;++i){
		Population pop (_n,_a,_f,_c);
		populations.push_back(pop);
	}	
}

void Simulation::step() {
	for (size_t i(0); i<populations.size();++i)
		populations[i].step();
}

void Simulation::run() {
	for (size_t t(0); t<endtime +1; ++t){
		print(t);
		step();
	} 
	printAlleles();
}

void Simulation::print(int t) {
	if (terminal) print_terminal(t);
	if (file) print_file(t);
}

void Simulation::print_terminal(int t){
	std::cout << t << "\t" ;
	for (size_t i(0); i<populations.size();++i)
		std::cout << populations[i].getAllelesFreq() << "\t";
	std::cout << std::endl;
}


void Simulation::print_file(int t){
	std::ostream *_output = &std::cout; 
	if(output.fail()) throw ("ERROR output failed");
	if (output.is_open()) _output = &output;
	(*_output) << t << "\t" ;
	for (size_t i(0); i<populations.size();++i)
		(*_output) << populations[i].getAllelesFreq() << "\t";
	(*_output) << std::endl;
}


void Simulation::printAlleles(){
	if (terminal) print_terminal_alleles();
	if (file) print_file_alleles();
}

void Simulation:: print_terminal_alleles(){
	std::string espace;
	size_t a=getFreqPop(0).size()+1;
	while (a > 0){
		espace += "\t";
		--a;
	}
	std::cout <<  "\t";
	for (size_t i(0); i<populations.size();++i)
		std::cout << populations[i].getCodons() << espace;
	std::cout << std::endl;
}

void Simulation::print_file_alleles(){
	std::ostream *_output = &std::cout; 
	if (output.is_open()) _output = &output;
	if(output.fail()) throw ("ERROR output failed");
	(*_output)<< "\t";
	for (size_t i(0); i<populations.size();++i)
		(*_output) << populations[i].getCodons() << "\t";
	(*_output) << std::endl;
	if (output.is_open()) output.close();
}
		
std::vector<double> Simulation:: getFreqPop(size_t nbSim) const{
	assert(populations.size() > nbSim);
	return populations[nbSim].getFreq(); 
}

size_t Simulation::getEndtime() const{ 
	return endtime; 
}


size_t Simulation::getIndividusOfPopulation(size_t index) const{
	return populations[index].getIndividuals();
}
