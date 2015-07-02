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

char buffer[110];
int p_digits[110];
int p_len;
int cur_len;
int k_len;
int n;
int cur_digits[110];
int backup_digits[110];
int k_digits[110];

int is_digit(char c) {
  return (('0' <= c) && (c <= '9'));
}

void init_k(int k) {
  int i;
  for (i=0; i < 110; i++) {
    cur_digits[i] = k_digits[i] = 0;
  }
  k_len = 0;
  while (k) {
    cur_digits[k_len] = k_digits[k_len] = k % 10;
    k /= 10;
    k_len++;
  }
  cur_len = k_len;
}

void do_backup(void) {
  int i;
  for (i=0; i < 110; i++) {
    backup_digits[i] = cur_digits[i];
    cur_digits[i] = 0;
  }
}

int compare_p(void) {
  int i;
  if (cur_len > p_len) return 1;
  if (cur_len < p_len) return -1;
  for (i=p_len + 2; i >= 0; i--) {
    if (cur_digits[i] > p_digits[i]) return 1;
    if (cur_digits[i] < p_digits[i]) return -1;
  }
  return 0;
}

void mult_add(int offset) {
  int i;
  int k = k_digits[offset];
  int mult_carry = 0;
  int add_carry = 0;
  int pos;
  i = 0;
  while ((i <= cur_len) || mult_carry || add_carry) {
    pos = i + offset;
    mult_carry += k * backup_digits[i];
    add_carry += mult_carry % 10;
    add_carry += cur_digits[pos];
    cur_digits[pos] = add_carry % 10;
    if (cur_digits[pos] && (pos >= cur_len)) {
      cur_len = pos + 1;
      if (cur_len > p_len) return;
    }
    mult_carry /= 10;
    add_carry /= 10;
    i++;
  }
}

void mult_k(void) {
  int i;
  do_backup();
  for (i=0; i < k_len; i++) {
    if (k_digits[i]) {
      mult_add(i);
    }
  }
}

void pow_k_n(int k) {
  int i;
  init_k(k);
  for (i=1; i < n; i++) {
    if (cur_len > p_len) return;
    mult_k();
  }
}
  

int main(void) {
  int i;
  int k;
  int ten;
  int k_lo;
  int k_hi;
  char c;
  int cmp;

  while (1) {
    if (scanf("%d", &n) != 1) {
      exit(0);
    }
    c = ' ';
    while (!is_digit(c)) {
      scanf("%c", &c);
    }
    p_len = 0;
    while (is_digit(c)) {
      buffer[p_len] = c;
      p_len++;
      scanf("%c", &c);
    }
    for (i=0; i < 110; i++) {
      p_digits[i] = 0;
    }
    for (i=0; i < p_len; i++) {
      p_digits[i] = buffer[p_len - 1 - i] - '0';
    }

    if ((p_len == 1)&&(p_digits[0]==1)) {
      k = 1;
    } else if (n == 1) {
      k = 0;
      ten = 1;
      for (i=0; i < p_len; i++) {
        k += ten * p_digits[i];
        ten *= 10;
      }
    } else {
      cmp = -1;
      k = 1;
      while (cmp == -1) {
        k *= 2;
        pow_k_n(k);
        cmp = compare_p();
      }
      k_lo = k / 2 + 1;
      k_hi = k - 1;
      while (cmp) {
        k = (k_hi - k_lo) / 2 + k_lo;
        pow_k_n(k);
        cmp = compare_p();
        if (cmp == 1) {
          k_hi = k - 1;
        }
        if (cmp == -1) {
          k_lo = k + 1;
        }
      }
    }
    printf("%d\n", k);
  }
}
