#include <tclap/CmdLine.h>
#include <string>


int main(int argc, char ** argv) {
  	
  TCLAP::CmdLine cmd("commande");
  
  //Saisie par l'utilisateur
  TCLAP::ValueArg <std::string> file_name("F", "file name", "File with parameters", false, "", "string");
  cmd.add(file_name);

  //Taille de la population
  TCLAP::ValueArg <size_t> population_size("N", "size", "number of individuals", true, 100, "size_t");
  cmd.add(population_size);

  //Durée (en nombre de générations) de la simulation 
  TCLAP::ValueArg <size_t> duration("T", "time", "number of generations", true, 10, "size_t");
  cmd.add(duration);

  //Nombre d’allèles dans la population
  TCLAP::ValueArg <size_t> alleles_number("A", "alleles number", "number of alleles in the population", true, 2, "size_t");
  cmd.add(alleles_number);
  
  //Fréquences initiales des allèles 
  TCLAP::MultiArg<double> freq("f", "frequences", "frequencies (as fraction of the population)", true, "double" );
  cmd.add(freq);

  //la simulation sera répétée R fois
  TCLAP::ValueArg <size_t> repetitions("R", "number of repetions", "simulation will be repeted R times", true, 2, "size_t");
  cmd.add(repetitions);
  
  cmd.parse(argc, argv);
  
 /* if(file_name.getValue() != "" ) {
	//on lit le fichier
	  	//if la fonction qui lit le ficher renvoit un message d'erreur on utilise les valeurs par défauts
	 } */
	  
  if (population_size.getValue() < 1) {
    std::cerr << "Population size must be strictly positive" << std::endl;
    return 1;
  }
  
  if (duration.getValue() < 1) {
    std::cerr << "Simulation duration must be strictly positive" << std::endl;
    return 1;
  }
  
  if (alleles_number.getValue() < 1) {
    std::cerr << "Number of alleles must be strictly positive" << std::endl;
    return 1;
  }
  
  
  double total_freq(0);
  for(auto f : freq.getValue()) {
		total_freq += f;
	  if (total_freq != 1) {
		   std::cerr << "Sum of frequencies must be equal to 1" << std::endl;
	  
	  if (f < 0 or f > 1)  {
		  std::cerr << "Frequencies must be between 0 and 1 included" << std::endl;
	   
		  
		  return 1;
		}
	  }
  
   if (repetitions.getValue() < 1) {
    std::cerr << "Number of repetitions must be strictly positive" << std::endl;
    return 1;
  }
  
}
  return 0;
}



