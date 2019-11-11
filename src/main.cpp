#include <tclap/CmdLine.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


int main(int argc, char ** argv) {
	
	//try{}
	
  TCLAP::CmdLine cmd("commande");
  
  //Saisie par l'utilisateur
  TCLAP::ValueArg <std::string> file_name("f", "file name", "File with parameters", false, "", "string");
  cmd.add(file_name);
  
  //Affichage terminal et/ou fichier
  TCLAP::ValueArg <bool> terminal("e", "terminal", "Print results in terminal", false, "", "bool");
  cmd.add(terminal);
  TCLAP::ValueArg <bool> print_file("i", "print_file", "Print results in a file", false, "", "bool");
  cmd.add(print_file);

  //Taille de la population
  TCLAP::ValueArg <size_t> population_size("n", "size", "number of individuals", false, 100, "size_t");
  cmd.add(population_size);

  //Durée (en nombre de générations) de la simulation 
  TCLAP::ValueArg <size_t> duration("t", "time", "number of generations", false, 10, "size_t");
  cmd.add(duration);

  //Nombre d’allèles dans la population
  TCLAP::ValueArg <size_t> alleles_number("a", "alleles number", "number of alleles in the population", false, 2, "size_t");
  cmd.add(alleles_number);
  
  //Fréquences initiales des allèles 
  TCLAP::MultiArg<double> freq("p", "frequences", "frequencies (as fraction of the population)", false, "double" );
  cmd.add(freq);

  //la simulation sera répétée R fois
  TCLAP::ValueArg <size_t> repetitions("r", "number of repetions", "simulation will be repeted R times", false, 2, "size_t");
  cmd.add(repetitions);
  
  //positions le long de la séquence qui déterminent les allèles	
  TCLAP::MultiArg<size_t> markers("m", "markers", "alleles' positions on the sequence", false, "size_t" );
  cmd.add(markers);  	
  
  cmd.parse(argc, argv);
  
  if(file_name.getValue() != "" ) {
	//on lit le fichier 
	try {
        std::ifstream confstr(file_name.getValue());
      
        if (confstr.is_open()) {
            std::string item, key, line;
            double value;
	
				while (std::getline(confstr, line)) {
		   
					// This removes all spaces from the string
					line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
					
					std::stringstream ss(line);
					std::getline(ss, item, ';');
					key = item.substr(0, 4);
					std::transform(key.begin(), key.end(), key.begin(), ::tolower);
				   
						std::getline(ss, item, ';');
						while (std::getline(ss, item, ';')) {
							size_t split = item.find('=');
							key = item.substr(0, split);
							std::transform(key.begin(), key.end(), key.begin(), ::tolower);
							value = stod(item.substr(split+1));
							if (key[0] == 'e') {
								bool terminal(value);
							} else if (key[0] == 'i') {
								bool print_file(value);
							} else if (key[0] == 'n') {
								size_t population_size(value);
							} else if (key[0] == 't') {
								size_t duration(value);
							} else if (key[0] == 'a') {
								size_t alleles_number(value);
							} else if (key[0] == 'p') {
								double freq(value);
							} else if (key[0] == 'r') {
								 size_t repetitions(value);
							} else if (key[0] == 'm') {
								size_t markers(value);
							}
						}
					}
					 
					  std::stringstream ss(line);
			} else {
				throw("Could not open configuration file " + file_name.getValue());
			}	
				
		} 
		
	catch(std::string const& e) {
		// on utilise les valeurs par défauts
	}
  } 
	  
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

	/*
	catch() {}  //erreurs de tout le monde
*/


  return 0;
}

    
