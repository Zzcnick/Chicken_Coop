#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int s_setup() {
  int sd = -1; // Socket Descriptor

  // Creating A Socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
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

int main() {
  int sd = -1; int fd = -1;
  sd = s_setup();
  if (sd > -1) {
    printf("Socket successfully created!\n");
  }
  fd = s_connect(sd);
  if (fd > -1) {
    printf("Connection established!\n");
  }
}
