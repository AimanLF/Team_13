#include <tclap/CmdLine.h>
#include "read_fasta.cpp"
#include "population.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

//RandomNumbers *_rng;
/*
void parse_args(int argc, char **argv) {
	
	
  TCLAP::CmdLine cmd("commande");
  
  //Saisie par l'utilisateur
  TCLAP::ValueArg <std::string> file_name("f", "file name", "File with parameters", false, "", "string");
  cmd.add(file_name);
  
  //Affichage terminal et/ou fichier
  TCLAP::ValueArg <bool> terminal("e", "terminal", "Print results in terminal", false, "", "bool");
  cmd.add(terminal);
  TCLAP::ValueArg <bool> print_file("i", "print_file", "Print results in a file", false, "", "bool");
  cmd.add(print_file);

  //Taille de la population (= aussi nombre de séquences dans le .fasta)
  TCLAP::ValueArg <size_t> population_size("n", "size", "number of individuals", false, 100, "size_t");
  cmd.add(population_size);

  //Durée (en nombre de générations) de la simulation 
  TCLAP::ValueArg <size_t> duration("t", "time", "number of generations", false, 10, "size_t");
  cmd.add(duration);

  //Nombre de combinaisons de nucléotides différentes aux positions markers
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

  //_rng = new RandomNumbers();

}*/

int main(int argc, char ** argv) {
	
	int nerr = 0;
	
	try{ // exceptions TCLAP
		TCLAP::CmdLine cmd("commande");
  
  //Saisie par l'utilisateur
  TCLAP::ValueArg <std::string> file_name("f", "file name", "File with parameters", false, "", "string");
  cmd.add(file_name);
  
  //Affichage terminal et/ou fichier
  TCLAP::ValueArg <bool> terminal("e", "terminal", "Print results in terminal", false, "", "bool");
  cmd.add(terminal);
  TCLAP::ValueArg <bool> print_file("i", "print_file", "Print results in a file", false, "", "bool");
  cmd.add(print_file);

  //Taille de la population (= aussi nombre de séquences dans le .fasta)
  TCLAP::ValueArg <size_t> population_size("n", "size", "number of individuals", false, 100, "size_t");
  cmd.add(population_size);

  //Durée (en nombre de générations) de la simulation 
  TCLAP::ValueArg <size_t> duration("t", "time", "number of generations", false, 10, "size_t");
  cmd.add(duration);

  //Nombre de combinaisons de nucléotides différentes aux positions markers
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
  
		if(!file_name.isSet()) {
		//on lit le fichier 
		
			try {
				read_fasta(freq.getValue(), Population::getgenetic_code(), markers.getValue(), population_size.getValue(), alleles_number.getValue(), file_name.getValue());
			} catch(std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
				nerr+= 1;
			}
		} 
		  
		if (population_size.getValue() < 1) {
			std::cerr << "Population size must be strictly positive" << std::endl;
			nerr+= 1;
		}
		
		if (duration.getValue() < 1) {
			std::cerr << "Simulation duration must be strictly positive" << std::endl;
			nerr+= 1;
		}
	  
		if (alleles_number.getValue() < 1) {
			std::cerr << "Number of alleles must be strictly positive" << std::endl;
			nerr+= 1;
		}
	  
		double total_freq(0);
		for(auto f : freq.getValue()) {
			total_freq += f;
			
			if (total_freq != 1) {
			   std::cerr << "Sum of frequencies must be equal to 1" << std::endl;
			   nerr+= 1;
			}
			
			if (f < 0 or f > 1)  {
			  std::cerr << "Frequencies must be between 0 and 1 included" << std::endl;
			  nerr+= 1;
			}
		}
	  
	  if (repetitions.getValue() < 1) {
		std::cerr << "Number of repetitions must be strictly positive" << std::endl;
		nerr+= 1;
	  }
	  
	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		nerr+= 1;
	}

	//if (_rng) delete _rng;
	
	return nerr;
}

    
