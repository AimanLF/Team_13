#include "simulation.h"


Simulation::Simulation(const size_t _t, const size_t _r, size_t _n, size_t _a,
						const std::vector<double>& _f, const std::vector<std::string>& _c)
:endtime(_t), repetition(_r)
{
	for (size_t i(0); i<_r;++i){
		Population pop (_n,_a,_f,_c);
		pops.push_back(pop);
	}
}

void Simulation::run() {
	for (size_t i(0); i<pops.size();++i){
		pops[i].step();
		pops[i].print();
	}
}
