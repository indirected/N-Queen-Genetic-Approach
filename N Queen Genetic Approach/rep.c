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
  if(gen%100 == 0 || p->highestEverFitness == 1)
	rawStat(stdout, p, pop);


}

void rawStat(FILE *fp, POPULATION *p, IPTR pop)
{
	fprintf(fp," %5d | %10.5lf |%10.5lf |%10.5lf|", p->gen, p->max,
		p->avg, p->min);
	fprintf(fp,"%12d|%12.5lf|%8d\n", p->highestEverGen,  p->highestEverFitness,
		p->highestEverIndex);
	//fprintf(fp,"   %d-Queen\n", p->lchrom);
}

