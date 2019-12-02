#include <tclap/CmdLine.h>
#include <ctime>
#include "read_fasta.h"
#include "migration.h"

int main(int argc, char ** argv) {
	
	float temps;
    clock_t ti, tf;
	ti=clock();
	
	try {
	
	  TCLAP::CmdLine cmd("commande");
  
	  //Saisie par l'utilisateur
	  TCLAP::ValueArg <std::string> file_name("F", "File_name", "Fasta file containing sequences.", false, "", "string");
	  cmd.add(file_name);
	  
	  //Affichage terminal et/ou fichier
	  TCLAP::ValueArg <bool> terminal("T", "Terminal", "Print results in terminal.", false, false, "bool");
	  cmd.add(terminal);
	  TCLAP::ValueArg <bool> print_file("p", "print_file", "Print results in a file.", false, false, "bool");
	  cmd.add(print_file);

	  //Taille de la population
	  TCLAP::ValueArg <int> population_size("n", "size", "Number of individuals.", false, 100, "int");
	  cmd.add(population_size);

	  //Durée en nombre de générations 
	  TCLAP::ValueArg <int> generation("g", "generations", "Number of generations.", false, 10, "int");
	  cmd.add(generation);

	  //Fréquences 
	  TCLAP::MultiArg<double> freq("f", "frequences", "Frequencies (as fraction of the population).", false, "double" );
	  cmd.add(freq);

	  //Répétitions de la simulation
	  TCLAP::ValueArg <int> repetitions("r", "number_repetions", "Simulation will be repeated R times.", false, 3, "int");
	  cmd.add(repetitions);
	  
	  //marqueurs	
	  TCLAP::MultiArg <size_t> markers("m", "markers", "Alleles' positions on the sequence.", false, "size_t" );
	  cmd.add(markers);
	  
	  //Type de migration
	  TCLAP::ValueArg <std::string> migration_type("M", "Migration_type", "Choose a migration type (star/ring/complete).", false, "","string");
      cmd.add(migration_type);
      
	  cmd.parse(argc, argv);		//trier les exeptions en fonctions du fasta/terminal
	   
	   
	  //Gestion d'erreurs 	
	  if (!terminal.isSet() and !print_file.isSet()) throw TCLAP::ArgException("At least one output (terminal/file) has to specified."); 
	  if (generation.getValue() < 1) throw TCLAP::ArgException("Simulation duration must be strictly positive.");
	  if (repetitions.getValue() < 1) throw TCLAP::ArgException("Number of repetitions must be strictly positive.");
	  
	  std::vector<std::string> _genetic_code;
	  std::vector<double> _freqs(freq.getValue());
	  std::vector<size_t> _markers(markers.getValue());
	  int _population_size(population_size.getValue());
	  size_t _alleles_number((freq.getValue()).size());
	  std::string _file_name(file_name.getValue());
	  
		if(file_name.isSet()) {													//option fasta
			
			try {
				if (!markers.isSet()) throw TCLAP::ArgException("Expect markers to read the file");
				read_fasta(_freqs, _genetic_code, _markers, _population_size, _alleles_number, _file_name);
			} catch(std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
				return -2;
			}
			
		} else {
			
			double total_freq(0);
			for(auto f : freq.getValue()) {
				total_freq += f;
				if (f < 0 or f > 1) throw TCLAP::ArgException("Frequencies must be between 0 and 1 included.");
				}
			if (1-total_freq > 0.001 or 1-total_freq < -0.001) throw TCLAP::ArgException("Sum of frequencies must be equal to 1.");
			if (population_size.getValue() < 1) throw TCLAP::ArgException("Population size must be strictly positive.");
			
			for (size_t i(0) ; i < (freq.getValue()).size() ; ++i) _genetic_code.push_back(std::to_string(i+1));		
		}
		
		if(migration_type.isSet()) {							//option migration		
			std::string t = migration_type.getValue();
			if (t != "star" and t != "ring" and t != "complete") throw TCLAP::ArgException("Migration type invalid.");
			
			Migration migration(generation.getValue(), repetitions.getValue(), _population_size, _alleles_number, terminal.getValue(), print_file.getValue(), _freqs, _genetic_code, migration_type.getValue());
			migration.run();
		} else {
			Simulation simulation(generation.getValue(), repetitions.getValue(), _population_size, _alleles_number, terminal.getValue(), print_file.getValue(), _freqs, _genetic_code);
			simulation.run();
		}
		
	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << std::endl;
		return -1;
	}
	
	tf=clock();
	temps = (tf-ti)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);
	
	return 0;
}
