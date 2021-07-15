/* randgen.c => contains random number generator and related utilities
   including advance_random, warmup_random, random, randomize
*/

#include "type.h"

#define RANCONST 1.0E-9
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* GLOBAL VARIABLES */

double oldrand[56];     /* array of 55 random numbers */
int    jrand;          /* current random */

/* FUNCTIONS */

void advance_random()   /* create next batch of 55 random numbers */
{
  int j1;
  double new_random;

/*  printf("Entering Advance Random\n");*/
  for (j1=1;j1<=24;j1++){
    new_random = oldrand[j1] - oldrand[j1+31];
    if (new_random < 0.0){
      new_random = new_random + 1.0;
    }
    oldrand[j1] = new_random;
  }
  for (j1=25;j1<=55;j1++){
    new_random = oldrand[j1] - oldrand[j1-24];
    if (new_random < 0.0){
      new_random = new_random + 1.0;
    }
    oldrand[j1] = new_random;
  }
/*  printf("leaving Advance Random\n");*/
}

void warmup_random(double random_seed)
{
  int    j1, ii;
  double new_random, prev_random;

  oldrand[55] = random_seed;
  new_random  = RANCONST;
  prev_random = random_seed;
  for (j1=1;j1<=54;j1++){
    ii = (21*j1) % 55;
    oldrand[ii] = new_random;
    new_random  = prev_random - new_random;
    if (new_random < 0.0){
      new_random += 1.0;
    }
    prev_random = oldrand[ii];
  }
  advance_random();
  advance_random();
  advance_random();
  jrand = 0;
}

double f_random()
{
/* Fetch a single random number between 0.0 and 1.0 - Substractive Method 
   See Knuth, D. (1969), v.2 for details */

  jrand++;
  if (jrand > 55){
    jrand = 1;
    advance_random();
  }
  return (oldrand[jrand]);
}

void randomize(POPULATION *p)  /* Get seed number for random and start it up */
{

  /*printf("Enter seed random number (0.0..1.0) > "); 
  scanf("%lf",&p->randomseed);
  while ( p->randomseed < 0.0 || p->randomseed > 1.0){
    printf("ERROR: Enter seed random number again (0.0..1.0) > ");
    scanf("%lf\n",&p->randomseed);
  }*/

    srand(time(NULL));
    p->randomseed = (double)rand() / RAND_MAX;


    warmup_random(p->randomseed);
}


int flip(double prob)
{/* Flip a biased coin...true if heads */

if (prob == 1.0) 
  return 1;
else 
  return (f_random() <= prob);

}

int rnd(int low, int high)
{ /* pick a random int between low and high */
  double fr;
  int i;
  fr = f_random();
  
  if(low >= high) {
    i = low;
  } else {
    i = ((int)(fr * (double)(high - low + 1)) + low);
    if (i > high) i = high;
  }
  return i;
}


/*Creates an array of size n
  Fills it with numbers 1 to n
  Then shuffles it.*/
int* CreateShuffledArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    int maxrand = n * 100;
    for (int i = 0; i < n; i++) {
        arr[i] = i+1;
    }
    
    for (int i = 0; i < n - 1; i++) {
        int j = i + rnd(1, maxrand) / (maxrand / (n - i) + 1);
        int t = arr[j];
        arr[j] = arr[i];
        arr[i] = t;
    }
   /* for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");*/
    return arr;
}