#include <gtest/gtest.h>
#include "../src/multibinomial.h"

/*!
  TEST(MultibinomialTest,somme1): Test que la somme des allèles est toujours équales à 1 après 10 appels de multibinomial
  TEST(MultibinomialTest, fixation): Test qu'un allèle à 0 ne peut pas réapparaître
 */
 
TEST(MultibinomialTest,somme1){
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
