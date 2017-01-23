#ifndef HIGHSCORE
#define HIGHSCORE

// ============================================
// Highscores Header File
// ============================================ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef struct playerscore {
  char *username;
  double score;
  struct playerscore *next;
} playerscore;

playerscore * free_scorelist( playerscore *l );
playerscore * insert_front( playerscore *l, char *u, double s );
playerscore * insert( playerscore *l, char *u, double s );
char * sprint_node( playerscore *n ); 
void print_list( playerscore *l ); 
void read_scores(char * filename);
int write_scores( playerscore *l);
void print_scores(char * filename);
#endif
