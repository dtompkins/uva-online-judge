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

  * I initially messed up the "ignore all invalid actions"
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma warning(disable: 4996)

#define maxblocks 25
int positions[maxblocks][maxblocks];
int count[maxblocks];
int location[maxblocks];
int height[maxblocks];

char command[5];
char method[5];

const char move[] = "move";
const char pile[] = "pile";
const char onto[] = "onto";
const char over[] = "over";
const char squit[] = "quit";

void clear_block(int a) {
  int loc = location[a];
  int c;
  while (count[loc] > height[a] + 1) {
    c = positions[loc][count[loc]-1];
    assert(count[c] == 0);
    count[c] = 1;
    positions[c][0] = c;
    location[c] = c;
    height[c] = 0;
    count[loc]--;
  }
}

int main(void) {

  int a, b, c;
  int i, j, n;
  int from, to, qty, start_height;
  if (scanf("%d", &n) != 1) {
    exit(0);
  }

  for (i=0; i<n; ++i) {
    count[i] = 1;
    positions[i][0] = i;
    location[i] = i;
    height[i] = 0;
  }

  while (1) {
    if (scanf("%s", command) != 1) {
      exit(0);
    }

    if (strcmp(command, squit) == 0) {
      for (i=0; i<n; ++i) {
        printf("%d:", i);
        for (j=0; j<count[i]; ++j) {
          printf(" %d", positions[i][j]);
        }
        printf("\n");
      }
      exit(0);
    }

    if (scanf("%d %s %d", &a, method, &b) != 3) {
      exit(0);
    }

    if (a != b && location[a] != location[b]) {
      if (strcmp(method, onto) == 0) {
        clear_block(b);
      }

      if (strcmp(command, move) == 0) {
        clear_block(a);
      }

      from = location[a];
      to = location[b];
      start_height = height[a];
      qty = count[from] - start_height;

      for (i=0; i<qty; i++) {
        c = positions[from][start_height + i];
        positions[to][count[to]] = c;
        location[c] = to;
        height[c] = count[to];
        count[to]++;
        count[from]--;
      }
    }
  }
}