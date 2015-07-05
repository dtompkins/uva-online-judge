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
#include <limits.h>

#pragma warning(disable: 4996)

int attempted[101];
int numsolved[101];
int solved[101][11];
int time[101];
int sortorder[101];

void reset(void) {
  int i,j;
  for (i=0; i <= 100; i++) {
    attempted[i] = 0;
    numsolved[i] = 0;
    time[i] = 0;
    for (j=1; j <= 9; j++) {
      solved[i][j] = 0;
    }
    sortorder[i] = i;
  }
}

int t,T;

char line[4096];

int blank_line(void) {
  int i;
  int len = strlen(line);
  for (i=0; i < len; i++) {
    if (line[i] != ' ') return 0;
  }
  return 1;
}

int compare_contestant(const void *aa, const void *bb) {
  int a = *(int *)aa;
  int b = *(int *)bb;
  int ret;
  ret = numsolved[b] - numsolved[a];
  if (ret == 0) {
    ret = time[a] - time[b];
    if (ret == 0) {
      ret = a - b;
    }
  }
  return ret;
}

int main(void) {
  int i;
  int c, p, ptime;
  char r;

  gets(line);
  if (sscanf(line, "%d", &T) != 1) {
    exit(0);
  }
  gets(line);
  for (t=0; t < T; t++) {
    reset();
    while (1) {
      if (gets(line) == NULL) break;
      if (blank_line()) break;
      sscanf(line,"%d %d %d %c", &c, &p, &ptime, &r);
      attempted[c] = 1;
      if ((r == 'C')&&(solved[c][p]<=0)) {
        time[c] += ptime + (solved[c][p] * -20);
        solved[c][p] = 1;
        numsolved[c]++;
      }
      if ((r == 'I')&&(solved[c][p]<=0)) {
        solved[c][p]--;
      }
    }

    qsort(sortorder + 1, 100, sizeof(int), compare_contestant);

    if (t) printf("\n");
    for (i=1; i <= 100; i++) {
      c = sortorder[i];
      if (attempted[c]) {
        printf("%d %d %d\n", c, numsolved[c], time[c]);
      }
    }
  }
}
