#define MAXCITY 31  /* max no of cities*/
typedef struct {
  int chrom[MAXCITY];   /* the chromosome */
  double fitness;   
  int parent1;
  int parent2;
} INDIVIDUAL;

typedef INDIVIDUAL *IPTR;

typedef struct {

  IPTR op;       /* arrays of individuals form an evolving population*/
  IPTR np;
  
  int    lchrom;  /* chromosome length */
  int    gen;     /* current generation */

  double sumFitness; /* statistics parameters for selection and tracking*/
  double max;        /* progress */
  double avg;
  double min;

  double pCross;        /* probability of Xover */
  double pMut;          /* probability of Mutation */
  double randomseed;  

  
  double highestEverFitness;
  int    highestEverGen;
  int    highestEverIndex;

  int    maxi; /* index of best individual in current population*/
  int    mini; /* index of worst individual in current population*/

  int    maxGen; /* when to stop */
  int    popSize;/* population size */

  char  *ofile;  /* output File name */
} POPULATION;
