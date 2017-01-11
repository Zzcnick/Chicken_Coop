// ============================================
// Board Manipulation and Card Manipulation
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

char * ctos(card c) {
  char cardstr[256];
  strcpy(cardstr, c.color);

  char firstbracket[4];
  strcpy(firstbracket, c.shading);
  firstbracket[1]='\0';
  strcat(cardstr, firstbracket);
  
  int i;  
  for (i=0; i<c.number; i++) {
    strcat(cardstr, c.shape);
  }

  strcat(cardstr, &c.shading[1]);
  
  strcat(cardstr, WHT);

  char *ret = (char*)malloc(strlen(cardstr)+1);
  strcpy(ret, cardstr);
  return ret;
}

void print_card(card c) {
  printf("%s\n\n", ctos(c));
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
    //c.display = "!!!";
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

  card kinbote = { "X", "[]", 2, GRN };
  print_card(kinbote);
  
  card shade = { "S", "{}", 3, BLU };
  print_card(shade);
  
  printf("\n");

  return 0;
}
