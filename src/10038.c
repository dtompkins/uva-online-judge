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

  * lame: I accidentally used exit(1) instead of exit(0) and
    couldn't figure out why it was saying "runtime error"
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

int diff[3002];
int N;

void init_diff(void) {
  int i;
  for (i=1; i <= N-1; i++) {
    diff[i] = 0;
  }
}

int is_good(int d) {
  if (d < 0) d *= -1;
  if (d == 0) return 0;
  if (d > N - 1) return 0;
  if (diff[d]) return 0;
  diff[d] = 1;
  return 1;
}


int main(void) {
  int i;
  int jolly;
  int prev;
  int next;

  while(1) {
    if (scanf("%d", &N) != 1) {
      exit(0);
    }
    init_diff();
    jolly = 1;
    if (N) scanf("%d", &prev);
    for (i=1; i < N; i++) {
      scanf("%d", &next);
      if ((jolly)&&(!is_good(next - prev))) jolly = 0;
      prev = next;
    }
    if (jolly) {
      printf("Jolly\n");
    } else {
      printf("Not jolly\n");
    }
  }
}
