#include <tclap/CmdLine.h>
#include "read_fasta.h"
#include "simulation.h"
#include "migration.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

int main(int argc, char ** argv) {
	
	try {
	
	  TCLAP::CmdLine cmd("commande");
  
	  //Saisie par l'utilisateur
	  TCLAP::ValueArg <std::string> file_name("f", "file_name", "File with parameters", false, "string");
	  cmd.add(file_name);
	  
	  //Affichage terminal et/ou fichier
	  TCLAP::ValueArg <bool> terminal("e", "terminal", "Print results in terminal", false, "", "bool");
	  cmd.add(terminal);
	  TCLAP::ValueArg <bool> print_file("i", "print_file", "Print results in a file", false, "", "bool");
	  cmd.add(print_file);

	  //Taille de la population
	  TCLAP::ValueArg <int> population_size("n", "size", "number of individuals", false, 100, "int");
	  cmd.add(population_size);

	  //Durée en nombre de générations 
	  TCLAP::ValueArg <int> duration("t", "time", "number of generations", false, 10, "int");
	  cmd.add(duration);

	  //Fréquences 
	  TCLAP::MultiArg<double> freq("p", "frequences", "frequencies (as fraction of the population)", false, "double" );
	  cmd.add(freq);

	  //Répétitions de la simulation
	  TCLAP::ValueArg <int> repetitions("r", "number_repetions", "simulation will be repeated R times", false, 3, "int");
	  cmd.add(repetitions);
	  
	  //marqueurs	
	  TCLAP::MultiArg<size_t> markers("m", "markers", "alleles' positions on the sequence", false, "size_t" );
	  cmd.add(markers);
	  
	  //Extension:
	  //Remplissage de la matrice 
	  TCLAP::ValueArg <string> star("s", "star", "Star migration pattern", false, "string");
      TCLAP::ValueArg <string> ring("g", "ring", "Ring migration pattern", false, "string");
	  TCLAP::ValueArg <string> complete("c", "complete", "Complete migration pattern", false, "string");
      cmd.xorAdd(star, ring, complete);
	  
	  //Ratio de population à migrer
	  TCLAP::ValueArg <double> migration_ratio("a", "migration_ratio", "Percentage of the population to move", false, 0, "double");
	  cmd.add(migration_ratio);
	  
	  cmd.parse(argc, argv);		//trier les exeptions en fonctions du fasta/terminal
	   
	   
	  //Gestion d'erreurs 	
	  if (!terminal.isSet() and !print_file.isSet()) throw TCLAP::ArgException("At least one output (terminal/file) has to specified"); 
	  if (duration.getValue() < 1) throw TCLAP::ArgException("Simulation duration must be strictly positive");
	  if (repetitions.getValue() < 1) throw TCLAP::ArgException("Number of repetitions must be strictly positive");
	  if ( (repetitions.getValue() < 0) or (repetitions.getValue() > 1) ) throw TCLAP::ArgException("Ratio has to be between 0 and 1");
	  
	  std::string migration_type;
	  if (star.isSet()) migration_type = star.getValue() );
      else if(ring.isSet()) migration_type = ring.getValue() );
      else migration_type = "";

	  
	  std::vector<std::string> _genetic_code;
	  std::vector<double> _freqs(freq.getValue());
	  std::vector<size_t> _markers(markers.getValue());
	  int _population_size(population_size.getValue());
	  size_t _alleles_number((freq.getValue()).size());
	  std::string _file_name(file_name.getValue());
	  
		if(file_name.isSet()) {
			
			try {
				//for (auto val : markers.getValue()) if (val < 1) throw TCLAP::ArgException("Markers must be strictly positive"); //les size_t négatifs sont convertis en positifs donc pas de sens
				read_fasta(_freqs, _genetic_code, _markers, _population_size, _alleles_number, _file_name);
			} catch(std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
				return -2;
			}
			
		} else {
			
			double total_freq(0);
			for(auto f : freq.getValue()) {
				total_freq += f;
				if (f < 0 or f > 1) throw TCLAP::ArgException("Frequencies must be between 0 and 1 included");
				}
			if (1-total_freq > 0.001 or 1-total_freq < -0.001) throw TCLAP::ArgException("Sum of frequencies must be equal to 1");
			if (population_size.getValue() < 1) throw TCLAP::ArgException("Population size must be strictly positive");
			
			for (size_t i(0) ; i < (freq.getValue()).size() ; ++i) _genetic_code.push_back(std::to_string(i+1));		
		}
		
		if(migration_type != "") {					
			Migration migration(duration.getValue(), repetitions.getValue(), _population_size, _alleles_number, terminal.getValue(), print_file.getValue(), _freqs, _genetic_code, migration_type,migration_ratio.getValue())
			migration.run();
		} else {
			Simulation simulation(duration.getValue(), repetitions.getValue(), _population_size, _alleles_number, terminal.getValue(), print_file.getValue(), _freqs, _genetic_code);
			simulation.run();
		}
		
	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << std::endl;
		return -1;
	}
	
	return 0;
}
