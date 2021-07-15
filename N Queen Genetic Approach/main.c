#include <math.h>
#include <stdio.h>
#include "conio.h"
#include "type.h"
int erfunc(char *s, int val);
void initialize(char *argv[], POPULATION *p);
void generation(POPULATION *p, int gen);
void report(int gen, POPULATION *p, IPTR  pop);
void statistics(POPULATION *p, IPTR pop);

main(int argc, char *argv[])
{
  IPTR tmp, op, np;
  POPULATION population;
  POPULATION *p = &population;

  p->gen = 0;
  //if(argc != 2) erfunc("Usage: ga <inputfile name> ", argc);
  initialize(argv, p);
  //p->highestEverFitness = -_CRT_INT_MAX;
  while(/*p->gen < p->maxGen && */p->highestEverFitness< 1/*(p->lchrom) * (p->lchrom - 1)/2*/){
    p->gen++;
	 generation(p, p->gen);
	 statistics(p, p->np);
	 report(p->gen, p, p->np);
    tmp = p->op;
    p->op = p->np;
    p->np = tmp;
  }
  printf("\n");

      for (int i = 0; i < p->lchrom; i++) {
          printf("%d ", p->op[p->highestEverIndex].chrom[i]);
      }

      //bahrami

    /*//To Test Eval
    POPULATION a;
    a.lchrom = 8;
    INDIVIDUAL b = { {1,2,3,4,5,6,7,8} };
    eval(&a, &b);*/


    /*//To Test Crossover
    warmup_random(0.2);
    POPULATION a;
    a.lchrom = 6;
    a.pCross = 1;
    INDIVIDUAL b = { {1,6,4,2,5,3} };
    INDIVIDUAL c = { {4,2,5,3,6,1} };
    INDIVIDUAL d = { {0,0,0,0,0,0} };
    INDIVIDUAL e = { {0,0,0,0,0,0} };

    crossover(&a, &b, &c, &d, &e);
    for (int i = 0; i < a.lchrom; i++) printf("%d ", d.chrom[i]);
    printf("\n");
    for (int i = 0; i < a.lchrom; i++) printf("%d ", e.chrom[i]);*/


}
