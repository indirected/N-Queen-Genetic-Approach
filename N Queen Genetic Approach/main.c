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
  if(argc != 2) erfunc("Usage: ga <inputfile name> ", argc);
  initialize(argv, p);
  while(p->gen < p->maxGen){
    p->gen++;
	 generation(p, p->gen);
	 statistics(p, p->np);
	 report(p->gen, p, p->np);
    tmp = p->op;
    p->op = p->np;
    p->np = tmp;
  }



    /*//To Test Eval
    POPULATION a;
    a.lchrom = 8;
    INDIVIDUAL b = { {1,2,3,4,5,6,7,8} };
    eval(&a, &b);*/
}
