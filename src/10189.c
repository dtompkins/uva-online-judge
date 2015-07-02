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
#include <limits.h>

#pragma warning(disable: 4996)

char minefield[102][102];
int rows;
int cols;

void clear_minefield(void) {
  int i,j;
  for (i=0; i < 102; i++) {
    for (j=0; j < 102; j++) {
      minefield[i][j] = 0;
    }
  }
}

int count_mines(char *three) {
  int c = 0;
  if (three[0] == '*') c++;
  if (three[1] == '*') c++;
  if (three[2] == '*') c++;
  return c;
}

int main(void) {

  int i,j;
  char *above, *mid, *below;
  int numfield = 0;
  while (1) {
    numfield++;
    if (scanf("%d %d", &rows, &cols) != 2) {
      exit(0);
    }
    if ((rows == 0)&&(cols == 0)) {
      exit(0);
    }

    for (i=0; i < rows; i++) {
      scanf("%s", &minefield[i + 1][1]);
    }

    for (i=1; i <= rows; i++) {
      above = &minefield[i-1][0];
      mid = &minefield[i][0];
      below = &minefield[i+1][0];
      for (j=1; j <= cols; j++) {
        if (minefield[i][j] == '.') {
          minefield[i][j] = count_mines(above) + count_mines(mid) + count_mines(below) + '0';
        }
        above++;
        mid++;
        below++;
      }
    }

    if (numfield > 1) {
      printf("\n");
    }
    printf("Field #%d:\n", numfield);
    for (i=1; i <= rows; i++) {
      printf("%s\n", &minefield[i][1]);
    }
    clear_minefield();
  }
}

