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

********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

int N;
int reg[10];
int ram[1000];
int ramsize;
int PC;
int icount;

int is_digit(char c) {
  return (('0' <= c) && (c <= '9'));
}

void reset(void) {
  int i;
  for (i=0; i < 10; i++) reg[i] = 0;
  for (i=0; i < 1000; i++) ram[i] = 0;
}

char line[4096];

int main(void) {
  int n;
  int cur, curA, curB, curC;

  gets(line);
  if (sscanf(line, "%d", &N) != 1) {
    exit(0);
  }
  gets(line);

  for (n=0; n < N; n++) {
    reset();
    ramsize = 0;
    while(1) {
      gets(line);
      if (!is_digit(line[0])) break;
      ram[ramsize] = atoi(line);
      ramsize++;
    }
    icount = 0;
    PC = 0;
    while(1) {
      icount++;
      cur = ram[PC];
      curA = cur / 100;
      curB = (cur - curA * 100) / 10;
      curC = cur % 10;

      if (curA == 1) break;
      if (curA == 2) {
        reg[curB] = curC;
      }
      if (curA == 3) {
        reg[curB] = (reg[curB] + curC) % 1000;
      }
      if (curA == 4) {
        reg[curB] = (reg[curB] * curC) % 1000;
      }
      if (curA == 5) {
        reg[curB] = reg[curC];
      }
      if (curA == 6) {
        reg[curB] = (reg[curB] + reg[curC]) % 1000;
      }
      if (curA == 7) {
        reg[curB] = (reg[curB] * reg[curC]) % 1000;
      }
      if (curA == 8) {
        reg[curB] = ram[reg[curC]];
      }
      if (curA == 9) {
        ram[reg[curC]] = reg[curB];
      }
      if ((curA == 0)&&(reg[curC])) {
        PC = reg[curB];
      } else {
        PC++;
      }
    }
    if (n > 0) printf("\n");
    printf("%d\n", icount);
  }
}

