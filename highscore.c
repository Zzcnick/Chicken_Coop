// ============================================
// Highscores Algorithms and File Editing
// ============================================

#include <stdio.h>
#include <stdlib.h>

#include "highscore.h"

playerscore * free_scorelist( playerscore *l ) {
  playerscore *f = l;
  while(l) {
    l = l->next;
    free(f);
    f=l;
  }
  return l;
}

playerscore * insert_front( playerscore *l, char *u, double s ) {
  playerscore *new = ( playerscore *)malloc(sizeof( playerscore ));
  new->username = u;
  new->score = s;
  new->next = l;
  return new;

}

playerscore * insert( playerscore *l, char *u, double s ) {
  if (l==0) {
    l = insert_front(l, u, s);
    return l;
  }
  if ( s < l->score) {
    l = insert_front (l, u, s);
    return l;
  }
  playerscore *f = l;
  while ( f && s > f->score) {
    f = f->next;
  }
  playerscore *g = l;
  while (g->next != f) {
    g = g->next;
  }
  g->next = insert_front(f, u, s);
  return l;
}

void print_node( playerscore *n ) {
  if (n != 0) {
    printf("%s\t\t%lf\n", n->username, n->score);
  }  
}

void print_list( playerscore *l ) {
  if (l) {
    print_node(l);
    print_list(l->next);
  }
}

/*playerscore * read_scores() {
}

int write_scores( playerscore *l) {
}

void print_scores() {
}*/

int main() {
  playerscore * list;
  list = insert(list, "Sarah", 3.14);
  list = insert(list, "Zicheng", 6.28);
  list = insert(list, "Jan", 4.13);
  list = insert(list, "Enver", 1.23);
  print_list(list);
  //free_scorelist(list);
  return 0;
}
