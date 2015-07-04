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

char dict_words[1000][17];
int dict_pattern[1000][17];
int sorted_pattern[1000];
int n,N;

char c_words[40][81];
int c_pattern[40][81];
int c_matches[40];
int c_mstart[40];
int c_sorted[40];
int W;

char line[100];
char cypher[26];

int blank_line(void) {
  int i;
  int len = strlen(line);
  for (i=0; i < len; i++) {
    if (line[i] != ' ') return 0;
  }
  return 1;
}

int compare_pattern(int *a, int *b) {
  int i = 0;
  while (1) {
    if (a[i] < b[i]) return -1;
    if (a[i] > b[i]) return 1;
    if (a[i] == 0) return 0;
    i++;
  }
}

int compare_sort_patterns(const void *a, const void *b) {
  return compare_pattern(dict_pattern[*(int *)a], dict_pattern[*(int *)b]);
}


int compare_sort_words(const void *a, const void *b) {
  return c_matches[*(int *)a] - c_matches[*(int *)b];
}


void make_pattern(char *src, int *dst) {
  int len=strlen(src);
  int i, j, next;
  for (i=0; i <= len; i++) {
    dst[i] = 0;
  }
  next = 1;
  for (i=0; i < len; i++) {
    if (!dst[i]) {
      for (j=i; j < len; j++) {
        if (src[j] == src[i]) dst[j] = next;
      }
      next ++;
    }
  }
}

void print_pattern(int *p) {
  int i=0;
  while (p[i]) printf("%d", p[i++]);
  printf("\n");
}

int find_pattern(int *p, int *start) {
  int lo = 0;
  int hi = N-1;
  int mid;
  int cmp;

  while (lo <= hi) {
    mid = lo + (hi - lo) / 2;
    cmp = compare_pattern(p, dict_pattern[sorted_pattern[mid]]);
    if (cmp == 0) break;
    if (cmp < 0) hi = mid - 1;
    if (cmp > 0) lo = mid + 1;
  }
  if (lo > hi) {
    return 0;
  }
  lo = hi = mid;
  while ((lo > 0) && (compare_pattern(p, dict_pattern[sorted_pattern[lo - 1]]) == 0)) lo--;
  while ((hi < N - 1) && (compare_pattern(p, dict_pattern[sorted_pattern[hi + 1]]) == 0)) hi++;
  *start = lo;
  return (hi - lo + 1);
}

int find_solution(int ii) {
  int i,j,k,w,len;
  char *s;
  char *d;
  int map[26];
  int valid;
  if (ii == W) return 1;
  
  for (j=0; j < 26; j++) map[j] = 0;  
  w = c_sorted[ii];
  s = c_words[w];
  len = strlen(s);
  for (i=0; i < c_matches[w]; i++) {
    d = dict_words[sorted_pattern[c_mstart[w] + i]];
    valid = 1;
    for (j=0; j < len; j++) {
      if (cypher[s[j] - 'a']) {
        if (cypher[s[j] - 'a'] != d[j]) {
          valid = 0;
          break;
        }
      } else {
        for (k=0; k < 26; k++) {
          if (cypher[k] == d[j]) {
            valid = 0;
          }
        }
        if (!valid) break;
        map[s[j] - 'a'] = d[j];
        cypher[s[j] - 'a'] = d[j];
      }
    }
    if (valid) {
      valid = find_solution(ii + 1);
    }
    if (valid) return 1;
    for (k=0; k < 26; k++) {
      if (map[k]) {
        map[k] = 0;
        cypher[k] = 0;
      }
    }
  }
  return 0;
}

int main(void) {
  int i;
  int len;
  int sol_found;
  
  if (scanf("%d", &N) != 1) {
    exit(0);
  }

  for (n=0; n < N; n++) {
    scanf("%s", dict_words[n]);
    make_pattern(dict_words[n], dict_pattern[n]);
    sorted_pattern[n] = n;
  }

  qsort(sorted_pattern, N, sizeof(int), compare_sort_patterns);

  gets(line);

  while (1) {
    if (gets(line) == NULL) exit(0);
    if (blank_line()) exit(0);
    for (i=0; i < 26; i++) cypher[i] = 0;
    W = 0;
    len = strlen(line);
    i = 0;
    sol_found = 1;
    while (i < len) {
      if (line[i] == ' ') {
        i++;
      } else {
        sscanf(line + i, "%s", c_words[W]);
        while ((i < len) && (line[i] != ' ')) i++;
        make_pattern(c_words[W], c_pattern[W]);
        c_matches[W] = find_pattern(c_pattern[W], &c_mstart[W]);
        if (c_matches[W] == 0) {
          sol_found = 0;
          break;
        }
        c_sorted[W] = W;
        W++;
      }
    }
    if (sol_found) {
      qsort(c_sorted, W, sizeof(int), compare_sort_words);
      sol_found = find_solution(0);
    }
    if (sol_found == 0) {
      for (i=0; i < len; i++) {
        if (line[i] == ' ') {
          printf(" ");
        } else {
          printf("*");
        }
      }
      printf("\n");
    } else {
      for (i=0; i < len; i++) {
        if (line[i] == ' ') {
          printf(" ");
        } else {
          printf("%c", cypher[line[i] - 'a']);
        }
      }
      printf("\n");
    }
  }
}
