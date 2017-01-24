#ifndef SET_SERVER
#define SET_SERVER

#define INPUT_BUFFER_SIZE 128
#define STDIN STDIN_FILENO
#define STDOUT STDOUT_FILENO     

int s_setup();
int s_connect();
int c_connect();

#endif
