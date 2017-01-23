#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define STDIN STDIN_FILENO
#define STDOUT STDOUT_FILENO

int s_setup() {
  int sd = -1; // Socket Descriptor

  // Creating A Socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  inet_aton( "127.0.0.1", &(sin.sin_addr) );
  //sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(5375);
    
  bind( sd, (struct sockaddr *)&sin, sizeof(sin) );
  
  return sd;
}

int s_connect(int sd) {
  int connection = -1;
  if (listen(sd, 1))
    return -1; // Error
  printf("Server listening...\n");

  struct sockaddr_in sin;
  unsigned int sin_size = sizeof(sin);
  connection = accept( sd, (struct sockaddr *)&sin, &sin_size );

  if (connection == -1)
    return connection;
  
  printf("Successfully connected to [%d]!\n", connection);
  return connection;
}

int parse(char * buffer) {
  if (strcmp(buffer, "add") == 0) {
    printf("[SERVER] Adding connection...\n");

    int sd;
    sd = s_setup();
    if (sd > -1) 
      printf("Socket successfully created!\n");
    sd = s_connect(sd);

    return sd;
  }
  return -1;
}

int main() {
  char rbuffer[128]; // Reading From Clients
  char wbuffer[128]; // Writing To Clients
  fd_set fds;
  char * message = "Connected!\n";
  int max_clients = 4;
  int clients[max_clients];
  int num_clients = 0;
  int max_sd;
  int i;

  // Initializing Client Sockets
  for (i = 0; i < max_clients; i++)
    clients[i] = 0;

  int sd;
  sd = s_setup();
  if (sd > -1) {
    printf("Socket successfully created!\n");
  }

  int host = -1;
  host = s_connect(sd);
  if (host > -1) {
    printf("Connection established to host!\n");
  }  

  max_sd = host;

  // Before Starting Game, Setting Up Room
  printf("Host: %d\n", max_sd);
  while (1) {
    printf("SERVER>>> ");
    fflush(stdout);
    FD_ZERO(&fds);
    FD_SET(STDIN, &fds);
    FD_SET(host, &fds);

    select( max_sd + 1, &fds, NULL, NULL, NULL );
    
    if (FD_ISSET(STDIN, &fds)) {
      //printf("Received input from stdin!\n"); // Debugging
      fgets( rbuffer, sizeof(rbuffer), stdin );
      printf("\n[SERVER STDIN] %s\n", rbuffer);
    }
    if (FD_ISSET(host, &fds)) {
      recv(host, rbuffer, sizeof(rbuffer), 0);
      printf("\n[CLIENT %d] %s\n", host, rbuffer);
      strcpy(wbuffer, "[SERVER] Received: ");
      strcat(wbuffer, rbuffer);
      send(host, wbuffer, sizeof(wbuffer), 0);
    }
  }
  
  return 0;
}


/*
int main() {
  int master_socket;
  int addrlen;
  int new_socket;
  int client_socket[32];
  int max_clients = 32;
  int i;
  int sd, max_sd;
  int activity;
  int valread;
  char buffer[1024];

  fd_set readfds;
  char * message = "You have connected!";

  for (i = 0; i < max_clients; i++)
    client_socket[i] = 0;

  master_socket = s_setup();
  listen(master_socket, 1);
  
  printf("Waiting for connections...\n");

  while (1) {
    printf("Hello\n");

    FD_ZERO(&readfds);
    FD_SET(master_socket, &readfds);
    
    // Adding Child Sockets
    for (i = 0; i < max_clients; i++) {
      sd = client_socket[i];

      if (sd > 0) // client connected
	FD_SET(sd, &readfds);

      if (sd > max_sd) // max_sd used for select
	max_sd = sd;
    }
    
    activity = select( max_sd + 1,
		       &readfds,
		       0, 0, 0 );

    // Check Master Socket
    if (FD_ISSET(master_socket, &readfds)) {
      new_socket = s_connect(master_socket);
      
      for (i = 0; i < max_clients; i++) {
	if (client_socket[i] == 0) { // empty space
	  client_socket[i] = new_socket;
	  break;
	}
      }
    }

    // Check Other Sockets
    for (i = 0; i < max_clients; i++) {
      sd = client_socket[i];

      if (FD_ISSET(sd, &readfds)) {
	valread = read( sd, buffer, 1023 );
	if (valread == 0) { // Client Disconnected
	  close(sd);
	  client_socket[i] = 0;
	} else {
	  buffer[valread] = 0;
	  printf("[SERVER] Read %s\n", buffer);
	}
      }
    }
  }
  return 0;
}
*/
