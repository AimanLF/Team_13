#include <tclap/CmdLine.h>
#include <ctime>
#include "read_fasta.h"
#include "migration.h"

int main(int argc, char ** argv) {

	bool warning_frequence(false);
	bool warning_population_size(false);
	
	try {
	
	  TCLAP::CmdLine cmd("commande");

	  TCLAP::ValueArg <std::string> file_name("F", "File_name", "Fasta file containing sequences.", false, "", "string");
	  cmd.add(file_name);
	  
	  TCLAP::SwitchArg terminal("T", "Terminal", "Print results in terminal.", false);
	  cmd.add(terminal);
	  TCLAP::SwitchArg print_file("P", "Print_file", "Print results in a file.", false);
	  cmd.add(print_file);
	  
	  TCLAP::ValueArg <int> population_size("N", "Size", "Number of individuals.", false, 100, "int");
	  cmd.add(population_size);

	  TCLAP::ValueArg <int> generation("G", "Generations", "Number of generations.", false, 10, "int");
	  cmd.add(generation);
	  
	  TCLAP::MultiArg<double> freq("f", "frequences", "Frequencies (as fraction of the population).", false, "double" );
	  cmd.add(freq);
	  
	  TCLAP::ValueArg <int> repetitions("R", "Repetions", "Simulation will be repeated R times.", false, 3, "int");
	  cmd.add(repetitions);
	  	
	  TCLAP::MultiArg <int> markers("m", "markers", "Alleles' positions on the sequence.", false, "int" );
	  cmd.add(markers);
	  
	  TCLAP::ValueArg <std::string> migration_type("M", "Migration", "Choose a migration type (star/ring/complete).", false, "","string");
      cmd.add(migration_type);
      
	  cmd.parse(argc, argv);
	   
	  	
	  if (!terminal.isSet() and !print_file.isSet()) throw TCLAP::ArgException("At least one output (terminal/file) has to specified."); 
	  if (generation.getValue() < 1) throw TCLAP::ArgException("Simulation duration must be strictly positive.");
	  if (repetitions.getValue() < 1) throw TCLAP::ArgException("Number of repetitions must be strictly positive.");
	  for(double f:freq.getValue()){
		double a = population_size.getValue()*f;
		double b = (int)(population_size.getValue()*f); 
		if(std::abs(a - b)>1e-6 ) throw TCLAP::ArgException("Number of individus for each frequence must be an integer");	
	}
	  
	  if((freq.getValue().empty() == false) and (file_name.getValue().empty() == false )) {
		  warning_frequence = true;
	  }
	  
	  if((population_size.isSet() == true) and (file_name.getValue().empty() == false )) {
		  warning_population_size = true;
	  }
	  
	  
	  std::vector<std::string> _genetic_code;
	  std::vector<double> _freqs(freq.getValue());
	  std::vector<size_t> _markers;
	  int _population_size(population_size.getValue());
	  size_t _alleles_number((freq.getValue()).size());
	  std::string _file_name(file_name.getValue());
	  
		if(file_name.isSet()) {											
			
			try {
				if (!markers.isSet()) throw TCLAP::ArgException("Expect markers to read the file");
				for (auto val : markers.getValue()){
					if (val > 0) _markers.push_back(val);
					else throw TCLAP::ArgException("Markers must be strictly positive");
					}
				read_fasta(_freqs, _genetic_code, _markers, _population_size, _alleles_number, _file_name);
			} catch(std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
				return -2;
			} catch(std::logic_error &e){
				std::cerr << e.what() << std::endl;
				return -3;
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
	
	if(warning_frequence) {
		  std::cout << "\033[1;33mWARNING: frequences in terminal are not used, they are taken from the fasta file\033[0m" << std::endl;
	  }
	  
	if(warning_population_size) {
		std::cout << "\033[1;33mWARNING: population number in terminal are not used, they are taken from the fasta file\033[0m" << std::endl;
	  }
	  
	return 0;
}
