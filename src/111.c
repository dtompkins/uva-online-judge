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

