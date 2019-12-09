#ifndef MIGRATION
#define MIGRATION

#include "simulation.h"

/*! \class Migration
  This class herited from Simulation, a extension is added, the individuals now migrate from their population to another. 
  The migration can be represented as a complete, star or ring network.
  Migration parameters:
  - \ref matrix : Hold the rates, the fraction of population no i that is moving to no j at each generation
 */

typedef std::vector<std::vector<double>> Matrix;
typedef std::vector<double> Ligne;

class Migration : public Simulation
{
public:
/*! 
  Constructor initializes the following variables:
  \param all the parameters from Simulation 
  \param matrix : the matrix is initialized using the create_matrix function, according to the type of the matrix (complete, star or ring)
 */
 
	Migration(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
				const std::vector<double>& _f, const std::vector<std::string>& _c,
				std::string _matrix);
/*!
  The main operation of this class: runs the simulation through a loop with \ref endtime steps and make the populations migrate. 
  Each iteration calls \ref Simulation::step, \ref Simulation::print and \ref Migration::migrate.
  Finaly, print the genetique code of each population \ref Simulation::print_alleles().
 */			
	void run(); 
/*!
  Do one step of migration of the simulation.
 */
	void migrate();	// fait migrer toutes les populations de la simulation
/*!
  Display the matrix of the simulation
 */
	void print_matrix() const;
/*!
  Create a matrix according to his type(complete, star or ring)
 */
	static Matrix create_matrix(std::string matrix, size_t n); 
/*!
  Pick one or more rate of the matrix
 */
	static double pick_ratio(int n);
private:
	Matrix matrix;
};

#endif
