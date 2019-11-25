#include <migration.h>

Migration::run()
{
	for (size_t t(0); t<endtime; ++t){
		print(t+1);
		step();
		migrate();
	} 
	printAlleles();
}

Migration::migrate(Population pop1, Population pop2, vector<vector<double>> matrix)
{

}
