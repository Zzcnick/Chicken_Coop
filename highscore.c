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

void print_scores(char * filename) {
  FILE *fp;
  fp = fopen(filename, "r");
  char line[1024];
  while (fgets(line, sizeof(line), (FILE *)fp) != NULL) {
    *strchr(line, '\n') = 0;
    printf("%s seconds per Set\n", line);
  }
  fclose(fp);
}

int write_scores( playerscore *l, char * filename) {
  FILE *fp;
  fp = fopen(filename, "w+");
  char inputstr[256];

  playerscore *f = l;
  while (f!= 0) {
    char temp[256];
    sprintf(temp, "%s\t\t%lf\n", f->username, f->score);
    strcat(inputstr, temp);    
    f = f->next;
  }
  
  fputs(inputstr, fp);
  fclose(fp);
  return 0;
}

playerscore * read_scores( char * filename ) {
  FILE *fp;
  fp = fopen(filename, "r");
  playerscore *l = 0;
  char line[1024];
  char * sep = "\t\t";
  while (fgets(line, sizeof(line), (FILE *)fp) != NULL) {
    char * user = strtok(line, sep);
    char * username = strdup(user);
    char * scorestr = strtok(NULL, sep);
    double score;
    sscanf(scorestr, "%lf", &score);    
    l = insert(l, username, score);
  }
  fclose(fp);
  return l;
}

