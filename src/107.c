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

int N, W, H;

int main(void) {
  int i;
  int numcats;
  int found;
  int curheight;
  int sumheight;
  int lazy;

  while (1) {
    if (scanf("%d %d", &H, &W) != 2) {
      exit(0);
    }
    if ((H == 0) && (W == 0)) {
      exit(0);
    }
    if ((H == 1) && (W == 1)) {
      printf("%d %d\n", 0, 1);
      continue;
    }    
    N = 0;
    found = 0;
    while (1) {
      N++;
      if (W % N) continue;
      numcats = W;
      curheight = 1;
      sumheight = W;
      lazy = 0;
      i = 0;
      while (1) {
        i++;
        numcats /= N;
        lazy += numcats;
        curheight *= (N+1);
        sumheight += numcats * curheight;
        if ((numcats == 1) && (curheight == H)) {
          found = 1;
          break;
        }
        if ((curheight > H) || (numcats % N)) {
          break;
        }
      }
      if (found) break;
    }
    printf("%d %d\n", lazy, sumheight);
  }
}

