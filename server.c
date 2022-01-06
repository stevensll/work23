#include "networking.h"


int main() {
    
    int sd = server_connect();
    printf("Server up and running");
    listen_socket(sd);
    
}