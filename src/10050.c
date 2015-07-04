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

int t,T;
int n,N;
int p,P;
int days[3660];

int main(void) {
  int i,h,count;
  
  if (scanf("%d", &T) != 1) {
    exit(0);
  }

  for (t=0; t < T; t++) {
    scanf("%d", &N);
    for (i=0; i < N; i++) {
      days[i] = 0;
    }
    scanf("%d", &P);
    for (p=0; p < P; p++) {
      scanf("%d", &h);
      for (i=h-1; i < N; i += h) {
        if (i % 7 < 5) days[i] = 1;
      }
    }
    count = 0;
    for (i=0; i < N; i++) {
      count += days[i];
    }
    printf("%d\n", count);
  }
}
