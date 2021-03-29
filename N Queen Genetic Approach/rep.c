#include <stdio.h>
#include <stdlib.h>

#include "type.h"

void rawStat(FILE *fp, POPULATION *p, IPTR pop);
//void rawStat();

void report(int gen, POPULATION *p, IPTR  pop)
{ /* report generations stats */
  FILE *fp;

  if( (fp = fopen(p->ofile, "a")) == NULL){
	 printf("error in opening file %s \n", p->ofile);
	 exit(1);
  }else{
	 rawStat(fp, p, pop);
	 fclose(fp);
  }
  rawStat(stdout, p, pop);


}

void rawStat(FILE *fp, POPULATION *p, IPTR pop)
{
  fprintf(fp," %3d %10.2lf %10.2lf %10.2lf ", p->gen, p->max,
	  p->avg, p->min);
  fprintf(fp," %3d %10.2lf %3d", p->highestEverGen,  p->highestEverFitness,
	  p->highestEverIndex);
  fprintf(fp,"   %d-Queen\n", p->lchrom);
}

