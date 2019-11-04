#include <vector>
#include <string>


class Population{
public :
	Population(size_t n_, size_t a_, const std::vector<double> &frequence_, const std::vector<std::string> &codons_);
	//Mis à jour de la population avec les nouvelles fréquences d'allèles
	void step();
	//Affiche la population
	void print() const;
	
private :
	size_t n; //Nb d'individus
	size_t a; //Nb allèle
	std::vector<double> frequence; //Frequence de chaque allèle
	std::vector<std::string> codons; //Codons de chaque allèle
	
};
