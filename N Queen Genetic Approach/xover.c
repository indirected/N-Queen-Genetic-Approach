#include <stdio.h>
#include "type.h"


int rnd(int low, int high);
int flip(double);
int muteX(POPULATION *p, int pa, int pb);
void Mutation(POPULATION* p, int* c);
void SwapMutation(POPULATION* p, int* c);
void DisplacementMutation(POPULATION* p, int* c);


void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2)
{
/* p1,p2,c1,c2,m1,m2,mc1,mc2 */
  int *pi1,*pi2,*ci1,*ci2;
  int xp, i;
  int StartPoint, EndPoint;

  pi1 = p1->chrom;
  pi2 = p2->chrom;
  ci1 = c1->chrom;
  ci2 = c2->chrom;
    
    //Crossover Method: Partially-Mapped Crossover
    if(flip(p->pCross)){ //Crossover Happens
        //printf("Entering Crossover.\n");


        //Copy the Parents in Childs
        for (int i = 0; i < p->lchrom; i++) {
            ci1[i] = pi1[i];
            ci2[i] = pi2[i];
        }

        //Find a Random Start and End
        StartPoint = rnd(0, p->lchrom - 1);
        EndPoint = rnd(0, p->lchrom - 1);

        //Making sure the EndPoint is Bigger
        if (StartPoint > EndPoint) {
            int t = StartPoint;
            StartPoint = EndPoint;
            EndPoint = t;
        }
        //printf("Start: %d, End: %d\n", StartPoint, EndPoint);


        //Doing the Crossover
        for (int i = StartPoint; i <= EndPoint; i++) {
            int currentC1 = ci1[i];
            int currentC2 = ci2[i];

            //Checking: If they are the same, Skip this index
            if (currentC1 == currentC2) continue;


            for (int j = 0; j < p->lchrom; j++) {
                if (ci1[j] == currentC2) ci1[j] = currentC1;
                if (ci2[j] == currentC1) ci2[j] = currentC2;
            }
            ci1[i] = currentC2;
            ci2[i] = currentC1;
        }

    } 
    else {
        //Copy the Parents in Childs
        for (int i = 0; i < p->lchrom; i++) {
            ci1[i] = pi1[i];
            ci2[i] = pi2[i];
        }
    }


    Mutation(p, ci1);
    Mutation(p, ci2);
    
}


void Mutation(POPULATION* p, int* c) {
    //DisplacementMutation(p, c);

    SwapMutation(p, c);
}



void SwapMutation(POPULATION* p, int* c) {
    if (flip(p->pMut)) {
        int Point1, Point2;
        do {
            Point1 = rnd(0, p->lchrom - 1);
            Point2 = rnd(0, p->lchrom - 1);
        } while (Point1 == Point2);
        int t = c[Point1];
        c[Point1] = c[Point2];
        c[Point2] = t;
    }
}


//Displacement Mutation
void DisplacementMutation(POPULATION* p, int* c) {
    if (flip(p->pMut)) {

        int SelectedQueen, InsertionPoint;
        do {
            SelectedQueen = rnd(0, p->lchrom - 1);
            InsertionPoint = rnd(0, p->lchrom - 1);
        } while (SelectedQueen == InsertionPoint);
        int temp = c[SelectedQueen];


        if (InsertionPoint < SelectedQueen) { //Shift Right
            int i;
            for (i = SelectedQueen; i > InsertionPoint; i--) {
                c[i] = c[i - 1];
            }
            c[i] = temp;
        }
        else { //Shift Left
            int i;
            for (i = SelectedQueen; i < InsertionPoint; i++) {
                c[i] = c[i + 1];
            }
            c[i] = temp;
        }

    }
}


int muteX(POPULATION *p, int pa, int pb)
{
  return (flip(p->pMut) ? 1 - pa  : pa);
}



