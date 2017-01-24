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
    printf("%s", c.shape);
  printf("%c", c.shading[1]);
  printf("%s\t", WHT);
}

void write_card(char * buffer, card c) {
  sprintf(buffer + strlen(buffer), "%s", c.color);
  sprintf(buffer + strlen(buffer), "%c", c.shading[0]);
  int i;
  for (i = 0; i < c.number; i++)
    sprintf(buffer + strlen(buffer), "%s", c.shape);
  sprintf(buffer + strlen(buffer), "%c", c.shading[1]);
  sprintf(buffer + strlen(buffer), "%s\t", WHT);
}

int deal(deck * d) {
  if (d->removed - d->dealt < 21) {
    if (d->dealt == 0) {
      return 1;
    }
    d->dealt-=3;
    return 0;
  }
  return -1;
}

int remove_set(deck * d, int index1, int index2, int index3) {
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
  printf("\n");
}

void write_display(char * buffer, deck d) {
  sprintf(buffer, "\t0\t1\t2\n");
  int i;
  char alphabet[7] = "ABCDEFG";
  int a=0;
  for (i = d.dealt; i < d.removed; i++ ) {
    if (i%3 == 0) {
      sprintf(buffer + strlen(buffer), "%c\t", alphabet[a]);
      a++;
    }
    write_card(buffer, d.order[i]);
    if (i%3 == 2) {
      sprintf(buffer + strlen(buffer), "\n");
    }
  }
  sprintf(buffer + strlen(buffer), "\n");
  //printf("DEBUGGING:\n%s\n", buffer); // Debugging
}

int populate(deck * d) {
  int i;
  card c;
  for (i = 0; i < 81; i++) {
    if (i % 3 == 0) c.shape = "O";
    if (i % 3 == 1) c.shape = "S";
    if (i % 3 == 2) c.shape = "X";
    if ((i/3) % 3 == 0) c.shading = "{}";
    if ((i/3) % 3 == 1) c.shading = "[]";
    if ((i/3) % 3 == 2) c.shading = "()";
    c.number = ((i/9) % 3 + 1);
    if ((i/27) % 3 == 0) c.color = RED;
    if ((i/27) % 3 == 1) c.color = GRN;
    if ((i/27) % 3 == 2) c.color = BLU;
    d->order[i] = c;
  }
  d->dealt = 81; // Index of cards that have been dealt
  d->removed = 81; // Index of cards that have been removed
  // |--------<DEALT>---------<REMOVED>---------|
  // |  undealt  |   displayed    |     removed |
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
int check_attr_nums(int a, int b, int c) {
  return (a==b && b==c) || ((a!=b) && (b!=c) && (c!=a));
}

int check_set(card c1, card c2, card c3) {
  int checkNums = check_attr_nums(c1.number, c2.number, c3.number);
  int checkShapes = check_attr((void *)c1.shape, (void *)c2.shape, (void *)c3.shape);
  int checkColors = check_attr((void *)c1.color, (void *)c2.color, (void *)c3.color);
  int checkShadings = check_attr((void *)c1.shading, (void *)c2.shading, (void *)c3.shading);    
  return checkNums && checkShapes && checkColors && checkShadings;
}

int set_exists(deck d) {
  int a;
  card board[21];
  int size = 0;
  for (a=d.dealt; a<d.removed; a++) {
    board[a-d.dealt] = d.order[a];
    size++;
  }
  if (size < 3) {
    return -1;
  }
  int i, j, k;
  for (i=0; i<size-2; i++) {
    for (j=i+1; j<size-1; j++) {
      for (k=i+2; k<size; k++) {
	if (check_set(board[i], board[j], board[k])) {
	  //printf("%d, %d, %d\n", i, j, k); // Debugging
	  return 0;
	}
      }
    }
  }
  return -1;
}


  
      
  



