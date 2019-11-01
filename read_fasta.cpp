#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void read_fasta(std::vector<double>& f, std::vector<std::string>& alleles, std::vector<size_t> marqueurs, size_t& N, size_t& A, std::string& file){
	try{
		std::ifstream confstr(file);
		if (confstr.is_open()){
			std::vector<std::string> sequences, ALLELES;
			std::vector<double> F;
			size_t N_ind(0);
			
			std::string line, new_seq("");
			bool exist(false);
			
			while(std::getline(confstr, line)){
				
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                if (line[0] == '>') ++N_ind;
                else{
					for (auto num : marqueurs) new_seq += line[num];		//à voir si les marquers commencent par 1 ou 0
					sequences.push_back(new_seq);		//rassemble TOUTES les sequences
					for (auto seq : ALLELES) if (new_seq == seq) exist = true;
					if (not exist) ALLELES.push_back(new_seq);		//rassemble les allèles (uniques)
					}
				}
			for (size_t i(0) ; i < ALLELES.size() ; ++i){
				double c(0);
				for (size_t k(0) ; k < sequences.size() ; ++k) if (ALLELES[i] == sequences[k]) ++c; //compte le nbre d'apparition de l'allèle
				F.push_back(c/sequences.size());
				}
			A = ALLELES.size(), N = N_ind, alleles = ALLELES, f = F;
			confstr.close();
		} else throw("Could not open configuration file " + file);
		} 
	}
	/* à ajouter dans le main*/

catch(std::ifstream::failure &e){
			std::cout << e.what() << std::endl;
			return 1;
				}
