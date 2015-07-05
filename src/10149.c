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

  * First attempt was my first (legit) "Time Limit Exceeded" :(  
    (my early_terminate was way too thorough to justify it)
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

int rolls[14][5];
int scores[13][14];
int maxscore[13];

int curscore[13];
int curalloc[14];
int bestscore[13];
int bestsum_with_bonus;

int compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

void update_scores(void) {
  int cat,r,d,val,chance,maxcount;
  int count[7];
  for (r=1; r <= 13; r++) {
    for (d=1; d <= 6; d++) count[d] = 0;
    chance = 0;
    maxcount = 0;
    for (d=0; d < 5; d++) {
      val = rolls[r][d];
      count[val]++;
      if (count[val] > maxcount) maxcount = count[val];
      chance += val;
    }
    for (cat=0; cat < 6; cat++) {
      scores[cat][r] = count[cat+1] * (cat+1);
    }
    scores[6][r] = chance;
    scores[7][r] = (maxcount >= 3) ? chance : 0;
    scores[8][r] = (maxcount >= 4) ? chance : 0;
    scores[9][r] = (maxcount == 5) ? 50 : 0;
    scores[10][r] = 0;
    if ((count[3] && count[4]) && ((count[1] && count[2])||(count[2] && count[5])||(count[5] && count[6]))) {
      scores[10][r] = 25;
    }
    scores[11][r] = 0;
    if ((count[2] && count[3] && count[4] && count[5]) && (count[1] || count[6])) {
      scores[11][r] = 35;
    }
    scores[12][r] = 0;
    if (maxcount == 3) {
      for (d=1; d <= 6; d++) {
        if (count[d] == 2) scores[12][r] = 40;
      }
    }
  }
  for (cat=0; cat < 12; cat++) {
    maxscore[cat] = 0;
    for (r=1; r <= 13; r++) {
      if (scores[cat][r] > maxscore[cat]) maxscore[cat] = scores[cat][r];
    }
  }
}

int get_score(int *s) {
  int i;
  int score = 0;
  for (i=0; i < 6; i++) {
    score += s[i];
  }
  if (score >= 63) score += 35;
  for (i=6; i < 13; i++) {
    score += s[i];
  }
  return score;
}

void update_best(void) {
  int i;
  int score = get_score(curscore);
  if (score > bestsum_with_bonus) {
    bestsum_with_bonus = score;
    for (i=0; i < 13; i++) {
      bestscore[i] = curscore[i];
    }
  }
}

int early_terminate(void) {
  int i;
  int opt[13];
  for (i=0; i < 13; i++) {
    opt[i] = (curscore[i] == -1) ? maxscore[i] : curscore[i];
  }
  return get_score(opt) <= bestsum_with_bonus;
}

void allocate(int i) {
  int r;
  if (i < 0) {
    update_best();
    return;
  }
  for (r=1; r <= 13; r++) {
    if (curalloc[r] == -1) {
      curscore[i] = scores[i][r];
      curalloc[r] = i;
      if (!early_terminate()) allocate(i-1);
      curscore[i] = -1;
      curalloc[r] = -1;
    }
  }
}

int main(void) {
  int i,j,sbest,spos,bonus;

  while(1) {
    for (i=1; i <= 13; i++) {
      for (j=0; j < 5; j++) {
        if (scanf("%d", &rolls[i][j]) != 1) exit(0);
      }
    }
    update_scores();
    for (i=0; i < 13; i++) {
      curscore[i] = -1;
      curalloc[i+1] = -1;
    }
    /* initial greedy seed */
    bestsum_with_bonus = -1;
    for (i=12; i >= 0; i--) {
      sbest = -1;
      for (j=1; j <= 13; j++) {
        if (curalloc[j] == -1) {
          if (scores[i][j] > sbest) {
            sbest = scores[i][j];
            spos = j;
          }
        }
      }
      curscore[i] = sbest;
      curalloc[spos] = i;
    }
    update_best();
    for (i=0; i < 13; i++) {
      curscore[i] = -1;
      curalloc[i+1] = -1;
    }
    allocate(12);
    sbest = 0;
    for (i=0; i < 6; i++) {
      sbest += bestscore[i];
      printf("%d ", bestscore[i]);
    }
    bonus = (sbest >= 63) ? 35 : 0;
    for (i=6; i < 13; i++) {
      sbest += bestscore[i];
      printf("%d ", bestscore[i]);
    }
    printf("%d %d\n", bonus, sbest + bonus);
  }
}
