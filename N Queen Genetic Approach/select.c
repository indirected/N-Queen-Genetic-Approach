
#include "type.h"

double f_random();
int rnd(int low, int high);

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

int Tournoment(IPTR pop, int popsize, int lchrom ) {
    int t1, t2;
    do {
        t1 = rnd(0, popsize - 1);
        t2 = rnd(0, popsize - 1);
    } while (t1 == t2);
    int scaled_fitness[2];

    if (pop[t1].fitness > pop[t2].fitness) {
        scaled_fitness[0] = 2/3;
        scaled_fitness[1] = 1/3;

    }
    else {
        scaled_fitness[1] = 2/3;
        scaled_fitness[0] = 1/3;
    }

    double rand = f_random();
    if (scaled_fitness[0] > rand) return t1;
    else return t2;
}

