#include <random>
#include <iostream>
#include <vector>
#include <multibinomial.h>

std::vector<double> multibinomial (int N, std::vector<double> f,std::mt19937 rng)
{	
	std::vector<double> new_frequences;
	double mean(N);
	double sum(N);	
	
	for(size_t i(0); i< f.size()-1; ++i) {
			
			double var(f[i]*N);
			
			if(sum !=0) {
		
				std::binomial_distribution<> distribution(mean, var/sum); //pour avoir le chiffres réels
		
				new_frequences.push_back(distribution(rng)); //on transforme en pourcentage
			
				sum -= var;
				mean -= new_frequences[i];
			} else {
				new_frequences.push_back(0.0);
			}
		
	}
	
	double f_last(N);
	for(auto _f : new_frequences) {
		f_last -= _f;
	}
	
	new_frequences.push_back(f_last);
	
	for(auto& fre : new_frequences) {
		fre = fre/N;
	}
	 	
	return new_frequences;
}
