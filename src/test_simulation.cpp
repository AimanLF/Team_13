#include <gtest/gtest.h>
#include "simulation.h"
#include <vector>
#include <string>

#include <iostream>

bool isEqual(double x, double y, double epsilon){return std::abs(x - y) < epsilon;}
bool isEqual(double x, double y){return isEqual(x, y, 6e-2);}

TEST(simulationTest,sameAverage){
double freq1 (0.3);
double freq2 (0.4);
double freq3 (0.1);
double freq4 (0.05);
double freq5 (0.15);
size_t nbPop(50000);

//Test if after 1, 2 and 3 generation(s) same average frequencies on 100 populations with same frequencies
 for (size_t i(0); i < 3; i++){
    Simulation simulation(i,nbPop,2000,5,false, false,std::vector<double> {freq1, freq2, freq3, freq4, freq5}, std::vector<std::string> (5,"-")); 
    simulation.run();
    
    double f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;
    for (size_t i(0); i < nbPop; i++){ 
      std::vector <double> freq (simulation.getFreqPop(i));
      f1 += freq[0];
      f2 += freq[1];
      f3 += freq[2];
      f4 += freq[3];
      f5 += freq[4];
    }
    EXPECT_NEAR(freq1, f1/nbPop, 7e-2);
    EXPECT_NEAR(freq2, f2/nbPop, 7e-2);
    EXPECT_NEAR(freq3, f3/nbPop, 7e-2);
    EXPECT_NEAR(freq4, f4/nbPop, 7e-2);
    EXPECT_NEAR(freq5, f5/nbPop, 7e-2);
  }
}

TEST(simulationTest,fixation_time){
	//Test si une allèle se fixe avec 3 allèles, 9 fois au minimum sur 10
	int testOK(0);
	for (size_t i(0); i < 10; ++i){
		double freqx (0.85);
		double freqy (0.15);
		Simulation simulation1(50000,1,5000,2,false, false,std::vector<double> {freqx, freqy}, std::vector<std::string> (2,"-"));
		simulation1.run();

		std::vector <double> f1 (simulation1.getFreqPop(0));
		if(isEqual(1.0,f1[0]) or isEqual(1.0,f1[1])) ++testOK;
	}		

	//Test si une allèle se fixe avec 5 allèles
	double freq1 (0.3);
	double freq2 (0.4);
	double freq3 (0.1);
	double freq4 (0.05);
	double freq5 (0.15);
	Simulation simulation2(50000,1,5000,5, false, false, std::vector<double> {freq1, freq2, freq3, freq4, freq5}, std::vector<std::string> (5,"-"));
	simulation2.run();
	
	std::vector <double> f2 (simulation2.getFreqPop(0));
	bool cond2(isEqual(1.0,f2[0]) or isEqual(1.0,f2[1]) or isEqual(1.0,f2[2]) or isEqual(1.0,f2[3]) or isEqual(1.0,f2[4]));

	EXPECT_TRUE(testOK >= 8);
	EXPECT_TRUE(cond2);

}
