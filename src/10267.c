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

  * Initially I was actually saving the .bmp files
    (I still think the language was a bit unclear)
  * I wasted a LOT of time -- I was printing '0's not 'O's.
    (this also was not very clear)
  * based on my speed ranking, my stack/flood implementation was
    pretty efficient
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#pragma warning(disable: 4996)

char pic[252][253];

char line[4096];
char filename[15];

int stack_x[63504];
int stack_y[63504];
int stacksize;

int W;
int H;

void push(int x, int y) {
  stack_x[stacksize] = x;
  stack_y[stacksize] = y;
  stacksize++;
}

void pop(int *x, int *y) {
  stacksize--;
  *x = stack_x[stacksize];
  *y = stack_y[stacksize];
}

  

int main(void) {
  char c;
  int i,j;
  int x,y,w1,w2,z1,z2;
  int small, big;
  int small2, big2;
  int match;
  while (1) {
    gets(line);
    if (line[0] == 'X') {
      exit(0);
    }
    if (line[0] == 'I') {
      sscanf(line + 1, "%d %d", &W, &H);
      line[0] = 'C';
    }
    if (line[0] == 'C') {
      for (i=1; i <= H; i++) {
        for (j=1; j <= W; j++) {
          pic[i][j] = 'O';
        }
        pic[i][W+1] = 0;
      }
      for (j=1; j <= W; j++) {
        pic[H+1][j] = 0;
      }
    }
    if (line[0] == 'L') {
      sscanf(line + 1, "%d %d %c", &x, &y, &c);
      pic[y][x] = c;
    }
    if (line[0] == 'V') {
      sscanf(line + 1, "%d %d %d %c", &x, &z1, &z2, &c);
      small = z1 < z2 ? z1 : z2;
      big = z1 > z2 ? z1 : z2;
      for (i=small; i <= big; i++) {
        pic[i][x] = c;
      }
    }
    if (line[0] == 'H') {
      sscanf(line + 1, "%d %d %d %c", &z1, &z2, &y, &c);
      small = z1 < z2 ? z1 : z2;
      big = z1 > z2 ? z1 : z2;
      for (i=small; i <= big; i++) {
        pic[y][i] = c;
      }
    }
    if (line[0] == 'K') {
      sscanf(line + 1, "%d %d %d %d %c", &z1, &w1, &z2, &w2, &c);
      small = z1 < z2 ? z1 : z2;
      big = z1 > z2 ? z1 : z2;
      small2 = w1 < w2 ? w1 : w2;
      big2 = w1 > w2 ? w1 : w2;
      for (i=small2; i <= big2; i++) {
        for (j=small; j <= big; j++) {
          pic[i][j] = c;
        }
      }
    }
    if (line[0] == 'F') {
      sscanf(line + 1, "%d %d %c", &x, &y, &c);
      match = pic[y][x];
      if (match != c) {
        push(x,y);
        while (stacksize) {
          pop(&x, &y);
          pic[y][x] = c;
          if (pic[y-1][x] == match) push(x,y-1);
          if (pic[y+1][x] == match) push(x,y+1);
          if (pic[y][x-1] == match) push(x-1,y);
          if (pic[y][x+1] == match) push(x+1,y);
        }
      }
    }
    if (line[0] == 'S') {
      sscanf(line + 1, "%s", &filename);
      printf("%s\n", filename);
      for (i=1; i <= H; i++) {
        printf("%s\n", &pic[i][1]);
      }
    }
  }
}

