/********************************************************************
  !!! DISCLAIMER !!! 
  
  This is *quick* and *dirty* and *disgusting* code.
  
  I'm completing some of the UVa Online Judge problems because:
  * I'm becoming old and decrepit, and this will help me stay sharp
  * It gives me ideas for designing my own assignments
  * It's fun
  
  For more information, visit https://uva.onlinejudge.org/
  The problem # is the name of the file.
  
  If any of my students are reading this, this is NOT good style.
  I must fall back to the classic: "Do as I say, not as I do"
*********************************************************************
POST-MORTEM NOTES (if any):

  * I (personally) think this was MUCH easier with INTs
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#pragma warning(disable: 4996)

int count;
int amount[1000];
int total;

int find_xfer(int lo, int hi) {
  int above = 0;
  int below = 0;
  int i;
  for (i=0; i < count; i++) {
    if (amount[i] > hi) {
      above += (amount[i] - hi);
    }
    if (amount[i] < lo) {
      below += (lo - amount[i]);
    }
  }
  return below > above ? below : above;
}

int main(void) {

  int i;
  int dollars,cents;
  int lo,hi;
  int exchange;
  int exchange_alt;
  while (1) {
    if (scanf("%d", &count) != 1) {
      exit(0);
    }
    if (count == 0) {
      exit(0);
    }
    total = 0;
    for (i=0; i < count; i++) {
      scanf("%d.%d", &dollars, &cents);
      amount[i] = dollars * 100 + cents;
      total += amount[i];
    }
    lo = total / count;
    hi = lo + 1;
    exchange = find_xfer(lo, hi);
    exchange_alt = find_xfer(lo - 1, hi - 1);
    if (exchange_alt < exchange) {
      exchange = exchange_alt;
    }
    exchange_alt = find_xfer(lo + 1, hi + 1);
    if (exchange_alt < exchange) {
      exchange = exchange_alt;
    }
    printf("$%01d.%02d\n", exchange / 100, exchange % 100);
  }
}

