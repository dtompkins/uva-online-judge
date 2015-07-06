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

char from[] = "1234567890-=WERTYUIOP[]\\SDFGHJKL;'XCVBNM,./";
char to[]   = "`1234567890-QWERTYUIOP[]ASDFGHJKL;ZXCVBNM,.";

char map[256];

void make_map(void) {
  int i, len;
  len = strlen(from);
  for (i=0; i < 256; i++) {
    map[i] = i;
  }
  for (i=0; i < len; i++) {
    map[from[i]] = to[i];
  }
}

int main(void) {
  char c;
  make_map();
  while (1) {
    if (scanf("%c", &c) != 1) exit(0);
    printf("%c", map[c]);
  }
}
