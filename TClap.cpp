#include <tclap/CmdLine.h>
#include <string>

using namespace TCLAP;
using namespace std;

int main(int argc, char ** argv) {
  	
  CmdLine cmd("commande");
  
  //Taille de la population
  ValueArg <long unsigned int> population_size("N", "size", "number of individuals", true, 100, "long unsigned int");
  cmd.add(population_size);

  //Durée (en nombre de générations) de la simulation 
  ValueArg <long unsigned int> duration("T", "time", "number of generations", true, 10, "long unsigned int");
  cmd.add(duration);

  //Nombre d’allèles dans la population
  ValueArg <unsigned int> alleles_number("A", "alleles number", "number of alleles in the population", true, 2, "unsigned int");
  cmd.add(alleles_number);
  
  //Fréquences initiales des allèles 
  MultiArg<double> freq("f", "frequences", "initial alleles' frequencies (as fraction of the population)", .8, true,"int" );
  cmd.add(freq);

  //la simulation sera répétée R fois
  ValueArg <unsigned int> repetitions("R", "number of repetions", "simulation will be repeted R times", true, 2, "unsigned int");
  cmd.add(repetitions);
  
  cmd.parse(argc, argv);
  
  if (population_size.getValue() < 1) {
    cerr << "Population size must be strictly positive" << endl;
    return 1;
  }
  
  if (duration.getValue() < 1) {
    cerr << "Simulation duration must be strictly positive" << endl;
    return 1;
  }
  
  if (alleles_number.getValue() < 1) {
    cerr << "Number of alleles must be strictly positive" << endl;
    return 1;
  }
  
  for(auto f : freq) {
	  if (f.getValue() < 0 or f.getValue() > 1)  {
		  cerr << "Frequencies must be between 0 and 1 included" << endl;
		  return 1;
  
   if (repetitions.getValue() < 1) {
    cerr << "Number of repetitions must be strictly positive" << endl;
    return 1;
  }
  
  return 0;
}
