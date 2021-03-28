#include "type.h"

int rnd(int low, int high);
int flip(double);
int muteX(POPULATION *p, int pa, int pb);

void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2)
{
/* p1,p2,c1,c2,m1,m2,mc1,mc2 */
  int *pi1,*pi2,*ci1,*ci2;
  int xp, i;

  pi1 = p1->chrom;
  pi2 = p2->chrom;
  ci1 = c1->chrom;
  ci2 = c2->chrom;
  
  if(flip(p->pCross)){

    xp = rnd(0, p->lchrom - 1);
    for(i = 0; i < xp; i++){
      ci1[i] = muteX(p, pi1[i],pi2[i]);
      ci2[i] = muteX(p, pi2[i],pi1[i]);
    }
    for(i = xp; i < p->lchrom; i++){
      ci1[i] = muteX(p, pi2[i],pi1[i]);
      ci2[i] = muteX(p, pi1[i],pi2[i]);
    }
  } else {
    for(i = 0; i < p->lchrom; i++){
      ci1[i] = muteX(p, pi1[i],pi2[i]);
      ci2[i] = muteX(p, pi2[i],pi1[i]);
    }
  }
}

int muteX(POPULATION *p, int pa, int pb)
{
  return (flip(p->pMut) ? 1 - pa  : pa);
}



