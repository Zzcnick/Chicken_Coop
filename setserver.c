#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "setserver.h"

int s_setup() {
  int sd = -1; // Socket Descriptor

  // Creating A Socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;

  inet_aton( "149.89.150.103" , &(sin.sin_addr) );
  //sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(5375);
    
  bind( sd, (struct sockaddr *)&sin, sizeof(sin) );
  
  return sd;
}

int s_connect(int sd) {
  int connection = -1;
  if (listen(sd, 1))
    return -1; // Error
  printf("Waiting for incoming connection...\n");

  struct sockaddr_in sin;
  unsigned int sin_size = sizeof(sin);
  connection = accept( sd, (struct sockaddr *)&sin, &sin_size );

  if (connection == -1)
    return connection;
  
  // printf("Successfully connected to [%d]!\n", connection); // Debugging
  return connection;
}

int c_connect(char * ip) {
  int sd = -1;
  sd = socket( AF_INET, SOCK_STREAM, 0 );

  printf("IP: %s\n", ip); // Debugging

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  inet_aton( ip , &(sin.sin_addr) );
  sin.sin_port = htons(5375);

  if (connect( sd, (struct sockaddr *)&sin, sizeof(sin))) {
    printf("Something went wrong...\n");
    return -1;
  }

  return sd;
}
