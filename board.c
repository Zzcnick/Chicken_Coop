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



int main() {

  card kinbote = { "X", "[]", 2, GRN };
  printf("%s",ctos(kinbote));

  printf("\t");
  
  card shade = { "S", "{}", 3, BLU };
  printf("%s",ctos(shade));

  printf("\n");
  return 0;
}
