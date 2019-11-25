# Wright-Fisher Simulation
Aim is to simulate the evolution of a genetic population over time. A population is composed of individuals, each one has a genome. At each generation a new population of the same size is randomly chosen among individuals of the last population. Using the multinomial distribution we define new frequencies for each alleles (e.g. different genotypes) allowing the population to evolve.

## Run the program
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes:   
_git clone https://github.com/EPFL-SV-cpp-projects/Team_13.git   
cd Team_13   
mkdir build  
cd build   
cmake ..  
make   
make doc
./Wright_Fisher

## Use read_fasta
In order for the program to read you .fasta file, it will have to contain nucleotides sequences composed of A, T, C, G or N. In this last case, N will be replaces randomly by an other nucleotide.
Other lines (chromosome number) have to start with ">" symbol.
Example:
```
>chr11 
CACTGTGTNTGATGATCAACAAAAACCTGGGGGGGGTAGTAGTAGTCC
>chr7 
AAATGGTGCGTGATGCCCCCCCCCCCCNCCTTGTGAAAA
>chr2
...
```

## Read the output
Standard output is formated this way:
```
0 0.1|0.2|0.3|0.4          0.1|0.2|0.3|0.4          0.1|0.2|0.3|0.4 
1 0.096|0.21|0.274|0.42    0.087|0.206|0.298|0.409  0.098|0.207|0.311|0.384 
2 0.075|0.208|0.279|0.438  0.086|0.208|0.307|0.399  0.087|0.214|0.307|0.392 
3 0.067|0.2|0.284|0.449    0.074|0.193|0.333|0.4    0.096|0.215|0.288|0.401 
4 0.067|0.208|0.287|0.438  0.088|0.196|0.311|0.405  0.106|0.222|0.279|0.393
  ACG|ACA|ATA|ATG          ACT|ACA|AGA|GCA          ACG|AGA|AGT|AAA
```
Each line corresponds to one generation, the first column is the generation number (i.e. time), each subsequent column represents a replica of the simulation where each is represented by the frequencies of the alleles in the population (separated by '|'). If a fasta fi le was provided as input, the last line indicates the calculated alleles.

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
