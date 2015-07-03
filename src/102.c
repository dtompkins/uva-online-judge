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

********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

int B[3];
int G[3];
int C[3];

char solutions[6][4] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

int *char_to_array(char c) {
  if (c == 'B') return B;
  if (c == 'G') return G;
  if (c == 'C') return C;
  return NULL;
}

int moves(int a[], int bin) {
  return a[0] + a[1] + a[2] - a[bin];
}

int eval_sol(char *sol) {
  int total = 0;
  int i;
  for (i=0; i < 3; ++i) {
    total += moves(char_to_array(sol[i]), i);
  }
  return total;
}

int main(void) {
  int i;
  int score;
  int bestid;
  int best = 0;

  while (1) {
    if (scanf("%d %d %d %d %d %d %d %d %d", &B[0], &G[0], &C[0],
                                            &B[1], &G[1], &C[1],
                                            &B[2], &G[2], &C[2]) != 9) {
      exit(0);
    }

    for (i = 0; i < 6; i++) {
      score =  eval_sol(solutions[i]);
      if (i == 0 || score < best) {
        bestid = i;
        best = score;
      }
    }

    printf("%s %d\n", solutions[bestid], best);
  }
}