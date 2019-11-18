#include <random>
#include <iostream>
#include <vector>
#include <multibinomial.h>

std::vector<double> multibinomial (int N, std::vector<double> f,std::mt19937 rng)
{
	std::vector<double> new_frequences;
	
	for(size_t i(0); i< f.size()-1; ++i) {
		if(f[i] == 0 ) {
			new_frequences.push_back(0.0);
		} else {
			double mean(N);
			double var(f[i]);
			double tmps(N);
		
			for(size_t j(0); j<i; ++j) {
				mean -= new_frequences[j];
				tmps -=f[j];
			}
		
			var = var/tmps;
		
			std::binomial_distribution<> distribution(mean*100, var); //pour avoir le chiffres réels
		
			new_frequences.push_back(distribution(rng)*0.01); //on transforme en pourcentage
		}
	}
	
	double f_last(1);
	for(auto f : new_frequences) {
		f_last -= f;
	}
	
	new_frequences.push_back(f_last);
	
	return new_frequences;
}
