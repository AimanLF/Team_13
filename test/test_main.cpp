#include "test_simulation_migration.cpp"
#include "test_multibinomial.cpp"
#include "test_readfasta.cpp"

/*! Runs all the tests.*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
