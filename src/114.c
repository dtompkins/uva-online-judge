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

char surface[52][52];

int score[52][52];
int cost[52][52];
int wall_cost;

int m;
int n;

int cur_x;
int cur_y;
int cur_dir;
int cur_life;
int cur_points;
int next_x;
int next_y;
int total_points;

int right = 0;
int up = 1;
int left = 2;
int down = 3;

void update_next(void) {
  next_x = cur_x;
  next_y = cur_y;
  if (cur_dir == right) {
    next_x++;
  } else if (cur_dir == up) {
    next_y++;
  } else if (cur_dir == left) {
    next_x--;
  } else if (cur_dir == down) {
    next_y--;
  }
}

void build_surface(void) {
  int i,j;
  for (i=1; i <= m; i++) {
    surface[1][i] = 'w'; 
    surface[n][i] = 'w';
  }
  for (i=2; i < n; i++) {
    surface[i][1] = 'w';
    for (j=2; j < m; j++) {
      surface[i][j] = ' ';
    }
    surface[i][m] = 'w';
  }
}

void change_direction(void) {
  cur_dir--;
  if (cur_dir == -1) {
    cur_dir = 3;
  }
}

int main(void) {
  int i;
  int p;
  int x,y,c,v;

  if (scanf("%d %d", &m, &n) != 2) {
    exit(0);
  }
  build_surface();
  scanf("%d", &wall_cost);
  scanf("%d", &p);

  for (i=0; i < p; i++) {
    scanf("%d %d %d %d", &x, &y, &v, &c);
    surface[y][x] = 'b';
    score[y][x] = v;
    cost[y][x] = c;
  }

  total_points = 0;
  
  while (1) {
    if (scanf("%d %d %d %d", &cur_x, &cur_y, &cur_dir, &cur_life) != 4) {
      printf("%d\n", total_points);
      exit(0);
    }
    cur_points = 0;

    while (cur_life > 1) {
      cur_life--;
      update_next();
      if (surface[next_y][next_x] == ' ') {
        cur_x = next_x;
        cur_y = next_y;
      } else if (surface[next_y][next_x] == 'b') {
        change_direction();
        cur_points += score[next_y][next_x];
        cur_life -= cost[next_y][next_x];
      } else if (surface[next_y][next_x] == 'w') {
        change_direction();
        cur_life -= wall_cost;
      } else {
        printf("unexpected: (%d,%d)\n", next_x, next_y);
      }
    }
    printf("%d\n", cur_points);
    total_points += cur_points;
  }

}
