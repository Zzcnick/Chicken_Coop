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
  char * shape; // "O", "X", or "S"
  char * shading; // "{}", "[]", or "()"
  int number; // 1, 2, or 3
  char * color; // RED, GRN, or BLU  
};
typedef struct card card;

struct deck {
  card order[81];
  int dealt;
  int removed;
}; 
typedef struct deck deck;

int populate(deck * d); //DONE
int shuffle(deck * d); //DONE
int deal(deck * d); //DONE
int check_attr(void *a, void *b, void *c); //DONE
int check_attr_nums(int a, int b, int c); // DONE
int check_set(card c1, card c2, card c3); //DONE
int remove_set(deck * d, int index1, int index2, int index3); //DONE
void print_card(card c); //DONE
void swap(deck * d, int i1, int i3); //DONE
void display(deck d); //DONE
int set_exists(deck d); 
#endif
