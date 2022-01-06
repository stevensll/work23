#include "networking.h"


int main() {

  int sd = client_handshake();

  char *buffer = calloc(BUFFER_SIZE, sizeof(char));

  while (1) {

    printf("Enter text to be capitalized: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    write(sd, buffer, BUFFER_SIZE);

    read(sd, buffer, BUFFER_SIZE);

    printf("Server sends: %s\n", buffer);

  }

}