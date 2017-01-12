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

int main() {

  deck duck;
  populate(&duck);
  print_deck(duck);
  printf("\n");

  return 0;
}

// THE JUNKYARD OF OBSOLETE CODE
// ==================================================
// OBSOLETE 
void ctos(card c) {

  //return "hello";
  /*
  char cardstr[256];
  strcpy(cardstr, "hello");
  printf("%s\n", cardstr);
  c->display = cardstr;
  return c->display;
*/
  /*
  strcpy(cardstr, c->color); // change color
  strcat(cardstr, c->shading); // opening bracket and closing bracket

  int l = strlen(cardstr) - 1;
  int i;
  //for (i = 0; i < c->number; i++) {
  //cardstr[l] = c->shape; // will overwrite closing bracket on first iteration
  //l++;
  //}
  //cardstr[l] = 0; // null terminate
  //strcat(cardstr, c->shading+1); // closing bracket
  strcat(cardstr, WHT); // change color back to white
  printf("%s\n", cardstr);
  cardstr[10] = 0;

  c->display = cardstr;
  printf("C Display inside ctos: %s\n", c->display);
  return c->display;
  */

  /*
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
  */
}

