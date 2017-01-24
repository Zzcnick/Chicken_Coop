// ============================================
// Set Driver File
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>    
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>                   
#include "highscore.h"
#include "board.h"
#include "setserver.h"

#define BUFFER_SIZE 4096

// Instance Variables... sort of...
int MASTER_HOST = -1;
int MASTER_SERVER = -1;

static void sighandler(int signo) {
  if (signo == SIGINT)
    { // ^C (signal 2)
      if (MASTER_HOST > 0)
	close(MASTER_HOST);
      if (MASTER_SERVER > 0)
	close(MASTER_SERVER);
      exit(0);
    }
}

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

void remove_whitespace(char * buffer) {
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

void send_client(int sd, char * buffer, char * message) {
  strcpy(buffer, message); 
  send(sd, buffer, BUFFER_SIZE, 0);
  //printf("DEBUG: %s\n", buffer); // Debugging
}

int main() {    
  signal(SIGINT, sighandler);

  system("clear");
  srand(time(0));
  printf("Set 2.0\n");
  printf("By Sarah Yoon and Zicheng Zhen\n\n");

  printf("Input username: ");
  char user[128];
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
    
    char rbuffer[BUFFER_SIZE];
    char wbuffer[BUFFER_SIZE];
    fd_set fds;
    int max_sd;
    int result;
    int hostscore = 0, serverscore = 0;
    int guesser; // 0 - server, 1 - client
    char hostname[128]; // username of host
    char ip[32]; // IP Address - Client

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
	MASTER_HOST = host;
	recv(host, hostname, 128, 0); // Receive hostname

	// GAME SETUP
	deck swan;
	populate(&swan);
	shuffle(&swan);

	// SELECT LOOP
	while (swan.removed > 0) { // CHANGE THIS LATER

	  wbuffer[0] = 0; // Clear Buffer

	  while (swan.removed - swan.dealt < 9) {
	    deal(&swan);
	  }
	  display(swan);
	  write_display(wbuffer, swan);
	  send(host, wbuffer, sizeof(wbuffer), 0);

	  while (set_exists(swan) == -1 && swan.dealt > 0) {
	    printf("No sets on the table! Dealing...\n"); 
	    send_client(host, wbuffer, "No sets on the table! Dealing...\n"); 
	    deal(&swan);
	    display(swan);
	    write_display(wbuffer, swan);
	    send(host, wbuffer, sizeof(wbuffer), 0);
	  }
	  
	  if (set_exists(swan) == -1 && swan.dealt == 0) {
	    break; // Exit to End Condition
	  }

	  printf("Please enter a Set.\n%s: ", user);
	  sprintf(wbuffer, "Please enter a Set.\n%s: ", hostname);
	  send(host, wbuffer, sizeof(wbuffer), 0);
	  fflush(stdout); // Flush Buffer

	  wbuffer[0] = 0; // Clear Buffer
	  
	  if (host > 0) {
	    FD_ZERO(&fds);
	    FD_SET(STDIN, &fds);
	    FD_SET(host, &fds);
	    select(max_sd + 1, &fds, NULL, NULL, NULL);

	    if (FD_ISSET(STDIN, &fds)) {
	      //printf("[SERVER STDIN] "); // Debugging
	      fgets(rbuffer, sizeof(rbuffer), stdin);
	      *strchr(rbuffer, '\n') = 0;
	      if (strcmp(rbuffer, "exit") == 0) { exit(0); }
	      else {
		result = parse(&swan, rbuffer);
		guesser = 0;
	      }
	      //printf("DEBUGGING:\n%s\n", wbuffer); // Debugging
	      //printf("%s\n", rbuffer); // Debugging
	    }
	    if (FD_ISSET(host, &fds)) {
	      recv(host, rbuffer, sizeof(rbuffer), 0);
	      *strchr(rbuffer, '\n') = 0;
	      if (strcmp(rbuffer, "exit") == 0) { exit(0); }
	      else {
		result = parse(&swan, rbuffer);
		guesser = 1;
	      }
	      //send(host, rbuffer, sizeof(rbuffer), 0); // Debugging
	      //printf("[CLIENT %d] %s\n", host, rbuffer); // Debugging
	    }
	  }
	  
	  printf("\e[1;1H\e[2J\n"); // Clear Screen
	  send_client(host, wbuffer, "\e[1;1H\e[2J\n"); // Clear Client
	  
	  if (result == 0) { // Success
	    if (guesser == 0) { // Server
	      printf("A set has been found by %s!\n", user);
	      sprintf(wbuffer, "A set has been found by %s!\n", user);
	      send(host, wbuffer, sizeof(wbuffer), 0);
	      serverscore++;
	    } else { // Client
	      printf("A set has been found by %s!\n", hostname);
	      sprintf(wbuffer, "A set has been found by %s!\n", hostname);
	      send(host, wbuffer, sizeof(wbuffer), 0);
	      hostscore++;
	    }
	  } else  { // Failure
	    if (guesser == 0) { // Server
	      printf("%s guessed, and failed!\n", user);
	      sprintf(wbuffer, "%s guessed, and failed!\n", user);
	      send(host, wbuffer, sizeof(wbuffer), 0);
	    } else { // Client
	      printf("%s guessed, and failed!\n", hostname);
	      sprintf(wbuffer, "%s guessed, and failed!\n", hostname);
	      send(host, wbuffer, sizeof(wbuffer), 0);
	    }
	  }	    
	}
	// END GAME
	printf("Game finished!\n");
	send_client(host, wbuffer, "Game finished!\n");
	printf("Final Scores:\n%s: %d\n%s: %d\n",
	       user, serverscore, hostname, hostscore);
	sprintf(wbuffer,
		"Final Scores:\n%s: %d\n%s: %d\n",
		user, serverscore, hostname, hostscore);
	send(host, wbuffer, sizeof(wbuffer), 0);
	strcpy(wbuffer, "exit");
	send(host, wbuffer, sizeof(wbuffer), 0);
	return 0; // IMPLEMENT SCORES HERE
      }
      // END SERVER CODE ==========================

      // CLIENT CODE ==============================
      else if (strcmp(mode, "2") == 0) { // Joining
	printf("You are joining a server!\n");
	printf("Please enter the IP address you are trying to connect to.\n");
	fgets(ip, sizeof(ip), stdin);
	*strchr(ip, '\n') = 0;
	printf("IP entered: %s\n", ip); // Debugging
	int sd = c_connect(ip);
	if (sd < 0) {
	  printf("Error joining; aborting.\n");
	  return -1;
	}
	send(sd, user, 128, 0); // Sending username to server.
	MASTER_HOST = sd;

	// SELECT LOOP
	while (sd > 0) {
	  FD_ZERO(&fds);
	  FD_SET(STDIN, &fds);
	  FD_SET(sd, &fds);
	  select(sd + 1, &fds, NULL, NULL, NULL);
	  
	  if (FD_ISSET(STDIN, &fds)) {
	    fgets(rbuffer, sizeof(rbuffer), stdin);
	    if (strcmp(rbuffer, "exit") == 0) {
	      return 0;
	    }
	    send(sd, rbuffer, sizeof(rbuffer), 0);
	  }
	  if (FD_ISSET(sd, &fds)) {
	    recv(sd, rbuffer, sizeof(rbuffer), 0);
	    if (strcmp(rbuffer, "exit") == 0) {
	      return 0;
	    }
	    printf("%s", rbuffer); // Debugging
	    fflush(stdout); // Printing Name
	  }
	}
      }
      // END CLIENT CODE ==========================
    }
  }
  return 0;
}
