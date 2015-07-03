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

  * very annoying notation
  * Took me for ever to realize how the @#%@#$ last line scores 9
      10
      3 1 2 4 9 5 10 6 8 7
      1 2 3 4 5 6 7 8 9 10
      4 7 2 3 10 6 9 1 5 8
      3 1 2 4 9 5 10 6 8 7
      2 10 1 3 8 4 9 5 7 6 => 3 7 2 1 9 4 5 6 10 8 ???
  * had to re-re-re-read the question
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

int ranking[21];
int student_ranking[21];
int ord[21];

int N;

int mymax(int a, int b) {
  return a > b ? a : b;
}

int bestseq(int pos, int lensofar, int maxsofar, int bestsofar) {
  /* early exit */
  int len1, len2;
  if (pos == N) {
    return mymax(lensofar, bestsofar);
  }
  if (ord[pos] < maxsofar) {
    return bestseq(pos + 1, lensofar, maxsofar, bestsofar);
  } else {
    len1 = bestseq(pos + 1, lensofar + 1, ord[pos], bestsofar);
    len2 = bestseq(pos + 1, lensofar, maxsofar, mymax(len1,bestsofar));
    return mymax(len1,len2);
  }
}

int main(void) {
  int i;

  if (scanf("%d", &N) != 1) {
    exit(0);
  }

  for (i=1; i <= N; i++) {
    scanf("%d", &ranking[i]);
  }

  while (1) {
    for (i=1; i <= N; i++) {
      if (scanf("%d", &student_ranking[i]) != 1) {
        exit(0);
      }
      ord[student_ranking[i] - 1] = ranking[i];
    }
    printf("%d\n", bestseq(0, 0, -1, 0));
  }
}

