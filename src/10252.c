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

  * I did NOT like their definition of "subsequence"
    I interpreted it as consecutive subsequence (which is way harder)
  * once again: VERY annoying I/O -- scanf would not work because
    of potential blank lines. grrr.
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

char a[1001];
char b[1001];
char x[1001];
int alen,blen,xlen;

int char_compare(const void *a, const void *b) {
  return (*(char *)a - *(char *)b);
}

int main(void) {
  int i,j;
  char *r1, *r2;
  while(1) {
    a[0] = b[0] = 0;
    r1 = gets(a);
    r2 = gets(b);
    if ((r1 == NULL)||(r2 == NULL)) exit(0);
    alen = strlen(a);
    blen = strlen(b);
    xlen = 0;
    qsort(a, alen, sizeof(char), char_compare);
    qsort(b, blen, sizeof(char), char_compare);
    i = j = 0;
    while ((i < alen)&&(j < blen)) {
      if (a[i] == b[j]) {
        x[xlen] = a[i];
        xlen++;
        i++;
        j++;
      } else if (a[i] < b[j]) {
        i++;
      } else {
        j++;
      }
    }
    x[xlen] = 0;
    printf("%s\n", x);
  }
}
