// ============================================
// Board Manipulation and Card Manipulation
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

/* char * ctos(card c) {
  char * ret = "";
  int i;
  for (i=0; i<c.number; i++)  {
    char * str = c.;
    ret = strcat(ret, 

struct card {
  char shape; // 'O', 'X', or 'S'
  char * shading; // "{}", "[]", or "()"
  int number; // 1, 2, or 3
  char * color; // RED, GRN, or BLU
  char * display; // The string version of the card
};

*/

void print_card(card c) {
  printf("%s\n", c.display);
}

void print_deck(deck d) {
  int i;
  for (i = 0; i < d.pointer; i++) {
    print_card(d.order[i]);
  }
}

int populate(deck * d) {
  int i;
  for (i = 0; i < 81; i++) {
    card c;
    if (i % 3 == 0) c.shape = 'O';
    if (i % 3 == 1) c.shape = 'S';
    if (i % 3 == 2) c.shape = 'X';
    if ((i/3) % 3 == 0) c.shading = "{}";
    if ((i/3) % 3 == 1) c.shading = "[]";
    if ((i/3) % 3 == 2) c.shading = "()";
    c.number = ((i/9) % 3 == 0);
    if ((i/27) % 3 == 0) c.color = RED;
    if ((i/27) % 3 == 0) c.color = GRN;
    if ((i/27) % 3 == 0) c.color = BLU;
    //    sprintf(c.display, "%d\n", i);
    c.display = "!!!";
    d->order[i] = c;
  }
  d->pointer = 81; // Number Of Cards Remaining
  return 0;
}

//int populate(deck d);
//int shuffle(deck d);
//int deal(deck d); // EDIT
//int check_set(card c1, card c2, card c3);
//int remove_card(deck d);
//void print_deck(deck d)

int main() {

  /* // Simple Deck Testing
  deck d;
  int x = populate(&d);
  printf("Status: %d\n", x);
  print_deck(d);
  */

  return 0;
}
