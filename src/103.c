/********************************************************************
  !!! DISCLAIMER !!! 
  
  This is *quick* and *dirty* and *disgusting* code.
  
  I'm completing some of the UVa Online Judge problems because:
  * I'm becoming old and decrepit, and this will help me stay sharp
  * It gives me ideas for designing my own assignments
  * It's fun
  
  For more information, visit https://uva.onlinejudge.org/
  The problem # is the name of the file.
  
  If any of my students are reading this, this is NOT good style.
  I must fall back to the classic: "Do as I say, not as I do"
*********************************************************************
POST-MORTEM NOTES (if any):

  * 1st try: messed up -- went smallest -> largest dimension
    I assumed smallest box was always in... counterexample:
       1 1 100
       2 2 2
       3 3 3
  * 2nd try: selection sort: find the biggest box (nothing fits)
    that didn't work either
  * 3rd try: more clever caching recursion
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

typedef int box[10];
box sequence[30];

int canfit[30][30];
int nextfit[30];
int bestfit[30];

int sortorder[30];
int keep[30];
int dimension;
int numseq;

int compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int inside(int a, int b) {
  int i = 0;
  for (i=0; i < dimension; i++) {
    if (sequence[a][i] >= sequence[b][i]) return 0;
  }
  return 1;
}


void sortbox(box b) {
  qsort(b, dimension, sizeof(int), compare);
}

int find_best_fit(int i) {
  int j;
  int score;
  int best = 1;
  if (bestfit[i]) return bestfit[i];
  nextfit[i] = -1;
  for (j = 0; j < numseq; j++) {
    if (canfit[i][j]) {
      score = find_best_fit(j) + 1;
      if (score > best) {
        best = score;
        nextfit[i] = j;
      }
    }
  }
  bestfit[i] = best;
  return best;
}

int main(void) {
  int i,j;
  int bestlen;
  int best;
  int score;

  while (1) {
    if (scanf("%d %d", &numseq, &dimension) != 2) {
      exit(0);
    }

    for (i = 0; i < numseq; i++) {
      for (j = 0; j < dimension; j++) {
        scanf("%d", &sequence[i][j]);
      }
      sortbox(sequence[i]);
      bestfit[i] = 0;
      nextfit[i] = -1;
    }

    for (i = 0; i < numseq; i++) {
      for (j = 0; j < numseq; j++) {
        canfit[i][j] = inside(i,j);
      }
    }

    bestlen = 0;
    best = 0;
    for (i = 0; i < numseq; i++) {
      score = find_best_fit(i);
      if (score > bestlen) {
        best = i;
        bestlen = score;
      }
    }

    printf("%d\n", bestlen);
    printf("%d", best + 1);
    while (nextfit[best] != -1) {
      best = nextfit[best];
      printf(" %d", best+1);
    }
    printf("\n");
  }
}

