#include <tclap/CmdLine.h>
#include "read_fasta.h"
#include "simulation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

int main(int argc, char ** argv) {
	
	int nerr = 0;
	
	try {
	
	  TCLAP::CmdLine cmd("commande");
  
	  //Saisie par l'utilisateur
	  TCLAP::ValueArg <std::string> file_name("f", "file_name", "File with parameters", false, "", "string");
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
	  TCLAP::ValueArg <size_t> alleles_number("a", "alleles_number", "number of alleles in the population", false, 2, "size_t");
	  cmd.add(alleles_number);
	  
	  //Fréquences initiales des allèles 
	  TCLAP::MultiArg<double> freq("p", "frequences", "frequencies (as fraction of the population)", false, "double" );
	  cmd.add(freq);

	  //la simulation sera répétée R fois
	  TCLAP::ValueArg <size_t> repetitions("r", "number_repetions", "simulation will be repeted R times", false, 2, "size_t");
	  cmd.add(repetitions);
	  
	  //positions le long de la séquence qui déterminent les allèles	
	  TCLAP::MultiArg<size_t> markers("m", "markers", "alleles' positions on the sequence", false, "size_t" );
	  cmd.add(markers);  	
	  
	  cmd.parse(argc, argv);
	  
	  std::vector<std::string> _genetic_code;
	  std::vector<double> _freqs(freq.getValue());
	  std::vector<size_t> _markers(markers.getValue());
	  size_t _population_size(population_size.getValue());
	  size_t _alleles_number(alleles_number.getValue());
	  std::string _file_name(file_name.getValue());
	  
		if(file_name.isSet()) {
		//on lit le fichier 

			try {
				read_fasta(_freqs, _genetic_code, _markers, _population_size, _alleles_number, _file_name);
			} catch(std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
				nerr+= 1;
			}
			
		} else {
			for (size_t i(0) ; i < (freq.getValue()).size() ; ++i) _genetic_code.push_back(std::to_string(i+1));		
		}
		
		Simulation(duration.getValue(), repetitions.getValue(), _population_size, _alleles_number, terminal.getValue(), print_file.getValue(), _freqs, _genetic_code);
	 
		  
		if(!terminal.isSet() and !print_file.isSet()) {
			std::cerr << "At least one output has to specified" << std::endl; 
		}
			
		if(population_size.getValue() < 1) {
			std::cerr << "Population size must be strictly positive" << std::endl;
			nerr+= 1;
		}
		
		if(duration.getValue() < 1) {
			std::cerr << "Simulation duration must be strictly positive" << std::endl;
			nerr+= 1;
		}
	  
		if(alleles_number.getValue() < 1) {
			std::cerr << "Number of alleles must be strictly positive" << std::endl;
			nerr+= 1;
		}
	  
		double total_freq(0);
		for(auto f : freq.getValue()) {
			total_freq += f;
		
		if (f < 0 or f > 1)  {
		   std::cerr << "Frequencies must be between 0 and 1 included" << std::endl;
		   nerr+= 1;
			}
	  
		}
	/*	if (total_freq != 1) {
		   std::cerr << "Sum of frequencies must be equal to 1" << std::endl;
		   nerr+= 1;
			}
		*/	
	  if (repetitions.getValue() < 1) {
		std::cerr << "Number of repetitions must be strictly positive" << std::endl;
		nerr+= 1;
	  }
	  
	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		nerr+= 1;
	}
	
	return nerr;
}

 /*#include <math>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>


int main()
{
	vector<vector<double>> matrix;() 
	
	//condition pour quue la taille des pop soit constante : r(0,1) + r(2,1) = r(1,0) + r(1,2)  (=le nombre d'individus arrivant de la pop 0 et la pop 2 dans la pop 1 doit être égal à celui partant de la pop 1 vers la pop 0 et 2)
	std::srand(unsigned(std::time(0)));
	for(size_t i(0), i < get_PopulationsSize(), ++i) {

		if(i = get_PopulationsSize() -1 ) {
			move_pop(i, 0, vector<size_t>(round(ratio * size_pop), );
		} else { 
			move_pop(i, i+1, vector<size_t>(round(ratio * size_pop), );	//méthode de simulation qui prendrait en argument une population de départ, une d'arrivée et les individus à faire migrer
		} 
		
		std::random_shuffle(population[i].begin(), population[i].end();  //on mélange la population pour que se soient toujours les mêmes individus qui migrent
		
		}
	return 0;
}
*/
