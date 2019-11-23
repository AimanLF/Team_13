# Wright-Fisher Simulation
Aim is to simulate the evolution of a genetic population over time. A population is composed of individuals, each one has a genome. At each generation a new population of the same size is randomly chosen among individuals of the last population. Using the multinomial distribution we define new frequencies for each alleles (e.g. different genotypes) allowing the population to evolve.

## Run the program
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes:   
git clone https://github.com/EPFL-SV-cpp-projects/Team_13.git   
cd Team_13  
rm -rf build   
mkdir build 
cd build   
cmake ..  
make   
make doc

## Output

```
tbd
```

## Understand the tests
To execute the tests, type the command:
make test
### Test_multibinomial
sameAverage: tests the stability of alleles frequencies over time. For a large number of populations, frequencies after 1, 2, 3 generations on average are the same has for t=0.

fixation_time: for any simulation, one allele will always reach a frequency equal to 1 (so only one to remain). This test verify it's the case (with 2 and 5 alleles).  

### test_simulation
somme1: check if sum of alleles frequencies remains equal to 1 after a given number of calls to multibinomial (10 in this case). 

fixation: controls that if an allele disappear (ie. its frequence is null) it won't reappear in the simulation. 
```
tbd
```
