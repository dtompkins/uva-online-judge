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

  * the I/O on this one was SOOOO annoying
  * does not require a blank line at the end of the file
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

char names[20][100];
int N;
int votes[1001][21];
int V;
int vpos[1001];
int counts[20];
int eliminated[20];

char line[4096];

int blank_line(void) {
  int i;
  int len = strlen(line);
  for (i=0; i < len; i++) {
    if (line[i] != ' ') return 0;
  }
  return 1;
}

int is_digit(char c) {
  return (('0' <= c) && (c <= '9'));
}

int main(void) {
  int c,count;
  int i;
  int needed;
  int min,max;

  gets(line);
  sscanf(line, "%d", &count);
  gets(line);
  for (c=0; c < count; c++) {
    gets(line);
    sscanf(line, "%d", &N);
    for (i=0; i < N; i++) {
      gets(names[i]);
    }
    V=0;
    while(1) {
      if (gets(line) == NULL) break;
      if (blank_line()) break;
      sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    &votes[V][0], &votes[V][1], &votes[V][2], &votes[V][3], &votes[V][4], 
                    &votes[V][5], &votes[V][6], &votes[V][7], &votes[V][8], &votes[V][9], 
                    &votes[V][10], &votes[V][11], &votes[V][12], &votes[V][13], &votes[V][14], 
                    &votes[V][15], &votes[V][16], &votes[V][17], &votes[V][18], &votes[V][19]);
      for (i=0; i < N; i++) {
        votes[V][i]--;
      }
      V++;
    }
    for (i=0; i < N; i++) {
      counts[i] = eliminated[i] = 0;
    }
    needed = V / 2 + 1;
    for (i=0; i < V; i++) {
      vpos[i] = 0;
      counts[votes[i][vpos[i]]]++;
    }
    while(1) {
      min = 1001;
      max = 0;
      for (i=0; i < N; i++) {
        if (!eliminated[i]) {
          if (counts[i] > max) max = counts[i];
          if (counts[i] < min) min = counts[i];
        }
      }
      if (max >= needed) break;
      if (max == min) break;
      for (i=0; i < N; i++) {
        if (counts[i] == min) {
          eliminated[i] = 1;
        }
      }
      for (i=0; i < V; i++) {
        if (eliminated[votes[i][vpos[i]]]) {
          while (eliminated[votes[i][vpos[i]]]) {
            vpos[i]++;
          }
          counts[votes[i][vpos[i]]]++;
        }
      }
    }
    if (c > 0) printf("\n");
    if (max == min) {
      for (i=0; i < N; i++) {
        if (!eliminated[i]) {
          printf("%s\n", names[i]);
        }
      }
    } else {
      for (i=0; i < N; i++) {
        if (counts[i] >= needed) {
          printf("%s\n", names[i]);
        }
      }
    }
  }
}
