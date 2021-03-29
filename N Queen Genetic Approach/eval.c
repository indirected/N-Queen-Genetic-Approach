#include <stdio.h>
#include <math.h>    /* for pow(x, y) */
#include "type.h"
#include <stdlib.h>

double decode(IPTR pj, int index, int size);
double binToDec(int *chrom, int l);
double __eval(POPULATION* p, IPTR pj);

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

double eval(POPULATION *p, IPTR pj) 
     /* Called from gen.c and init.c */
{
    //int GuardSum = 0;
    //int GuardMax = p->lchrom * (p->lchrom - 1) / 2;
    //for (int i = 1; i < p->lchrom; i++) {
    //    GuardSum += GuardCount(pj, i,p->lchrom);
    //}
    ////printf("%d", GuardSum);

    //return 1 - ((double)GuardSum / GuardMax);
    ////return (double)GuardMax - GuardSum;
    return (double)__eval(p, pj);
}


double __eval(POPULATION* p, IPTR pj) {
    int t1 = 0;
    int t2 = 0;
    
    int len = p->lchrom;
    int* f1 = (int*)malloc(p->lchrom * sizeof(int));
    int* f2 = (int*)malloc(p->lchrom * sizeof(int));
  
    for (int i = 0; i < len; i++) {
        f1[i] = pj->chrom[i] - i;
        f2[i] = 1 + len - pj->chrom[i] - i;
    }
    qsort(f1, len, sizeof(int), compare);
    qsort(f2, len, sizeof(int), compare);
    for (int i = 1; i < len; i++) {
        if (f1[i] == f1[i - 1]) t1++;
        if (f2[i] == f2[i - 1]) t2++;
    }
    return -t1 - t2;
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
