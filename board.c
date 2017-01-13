// ============================================
// Board Manipulation and Card Manipulation
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

void print_card(card c) {
  printf("%s", c.color);
  printf("%c", c.shading[0]);
  int i;
  for (i = 0; i < c.number; i++)
    printf("%c", c.shape);
  printf("%c", c.shading[1]);
  printf("%s\t", WHT);
}

void print_deck(deck d) {
  int i;
  for (i = 0; i < d.pointer; i++) {
    print_card(d.order[i]);
    if (i % 9 == 8)
      printf("\n");
  }
}

int populate(deck * d) {
  int i;
  card c;
  for (i = 0; i < 81; i++) {
    if (i % 3 == 0) c.shape = 'O';
    if (i % 3 == 1) c.shape = 'S';
    if (i % 3 == 2) c.shape = 'X';
    if ((i/3) % 3 == 0) c.shading = "{}";
    if ((i/3) % 3 == 1) c.shading = "[]";
    if ((i/3) % 3 == 2) c.shading = "()";
    c.number = ((i/9) % 3 + 1);
    if ((i/27) % 3 == 0) c.color = RED;
    if ((i/27) % 3 == 1) c.color = GRN;
    if ((i/27) % 3 == 2) c.color = BLU;
    d->order[i] = c;
  }
  d->pointer = 81; // Number Of Cards Remaining
  return 0;
}

int shuffle(deck * d) {
  card tmp;
  swap(d, 0, 1);
    int i, i1, i2;
  int p = d->pointer;
  for (i = 0; i < p * 7; i++) {
    i1 = rand() % p;
    i2 = rand() % p;
    swap(d, i1, i2);
  }
  return 0;
}

void swap(deck * d, int i1, int i2) {
  card tmp;
  tmp = d->order[i1];
  d->order[i1] = d->order[i2];
  d->order[i2] = tmp;
}

int set_exists(board b) {
  if (b.size < 3) 
    return -1;
  int i, j, k;
  for (i = 0; i < b.size - 2; i++) {
    for (j = 1; j < b.size - 1; j++) {
      for (k = 2; k < b.size; k++) {
	if (check_set(b.display[i], b.display[j], b.display[k]))
	  return -1;
      }
    }
  }
  return 0;
}

int check_set(card c1, card c2, card c3) {
  return 0;
}

int main() {
  // Seeding Randomness
  srand(time(0));

  deck duck;
  populate(&duck);

  printf("Before Shuffling:\n");
  print_deck(duck);
  printf("\n");

  printf("After Shuffling:\n");
  shuffle(&duck);
  print_deck(duck);
  printf("\n");

  return 0;
}

// THE JUNKYARD OF OBSOLETE CODE
// ==================================================
