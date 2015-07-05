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
  
  * ugh, I hate this blank line I/O
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

int t,T;
int n,N;

int cards_odd[52];
int cards_even[52];
int *src;
int *dst;
int shuffles[100][52];
char line[4096];

char *card_names[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
char *card_suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

void print_card(int i) {
  printf("%s of %s\n", card_names[i % 13], card_suits[i / 13]);
}

int blank_line(void) {
  int i;
  int len = strlen(line);
  for (i=0; i < len; i++) {
    if (line[i] != ' ') return 0;
  }
  return 1;
}

int main(void) {
  int i,pos,s,nums;
  
  if (scanf("%d", &T) != 1) {
    exit(0);
  }
  for (t=0; t < T; t++) {
    scanf("%d", &N);
    for (n=0; n < N; n++) {
      for (i=0; i < 52; i++) {
        scanf("%d", &pos);
        shuffles[n][pos - 1] = i;
      }
    }
    gets(line);

    for(i=0; i < 52; i++) {
      cards_odd[i] = i;
    }
    nums = 0;
    while (1) {
      if (gets(line) == NULL) break;
      if (blank_line()) break;
      if (sscanf(line, "%d", &s) != 1) break;
      nums++;
      if (nums % 2 == 1) {
        src = cards_odd;
        dst = cards_even;
      } else {
        src = cards_even;
        dst = cards_odd;
      }
      for (i=0; i < 52; i++) {
        dst[shuffles[s - 1][i]] = src[i];
      }
    }
    if (t) printf("\n");
    for(i=0; i < 52; i++) {
      print_card(dst[i]);
    }
  }
}
