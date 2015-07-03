/********************************************************************
  !!! DISCLAIMER !!! 
  
  This code is _really_ "quick & dirty".  It is NOT pretty.
  
  It solves a problem from the UVa Online Judge library.
  https://uva.onlinejudge.org/
  The problem # is the name of the file.
  
  See the README.md for more information.
  
  --Dave
*********************************************************************
POST-MORTEM NOTES (if any):

  * 1st try: didn't consider 1 2 1 2
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

int dim;

typedef double ttable[20][20];
typedef int tseq[20][20][22];

double exchange[20][20];
double bestrate_odd[20][20];
double bestrate_even[20][20];
int bestseq_odd[20][20][22];
int bestseq_even[20][20][22];

double (*currate)[20];
double (*nextrate)[20];

int (*curseq)[20][22];
int (*nextseq)[20][22];

int compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int main(void) {
  int i,j,k,seq;
  int newbest;
  double bestrate, rate;
  int found;

  while (1) {
    if (scanf("%d", &dim) != 1) {
      exit(0);
    }
    found = 0;
    for (i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++) {
        if (i == j) {
          exchange[i][j] = 1.0;
        } else {
          scanf("%lf", &exchange[i][j]);
        }
        bestrate_odd[i][j] = exchange[i][j];
        bestseq_odd[i][j][0] = i;
        bestseq_odd[i][j][1] = j;
      }
    }

    for (seq=2; seq <= dim; seq++) {
      if (seq % 2 == 0) {
        nextrate = bestrate_even;
        nextseq = bestseq_even;
        currate = bestrate_odd;
        curseq = bestseq_odd;
      } else {
        nextrate = bestrate_odd;
        nextseq = bestseq_odd;
        currate = bestrate_even;
        curseq = bestseq_even;
      }

      for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
          newbest = 0;
          bestrate = 0.0;
          for (k = 0; k < dim; k++) {
            rate = currate[i][k] * exchange[k][j];
            if (rate > bestrate) {
              bestrate = rate;
              newbest = k;
            }
          }
          nextrate[i][j] = bestrate;
          for (k = 0; k < seq; k++) {
            nextseq[i][j][k] = curseq[i][newbest][k];
          }
          nextseq[i][j][seq] = j;
        }
      }
      for (i = 0; i < dim; i++) {
        if (nextrate[i][i] > 1.01) {
          found = 1;
          break;
        }
      }
      if (found) break;
    }
    if (found) {
      printf("%d", nextseq[i][i][0] + 1);
      for (k=1; k <= seq; k++) {
        printf( " %d", nextseq[i][i][k] + 1);
      }
      printf("\n");
    } else {
      printf("no arbitrage sequence exists\n");
    }
  }
}

