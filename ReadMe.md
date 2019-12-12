# Wright-Fisher Simulation
The program is an implementation of the model of Wright-Fisher. This model does not take into account the environmental factors and focuses only on the generation drift, which is an evolutionary mechanism where the frequencies of alleles in a population vary randomly in time. That means the alleles does not change but only their frequencies. To define the new frequencies at each generation we use the multibinomial distribution.

## A. Run the program
These instructions allow to get a copy of the project, compile this one and create the documentation. 
```
0 _git clone https://github.com/EPFL-SV-cpp-projects/Team_13.git   
1 cd Team_13  
2 mkdir build   
3 cd build   
4 cmake ..  
5 make  
6 make doc  
```

## B. Use read_fasta
The fasta file have to contain nucleotides sequences composed of A, T, C, G or N. In this last case, N will be replaces randomly by an other nucleotide. Other lines (chromosome number) have to start with ">" symbol.
Example:
```
>chr11 
CACTGTGTNTGATGATCAACAAAAACCTGGGGGGGGTAGTAGTAGTCC
>chr7 
AAATGGTGCGTGATGCCCCCCCCCCCCNCCTTGTGAAAA
```

## C.Usage and parameters

### 1. From the terminal (without fasta file)
#### usage
``` ./WrightFisher  {-T|-P} [-N <int>] [-G <int>] [-f <double>] [-R <double>] ```
#### parameters
```-N -Size         <int>     ``` The size of the population, i.e:  number of individuals per population.

```-G -Generations  <int>     ``` Duration of the simulation, i.e: the number of generations.

```-f -frequences   <double>  ``` (required)(accepted multiple times)List of the initials frequencies of the alleles.

```-R -Repetitions  <int>     ``` Number of time the simulation is repeat with the same parameters. 

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

```-M -Migration    <string>   ```A migration type between star ring or complete.

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

## D. Tests
The tests check the fonctionnement of the program. The file test_main.cpp execute all the tests, which are split into three seperate files: test_readfasta.cpp, test_multibinomial and test_simulation_migration.cpp. To execute thoses tests the command is:

```./testWrightFisher```
