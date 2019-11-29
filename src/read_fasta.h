#ifndef READ_FASTA
#define READ_FASTA

#include <vector>
#include <string>
 
char pick_nucleotide();
void read_fasta(std::vector<double>& f, std::vector<std::string>& alleles, std::vector<size_t> marqueurs, int& N, size_t& A, std::string& file);

#endif
