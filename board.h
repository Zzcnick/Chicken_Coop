#ifndef BOARD
#define BOARD

// ============================================
// Board Header File
// ============================================ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define BLU "\x1B[34m"
#define WHT "\x1B[37m"

struct card {
  char * shape; // 'O', 'X', or 'S'
  char * shading; // "{}", "[]", or "()"
  int number; // 1, 2, or 3
<<<<<<< HEAD
  char * color; // RED, GRN, or BLU  
=======
  char * color; // RED, GRN, or BLU
  char * display; // The string version of the card
>>>>>>> 50f8c3a51e671da18678423443b698937cb2edc0
};
typedef struct card card;

struct deck {
  card order[81];
  int pointer;
}; 
typedef struct deck deck;

char * ctos(card c);
<<<<<<< HEAD
int populate(deck d);
=======
int populate(deck * d);
>>>>>>> 50f8c3a51e671da18678423443b698937cb2edc0
int shuffle(deck d);
int deal(deck d); // EDIT
int check_set(card c1, card c2, card c3);
int remove_card(deck d);
void print_card(card c);
void print_deck(deck d);
#endif
