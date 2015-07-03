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

  * very annoying -- no indication that removed 0 should not print
    for cousins
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

char buf1[33];
char buf2[33];

int num_people;
char names[301][33];
int parent[301];
int children[301][301];
int num_children[301];

int lookup(char *s) {
  int i;
  for (i=1; i <= num_people; i++) {
    if (strcmp(names[i], s)==0) return i;
  }
  num_people++;
  strcpy(names[num_people], s);
  return num_people;
}

int is_parent(int c, int p) {
  int g = 0;
  while (c) {
    if (c == p) return g;
    c = parent[c];
    g++;
  }
  return 0;
}

void print_grand(int i, const char *type) {
  while (i > 2) {
    i--;
    printf("great ");
  }
  if (i == 2) {
    printf("grand ");
  }
  printf("%s\n", type);
}

int check_cousins(int x, int y) {
  int xp,yp,xdist,ydist,k,j;

  xp = parent[x];
  xdist = 0;
  while (xp) {
    yp = parent[y];
    ydist = 0;
    while (yp) {
      if (xp == yp) {
        k = xdist < ydist ? xdist : ydist;
        j = xdist < ydist ? (ydist - xdist) : (xdist - ydist);
        if (j) {
          printf("%d cousin removed %d\n", k, j);
        } else {
          printf("%d cousin\n", k);
        }
        return 1;
      }
      yp = parent[yp];
      ydist++;
    }
    xp = parent[xp];
    xdist++;
  }
  return 0;
}

int main(void) {

  int p,c,x,y;
  int result;

  while (1) {
    if (scanf("%s %s", buf1, buf2) != 2) {
      printf("unexpected\n");
      exit(0);
    }
    if (strcmp(buf1,"no.child")==0) break;
    
    c = lookup(buf1);
    p = lookup(buf2);

    parent[c] = p;
    children[p][num_children[p]] = c;
    num_children[p]++;
  }

  while (1) {
    if (scanf("%s %s", buf1, buf2) != 2) {
      exit(0);
    }
    
    x = lookup(buf1);
    y = lookup(buf2);

    result = is_parent(x, y);
    if (result) {
      print_grand(result, "child");
      continue;
    }
    result = is_parent(y, x);
    if (result) {
      print_grand(result, "parent");
      continue;
    }
    if (parent[x] && (parent[x] == parent[y])) {
      printf("sibling\n");
      continue;
    }
    if (check_cousins(x, y)) continue;
    printf("no relation\n");
  }

}

