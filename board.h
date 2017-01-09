// ============================================
// Board Header File
// ============================================ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct card {
  char shape;
  char shading;
  int number;
  int color;
};
typedef struct card card;

struct deck {
  card order[81];
  int pointer;
}; 
typedef struct deck deck;

char * ctos(int color);
int populate(deck d);
int shuffle(deck d);
int deal(deck d); // EDIT
int check_set(card c1, card c2, card c3);
int remove_card(deck d);
