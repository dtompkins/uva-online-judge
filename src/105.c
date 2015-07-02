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

