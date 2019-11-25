#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <read_fasta.h>

char pick_nucleotide(){
	double i(rand() % 4);
	if (i == 0) return 'A';
	if (i == 1) return 'T';
	if (i == 2) return 'G';
	return 'C';
}

void read_fasta(std::vector<double>& f, std::vector<std::string>& alleles, std::vector<size_t> marqueurs, size_t& N, size_t& A, std::string& file){
		std::ifstream confstr(file);
		if (confstr.is_open()){
			
			std::vector<std::string> sequences, ALLELES;
			std::vector<double> F;
			size_t N_ind(0);
			
			std::string line, new_seq("");
			bool exist(false);
			
			while(std::getline(confstr, line)){
				//attention marqueurs > line.size()
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);
                if (line[0] == '>') ++N_ind;
                else if (line[0] == 'A' or line[0] == 'T' or line[0] == 'G' or line[0] == 'C' or line[0] == 'N'){
					for (auto num : marqueurs)  if (line[num] == 'N') new_seq += pick_nucleotide(); 					//comme demandé en cours, pick un nucleotide au hasard (même proba)
												else new_seq += line[num];												//à chaque N rencontré
					sequences.push_back(new_seq);
					for (auto seq : ALLELES) if (new_seq == seq) exist = true;
					if (not exist) ALLELES.push_back(new_seq);
				} else throw std::invalid_argument("The file " + file + " does not have the required content.");			//fichier contenant autre chose rejeté
			}
			for (size_t i(0) ; i < ALLELES.size() ; ++i){
				double c(0);
				for (size_t k(0) ; k < sequences.size() ; ++k) if (ALLELES[i] == sequences[k]) ++c;
				F.push_back(c/sequences.size());
			}
			A = ALLELES.size(), N = N_ind, alleles = ALLELES, f = F;
			confstr.close();
		} else throw std::invalid_argument("Could not open configuration file " + file);									//fichier impossible à ouvrir rejeté
}

