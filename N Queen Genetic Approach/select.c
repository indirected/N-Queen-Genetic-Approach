
#include "type.h"

double f_random();

int roulette(IPTR pop, double sumFitness, int popsize)
{ 

  /* select a single individual by roulette wheel selection */
  
  double rand,partsum;
  int i;

  partsum = 0.0; i = 0;
  rand = f_random() * sumFitness; 
  
  i = -1;
  do{
    i++;
    partsum += pop[i].fitness;
  } while (partsum < rand && i < popsize - 1) ;
  
  return i;
}


