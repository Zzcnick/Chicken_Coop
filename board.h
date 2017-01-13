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
  char shape; // 'O', 'X', or 'S'
  char * shading; // "{}", "[]", or "()"
  int number; // 1, 2, or 3
  char * color; // RED, GRN, or BLU  
};
typedef struct card card;

struct deck {
  card order[81];
  int pointer;
}; 
typedef struct deck deck;

struct board {
  deck * pile;
  card display[21];
  int size;
};
typedef struct board board;

int populate(deck * d);
int shuffle(deck * d);
int deal(deck * d); // EDIT
int check_set(card c1, card c2, card c3);
int remove_card(deck d);
int set_exists(board b);
void print_card(card c);
void print_deck(deck d);
void swap(deck * d, int i1, int i3);
#endif
