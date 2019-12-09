#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include "read_fasta.h"
#include <multibinomial.h>

char pick_nucleotide(){
	double i = randomUniform(0,3);
	if (i == 0) return 'A';
	if (i == 1) return 'T';
	if (i == 2) return 'G';
	return 'C';
}

void sort(std::vector<double>& frequence, std::vector<std::string>& genetic_code){
std::vector<std::string> new_genetic_code(genetic_code);
	std::sort(new_genetic_code.begin(),new_genetic_code.end());
	std::vector<int>index;
	
	for (size_t i(0); i<genetic_code.size(); ++i){
		std::string codon = genetic_code[i];
		std::vector<std::string>::iterator it = std::find(new_genetic_code.begin(), new_genetic_code.end(), codon);
		if (it != genetic_code.end())
			  index.push_back(std::distance(new_genetic_code.begin(), it));
	}
	
	std::vector<double> new_frequence(frequence.size());
	for (size_t i(0); i<index.size(); ++i){
		 int nb=index[i];
		 new_frequence[nb]=frequence[i];
	 }
	 
	 genetic_code=new_genetic_code;
	 frequence=new_frequence;
 }

void read_fasta(std::vector<double>& f, std::vector<std::string>& alleles, std::vector<size_t> marqueurs, int& N, size_t& A, std::string& file){
		std::ifstream confstr(file.c_str());
		if (confstr.is_open()){
			
			std::vector<std::string> sequences, ALLELES;
			std::vector<double> F;
			size_t N_ind(0);
			
			std::string line;
			
			while(std::getline(confstr, line)){
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);
                if (line[0] == '>') ++N_ind;
                else if (line[0] == 'A' or line[0] == 'T' or line[0] == 'G' or line[0] == 'C' or line[0] == 'N'){
					for (auto val : marqueurs) if (val > line.size()) throw std::invalid_argument("Markers refer to non-existant nucleotide.");
					std::string new_seq("");
					bool exist(false);
					for (auto num : marqueurs)  if (line[num-1] == 'N') new_seq += pick_nucleotide();
												else new_seq += line[num-1];
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
			sort(F,ALLELES);
			A = ALLELES.size(), N = N_ind, alleles = ALLELES, f = F;
			confstr.close();
		} else throw std::invalid_argument("Could not open configuration file " + file);									//fichier impossible à ouvrir rejeté
}

