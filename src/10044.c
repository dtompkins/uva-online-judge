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
  
  * The I/O is VERY annoying
  * no limits on line size, name size, max matches, etc. is lame
  * no mention of blank line (as in sample debug) between scenarios
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#pragma warning(disable: 4996)

int t,T;
int p,P;
int n,N;

int *dynstack;
int dynstack_size;
int dynstack_max;

void create_dynstack(void) {
  dynstack_max = 4096;
  dynstack_size = 0;
  dynstack = (int *) malloc(dynstack_max * sizeof(int));
}

void reset_dynstack(void) {
  dynstack_size = 0;
}

void push_dynstack(int i) {
  if (dynstack_size == dynstack_max) {
    dynstack_max *= 2;
    dynstack = (int *) realloc(dynstack, dynstack_max * sizeof(int));
  }
  dynstack[dynstack_size] = i;
  dynstack_size++;
}

int pop_dynstack(void) {
  dynstack_size--;
  return (dynstack[dynstack_size]);
}

struct ilist_node {
  int item;
  struct ilist_node *next;
};

struct ilist {
  int count;
  struct ilist_node *first;
};

int in_ilist(struct ilist *lst, int i) {
  struct ilist_node *node = lst->first;
  while (node) {
    if (node->item == i) return 1;
    node = node->next;
  }
  return 0;
}

void add_unique_ilist(struct ilist *lst, int i) {
  struct ilist_node *node;
  if (in_ilist(lst,i)) return;
  node = (struct ilist_node *) malloc(sizeof(struct ilist_node));
  node->item = i;
  node->next = lst->first;
  lst->first = node;
  lst->count++;
}

void init_ilist(struct ilist *lst) {
  lst->count = 0;
  lst->first = NULL;
}

char **authors;
struct ilist *co_authors;
int *erdos;
int authors_size;
int authors_max;

char line[65536];

int blank_line(void) {
  int i;
  int len = strlen(line);
  for (i=0; i < len; i++) {
    if (line[i] != ' ') return 0;
  }
  return 1;
}

void create_authors(void) {
  authors_max = 4096;
  authors_size = 1;
  authors = (char **) malloc(authors_max * sizeof (char *));
  co_authors = (struct ilist *) malloc(authors_max * sizeof(struct ilist));
  erdos = (int *) malloc(authors_max * sizeof(int));
  authors[0] = strdup("Erdos, P.");
  init_ilist(&co_authors[0]);
  erdos[0] = 0;
}

void reset_authors(void) {
  int i;
  struct ilist_node *node;
  struct ilist_node *prev;
  for (i=0; i < authors_size; i++) {
    node = co_authors[i].first;
    while (node) {
      prev = node;
      node = node->next;
      free(prev);
    }
    co_authors[i].first = NULL;
    co_authors[i].count = 0;
    if (i) { 
      free(authors[i]);
      erdos[i] = -1;
    }
  }
  authors_size = 1;
}

int get_author_id(char *name) {
  int i;
  for (i=0; i < authors_size; i++) {
    if (strcmp(name, authors[i]) == 0) return i;
  }
  if (authors_size == authors_max) {
    authors_max *= 2;
    authors = (char **) realloc(authors, authors_max * sizeof (char *));
    co_authors = (struct ilist *) realloc(co_authors, authors_max * sizeof(struct ilist));
    erdos = (int *) realloc(erdos, authors_max * sizeof(int));
  }
  authors[authors_size] = strdup(name);
  init_ilist(&co_authors[authors_size]);
  erdos[authors_size] = -1;
  authors_size++;
  return (authors_size - 1);
}


int main(void) {
  int i,j,start,len,end,cur,e,found;
  struct ilist_node *node;

  create_dynstack();
  create_authors();
  
  gets(line);
  if (sscanf(line, "%d", &T) != 1) {
    exit(0);
  }
  for (t=0; t < T; t++) {
    reset_authors();
    gets(line);
    if (blank_line()) gets(line);
    sscanf(line, "%d %d", &P, &N);
    for (p=0; p < P; p++) {
      gets(line);
      len = strlen(line);
      start = 0;
      while (line[start] == ' ') start++;
      for (i=0; i < len; i++) {
        if ((line[i] == '.')&&((line[i+1] == ',')||(line[i+1] == ':'))) {
          end = (line[i+1] == ':') ? 1 : 0;
          line[i+1] = 0;
          push_dynstack(get_author_id(line + start));
          if (end) break;
          start = i + 2;
          while (line[start] == ' ') start++;
        }
      }
      for (i=0; i < dynstack_size; i++) {
        for (j=0; j < dynstack_size; j++) {
          if (i != j) {
            add_unique_ilist(&co_authors[dynstack[i]], dynstack[j]);
          }
        }
      }
      reset_dynstack();
    }

    e = 0;
    found = 1;
    while (found) {
      found = 0;
      for (i=0; i < authors_size; i++) {
        if (erdos[i] == e) {
          node = co_authors[i].first;
          while (node) {
            if (erdos[node->item] == -1) {
              erdos[node->item] = e + 1;
              found = 1;
            }
            node = node->next;
          }
        }
      }
      e++;
    }
    printf("Scenario %d\n", t +1);
    for (n=0; n < N; n++) {
      gets(line);
      cur = get_author_id(line);
      if (erdos[cur] == -1) {
        printf("%s infinity\n", line);
      } else {
        printf("%s %d\n", line, erdos[cur]);
      }
    }
  }
}
