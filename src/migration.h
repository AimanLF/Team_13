#include <simulation.h>
#include <vector>
#include <string>
#include <map>

class Migration : Simulation
{
	public:
		void run() override;
		void migrate(Population pop1, Population pop2, vector<vector<double>> matrix);
	
	private:
		map<string, vector<vector<double>> all_matrix;		//avec le string = type de migration
};
