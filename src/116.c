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

int rows;
int cols;
int grid[10][100];

int prev[10][100];
int best[10][100];

int path1[100];
int path2[100];

void genpath(int c, int r, int *path) {
  while (c >= 0) {
    path[c] = r;
    r = prev[r][c];
    c--;
  }
}

int compare_paths(int c, int r1, int r2) {
  int i;
  if (best[r1][c] < best[r2][c]) return r1;
  if (best[r1][c] > best[r2][c]) return r2;
  genpath(c, r1, path1);
  genpath(c, r2, path2);
  for (i=0; i <= c; i++) {
    if (path1[i] < path2[i]) return r1;
    if (path1[i] > path2[i]) return r2;
  }
  return r1 < r2 ? r1 : r2;
}

int main(void) {

  int i,j,c;
  int best_row;

  while (1) {
    if (scanf("%d %d", &rows, &cols) != 2) {
      exit(0);
    }
    for (i=0; i < rows; i++) {
      for (j=0; j < cols; j++) {
        scanf("%d", &grid[i][j]);
      }
    }

    for (i=0; i < rows; i++) {
      prev[i][0] = -1;
      best[i][0] = grid[i][0];
    }

    for (c=1; c < cols; c++) {
      for (i=0; i < rows; i++) {
        best_row = compare_paths(c - 1, (i - 1 + rows) % rows, compare_paths(c - 1, i, (i + 1) % rows));
        prev[i][c] = best_row;
        best[i][c] = grid[i][c] + best[best_row][c-1];
      }
    }

    best_row = 0;
    for (i=1; i < rows; i++) {
      best_row = compare_paths(cols - 1, best_row, i);
    }
    genpath(cols - 1, best_row, path1);
    printf("%d", path1[0] + 1);
    for (i=1; i < cols; i++) {
      printf(" %d", path1[i] + 1);
    }
    printf("\n%d\n", best[best_row][cols - 1]);
  }
}

