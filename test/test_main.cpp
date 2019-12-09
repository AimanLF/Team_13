#include "test_simulation_migration.cpp"
#include "test_multibinomial.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
