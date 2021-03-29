#include <stdio.h>
#include <math.h>    /* for pow(x, y) */
#include "type.h"

double decode(IPTR pj, int index, int size);
double binToDec(int *chrom, int l);

double eval(POPULATION *p, IPTR pj) 
     /* Called from gen.c and init.c */
{
    int GuardSum = 0;
    int GuardMax = p->lchrom * (p->lchrom - 1) / 2;
    for (int i = 1; i < p->lchrom; i++) {
        GuardSum += GuardCount(pj, i,p->lchrom);
    }
    //printf("%d", GuardSum);

    //return 1 - ((double)GuardSum / GuardMax);
    return (double)GuardMax - GuardSum;
}

double decode(IPTR pj, int index, int size)
{
  return ((double) binToDec(&(pj->chrom[0]), size));
}

double binToDec(int *chrom, int l)
{
  int i;
  double prod;

  prod = 0.0;

  for(i = 0; i < l; i++){
    prod += (chrom[i] == 0 ? 0.0 : pow((double)2.0, (double) i));
  }
  return prod;
}

void decToBin(int ad, int *barray, int size)
{
  int i, t;

  t = ad;
  for(i = 0; i < size; i++){
    barray[i] = t%2;
    t = t/2;
  }
}


//To Count the Queens that Threat each other from 0 to i
int GuardCount(IPTR pi, int i,int popsize) {
    int count = 0;
    for (int j = 0; j < i; j++) {
        if (j != i) {
            int diff = pi->chrom[i] - pi->chrom[j];
            if (i - j == diff || i - j == -diff) count++;
        }
    }
    return count;
}
