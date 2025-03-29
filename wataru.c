#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  char buffer[BUFFER_SIZE] = {0};

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket Failed");
    exit(EXIT_FAILURE);
  }

  // address options
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // binding port to socket
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("Accept failed");
      continue;
    }

    printf("New connection from %s:%d\n", inet_ntoa(address.sin_addr),
           ntohs(address.sin_port));

    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork failed");
      close(new_socket);
    } else if (pid == 0) {
      close(server_fd);

      read(new_socket, buffer, BUFFER_SIZE);
      printf("Client: %s\n", buffer);
      send(new_socket, buffer, strlen(buffer), 0);

      printf("Message echoed back to client.\n");
      close(new_socket);
      exit(0);
    } else {
      close(new_socket);
    }
  }
}
