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

char board[8][9];

int valid(int x, int y) {
  return ((x >= 0)&&(x <= 7)&&(y >= 0)&&(y <= 7));
}

char getspot(int x, int y) {
  if (valid(x,y)) {
    return board[y][x];
  } else {
    return ' ';
  }
}

char line[4096];

int main(void) {
  int i,j,col,xdir,ydir;
  int kx,ky;
  int x,y;
  int empty;
  int game = 0;
  int checkfound;
  while(1) {
    game++;
    empty = 1;
    for (i=0; i < 8; i++) {
      gets(line);
      sscanf(line, "%s", board[i]);
      if (empty && strcmp(board[i],"........")) empty = 0;
    }
    if (empty) break;
    gets(line);

    for (col=0; col < 2; col++) {
      if (col) {
        for (i=0; i < 8; i++) {
          for (j=0; j < 8; j++) {
            if ((board[i][j] >= 'a') && (board[i][j] <= 'z')) {
              board[i][j] = 'A' + (board[i][j] - 'a');
            } else if ((board[i][j] >= 'A') && (board[i][j] <= 'Z')) {
              board[i][j] = 'a' + (board[i][j] - 'A');
            }
          }
        }
      }
      checkfound = 0;
      kx = -1;
      for (i=0; i < 8; i++) {
        for (j=0; j < 8; j++) {
          if (board[i][j] == 'K') {
            kx = j;
            ky = i;
            break;
          }
        }
        if (kx >= 0) break;
      }

      if (col==0) {
        if (getspot(kx-1, ky-1) == 'p') goto incheck;
        if (getspot(kx+1, ky-1) == 'p') goto incheck;
      } else {
        if (getspot(kx-1, ky+1) == 'p') goto incheck;
        if (getspot(kx+1, ky+1) == 'p') goto incheck;
      }
      if (getspot(kx-2, ky-1) == 'n') goto incheck;
      if (getspot(kx-2, ky+1) == 'n') goto incheck;
      if (getspot(kx+2, ky-1) == 'n') goto incheck;
      if (getspot(kx+2, ky+1) == 'n') goto incheck;
      if (getspot(kx-1, ky-2) == 'n') goto incheck;
      if (getspot(kx+1, ky-2) == 'n') goto incheck;
      if (getspot(kx-1, ky+2) == 'n') goto incheck;
      if (getspot(kx+1, ky+2) == 'n') goto incheck;

      for (ydir=-1; ydir <= 1; ydir += 2) {
        x = kx;
        y = ky + ydir;
        while (valid(x,y)) {
          if (getspot(x,y) == 'r') goto incheck;
          if (getspot(x,y) == 'q') goto incheck;
          if (getspot(x,y) != '.') break;
          y += ydir;
        }
      }
      for (xdir=-1; xdir <= 1; xdir += 2) {
        x = kx + xdir;
        y = ky;
        while (valid(x,y)) {
          if (board[y][x] == 'r') goto incheck;
          if (board[y][x] == 'q') goto incheck;
          if (board[y][x] != '.') break;
          x += xdir;
        }
      }
      for (ydir=-1; ydir <= 1; ydir += 2) {
        for (xdir=-1; xdir <= 1; xdir += 2) {
          x = kx + xdir;
          y = ky + ydir;
          while (valid(x,y)) {
            if (board[y][x] == 'b') goto incheck;
            if (board[y][x] == 'q') goto incheck;
            if (board[y][x] != '.') break;
            x += xdir;
            y += ydir;
          }
        }
      }
      
      continue;

incheck:
      if (col) {
        printf("Game #%d: black king is in check.\n", game);
      } else {
        printf("Game #%d: white king is in check.\n", game);
      }
      checkfound = 1;
      break;
    }
    if (!checkfound) {
      printf("Game #%d: no king is in check.\n", game);
    }
  }
}

