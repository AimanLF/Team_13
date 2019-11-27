#include <gtest/gtest.h>
#include "multibinomial.h"
#include <random>
#include <vector>

//variable externe, comment faire mieux ? 
extern std::random_device rd;
extern std::mt19937 rng = std::mt19937(rd());

TEST(MultibinomialTest,somme1){
//Test que la somme des allèles est toujours équales à 1 après 10 appels de multibinomial
  std::vector<double> test = {0.3,0.2,0.4,0.1};
  
  for(size_t i(0); i < 10; i++) {
    test = multibinomial(100,test,rng);
  
	double somme (0.0);
	for(auto f : test) {
		somme += f;
	}
	
	EXPECT_NEAR(1, somme, 1e-4);
	}

}

TEST(MultibinomialTest, fixation){
 //Test qu'un allèle à 0 ne peut pas réapparaître
 std::vector<double> test = {0.3,0.2,0.5,0.0};
 
 for(size_t i(0); i < 10; i++) {
    test = multibinomial(100,test,rng);
    
    EXPECT_TRUE(test[3] == 0.0);
    }
  
}
/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
