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
			for (auto val : marqueurs) if (val < 0) throw std::invalid_argument("Invalid markers given in file : " + file);	//marqueurs négatif rejetés
			
			std::vector<std::string> sequences, ALLELES;
			std::vector<double> F;
			size_t N_ind(0);
			
			std::string line, new_seq("");
			bool exist(false);
			
			while(std::getline(confstr, line)){
				
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);
                if (line[0] == '>') ++N_ind;
                else if (line[0] == 'A' or line[0] == 'T' or line[0] == 'G' or line[0] == 'C'){
					for (auto num : marqueurs) new_seq += line[num];
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
}

/* à ajouter dans le main
	
	catch(std::invalid_argument &e){
		std::cout << e.what() << std::endl;
		return 0;
		}
*/
