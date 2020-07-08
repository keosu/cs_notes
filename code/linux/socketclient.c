
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERVER "bakawali"
#define SERVPORT 3333

int main(int argc, char *argv[]) {
  int sd, rc;
  struct sockaddr_in serveraddr, clientaddr;
  int serveraddrlen = sizeof(serveraddr);
  char server[255];
  char buffer[100];
  char *bufptr = buffer;
  int buflen = sizeof(buffer);
  struct hostent *hostp;
  memset(buffer, 0x00, sizeof(buffer));
  /* 36 characters + terminating NULL */
  memcpy(buffer, "Hello! A client request message lol!", 37);

  /* get a socket descriptor */
  if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("UDP Client - socket() error");
    exit(-1);
  } else
    printf("UDP Client - socket() is OK!\n");

  if (argc > 1)
    strcpy(server, argv[1]);
  else {
    /*Use default hostname or IP*/
    printf("UDP Client - Usage %s <Server hostname or IP>\n", argv[0]);
    printf("UDP Client - Using default hostname/IP!\n");
    strcpy(server, SERVER);
  }
  memset(&serveraddr, 0x00, sizeof(struct sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(SERVPORT);
  if ((serveraddr.sin_addr.s_addr = inet_addr(server)) ==
      (unsigned long)INADDR_NONE) {
    hostp = gethostbyname(server);
    if (hostp == (struct hostent *)NULL) {
      printf("HOST NOT FOUND --> ");
      printf("h_errno = %d\n", h_errno);
      exit(-1);
    } else {
      printf("UDP Client - gethostname() of the server is OK... \n");
      printf("Connected to UDP server %s on port %d.\n", server, SERVPORT);
    }
    memcpy(&serveraddr.sin_addr, hostp->h_addr, sizeof(serveraddr.sin_addr));
  }

  rc = sendto(sd, bufptr, buflen, 0, (struct sockaddr *)&serveraddr,
              sizeof(serveraddr));
  if (rc < 0) {
    perror("UDP Client - sendto() error");
    close(sd);
    exit(-1);
  } else
    printf("UDP Client - sendto() is OK!\n");
  printf("Waiting a reply from UDP server...\n");

  rc = recvfrom(sd, bufptr, buflen, 0, (struct sockaddr *)&serveraddr,
                &serveraddrlen);
  if (rc < 0) {
    perror("UDP Client - recvfrom() error");
    close(sd);
    exit(-1);
  } else {
    printf("UDP client received the following: \"%s\" message\n", bufptr);
    printf(" from port %d, address %s\n", ntohs(serveraddr.sin_port),
           inet_ntoa(serveraddr.sin_addr));
  }
  close(sd);
  exit(0);
}
