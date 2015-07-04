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

  * note that A cannot be used for an a-2-3-4-5 straight
  * the test debug input has a bad test case:
    7C 7C 7D 2H 5S 2D 6D 7S 7S 7D
    (two 7C's)
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

int card_values[255];
int card_suits[255];

int black_values[5];
int black_suits[5];
int white_values[5];
int white_suits[5];

void init_cards(void) {
  int i;
  card_values['T'] = 10;
  card_values['J'] = 11;
  card_values['Q'] = 12;
  card_values['K'] = 13;
  card_values['A'] = 14;
  for (i=2; i <= 9; i++) {
    card_values['0' + i] = i;
  }
  card_suits['C'] = 1;
  card_suits['D'] = 2;
  card_suits['H'] = 3;
  card_suits['S'] = 4;
}

int compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int freq[15];

void get_ranks(int *v, int *s, int *major, int *minor) {
  int i;
  int is_flush;
  int is_straight;
  int total = 0;
  int m15;
  int maxval;
  int maxfreq;
  int secval;
  int secfreq;

  is_flush = 1;
  for (i=0; i < 4; i++) {
    if (s[i] != s[i+1]) {
      is_flush = 0;
      break;
    }
  }

  is_straight = 1;
  for (i=0; i < 4; i++) {
    if (v[i] != v[i+1] - 1) {
      is_straight = 0;
      break;
    }
  }

  m15 = 1;
  for (i=0; i < 5; i++) {
    total += v[i] * m15;
    m15 *= 15;
  }

  for (i=0; i < 15; i++) {
    freq[i] = 0;
  }
  maxfreq = 0;
  for (i=0; i < 5; i++) {
    freq[v[i]]++;
    if (freq[v[i]] > maxfreq) {
      maxfreq = freq[v[i]];
      maxval = v[i];
    }
  }
  secfreq = 0;
  for (i=0; i < 15; i++) {
    if (i != maxval) {
      if (freq[i] > secfreq) {
        secfreq = freq[i];
        secval = i;
      }
    }
  }

  if (is_straight && is_flush) {
    *major = 9;
    *minor = v[0];
    return;
  }

  if (maxfreq == 4) {
    *major = 8;
    *minor = maxval;
    return;
  }

  if ((maxfreq == 3)&&(secfreq == 2)) {
    *major = 7;
    *minor = maxval;
    return;
  }

  if (is_flush) {
    *major = 6;
    *minor = total;
    return;
  }

  if (is_straight) {
    *major = 5;
    *minor = v[0];
    return;
  }

  if (maxfreq == 3) {
    *major = 4;
    *minor = maxval;
    return;
  }

  if ((maxfreq == 2) && (secfreq == 2)) {
    *major = 3;
    *minor = (maxval > secval ? maxval : secval) * 15 * 15 + (maxval < secval ? maxval : secval) * 15;
    for (i=0; i < 15; i++) {
      if (freq[i] == 1) {
        *minor += i;
      }
    }
    return;
  }

  if (maxfreq == 2) {
    *major = 2;
    *minor = maxval * 759375 + total;
    return;
  }

  *major = 1;
  *minor = total;
  return;
}

int main(void) {
  int i;
  char val, suit;
  int bmajor, bminor, wmajor, wminor;

  init_cards();

  while(1) {
    for (i=0; i < 5; i++) {
      if (scanf(" %c%c", &val, &suit) != 2) {
        exit(0);
      }
      black_values[i] = card_values[val];
      black_suits[i] = card_suits[suit];
    }
    for (i=0; i < 5; i++) {
      if (scanf(" %c%c", &val, &suit) != 2) {
        exit(0);
      }
      white_values[i] = card_values[val];
      white_suits[i] = card_suits[suit];
    }
    qsort(black_values, 5, sizeof(int), compare);
    qsort(black_suits, 5, sizeof(int), compare);
    qsort(white_values, 5, sizeof(int), compare);
    qsort(white_suits, 5, sizeof(int), compare);

    get_ranks(black_values, black_suits, &bmajor, &bminor);
    get_ranks(white_values, white_suits, &wmajor, &wminor);

    if (wmajor > bmajor) {
      printf("White wins.\n");
    } else if (bmajor > wmajor) {
      printf("Black wins.\n");
    } else if (wminor > bminor) {
      printf("White wins.\n");
    } else if (bminor > wminor) {
      printf("Black wins.\n");
    } else {
      printf("Tie.\n");
    }
  }
}
