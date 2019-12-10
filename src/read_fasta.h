#ifndef READ_FASTA
#define READ_FASTA

#include <vector>
#include <string>
 
char pick_nucleotide();
void sort (std::vector<double>& frequence, std::vector<std::string>& genetic_code);
void read_next_line(size_t last_size, std::string& new_seq, size_t last_indice, std::vector<size_t>& marqueurs, std::ifstream& confstr);
void read_fasta(std::vector<double>& f, std::vector<std::string>& alleles, std::vector<size_t> marqueurs, int& N, size_t& A, std::string& file);

#endif
