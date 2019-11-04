#include <random>
#include <iostream>

//Seulement un cpp, une méthode
//vector multibinomial(int N, vector 
//return nouveau tableau de fréquences

//avec f tableau de fréquence actuelles, N nombre d'individus



std::vector<double> multinomiale (int N, std::vector<double> f)
{
	std::vector<double> new_frequences;
	
	for(int i(0); i<N ; ++i) {
		double mean(N);
		double var(f[i]);
		double tmps(N);
		
		for(int j(0); j<i; ++j) {
			mean -= new_frequences[j];
			tmps -=f[j];
		}
		
		var = var/tmps;
		
		std::binomial_distribution<double> distribution(mean, var);
		new_frequences[i] = distribution(rng);
	}
	return new_frequences;
}

/*il faut qu'on met un random generateur qqpart
 * donc dans quels fichiers si on s'en sert plusieurs fois ?
 */
