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

#pragma warning(disable: 4996)



int N;
int part[1000001];

int gcd(int n, int m) {
  if (0 == m) {
    return n;
  }
  return gcd(m, n % m);
}

int main(void) {
  int a,b,c;
  int i,k;
  int m,n;
  int P;
  int count;

  while (1) {
    if (scanf("%d", &N) != 1) {
      exit(0);
    }
    for (i=0; i <= N; i++) {
      part[i] = 0;
    }
    P = N;
    count = 0;
    m=0;
    n=0;
    while(1) {
      m++;
      n = m + 1;
      if (m*m + n*n > N) break;
      while (m*m + n*n <=N) {
        if ((gcd(m,n) == 1)&&((n-m) % 2 == 1)) {
          a = n*n - m*m;
          b = 2 * m * n;
          c = m*m + n*n;
          count++;
          for (k=1; k*c <= N; k++) {
            if (!part[k*a]) {
              part[k*a] = 1;
              P--;
            }
            if (!part[k*b]) {
              part[k*b] = 1;
              P--;
            }
            if (!part[k*c]) {
              part[k*c] = 1;
              P--;
            }
          }
        }
        n++;
      }
    }
    printf("%d %d\n", count, P);
  }
}

