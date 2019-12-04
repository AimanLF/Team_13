#ifndef MULTIBINOMIAL
#define MULTIBINOMIAL

#include <vector>
#include <random>

/*!
  Calculation of the new alleles frequencies following a multibinomiale law
  \param N: total number of individuals in the populaiton
  \param f : alleles frequencies of the population at a certain time-step t
  \return a table contianing the new alleles frquencies at time step t+1
*/ 
std::vector<double> multibinomial (int N, std::vector<double> f);

/*!
  \param a: inferior bound of the uniform distribution
  \param b : upper bound of the uniform distribution
  \return a int randomly generated following a uniform distribution
*/ 
int randomUniform (int a, int b);

#endif
