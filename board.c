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

int deal(deck * d) {
  if (d->removed - d->dealt < 21) {    
    d->dealt-=3;
    return 0;
  }
  return -1;
}

int remove_set(deck * d, int r1, int c1, int r2, int c2, int r3, int c3) {
  int offset = d->dealt;

  int index1 = (r1+1)*(c1+1)-1+offset;
  int index2 = (r2+1)*(c2+1)-1+offset;
  int index3 = (r3+1)*(c3+1)-1+offset;

  int toswap1 = d->removed - 3;
  int toswap2 = d->removed - 2;
  int toswap3 = d->removed - 1;
  
  swap(d, index1, toswap1);
  swap(d, index2, toswap2);
  swap(d, index3, toswap3);
  
  d->removed-=3;
  return 0;
}
  
void display(deck d) {
  printf("\t0\t1\t2\n");
  int i;
  char alphabet[7] = "ABCDEFG";
  int a=0;
  for (i = d.dealt; i < d.removed; i++ ) {
    if (i%3 == 0) {
      printf("%c\t", alphabet[a]);
      a++;
    }
    print_card(d.order[i]);
    if (i%3 == 2) {
      printf("\n");
    }
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
  d->dealt = 81;
  d->removed = 81;
  return 0;
}

int shuffle(deck * d) {
  card tmp;
  swap(d, 0, 1);
    int i, i1, i2;
  int p = d->dealt;
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



int check_attr(void *a, void *b, void *c) {
  return (a==b && b==c) || ((a!=b) && (b!=c) && (c!=a));
}


int check_set(card c1, card c2, card c3) {
  int checkNums = check_attr(c1.number, c2.number, c3.number);
  int checkShapes = check_attr(c1.shape, c2.shape, c3.shape);
  int checkColors = check_attr(c1.color, c2.color, c3.color);
  int checkShadings = check_attr(c1.shading, c2.shading, c3.shading);    
  return checkNums && checkShapes && checkColors && checkShadings;
}



