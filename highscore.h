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
void print_node( playerscore *n ); //temp
void print_list( playerscore *l ); //temp
playerscore * read_scores();
int write_scores( playerscore *l);
void print_scores();

