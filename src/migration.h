#include <simulation.h>
#include <vector>
#include <string>

typedef std::vector<std::vector<double>> Matrix;
typedef std::vector<double> Ligne;

class Migration : Simulation
{
	public:
		Migration(size_t _t, size_t _r, size_t _n, size_t _a, bool terminal,bool file,
					const std::vector<double>& _f, const std::vector<std::string>& _c,
					std::string _matrix, double _migration_ratio);
					
		void run(); //override; à ajouter, mais enlevé pour l'instant sinon compile pas
		void migrate(Population& pop1, Population& pop2, Matrix matrix);
		void print_matrix() const;
	private:
		Matrix matrix;
		static Matrix create_matrix(std::string matrix, size_t n, double value);		//avec le string = type de migration
};
