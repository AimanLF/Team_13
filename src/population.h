#include <string>
#include <vector>
#include <iostream>
#include <random>

/*! \class Population
  A population is a number of \ref individuals with each a number of \ref alleles
  
   Population parameters:
  - \ref individuals : total number of individuals
  - \ref alleles : total number of alleles
  - \ref frenquence : the initial frequencies
  - \ref genetic_code : list of the different codons
  - \ref rng : random generator of all the populations (static)
 */

class Population{

public :

/*! 
  Default constructor initializes the following variables:
  \param _n (size_t): total number of individuals
  \param _a (size_t): total number of alleles 
  \param _f (vector<double>): frequencies of different alleles
  \param _c (vector<string>): list of the different codons
 */
	Population(size_t _n, size_t _a, const std::vector<double>& _f, const std::vector<std::string>& _c)
	:individuals(_n), alleles(_a), frequence(_f), genetic_code(_c)
	{
		std::random_device rd;
		rng = std::mt19937(rd());
	};
		
/*! 
  Performs one time-step of the simulation, update the population with new frenquienies of alleles
 */
	void step();

/*! 
  Return a string of the alleles frenquencies.
*/
	std::string getAllelesFreq() const;
	
	std::vector<double> getAllelesFreq() const;
private :
	size_t individuals; 
	size_t alleles; 
	std::vector<double> frequence; 
	std::vector<std::string> genetic_code; 
	static std::mt19937 rng;
};
