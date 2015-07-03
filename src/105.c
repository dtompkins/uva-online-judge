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

  * 1st try: very naive, one array entry per x
  * 2nd try: 2 entries per x -- failed on 0 width building? 
    debug test provided to that, but hard to say if problem spec
    allows for that
  * final try: add entries for in-between buildings (e.g., 10.5)
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

int skyline[20002];

int main(void) {
  int i;
  int l, h, r;
  int maxr = 0;
  int p;
  while (scanf("%d %d %d", &l, &h, &r) == 3) {
    if (r > maxr) {
      maxr = r;
    }
    for (i = l; i <= r; i++) {
      if (h > skyline[i*2]) {
        skyline[i*2] = h;
      }
      if (i < r) {
        if (h > skyline[i*2+1]) {
          skyline[i*2+1] = h;
        }
      }
    }
  }
  p = 0;
  for (i = 0; i < maxr; i++) {
    if (skyline[i*2] != p) {
      printf("%d %d ", i, skyline[i*2]);
      p = skyline[i*2];
    }
    if (skyline[i*2 + 1] != p) {
      printf("%d %d ", i, skyline[i*2 + 1]);
      p = skyline[i*2 + 1];
    }
  }
  printf("%d %d\n", maxr, 0);
}

