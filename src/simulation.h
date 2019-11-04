#include "population.h"

/*! \class Simulation
  This is the main class. 
  It manages user inputs, defines the simulation parameters and constructs the \ref Population \ref pop.
  It then runs the simulation and prints the results to the output streams.
  These streams can be files with names based on the string \ref output with a suffix.

  Simulation parameters:
  - \ref endtime : total number of time-steps
  - \ref repetition : total number of simulation
 */

class Simulation {
    
public:

/*! 
  Default constructor initializes the following variables:
  \param _t (size_t): duration of simulation (number of time-steps)
  \param _r (size_t): total number of simulation 
 */
    Simulation(const size_t _t, const size_t _r, size_t _n, size_t _a, 
					const std::vector<double>& _f, const std::vector<std::string>& _c);
	
/*!
  The main operation of this class: runs the simulation through a loop with \ref endtime steps. 
  Each iteration calls \ref Population::step and \ref Population::print if it is usefull to write out the results. 
 */
    void run();

private:
	std::vector<Population> pops;
	size_t endtime;			
	size_t repetition;		
};
