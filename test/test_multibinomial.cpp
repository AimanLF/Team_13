#include <gtest/gtest.h>
#include "../src/multibinomial.h"

/*!
  TEST(MultibinomialTest,somme1): tests if the sum of the alleles’ frequencies is always equal to 1.00 after a given
several calls of multibinomial.
  TEST(MultibinomialTest, fixation): tests that if an allele won’t reappear if its frequence equals 0.
in the simulation.
 */

TEST(MultibinomialTest, somme1){
	std::vector<double> test = {0.3,0.2,0.4,0.1};
	for(size_t i(0); i < 10; i++) {
		test = multibinomial(100,test);
		double somme (0.0);
		for(auto f : test)
			somme += f;
		EXPECT_NEAR(1, somme, 1e-4);
	}
}

TEST(MultibinomialTest, fixation){
	std::vector<double> test = {0.3,0.2,0.5,0.0}; 
	for(size_t i(0); i < 10; i++) {
		test = multibinomial(100,test);
		EXPECT_TRUE(test[3] == 0.0);
	}  
}
