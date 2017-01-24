// ============================================
// Set Driver File
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>    
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>                   
#include "highscore.h"
#include "board.h"
#include "setserver.h"

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

char * remove_whitespace(char * buffer) {
  int l = strlen(buffer);
  int i;
  for (i = 0; i < l; i++) {
    if (buffer[i] == ' ') {
      char tmp = buffer[i];
      buffer[i] = buffer[i + 1];
      buffer[i + 1] = tmp;
    }
  }
}

int main() {    
  system("clear");
  srand(time(0));
  printf("Set 2.0\n");
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

  // SINGLE PLAYER MODE
  if (strcmp(mode, "1") == 0) {
    deck duck;
    populate(&duck);
    shuffle(&duck);
    int secsToAdd = 0;
    int times[3];
    int index = 0;
    
    while (duck.removed > 72) {      
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
    for (index=0; index<3; index++) {
      score += (double)times[index];
    }
    score = score/3;
    printf("Thanks for playing! On average you took %lf seconds per Set.\n", score);

    playerscore * list = read_scores("h.txt");
    list = insert(list, user, score);
    write_scores(list, "h.txt");
    printf("\nScore rankings:\n");
    printf("===============================\n");
    print_scores("h.txt");
    free(list);
    printf("\n");
  }

  // MULTIPLAYER MODE
  else if (strcmp(mode, "2") == 0) {
    printf("You have selected multiplayer!\n");
    printf("Are you hosting or joining a room?\n\t1. Hosting\n\t2. Joining\n\nEnter a choice: ");
    
    char rbuffer[128];
    char wbuffer[128];
    fd_set fds;
    int max_sd;

    while (1) {
      fgets(mode, sizeof(mode), stdin);
      *strchr(mode, '\n') = 0;
      remove_whitespace(mode);

      // SERVER CODE ==============================
      if (strcmp(mode, "1") == 0) { // Hosting
	printf("You are hosting the server!\n");
	int sd;
	sd = s_setup();
	if (sd < 0) {
	  printf("Error hosting; aborting.\n");
	  return -1;
	}
	int host = -1;
	host = s_connect(sd);
	if (host > -1) {
	  printf("Incoming connection received. Game starting!\n");
	}
	max_sd = host;
	
	// GAME SETUP
	deck swan;
	populate(&swan);
	shuffle(&swan);

	// SELECT LOOP
	while (duck.removed > 0) {


	  while (host > 0) {
	    FD_ZERO(&fds);
	    FD_SET(STDIN, &fds);
	    FD_SET(host, &fds);
	    select(max_sd + 1, &fds, NULL, NULL, NULL);

	    if (FD_ISSET(STDIN, &fds)) {
	      printf("[SERVER STDIN] ");
	      fgets(rbuffer, sizeof(rbuffer), stdin);
	      printf("%s\n", rbuffer);
	    }
	    if (FD_ISSET(host, &fds)) {
	      recv(host, rbuffer, sizeof(rbuffer), 0);
	      printf("[CLIENT %d] %s\n", host, rbuffer);
	      strcpy(wbuffer, "Received: ");
	      strcat(wbuffer, rbuffer);
	      send(host, wbuffer, sizeof(wbuffer), 0);
	    }
	  }
	}
      }
      // END SERVER CODE ==========================

      // CLIENT CODE ==============================
      else if (strcmp(mode, "2") == 0) { // Joining
	printf("You are joining a server!\n");
	int sd = c_connect();
	if (sd < 0) {
	  printf("Error joining; aborting.\n");
	}

	// SELECT LOOP
	while (sd > 0) {
	  FD_ZERO(&fds);
	  FD_SET(STDIN, &fds);
	  FD_SET(sd, &fds);
	  select(sd + 1, &fds, NULL, NULL, NULL);
	  
	  if (FD_ISSET(STDIN, &fds)) {
	    fgets(rbuffer, sizeof(rbuffer), stdin);
	    send(sd, rbuffer, sizeof(rbuffer), 0);
	  }
	  if (FD_ISSET(sd, &fds)) {
	    recv(sd, rbuffer, sizeof(rbuffer), 0);
	    printf("[SERVER] %s\n", rbuffer);
	  }
	}
      }
      // END CLIENT CODE ==========================
    }
  }
  return 0;
}
