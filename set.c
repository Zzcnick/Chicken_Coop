// ============================================
// Set Driver File
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include "highscore.h"
#include "board.h"
#include <time.h>

int parse(deck * d, char * input) {
  int r1, r2, r3;
  r1 = input[0]-65;
  r2 = input[3]-65;
  r3 = input[6]-65;
  int c1, c2, c3;
  c1 = input[1] - 48;
  c2 = input[4] - 48;
  c3 = input[7] - 48;
  int offset = d->dealt;
  int index1 = 3*(r1+1) - (2-c1) - 1 + offset;
  int index2 = 3*(r2+1) - (2-c2) - 1 + offset;
  int index3 = 3*(r3+1) - (2-c3) - 1 + offset;
  
  if (check_set(d->order[index1], d->order[index2], d->order[index3]) != 0) {
    remove_set(d, index1, index2, index3);
    printf("BOOYAH!\n");
    return 0;
  }
  else {
    printf("If at first you don't succeed, try try again!\n");
    return 1;
  }
}

/* ============= MULTIPLAYER ==============
int c_connect() {
  int sd = -1;
  sd = socket( AF_INET, SOCK_STREAM, 0 );

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  inet_aton( "127.0.0.1", &(sin.sin_addr) );
  sin.sin_port = htons(5375);

  sd = connect( sd, (struct sockaddr_in *)sin, sizeof(sin) );

  return sd;
}
 ============================================ */
    
int main() {    
  system("clear");
  srand(time(0));
  printf("SET 2.0\n");
  printf("By Sarah Yoon and Zicheng Zhen\n\n");

  printf("Input username: ");
  char user[1000];
  fgets(user, sizeof(user), stdin);
  *strchr(user, '\n') = 0;
  printf("===============================\n");

  printf("Choose a game mode:\n");
  printf("1. Single Player\n");
  printf("2. Multiplayer\n");
  printf("Enter 1 or 2: ");
  char mode[8];
  fgets(mode, sizeof(mode), stdin);
  *strchr(mode, '\n') = 0;

  if (strcmp(mode, "1") == 0) {
    deck duck;
    populate(&duck);
    shuffle(&duck);
    int secsToAdd = 0;
    int times[27];
    int index = 0;
    
    while (duck.removed > 0) {      
      while (duck.removed-duck.dealt < 9) {
	deal(&duck);
      }
      display(duck);

      while (set_exists(duck)==-1) {
	printf("No sets on the table! Dealing...\n");
	deal(&duck);
	display(duck);
      }
    
      printf("Please enter a Set.\n");
      printf("%s: ", user);
      time_t start_time, stop_time;
      int elapsed;
      start_time = time(NULL);
      char input[1024];
      fgets(input, sizeof(input), stdin);
      *strchr(input, '\n') = 0;
      system("clear");
      if (strcmp(input, "exit") == 0) {
	exit(0);
      }
      else {
	printf("\n");
	if (parse(&duck, input) == 0) {
	  stop_time = time(NULL);
	  elapsed = difftime(stop_time, start_time) + secsToAdd;
	  printf("You took %d seconds.\n", elapsed);
	  times[index] = elapsed;
	  index++;
	  secsToAdd = 0;
	}
	else {
	  stop_time = time(NULL);
	  elapsed = difftime(stop_time, start_time);
	  secsToAdd += elapsed;
	  printf("Tick tock, maggot!\n");
	}
	printf("\n");
      }
    }
    double score;
    for (index=0; index<27; index++) {
      score += (double)times[index];
    }
    score = score/27;
    printf("Thanks for playing! On average you took %lf seconds per Set.\n", score);
  }
  else {
    printf("Sorry, but Multiplayer isn't working yet :(\n");
  }
  return 0;
}
