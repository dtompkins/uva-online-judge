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

char lines[101][81];
int N;

char tline[81];

int t,T;

char cypher[26];

char fox[] = "the quick brown fox jumps over the lazy dog";
int num_fox_spaces = 8;
int fox_spaces[8] = {3, 9, 15, 19, 25, 30, 34, 39};
int foxlen = 43;

int blank_line(char *line) {
  int i;
  int len = strlen(line);
  for (i=0; i < len; i++) {
    if (line[i] != ' ') return 0;
  }
  return 1;
}

int is_fox_match(char *line) {
  int i,s,d;
  int len = strlen(line);
  if (len != foxlen) return 0;
  for (i=0; i < num_fox_spaces; i++) {
    if (line[fox_spaces[i]] != ' ') return 0;
  }
  for (i=0; i < 26; i++) {
    cypher[i] = 0;
  }
  for (i=0; i < foxlen; i++) {
    if ((line[i] == ' ')&&(fox[i] == ' ')) continue;
    s = line[i] - 'a';
    if ((s < 0)||(s >= 26)) return 0;
    d = fox[i];
    if (cypher[s] && (cypher[s] != d)) return 0;
    cypher[s] = d;
  }
  return 1;
}

int main(void) {
  int i,j;
  int len;
  int sol_found;
  
  gets(tline);
  if (sscanf(tline, "%d", &T) != 1) {
    exit(0);
  }
  gets(tline);

  for (t=0; t < T; t++) {
    N = 0;
    while (1) {
      if (gets(lines[N]) == NULL) break;
      if (blank_line(lines[N])) break;
      N++;
    }
    sol_found = 0;
    for (i=0; i < N; i++) {
      if (is_fox_match(lines[i])) {
        sol_found = 1;
        break;
      }
    }
    if (t) printf("\n");
    if (sol_found) {
      for (i=0; i < N; i++) {
        len = strlen(lines[i]);
        for (j=0; j < len; j++) {
          if ((lines[i][j] >= 'a')&&(lines[i][j] <= 'z')) {
            lines[i][j] = cypher[lines[i][j] - 'a'];
          }
        }
        printf("%s\n", lines[i]);
      }
    } else {
      printf("No solution.\n");
    }
  }
}
