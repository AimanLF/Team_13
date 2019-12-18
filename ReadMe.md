# Wright-Fisher Simulation
The program is an implementation of the model of Wright-Fisher. This model does not take into account the environmental factors and focuses only on the generation drift, which is an evolutionary mechanism where the frequencies of alleles in a population vary randomly in time. That means the alleles does not change but only their frequencies. To define the new frequencies at each generation we use the multibinomial distribution. In addition, the populations can migrate following different networks.

## A.Requirements
The Wright-Fisher program required the following to run :
* CMake to compile
* tclap to handle the user options management
* gtest for the unit tests
* doxygen to generate the documentation


## B. Run the program
These instructions allow to get a copy of the project, compile and create the documentation. 
```
0 _git clone https://github.com/EPFL-SV-cpp-projects/Team_13.git   
1 cd Team_13  
2 mkdir build   
3 cd build   
4 cmake ..  
5 make  
6 make doc  
```

## C. Use read_fasta
The fasta file have to contain nucleotides sequences composed of A, T, C, G or N. Note that N will be replaces randomly by an other nucleotide. Before each nucleotides sequence, the user must put a line with a ">" symbol.
Example:
```
>chr11 
CACTGTGTNTGATGATCAACAAAAACCTGGGGGGGGTAGTAGTAGTCC
>chr7 
AAATGGTGCGTGATGCCCCCCCCCCCCNCCTTGTGAAAA
```

## D.Usage and parameters

### 1. From the terminal (without fasta file)
#### usage
``` ./WrightFisher  {-T|-P} [-N <int>] [-G <int>] [-f <double>] [-R <double>] [-M <string>]```
#### parameters
```-N -Size         <int>     ``` The size of the population, i.e:  number of individuals per population.

```-G -Generations  <int>     ``` Duration of the simulation, i.e: the number of generations.

```-f -frequences   <double>  ``` (required)(accepted multiple times)List of the initials frequencies of the alleles.

```-R -Repetitions  <int>     ``` Number of time the simulation is repeat with the same parameters. 

```-M -Migration    <string>  ``` The type of network that links the populations (complete, star, ring), i.e how the individuals will migrate.

```-P -Print_file   <bool>    ``` Indicate if the output must be in a file. 

```-T -Terminal     <bool>    ``` Indicate if the output must be in terminal.

It is required to choose at least one of output localisation (-T and/or -P)

### 2. From fasta file (with fasta file)
#### usage 
```./WrightFisher  {-T|-P} [-F <string>] [-G <int>] [-R <double>] [-m <int>] [-M <string>]```
#### parameters
```-F -File_name    <string>   ```(required) Name of the fasta file.

```-G -Generations  <int>      ```Duration of the simulation, i.e: the number of generations.

```-R -Repetitions  <int>      ```Number of time the simulation is repeat with the same parameters. 

```-m -markers      <int>      ```(required)(accepted multiple times) List of markers to read the fasta file.

```-M -Migration    <string>   ``` The type of network that links the populations (complete, star, ring), i.e how the individuals will migrate.

```-P -Print_file   <bool>     ```Indicate if the output must be in a file.

```-T -Terminal     <bool>     ```Indicate if the output must be in terminal.

It is required to choose at least one of output localisation (-T and/or -P)

### 3. Useful
#### usage 
```./WrightFisher[--] [--version][-h]```
#### parameters
```-    --ignore_rest ```Ignores the rest of the labeled arguments following this flag.

```--version          ```Displays version information and exits.

```-h   --help        ```Displays usage information and exits.

## E. Tests
The tests check the fonctionnement of the program. The file test_main.cpp execute all the tests, which are split into three seperate files: test_readfasta.cpp, test_multibinomial and test_simulation_migration.cpp. To execute thoses tests the command is:

```./testWrightFisher``` or ```make test```
