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

int grid[100][100];
int N;
int W;
int offset;

int max1d(int a[], int len) {
  int maxsofar = 0;
  int maxendinghere = 0;
  int curitem;
  int i;
  for (i=0; i < len; i++) {
    curitem = a[i];
    maxendinghere = (maxendinghere + curitem) > 0 ? (maxendinghere + curitem) : 0;
    maxsofar = maxendinghere > maxsofar ? maxendinghere : maxsofar;
  }
  return maxsofar;
}

int max2d(int row, int width) {
  int maxsofar = 0;
  int maxendinghere = 0;
  int curitem;
  int i,j;
  for (i=0; i < N; i++) {
    curitem = 0;
    for (j=0; j < width; j++) {
      curitem += grid[row+j][i];
    }
    maxendinghere = (maxendinghere + curitem) > 0 ? (maxendinghere + curitem) : 0;
    maxsofar = maxendinghere > maxsofar ? maxendinghere : maxsofar;
  }
  return maxsofar;
}

int main(void) {
  int i,j;
  int width, newmax, maxsofar;

  while (1) {

    if (scanf("%d", &N) != 1) {
      exit(0);
    }

    for (i=0; i < N; i++) {
      for (j=0; j < N; j++) {
        scanf("%d", &grid[i][j]);
      }
    }

    maxsofar = 0;

    for (width=1; width <= N; width++) {
      for (i=0; i <= N - width; i++) {
        newmax = max2d(i, width);
        maxsofar = newmax > maxsofar ? newmax : maxsofar;
      }
    }
    printf("%d\n", maxsofar);
  }
}
