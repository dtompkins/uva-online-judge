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

  * initial arraytree implementation was running out of ram
    (they must have had a really lopsided test case)
  * 2nd version -- messed up by checking if tree is NULL
    instead of checking if it's a leaf (left == right == NULL)
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

struct node {
  int val;
  struct node *left;
  struct node *right;
};

struct node *newnode(int v) {
  struct node *n = malloc(sizeof(struct node));
  n->val = v;
  n->left = NULL;
  n->right = NULL;
  return n;
}

int target;

struct node *scantree(void) {
  char c = ' ';
  int i;
  struct node *n = NULL;
  while (c != '(') {
    scanf("%c", &c);
  }
  if (scanf("%d", &i) == 1) {
    n = newnode(i);
    n->left = scantree();
    n->right = scantree();
  }
  while (c != ')') {
    scanf("%c", &c);
  }
  return n;
}

void freetree(struct node *t) {
  if (t) {
    freetree(t->left);
    freetree(t->right);
    free(t);
  }
}

int checksum(struct node *t, int sofar) {
  if (t == NULL) {
    return 0;
  } else if ((t->left == NULL) && (t->right == NULL)) {
    return ((sofar + t->val) == target);
  } else {
    return (checksum(t->left, t->val + sofar) || checksum(t->right, t->val + sofar));
  }
}
  


int main(void) {
  
  struct node *t;

  while (1) {
    if (scanf("%d", &target) != 1) {
      exit(0);
    }
    t = scantree();
    if (t) {
      if (checksum(t, 0)) {
        printf("yes\n");
      } else {
        printf("no\n");
      }
    } else {
      printf("no\n");
    }
    /* freetree(t); */
  }
}

