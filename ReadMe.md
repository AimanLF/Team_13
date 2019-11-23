# Wright-Fisher Simulation
Aim is to simulate the evolution of a genetic population over time. A population is composed of individuals, each one has a genome. At each generation a new population of the same size is randomly chosen among individuals of the last population. Using the multinomial distribution we define new frequencies for each alleles (e.g. different genotypes) allowing the population to evolve.

## Run the program
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes:   
_git clone https://github.com/EPFL-SV-cpp-projects/Team_13.git   
cd Team_13  
rm -rf build   
mkdir build 
cd build   
cmake ..  
make   
make doc_

## Use read_fasta
In order for the program to read you .fasta file, it will have to contain nucleotides sequences composed of A, T, C, G or N. In this last case, N will be replaces randomly by an other nucleotide.
Other lines (chromosome number) has to start with ">" symbol.
Example:
```
>chr11 
CACTGTGTNTGATGATCAACAAAAACCTGGGGGGGGTAGTAGTAGTCC
>chr7 
AAATGGTGCGTGATGCCCCCCCCCCCCNCCTTGTGAAAA
...
```

## Read the output

```
tbd
```

## Understand the tests
To execute the tests, type the command:

_make test_

### Test_multibinomial
sameAverage: tests the stability of alleles frequencies over time. For a large number of populations, frequencies after 1, 2, 3 generations on average are the same has for t=0.

fixation_time: for any simulation, one allele will always reach a frequency equal to 1 (so only one to remain). This test verify it's the case (with 2 and 5 alleles).  

### test_simulation
somme1: check if sum of alleles frequencies remains equal to 1 after a given number of calls to multibinomial (10 in this case). 

fixation: controls that if an allele disappear (ie. its frequence is null) it won't reappear in the simulation (corresponds to extinction of the character). 
```
tbd
```
