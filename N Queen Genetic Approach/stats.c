#include <stdio.h>
/*#include <math.h>*/


#include "type.h"

void statistics(POPULATION *p, IPTR pop)
{ /* calculate population stats */
  int size, i, j, s;
  IPTR pi;

  p->sumFitness = pop[0].fitness;
  p->max = p->sumFitness;
  p->min = p->sumFitness;
  p->maxi = p->mini = 0;
  for(i = 1; i < p->popSize; i++){
    pi = &(pop[i]);
    p->sumFitness += pi->fitness; 
    if (p->max < pi->fitness) {
      p->max = pi->fitness;   p->maxi = i;
    }
    if (p->min > pi->fitness){
      p->min = pi->fitness;   p->mini = i;
    }
  }
  p->avg = p->sumFitness / (double) p->popSize;
  if(p->highestEverFitness < p->max) {
    p->highestEverFitness = p->max; 
    p->highestEverGen = p->gen; 
    p->highestEverIndex = p->maxi;
  }
}
