#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERVPORT 3333

int main(int argc, char *argv[]) {
  int sd, rc;
  struct sockaddr_in serveraddr, clientaddr;
  int clientaddrlen = sizeof(clientaddr);
  int serveraddrlen = sizeof(serveraddr);
  char buffer[100];
  char *bufptr = buffer;
  int buflen = sizeof(buffer);

  if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("UDP server - socket() error");
    exit(-1);
  } else {
    printf("UDP server - socket() is OK\n");
  }
  printf("UDP server - try to bind...\n");

  /* bind to address */
  memset(&serveraddr, 0x00, serveraddrlen);
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(SERVPORT);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((rc = bind(sd, (struct sockaddr *)&serveraddr, serveraddrlen)) < 0) {
    perror("UDP server - bind() error");
    close(sd);
    exit(-1);
  } else
    printf("UDP server - bind() is OK\n");

  printf("Using IP %s and port %d\n", inet_ntoa(serveraddr.sin_addr), SERVPORT);
  printf("UDP server - Listening...\n");

  rc = recvfrom(sd, bufptr, buflen, 0, (struct sockaddr *)&clientaddr,
                &clientaddrlen);

  if (rc < 0) {
    perror("UDP Server - recvfrom() error");
    close(sd);
    exit(-1);
  } else {
    printf("UDP Server - recvfrom() is OK...\n");
  }

  printf("UDP Server received message:\n %s \n", bufptr);
  printf("from port %d and address %s.\n", ntohs(clientaddr.sin_port),
         inet_ntoa(clientaddr.sin_addr));

  printf("Server replying to client...\n");

  rc = sendto(sd, bufptr, buflen, 0, (struct sockaddr *)&clientaddr,
              clientaddrlen);

  if (rc < 0) {
    perror("UDP server - sendto() error");
    close(sd);
    exit(-1);
  } else
    printf("UDP Server - sendto() is OK...\n");

  close(sd);
  exit(0);
}