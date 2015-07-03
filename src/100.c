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

  * I originally cached every calculated value, but was running
    out of ram (I tried lots of things but had many run-time errors)
  * caching all the values < 10000 seemed to be "good enough"
  * annoying if j < i
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define maxcycles 10001
int cycles[maxcycles];

int get_cycles(int n) {
  int c = 0;
  if (n < maxcycles && cycles[n]) {
    return cycles[n];
  }
  if (n % 2 == 0) {
    c = get_cycles(n / 2) + 1;
  } else {
    c = get_cycles(3*n + 1) + 1;
  }
  if (n < maxcycles) {
    cycles[n] = c;
  }
  return c;
}

int main(void) {

  cycles[1] = 1;

  while (1) {
    int i, j, k;
    int small, big;
    int c;
    int max = 0;

    if (scanf("%d", &i) != 1) {
      exit(0);
    }

    if (scanf("%d", &j) != 1) {
      exit(0);
    }

    if (i < j) {
      small = i;
      big = j;
    } else {
      small = j;
      big = i;
    }

    for (k=small; k <= big; ++k) {
      c = get_cycles(k);
      if (c > max) max = c;
    }

    printf("%d %d %d\n", i, j, max);
  }
}
