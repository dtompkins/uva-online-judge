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

  * I think the 001 input was *really* unfair, and not hinted at
    at all by the question spec.
  * I also wasted a few attempts - I forgot to print new lines
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#pragma warning(disable: 4996)

int S;
int N;

char string_num[20];

char display[23][110];
int digits[8];
int num_digits;

/*   1
    2 3
     4
    5 6
     7
*/

void clear_display(void) {
  int i;
  int j;
  int w = (S+2) * num_digits + (num_digits -1);
  int h = 2 * S + 3;
  for (i=0; i < h; i++) {
    for (j=0; j < w; j++) {
      display[i][j] = ' ';
    }
    display[i][w] = 0;
  }
}

int segments[10][8] = { {1, 2, 3, 5, 6, 7, 0},
                        {3, 6, 0},
                        {1, 3, 4, 5, 7, 0},
                        {1, 3, 4, 6, 7, 0},
                        {2, 3, 4, 6, 0},
                        {1, 2, 4, 6, 7, 0},
                        {1, 2, 4, 5, 6, 7, 0},
                        {1, 3, 6, 0},
                        {1, 2, 3, 4, 5, 6, 7, 0},
                        {1, 2, 3, 4, 6, 7, 0} };

void draw_segment(int seg, int col) {
  int i;
  int offset;
  int start = (S + 3) * col;
  if ((seg == 1)||(seg == 4)||(seg == 7)) {
    if (seg == 1) offset = 0;
    if (seg == 4) offset = S + 1;
    if (seg == 7) offset = 2*S + 2;
    for (i=0; i < S; i++) {
      display[offset][start + 1 + i] = '-';
    }
  } else {
    offset = 1;
    if (seg > 4) offset =  S + 2;
    if ((seg == 3) || (seg == 6)) start += S + 1;
    for (i=0; i < S; i++) {
      display[offset + i][start] = '|';
    }
  }
}

int main(void) {
  int i,j,d;
  while (1) {
    if (scanf("%d %s", &S, &string_num) != 2) {
      exit(0);
    }
    if ((S == 0) && (strcmp(string_num,"0") == 0)) {
      exit(0);
    }
    num_digits = strlen(string_num);
    for (i=0; i < num_digits; i++) {
      digits[i] = string_num[i] - '0';
    }
    clear_display();
    for (i=0; i < num_digits; i++) {
      d = digits[i];
      for (j=0; j < 8; j++) {
        if (segments[d][j] == 0) break;
        draw_segment(segments[d][j], i);
      }
    }
    for (i=0; i < 2 * S + 3; i++) {
      printf("%s\n", display[i]);
    }
    printf("\n");
  }
}

