#include "population.h"
#include <string>
#include <fstream>

/*! \class Simulation
  This class defines the simulation parameters and constructs all the \ref Population in \ref pops.
  It then runs the simulation and prints the results to the output streams.

  Simulation parameters:
  - \ref endtime : total number of time-steps
  - \ref repetition : total number of simulation
  - \ref populations: vector which contains all simulations of one population
 */

class Simulation {
    
public:

/*! 
  Default constructor initializes the following variables:
  \param _t (size_t): duration of simulation (number of time-steps)
  \param _r (size_t): total number of simulation 
  \param _n (size_t): individuals of the _r populations find in \ref pops;
  \param _a (size_t): alleles of the _r populations find in \ref pops;
  \param _f (vector<double>): frequence of the _r populations find in \ref pops; 
  \param _c (vector<string):codon of the _r populations find in \ref pops;
 */
    Simulation(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
					const std::vector<double>& _f, const std::vector<std::string>& _c);
	
/*!
  The main operation of this class: runs the simulation through a loop with \ref endtime steps. 
  Each iteration calls \ref Population::step and \ref Population::print
 */
	void step();
	void run();
	void print_term(int t);
	void print_fichier(int t);
	void print(int t);
	void print_term_alleles();
	void print_fichier_alleles();
	void printAlleles();
	
	size_t getEndtime();

/*!
  Return the allelic frequencies of a given population
 */	
    std::vector<double> getFreqPop (size_t numPopu) const;

protected:
	std::vector<Population> populations;
	size_t endtime;			
	size_t repetition;		
	bool term;	
	bool fichier;
	std::ofstream output;
};
