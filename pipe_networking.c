#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  if (mkfifo("non", 0666) == -1) {
    perror("Could not create WKP");
  }
  printf("WKP created. Waiting for client connection...\n");

  if(from_client = open(WKP, O_RDONLY) == -1) {
    perror("Could not open WKP for reading");
    unlink("non");
    exit(1);
  }

  printf("Client connected. Removing WKP...\n");
  unlink("non");
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  printf("Waiting for client to send private pipe name...\n");
  from_client = open("non", O_RDONLY);
  if (from_client == -1) {
    perror("Error opening WKP");
    exit(1);
  }

  char ppipe[256];
  if (read(from_client, ppipe, sizeof(ppipe)) <= 0) {
    perror("Error reading private pipe name from client");
    close(from_client);
    unlink("non"); 
    exit(1);
  }
  printf("Received private pipe name from client: %s\n", ppipe);

  *to_client = open(ppipe, O_WRONLY);
  if (*to_client == -1) {
    perror("Error opening client's private pipe");
    close(from_client);
    unlink("non");
    exit(1);
  }
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
