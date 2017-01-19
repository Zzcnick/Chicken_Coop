#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  
  int sd = -1; // Socket Descriptor
  int i;

  // Creating A Socket
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_addr = inet_aton(
  
  i = bind( sd, 

  return 0;
}
