#include "networking.h"

int server_connect() {
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo("127.0.0.1", "9845", hints, &results);  //Server sets node to NULL
  
  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  bind(sd, results->ai_addr, results->ai_addrlen);

  free(hints);
  freeaddrinfo(results);
  return sd;
}
void listen_socket(int sd){
  listen(sd,5);
  server_handshake(sd);
}

void server_handshake(int sd) {
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);

  int f = fork();
  if(f){
    server_handshake(sd);
  }
  else{
    upper(client_socket);
  }
}

int client_handshake() {
 struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo("127.0.0.1", "9845", hints, &results);  //Server sets node to NULL

  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  bind(sd, results->ai_addr, results->ai_addrlen);


  free(hints);
  freeaddrinfo(results);

  socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  connect(sd, results->ai_addr, results->ai_addrlen);

  return sd;
}

void upper(int client_socket){
  char *buffer = calloc(BUFFER_SIZE, sizeof(char));
  while(1){
    read(client_socket, buffer, BUFFER_SIZE);

    int i;
    for(i = 0; i < strlen(buffer); i++){
      buffer[i] = toupper(buffer[i]);
    }
    write(client_socket, buffer,BUFFER_SIZE);
  }
}