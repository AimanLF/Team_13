#ifndef READ_FASTA
#define READ_FASTA

#include <vector>
#include <string>

/*!
  \return a nucleotide (A, T, G or C) using uniform distribution.
 */
char pick_nucleotide();

/*!
  When reading a fasta, sorts the alleles in alphabetic order and adapts the 
  frequencies vector to that new order.
 */
void sort(std::vector<double>& frequence, std::vector<std::string>& genetic_code);

/*!
  Used with the sort function of the standard library, to sort a
  vector's values from lower to higher (markers vector).
 */
int SortCroissant(const int& a,const int& b);

/*!
  Recurrent function that allows reading the next line of the fasta looking for
  the next nucleotide indicated by the markers vector.
  Also calls \ref pick_nucleotide().
 */
void read_next_line(size_t last_size, std::string& new_seq, size_t last_indice, std::vector<size_t>& marqueurs, std::ifstream& confstr);

/*!
  Reads a fasta file using genome markers to modify by reference the parameters of a population:
  number of individuals, alleles and their number and frequencies.
  Also calls \ref read_next_line(), \ref SortCroissant(), \ref pick_nucleotide() and \ref sort(). 
 */
void read_fasta(std::vector<double>& f, std::vector<std::string>& alleles, std::vector<size_t> marqueurs, int& N, size_t& A, std::string& file);

#endif
