#include <gtest/gtest.h>
#include "multibinomial.cpp"
#include <random>
#include <vector>

std::mt19937 rng;
std::random_device rd;
rng = std::mt19937(rd());

TEST(MultibinomialTest,somme1){
//Test que la somme des allèles est toujours équales à 1 après 10 appels de multibinomial
  std::vector<double> test = {0.3,0.2,0.4,0.1};
  
  for(size_t i(0); i < 10; i++)
    test = multibinomial(4,test,rng);
  
  double somme (0);
  for(auto f : test)
    somme += f;
  
  EXPECT_NEAR(1, somme, 1e-4);
}

TEST(MultibinomialTest, fixation){
 //Test que une allèles étant = 0 ne peut pas réapparaître
 std::vector<double> test = {0.3,0.2,0.5,0.0};
 
 for(size_t i(0); i < 10; i++)
    test = multibinomial(4,test,rng);
    
    EXCEPT(0, test[3]);
  
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
