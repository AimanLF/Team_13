#ifndef SIMULATION
#define SIMULATION

#include "population.h"
#include <fstream>

/*! \class Simulation
  This class defines the simulation parameters and constructs all the \ref Population in \ref populations.
  It then runs the simulation and prints the results on \ref terminal, \ref file or both.

  Simulation parameters:
  - \ref endtime : total number of time-steps
  - \ref repetition : total number of simulation (number of populations)
  - \ref populations: vector which contains all simulations of one population
  - \ref terminal : indication to print in terminal or not
  - \ref file : indication to print in file or not
  - \ref output : output to write on file 
 */

class Simulation {
    
public:

/*! 
  Constructor initializes the following variables:
  \param _t (size_t): total number of time-steps
  \param _r (size_t): total number of simulation (number of populations)
  \param _n (size_t): individuals of the _r populations find in \ref populations;
  \param _a (size_t): alleles of the _r populations find in \ref populations;
  \param _terminal (size_t): indication to print in terminal or not
  \param _file (size_t): indication to print in file or not
  \param _f (vector<double>): frequence of the _r populations find in \ref populations; 
  \param _c (vector<string):codon of the _r populations find in \ref populations;
 */
    Simulation(size_t _t, size_t _r, size_t _n, size_t _a, bool _terminal,bool _file,
					const std::vector<double>& _f, const std::vector<std::string>& _c);
	
/*!
  The main operation of this class: runs the simulation through a loop with \ref endtime steps. 
  Each iteration calls \ref Simulation::step and \ref Simulation::print.
  Finaly, print the genetique code of each population \ref Simulation::print_alleles().
 */
	void run();
 
 /*!
  Do one step of the simulation.
  Call \ref Population::step at each iteartion of a loop on all \ref populations
 */
	void step();
	
/*!
  Display of each step of the simulaiton
  Print in \ref terminal with \ref Simulation::print_terminal.
  Or print in \ref file with \ref Simulation::print_file.
  Or print in both in function of input.
  \param t : the index of the step that we have to print.
 */
	void print(int t);
	void print_terminal(int t);
	void print_file(int t);

/*!
  Display of the genetique code of each population
  Print in \ref terminal with \ref Simulation::print_terminal_alleles.
  Or print in \ref file with \ref Simulation::print_file_alleles.
  Or print in both in function of input.
 */
	void printAlleles();
	void print_terminal_alleles(std::string esp);
	void print_file_alleles(std::string esp);
	
/*!
  \return the allelic frequencies of a given population
  \param nbSim: index of the population of interest in \ref populations 
 */	
    std::vector<double> getFreqPop (size_t nbSim) const;

/*!
  \return the total number of time-step 
 */	
    size_t getEndtime() const;
        
/*!
  \return the number of individus in the population
  \param index: index of the population of interest in \ref populations 
 */	    
    size_t getIndividusOfPopulation(size_t index) const;

protected:
	size_t endtime;			
	size_t repetition;	
	std::vector<Population> populations;	
	bool terminal;	
	bool file;
	std::ofstream output;
};

#endif
