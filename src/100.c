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
