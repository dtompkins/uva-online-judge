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

#pragma warning(disable: 4996)

int M;
int N;

int curorder[10];
int indent;

char alpha = 'a';

void printorder(void) {
  int i;
  for (i=0; i < N; i++) {
    if (i > 0) {
      printf(",");
    }
    printf("%c", alpha + curorder[i] - 1);
  }
}

void printindent(void) {
  int i;
  for (i=0; i < indent; i++) {
    printf(" ");
  }
}

void printif(int first, int second) {
  printindent();
  printf("if %c < %c then\n", alpha + first - 1, alpha + second - 1);
}

void printelse(void) {
  printindent();
  printf("else\n");
}

void printwrite(void) {
  printindent();
  printf("writeln(");
  printorder();
  printf(")\n");
}

void insert_at(int pos, int var) {
  int i;
  for (i=N-1; i > pos; i--) {
    curorder[i] = curorder[i-1];
  }
  curorder[pos] = var;
}

void remove_at(int pos) {
  int i;
  for (i=pos; i < N; i++) {
    curorder[i] = curorder[i+1];
  }
  curorder[N-1] = 0;
}

void nextvar(void);

void nextif(int curpos, int curvar) {
  printif(curvar, curorder[curpos]);
  insert_at(curpos, curvar);
  nextvar();
  remove_at(curpos);
  printelse();
  if (curvar == curpos + 2) {
    insert_at(curpos + 1, curvar);
    nextvar();
    remove_at(curpos + 1);
  } else {
    indent += 2;
    nextif(curpos + 1, curvar);
    indent -= 2;
  }
}

void nextvar(void) {
  int i;
  int curvar;
  indent += 2;
  if (curorder[N-1]) {
    printwrite();
  } else {
    curvar = 3;
    while (curorder[curvar - 1]) {
      curvar++;
    }
    nextif(0, curvar);
  }
  indent -= 2;
}

int main(void) {
  int i,p;
  if (scanf("%d", &M) != 1) {
    exit(0);
  }
  for (p=0; p < M; p++) {
    if (p > 0) {
      printf("\n");
    }
    if (scanf("%d", &N) != 1) {
      exit(0);
    }
    for (i=0; i < N; i++) {
      curorder[i] = i + 1;
    }

    printf("program sort(input,output);\nvar\n");
    printorder();
    printf(" : integer;\nbegin\n  readln(");
    printorder();
    printf(");\n");

    indent = 2;

    if (N == 1) {
      printwrite();
    } else {
      for (i=0; i < N; i++) {
        curorder[i] = 0;
      }

      printif(1,2);
      curorder[0] = 1;
      curorder[1] = 2;
      nextvar();
      printelse();
      curorder[0] = 2;
      curorder[1] = 1;
      nextvar();
    }
    printf("end.\n");
  }
}

