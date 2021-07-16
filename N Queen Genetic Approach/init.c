#include <stdio.h>
#include <stdlib.h>  /* for calloc */
#include <string.h>
#include "type.h"

//Random Functions -> random.c
int flip(double p);
void randomize(POPULATION *p);
int* CreateShuffledArray(int);


void statistics(POPULATION *p, IPTR pop);

void rawStat(FILE *fp, POPULATION *p, IPTR pop);

double eval(POPULATION *p, IPTR pi);


void initData(char *inputFile, POPULATION *p);
void initPop(POPULATION *p);
void initReport(POPULATION *p);

void initialize(char *argv[], POPULATION *p)
{ /* initialize everything */

  char *Ifile;
  int  nameLength = strlen(argv[1]);
  Ifile = (char *) calloc(nameLength + 1, sizeof(char));
  strcpy(Ifile, argv[1]);

  initData(Ifile, p);
  printf("after initData\n");

  initPop(p);
  printf("after initPOP\n");

  statistics(p, p->op);
  printf("after STATS\n");

  initReport(p);
}

void initData(char *Ifile, POPULATION *p)
{ /* inittialize global params,

	  popsize:   population size
	  lchrom :   chromosome lenght
	  maxgen :   maximum no. of generations.
	  pcross :   crossover probability
	  pmut   :   mutation probability           */
  int i;
  //FILE *inpfl;
  char tmp[1024];


  ////Best Values
  //char tmp[] = "ofile";
  //p->lchrom = 1000;
  //p->popSize = 50;
  //selectionmethod = TournamentSelection;
  //crossovermethod = PartiallyMapped;
  //mutationmethod = Swap;
  //p->pCross = 0.6;
  //p->pMut = 0.4;






  /*if( (inpfl = fopen(Ifile,"r")) == NULL){
	 printf("error in opening file %s \n", Ifile);
	 exit(1);
  }*/

  printf("Enter chromosome length.(The N in N-Queen) - lChrom-> ");
  scanf("%d", &p->lchrom);
  //fscanf(inpfl,"%d",&p->lchrom);


  printf("Enter population size - popSize-> ");
  scanf("%d", &p->popSize);
  //fscanf(inpfl,"%d",&p->popSize);
  if(p->popSize % 2 != 0) {
	 p->popSize++;
	 printf("\nNote population size must be even. New popoulation size: %i\n", p->popSize);
  }
  


  printf("Enter max. generations - maxGen-> ");
  scanf("%d", &p->maxGen);
  //fscanf(inpfl,"%d",&p->maxGen);


  printf("Enter Selection Method.(1 or 2)\n\t 1.Roulette Wheel\n\t 2.Tournament\n");
  do{
	  printf("selectionmethod-> ");
	  scanf("%d", &selectionmethod); 
  } while(selectionmethod != 1 && selectionmethod != 2);

  

  printf("Enter Crossover Method.(1 or 2)\n\t 1.Partially Mapped Crossover\n\t 2.Order One Crossover\n");
  do { 
	  printf("crossovermethod-> ");
	  scanf("%d", &crossovermethod); 
  }
  while (crossovermethod != 1 && crossovermethod != 2);


  printf("Enter Mutation Method.(1 or 2)\n\t 1.Swap Mutation\n\t 2.Displacement Mutation\n");
  do {
	  printf("mutationmethod-> ");
	  scanf("%d", &mutationmethod); 
  } while (mutationmethod != 1 && mutationmethod != 2);


  printf("Enter crossover probability - pCross-> ");
  scanf("%lf", &p->pCross);
  //fscanf(inpfl,"%lf",&p->pCross);


  printf("Enter mutation probability - pMut-> ");
  scanf("%lf", &p->pMut);
  //fscanf(inpfl,"%lf",&p->pMut);


  printf("Enter file name for graph output -fname-> ");
  scanf("%s", tmp);
  //fscanf(inpfl,"%s", tmp);

  

  p->ofile = (char *)calloc(strlen(tmp)+1, sizeof(char));
  strcpy(p->ofile, tmp);
  //printf("Save file is %s\n", p->ofile);
  FILE* fp = fopen(p->ofile, "w");
  fclose(fp);

  printf("\n");

  randomize(p); /* initialize random number generator */

  /* set progress indicators to zero */
  p->highestEverFitness = 0.0;
  p->highestEverGen = 0;
  p->highestEverIndex = 0;

}


void initPop(POPULATION *p)
{ /* initialize a random population */
  IPTR pi, pj;
  int i, j;
  FILE *fp;
  double f1;
  int* currentShuffle;
  p->op = (IPTR)calloc(p->popSize, sizeof(INDIVIDUAL));
  p->np = (IPTR)calloc(p->popSize, sizeof(INDIVIDUAL));


  for(i = 0; i < p->popSize; i++){
	 
	 pi = &(p->op[i]);
	 pi->chrom = (int *)calloc(p->lchrom, sizeof(int));

	 pj = &(p->np[i]);
	 pj->chrom = (int *)calloc(p->lchrom, sizeof(int));

	 currentShuffle = CreateShuffledArray(p->lchrom);
	 for (j = 0; j < p->lchrom; j++){
		 pi->chrom[j] = currentShuffle[j];

	 }
	 free(currentShuffle);
	 pi->fitness  = eval(p, pi);

  }
}


void initReport(POPULATION *p)
{
  FILE *fp;
  int i, k;
  printf("==================================================\n");
  printf("\n\nPopulation Size(popsize)  %d\n", p->popSize);
  printf("Chromosome length (lchrom)  %d\n", p->lchrom);
  printf("Maximum num of generations(maxgen)  %d\n", p->maxGen);
  printf("Crossover Probability (pcross)  %lf\n", p->pCross);
  printf("Mutation Probability (pmut)  %lf\n", p->pMut);
  printf("\n\t\tFirst Generation Stats  \n\n");
  printf("Maximum Fitness  %lf\n", p->max);
  printf("Average Fitness  %lf\n", p->avg);
  printf("Minimum Fitness  %lf\n", p->min);
  printf("==================================================\n");


  if ((fp = fopen(p->ofile, "a")) == NULL) {
	  printf("error in opening file %s \n", p->ofile);
	  exit(1);
  }
  else {
	  fprintf(fp, "   gen |  CurGenMax |CurGenAvg  |CurGenMin |HghstEverGen|HghstEverFit|HghstEverIdx\n");
	  printf("   gen |  CurGenMax |CurGenAvg  |CurGenMin |HghstEverGen|HghstEverFit|HghstEverIdx\n");
	  fclose(fp);
  }


  if( (fp = fopen(p->ofile, "a")) == NULL){
	 printf("error in opening file %s \n", p->ofile);
	 exit(1);
  }else{
	 rawStat(fp, p,  p->op);
	 fclose(fp);
  }
  rawStat(stdout, p, p->op);
}

