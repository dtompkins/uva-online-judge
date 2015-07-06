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

char grid[50][51];
char words[20][51];
int t, T;
int n, N;
int W, H;

void tolower(char *w) {
  char *c = w;
  while (*c) {
    if ((*c >= 'A')&&(*c <= 'Z')) *c = *c - 'A' + 'a';
    c++;
  }
}

int find_word(int x, int y, char *w, int dir_x, int dir_y) {
  int i;
  int len = strlen(w);
  for (i=0; i < len; i++) {
    if ((x < 0)||(x >= W)) return 0;
    if ((y < 0)||(y >= H)) return 0;
    if (grid[y][x] != w[i]) return 0;
    x += dir_x;
    y += dir_y;
  }
  return(1);
}

int main(void) {
  int h, x, y, found, dx, dy;
  scanf("%d", &T);
  for (t=0; t < T; t++) {
    scanf("%d %d", &H, &W);
    for (h=0; h < H; h++) {
      scanf("%s", &grid[h]);
      tolower(grid[h]);
    }
    scanf("%d", &N);
    for (n=0; n < N; n++) {
      scanf("%s", &words[n]);
      tolower(words[n]);
    }
    if (t) printf("\n");
    for (n=0; n < N; n++) {
      found = 0;
      for (y=0; y < H; y++) {
        for (x=0; x < W; x++) {
          for (dx=-1; dx <= 1; dx++) {
            for (dy=-1; dy <= 1; dy++) {
              if (dx || dy) found = find_word(x, y, words[n], dx, dy);
              if (found) break;
            }
            if (found) break;
          }
          if (found) break;
        }
        if (found) break;
      }
      printf("%d %d\n", y+1, x+1);
    }
  }
}
